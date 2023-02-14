/******************************************************************************
 *
 * Description: Header file for the Door Locker Security Systems (Control ECU)
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define READY                          0
#define ENTER_PASS                     2
#define RE_ENTER_PASS                  3
#define OPEN_DOOR                      4
#define CLOSE_DOOR                     5
#define BUZZER_ON                      6
#define MAIN_OPTIONS                   7


#define MATCHED                     0
#define UNMATCHED                   1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function to create password option
 */
void Control_ECU_createPass(void);
/*
 * Description :
 * Function to get password from user till '=' at the first use
 */
void create_pass(void);
/*
 * Description :
 * Function to get password from user till '='
 * check it matched with the password or no
 * if matched then store it in EEPROM
 */
uint8 reenter_pass(void);

/*
 * Description :
 * Function responsible to store password in EEPROM (in case of matched)
 */
void store_pass(void);
uint8 main_options(void);
void Control_ECU_openDoor(void);
/*
 * Description :
 * Function to get password from user till '='
 */
void enter_pass(void);
uint8 compare_pass (void);
void unmached_pass(void);
void Control_ECU_changePass(void);
#endif /* CONTROL_ECU_H_ */
