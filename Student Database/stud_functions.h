/*********************************************************************************************************
											 HEADER FILES										
*********************************************************************************************************/

#include "stud_data.h"

/*********************************************************************************************************
									  	    MACRO DEFINITIONS
*********************************************************************************************************/

//Debug macros
#define DISP_DEBUG		1
#define ADD_DEBUG		1
#define DEL_DEBUG		1
#define SEARCH_DEBUG	1
#define SBN_DEBUG		1
#define SBR_DEBUG		1
#define SORT_DEBUG		1
#define SOBN_DEBUG		1
#define SOBR_DEBUG		1
#define MARKS_DEBUG		1

//Operation specific macros
#define SEARCH_BY_NAME	1
#define SEARCH_BY_RNO	2

#define SORT_BY_NAME	1	
#define SORT_BY_RNO		2

#define DEL_BY_NAME		1
#define DEL_BY_ROLL		2

#define STRING_COMPARE_FAIL			-1
#define STRING_EQUAL				0
#define STRING_1					1
#define STRING_2					2
#define STRING_UNDEFINED			3

#define MAX_MARK		100

#define NOT_FOUND 		-1
#define FIRST_POSITION 	0

#define INVALID_MARKS(x, MAX_MARK)		( ( x < 0 ) || ( x > MAX_MARK ) )
#define YES(x)							( (x == 'y') || (x == 'Y') )
#define NO(x)							( (x == 'n') || (x == 'N') )

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
int add_to_file( FILE*, STUDENT* );		//Adds structure contents to file
void free_students( STUDENT* );			//Freeing dynamically allocated student name and marks memory
int string_compare(char*, char*);	//Compares two strings and check if they are equal
int char_count(char *);	//Finding size of string 		
int student_count(STUDENT*);	//FInding number of students

/*********************************************************************************************************/
