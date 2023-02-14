# Door_Locker_Security_System
### System to unlock a door using a password.
## Drivers:
> GPIO, Keypad, LCD, Timer, UART, I2C, EEPROM, Buzzer and DC-Motor.
## Microcontroller:
> ATmega32
## Desciption :
##### The System consists of 2 ECU’s: 
###### The first ECU called HMI is responsible for interactioning with the user by taking inputs through keypad and display messages on the LCD. 
###### The second ECU called control ECU which is responsible for all the processing and decisions in the system like password checking, open the door and activate the system alarm. In the project I implemented the following drivers Keypad, LCD, DC Motor, UART, Timer, I2C and External EEPROM.

## Door Locker System Sequence:
1. The user create password by entering from HMI-ECU two times and send data byte by byte to Control-ECU by UART to check them if matched then store password in EEPROM, otherwise ECU will asking user to re-enter password again two times till it matched.
2. Go to Home Screen wich display 2 main options to user:
'+': Open Door 
'-': Change Password
in both cases it will ask the user to enter the password then send password to Control-ECU by UART to get current password from EEPROM to match it with entered password from user.
3. Open Door Option:
  - If matched: Turn DC motor On to rotate Clock_wise for 15 Sec (as door is opening) then   hold the motor for 3-seconds then DC motor rotate Anti-ClockWise for 15 Sec (as door is closing).
  - If the two passwords are not matched for 3 consecutive times, then:
      • Activate Buzzer for 1-minute (alarm).
      • Display error message on LCD for 1 minute.
      • System should be locked no inputs from Keypad will be accepted during this period.
      • Go to Step 2 the main options again.
4. Change password Option:
  - If matched: Go to Step 1 (enter the pass twice)
  - If the two passwords are not matched for 3 consecutive times, then:
      • Activate Buzzer for 1-minute (alarm).
      • Display error message on LCD for 1 minute.
      • System should be locked no inputs from Keypad will be accepted during this period.
      • Go to Step 2 the main options again
