/******************************************************************************
 *
 * Description: Header file for the Door Locker Security Systems (Human Machine Interface)
 *
 * Author: Esraa Mohamed
 *
 *******************************************************************************/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

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

/* Function to :
 * Take the password from user
 * Send the pass to Control_ECU by UART
 * Display * on the screen
 */
void HMI_ECU_takePass(void);


#endif /* HMI_ECU_H_ */
