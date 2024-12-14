#include "functionality.h"

char key;
volatile int temp = 0;
char confirm_input[15];
char QnA[10][2] = {0};

struct student_credentials _student;
struct student_credentials eeprom_data;

fw_states welcome_notes(void)
{
	bool START_EXAM = false;
	lcd_put_cur(0, 0);
	lcd_send_string("WELCOME TO EXAM");
	lcd_put_cur(1, 0);
	lcd_send_string("TO CONTINUE");
	lcd_put_cur(1, 12);
	lcd_send_data(0x7E);
	lcd_put_cur(1, 14);
	lcd_send_data('#');
	// k_msleep(2000);
	while (START_EXAM == false)
	{
		key = read_keypad();
		switch (key)
		{
		case '#':
			STATES = STATE_ASK_ROLL_NO;
			START_EXAM = true;
			return STATES;
			break;

		default:
			break;
		}
	}
}

fw_states enter_roll_number(void)
{
	char input[15] = {0};
	volatile int digit_count = 0;
	bool roll_number_entered = false;
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("ENTER ROLLNO:");
	lcd_put_cur(1, 0);
	digit_count = 0;
	while (roll_number_entered == false)
	{

		key = read_keypad();
		switch (key)
		{
		case '0':
			input[digit_count] = '0';
			digit_count++;
			lcd_send_data('0');
			break;
		case '1':
			input[digit_count] = '1';
			digit_count++;
			lcd_send_data('1');
			break;
		case '2':
			input[digit_count] = '2';
			digit_count++;
			lcd_send_data('2');
			break;
		case '3':
			input[digit_count] = '3';
			digit_count++;
			lcd_send_data('3');
			break;
		case '4':
			input[digit_count] = '4';
			digit_count++;
			lcd_send_data('4');
			break;
		case '5':
			input[digit_count] = '5';
			digit_count++;
			lcd_send_data('5');
			break;
		case '6':
			input[digit_count] = '6';
			digit_count++;
			lcd_send_data('6');
			break;
		case '7':
			input[digit_count] = '7';
			digit_count++;
			lcd_send_data('7');
			break;
		case '8':
			input[digit_count] = '8';
			digit_count++;
			lcd_send_data('8');
			break;
		case '9':
			input[digit_count] = '9';
			digit_count++;
			lcd_send_data('9');
			break;
		case '#':
			if (digit_count >= 13)
			{
				STATES = STATE_INVALID_ENROLLMENT;
				return STATES;
			}
			else if (digit_count > 0)
			{
				input[digit_count++] = '\0';
				digit_count = 0;
				sscanf(input, "%llu", &_student.roll_number);
				lcd_put_cur(1, 0);
				lcd_send_string(input);
				roll_number_entered = true;
				break;
			}
			else
				break;
		default:
			break;
		}
	}
	if (roll_number_entered == true)
	{
		memset(input, 0x00, sizeof(input));
		// printk("\r\nStudent number: %llu\r\n", _student.roll_number);
		STATES = STATE_CONFIRM_ROLL_NO;
		return STATES;
	}
}

void confirm_credentials(struct student_credentials *student)
{
	bool CRED_CONFIRMED = false;
	lcd_clear();
	lcd_put_cur(0, 0);
	sprintf(confirm_input, "%llu", _student.roll_number);
	lcd_send_string("Confirm RollNo:");
	lcd_put_cur(1, 0);
	lcd_send_string(confirm_input);
	while (CRED_CONFIRMED == false)
	{
		key = read_keypad();
		switch (key)
		{
		case 'E':
			STATES = STATE_ASK_ROLL_NO;
			CRED_CONFIRMED = true;
			break;
		case '#':
			CRED_CONFIRMED = true;
			break;
		}
	}
	if (CRED_CONFIRMED == true)
	{
		student->roll_number = _student.roll_number;
		printk("\tStd: %llu\n", student->roll_number);
		save_2_eeprom(*student);
		STATES = STATE_ENTER_SUB_CODE;
	}
	
}

void invalid_enrollment(void)
{
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Invalid Roll No");
	lcd_put_cur(1, 0);
	lcd_send_string("Try Again!");
	k_sleep(K_MSEC(2000));
	STATES = STATE_ASK_ROLL_NO;
	return;
}

void enter_subject_code(void)
{
	bool IS_SUBJECT_CODE_ENTERED = false;
	char input[8] = {0};
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Subject Code:");
	lcd_put_cur(1, 0);
	volatile int digit_count = 0;
	while (IS_SUBJECT_CODE_ENTERED == false)
	{
		key = read_keypad();
		switch (key)
		{
		case '0':
			input[digit_count] = '0';
			digit_count++;
			lcd_send_data('0');
			key = 0;
			break;
		case '1':
			input[digit_count] = '1';
			digit_count++;
			lcd_send_data('1');
			key = 0;
			break;
		case '2':
			input[digit_count] = '2';
			digit_count++;
			lcd_send_data('2');
			key = 0;
			break;
		case '3':
			input[digit_count] = '3';
			digit_count++;
			lcd_send_data('3');
			key = 0;
			break;
		case '4':
			input[digit_count] = '4';
			digit_count++;
			lcd_send_data('4');
			key = 0;
			break;
		case '5':
			input[digit_count] = '5';
			digit_count++;
			lcd_send_data('5');
			key = 0;
			break;
		case '6':
			input[digit_count] = '6';
			digit_count++;
			lcd_send_data('6');
			key = 0;
			break;
		case '7':
			input[digit_count] = '7';
			digit_count++;
			lcd_send_data('7');
			key = 0;
			break;
		case '8':
			input[digit_count] = '8';
			digit_count++;
			lcd_send_data('8');
			key = 0;
			break;
		case '9':
			input[digit_count] = '9';
			digit_count++;
			lcd_send_data('9');
			key = 0;
			break;
		// case 'A':
		// 	input[digit_count] = 'A';
		// 	digit_count++;
		// 	lcd_send_data('A');
		// 	key = 0;
		// 	break;
		// case 'B':
		// 	input[digit_count] = 'B';
		// 	digit_count++;
		// 	lcd_send_data('B');
		// 	key = 0;
		// 	break;
		// case 'C':
		// 	input[digit_count] = 'C';
		// 	digit_count++;
		// 	lcd_send_data('C');
		// 	key = 0;
		// 	break;
		// case 'D':
		// 	input[digit_count] = 'D';
		// 	digit_count++;
		// 	lcd_send_data('D');
		// 	key = 0;
		// 	break;
		case '#':
			if (digit_count > 7)
			{
				STATES = STATE_INVALID_SUBJECT_CODE;
				return;
				break;
			}
			else if (digit_count < 6)
			{
				STATES = STATE_INVALID_SUBJECT_CODE;
				return;
				break;
			}
			else if (digit_count <= 7 && digit_count >= 6)
			{
				input[digit_count++] = '\0';
				sscanf(input, "%lu", &_student.subject_code);
				lcd_put_cur(1, 0);
				lcd_send_string(input);
				IS_SUBJECT_CODE_ENTERED = true;
				digit_count = 0;
			}
			break;

		default:
			break;
		}
	}
	if (IS_SUBJECT_CODE_ENTERED == true)
	{
		memset(input, 0x00, sizeof(input));
		printk("Subject Code: %lu\n", _student.subject_code);
		STATES = STATE_CONFIRM_SUB_CODE;
	}
}

void confirm_subject_code(struct student_credentials *student)
{
	bool IS_SUBJECT_CODE_CONFIRMED = false;
	char output[9] = {0};
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	k_sleep(K_USEC(40));
	lcd_send_string("Confirm Code:");
	sprintf(output, "%zu", &_student.subject_code);
	printk("Output: %s\n", output);
	lcd_put_cur(1, 0);
	k_sleep(K_USEC(40));
	lcd_send_string(output);
	while (IS_SUBJECT_CODE_CONFIRMED == false)
	{
		key = read_keypad();
		switch (key)
		{
		case 'E':
			STATES = STATE_ENTER_SUB_CODE;
			return;
			break;
		case '#':
			IS_SUBJECT_CODE_CONFIRMED = true;
			break;
		default:
			break;
		}
	}
	if (IS_SUBJECT_CODE_CONFIRMED == true)
	{
		student->subject_code = _student.subject_code;
		printk("Confirmed Subject Code: %lu\n", student->subject_code);
		save_2_eeprom(*student);
		STATES = STATE_ENTER_CENTER_NO;
	}
}

void invalid_subject_code(void)
{
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Invalid Sub code");
	lcd_put_cur(1, 0);
	lcd_send_string("Try Again!");
	k_sleep(K_MSEC(2000));
	STATES = STATE_ENTER_SUB_CODE;
	return;
}

void enter_center_number(void)
{
	bool IS_CENTER_CODE_ENTERED = false;
	char input[6] = {0};
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Center Code:");
	lcd_put_cur(1, 0);
	volatile int digit_count = 0;
	while (IS_CENTER_CODE_ENTERED == false)
	{
		key = read_keypad();
		switch (key)
		{
		case '0':
			input[digit_count] = '0';
			digit_count++;
			lcd_send_data('0');
			key = 0;
			break;
		case '1':
			input[digit_count] = '1';
			digit_count++;
			lcd_send_data('1');
			key = 0;
			break;
		case '2':
			input[digit_count] = '2';
			digit_count++;
			lcd_send_data('2');
			key = 0;
			break;
		case '3':
			input[digit_count] = '3';
			digit_count++;
			lcd_send_data('3');
			key = 0;
			break;
		case '4':
			input[digit_count] = '4';
			digit_count++;
			lcd_send_data('4');
			key = 0;
			break;
		case '5':
			input[digit_count] = '5';
			digit_count++;
			lcd_send_data('5');
			key = 0;
			break;
		case '6':
			input[digit_count] = '6';
			digit_count++;
			lcd_send_data('6');
			key = 0;
			break;
		case '7':
			input[digit_count] = '7';
			digit_count++;
			lcd_send_data('7');
			key = 0;
			break;
		case '8':
			input[digit_count] = '8';
			digit_count++;
			lcd_send_data('8');
			key = 0;
			break;
		case '9':
			input[digit_count] = '9';
			digit_count++;
			lcd_send_data('9');
			key = 0;
			break;
		case '#':
			if (digit_count > 5)
			{
				STATES = STATE_INVALID_CENTER_CODE;
				return;
				break;
			}
			else if (digit_count < 4)
			{
				STATES = STATE_INVALID_CENTER_CODE;
				return;
				break;
			}
			else if (digit_count <= 5 && digit_count >= 4)
			{
				input[digit_count] = '\0';
				sscanf(input, "%lu", &_student.center_code);
				lcd_put_cur(1, 0);
				lcd_send_string(input);
				IS_CENTER_CODE_ENTERED = true;
				digit_count = 0;
			}
			break;
		default:
			break;
		}
	}
	if (IS_CENTER_CODE_ENTERED == true)
	{
		memset(input, 0x00, sizeof(input));
		printk("Center Code: %lu\n", _student.center_code);
		STATES = STATE_CONFIRM_CENTER_NO;
	}
}

void confirm_center_number(struct student_credentials *student)
{
	bool IS_CENTER_NO_CONFIRMED = false;
	char output[7] = {0};
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Confirm Number:");
	lcd_put_cur(1, 0);
	sprintf(output, "%lu", _student.center_code);
	lcd_send_string(output);
	while (IS_CENTER_NO_CONFIRMED == false)
	{
		key = read_keypad();
		switch (key)
		{
		case 'E':
			STATES = STATE_ENTER_CENTER_NO;
			return;
			break;
		case '#':
			IS_CENTER_NO_CONFIRMED = true;
			break;
		default:
			break;
		}
	}
	if (IS_CENTER_NO_CONFIRMED == true)
	{
		student->center_code = _student.center_code;
		printk("Confirmed Center Code: %lu\n", student->center_code);
		save_2_eeprom(*student);
		STATES = STATE_ASK_PAPER_CODE;
	}
}

void invalid_center_number(void)
{
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Invalid center #");
	lcd_put_cur(1, 0);
	lcd_send_string("Try Again!");
	k_sleep(K_MSEC(2000));
	STATES = STATE_ENTER_CENTER_NO;
	return;
}

void enter_paper_code(void)
{
	bool paper_number_entered = false;
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("ENTER PAPER CODE:");
	lcd_put_cur(1, 0);
	char input[4] = {0};
	volatile int digit_count = 0;
	while (paper_number_entered == false)
	{
		key = read_keypad();
		lcd_send_cmd(0x0E);
		if ((key == 'A') || (key == 'B') || (key == 'C') || (key == 'D'))
		{
			for (uint8_t i = 0; i < 1; i++)
			{
				lcd_put_cur(1, 0);
				input[i] = key;
				lcd_send_string(input);
				digit_count++;
			}
		}
		else if (key == '#' && digit_count > 0)
		{
			digit_count = 0;
			k_msleep(500);
			paper_number_entered = true;
		}
	}
	if (paper_number_entered == true)
	{
		_student.paper_type = input[0];
		printk("\nStudent paper: %c\n", _student.paper_type);
		STATES = STATE_CONFIRM_PAPER_CODE;
		return;
	}
}

void confirm_paper_code(struct student_credentials *student)
{
	bool IS_PAPER_CODE_CONFIRMED = false;
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Confirm Code:");
	lcd_put_cur(1, 0);
	lcd_send_data(_student.paper_type);
	while (IS_PAPER_CODE_CONFIRMED == false)
	{
		key = read_keypad();
		switch (key)
		{
		case 'E':
			STATES = STATE_ASK_PAPER_CODE;
			return;
			break;
		case '#':
			IS_PAPER_CODE_CONFIRMED = true;
			break;
		default:
			break;
		}
	}
	if (IS_PAPER_CODE_CONFIRMED == true)
	{
		student->paper_type = _student.paper_type;
		printk("Student Paper Code: %c\n", student->paper_type);
		save_2_eeprom(*student);
		STATES = STATE_LCD_QUE_SETUP;
	}
}

void setup_for_que(struct student_credentials student)
{
	k_sleep(K_MSEC(10));
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("QUE");
	lcd_put_cur(0, 6);
	lcd_send_string("ANS");
	lcd_put_cur(0, 12);
	lcd_send_string("CODE");
	lcd_put_cur(1, 13);
	lcd_send_data(student.paper_type);
	// STATES = STATE_SETUP_NEXT_QUE;
}

fw_states que_ans(void)
{
	bool QUE_NO_RECEIVED = false;
	bool ANS_ENTERED = false;
	bool ANS_RECEIVED = false;
	unsigned int input_received_count = 0;
	unsigned long int question_num = 0;
	unsigned char answer;
	unsigned char inputs[4] = {0};

	lcd_put_cur(1, 0);
	while (QUE_NO_RECEIVED == false)
	{
		key = read_keypad();
		if (key >= '0' && key <= '9' && input_received_count < 2)
		{
			lcd_send_data(key);
			inputs[input_received_count] = key;
			input_received_count++;
		}
		else if (key == '#' && input_received_count > 0)
		{
			inputs[input_received_count++] = '\0';
			// printk("input received: %s\r\n", inputs);
			sscanf(inputs, "%d", &question_num);
			// printk("input received in int: %d\r\n", question_num);
			QnA[question_num - 1][0] = question_num;
			// printk("Array val: %d\r\n", QnA[question_num - 1][0]);
			input_received_count = 0;
			// char char_question_num = (char)QnA[question_num - 1][0];
			QUE_NO_RECEIVED = true;
		}
		else if (key == 'V')
		{
			STATES = STATE_VERIFY;
			ANS_RECEIVED = true;
			return STATES;
		}
		else if (key == '*')
		{
			STATES = STATE_CONFIRM_SUBMIT;
			ANS_RECEIVED = true;
			return STATES;
		}
	}
	lcd_put_cur(1, 7);
	while (QUE_NO_RECEIVED == true && ANS_RECEIVED == false)
	{
		key = read_keypad();
		if (ANS_ENTERED == false)
		{
			if ((key == 'A') || (key == 'B') || (key == 'C') || (key == 'D'))
			{
				lcd_send_data(key);
				inputs[input_received_count] = key;
				ANS_ENTERED = true;
			}
		}
		else if (key == '#' && (ANS_ENTERED == true))
		{
			answer = inputs[input_received_count];
			QnA[question_num - 1][1] = answer;
			// printk("Answer received: %c\r\n", answer);
			// for (size_t i = 0; i < (sizeof(QnA)) / 2; i++)
			// {
			// 	printk("Q: %d\t, A: %c\r\n", QnA[i][0], QnA[i][1]);
			// }
			// printk("%d", sizeof(QnA));
			save_2_eeprom(student);
			STATES = STATE_LCD_QUE_SETUP;
			ANS_RECEIVED = true;
			return STATES;
		}

		else if (key == 'V')
		{
			ANS_RECEIVED = false;
			STATES = STATE_VERIFY;
			ANS_RECEIVED = true;
			return STATES;
		}
		else if (key == '*')
		{
			STATES = STATE_CONFIRM_SUBMIT;
			ANS_RECEIVED = true;
			return STATES;
		}
	}
}

fw_states verify_paper(void)
{
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("QUE");
	lcd_put_cur(0, 6);
	lcd_send_string("ANS");
	lcd_put_cur(0, 12);
	lcd_send_string("CODE");
	bool VERIFIED = false;
	static int qna_index = 0;

	// if (qna_index < 0)
	// 	qna_index = 0;
	// else if (qna_index >= (sizeof(QnA) / 2))
	// 	qna_index = 0;

	char str[3];

	sprintf(str, "%d", QnA[qna_index][0]);
	lcd_put_cur(1, 0);
	lcd_send_string(str);

	lcd_put_cur(1, 7);
	lcd_send_data(QnA[qna_index][1]);

	lcd_put_cur(1, 13);
	lcd_send_data(_student.paper_type);

	lcd_put_cur(1, 7);

	while (VERIFIED == false)
	{
		key = read_keypad();
		switch (key)
		{
		case 'A':
			QnA[qna_index][1] = key;
			lcd_put_cur(1, 7);
			lcd_send_data(QnA[qna_index][1]);
			
			break;
		case 'B':
			QnA[qna_index][1] = key;
			lcd_put_cur(1, 7);
			lcd_send_data(QnA[qna_index][1]);
			
			break;
		case 'C':
			QnA[qna_index][1] = key;
			lcd_put_cur(1, 7);
			lcd_send_data(QnA[qna_index][1]);
			
			break;
		case 'D':
			QnA[qna_index][1] = key;
			lcd_put_cur(1, 7);
			lcd_send_data(QnA[qna_index][1]);
			
			break;
		case 'P':
			if (qna_index <= 0)
			{
				qna_index = (sizeof(QnA) / 2)-1;
			}
			else
			{
				qna_index--;
				sprintf(str, "%d", QnA[qna_index][0]);
				// sprintf(str, "%c", QnA[qna_index][1]);
				lcd_put_cur(1, 0);
				lcd_send_string(str);
				// lcd_put_cur(1,7);
				// lcd_send_string(QnA[qna_index][1]);
			}
			break;
		case 'N':
			if (qna_index >= (sizeof(QnA) / 2)-1)
			{
				qna_index = 0;
			}
			else
			{
				qna_index++;
				sprintf(str, "%d", QnA[qna_index][0]);
				// sprintf(str, "%c", QnA[qna_index][1]); 
				lcd_put_cur(1, 0);
				lcd_send_string(str);
				// lcd_put_cur(1,7);
				// lcd_send_string(QnA[qna_index][1]);
			}
			break;
		case 'V':
			STATES = STATE_SETUP_NEXT_QUE;
			VERIFIED = true;
			return STATES;
			break;
		default:
			break;
		}
		// if ((key == 'A') || (key == 'B') || (key == 'C') || (key == 'D'))
		// {
		// 	QnA[qna_index][1] = key;
		// 	lcd_put_cur(1, 7);
		// 	lcd_send_data(QnA[qna_index][1]);

		// 	// for (size_t i = 0; i < (sizeof(QnA)) / 2; i++)
		// 	// {
		// 	// 	printk("Q: %d\t, A: %c\r\n", QnA[i][0], QnA[i][1]);
		// 	// }
		// }
	}
}

fw_states confirm_submission(void)
{
	bool SUBMIT_PAPER = false;
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("Confirm Submit?");
	lcd_put_cur(1, 0);
	lcd_send_string("*-Submit P-Back");
	while (SUBMIT_PAPER == false)
	{
		key = read_keypad();
		switch (key)
		{
		case '*':
			STATES = STATE_SUBMIT;
			SUBMIT_PAPER = true;
			return STATES;
			break;
		case 'P':
			STATES = STATE_LCD_QUE_SETUP;
			return STATES;
			break;
		default:
			break;
		}
	}
}

fw_states submit_paper()
{
	save_2_eeprom(student);
	lcd_clear();
	lcd_put_cur(0, 2);
	lcd_send_string("Submitted");
	lcd_put_cur(1, 2);
	lcd_send_string("Successfully");
	k_sleep(K_MSEC(3000));
	lcd_clear();
	lcd_put_cur(0, 2);
	lcd_send_string(" ***THANK YOU****");
	STATES = STATE_IDLE;
	return STATES;
};

void save_2_eeprom(struct student_credentials student)
{
	memcpy(student.answers, QnA, sizeof(QnA));
	printk("Student Roll No.: %llu\n", student.roll_number);
	// printk("Student Paper Type: %c\n", student.paper_type);
	// for (size_t i = 0; i < (sizeof(student.answers)/2); i++)
	// {
	// 	printk("Question: %d\tAnswer: %c\n", student.answers[i][0], student.answers[i][1]);
	// 	k_sleep(K_USEC(10));
	// }
	i2c_eeprom_write(0x0000, &student, sizeof(student));
	k_sleep(K_MSEC(10));
	i2c_eeprom_read(0x0000, &eeprom_data, sizeof(eeprom_data));
	k_sleep(K_MSEC(10));
	printk("\nStudent Roll No.: %llu\n", eeprom_data.roll_number);
	printk("Student Subject Code: %lu\n", eeprom_data.subject_code);
	printk("Student Center Code: %lu\n", eeprom_data.center_code);
	printk("Student Paper Type: %c\n", eeprom_data.paper_type);
	for (size_t i = 0; i < (sizeof(eeprom_data.answers) / 2); i++)
	{
		printk("Question: %d\tAnswer: %c\n", eeprom_data.answers[i][0], eeprom_data.answers[i][1]);
		k_sleep(K_USEC(10));
	}
}