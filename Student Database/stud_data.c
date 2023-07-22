/*******************************************************************************************************
*   TASK :
*
* 	1. Create a student database in .csv format containing the following details :
*
*		( name, age, roll number, three subject marks ) 
*
*	2. Allow user to perform the following operations :	
*		
*		-> 	Listing database
*		->	Adding student data to database
*		->	Deleting student data from database
*		->	Searching student based on name / roll number
*		->	Sorting based on name / roll number
*		->	Total marks of student 
*		->	Average marks of student
*		->	Exit
*
*	3. Perform input validation
*
*	Date : 22/10/2021	10:30:00 AM
*
**********************************************************************************************************
											 HEADER FILES										
*********************************************************************************************************/

#include "stud_data.h"

/**********************************************************************************************************
								     	   FUNCTION PROTOTYPES
**********************************************************************************************************/

//Functions used to perform operations based on user choice
int display_student( STUDENT*);
int add_student( STUDENT**, int* );
int del_student( STUDENT** );
int search_student( STUDENT* );
void search_by_name( STUDENT*, char*, int* );
int search_by_roll( STUDENT*, int );
int sort_student( STUDENT ** );
int sort_by_name( STUDENT** );
int sort_by_roll( STUDENT** );
int marks_student( STUDENT*, int );

//Helper function prototypes
int get_file_contents( FILE*, STUDENT** );	//Used to get file contents into structure
int add_to_file( FILE*, STUDENT* );			//Adds structure contents to file
void free_students( STUDENT* );				//Freeing dynamically allocated student name and marks memory
int string_compare(char*, char*);			//Compares two strings and check if they are equal
int char_count(char *);						//Finding size of string 		
int student_count(STUDENT*);				//FInding number of students

/**********************************************************************************************************
								    		  MAIN FUNCTION
**********************************************************************************************************/

int main()	
{
	FILE *fp;
	STUDENT *stud = NULL;	//Structure objects containing student details
	int choice, status = RUN_PROGRAM, flag = 0, pos;	

	//Opening file to read content

	fp = fopen("student.csv", "r+");		
	if ( fp == NULL )
	{
		printf("\nFILE DOES NOT EXIST\n\n");
		return EXIT_FAILURE;
	}

	//Allocating memory dynamically and checking if it was properly allocated

	stud = ( STUDENT *)malloc( STUDENTS_COUNT * sizeof( STUDENT ) );
	if ( stud == NULL )
	{
		printf("Could not allocate memory\n");
		return EXIT_FAILURE;
	}

	pos = get_file_contents( fp, &stud );	

	//Closing file after copying contents to struct student 
	fclose(fp);
	
	do
	{
		printf("\n\n\t\t\t\t\tSTUDENT DATABASE MANAGEMENT\n\n\
				1. List student data\n\
				2. Add student data\n\
				3. Delete student data\n\
				4. Search student data\n\
				5. Sort Student data\n\
				6. Display total marks of student\n\
				7. Display average mark of student\n\
				8. Exit\n\n\
				ENTER YOUR CHOICE : ");

		if ( int_input_validate( &choice ) == PASS )		//Getting choice from user 
		{
			switch( choice )
			{
				case  LIST_DATA 	  	: 	flag = display_student( stud );
											break;
				
				case  ADD_DATA  		: 	flag = add_student( &stud, &pos );
							        		break;											
				
				case  DEL_DATA			: 	flag = del_student( &stud );
											break;
		
				case  SEARCH_DATA 		: 	flag = search_student( stud );				            			
											break;		
		
				case  SORT_DATA			:	flag = sort_student( &stud );				            			
											break;	

				case  TOTAL_MARKS 		: 	flag = marks_student( stud, TOTAL_MARKS );
						        			break;		
		
				case  AVG_MARKS 		:	flag = marks_student( stud, AVG_MARKS );
											break;
		
				case  EXIT	  	 		: 	status = EXIT_PROGRAM ; 
											break;	
		
				default		  	  		: 	printf("Enter valid choice ( 1 to 8 )");
		           	          				break;
			}
		}

		if ( status == EXIT_PROGRAM )
		{
			printf("\n\nSTUDENT DATABASE CLOSED\n\n");
			break;
		}

	}while(1);	


	//Updating database to file
	
	fp = fopen("student.csv", "w+");		
	if ( fp == NULL )
	{
		printf("Cannot open file\n");
		fclose(fp);
		return EXIT_FAILURE;
	}

	add_to_file( fp, stud );

	//Freeing heap memory after using it
	if ( stud != NULL )
	{
		free_students( stud );
		free( stud );
		stud = NULL;
	}

	//Closing file
	fclose(fp);
	
	if ( flag == FAIL )
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/*********************************************************************************************************/

