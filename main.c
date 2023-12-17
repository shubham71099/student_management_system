#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SUBJECTS 6
#define string_size 100

void print_banner();
void home();
void admin_home();
void show_home_actions(int action);
void show_admin_actions(int action);
void adminlogin();
void adminregister();
void updateadmindata();
void teacherlogin();
void teacher_home(char *id);
void show_teacher_actions(int action,char *id);
void show_teacher_profile(char *id);
void update_teacher_password(char *id);
void add_student_marks(char *id);
void studentlogin();
void student_home(char *id);
void getPassword(char *password, int max_len);
int add_course();
void edit_course();
void view_course();
void add_teacher();
void edit_teacher();
void view_teacher();
void delete_teacher();
void add_student();
void edit_student();
void search_student();
void view_student();
void delete_student();
void fees_payment();
void fees_pending_list();
bool take_int_input(int *number);
bool isValidMobileNumber(const char *number);
bool isValidEmail(const char *email);
bool unique_email(int no,const char *email);
int isValidName(const char *name);
int isLeapYear(int year);
int isValidDate(int day, int month, int year);

struct course
{
	char course_name[string_size];
	int course_id, fees;
	char subject[MAX_SUBJECTS][string_size];
};

struct teacher
{
	int teacher_id, teacher_salary;
	char teacher_name[string_size], teacher_email[string_size], teacher_doj[string_size], teacher_mobile[string_size], teacher_course[string_size], teacher_password[string_size];
};

struct student
{
	char student_name[string_size], student_email[string_size], student_mobile[string_size], fees[30], dob[30];
	char student_password[string_size], student_course[string_size], student_address[string_size];
	char subject[MAX_SUBJECTS][string_size];
	int enrollment_no;
	int marks[MAX_SUBJECTS];
};

struct login
{
	char username[20];
	char password[20];
};
void main()
{
	//	admin_home();
	//	adminlogin();
	home();
}

bool take_int_input(int *number)
{
	if (scanf("%d", number) == 1)
	{
		return true;
	}
	else
	{
		printf("\n\t\t\t\t\x1b[38;5;45m Please Enter Number Only... \x1b[0m\n");
		while (getchar() != '\n');
		return false;
	}
}

bool isValidMobileNumber(const char *number)
{
	int length = 0, i;

	// Check if the input is NULL
	if (number == NULL)
	{
		return false;
	}

	// Calculate the length of the string
	while (number[length] != '\0')
	{
		length++;
	}

	// Check if the length is not more than 10 digits
	if (length != 10)
	{
		return false;
	}

	// Check that all characters are digits
	for (i = 0; i < length; i++)
	{
		if (!isdigit(number[i]))
		{
			return false;
		}
	}

	return true;
}

bool isValidEmail(const char *email)
{
	// Check if the input is NULL
	if (email == NULL)
	{
		return false;
	}

	// Check for the presence of '@' character
	const char *at = strchr(email, '@');
	if (at == NULL)
	{
		return false;
	}

	// Check for at least one character before '@'
	if (at == email)
	{
		return false;
	}

	// Check for at least one character after '@'
	if (*(at + 1) == '\0')
	{
		return false;
	}

	// Check for a dot (.) character after '@'
	const char *dot = strchr(at, '.');
	if (dot == NULL)
	{
		return false;
	}

	// Check for at least one character after the last dot
	if (*(dot + 1) == '\0')
	{
		return false;
	}

	// Ensure that there are no consecutive dots
	const char *c;
	for (c = email; *c; ++c)
	{
		if (*c == '.' && *(c + 1) == '.')
		{
			return false;
		}
	}

	return true;
}

bool unique_email(int no,const char *email)
{
	if(no==1)
	{
		struct teacher teacher_info;
	    FILE *fp = fopen("teacherinfo.bin", "rb");
	    if (fp == NULL)
	    {
	        perror("Error opening file");
	        return false;
	    } 
	    while (fread(&teacher_info, sizeof(struct teacher), 1, fp) == 1)
		{
	        if ((strcmp(teacher_info.teacher_email, email) == 0))
	        {
	        	fclose(fp);
	        	return true;
			}
	    }
	    fclose(fp);
	    return false;
	}
	if(no==2)
	{
		struct student student_info;
		FILE *fp = fopen("studentinfo.bin", "rb");
		if (fp == NULL)
	    {
	        perror("Error opening file");
	        return false;
	    }
		while (fread(&student_info, sizeof(struct student), 1, fp) == 1)
		{
	        if ((strcmp(student_info.student_email, email) == 0))
	        {
	        	fclose(fp);
	        	return true;
			}
	    }
	    fclose(fp);
	    return false; 
	}
	
}

int isValidName(const char *name)
{
	if (name == NULL)
	{
		return 0; // NULL pointer, not a valid name
	}

	if (name[0] == '\0' || name[0] == '\n')
	{
		return 0; // Empty string, not a valid name
	}

	return 1;
}

int isLeapYear(int year)
{
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return 1;
	return 0;
}

int isValidDate(int day, int month, int year)
{
	if (year < 1900 || year > 2099)
		return 0;
	if (month < 1 || month > 12)
		return 0;

	int maxDaysInMonth[] = {0, 31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (day < 1 || day > maxDaysInMonth[month])
		return 0;

	return 1;
}

void print_banner()
{
	system("cls");
	printf("\t\t\t\x1b[38;5;45m =========================================================================== \x1b[0m\n");
	printf("\t\t\t\x1b[38;5;45m ===============         STUDENT MANAGEMENT SYSTEM         ================= \x1b[0m\n");
	printf("\t\t\t\x1b[38;5;45m =========================================================================== \x1b[0m\n");
	fflush(stdin);
}

void home()
{
	int choice;
	while (choice != 4)
	{
		print_banner();
		printf("\n");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m |      MENU      | \x1b[0m");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
		printf("\n\n");

		printf("\n\n\t\t\t       (1)  Admin Login ");
		printf("\n\n\t\t\t       (2)  Teacher Login  ");
		printf("\n\n\t\t\t       (3)  Student Login  ");
		printf("\n\n\t\t\t       (4)  Exit       ");
		fflush(stdin);

		while (1)
		{
			printf("\n\n\t\t\t\x1b[38;5;45m Please select your role from above : \x1b[0m");

			if (take_int_input(&choice))
			{
				if (choice >= 1 && choice <= 4)
				{
					show_home_actions(choice);
					break;
				}
				else
				{
					printf("\n\t\t\t\t Please Enter a Valid Choice... ");
				}
			}
		}
	}
	
}

void show_home_actions(int action)
{
	switch (action)
	{
	case 1:
		adminlogin();
		system("cls");
		break;

	case 2:
		teacherlogin();
		system("cls");
		break;

	case 3:
		studentlogin();
		system("cls");
		break;

	case 4:
		break;
	default:
		break;
	}
}

void admin_home()
{
	int choice;
	while (choice != 16)
	{
		print_banner();
		printf("\n");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m |      MENU      | \x1b[0m");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
		printf("\n\n");

		printf("\n\t\t\t       (1)  Add New Course ");
		printf("\n\t\t\t       (2)  Edit Course Details  ");
		printf("\n\t\t\t       (3)  List of Courses  ");
		printf("\n\t\t\t       (4)  Add New Teacher    ");
		printf("\n\t\t\t       (5)  Edit Teacher Details   ");
		printf("\n\t\t\t       (6)  List of Teachers  ");
		printf("\n\t\t\t       (7)  Delete Teacher Details  ");
		printf("\n\t\t\t       (8)  Add New Student  ");
		printf("\n\t\t\t       (9)  Edit Student Details  ");
		printf("\n\t\t\t       (10) Search Student Details  ");
		printf("\n\t\t\t       (11) List of Students ");
		printf("\n\t\t\t       (12) Delete Student Details  ");
		printf("\n\t\t\t       (13) Fees Payment  ");
		printf("\n\t\t\t       (14) Fees Pending List  ");
		printf("\n\t\t\t       (15) Update Userid & Password ");
		printf("\n\t\t\t       (16) Exit       ");
		fflush(stdin);

		while (1)
		{
			printf("\n\n\t\t\t\x1b[38;5;45m Enter your choice : \x1b[0m");

			if (take_int_input(&choice))
			{
				if (choice >= 1 && choice <= 16)
				{
					show_admin_actions(choice);
					break;
				}
				else
				{
					printf("\n\t\t\t\t Please Enter a Valid Choice... ");
				}
			}
		}
	}
}

void show_admin_actions(int action)
{
	time_t current_time;
	struct tm *time_info;
	char time_string[50];

	time(&current_time);

	time_info = localtime(&current_time);

	strftime(time_string, sizeof(time_string), "%d-%m-%Y %H:%M", time_info);
	fflush(stdin);
	switch (action)
	{
	case 1:
		add_course();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 2:
		edit_course();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 3:
		view_course();
		printf("\n\t\t\t\t\x1b[38;5;45m List of Courses As on : %s  \x1b[0m", time_string);
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 4:
		add_teacher();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 5:
		edit_teacher();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 6:
		view_teacher();
		printf("\n\t\t\t\t\x1b[38;5;45m List of Teachers As on : %s  \x1b[0m", time_string);
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 7:
		delete_teacher();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 8:
		add_student();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 9:
		edit_student();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 10:
		search_student();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 11:
		view_student();
		printf("\n\t\t\t\t\x1b[38;5;45m List of Students As on : %s  \x1b[0m", time_string);
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 12:
		delete_student();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 13:
		fees_payment();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;

	case 14:
		fees_pending_list();
		printf("\n\n\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
		getch();
		system("cls");
		break;
		
	case 15:
		updateadmindata();
		getch();
		system("cls");
		break;
	case 16:
		break;
	default:
		break;
	}
}

int add_course()
{
	print_banner();
	FILE *fp = NULL;
	struct course course_info;
	int courseCount = 0, last_course_id = 0;
	char line[100], course_name[50];
	int i;

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |      Add New Course     | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------+ \x1b[0m");

	fp = fopen("courseinfo.bin", "rb");

	if (fp == NULL)
	{
		last_course_id = 0;
	}
	else
	{

		while (fread(&course_info, sizeof(struct course), 1, fp) == 1)
		{

			last_course_id = course_info.course_id;
		}

		fclose(fp);
	}

	fp = fopen("courseinfo.bin", "ab");

	fflush(stdin);

	if (fp == NULL)
	{
		fprintf(stderr, "\t\t\t\n Can't Open");
		return 1;
	}

	course_info.course_id = last_course_id + 1;

	while (1)
	{
		printf("\n\n\n\t\t\tEnter Course Name  : ");
		fgets(course_name, 30, stdin);
		if (isValidName(course_name))
		{
			strcpy(course_info.course_name, course_name);
			break;
		}
		else
		{
			printf("\n\t\t\t\t\x1b[38;5;45m Please Enter a Valid Name \x1b[0m\n");
			fflush(stdin);
		}
	}

	while (1)
	{
		printf("\n\t\t\tEnter Fees(in Rs.) : ");
		if (take_int_input(&course_info.fees))
		{
			break;
		}
	}
	printf("\n\t\t\tEnter Name of 6 Subjects \n");

	for (i = 0; i < 6; i++)
	{
		printf("\n\t\t\tSubject %d : ", i + 1);
		fflush(stdin); // Flush any remaining characters in the input buffer
		fgets(course_info.subject[i], sizeof(course_info.subject[i]), stdin);
		course_info.subject[i][strcspn(course_info.subject[i], "\n")] = '\0'; // Remove the trailing newline
	}

	fwrite(&course_info, sizeof(struct course), 1, fp);

	fclose(fp);
	printf("\n\n\t\t\t--------------------------------------------------------");
	printf("\n\n\t\t\t\t  Course ID        :   \x1b[38;5;45m   %d \x1b[0m", course_info.course_id);
	printf("\n\n\t\t\t\t  Course Name      :   \x1b[38;5;45m   %s \x1b[0m", course_info.course_name);
	printf("\n\n\t\t\t\t  Course Fees      :   \x1b[38;5;45m   %d \x1b[0m", course_info.fees);
	printf("\n\n\t\t\t\t  Subjects              ");
	printf("\n\t\t\t\t_____________");
	printf("\n");
	for (i = 0; i < 6; i++)
	{
		printf("\n\t\t\t\t  Subject %d        :       %s", i + 1, course_info.subject[i]);
	}

	printf("\n\n\t\t\t--------------------------------------------------------");
	printf("\n\n\t\t\t\x1b[38;5;45m Course added successfully !!  \x1b[0m");
	return 0;
}

void edit_course()
{
	print_banner();
	FILE *fp, *fp1;
	struct course course_info;
	int course_id, i;
	int found = 0;
	fp = fopen("courseinfo.bin", "rb");

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |   Edit Course Details   | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------+ \x1b[0m");

	if (fp == NULL)
	{
		fprintf(stderr, "\t\t\t\n Course List is Empty \n");
	}

	fp1 = fopen("temp.bin", "wb");

	printf("\n\n\n\t\t\tEnter Course Id to Update : ");
	scanf("%d", &course_id);

	while (fread(&course_info, sizeof(struct course), 1, fp))
	{
		if (course_info.course_id == course_id)
		{
			printf("\n\n\t\t\t--------------------------------------------------------------------");
			printf("\n\n\t\t\t\t  Course ID        :  \x1b[38;5;45m %d \x1b[0m", course_info.course_id);
			printf("\n\n\t\t\t\t  Course Name      :  \x1b[38;5;45m %s \x1b[0m", course_info.course_name);
			printf("\n\n\t\t\t\t  Course Fees      :  \x1b[38;5;45m %d \x1b[0m", course_info.fees);
			printf("\n\n\t\t\t\t  Subjects              ");
			printf("\n\t\t\t\t_____________");
			printf("\n");
			for (i = 0; i < 6; i++)
			{
				printf("\n\t\t\t\t  Subject %d        :   %s\n", i + 1, course_info.subject[i]);
			}

			printf("\n\t\t\t--------------------------------------------------------------------");

			printf("\n\t\t\tEnter course new name: ");
			fflush(stdin); // Flush any remaining characters in the input buffer
			fgets(course_info.course_name, sizeof(course_info.subject[i]), stdin);

			while (1)
			{
				printf("\n\t\t\tEnter New Fees(in Rs.) : ");
				if (take_int_input(&course_info.fees))
				{
					break;
				}
			}
			course_info.course_name[strcspn(course_info.course_name, "\n")] = '\0';

			found = 1;
		}
		fwrite(&course_info, sizeof(struct course), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);

	if (found)
	{
		remove("courseinfo.bin");
		rename("temp.bin", "courseinfo.bin");
		printf("\n\t\t\t\x1b[38;5;45m Course Updated Successfully !!  \x1b[0m");
	}
	if (!found)
	{

		printf("\n\n\n");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-----------------------------------------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                           | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |    Sorry ! No Course details found for above Course ID    | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                           | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-----------------------------------------------------------+ \x1b[0m");
		printf("\n\n");
	}
}
void view_course()
{
	print_banner();
	FILE *fp = NULL;
	struct course course_info;
	fp = fopen("courseinfo.bin", "rb");
	int i;

	if (fp == NULL)
	{
		printf("\n\n\n\n");
		printf("\n\t\t\t\t\t      +--------------------------------+");
		printf("\n\t\t\t\t\t      |      Course List is Empty      |");
		printf("\n\t\t\t\t\t      +--------------------------------+");
		printf("\n\n");
	}
	else
	{
		printf("\n");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      +-----------------------+ \x1b[0m");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      |      Course List      | \x1b[0m");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      +-----------------------+ \x1b[0m");
		printf("\n\n");
	}

	while (fread(&course_info, sizeof(struct course), 1, fp))
	{

		printf("\n\t\t\t\t   Course ID         :    %d", course_info.course_id);
		printf("\n\t\t\t\t   Course Name       :   \x1b[38;5;45m %s \x1b[0m", course_info.course_name);
		printf("\n\t\t\t\t   Course Fees       :    %d", course_info.fees);
		printf("\n");
		for (i = 0; i < 6; i++)
		{
			printf("\n\t\t\t\t   Subject %d         :    %s", i + 1, course_info.subject[i]);
		}
		printf("\n\t\t\t\t____________________________________________________________ \n");
	}
	fclose(fp);
}

void add_teacher()
{
	print_banner();

	time_t current_time;
	struct tm *time_info;
	char time_string[50];

	time(&current_time);

	time_info = localtime(&current_time);

	strftime(time_string, sizeof(time_string), "%d-%m-%Y", time_info);

	int i, selected_course, last_teacher_id = 100;
	char teacher_mobile[15];
	char teacher_email[100], teacher_name[30];
	struct course courses[30];
	FILE *fp = NULL;
	struct teacher teacher_info;

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |      Add New Teacher     | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");

	fp = fopen("teacherinfo.bin", "rb");

	if (fp == NULL)
	{
		last_teacher_id = 100;
	}
	else
	{

		while (fread(&teacher_info, sizeof(struct teacher), 1, fp) == 1)
		{

			last_teacher_id = teacher_info.teacher_id;
		}

		fclose(fp);
	}

	fp = fopen("courseinfo.bin", "rb");

	if (fp == NULL)
	{
		perror("Error opening file");
		return;
	}

	int numCourses = 0;
	while (fread(&courses[numCourses], sizeof(struct course), 1, fp) == 1)
	{
		(numCourses)++;
	}

	fclose(fp);

	fp = fopen("teacherinfo.bin", "ab");
	fflush(stdin);
	teacher_info.teacher_id = last_teacher_id + 1;
	strcpy(teacher_info.teacher_password, "teacher");
	sscanf(time_string, "%10s", teacher_info.teacher_doj);

	if (fp == NULL)
	{
		fprintf(stderr, "\t\t\t\n Can't Open");
	}

	for (i = 0; i < numCourses; i++)
	{
		printf("\n\t\t\t     (%d) %s ", i + 1, courses[i].course_name);
	}

	while (1)
	{
		printf("\n\n\t\t\t Select Course From Above List : ");

		if (take_int_input(&selected_course))
		{
			if (selected_course >= 1 && selected_course <= numCourses)
			{
				strcpy(teacher_info.teacher_course, courses[selected_course - 1].course_name);
				break;
			}
			else
			{
				printf("\n\t\t\t\t\x1b[38;5;45m Invalid Choice!! Please select from the options provided. \x1b[0m");
			}
		}
	}
	printf("\n\n\t\t\t Selected Course  :  %s ", teacher_info.teacher_course);
	fflush(stdin);

	while (1)
	{
		printf("\n\n\t\t\t Teacher's Name   :  ");
		fgets(teacher_name, 30, stdin);
		if (isValidName(teacher_name))
		{
			strcpy(teacher_info.teacher_name, teacher_name);
			break;
		}
		else
		{
			printf("\n\t\t\t\t\x1b[38;5;45m Please Enter a Valid Name \x1b[0m\n");
			fflush(stdin);
		}
	}

	while (1)
	{
		printf("\n\t\t\t Email            :  ");
		if (scanf("%99s", teacher_email) == 1)
		{ // Limit input to 99 characters
			// Validation of the email address using isValidEmail function
			if(isValidEmail(teacher_email))
            {
                if (unique_email(1,teacher_email))
                {
                    printf("\n\t\t\t\x1b[38;5;45m Email is already in use. Please enter another email. \x1b[0m\n");
                }
                else
                {
                    strcpy(teacher_info.teacher_email, teacher_email);
                    break;
                }
            }
			else
			{
				printf("\n\t\t\t\t\x1b[38;5;45m Please Enter a Valid Email Address \x1b[0m\n");
			}
		}
		else
		{
			printf("Error reading email address\n");
		}

		// Clear the input buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
	}

	while (1)
	{

		printf("\n\t\t\t Mobile           :  ");
		if (scanf("%14s", teacher_mobile) == 1)
		{
			// Validation of the mobile number using your isValidMobileNumber function
			if (isValidMobileNumber(teacher_mobile))
			{
				strcpy(teacher_info.teacher_mobile, teacher_mobile);
				break;
			}
			else
			{
				printf("\n\t\t\t\t\x1b[38;5;45m Please Enter 10 Digit Number Only \x1b[0m\n");
			}
		}

		fflush(stdin);
	}

	while (1)
	{
		printf("\n\t\t\t Salary           :  ");
		if (take_int_input(&teacher_info.teacher_salary))
		{
			break;
		}
	}

	fwrite(&teacher_info, sizeof(struct teacher), 1, fp);
	printf("\n\n\t\t\t--------------------------------------------------------");
	printf("\n\n\t\t\t\x1b[38;5;45m Teacher added successfully !!  \x1b[0m");
	printf("\n\n\t\t\t Teacher Login ID  : \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_email);
	printf("\n\t\t\t Default Password  : \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_password);
	printf("\n\n\t\t\t--------------------------------------------------------");

	fclose(fp);
}

void edit_teacher()
{
	print_banner();
	FILE *fp, *fp1;
	struct teacher teacher_info;
	int teacher_id;
	char teacher_mobile[15];
	char teacher_email[100];
	int found = 0;
	fp = fopen("teacherinfo.bin", "rb");

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |   Edit Teacher Details   | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");

	if (fp == NULL)
	{
		fprintf(stderr, "\n\n\n\n\t\t\t Teacher's List is Empty \n");
	}

	fp1 = fopen("temp.bin", "wb");
	fflush(stdin);
	printf("\n\n\n\t\t\tEnter Teacher's Id to Update : ");
	scanf("%d", &teacher_id);

	while (fread(&teacher_info, sizeof(struct teacher), 1, fp))
	{
		if (teacher_info.teacher_id == teacher_id)
		{
			printf("\n\n\t\t\t--------------------------------------------------------------------");
			printf("\n\t\t\t\t   Teacher ID       :    %d", teacher_info.teacher_id);
			printf("\n\t\t\t\t   Name             :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_name);
			printf("\n\t\t\t\t   Department       :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_course);
			printf("\n\t\t\t\t   Date of Joining  :    %s", teacher_info.teacher_doj);
			printf("\n\t\t\t\t   Mobile No.       :    %s", teacher_info.teacher_mobile);
			printf("\n\t\t\t\t   Email-id         :    %s ", teacher_info.teacher_email);
			printf("\n\t\t\t\t   Salary           :    %d", teacher_info.teacher_salary);
			printf("\n");
			printf("\n\t\t\t--------------------------------------------------------------------");

			printf("\n\t\t\tEnter Teacher's New Name : ");
			fflush(stdin);
			fgets(teacher_info.teacher_name, sizeof(teacher_info.teacher_name), stdin);

			while (1)
			{
				printf("\n\t\t\tEnter New Salary(in Rs.) : ");
				if (take_int_input(&teacher_info.teacher_salary))
				{
					break;
				}
			}
			teacher_info.teacher_name[strcspn(teacher_info.teacher_name, "\n")] = '\0';

			while (1)
			{

				printf("\n\t\t\tEnter New Mobile No.     : ");
				if (scanf("%14s", teacher_mobile) == 1)
				{
					// Validation of the mobile number using your isValidMobileNumber function
					if (isValidMobileNumber(teacher_mobile))
					{
						strcpy(teacher_info.teacher_mobile, teacher_mobile);
						break;
					}
					else
					{
						printf("\n\t\t\t\t\x1b[38;5;45m Please Enter 10 Digit Number Only \x1b[0m\n");
					}
				}

				fflush(stdin);
			}

			while (1)
			{
				printf("\n\t\t\tEnter New Email ID       : ");
				if (scanf("%99s", teacher_email) == 1)
				{ // Limit input to 99 characters
					// Validation of the email address using isValidEmail function
					if (isValidEmail(teacher_email))
					{
						strcpy(teacher_info.teacher_email, teacher_email);
						break;
					}
					else
					{
						printf("\n\t\t\t\t\x1b[38;5;45m Please Enter a Valid Email Address \x1b[0m\n");
					}
				}
				else
				{
					printf("Error reading email address\n");
				}

				// Clear the input buffer
				int c;
				while ((c = getchar()) != '\n' && c != EOF)
					;
			}

			found = 1;
		}
		fwrite(&teacher_info, sizeof(struct teacher), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);

	if (found)
	{
		remove("teacherinfo.bin");
		rename("temp.bin", "teacherinfo.bin");
		printf("\n\t\t\t\x1b[38;5;45m Teacher Details Updated Successfully !!  \x1b[0m");
	}
	if (!found)
	{

		printf("\n\n\n");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-------------------------------------------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                             | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |    Sorry ! No Teacher details found for above Teacher ID    | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                             | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-------------------------------------------------------------+ \x1b[0m");
		printf("\n\n");
	}
}

void view_teacher()
{
	print_banner();
	FILE *fp = NULL;
	struct teacher teacher_info;

	fp = fopen("teacherinfo.bin", "rb");
	int i;

	if (fp == NULL)
	{
		printf("\n\n\n\n");
		printf("\n\t\t\t\t\t      +-----------------------------------+");
		printf("\n\t\t\t\t\t      |      Teacher's List is Empty      |");
		printf("\n\t\t\t\t\t      +-----------------------------------+");
		printf("\n\n");
	}
	else
	{
		printf("\n");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      |      Teacher's List      | \x1b[0m");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");
		printf("\n\n");
	}
	fflush(stdin);
	while (fread(&teacher_info, sizeof(struct teacher), 1, fp))
	{

		printf("\n\t\t\t\t   Teacher ID        :    %d", teacher_info.teacher_id);
		printf("\n\t\t\t\t   Name              :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_name);
		printf("\n\t\t\t\t   Department        :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_course);
		printf("\n\t\t\t\t   Date of Joining   :    %s", teacher_info.teacher_doj);
		printf("\n\t\t\t\t   Mobile No.        :    %s", teacher_info.teacher_mobile);
		printf("\n\t\t\t\t   Email-id          :    %s ", teacher_info.teacher_email);
		printf("\n\t\t\t\t   Password          :    %s ", teacher_info.teacher_password);
		printf("\n\t\t\t\t   Salary            :    %d", teacher_info.teacher_salary);
		printf("\n");
		printf("\n\t\t\t\t____________________________________________________________ \n");
	}
	fclose(fp);
}
void delete_teacher()
{
	print_banner();
	FILE *fp, *fp1;
	struct teacher teacher_info;
	int teacher_id, found = 0;

	fp = fopen("teacherinfo.bin", "rb");
	fp1 = fopen("temp.bin", "wb");

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +----------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |   Delete Teacher Details   | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +----------------------------+ \x1b[0m");

	printf("\n\n\t\t\tEnter Teacher's ID to Delete : ");
	scanf("%d", &teacher_id);

	if (fp == NULL)
	{
		fprintf(stderr, "\t\t\t\n Can't Open\n");
	}
	while (fread(&teacher_info, sizeof(struct teacher), 1, fp))
	{
		if (teacher_info.teacher_id == teacher_id)
		{
			found = 1;
			printf("\n\t\t\t\t   Teacher ID       :    %d", teacher_info.teacher_id);
			printf("\n\t\t\t\t   Name             :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_name);
			printf("\n\t\t\t\t   Department       :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_course);
			printf("\n\t\t\t\t   Date of Joining  :    %s", teacher_info.teacher_doj);
			printf("\n\t\t\t\t   Mobile No.       :    %s", teacher_info.teacher_mobile);
			printf("\n\t\t\t\t   Email-id         :    %s ", teacher_info.teacher_email);
			printf("\n\t\t\t\t   Salary           :    %d", teacher_info.teacher_salary);
			printf("\n");
			printf("\n\t\t\t\t____________________________________________________________ \n");
		}
		else
		{
			fwrite(&teacher_info, sizeof(struct teacher), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	if (found)
	{
		char confirm;
		printf("\n\t\t\t   Do you want to delete this teacher ? (Y/N): ");
		scanf(" %c", &confirm);

		if (confirm == 'y' || confirm == 'Y')
		{
			remove("teacherinfo.bin");
			rename("temp.bin", "teacherinfo.bin");
			printf("\n\n\t\t\t   Teacher details deleted for Teacher Id  %d  . ", teacher_id);
		}
		else
		{
			printf("\n\t\t\t   Teacher details not deleted.");
		}
	}
	if (!found)
	{
		printf("\n\n\n");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-------------------------------------------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                             | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |    Sorry ! No Teacher details found for above Teacher ID    | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                             | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-------------------------------------------------------------+ \x1b[0m");
		printf("\n\n");
	}
}

void add_student()
{

	print_banner();
	int i, selected_course, last_enrollment_no = 230000000;
	int day, month, year;
	char student_mobile[15];
	char student_email[100], student_name[30];
	struct course courses[50];
	FILE *fp = NULL;
	struct student student_info;

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |      Add New Student     | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");

	fp = fopen("studentinfo.bin", "rb");

	if (fp == NULL)
	{
		last_enrollment_no = 230000000;
	}
	else
	{

		while (fread(&student_info, sizeof(struct student), 1, fp) == 1)
		{

			last_enrollment_no = student_info.enrollment_no;
		}

		fclose(fp);
	}
	fp = fopen("courseinfo.bin", "rb");

	int numCourses = 0;
	while (fread(&courses[numCourses], sizeof(struct course), 1, fp) == 1)
	{
		(numCourses)++;
	}

	fclose(fp);

	fp = fopen("studentinfo.bin", "ab");
	fflush(stdin);
	student_info.enrollment_no = last_enrollment_no + 1;
	strcpy(student_info.fees, "Unpaid");
	strcpy(student_info.student_password, "student");

	if (fp == NULL)
	{
		fprintf(stderr, "\t\t\t\n Can't Open");
	}

	for (i = 0; i < numCourses; i++)
	{
		printf("\n\t\t\t     (%d) %s ", i + 1, courses[i].course_name);
	}

	while (1)
	{
		printf("\n\n\t\t\t Select Course From Above List : ");

		if (take_int_input(&selected_course))
		{
			if (selected_course >= 1 && selected_course <= numCourses)
			{
				struct course selected_course_details = courses[selected_course - 1];
				strcpy(student_info.student_course, courses[selected_course - 1].course_name);
				for (i = 0; i < 6; i++)
				{
					strcpy(student_info.subject[i], selected_course_details.subject[i]);
					student_info.marks[i] = -1;
				}
				break;
			}
			else
			{
				printf("\n\t\t\t\t\x1b[38;5;45m Invalid Choice!! Please select from the options provided. \x1b[0m");
			}
		}
	}

	printf("\n\n\t\t\t Selected Course             :  %s ", student_info.student_course);
	fflush(stdin);

	while (1)
	{
		printf("\n\n\t\t\t Student Name                :  ");
		fgets(student_name, 30, stdin);
		if (isValidName(student_name))
		{
			strcpy(student_info.student_name, student_name);
			break;
		}
		else
		{
			printf("\n\t\t\t\t\x1b[38;5;45m Please Enter a Valid Name \x1b[0m\n");
			fflush(stdin);
		}
	}

	while (1)
	{
		printf("\n\t\t\t Email                       :  ");
		if (scanf("%99s", student_email) == 1)
		{ // Limit input to 99 characters

			if (isValidEmail(student_email))
			{
				if (unique_email(2,student_email))
                {
                    printf("\n\t\t\t\x1b[38;5;45m Email is already in use. Please enter another email. \x1b[0m\n");
                }
                else
                {
                    strcpy(student_info.student_email, student_email);
					break;
                }
			}
			else
			{
				printf("\n\t\t\t\t\x1b[38;5;45m Please Enter a Valid Email Address \x1b[0m\n");
			}
		}
		else
		{
			printf("Error reading email address\n");
		}

		// Clear the input buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF)
			;
	}

	while (1)
	{

		printf("\n\t\t\t Mobile                      :  ");
		fflush(stdin);
		if (scanf("%14s", student_mobile) == 1)
		{
			// Validation of the mobile number using your isValidMobileNumber function
			if (isValidMobileNumber(student_mobile))
			{
				strcpy(student_info.student_mobile, student_mobile);
				break;
			}
			else
			{
				printf("\n\t\t\t\t\x1b[38;5;45m Please Enter 10 Digit Number Only \x1b[0m\n");
			}
		}
		else
		{
			printf("\n\t\t\t\t\x1b[38;5;45m Error reading mobile number \x1b[0m\n");
			// Clear the input buffer
			int c;
			while ((c = getchar()) != '\n' && c != EOF)
				;
		}
	}
	fflush(stdin);

	printf("\n\t\t\t Address                     :  ");
	scanf("%50[^\n]", student_info.student_address);

	int status = 0;
	do
	{
		printf("\n\t\t\t Date of Birth(dd-mm-yyyy)   :  ");
		scanf("%d-%d-%d", &day, &month, &year);
		if (isValidDate(day, month, year))
		{
			char dob[11];
			snprintf(dob, sizeof(dob), "%02d-%02d-%d", day, month, year);
			strcpy(student_info.dob, dob);
			status = 1;
		}
		else
		{
			fflush(stdin);
			printf("\n\t\t\t\t\x1b[38;5;45m Invalid date of birth !! \x1b[0m\n");
		}
	} while (status == 0);

	fwrite(&student_info, sizeof(struct student), 1, fp);
	printf("\n\n\t\t\t--------------------------------------------------------");
	printf("\n\n\t\t\t\x1b[38;5;45m Student added successfully !!  \x1b[0m");
	printf("\n\n\t\t\t Student Login ID  : \x1b[38;5;45m %s \x1b[0m", student_info.student_email);
	printf("\n\t\t\t Default Password  : \x1b[38;5;45m %s \x1b[0m", student_info.student_password);
	printf("\n\n\t\t\t--------------------------------------------------------");

	fclose(fp);
}

void edit_student()
{
	print_banner();
	FILE *fp = NULL;
	FILE *fp1 = NULL;
	struct student student_info;
	int enrollment_no, found = 0;
	char student_mobile[15];
	char student_email[100];
	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |      Edit Student Detail      | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------------+ \x1b[0m");

	fp = fopen("studentinfo.bin", "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "\n\n\n\n\t\t\t Student List is Empty \n");
	}

	fp1 = fopen("temp.bin", "wb");
	fflush(stdin);
	printf("\n\n\n\t\t\tEnter Enrollment No. : ");
	scanf("%d", &enrollment_no);
	fflush(stdin);
	while (fread(&student_info, sizeof(struct student), 1, fp))
	{
		if (student_info.enrollment_no == enrollment_no)
		{
			found = 1;
			printf("\n\t\t\t\t   Enrollment No.     :    %d", student_info.enrollment_no);
			printf("\n\t\t\t\t   Name               :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
			printf("\n\t\t\t\t   Date of Birth      :    %s", student_info.dob);
			printf("\n\t\t\t\t   Department         :    %s", student_info.student_course);
			printf("\n\t\t\t\t   Mobile No.         :    %s", student_info.student_mobile);
			printf("\n\t\t\t\t   Email-id           :    %s ", student_info.student_email);
			printf("\n\t\t\t\t   Fees Status        :    %s", student_info.fees);
			printf("\n\t\t\t\t   Address            :    %s", student_info.student_address);
			printf("\n");
			printf("\n\t\t\t\t____________________________________________________________ \n");
			printf("\n\t\t\t--------------------------------------------------------------------");

			printf("\n\t\t\tEnter Student's Updated Name : ");
			fflush(stdin);
			fgets(student_info.student_name, sizeof(student_info.student_name), stdin);

			while (1)
			{

				printf("\n\t\t\tEnter New Mobile No.     : ");
				fflush(stdin);
				if (scanf("%14s", student_mobile) == 1)
				{
					// Validation of the mobile number using your isValidMobileNumber function
					if (isValidMobileNumber(student_mobile))
					{
						strcpy(student_info.student_mobile, student_mobile);
						break;
					}
					else
					{
						printf("\n\t\t\t\t\x1b[38;5;45m Please Enter 10 Digit Number Only \x1b[0m\n");
					}
				}

				fflush(stdin);
			}

			while (1)
			{
				printf("\n\t\t\tEnter New Email ID       : ");
				if (scanf("%99s", student_email) == 1)
				{ // Limit input to 99 characters
					// Validation of the email address using isValidEmail function
					if (isValidEmail(student_email))
					{
						strcpy(student_info.student_email, student_email);
						break;
					}
					else
					{
						printf("\n\t\t\t\t\x1b[38;5;45m Please Enter a Valid Email Address \x1b[0m\n");
					}
				}
				else
				{
					printf("Error reading email address\n");
				}

				// Clear the input buffer
				int c;
				while ((c = getchar()) != '\n' && c != EOF)
					;
			}

			printf("\n\t\t\tNew Address              : ");
			fflush(stdin);
			scanf("%50[^\n]", student_info.student_address);

			found = 1;
		}
		fwrite(&student_info, sizeof(struct student), 1, fp1);
	}

	fclose(fp);
	fclose(fp1);

	if (found)
	{
		remove("studentinfo.bin");
		rename("temp.bin", "studentinfo.bin");
		printf("\n\t\t\t\x1b[38;5;45m Student Details Updated Successfully !!  \x1b[0m");
	}
	if (!found)
	{
		printf("\n\n\n");
		printf("\n\t\t\t\t\x1b[38;5;45m +-------------------------------------------------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m |                                                                   | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m |     Sorry ! No Student details found for above Enrollment No      | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m |                                                                   | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m +-------------------------------------------------------------------+ \x1b[0m");
		printf("\n\n");
	}
}
void search_student()
{
	print_banner();
	struct student student_info;
	int choice, enrollment_no, found = 0;
	char student_name[100];
	FILE *fp = NULL;
	int status = 0;

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |      Search Student Details     | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------------+ \x1b[0m");

	fp = fopen("studentinfo.bin", "rb");

	printf("\n\t\t\t       (1)  Search By Enrollment No. ");
	printf("\n\t\t\t       (2)  Search By Student Name  ");
	while (1)
	{
		printf("\n\n\t\t\t\x1b[38;5;45m Select Option From Above : \x1b[0m");

		if (take_int_input(&choice))
		{
			if (choice == 1)
			{
				status = 1;
				printf("\n\n\t\t\tEnter Enrollment No : ");
				scanf("%d", &enrollment_no);

				while (fread(&student_info, sizeof(struct student), 1, fp))
				{
					if (student_info.enrollment_no == enrollment_no)
					{
						found = 1;
						printf("\n\t\t\t\t   Enrollment No.     :    %d", student_info.enrollment_no);
						printf("\n\t\t\t\t   Name               :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
						printf("\n\t\t\t\t   Date of Birth      :    %s", student_info.dob);
						printf("\n\t\t\t\t   Department         :    %s", student_info.student_course);
						printf("\n\t\t\t\t   Mobile No.         :    %s", student_info.student_mobile);
						printf("\n\t\t\t\t   Email-id           :    %s ", student_info.student_email);
						printf("\n\t\t\t\t   Password           :    %s ", student_info.student_password);
						printf("\n\t\t\t\t   Fees Status        :    %s", student_info.fees);
						printf("\n\t\t\t\t   Address            :    %s", student_info.student_address);
						printf("\n\n\t\t\t\t____________________________________________________________ \n");
						break;
					}
				}
				if (!found)
				{
					printf("\n\n\n");
					printf("\n\t\t\t\t\x1b[38;5;45m +-------------------------------------------------------------------+ \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m |                                                                   | \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m |     Sorry ! No Student details found for above Enrollment No      | \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m |                                                                   | \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m +-------------------------------------------------------------------+ \x1b[0m");
					printf("\n\n");
				}
			}
			else if (choice == 2)
			{
				status = 1;
				printf("\n\n\t\t\tEnter Student Name : ");
				scanf(" %[^\n]", student_name);

				// Remove trailing newline character from student_name
				strtok(student_name, "\n");

				while (fread(&student_info, sizeof(struct student), 1, fp))
				{
					strtok(student_info.student_name, "\n");
					if (strcmp(student_info.student_name, student_name) == 0)
					{
						found = 1;
						printf("\n\t\t\t\t   Enrollment No.     :    %d", student_info.enrollment_no);
						printf("\n\t\t\t\t   Name               :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
						printf("\n\t\t\t\t   Date of Birth      :    %s", student_info.dob);
						printf("\n\t\t\t\t   Department         :    %s", student_info.student_course);
						printf("\n\t\t\t\t   Mobile No.         :    %s", student_info.student_mobile);
						printf("\n\t\t\t\t   Email-id           :    %s ", student_info.student_email);
						printf("\n\t\t\t\t   Password           :    %s ", student_info.student_password);
						printf("\n\t\t\t\t   Fees Status        :    %s", student_info.fees);
						printf("\n\t\t\t\t   Address            :    %s", student_info.student_address);

						printf("\n");
						printf("\n\t\t\t\t____________________________________________________________ \n");
						break;
					}
				}
				if (!found)
				{
					printf("\n\n\n");
					printf("\n\t\t\t\t\x1b[38;5;45m +-------------------------------------------------------------------+ \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m |                                                                   | \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m |          Sorry ! No Student details found with above Name         | \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m |                                                                   | \x1b[0m");
					printf("\n\t\t\t\t\x1b[38;5;45m +-------------------------------------------------------------------+ \x1b[0m");
					printf("\n\n");
				}
			}
			else
			{
				printf("\n\t\t\t\t Please Enter a Valid Choice... ");
			}

			if (status == 1)
			{
				break;
			}
		}
	}

	fclose(fp);
}
void view_student()
{
	print_banner();
	struct course courses[50];
	int selected_course, i, count = 0;
	FILE *fp = NULL;
	struct student student_info;

	fp = fopen("courseinfo.bin", "rb");

	int numCourses = 0;
	while (fread(&courses[numCourses], sizeof(struct course), 1, fp) == 1)
	{
		(numCourses)++;
	}

	fclose(fp);

	fp = fopen("studentinfo.bin", "rb");

	if (fp == NULL)
	{
		printf("\n\n\n\n");
		printf("\n\t\t\t\t\t      +-----------------------------------+");
		printf("\n\t\t\t\t\t      |       Student List is Empty       |");
		printf("\n\t\t\t\t\t      +-----------------------------------+");
		printf("\n\n");
	}
	else
	{
		printf("\n");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      |       Student List       | \x1b[0m");
		printf("\n\t\t\t\t\t\x1b[38;5;45m      +--------------------------+ \x1b[0m");
		printf("\n\n");
	}
	fflush(stdin);

	for (i = 0; i < numCourses; i++)
	{
		printf("\n\t\t\t     (%d) %s ", i + 1, courses[i].course_name);
	}

	while (1)
	{
		printf("\n\n\t\t\t Select Course From Above List : ");

		if (take_int_input(&selected_course))
		{
			if (selected_course >= 1 && selected_course <= numCourses)
			{
				strcpy(student_info.student_course, courses[selected_course - 1].course_name);
				break;
			}
			else
			{
				printf("\n\t\t\t\t\x1b[38;5;45m Invalid Choice!! Please select from the options provided. \x1b[0m");
			}
		}
	}

	printf("\n\t\t\t\t\t\x1b[38;5;45m Student List \x1b[0m\n\n");

	while (fread(&student_info, sizeof(struct student), 1, fp))
	{
		if (strcmp(student_info.student_course, courses[selected_course - 1].course_name) == 0)
		{
			count++;
			printf("\n\t\t\t\t   Enrollment No.     :    %d", student_info.enrollment_no);
			printf("\n\t\t\t\t   Name               :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
			printf("\n\t\t\t\t   Date of Birth      :    %s", student_info.dob);
			printf("\n\t\t\t\t   Department         :    %s", student_info.student_course);
			printf("\n\t\t\t\t   Mobile No.         :    %s", student_info.student_mobile);
			printf("\n\t\t\t\t   Email-id           :    %s ", student_info.student_email);
			printf("\n\t\t\t\t   Fees Status        :    %s", student_info.fees);
			printf("\n\t\t\t\t   Address            :    %s", student_info.student_address);
			//					int i;
			//					for (i = 0; i < 6; i++)
			//					{
			//						printf("\n\t\t %s :",student_info.subject[i]);
			//						printf(" %d ",student_info.marks[i]);
			//	                }
			printf("\n");
			printf("\n\t\t\t\t____________________________________________________________ \n");
		}
	}
	printf("\n\t\t\t\t Total Student  : %d\n", count);

	fclose(fp);
}
void delete_student()
{
	print_banner();
	FILE *fp, *fp1;
	struct student student_info;
	int enrollment_no, found = 0;

	fp = fopen("studentinfo.bin", "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "\n\n\n\n\t\t\t Student List is Empty \n");
	}

	fp1 = fopen("temp.bin", "wb");

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +----------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |   Delete Student Details   | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +----------------------------+ \x1b[0m");

	fflush(stdin);
	printf("\n\n\n\t\t\tEnter Enrollment No. : ");
	scanf("%d", &enrollment_no);

	while (fread(&student_info, sizeof(struct student), 1, fp))
	{
		if (student_info.enrollment_no == enrollment_no)
		{
			found = 1;
			printf("\n\t\t\t\t   Enrollment No.     :    %d", student_info.enrollment_no);
			printf("\n\t\t\t\t   Name               :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
			printf("\n\t\t\t\t   Date of Birth      :    %s", student_info.dob);
			printf("\n\t\t\t\t   Department         :    %s", student_info.student_course);
			printf("\n\t\t\t\t   Mobile No.         :    %s", student_info.student_mobile);
			printf("\n\t\t\t\t   Email-id           :    %s ", student_info.student_email);
			printf("\n\t\t\t\t   Fees Status        :    %s", student_info.fees);
			printf("\n\t\t\t\t   Address            :    %s", student_info.student_address);
			printf("\n");
			printf("\n\t\t\t\t____________________________________________________________ \n");
		}
		else
		{
			fwrite(&student_info, sizeof(struct student), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	if (found)
	{
		char confirm;
		printf("\n\t\t\t   Do you want to delete this Student ? (Y/N): ");
		scanf(" %c", &confirm);

		if (confirm == 'y' || confirm == 'Y')
		{
			remove("studentinfo.bin");
			rename("temp.bin", "studentinfo.bin");
			printf("\n\n\t\t\t   Student details deleted with Enrollment No.  %d  . ", enrollment_no);
		}
		else
		{
			printf("\n\t\t\t   Student details not deleted.");
		}
	}
	if (!found)
	{
		printf("\n\n\n");
		printf("\n\t\t\t\t\x1b[38;5;45m    +--------------------------------------------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                              | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |  Sorry ! No Student details found for above Enrollment No.   | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                              | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    +--------------------------------------------------------------+ \x1b[0m");
		printf("\n\n");
	}
}

void fees_payment()
{
	print_banner();
	FILE *fp = NULL;
	FILE *fp1 = NULL;
	struct student student_info;
	int enrollment_no, found = 0;

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |        Fees Payment       | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");

	fp = fopen("studentinfo.bin", "rb");

	if (fp == NULL)
	{
		fprintf(stderr, "\n\n\n\n\t\t\t Student List is Empty \n");
	}

	fp1 = fopen("temp.bin", "wb");

	fflush(stdin);
	printf("\n\n\n\t\t\tEnter Enrollment No. : ");
	scanf("%d", &enrollment_no);

	fflush(stdin);

	while (fread(&student_info, sizeof(struct student), 1, fp))
	{
		if (student_info.enrollment_no == enrollment_no)
		{
			if (strcmp(student_info.fees, "Unpaid") == 0)
			{
				printf("\n\n\t\t\t--------------------------------------------------------------------");
				printf("\n\t\t\t\t   Enrollment No.   :    %d", student_info.enrollment_no);
				printf("\n\t\t\t\t   Name             :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
				printf("\n\t\t\t\t   Department       :   \x1b[38;5;45m %s \x1b[0m", student_info.student_course);
				printf("\n\t\t\t\t   Fees Status      :    %s", student_info.fees);
				printf("\n");
				printf("\n\t\t\t--------------------------------------------------------------------");
				found = 1;

				char confirm;
				printf("\n\t\t\t   Do You Want to Deposite Fees for Above Student ? (Y/N): ");
				scanf(" %c", &confirm);

				if (confirm == 'y' || confirm == 'Y')
				{
					strcpy(student_info.fees, "Paid");
					fwrite(&student_info, sizeof(struct student), 1, fp1);
					printf("\n\t\t\t\x1b[38;5;45m Fees Deposited Successfully !!  \x1b[0m");
				}
				else
				{
					printf("\n\t\t\t\x1b[38;5;45m  Fees Not Deposited  !!  \x1b[0m");
					fwrite(&student_info, sizeof(struct student), 1, fp1);
				}
			}
			else
			{
				printf("\n\n\t\t\t--------------------------------------------------------------------");
				printf("\n\t\t\t\t   Enrollment No.   :    %d", student_info.enrollment_no);
				printf("\n\t\t\t\t   Name             :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
				printf("\n\t\t\t\t   Department       :   \x1b[38;5;45m %s \x1b[0m", student_info.student_course);
				printf("\n\t\t\t\t   Fees Status      :    %s", student_info.fees);
				printf("\n");
				printf("\n\t\t\t--------------------------------------------------------------------");
				found = 1;

				printf("\n\t\t\t\x1b[38;5;45m  Fees Already Paid  \x1b[0m");

				fwrite(&student_info, sizeof(struct student), 1, fp1);
			}
		}
		else
		{
			fwrite(&student_info, sizeof(struct student), 1, fp1);
		}
	}

	fclose(fp);
	fclose(fp1);
	remove("studentinfo.bin");
	rename("temp.bin", "studentinfo.bin");

	if (!found)
	{

		printf("\n\n\n");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-------------------------------------------------------------+ \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                             | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                Sorry ! Invalid Enrollment Number            | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    |                                                             | \x1b[0m");
		printf("\n\t\t\t\t\x1b[38;5;45m    +-------------------------------------------------------------+ \x1b[0m");
		printf("\n\n");
	}
}
//void fees_pending_list()
//{
//	print_banner();
//	FILE *fp = NULL;
//	struct student student_info;
//	int found = 0;
//	printf("\n");
//	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");
//	printf("\n\t\t\t\t\t\x1b[38;5;45m      |     Fees Pending List     | \x1b[0m");
//	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");
//
//	fp = fopen("studentinfo.bin", "rb");
//	if (fp == NULL)
//	{
//		fprintf(stderr, "\n\n\n\n\t\t\t Student List is Empty \n");
//	}
//		printf("\n\n\t Enrollment No \t\t Name \t Department ");
//		printf("\n\n\t---------------------------------------------------------------------------");
//		while (fread(&student_info, sizeof(struct student), 1, fp))
//		{
//			if (strcmp(student_info.fees, "Unpaid") == 0)
//			{
//				printf("\n\t  %d  %s  %s" , student_info.enrollment_no,student_info.student_name,student_info.student_course);
//				found = 1;
//			}
//			
//		}
//	
//	fclose(fp);
//}

void fees_pending_list()
{
    print_banner();
    struct course courses[50];
    struct student student_info;
    int selected_course, i, count = 0;
    FILE *fp_courses = fopen("courseinfo.bin", "rb");
    
    if (fp_courses == NULL)
    {
        fprintf(stderr, "\n\n\n\n\t\t\t Course List is Empty \n");
        return;
    }

    int numCourses = 0;
    while (fread(&courses[numCourses], sizeof(struct course), 1, fp_courses) == 1)
    {
        (numCourses)++;
    }

    fclose(fp_courses);

    printf("\n");
    printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");
    printf("\n\t\t\t\t\t\x1b[38;5;45m      |     Fees Pending List     | \x1b[0m");
    printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");

    FILE *fp_students = fopen("studentinfo.bin", "rb");
    if (fp_students == NULL)
    {
        fprintf(stderr, "\n\n\n\n\t\t\t Student List is Empty \n");
        return;
    }

    
    for (i = 0; i < numCourses; i++)
    {
        printf("\n\t\t\t     (%d) %s ", i + 1, courses[i].course_name);
    }

    while (1)
    {
        printf("\n\n\t\t\t Select Course From Above List : ");

        if (take_int_input(&selected_course))
        {
            if (selected_course >= 1 && selected_course <= numCourses)
            {
                break;
            }
            else
            {
                printf("\n\t\t\t\t\x1b[38;5;45m Invalid Choice!! Please select from the options provided. \x1b[0m");
            }
        }
    }
    printf("\n\t\t\t-------------------------------------------------------------------");
	printf("\n\t\t\t Enrollment No \t\t Name ");
    printf("\n\t\t\t-------------------------------------------------------------------\n");
    while (fread(&student_info, sizeof(struct student), 1, fp_students))
    {
        if (strcmp(student_info.student_course, courses[selected_course - 1].course_name) == 0 &&
            strcmp(student_info.fees, "Unpaid") == 0)
        {
            count++;
            printf("\n\t\t\t  %d  \t\t %s ", student_info.enrollment_no, student_info.student_name);
        }
    }
	printf("\n\n\t\t\t-------------------------------------------------------------------");
    printf("\n\t\t\t Total Students : %d\n", count);
    fclose(fp_students);
}


void getPassword(char *password, int max_len)
{
	int i = 0;
	char ch;
	while (1)
	{
		ch = getch();
		if (ch == 13) // Enter key
			break;
		else if (ch == 8) // Backspace
		{
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}
		else if (i < max_len - 1)
		{
			password[i++] = ch;
			printf("*");
		}
	}
	password[i] = '\0';
}

void adminlogin()
{
	print_banner();
	struct login user;
	FILE *fp;
	char id[20], pass[20];

	fp = fopen("adminlogin.bin", "rb");
	if (fp == NULL)
	{
		printf("\n\n\n\n\n\t\t\t\x1b[33m No any admin account found !!! Create a admin account first...... \x1b[0m");
		getch();
		adminregister();
	}
	fread(&user, sizeof(struct login), 1, fp);
	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |        ADMIN LOGIN        | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");

	printf("\n\n\n\t\t\t Enter Username : ");
	scanf("%s", &id);
	printf("\n\t\t\t Enter Password : ");
	getPassword(pass, sizeof(pass));
	if ((strcmp(user.username, id) == 0) && (strcmp(user.password, pass) == 0))
	{
		admin_home();
	}
	else
	{
		printf("\n\n\t\t\x1b[33m !!! Wrond username or password... \x1b[0m");
		getch();
		system("cls");
		adminlogin();
	}
	fclose(fp);
}

void adminregister()
{
	print_banner();
	struct login user;
	FILE *fp;
	fp = fopen("adminlogin.bin", "wb");
	if (fp == NULL)
	{
		printf("Error opening the file for writing.\n");
	}
	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |      ADMIN REGISTRATION       | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------------+ \x1b[0m");

	printf("\n\n\n\t\t\tEnter new username: ");
	fgets(user.username, sizeof(user.username), stdin);
	user.username[strcspn(user.username, "\n")] = '\0'; // Remove newline character

	printf("\n\n\t\t\tEnter new password: ");
	getPassword(user.password, sizeof(user.password));
	user.password[strcspn(user.password, "\n")] = '\0';

	fwrite(&user, sizeof(struct login), 1, fp);
	fclose(fp);
	printf("\n\n\n\t\t\t\x1b[33m Admin account created successfully !! Press any key to continue... \x1b[0m");
	getch();
	adminlogin();
}
void updateadmindata()
{
	print_banner();
	struct login user;
	FILE *fp;

	fp = fopen("adminlogin.bin", "rb+");
	if (fp == NULL)
	{
		printf("\n\n\n\n\n\t\t\t\x1b[33m No admin account found! Create an admin account first...\x1b[0m");
		getch();
		adminregister();
	}

	fread(&user, sizeof(struct login), 1, fp);

	printf("\n");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      |    UPDATE ADMIN CREDENTIALS   | \x1b[0m");
	printf("\n\t\t\t\t\t\x1b[38;5;45m      +-------------------------------+ \x1b[0m");

	printf("\n\n\n\t\t\tEnter new username: ");
	scanf("%s", user.username);

	printf("\n\t\t\tEnter new password: ");
	getPassword(user.password, sizeof(user.password));
	// Move file pointer to the beginning of file
	fseek(fp, 0, SEEK_SET);
	fwrite(&user, sizeof(struct login), 1, fp);
	fclose(fp);

	printf("\n\n\n\t\t\t\x1b[33m Admin account updated successfully! Press any key to continue...\x1b[0m");
}

void teacherlogin()
{
    print_banner();
    struct teacher teacher_info;
    FILE *fp;
    char id[20], pass[20];
    int loginSuccess = 0;

    fp = fopen("teacherinfo.bin", "rb");
    if (fp == NULL)
    {
        printf("\n\n\n\n\n\t\t\t\x1b[33m Teacher login credentials not found... \x1b[0m");
        getch();
        home();
        return;
    }
    printf("\n");
    printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");
    printf("\n\t\t\t\t\t\x1b[38;5;45m      |       TEACHER LOGIN       | \x1b[0m");
    printf("\n\t\t\t\t\t\x1b[38;5;45m      +---------------------------+ \x1b[0m");

    printf("\n\n\n\t\t\t Enter Email-id : ");
    scanf("%19s", id);  // Limit the input length to prevent buffer overflow
    printf("\n\t\t\t Enter Password : ");
    getPassword(pass, sizeof(pass));

    while (fread(&teacher_info, sizeof(struct teacher), 1, fp) == 1)
    {
        if ((strcmp(teacher_info.teacher_email, id) == 0) && (strcmp(teacher_info.teacher_password, pass) == 0))
        {
            loginSuccess = 1;
            break;
        }
    }
    if (loginSuccess)
    {
        teacher_home(id);
    }
    else
    {
        printf("\n\n\t\t\x1b[33m Wrong username or password... \x1b[0m");
        getch();
    }
    fclose(fp);
}

void teacher_home(char *id)
{
	print_banner();
	struct teacher teacher_info;
	FILE *fp;
	int choice;
	
	while (choice != 4)
	{	
		print_banner();
		fp = fopen("teacherinfo.bin", "rb");
		printf("\n");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m |      MENU      | \x1b[0m");
		printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
			
		while (fread(&teacher_info, sizeof(struct teacher), 1, fp))
		{
			if (strcmp(teacher_info.teacher_email, id) == 0)
			{
				printf("\n\n\t\t\t Welcome, \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_name);
			}
		}
		fclose(fp);
		printf("\n\n\n\t\t\t       (1)  View Profile ");
		printf("\n\n\t\t\t       (2)  Add Student Marks       ");
		printf("\n\n\t\t\t       (3)  Change Password  ");
		printf("\n\n\t\t\t       (4)  Exit       ");
		fflush(stdin);
		while (1)
		{
			printf("\n\n\t\t\t\x1b[38;5;45m Please enter your choice : \x1b[0m");
			fflush(stdin);
			if (take_int_input(&choice))
			{
				if (choice >= 1 && choice <= 4)
				{
					show_teacher_actions(choice,id);
					break;
				}
				else
				{
					printf("\n\t\t\t\t Please Enter a Valid Choice... ");
				}
			}
		}
	}		
	getch();	
}
void show_teacher_actions(int action,char *id)
{
	switch (action)
	{
		case 1:
			show_teacher_profile(id);
			printf("\n\t\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
			getch();
			break;
		case 2:
			add_student_marks(id);
			printf("\n\n\t\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
			getch();
			break;
		case 3:
			update_teacher_password(id);
			printf("\n\n\n\t\t\t\x1b[33m Press any key for return to main menu... \x1b[0m");
			getch();
			break;
		case 4:
			break;		
		default:
			break;
	}
}
void show_teacher_profile(char *id)
{
	print_banner();
	struct teacher teacher_info;
	FILE *fp;	
	fp = fopen("teacherinfo.bin", "rb");
	printf("\n");
	printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
	printf("\n\t\t\t\t\t\t\x1b[38;5;45m |    PROFILE     | \x1b[0m");
	printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------+ \x1b[0m");
	while (fread(&teacher_info, sizeof(struct teacher), 1, fp))
	{
		if (strcmp(teacher_info.teacher_email, id) == 0)
		{
			printf("\n\n\t\t\t Welcome, \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_name);
			printf("\n\n\t\t\t\t   ID               :    %d", teacher_info.teacher_id);
			printf("\n\n\t\t\t\t   Name             :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_name);
			printf("\n\n\t\t\t\t   Department       :   \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_course);
			printf("\n\t\t\t\t   Date of Joining  :    %s", teacher_info.teacher_doj);
			printf("\n\n\t\t\t\t   Mobile No.       :    %s", teacher_info.teacher_mobile);
			printf("\n\n\t\t\t\t   Email-id         :    %s ", teacher_info.teacher_email);
			printf("\n\n\t\t\t\t   Salary           :    %d", teacher_info.teacher_salary);
			printf("\n");
			printf("\n\t\t\t\t_____________________________________________________ \n");
		}
	}
	fclose(fp);
}
void update_teacher_password(char *id)
{
	print_banner();
    struct teacher teacher_info;
    FILE *fp;
    fp = fopen("teacherinfo.bin", "r+b");
    printf("\n");
    printf("\n\t\t\t\t\t\t\x1b[38;5;45m +---------------------+ \x1b[0m");
    printf("\n\t\t\t\t\t\t\x1b[38;5;45m |   CHANGE PASSWORD   | \x1b[0m");
    printf("\n\t\t\t\t\t\t\x1b[38;5;45m +---------------------+ \x1b[0m");

    if (fp == NULL) 
	{
        fprintf(stderr, "\n\n\n\n\t\t\t Teacher's List is Empty \n");
        return;
    }
    while (fread(&teacher_info, sizeof(struct teacher), 1, fp) == 1) 
	{
        if (strcmp(teacher_info.teacher_email, id) == 0) 
		{
			printf("\n\n\t\t\t Welcome, \x1b[38;5;45m %s \x1b[0m", teacher_info.teacher_name);
        	printf("\n\n\n\t\t\tEnter new password: ");
			getPassword(teacher_info.teacher_password, sizeof(teacher_info.teacher_password));
            fseek(fp, -(long int)sizeof(struct teacher), SEEK_CUR);  // Move the file pointer back
            fwrite(&teacher_info, sizeof(struct teacher), 1, fp);
            break;
        }
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\x1b[38;5;45m Password Updated Successfully !!  \x1b[0m");
}
void add_student_marks(char *id) 
{
	print_banner();
    FILE *fp, *tempFile;
    struct teacher teacher_info;
    struct student student_info;
    int enrollment_no, found = 0, i;

    FILE *fp1 = fopen("teacherinfo.bin", "rb");
    if (fp1 == NULL) 
	{
        fprintf(stderr, "\n\n\n\n\t\t\t Teacher's List is Empty \n");
        return;
    }
    while (fread(&teacher_info, sizeof(struct teacher), 1, fp1) == 1) 
	{
        if (strcmp(teacher_info.teacher_email, id) == 0) {
            break; // match teacher & student course
        }
    }
    fclose(fp1);

    fp = fopen("studentinfo.bin", "rb");
    tempFile = fopen("temp.bin", "wb");
    printf("\n");
    printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------------+ \x1b[0m");
    printf("\n\t\t\t\t\t\t\x1b[38;5;45m |  ADD STUDENT MARKS   | \x1b[0m");
    printf("\n\t\t\t\t\t\t\x1b[38;5;45m +----------------------+ \x1b[0m");
    printf("\n\n\t\t\tEnter Enrollment No : ");
    scanf("%d", &enrollment_no);
	    while (fread(&student_info, sizeof(struct student), 1, fp)) 
		{
	        if (student_info.enrollment_no == enrollment_no && strcmp(student_info.student_course, teacher_info.teacher_course) == 0) 
			{
	            found = 1;
	            printf("\n\t\t\t____________________________________________________________");
	            printf("\n\t\t\t   Enrollment No.    :   \x1b[38;5;45m %d \x1b[0m", student_info.enrollment_no);
	            printf("\n\t\t\t   Name              :   \x1b[38;5;45m %s \x1b[0m", student_info.student_name);
	            printf("\t\t\t   Department        :   \x1b[38;5;45m %s \x1b[0m", student_info.student_course);
	            for (i = 0; i < 6; i++) 
				{
	                printf("\n\t\t\t    %s  : %d", student_info.subject[i],student_info.marks[i]);
	            }
	            printf("\n\t\t\t____________________________________________________________ \n");
	
	            char confirm;
	            printf("\n\t\t\t   Do you want to proceed ? (Y/N): ");
	            scanf(" %c", &confirm);
	            if (confirm == 'y' || confirm == 'Y') 
				{
	                printf("\n\t\t\t Enter Marks for below subjects \n");
	                for (i = 0; i < 6; i++) 
					{
	                    printf("\n\t\t\t %s  :  ", student_info.subject[i]);
	                    while (!take_int_input(&student_info.marks[i])) 
						{
	                        printf("\n\t\t\t %s  :", student_info.subject[i]);
	                    }
	                }
	                printf("\n\t\t\t Marks updated successfully \n");
	                fwrite(&student_info, sizeof(struct student), 1, tempFile);
	            } 
				else 
				{
					printf("\n\t\t\t Student marks not updated.... ");
	                fwrite(&student_info, sizeof(struct student), 1, tempFile);
	            }
	        } 
			else 
			{
	            fwrite(&student_info, sizeof(struct student), 1, tempFile);
	        }
	    }

	    if (!found) 
		{
	        	printf("\n\n\n");
				printf("\n\t\t\t\t\x1b[38;5;45m +----------------------------------------------------------------------+ \x1b[0m");
				printf("\n\t\t\t\t\x1b[38;5;45m |                                                                      | \x1b[0m");
				printf("\n\t\t\t\t\x1b[38;5;45m |    Sorry ! Above Enrollment No. doesn't exist in your Department     | \x1b[0m");
				printf("\n\t\t\t\t\x1b[38;5;45m |                                                                      | \x1b[0m");
				printf("\n\t\t\t\t\x1b[38;5;45m +----------------------------------------------------------------------+ \x1b[0m");
				printf("\n\n");
	    }
	    fclose(fp);
	    fclose(tempFile);
	    remove("studentinfo.bin");
	    rename("temp.bin", "studentinfo.bin");
}
void studentlogin()
{
	print_banner();
	printf("\n working.... ");
	getch();
}
void student_home(char *id)
{
	
}
