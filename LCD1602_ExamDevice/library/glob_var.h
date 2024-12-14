#ifndef __GLOBAL_VARIABLE_H__
#define __GLOBAL_VARIABLE_H__

typedef enum fw_states_t
{
    /** @brief init states */
    STATE_START_APP,
    STATE_ASK_ROLL_NO,
    STATE_CONFIRM_ROLL_NO,
    STATE_ENTER_SUB_CODE,
    STATE_CONFIRM_SUB_CODE,
    STATE_ENTER_CENTER_NO,
    STATE_CONFIRM_CENTER_NO,
    /** @brief Exam States*/
    STATE_ASK_PAPER_CODE,
    STATE_CONFIRM_PAPER_CODE,
    STATE_LCD_QUE_SETUP,
    STATE_SETUP_NEXT_QUE,
    STATE_CONFIRM_SUBMIT,
    STATE_VERIFY,
    STATE_SUBMIT,
    STATE_SEND_DATA,
    STATE_BLUETOOTH_START,
    STATE_BLUETOOTH_STOP,
    STATE_IDLE,
    /** @brief INAVALID STATES */
    STATE_INVALID_ENROLLMENT,
    STATE_INVALID_SUBJECT_CODE,
    STATE_INVALID_CENTER_CODE,
    STATE_INVALID_QUESTION,
}fw_states;

struct student_credentials
{
	uint64_t roll_number;
    uint32_t subject_code;
    uint32_t center_code;
	char paper_type;
    char answers[10][2];
};

extern char QnA[10][2];
extern unsigned int STATES;
extern struct student_credentials student;

#endif