/* Zephyr Includes */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

/* Custom Includes */
#include "i2c-lcd.h"
#include "keypad_driver.h"
#include "functionality.h"
#include "glob_var.h"
#include "ble_handler.h"
#include "errno.h"
#include "eeprom_at24.h"

/* C standard Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student_credentials student;
unsigned int STATES;

int main(void)
{
	printk("The I2C 16x2 display and 4x4 matrix keypad\n");

	if (!device_is_ready(i2c_dev))
	{
		printk("I2C device is not ready\r\n");
		return 0;
	}

	if (!device_is_ready(R0_4x4.port))
	{
		printk("GPIO device is not ready\r\n");
		return 1;
	}

	// ble_init();
	// start_ble();
	GPIO_config();
	eeprom_init();
	STATES = STATE_START_APP;

	while (true)
	{
		switch (STATES)
		{
		case STATE_START_APP:
			lcd_init();
			lcd_clear();
			k_sleep(K_MSEC(1000));
			lcd_clear();
			welcome_notes();
			break;
		case STATE_ASK_ROLL_NO:
			enter_roll_number();
			break;
		case STATE_CONFIRM_ROLL_NO:
			confirm_credentials(&student);
			break;
		case STATE_ENTER_SUB_CODE:
			enter_subject_code();
			break;
		case STATE_CONFIRM_SUB_CODE:
			confirm_subject_code(&student);
			break;
		case STATE_ENTER_CENTER_NO:
			enter_center_number();
			break;
		case STATE_CONFIRM_CENTER_NO:
			confirm_center_number(&student);
			break;
		case STATE_ASK_PAPER_CODE:
			enter_paper_code();
			break;
		case STATE_CONFIRM_PAPER_CODE:
			confirm_paper_code(&student);
			break;
		case STATE_LCD_QUE_SETUP:
			setup_for_que(student);
			que_ans();
			break;
		case STATE_SETUP_NEXT_QUE:
			setup_for_que(student);
			que_ans();
			break;
		case STATE_VERIFY:
			verify_paper();
			break;
		case STATE_CONFIRM_SUBMIT:
			confirm_submission();
			break;
		case STATE_SUBMIT:
			submit_paper();
			break;
		case STATE_IDLE:
			k_sleep(K_MSEC(5000));
			break;

		/** @category INVALID STATES */
		case STATE_INVALID_ENROLLMENT:
			invalid_enrollment();
			break;
		case STATE_INVALID_SUBJECT_CODE:
			invalid_subject_code();
			break;
		case STATE_INVALID_CENTER_CODE:
			invalid_center_number();
			break;
		default:
			break;
		}
		k_sleep(K_MSEC(500));
	}
}
