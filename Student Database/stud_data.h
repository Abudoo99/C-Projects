/*********************************************************************************************************
											 HEADER FILES										
*********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "validate.h"

/*********************************************************************************************************
									  	   MACRO DEFINITIONS
*********************************************************************************************************/

#define STUDENTS_COUNT		100		
#define NAME_SIZE			100
#define NUMBER_OF_MARKS		3

#define RUN_PROGRAM		0
#define EXIT_PROGRAM	-1


enum options{
			LIST_DATA = 1,
			ADD_DATA,
			DEL_DATA,
			SEARCH_DATA,
			SORT_DATA,
			TOTAL_MARKS,
			AVG_MARKS,
			EXIT
			};


/**********************************************************************************************************
								    	  STRUCTURE DEFINITIONS
**********************************************************************************************************/

typedef struct 
{
	int age;
	int r_no, *marks;
	char *name;	
}STUDENT;

/*********************************************************************************************************/

