/*******************************************************************************************************************************************************
*   TASK :
*
* 	1. Compare contents of two files and print same if they are same.
*	2. If they dont match, print the number of words that do not match
*
*
*	Date : 	18/10/2021	10:00:00 AM
*	
*********************************************************************HEADER FILES**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/******************************************************************MACRO DEFINITIONS*******************************************************************/

#define PASS				0
#define FAIL				1
#define NULL_CHAR			'\0'
#define NEWLINE				'\n'
#define WHITESPACE			' '

#define WORDS_SIZE			20
#define POS_SIZE			100

#define DISPLAY_ALL			0
#define DISPLAY_MELD		1

#define END_OF_BUFFER		5
#define END_OF_WORD			6

#define WORD_EQUAL			2
#define WORD_NOT_EQUAL		3
#define UNASSIGNED			4

//Debug macros
#define POS_BUF_PRINT		0
#define FILE_GETC			0
#define FILE_FREAD			1

/*************************************************************STRUCTURE DEFINITIONS*******************************************************************/

typedef struct 
{
	int eq_size, ne_size; 	//For mismatched buffer
	int *mismatch;	//Used to hold positions of unmatched words
	int *match;	//Used to check whether word is unmatched or not
}POSITION;

/*************************************************************FUNCTION PROTOTYPES*********************************************************************/

int check_buffer( char*, POSITION*, char*, POSITION* );	

int get_file( FILE*, char*, int );
int get_word( char* , char**, int*, int* );

int resize( int** , int );
int char_count( char* );
int word_compare( char*, char* );

void display_words_int( int*, int );
void display_meld( char*, int*, int, int );

/*****************************************************************MAIN FUNCTION************************************************************************/

int main()
{
	clock_t t;
	t = clock();

	FILE *fp1, *fp2;										//File pointers of files
	POSITION f1 = {0,0, NULL, NULL}, f2 = { 0,0, NULL, NULL};	//Contains match and mismatch buffers
	long int buffer1_size = 0, buffer2_size = 0;			//Stores buffer size
	int flag = 0;											//Exit status flag
	char *buffer1 = NULL, *buffer2 = NULL;					//Buffer used to store files

	//Opening files

	fp1 = fopen("File1.txt", "r+");		
	if ( fp1 == NULL )
	{
		printf("\nFILE 1 DOES NOT EXIST\n\n");
		return EXIT_FAILURE;
	}
	fp2 = fopen("File2.txt", "r+");
	if ( fp2 == NULL )
	{
		printf("\nFILE 2 DOES NOT EXIST\n\n");
		return EXIT_FAILURE;
	}

	//Finding size of files

	fseek( fp1, 0, SEEK_END );
	buffer1_size = ftell( fp1 );
	fseek( fp2, 0, SEEK_END );
	buffer2_size = ftell( fp2 );

	if ( (buffer1_size == 0) && (buffer2_size == 0) )
	{
		printf("Both files are empty. Enter some file content\n");
		fclose(fp1);
		fclose(fp2);
		return EXIT_SUCCESS;
	}

	//Bringing file pointer to SOF

	fseek( fp1, 0, SEEK_SET );
	fseek( fp2, 0, SEEK_SET );

	//Allocating memory dynamically and checking if it was allocated properly
	
	buffer1 = (char *)malloc( buffer1_size * sizeof(char) );
	if ( buffer1 == NULL )
	{
		printf("Could not allocate memory\n");
		return EXIT_FAILURE;
	}

	buffer2 = (char *)malloc( buffer2_size * sizeof(char) );
	if ( buffer2 == NULL )
	{
		printf("Could not allocate memory\n");
		return EXIT_FAILURE;
	}

	f1.match = (int *)malloc( POS_SIZE * sizeof(int) );
	if ( f1.match == NULL )
	{
		printf("Could not allocate memory\n");
		return EXIT_FAILURE;	
	}

	f2.match = (int *)malloc( POS_SIZE * sizeof(int) );
	if ( f2.match == NULL )
	{
		printf("Could not allocate memory\n");
		return EXIT_FAILURE;	
	}

	f1.mismatch = (int *)malloc( POS_SIZE * sizeof(int) );
	if ( f1.mismatch == NULL )
	{
		printf("Could not allocate memory\n");
		return EXIT_FAILURE;	
	}

	f2.mismatch = (int *)malloc( POS_SIZE * sizeof(int) );
	if ( f2.mismatch == NULL )
	{
		printf("Could not allocate memory\n");
		return EXIT_FAILURE;	
	}

	//Getting file contents into buffer

	if ( get_file(fp1, buffer1, buffer1_size) == FAIL )
	{
		return EXIT_FAILURE;
	}
	if ( get_file(fp2, buffer2, buffer2_size) == FAIL )
	{
		return EXIT_FAILURE;	
	}

	//Checking unequal positions in both buffers

	if ( check_buffer( buffer1, &f1, buffer2, &f2 ) == PASS )
	{	
		//Displaying file contents		
		
		printf("\033[3;1;4;31m");
		printf("\nFILE 1 CONTENTS:\n\n");
		printf("\033[0m");

		if ( f1.ne_size == 0 )
		{
			display_meld( buffer1, f1.mismatch, buffer1_size, DISPLAY_ALL );
		}
		else
		{
			display_meld( buffer1, f1.mismatch, buffer1_size, DISPLAY_MELD );
		}
	
		printf("\033[3;1;4;32m");
		printf("\nFILE 2 CONTENTS:\n\n");
		printf("\033[0m");

		if ( f2.ne_size == 0 )
		{
			display_meld( buffer2, f2.mismatch, buffer2_size, DISPLAY_ALL );
		}
		else
		{
			display_meld( buffer2, f2.mismatch, buffer2_size, DISPLAY_MELD );
		}

		printf("\n\nFILE OPERATIONS SUCCESSFUL\n\n");
		flag = EXIT_SUCCESS;
	}

	else
	{		
		printf("\n\nFILE OPERATIONS FAILED\n\n");
		flag = EXIT_FAILURE;		
	}

	//Closing files after using
	fclose(fp1);
	fclose(fp2);

	//Freeing heap memory after using it

	if ( f1.match != NULL )
	{
		free( f1.match );
		f1.match = NULL;
	}

	if ( f2.match != NULL )
	{
		free( f2.match );
		f2.match = NULL;
	}

	if ( f1.mismatch != NULL )
	{
		free( f1.mismatch );
		f1.mismatch = NULL;
	}

	if ( f2.mismatch != NULL )
	{
		free( f2.mismatch );
		f2.mismatch = NULL;
	}

	if ( buffer1 != NULL )
	{
		free( buffer1 );
		buffer1 = NULL;
	}

	if ( buffer2 != NULL )
	{
		free( buffer2 );
		buffer2 = NULL;
	}


	//Execution time calculation

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

	printf("\n\nExecition time : %f secs\n\n", time_taken);

	return flag;
}

/***************************************************************FUNCTION DEFINITIONS*******************************************************************/

/* Function receives buffer and stores unequal word positions
*   
*   Function Name : check_buffer
*
*   Parameters : char *buffer1	-	buffer containing file 1 contents
*				 POSITION *f1	-	file 1 position object				 
*				 char *buffer2	-	buffer containing file 2 contents
*				 POSITION *f2	-	file 2 position object
*
*   Return     : PASS or FAIL
*/

int check_buffer( char *buffer1, POSITION *f1, char *buffer2, POSITION *f2 )
{
	int w_count1 = 0, w_count2 = 0;		//Number of words in files
	int itr1 = 0, itr2 = 0, w_pos1 = 0, w_pos2 = 0;
	int word_file1 = 0, word_file2 = 0, wsize1 = 0, wsize2 = 0;
	char *words1 = NULL, *words2 = NULL;

	int temp_size = POS_SIZE;
 
	//Allocating memory dynamically and checking if it was allocated properly

	words1 = (char *)malloc( WORDS_SIZE * sizeof(char) );
	if ( words1 == NULL )
	{
		printf("Could not allocate memory\n");
		return FAIL;
	}

	words2 = (char *)malloc( WORDS_SIZE * sizeof(char) );
	if ( words2 == NULL )
	{
		printf("Could not allocate memory\n");
		return FAIL;
	}

	//Initial number of words in position buffers

	f1->eq_size = POS_SIZE;
	f2->eq_size = POS_SIZE;

	//Finding number of words in file 2

	for ( itr2 = 0; word_file2 != EOF; itr2++ )
	{
		word_file2 = get_word( buffer2, &words2, &w_pos2, &wsize2);
		w_count2++;
	
		if ( w_count2 > f2->eq_size )
		{
			f2->match = realloc( f2->match, (f2->eq_size + 10) * sizeof(int) );
			if ( f2->match == NULL )
			{
				printf("Could not re-allocate memory\n");
				return FAIL;
			}		

			f2->mismatch = realloc( f2->mismatch, ( f2->eq_size + 10 ) * sizeof(int) );
			if ( f2->mismatch == NULL )
				{	
				printf("Could not re-allocate memory\n");
				return FAIL;
			}

			f2->eq_size = f2->eq_size + 10;	
		}
	}

	f2->eq_size = w_count2; 

	f2->match = realloc( f2->match, (f2->eq_size) * sizeof(int) );
	if ( f2->match == NULL )
	{
		printf("Could not re-allocate memory\n");
		return FAIL;
	}

	f2->mismatch = realloc( f2->mismatch, ( f2->eq_size ) * sizeof(int) );
	if ( f2->mismatch == NULL )
	{	
		printf("Could not re-allocate memory\n");
		return FAIL;
	}

	w_pos2 = 0;

	//Saving positions of unmatched words

	for ( itr1 = 0; word_file1 != EOF; itr1++ )
	{
		word_file1 = get_word( buffer1, &words1, &w_pos1, &wsize1);
		w_count1++;

		if ( w_count1 > f1->eq_size )
		{
			f1->match = realloc( f1->match, (f1->eq_size + 10) * sizeof(int) );
			if ( f1->match == NULL )
			{
				printf("Could not re-allocate memory\n");
				return FAIL;
			}	

			f1->eq_size = f1->eq_size + 10;
		}

		//printf("Buf1 : %s\n", words1);

		w_pos2 = 0;		
		word_file2 = get_word( buffer2, &words2, &w_pos2, &wsize2);

		for ( itr2 = 0; word_file2 != EOF; itr2++ )
		{
			if ( *( f2->match + itr2 ) != WORD_EQUAL )
			{
				//printf("Buf2 : %s\n", words2);
		
				if ( word_compare( words1, words2 ) == WORD_EQUAL )
				{
					*( f1->match + itr1 ) = WORD_EQUAL;	
					*( f2->match + itr2 ) = WORD_EQUAL;
					*( f2->mismatch + itr2 ) = 0;
					break;
				}								
				else if ( word_compare( words1, words2 ) == WORD_NOT_EQUAL )
				{
					if ( *( f2->match + itr2 ) != WORD_EQUAL )  
					{
						*( f2->mismatch + itr2 ) = w_pos2 - wsize2  ;						
						*( f2->match + itr2 ) = 0;
					}
				}
			}
			word_file2 = get_word( buffer2, &words2, &w_pos2, &wsize2);
		} 
	
		if ( *( f1->match + itr1 ) != WORD_EQUAL )
		{
			*( f1->match + itr1 ) = 0;
			*( f1->mismatch + f1->ne_size++ ) = w_pos1 - wsize1 ;

			if ( f1->ne_size == temp_size )
			{
				f1->mismatch = realloc( f1->mismatch, ( temp_size + 10 ) * sizeof(int) );
				if ( f1->mismatch == NULL )
				{	
					printf("Could not re-allocate memory\n");
					return FAIL;
				}
					
				temp_size = temp_size + 10;
			}			
		}
	}

	f1->eq_size = w_count1;

	f1->match = realloc( f1->match, (f1->eq_size) * sizeof(int) );
	if ( f1->match == NULL )
	{
		printf("Could not re-allocate memory\n");
		return FAIL;
	}	

	if ( f1->ne_size != 0 )
	{
		f1->mismatch = realloc( f1->mismatch, (f1->ne_size) * sizeof(int) );
		if ( f1->mismatch == NULL )
		{
			printf("Could not re-allocate memory\n");
			return FAIL;
		}		
	}

	//Resizing mismatch buffer of file 2 
	f2->ne_size = resize( &(f2->mismatch), f2->eq_size );


#if POS_BUF_PRINT

	printf("\nFile 1 equal:\n");
	display_words_int( f1->match, w_count1);

	printf("\nFile 1 unequal:\n");
	display_words_int( f1->mismatch, f1->ne_size );

	printf("\nFile 2 equal:\n");
	display_words_int( f2->match, w_count2 );

	printf("\nFile 2 unequal:\n");
	display_words_int( f2->mismatch, f2->ne_size );
	
#endif


	//Freeing heap memory after using it

	if ( words1 != NULL )
	{
		free( words1 );
		words1 = NULL;
	}

	if ( words2 != NULL )
	{
		free( words2 );
		words2 = NULL;
	}

	return PASS;
}



/* Function receives a word from given file and stores it in the given string
*   
*   Function Name : get_word
*
*   Parameters : char *buffer	-	buffer where word is present
*   			 char **word	-	string in which word is stored
*				 int *pos		-	position of word to be searched
*				 int *wsize		-	word size 
*
*   Return     : PASS or EOF
*/

int get_word( char *buffer , char **word, int *pos, int *wsize )
{
	int char_num = 0, count = 0, w_size, flag = 0;
	char ch;

	w_size = WORDS_SIZE;

	*wsize = 0;

	while (1)
	{
		count++;		//Counting word size

		ch = *( buffer + *pos );
	 	(*pos)++;
		
		if ( ch == NULL_CHAR )
		{
			flag = END_OF_BUFFER;
			break;
		}
		if ( ( ch == WHITESPACE ) || ( ch == NEWLINE ) )
		{
			flag = END_OF_WORD;
			break;
		}
		(*wsize)++;

		if ( count > w_size )
		{
			*word = realloc( *word, ( w_size + 10 ) * sizeof(char) );

			if ( *word == NULL )
			{
				printf("Could not re-allocate memory\n");
				return FAIL;
			}
		
			w_size = w_size + 10;
		}

		*( *(word) + char_num ) = ch;
		char_num++; 
	}

	*( *(word) + char_num ) = NULL_CHAR;

	if ( flag == END_OF_BUFFER )
	{
		return EOF;
	}

	if ( flag == END_OF_WORD )
	{
		return PASS;
	}

	return FAIL;
}




/* Function stores file contents into given buffer
*   
*   Function Name : get_file
*
*   Parameters : FILE *fp		-	File pointer of file
*   			 char *buffer 	-	string in which file is stored
*				 int buf_size	-	Initial size of buffer
*
*   Return     : PASS or FAIL
*/

int get_file( FILE *fp, char *buffer, int buf_size )
{

#if FILE_FREAD

	int valid_check = 0;

	valid_check = fread( buffer, sizeof(char), buf_size, fp );

	if ( valid_check == EOF )
	{
		printf("File read failed\n");
		return FAIL;
	}

#endif

#if FILE_FGETC

	int char_num = 0; 
	char ch;

	while(1)
	{
		ch = fgetc( fp );

		if ( ch == EOF )
		{
			*( buffer + char_num ) = NULL_CHAR;
			//printf("EOF detected\n");
			break;
		}

		*( buffer + char_num ) = ch;
		char_num++; 
	}

#endif
	
	return PASS;
}





/* Function receives two strings from user and checks if are equal
*   
*   Function Name : word_compare
*
*   Parameters : char *word1	-	String 1
*				 char *word2	-	String 2
*
*   Return     : WORD_EQUAL or WORD_NOT_EQUAL
*/

int word_compare( char *word1, char *word2 )
{
	int char_num = 0, size1 = 0, size2 = 0, size = 0;

	size1 = char_count( word1 );
	size2 = char_count( word2 );

	if ( size1 > size2 )
	{
		size = size1;
	}
	else 
	{
		size = size2;
	}

	for( char_num = 0; char_num < size; char_num++ )
	{
		if ( *( word1 + char_num ) != *( word2 + char_num ) )
		{
			return WORD_NOT_EQUAL;
		}
	}
	return WORD_EQUAL;
}




/* Function displays contents of buffer similar to meld
*   
*   Function Name : display_meld
*
*   Parameters : char *buffer	-	string to be displayed
*				 int *pos_str	- 	position to be marked
*				 int size		- 	size of string
*				 int disp_type	-	DISPLAY ALL or DISPLAY WITH MISMATCH HIGHLIGHTS
*
*   Return     : NONE
*/

void display_meld( char *buffer, int *pos_str, int size, int disp_type )
{
	int char_num = 0, pos = 0;

	if ( disp_type == DISPLAY_ALL )
	{
		for( char_num = 0; char_num < size ; char_num++ )
		{
			printf("%c", *(buffer + char_num) );
		}
	}

	else
	{
		for( char_num = 0; char_num < size ; char_num++ )
		{
			if ( char_num == ( *( pos_str + pos ) - 1 ) )
			{
				while (1) 
				{
					if ( ( *( buffer + char_num ) == WHITESPACE ) 
					|| ( *( buffer + char_num ) == NEWLINE ) ) 
					{
						printf("%c", *(buffer + char_num) );
						pos++;
						break;
					}

					printf("\033[7;34m");
					printf("%c", *(buffer + char_num) );		
					printf("\033[0m");		
					char_num++;
				}
			}			
			else
			{
				printf("%c", *(buffer + char_num) );
			}
		}
	}

	return;
}





/* Function resizes integer array removing all zeroes
*   
*   Function Name : resize
*
*   Parameters : int **buffer	-	array to be displayed
*				 int size		- 	number of elements in array
*
*   Return     : size of modified buffer
*/

int resize( int **buffer, int size )
{
	int int_num, count = 0;
	int flag = 0;

	for ( int_num = 0; int_num < size ; int_num++ )
	{
		if ( *( *(buffer) + int_num ) != 0 )
		{
			flag = 1;
			*( *(buffer) + count++ ) = *( *(buffer) + int_num );
		}
	}

	if ( flag == 0 )
	{
		count = 0;
	}

	return count;
}





/* Function returns size of given string 
*   
*   Function Name : char_count
*
*   Parameters : char *word		-	String whose size is to be calculated
*
*   Return     : size of string
*/

int char_count( char *word )
{
	int char_num = 0, size = 0;

	for( char_num = 0; *( word + char_num ) != NULL_CHAR; char_num++ )
	{
		size++;
	}
	return size;
}




#if POS_BUF_PRINT 

/* Function displays contents of buffer
*   
*   Function Name : display_words_int
*
*   Parameters : int *buffer	-	array to be displayed
*				 int size		- 	number of elements in array
*
*   Return     : NONE
*/

void display_words_int( int *buffer, int size )
{
	int char_num = 0;

	for( char_num = 0; char_num < size ; char_num++ )
	{
		printf("%d ", *(buffer + char_num) );
	}
	return;
}

#endif

/******************************************************************************************************************************************************/
