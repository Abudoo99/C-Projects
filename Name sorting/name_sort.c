/*******************************************************************************************************************************************************
*   TASK :
*
* 	1. Get an input string of names from user dynamically.
*	2. Sort the given string of names in alphabetical order 
*	
*	Perform input validation
*
*	Date : 06/10/2021
*
*********************************************************************HEADER FILES**********************************************************************/

#include <stdlib.h>
#include "validate.h"

/******************************************************************MACRO DEFINITIONS*******************************************************************/
#define EMPTY					1

#define STRING_COMPARE_FAIL	   -1
#define STRING_EQUAL			1
#define STRING_1				2
#define STRING_2				3
#define STRING_UNDEFINED 		4

#define NEXT_CHAR				1

#define NAME_COUNT				100
#define MAX_CHAR_SIZE			40

/*************************************************************FUNCTION PROTOTYPES*********************************************************************/

int input_names( void );
int sort_names( char** );
void display_names( char** );
void free_names( char ** );
int get_string(char*);
int char_count( char* );
int string_count( char** );
int string_compare( char*, char* );

/*****************************************************************MAIN FUNCTION************************************************************************/

int main()
{
	printf("\nEnter string of names :\n\n");

	if ( input_names() == PASS )					//Checking if input names are received properly
	{			
		printf("\n\nNAME SORTING SUCCESSFUL\n\n");
	}
	else
	{	
		//Program execution not successful
		return FAIL;
	}
	return PASS;	
}


/*************************************************************FUNCTION PROTOTYPES********************************************************************/  


/* Function receives a string of names and returns its count
*   
*   Function Name : string_count
*
*   Parameters : char **str		-	string whose length we must find
*   
*   Return     : number of strings
*/

int string_count(char **str)
{
  int size = 0;

  while ( *( str + size) != NULL )
  {
    size++;
  }
 
  return size;
}



/* Function receives a string of names and returns its length 
*   
*   Function Name : char_count
*
*   Parameters : char *str		-	string whose length we must find
*   
*   Return     : size of string
*/

int char_count(char *str)
{
  int size = 0;

  while ( *(str + size) != NULL_CHAR )
  {
    size++;
  }
 
  return size;
}



/* Function receives names from user 
*   
*   Function Name : get string
*
*   Parameters 	  : char *name 	- 	String to receive
*   
*   Return	      : PASS or FAIL
*/

int get_string( char *name )
{
	int char_num = 0;		//For getting characters
	int char_check = 0; 	//For checking EOF

	while (1)
	{
		char_check = scanf("%c", ( name + char_num ));

		if ( char_check == EOF )
		{
			return EOF;
		}
	
		if (*( name + char_num ) == NEWLINE || *( name + char_num ) == WHITESPACE )
		{
			*( name + char_num ) = NULL_CHAR;
			return PASS;
		}

		char_num++;
	}
}
	



/* Function receives names from user 
*   
*   Function Name : input_names
*
*   Parameters 	  : char **names 	- 	Array to store strings received from user 
*					int names_count - 	number of names to be taken from user
*   
*   Return	      : PASS or FAIL
*/

int input_names( void )
{
	int str_num = 0; 			//String number
	char **names = NULL;		//Double pointer containing the names
	int end_check = 0;			//Used to check EOF occurence
	int curr_count = 0;			//For finding number of strings

	int max_names = NAME_COUNT;		//Initial number of strings set to NAME_COUNT

	names = (char**)malloc( max_names * sizeof(char*) );		//Dynamically allocating memory for names

	if ( names == NULL )										//checking if memory was allocated successfully
	{
		printf("\nCould not allocate memory\n");
	}

	while(1)
	{
		*( names + str_num ) = (char*)malloc( MAX_CHAR_SIZE * sizeof(char) );	

		if ( *( names + str_num ) == NULL )							//checking if memory was allocated successfully
		{
			printf("\nCould not allocate memory\n");
			return FAIL;
		}
		
		end_check = get_string( *( names + str_num ) );		//Getting string and checking EOF occurence
		if ( end_check == EOF )
		{
			*( names + str_num ) = NULL;
			break;
		}

		curr_count++;										//Incrementing number of strings by 1

		if ( curr_count > max_names )
		{
			names = (char **)realloc( names, (max_names + 10) * sizeof(char*) );	//Allocating memory for 10 more names
			
			if ( names == NULL )							//checking if memory was re-allocated successfully
			{
				printf("\nCould not re-allocate memory\n");
				return FAIL;
			}
			
			max_names = max_names + 10;	
		}

		*( names + str_num ) = (char *)realloc( *( names + str_num ), char_count( *( names + str_num ) ) );

		if ( *( names + str_num ) == NULL )							//checking if memory was re-allocated successfully
		{
			printf("\nCould not re-allocate memory\n");
			return FAIL;
		}

		INCREMENT( str_num );
	}

	names = (char **)realloc(names,( string_count(names) + 1 ) * sizeof(char *));
	
	if ( names == NULL )									//checking if memory was re-allocated successfully
	{
		printf("\nCould not re-allocate memory\n");
		return FAIL;
	}

	max_names = string_count( names );			//Getting number of strings 

	if ( sort_names( names ) == PASS )						//Checking if sorting is successful
	{
		printf("Number of names : %d\n", max_names);

		if ( names != NULL )
		{
			free_names( names );
			free( names );
			names = NULL;
		}

		return PASS;
	}
	else
	{
		return FAIL;
	}
}




/* Function receives names from user and frees dynamic memory
*   
*   Function Name : free_names
*
*   Parameters 	  : char **names -  String containing names for freeing
*   
*   Return	      : NONE
*/

void free_names( char **names )
{
	int str_num = 0;

	for( str_num = 0; *( names + str_num ) != NULL; str_num++ )
	{
		if ( ( names + str_num ) != NULL )
		{
			free( *(names + str_num) );
			*( names + str_num ) = NULL;
		}
	}

	return;
}



/* Function receives string from user and prints it
*   
*   Function Name : display_names
*
*   Parameters    : char **names	 - String to print 
*   
*   Return        : NONE
*/	

void display_names( char **names )
{
	int str_num = 0;

	printf("\nNames after sorting :\n\n");

	while ( *( names + str_num ) != NULL )				
	{
		printf("%s\n", *( names + str_num ) );
		str_num++;
	}
	
	return;
}




/* Function receives strings from user and sorts it in alphabetical order
*   
*   Function Name : sort_names
*
*   Parameters    : char **names	 - String to sort 
*   
*   Return        : PASS or FAIL
*/

int sort_names( char **names )
{
	int str_num = 0;			//String number
	char *temp_str = NULL;		//Temp variable used for swapping
	int str_count = 0;			//used to store number of strings 
	
	str_count = string_count( names );

	while ( NOT_ZERO( str_count ) )
	{
		for ( str_num = 0; str_num < str_count ; str_num++ )
		{	
			if ( * ( names + str_num + 1 ) != NULL )		//Checking done for last name 
			{
				if ( string_compare( * (names + str_num) , *(names + str_num + 1) ) == STRING_1 )
				{
					//swapping the strings
					temp_str = *(names + str_num); 
					*(names + str_num) = *(names + str_num + 1);
					*(names + str_num + 1) = temp_str;				
				}
			}
		}

		str_count--;	//Every time an iteration is done, the greatest string goes to the last 
	}					//position of names. So we dont need to check that for future iterations

	display_names( names );									//Display names after sorting		
	return PASS;
}




/* Function receives two strings from user and returns the string that needs to be swapped
*   
*   Function Name : string_compare
*
*   Parameters    : char *str1	 - 	String 1
*					char *str2	 - 	String 2	 
*   
*   Return        : STRING_EQUAL, STRING_1 ( string 1 is greater ), STRING_2 ( string 2 is greater )
*/


int string_compare( char *str1, char *str2 )
{
	int pos = 0;				//Temporary iteration variable
	int flag = STRING_UNDEFINED;	//used to return result of comparison

	int str_size, str1_size, str2_size;		//Used to store string sizes

	str1_size = char_count( str1 );
	str2_size = char_count( str2 );

	if ( str2_size > str1_size )
	{
		str_size = str2_size;
	}
	
	else
	{
		str_size = str1_size;
	}

	for ( pos = 0; pos < str_size ; pos++ )
	{
		if ( ( IS_UPPER( *(str1 + pos) ) && IS_UPPER( *(str2 + pos) ) ) ||
			 ( IS_LOWER( *(str1 + pos) ) && IS_LOWER( *(str2 + pos) ) ) )
		{
				
			if ( *(str1 + pos) > *(str2 + pos) )
			{
				//String 1 is greater than string 2 (alphabetically)
				return STRING_1;
			}

			else if ( *(str1 + pos) == *(str2 + pos) )
			{
				//this character of string 1 is equal to that of string 2
				flag = STRING_EQUAL;
			}

			else
			{
				//String 2 is greater than string 1 (alphabetically)
				return STRING_2;
			}
		}

		else if ( IS_UPPER( *(str1 + pos) ) && IS_LOWER( *(str2 + pos) ) )
		{
				
			if ( *(str1 + pos) > TO_UPPER( *(str2 + pos) ) )
			{
				//String 1 is greater than string 2 (alphabetically)
				return STRING_1;
			}

			else if ( *(str1 + pos) == TO_UPPER( *(str2 + pos) ) )
			{
				//this character of string 1 is equal to that of string 2
				flag = STRING_EQUAL;
			}

			else
			{
				//String 2 is greater than string 1 (alphabetically)
				return STRING_2;
			}
		}

		else if ( IS_LOWER( *(str1 + pos) ) && IS_UPPER( *(str2 + pos) ) )
		{
				
			if ( *(str1 + pos) > TO_LOWER( *(str2 + pos) ) )
			{
				//String 1 is greater than string 2 (alphabetically)
				return STRING_1;
			}

			else if ( *(str1 + pos) == TO_LOWER( *(str2 + pos) ) )
			{
				//this character of string 1 is equal to that of string 2
				flag = STRING_EQUAL;
			}

			else
			{
				//String 2 is greater than string 1 (alphabetically)
				return STRING_2;
			}
		}
		else			//For other characters
		{
			if ( *(str1 + pos) > *(str2 + pos) )
			{
				//String 1 is greater than string 2 (alphabetically)
				return STRING_1;
			}

			else if ( *(str1 + pos) == *(str2 + pos) )
			{
				//this character of string 1 is equal to that of string 2
				flag = STRING_EQUAL;
			}

			else
			{
				//String 2 is greater than string 1 (alphabetically)
				return STRING_2;
			}		
		}
	}
	if ( flag == STRING_EQUAL )
	{
		return STRING_EQUAL;
	}

	return STRING_COMPARE_FAIL;
}





/******************************************************************************************************************************************************/






