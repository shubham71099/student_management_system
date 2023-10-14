#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void print_banner();
void admin_home();
void show_admin_actions(int action);
int add_course();
void edit_course();
void view_course();

struct course
{
	char course_name[30];
	int course_id;
	char subject[6][50];
};
struct student
{
	char firstname[20];
	char lastname[20];
	int rollno;
	char course[15];
	char address[30];
};
struct login
{
	char username[20];
	char password[20];
};

void main()
{
	admin_home();
}

void print_banner()
{
	system("cls");
	printf("\t\t\t\x1b[38;5;45m =========================================================================== \x1b[0m\n");
	printf("\t\t\t\x1b[38;5;45m ===============         STUDENT MANAGEMENT SYSTEM         ================= \x1b[0m\n");
	printf("\t\t\t\x1b[38;5;45m =========================================================================== \x1b[0m\n");
}

void admin_home()
{
	int choice;
	while (choice != 12)
	{
		print_banner();
		printf("\n\n\t\t\t\t\t\t\t   MENU ");
		printf("\n\n");
		printf("\n\t\t\t       (1) Add New Course       ");
		printf("\n\t\t\t       (2) Edit Course Details       ");
		printf("\n\t\t\t       (3) List of Courses       ");
		printf("\n\t\t\t       (4) Add New Teacher       ");
		printf("\n\t\t\t       (5) Edit Teacher Details       ");
		printf("\n\t\t\t       (6) List of Teachers       ");
		printf("\n\t\t\t       (7) Add New Student       ");
		printf("\n\t\t\t       (8) Edit Student Details       ");
		printf("\n\t\t\t       (9) Search Student Details       ");
		printf("\n\t\t\t       (10) List of Students       ");
		printf("\n\t\t\t       (11) Update Userid & Password       ");
		printf("\n\t\t\t       (12) Exit       ");

		while (1)
		{
			printf("\n\n\t\t\t\x1b[38;5;45m Enter your choice : \x1b[0m");
			if (scanf("%d", &choice) == 1)
			{
				if (choice >= 1 && choice <= 12)
				{
					show_admin_actions(choice);
					break;
				}
				else
				{
					printf("\n\t\t\t\t Please enter a Valid Choice... ");
				}
			}
			else
			{
				printf("\n\t\t\t\t Please enter number only... ");
				while (getchar() != '\n')
					;
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

		break;

	case 5:

		break;

	case 6:

		break;

	case 7:

		break;

	case 8:

		break;

	case 9:

		break;

	case 10:

		break;

	case 11:

		break;

	case 12:
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
	char line[100];
	int i;

	printf("\n");
	printf("\n\t\t\t\t\t    ****************************");
	printf("\n\t\t\t\t\t    ***    Add New Course    ***");
	printf("\n\t\t\t\t\t    ****************************");

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

	// printf("\n\n\tLast ID: %d\n", last_course_id);
	fp = fopen("courseinfo.bin", "ab");

	if (fp == NULL)
	{
		fprintf(stderr, "\t\t\t\n Can't Open");
		return 1;
	}

	course_info.course_id = last_course_id + 1;

	printf("\n\n\t\t\tEnter Course Name : ");
	scanf("%s", course_info.course_name);

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
	printf("\n\n\t\t\t\t  Course ID        :      %d", course_info.course_id);
	printf("\n\n\t\t\t\t  Course Name      :   \x1b[38;5;45m   %s \x1b[0m", course_info.course_name);
	printf("\n\n\t\t\t\t  Subjects              ");
	printf("\n\t\t\t\t_____________");
	printf("\n");
	for (i = 0; i < 6; i++)
	{
		printf("\n\t\t\t\t  Subject %d        :       %s\n", i + 1, course_info.subject[i]);
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
	printf("\n\t\t\t\t\t    ****************************");
	printf("\n\t\t\t\t\t    ***  Edit Course Detail  ***");
	printf("\n\t\t\t\t\t    ****************************");

	if (fp == NULL)
	{
		fprintf(stderr, "\t\t\t\n Can't Open\n");
	}

	fp1 = fopen("temp.bin", "wb");

	printf("\n\n\t\t\tEnter Course Id to Update : ");
	scanf("%d", &course_id);

	while (fread(&course_info, sizeof(struct course), 1, fp))
	{
		if (course_info.course_id == course_id)
		{
			printf("\n\n\t\t\t--------------------------------------------------------------------");
			printf("\n\n\t\t\t\t  Course ID        :  %d", course_info.course_id);
			printf("\n\n\t\t\t\t  Course Name      : \x1b[38;5;45m %s \x1b[0m", course_info.course_name);
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
		printf("\n\n\t\t\t\t ******************************************************************** ");
		printf("\n\t\t\t\t ******************************************************************** ");
		printf("\n\t\t\t\t *****                                                          ***** ");
		printf("\n\t\t\t\t ****     Sorry ! No Course details found with Course ID  %d   ****", course_id);
		printf("\n\t\t\t\t *****                                                          ***** ");
		printf("\n\t\t\t\t ******************************************************************** ");
		printf("\n\t\t\t\t ******************************************************************** ");
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
		printf("\t\t\t\n Can't Open\n");
	}
	else
	{
		printf("\n");
		printf("\n\t\t\t\t\t    ****************************");
		printf("\n\t\t\t\t\t    ***      Course List     ***");
		printf("\n\t\t\t\t\t    ****************************");
		printf("\n\t\t\t\t____________________________________________________________ \n");
	}

	while (fread(&course_info, sizeof(struct course), 1, fp))
	{

		printf("\n\t\t\t\t   Course ID         :    %d", course_info.course_id);
		printf("\n\t\t\t\t   Course Name       :   \x1b[38;5;45m %s \x1b[0m", course_info.course_name);
		printf("\n");
		for (i = 0; i < 6; i++)
		{
			printf("\n\t\t\t\t   Subject %d         :    %s", i + 1, course_info.subject[i]);
		}
		printf("\n\t\t\t\t____________________________________________________________ \n");
	}
	fclose(fp);
}
