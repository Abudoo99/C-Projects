#include "validate.h"

int int_input_validate( int *num )
{
	int valid_check = VALID;		//Used to check if scanf is successful
	char dummy; 					//Used for receiving characters from stdin
	int dummy_count = 0;			//Used to count dummy characters in stdin stream

	valid_check = scanf("%d", num);
	
	if ( INPUT_FAILURE( valid_check, ONE_ARGUMENT ) )		//Checking if scanf is successful
	{
		printf("Enter valid arguments\n");
		return FAIL;
	}		
	
	if ( INPUT_SUCCESS( valid_check, ONE_ARGUMENT ) )		//Checking if any characters are present in stdin stream
	{
		while(scanf("%c", &dummy))
		{
			if ( IS_NEWLINE( dummy ) )						//If user has pressed '\n', we have to come out of loop
			{
				break;										
			}
			if ( NOT_WHITESPACE( dummy ) )					//whitespace is not invalid while taking input. 							
			{
				dummy_count++;								//Denotes that an extra character is present in stdin 
			}			
		}	
				
		if ( NOT_ZERO( dummy_count ) ) 							//If there are characters in stdin, return FAIL
		{
			fflush(stdin);									//Clearing stdin stream
			printf("Enter valid arguments\n");
			return FAIL;
		}			
	}

	if( INT_NEGATIVE( *num ))								//Checking if number is negative
	{
		printf("Number entered is negative\n");
		return FAIL;
	}

	if( IS_ZERO( *num ))									//Checking if number is zero
	{
		printf("Enter non-zero values\n");
		return FAIL;
	}
	return PASS;
}


int int_input_validate_two( int *num1, int *num2 )
{
	int valid_check = VALID;		//Used to check if scanf is successful
	char dummy; 					//Used for receiving characters from stdin
	int dummy_count = 0;			//Used to count dummy characters in stdin stream

	valid_check = scanf("%d %d", num1, num2);
	
	if ( INPUT_FAILURE( valid_check, TWO_ARGUMENTS ) )		//Checking if scanf is successful
	{
		printf("Enter valid arguments\n");
		return FAIL;
	}		
	
	if ( INPUT_SUCCESS( valid_check, TWO_ARGUMENTS ) )		//Checking if any characters are present in stdin stream
	{
		while ( scanf("%c", &dummy) )
		{
			if ( IS_NEWLINE( dummy ) )						//If user has pressed '\n', we have to come out of loop
			{
				break;										
			}
			if ( NOT_WHITESPACE( dummy ) )								//whitespace is not invalid while taking input. 							
			{
				dummy_count++;								//Denotes that an extra character is present in stdin 
			}			
		}	
				
		if ( NOT_ZERO( dummy_count ) ) 							//If there are characters in stdin, return FAIL
		{
			fflush(stdin);									//Clearing stdin stream
			printf("Enter valid arguments\n");
			return FAIL;
		}
	}

	/*if( INT_NEGATIVE( num1 ))								//Checking if number is negative
	{
		printf("Number entered is negative\n");
		return FAIL;
	}

	if( IS_ZERO( *num ))									//Checking if number is zero

	{
		printf("Enter non-zero values\n");
		return FAIL;
	}*/
	return PASS;
}



