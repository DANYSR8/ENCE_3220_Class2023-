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

unsigned char count = 9;
unsigned int buttonState = 0;  // variable for reading the pushbutton status

volatile unsigned char isr_1_flag = 0;
volatile unsigned char isr_2_flag = 0;
volatile unsigned char isr_3_flag = 0;

int timerstop = 0 ; 

void setup() {
   // LEDs Pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

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

  disp_on();

  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 62500;            // compare match register 16MHz/256 ////Setting the time speed 
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
}
//////////////////////////////////////////////////////////////////////////////////////////////////

void Display(unsigned char num)
{

  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, table[num]);
  digitalWrite(LATCH, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void Display_Numbers()
{// This function is not used 
  Display(count);
  // Reset Counter
  if(count == 0)
  {
    count = 10;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////

void disp_on()
{
   digitalWrite(DIGIT_1, LOW);  // HIGH means the display is off 
   digitalWrite(DIGIT_2, LOW);
   digitalWrite(DIGIT_3, LOW);
   digitalWrite(DIGIT_4, LOW);
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
ISR(TIMER1_COMPA_vect) // timer compare interrupt service routine
{                                             // Flag needs to be clear in Loop 
  // Set ISR Flag
  isr_3_flag = 1;

/////////////////////////////////////////////////////////////////////////////////////////////////
}
void loop() {
  


  if(isr_1_flag == 1)  // this reads the when the incremnet button is press 
  {
    isr_1_flag = 0 ;    // inturput is reset 
    count++ ;           // count is incremented 
    Display(count);     // new count value is dispated 

    if(count == 10)    // This Reset Counter once ten is reached 
   {
    count = 0;
  }

  }
  
   if(isr_3_flag == 1 && timerstop == 0)    // Attends to the timer updateing it with the system clock 
   {
    
    isr_3_flag = 0;                   // Reset ISR Flag
    digitalWrite(GREEN_LED, LOW);     // Green LED is off while counting down 
    digitalWrite(RED_LED, HIGH);      // Red LED is on while counting down
    count-- ;                         // incremnets the count down 
    Display(count);                   // shows upadte count value

    if (count == 0 || isr_2_flag == 1)  // stops the timer updating 
    {
      isr_2_flag = 0;
      timerstop = 1 ; 
      digitalWrite(GREEN_LED, HIGH);    // sets Green Led on and Red LED off 
      digitalWrite(RED_LED, LOW);
     
            
    }

     
  }

   if(isr_2_flag == 1 )                 // Stars the timer servecie by pressing the start button 
   {
     isr_2_flag = 0; 
     timerstop = 0;
   }
  
  
}


