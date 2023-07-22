
/********************************************************************HEADER FILES**********************************************************************/

#include <stdio.h>

/******************************************************************MACRO DEFINITIONS*******************************************************************/

#define PASS			0
#define FAIL			1

#define VALID   		PASS
#define EXIT_PROGRAM    FAIL			

#define NULL_CHAR		'\0'
#define NEWLINE			'\n'

//Number of arguments
#define ONE_ARGUMENT		1
#define TWO_ARGUMENTS		2
#define THREE_ARGUMENTS		3
#define FOUR_ARGUMENTS		4
#define FIVE_ARGUMENTS		5

//Macros for scanf
#define INPUT_SUCCESS( x,y )	(x == y) 	//x - scanf return , y - number of arguments in scanf
#define INPUT_FAILURE( x,y )	(x != y)	//x - scanf return , y - number of arguments in scanf

//Generic integer macros
#define INT_NEGATIVE(x)			(x < 0)
#define INT_POSITIVE(x)			(x > 0)
#define IS_ZERO(x)				(x == 0)
#define NOT_ZERO(x)				(x != 0)
#define NUM_COMPARE( x,y )		(x == y)

//Generic character macros
#define IS_DIGIT(x)				( (x >= '0') && (x <= '9') )		
#define IS_ALPHA(x)				( ( (x >= 'A') && (x <= 'Z') ) || ( (x >= 'a') && (x <= 'z') ) )
#define CHAR_NEGATIVE(x)		(x == '-')
#define CHAR_POSITIVE(x)		(x == '+')
#define IS_NEWLINE(x)			(x == '\n') 
#define NOT_NEWLINE(x)			(x != '\n')
#define IS_WHITESPACE(x)		(x == ' ')
#define NOT_WHITESPACE(x)		(x != ' ')


/*************************************************************FUNCTION PROTOTYPES**********************************************************************/

int int_input_validate(int*);
int int_input_validate_two(int*, int*);

int char_input_validate(char*);
int string_validate(char*, int);

/******************************************************************************************************************************************************/


