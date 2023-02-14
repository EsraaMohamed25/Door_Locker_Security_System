/******************************************************************************
 *
 * Description: Source file for the Door Locker Security Systems (Control ECU)
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/
#include <util/delay.h>
#include <avr/io.h>
#include "Control_ECU.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "uart.h"
#include "timers.h"

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

static volatile uint16 current_password;
static volatile uint16 new_password;
static volatile uint16 reenter_password;
static volatile uint16 stored_password;
static volatile uint16 eeprom_password;
static volatile uint16 eeprom_first_location = 0x0311;
static volatile uint16 eeprom_last_location;
static volatile uint8 pass_counter;
static volatile uint8 KEY;
static volatile uint8 counter;

Timer1_ConfigType Timer1_Config ={ 0,1000 ,F_CPU_1024,CTC};

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

/*
 * Description :
 * Function to create password option
 */
void Control_ECU_createPass(void){

	for(;;){
		UART_sendByte(ENTER_PASS);
		create_pass();

		UART_sendByte(RE_ENTER_PASS);
		uint8 re =reenter_pass();
		if(re == UNMATCHED)

			UART_sendByte(ENTER_PASS);
		else
			break;
	}
}


/*
 * Description :
 * Function to get password from user till '=' at the first use
 */
void create_pass(void){
	uint8 i,Rx;
	new_password = 0;
	UART_sendByte(READY);

	for(i=0;i < 5;i++){
		Rx = UART_recieveByte();
		if(Rx == '=')
			break;
		else
			new_password = (new_password * 10)+Rx;
	}
}
/*
 * Description :
 * Function to get password from user till '='
 * check it matched with the password or no
 * if matched then store it in EEPROM
 */
uint8 reenter_pass(void){
	uint8 i,Rx;
	reenter_password = 0;
	UART_sendByte(READY);

	for(i=0;i < 5;i++){
		Rx = UART_recieveByte();
		if(Rx == '=')
			break;
		else
			reenter_password = (reenter_password * 10)+ Rx;
	}
	if (new_password == reenter_password){
		store_pass();
		return MATCHED;
	}
	else
		return UNMATCHED;
}
/*
 * Description :
 * Function responsible to store password in EEPROM (in case of matched)
 */
void store_pass(void){

	eeprom_password = new_password;
	eeprom_last_location = eeprom_first_location;

	while(eeprom_password !=0){
		EEPROM_writeByte(eeprom_last_location ,eeprom_password %10);
		_delay_ms(10);
		eeprom_last_location++;
		eeprom_password = eeprom_password / 10;
	}
	eeprom_last_location--;
}
/*
 * Description :
 * Function responsible to recieve the option from user
 */
uint8 main_options(void){

	UART_sendByte(READY);
	for(;;){
		KEY = UART_recieveByte();
		if(	KEY == '+' || KEY == '-' )
			break;
	}
	return KEY;
}
/*
 * Description:
 * Function to count number of overflows
 */
void timer1(void){
	counter++;
}
/*
 * Description :
 * Function to open the door for 3 sec
 */
void open_door(void){
	DcMotor_Rotate(CW,100);
	//DELAY 15 SEC
	Timer1_setCallBack(timer1);
	Timer1_init(&Timer1_Config);
	while(counter < 15);
	Timer1_deInit();
	counter =0;
	DcMotor_Rotate(stop,0);
	//DELAY 3 SEC
	Timer1_setCallBack(timer1);
	Timer1_init(&Timer1_Config);
	while(counter < 3);
	Timer1_deInit();
	counter =0;
}
/*
 * Description :
 * Function to close the door
 */
void close_door(void){
	DcMotor_Rotate(A_CW,100);
	//DELAY 15 SEC
	Timer1_setCallBack(timer1);
	Timer1_init(&Timer1_Config);
	while(counter < 15);
	Timer1_deInit();
	counter =0;
	DcMotor_Rotate(stop,0);
}
/*
 * Description :
 * Function to open the door option
 */
void Control_ECU_openDoor(void){
	for(;;){
		UART_sendByte(ENTER_PASS);
		enter_pass();
		if (compare_pass() == MATCHED){
			pass_counter = 0;
			UART_sendByte(OPEN_DOOR);
			open_door();
			UART_sendByte(CLOSE_DOOR);
			close_door();
			return;
		}
		else{
			unmached_pass();
		}
	}
}
/*
 * Description :
 * Function to get password from user till '='
 */
void enter_pass(void){

	uint8 i,Rx;
	current_password = 0;
	UART_sendByte(READY);

	for(i=0;i < 5;i++){
		Rx = UART_recieveByte();
		if(Rx == '=')
			break;
		else
			current_password = (current_password * 10)+ Rx;
	}
}
/*
 * Description :
 * Function to compare the stored password with the current pass
 */
uint8 compare_pass (void){

	stored_password=0;
	uint16 i;
	uint8 byte =0;
	for( i = eeprom_last_location ;i >= eeprom_first_location ;i--){
		EEPROM_readByte(i, &byte);
		stored_password = (stored_password * 10 ) + byte;
	}
	if(current_password == stored_password)
		return MATCHED;
	else
		return UNMATCHED;
}

/*
 * Description :
 * Function to count the unmatched pass and fire alarm if exceed 3 times
 */
void unmached_pass(void){

	pass_counter++;
	if(pass_counter == 3){
		pass_counter = 0;

		UART_sendByte(BUZZER_ON);
		Buzzer_on();
		//delay 1 min
		Timer1_setCallBack(timer1);
		Timer1_init(&Timer1_Config);
		while(counter < 60);
		Timer1_deInit();
		counter =0;
		Buzzer_off();
	}
	return;
}

/*
 * Description :
 * Function to change pass option
 */
void Control_ECU_changePass(void){

	for(;;){
		UART_sendByte(ENTER_PASS);
		enter_pass();
		if (compare_pass() == MATCHED){
			pass_counter = 0;
			Control_ECU_createPass();
			return;

		}
	}
}
