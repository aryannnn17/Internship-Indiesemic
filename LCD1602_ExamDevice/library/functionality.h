#include "i2c-lcd.h"
#include "keypad_driver.h"
#include "stdint.h"
#include "glob_var.h"	
#include "eeprom_at24.h"

#ifndef __FUNCTIONALITY_H__
#define __FUNCTIONALITY_H__

extern char input[4];
extern volatile int digit_count;
extern char key;

/**
 * @brief Prints Welcome Message on LCD
*/
fw_states welcome_notes(void);
/**
 * @brief Asks user to enter their enrollment number
*/
fw_states enter_roll_number(void);
/**
 * @brief User will be able see his entered enrollment
*/
void confirm_credentials(struct student_credentials *student);
/**
 * @brief Invalid Enrollment Handler
*/
void invalid_enrollment(void);
/**
 * @brief User need to enter subject code
*/
void enter_subject_code(void);
/**
 * @brief Show user his entered subject code and provide option to edit
*/
void confirm_subject_code(struct student_credentials *student);
/**
 * @brief Invalid subject code handler
*/
void invalid_subject_code(void);
/**
 * @brief User will enter center number
*/
void enter_center_number(void);
/**
 * @brief Show user his entered center number and provide option to edit
*/
void confirm_center_number(struct student_credentials *student);
/**
 * @brief Invalid Center number handler
*/
void invalid_center_number(void);
/**
 * @brief Asks user to enter Paper Code
 * User can only enter Paper Code in form of A, B, C, or D (One Character Only)
*/
void enter_paper_code(void);
/**
 * @brief Show user his entered paper code and provide option to edit
*/
void confirm_paper_code(struct student_credentials *student);
/**
 * @brief Sets up LCD for user to enter Que No. and Ans. No.
*/
void setup_for_que(struct student_credentials student);
/**
 * @brief Handles Asking Que and Ans 
*/
fw_states que_ans(void);
/**
 * @brief Asks user to confirm their submission or not
*/
fw_states confirm_submission(void);
/**
 * @brief Function to handle paper submission
 * @attention For now it only starts application again
*/
fw_states submit_paper(void);
/**
 * @brief Verify and Edit answers
*/
fw_states verify_paper(void);
/**
 * @brief Save data to eeprom
*/
void save_2_eeprom(struct student_credentials student);

#endif /* __FUNCTIONALITY_H__ */