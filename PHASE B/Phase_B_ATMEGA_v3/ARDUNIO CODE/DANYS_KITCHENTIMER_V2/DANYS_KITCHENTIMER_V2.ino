#define BUTTON_1  2
#define BUTTON_2  3
#define GREEN_LED 4
#define RED_LED   5
#define BUZZER    6

#define DATA      9   
#define LATCH     8  
#define CLOCK     7  

#define DIGIT_4   10
#define DIGIT_3   11
#define DIGIT_2   12
#define DIGIT_1   13
 // number table 
unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c
,0x39,0x5e,0x79,0x71,0x00};

byte current_digit;

unsigned char count = 10;
unsigned int buttonState = 0;  // variable for reading the pushbutton status

volatile unsigned char isr_1_flag = 0;   // will be the incremnet button 
volatile unsigned char isr_2_flag = 0;   // Buzzer flag 
volatile unsigned char isr_3_flag = 0;   // system clock flag 

int timerstop = 1 ; 

void setup() 
{
   // LEDs Pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(BUZZER , OUTPUT);

  // Button Pins
  pinMode(BUTTON_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), Button_1_ISR, CHANGE);
  pinMode(BUTTON_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), Button_2_ISR, CHANGE);

  // 7-Seg Display
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  // Shift Register Pins
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);

  disp_off();

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 62500;            // 1 second refresh  
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts

 // Seting up timer 2 
  TCCR2A = 0;
  TCCR2B = 0;
  OCR2A = 10;            // 7 segment display refresh time 
  TCCR2A |= (1 << WGM21);   // CTC mode
  TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);    // 256 prescaler 
  TIMSK2 |= (1 << OCIE2A);  // enable timer compare interrupt  
  interrupts();             // enable all interrupts

  
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void display(unsigned char num, unsigned char dp)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, table[num] | (dp<<7));
  digitalWrite(LATCH, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void disp_off()
{
   digitalWrite(DIGIT_1, HIGH);  // HIGH means the display is off 
   digitalWrite(DIGIT_2, HIGH);
   digitalWrite(DIGIT_3, HIGH);
   digitalWrite(DIGIT_4, HIGH);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Button_1_ISR()                           // Flag needs to be clear in Loop 
{
  // Set ISR Flag
  isr_1_flag = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void Button_2_ISR()                           // Flag needs to be clear in Loop 
{ 
  // Set ISR Flag
  isr_2_flag = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER1_COMPA_vect) // timer compare interrupt service routine ---> 1 second counter 
{                      // Flag needs to be clear in Loop 
  // Set ISR Flag
  isr_3_flag = 1;

}
/////////////////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER2_COMPA_vect) // timer compare interrupt service routine -- > updates the timer mutiple times in a second 
{                     
  disp_off();  // turn off the display
 
  switch (current_digit)
  {
    case 1: //0x:xx
      display( int((count/60) / 10) % 6, 0 );   // prepare to display digit 1 (most left)
      digitalWrite(DIGIT_1, LOW);  // turn on digit 1
      break;
 
    case 2: //x0:xx
      display( int(count / 60) % 10, 1 );   // prepare to display digit 2
      digitalWrite(DIGIT_2, LOW);     // turn on digit 2
      break;
 
    case 3: //xx:0x
      display( (count / 10) % 6, 0 );   // prepare to display digit 3
      digitalWrite(DIGIT_3, LOW);    // turn on digit 3
      break;
 
    case 4: //xx:x0
      display(count % 10, 0); // prepare to display digit 4 (most right)
      digitalWrite(DIGIT_4, LOW);  // turn on digit 4
      break;

    default:
      break;
  }
 
  current_digit = (current_digit % 4) + 1;

}

/////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  

  if(isr_1_flag == 1)  // this reads the when the incremnet button is press 
  {
    isr_1_flag = 0 ;    // inturput is reset 
    count++ ;           // count is incremented 
    

  }
  
   if(isr_3_flag == 1 && timerstop == 0)    // Attends to the timer updateing it with the system clock 
   {
    
    isr_3_flag = 0;                   // Reset ISR Flag
    digitalWrite(GREEN_LED, LOW);     // Green LED is off while counting down 
    digitalWrite(RED_LED, HIGH);      // Red LED is on while counting down
    digitalWrite(BUZZER ,LOW);
    count-- ;                         // incremnets the count down 
    

    if (count == 0 || isr_2_flag == 1)  // stops the timer updating 
    {
      isr_2_flag = 0;
      timerstop = 1 ; 
      digitalWrite(GREEN_LED, HIGH);    // sets Green Led on and Red LED off 
      digitalWrite(RED_LED, LOW);
      digitalWrite(BUZZER ,HIGH);
     
            
    }
 
   }

   if(isr_2_flag == 1 )                 // Stars the timer agian after incremneting 
   {
     isr_2_flag = 0; 
     timerstop = 0;
   }
 
  
}
