/***************************************************************************************************************************
*   TASK :
*
* 	1. Get an input string from user dynamically.
*	2. Find a given word in that string.  
*	3. Give user the option to replace / replace all 
*	
*	Perform input validation
*
*	Date : 13/10/2021
*
***********************************************************HEADER FILES*****************************************************/

#include<stdio.h>
#include<stdlib.h>

#include "validate.h"

/*********************************************************MACRO DEFINITIONS*************************************************/

#define ONCE							1
#define NUMBER_OF_RETRIES				3

#define WORD_OK							0
#define WORD_NOT_OK						1

#define FIND_RETRY						0

#define REPLACE_ONCE					1
#define REPLACE_ALL						2
#define REPLACE_POS						3
#define REPLACE_MULTIPLE_POS			4

#define WORD_SIZE						50
#define STRING_SIZE						100
#define POS_SIZE						100


/*******************************************************FUNCTION PROTOTYPES*************************************************/

void display_string( char* );
int string_count( char* );
int string_count_num( int* );
int string_compare( char* , char*, int** );
int word_compare( char*, char*, int );
int input_string( char **, int );
void move_string( char*, char*, char*, int );
int get_find_status( char*, char*, int** );
int find_and_replace( char*, char*, int*, int );
int replace_word( char*, char*, int*, int );

/*********************************************************MAIN FUNCTION****************************************************/

int main()
{
	char *str = NULL, *word = NULL; 
	int *pos_str = NULL;	
	int str_size = 0, word_count = 0;		

	word = (char *)malloc( WORD_SIZE * sizeof(char) );	//Dynamically allocating memory for receiving a word
	if ( word == NULL )									
	{
		printf("\nCould not allocate memory\n");		//checking if memory was allocated successfully
		return EXIT_FAILURE;
	}			

	str = (char *)malloc( STRING_SIZE * sizeof(char) );	//Dynamically allocating memory for receiving a string 
	if ( str == NULL )									
	{
		printf("\nCould not allocate memory\n");		//checking if memory was allocated successfully
		return EXIT_FAILURE;
	}

	pos_str = (int *)malloc( POS_SIZE * sizeof(int) );	//Dynamically allocating memory for receiving position of word 
	if ( pos_str == NULL )									
	{
		printf("\nCould not allocate memory\n");		//checking if memory was allocated successfully
		return EXIT_FAILURE;
	}

	printf("\nEnter string for performing find and replace operations :\n\n");

	str_size = STRING_SIZE * sizeof(char);				//Initial size of string 

 	if ( input_string( &str, str_size ) == PASS )			
	{
		if ( *(str) == NULL_CHAR )			//If user did not enter any input
		{
			printf("\nSTRING EMPTY\n");
			return EXIT_FAILURE;
		}
	
		word_count = get_find_status( word, str, &pos_str );

		if ( word_count != FAIL )					//If word found, then only replace			
		{
			//If find and replace was successful, function returns PASS
			if ( find_and_replace( word, str, pos_str, word_count ) == PASS )			
			{		 
				printf("\nFind and replace operations performed successfully\n\n");
			}
			else
			{
				printf("\nFind and replace operations failed\n\n");
				return EXIT_FAILURE;
			}
		}
	}
	//Freeing heap memory after using it
	if( word != NULL )
	{
		free(word);	
		word = NULL;	
	}
	if( pos_str != NULL )
	{
		free(pos_str);	
		pos_str = NULL;	
	}

	return EXIT_SUCCESS;
}

/***********************************************************FUNCTION PROTOTYPES***********************************************************/  

/* Function receives a string from user  
*   
*   Function Name : input_string
*
*   Parameters : char **str		-	String to receive 
*				 int str_size	- 	Size allocated dynamically for string
*
*   Return     : PASS or FAIL
*/

int input_string( char **str, int str_size )
{
	int curr_size = 0, end_check = 0;

	while (1)
	{
		end_check = scanf( "%c", ( *(str) + curr_size) );

		if ( end_check == EOF )
		{
			break;
		}

		curr_size++;
		
		if ( curr_size > str_size )
		{
			*str = realloc( *str, ( str_size + 10 ) * sizeof(char) );

			if ( str == NULL )
			{
				printf("Could not reallocate memory\n");
				return FAIL;
			}
				
			str_size = str_size + 10 ;
		}

	}
	
	*( *(str) + curr_size ) = NULL_CHAR;

	*str = realloc( *str, ( string_count( *str ) + 1 ) * sizeof(char) );

	if ( *str == NULL )
	{
		printf("Could not reallocate memory\n");
		return FAIL;
	}

	return PASS;
}



/* Function receives string from user and prints it
*   
*   Function Name : display_string
*
*   Parameters : char *str	 - String to print 
*   
*   Return     : NONE
*/	

void display_string( char *str )
{
	printf("%s\n", str);
	return;
}




/* Function receives a string and returns its length 
*   
*   Function Name : string_count
*
*   Parameters : char *str	-	string whose length we must find
*   
*   Return     : string size
*/

int string_count(char *str)
{
  int size = 0;

  while ( *(str + size) != NULL_CHAR )
  {
    size++;
  }
 
  return size;
}




/* Function receives a string and returns its length 
*   
*   Function Name : string_count_num
*
*   Parameters : int *str	-	string whose length we must find
*   
*   Return     : string size
*/

int string_count_num(int *str)
{
  int size = 0;

  while ( *(str + size) != NULL_CHAR )
  {
    size++;
  }
 
  return size;
}




/* Function receives a string and a substring and returns number of occurences of substring in string 
*   
*   Function Name : string_compare
*
*   Parameters : char *word		-	Word to find
*                char *str		-	String to find the word 
*				 int **pos_str 	-	string containing position of found words	
*   
*   Return     : number of occurences of substring or FAIL
*/

int string_compare(char *word, char *str, int **pos_str)
{
	int str_num = 0;						//Temporary iteration variables 
	int count_w = 0;						//Used to find number of occurences of word
	int flag = WORD_OK;						// Flag variable for checking find status
	int pos_size = POS_SIZE;					//Allocated number of found words

	for (str_num = 0; *(str + str_num) != NULL_CHAR; str_num++)
	{
		//Checking if any word in string matches first letter of our word
		if ( *word == *(str + str_num) )		 
		{  			
			flag = word_compare( word, str, str_num );
			
			if ( flag == WORD_OK )					//Word is present in string 
			{
				*( *(pos_str) + count_w ) = str_num;	//Storing position of found word
				count_w++;							//To find number of occurences
			
				if ( count_w > pos_size )
				{
					*pos_str = realloc( *pos_str, ( pos_size + 20 ) * sizeof(int) );

					if ( *pos_str == NULL )
					{
						printf("Could not reallocate memory\n");
						return FAIL;
					}

					pos_size = pos_size + 20;
				}
			}		
		}
		
		flag = FIND_RETRY;		//If word is not found in one iteration, we retry until end of string
	}
	
	*( *(pos_str) + count_w ) = NULL_CHAR;

	*pos_str = realloc( *pos_str, ( string_count_num( *pos_str ) + 1) * sizeof(int) );

	if ( *pos_str == NULL )
	{
		printf("Could not reallocate memory\n");
		return FAIL;
	}

	if ( count_w == ONCE )
	{
		return ONCE;
	}
	else if ( count_w > ONCE )
	{
		return count_w;
	}

	return FAIL;				//If end of loop occurs and word not found in loop, function returns FAIL
}




/* Function receives a word and a string returns PASS if they match 
*   
*   Function Name : word_compare
*
*   Parameters : char *word		-	Word to find
*                char *str		-	String to find the word 
*				 int pos		- 	Position from which string compare must take place
*   
*   Return     : PASS or FAIL
*/

int word_compare( char *word, char *str, int pos )
{
	int check = 0;				//Temporary iteration variable

	for (check = 0; *(word + check) != NULL_CHAR; check++)
	{
		if (*(word + check) != *(str + pos + check))		//Checking if each character of our word is present in string
		{
			return WORD_NOT_OK;
		}	
	}
	return WORD_OK;
}





/* Function receives word from user and checks if it is present in string. 
*   
*   Function Name : get_find_status
*
*   Parameters : char *str		- 	Input string 
*				 char *word 	- 	Word to find in string
*				 int **pos_str 	-	string containing position of found words		
*   
*   Return     : returns word count or FAIL
*/			

int get_find_status( char *word, char *str, int **pos_str)
{
	int word_count = 0, word_size;

	word_size = WORD_SIZE * sizeof(char); 
	
	printf("Enter word to search : ");					//Receiving word from user

	if ( input_string( &word, word_size ) == PASS )
	{ 
		if ( *(word) == NULL_CHAR )
		{
			printf("\nWORD EMPTY\n");
			return FAIL;
		}		

		word_count = string_compare( word, str, pos_str );

		if ( word_count == FAIL )			//Checking if word is present in string
		{
			printf("\nCannot find word in string\n");
			return FAIL;
		}

		else
		{
			return word_count;
		}
		return PASS;
	}
	else
	{
		return FAIL;
	}	
}





/* Function receives word from user and performs replace operations
*   
*   Function Name : find_and_replace
*
*   Parameters : char *word	 	-	Word to find and replace
*				 char *str	 	- 	String to perform find and replace operation
*				 int *pos_str	-	string containing positions of found words
*				 int w_count 	-	number of occurences of find word 	
*   
*   Return     : returns PASS or FAIL
*/			

int find_and_replace( char *word, char *str, int *pos_str, int w_count )
{
	int opt;

	if ( w_count == ONCE )
	{
		if ( replace_word( word, str, pos_str, REPLACE_ONCE ) == PASS )
		{
			return PASS;
		}
		else
		{
			return FAIL;
		}
	}
	
	else
	{
			printf("\n\n\t\tNumber of occurences of word : %d\n", w_count );
			printf("\n\t\tChoose which operation you want to perform\n\
							1. Replace once\n\
							2. Replace all\n\
							3. Position wise replace\n\
							4. Range wise replace\n\
							Enter you choice : ");
			
			if ( int_input_validate( &opt ) == PASS )		//Getting choice from user and validating it
			{
				switch( opt )
				{
					case  REPLACE_ONCE 			:	if ( replace_word( word, str, pos_str, REPLACE_ONCE ) == PASS )
													{
														return PASS;
													}	
							    		 			break;
			
					case  REPLACE_ALL   		:	if ( replace_word( word, str, pos_str, REPLACE_ALL ) == PASS )
													{
														return PASS;
													}
						            				break;
				
					case  REPLACE_POS  			 :	if ( replace_word( word, str, pos_str, REPLACE_POS ) == PASS )
													{
														return PASS;
													}
						            				break;

					case  REPLACE_MULTIPLE_POS   : 	if ( replace_word( word, str, pos_str, REPLACE_MULTIPLE_POS ) == PASS )
													{
														return PASS;
													}
						            				break;
												
					default		  	  			 : 	printf("Enter valid choice\n");
		    	       								break;
				}
			}
	}

	return FAIL;
}





/* Function receives string and replace word and replaces word in string 
*   
*   Function Name : move_string
*
*   Parameters : char *str		-	String to replace the word 
*   			 char *word		-	Find word
*				 char *word_r	-	Replace word 
*				 int pos	 	-	position to replace at
*			   
*   Return     : NONE
*/

void move_string( char *str, char *word, char *word_r, int pos )
{
	int char_num = 0, word_num = 0;
	int str_size = 0, word_size = 0, rword_size = 0, new_size = 0, word_diff = 0;

	str_size = string_count( str );
	word_size = string_count( word );
	rword_size = string_count( word_r );

	word_diff = rword_size - word_size;
	
	if ( word_diff == 0 )
	{
		for ( char_num = pos; char_num < (pos + rword_size) ; char_num++ )
		{
			*(str + char_num) = *(word_r + word_num++);
		}	
	}

	else if ( word_diff > 0 )
	{
		new_size = str_size + word_diff;
		
		for ( char_num = new_size - 1; char_num >= (pos + word_diff); char_num-- )
		{
			*(str + char_num) = *(str + char_num - word_diff);
		}
		for ( char_num = pos; char_num < (pos + rword_size); char_num++ )
		{
			*(str + char_num) = *(word_r + word_num++);
		}

		*(str + new_size) = NULL_CHAR;		
	}

	else
	{
		new_size = str_size - (-1 * word_diff);

		for ( char_num = pos; char_num < (pos + rword_size) ; char_num++ )
		{
			*(str + char_num) = *(word_r + word_num++);
		}	
		for ( char_num = pos + rword_size ; *(str + char_num) != NULL_CHAR ; char_num++ )
		{
			*(str + char_num) = *(str + ( char_num + (-1 * word_diff) ) );
		}

		*(str + char_num) = NULL_CHAR;
	}

	//printf("String : %s\n", str); 
	
	return;
}





/* Function receives word and string and replaces word in string once
*   
*   Function Name : replace_word
*
*   Parameters : char *word		-	Word to replace 
*                char *str		-	String to replace the word 
*				 int *pos_str	- 	string containing position of words
*				 int rep_type 	-	Replace once or replace all
*			   
*   Return     : PASS or FAIL
*/	

int replace_word(char *word, char *str, int *pos_str, int rep_type)
{
 	int str_num = 0;					//Temporary iteration variable 				
	int count = 0;						//Number of found word positions
	int pos, pos_i, pos_f;				//Used to get position of word replace from user

 	char *word_r = NULL;				//Word to be replaced in the string

	int word_size =  WORD_SIZE * sizeof(char) ;

 	word_r = (char *)malloc( word_size ); 		 //Dynamically allocating memory for replace word

	if ( word_r == NULL )								 //checking if memory was allocated successfully
	{
		printf("\nCould not allocate memory\n");
		return FAIL;
	}

 	printf("\nEnter word to replace : ");				 //Getting replace word from user

	if ( input_string( &word_r, word_size ) == FAIL )
	{
		return FAIL;
	}

	if ( *(word_r) == NULL_CHAR )
	{
		printf("\nREPLACE WORD EMPTY\n");
		return FAIL;
	}

	count = string_count_num( pos_str );	

	for ( str_num = (count - 1); str_num >= 0; str_num-- )
	{	
		str = realloc( str, ( string_count( str ) + string_count( word_r ) ) * sizeof(char) );
	
		if ( str == NULL )		//checking if memory was re-allocated successfully
		{
			printf("\nCould not re-allocate memory\n");		
			return FAIL;
		}

		if ( rep_type == REPLACE_ONCE )
		{
			move_string( str, word, word_r, *(pos_str) );	 	//Replaces word once in string
			break; 
		}	

		if ( rep_type == REPLACE_POS )
		{
			printf("\nEnter which occurence of word to replace ( 0 to %d ):", count - 1);
			if ( int_input_validate( &pos ) == PASS )
			{
				if ( ( pos >= count ) || ( pos < 0 ) )
				{
					printf("\nEnter valid range\n");
					return FAIL;
				}
				move_string( str, word, word_r, *( pos_str + pos ) );	 	//Replaces word once in string
				break; 				
			}	
			else
			{
				return FAIL;
			}	
		}

		if ( rep_type == REPLACE_MULTIPLE_POS )
		{
			printf("\nEnter starting range of word to replace ( 0 to %d ):", count - 1);
			if ( int_input_validate( &pos_i ) == PASS )
			{
				if ( ( pos_i >= count ) || ( pos_i < 0 ) )
				{
					printf("\nEnter valid range\n");
					return FAIL;
				}
			
				printf("\nEnter ending range of word to replace ( %d to %d ):", pos_i, count - 1);
				
				if ( int_input_validate( &pos_f ) == PASS )
				{
					if ( ( pos_f < pos_i ) || ( pos_f < 0 ) || ( pos_f >= count ) )
					{
						printf("\nEnter valid range\n");
						return FAIL;
					}

					for ( str_num = pos_f; str_num >= pos_i; str_num-- )
					{
						str = realloc( str, ( string_count( str ) + string_count( word_r ) ) * sizeof(char) );
	
						if ( str == NULL )		//checking if memory was re-allocated successfully
						{	
							printf("\nCould not re-allocate memory\n");		
							return FAIL;
						}

						move_string( str, word, word_r, *( pos_str + str_num ) );	 	//Replaces word once in string
					}	
					break;
				}	
				else
				{
					return FAIL;
				}						
			}	
			else
			{
				return FAIL;
			}	
		}

		move_string( str, word, word_r, *( pos_str + str_num ) );	 	//Replaces word once in string			
	}

	str_num = string_count( str );

	*( str + str_num ) = NULL_CHAR;

	str = realloc( str, ( str_num + 1 ) * sizeof(char) );
	
	if ( str == NULL )		//checking if memory was re-allocated successfully
	{
		printf("\nCould not re-allocate memory\n");		
		return FAIL;
	}
	
	printf("\nString after replacing :\n\n");					//Display modified string
 	display_string( str );		


	//Freeing heap memory as we are not using it
	if( str != NULL )
	{
		free(str);
		str = NULL;
			
	}	
	if( word_r != NULL )
	{
		free(word_r);	
		word_r = NULL;
	}	

	return PASS;
}

/*****************************************************************************************************************************************************/	





