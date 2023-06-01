# ENCE_3220_Class2023-
PHASE_D
~ This respository contains contents of Phase D Final project "GPS Tracker with SMS messaging" 
Note : 5/32/23
Due to the SIM cardarriving lateand the acctication not being done creecly the SMS part of this project has be put
on hold to meet the deadline. 

## System Design 
 The overall object was to create a GPS tracker systems that would send Longitude and Latitude in a SMS to a phone.
 The block diagrams below display the evloution of the devopling this project starting off with a basic conecpt 
 and slowly evoling from protyopeing on the arduino to implmeting the module with the STM32 Discocery Board 
 
![image](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/c69a686b-6c91-4899-a331-ec60d530319d)

## Prototyping 
Prototyping for this proejct was done by testing each compnets and getting them to interface with an Ardunio Uno then transfering the knowlege learn to the STM32 Discovery board 

![image](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/83ae9884-e527-46f1-886e-71a5871548bc)

![GPS_RAW_DATA](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/fceb9dd3-2046-4c33-a46e-fa7b2639cb6b)
The image above displayes the raw data that is transmited by the GPS modlue direct through UART 

![GPS Data Working ](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/eeae7de8-ce9f-4c0e-b192-999afaa40916)
Using the Ardunio IDE there is a simple libary that takes the raw data and pase it to the corresopnding fomart that we want and can be seen above

## PCB Design 
### Schematic 
 ![image](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/8cb68cb9-03de-4ac0-9b43-e8331ea3aa7c)

### PCB Layout 
![image](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/fab208b2-f1e2-4ff3-8316-e27af6444165)


### 3D Renders 
Front View 
![Fornt_View](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/924bf65d-a44f-4430-81db-e1cd7f6089d8)

Back View 
![Back_View](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/ae01185c-33e3-4e0b-a31a-cddc7b99f09f)

Isometric View 
![Isometric_View](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/f69a15d1-7a3d-4195-a3cd-587e14a458bb)

## SoftWare Development 
The basic overview of the code on the STM32 can be seen below 
![image](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/7af97238-733f-4bbd-bdfd-fbc44794dd40)

A more deatail view of whatis inside of what is inside the main function can be seen below 
![image](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/5d20884c-23ae-427a-9744-17f016b0c240)

The code then lead to the correct parseing of data of the "GPRMC" NEMA sentice
![image](https://github.com/DANYSR8/ENCE_3220_Class2023-/assets/117769464/d56b4e7a-ce78-4dc3-9f6b-ab1e476fe7ab)

