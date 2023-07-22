/*********************************************************************************************************
											 HEADER FILES										
*********************************************************************************************************/

#include "stud_functions.h"

/**********************************************************************************************************
								    	    FUNCTION DEFINITIONS
**********************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------
	Function prints the student database
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : display_student
*
*   Parameters : STUDENT *stud		-	structure containing student data
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if DISP_DEBUG

int display_student( STUDENT* stud )
{
	int s_num = 0;
	
	
	printf("\n\n*****************************************************************************************************************\
			\n\t\t\t\t\t\t    STUDENT DATABASE\
			\n*****************************************************************************************************************\n");
	printf("\nS/No           NAME\t\t\tAGE\t       R_NO\t      MARK1\t     MARK2\t\tMARK3\t\n");
	for( s_num = 0; (stud + s_num)->name != NULL ; s_num++ )
	{
		if ( (stud + s_num)->name[0] == NULL_CHAR )
		{
			break;
		} 
		printf("\n%-10d     %-20s     %-10d     %-10d     %-10d     %-10d 	%-10d", s_num+1,
			(stud + s_num)->name, (stud + s_num)->age, (stud + s_num)->r_no, 
			(stud + s_num)->marks[0], (stud + s_num)->marks[1], (stud + s_num)->marks[2]);	
	}
	printf("\n\n*****************************************************************************************************************\n");
	return PASS;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function adds a student data to the database
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : add_student
*
*   Parameters : STUDENT **stud		-	structure to store student data
*				 int *pos			- 	position of last object
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if ADD_DEBUG

int add_student( STUDENT **stud, int *pos )
{
	int count = 0, itr = 0, roll = -1;
	int s_num = *pos;	//Adding student to last position

	//Getting student details from user
	printf("\nADDING STUDENT DETAILS\n");
	printf("\nEnter number of students you want to add : ");
	
	if ( int_input_validate( &count ) == PASS ) 
	{
		if (IS_ZERO(count))
		{
			return PASS;
		}
		
		//Re-allocating if more students enter database
		if ( count > STUDENTS_COUNT )
		{
			*stud = realloc( *stud, ( count )* sizeof( STUDENT ) );
			if ( *stud == NULL )
			{
				printf("Could not re-allocate memory\n");
				return FAIL;
			}
			printf("Address after : %p\n", *stud);
		}
	
		while( itr < count )
		{
			//Allocating memory dynamically and checking if it was allocated properly

			(*(stud) + s_num)->name = (char*)malloc( NAME_SIZE * sizeof(char) );
			if ( (*(stud) + s_num)->name == NULL )
			{
				printf("Could not allocate memory\n");
				return FAIL;
			}

			(*(stud) + s_num)->marks = (int*)malloc( NUMBER_OF_MARKS * sizeof(int) );
			if ( (*(stud) + s_num)->marks == NULL )
			{
				printf("Could not allocate memory\n");
				return FAIL;
			}
	
			printf("\nEnter student %d name : ", itr+1);
			scanf("%[^\n]s", (*(stud) + s_num)->name );

				

			printf("\nEnter student %d age : ", itr+1);
			while( int_input_validate(&(*(stud) + s_num)->age) != PASS )
			{
				printf("\n\nEnter student %d age : ", itr+1);
			}		

			roll_num : printf("\nEnter student %d roll number : ", itr+1);
			while( int_input_validate(&roll) != PASS )
			{
				printf("\n\nEnter student %d roll number : ", itr+1);
			}
	
			if ( search_by_roll( *stud, roll ) != NOT_FOUND )
			{
				printf("Roll number already exists\n");
				goto roll_num;				
			}
			
			(*(stud) + s_num)->r_no = roll;

			printf("\nEnter student %d marks in three subjects ( out of 100 ) :\n", itr+1);

			subject1 : printf("\n Subject 1 : ");			
			while( int_input_validate(&(*(stud) + s_num)->marks[0]) != PASS )
			{
				printf("\n\n Subject 1 : ");
			}

			if ( INVALID_MARKS( (*(stud) + s_num)->marks[0], MAX_MARK ) )
			{
				printf("Invalid mark entry\n");
				goto subject1;
			}	

			subject2 : printf("\n Subject 2 : ");	
			while( int_input_validate(&(*(stud) + s_num)->marks[1]) != PASS )
			{
				printf("\n\n Subject 2 : ");
			}

			if ( INVALID_MARKS( (*(stud) + s_num)->marks[1], MAX_MARK ) )
			{
				printf("Invalid mark entry\n");
				goto subject2;
			}
			
			subject3 : printf("\n Subject 3 : ");	
			while( int_input_validate(&(*(stud) + s_num)->marks[2]) != PASS )
			{
				printf("\n\n Subject 3 : ");
			}

			if ( INVALID_MARKS( (*(stud) + s_num)->marks[2], MAX_MARK ) )
			{
				printf("Invalid mark entry\n");
				goto subject3;
			}
	
			itr++;
			s_num++;
		}

		printf("\n%d students data added to database\n", count);

		*pos = *pos + count; //Incrementing positions to point recently added object as last object
	}	
	return PASS;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function deletes a student data from database
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : del_student
*
*   Parameters : STUDENT **stud		-	structure containing student data
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if DEL_DEBUG

int del_student( STUDENT **stud )
{
	int s_num = 0, pos, roll = 0, flag = 0, size = 0;

	display_student( *stud );
	
	printf("\nEnter roll number of student to delete : ");
	
	if ( int_input_validate( &roll ) == PASS )
	{
		pos = search_by_roll( *stud, roll );
					
		if ( pos == NOT_FOUND )
		{
			flag = FAIL;
			printf("\nStudent not present in database\n");
		}
		else
		{
			for( s_num = pos ; (*(stud) + s_num)->name != NULL; s_num++ )
			{
				if ( (*(stud) + s_num + 1)->name != NULL ) //For last element
				{
					*( *(stud) + s_num ) = *( *(stud) + s_num + 1 );
				}
				else
				{
					break;
				}
			}
			
			size = student_count( *stud );

			*stud = realloc( *stud, size * sizeof( STUDENT ) );
			(*(stud) + s_num)->name = NULL;

			printf("Student deleted from database\n");
		}							   
	}

	if (flag == FAIL)
	{
		return FAIL;
	}

	return PASS;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function searches the database for given student and returns FAIL if not found
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : search_student
*
*   Parameters : STUDENT *stud		-	structure that contains student data
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if SEARCH_DEBUG

int search_student( STUDENT* stud )
{
	int *pos = NULL, option, s_roll, flag = 0, s_num;
	char *s_name = NULL;

	//Allocating memory dynamically and checking if it was properly allocated

	s_name = (char *)malloc( NAME_SIZE * sizeof(char) );
	if (s_name == NULL)
	{
		printf("Could not allocate memory\n");
		return FAIL;
	}

	pos = (int *)malloc( 100 * sizeof(int) );
	if (pos == NULL)
	{
		printf("Could not allocate memory\n");
		return FAIL;
	}

	while(1)
	{
		printf("\n\n\t\t\t1. Search student data by name\
		 	 \n\t\t\t2. Search student data by roll number\n\
		 	 \n\t\t\tENTER YOUR CHOICE : ");
	
		if ( int_input_validate( &option ) == FAIL )
		{											
			continue;
		}	

		if ( option == SEARCH_BY_NAME ) 
		{
			//Getting student name to search in database	
			printf("\nSTUDENT DATABASE SEARCH\n\nEnter name of student to search in database : ");
			scanf("%[^\n]s", s_name);

			//Getting position of student in database
			search_by_name( stud, s_name, pos );
		}
		else if ( option == SEARCH_BY_RNO )
		{
			//Getting student roll number to search in database	
			printf("\nSTUDENT DATABASE SEARCH\n\nEnter roll number of student to search in database : ");
			if ( int_input_validate( &s_roll ) == FAIL )
			{
				continue;
			}	
			
			//Getting position of student in database
			*pos = search_by_roll( stud, s_roll );		
		}
		else
		{
			flag = FAIL;
			printf("Invalid option\n");
			continue;
		}

		if ( *pos == NOT_FOUND )
		{
			printf("Student not present in database\n");
			break;
		}
		else
		{
			printf("\nNAME\t\t\tAGE\t       R_NO\t      MARK1\t     MARK2\t\tMARK3\t\n");			
			for ( s_num = 0; *( pos + s_num ) != -1; s_num++ )
			{
				printf("\n%-20s    %-10d     %-10d     %-10d     %-10d 	%-10d",
				(stud + *(pos + s_num) )->name, (stud + *(pos + s_num))->age, (stud + *(pos + s_num))->r_no, 
				(stud + *(pos + s_num))->marks[0], (stud + *(pos + s_num))->marks[1], (stud + *(pos + s_num))->marks[2]);
				if ( option == SEARCH_BY_RNO )	
				{	
					break;		
				}
			}	
		}
		break;
	}

	//Freeing heap memory 
	if (s_name != NULL)
	{
		free(s_name);
		s_name = NULL;
	}

	if (pos != NULL)
	{
		free(pos);
		pos = NULL;
	}

	return flag;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function searches the database by student name and returns position of student in database
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : search_by_name
*
*   Parameters : STUDENT *stud		-	structure that contains student data
*				 char *s_name		-	name to find in database
*				 int *pos			-	position string containing positions of found names
*
*   Return     : NONE
*-------------------------------------------------------------------------------------------------------*/

#if SBN_DEBUG

void search_by_name( STUDENT* stud, char *s_name, int *pos )
{
	int s_num = 0, itr = 0;

	*pos = -1;	//For indicating fail case
	
	//Searching for student in database
	for ( s_num = 0; (stud + s_num)->name != NULL; s_num++ )
	{
		//Case insensitive search for name
		if ( string_compare( (stud + s_num)->name, s_name ) == STRING_EQUAL )		
		{
			*(pos + itr++) = s_num;	//Saving position of found name
		} 
	}

	*(pos + itr) = -1;

	return;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function searches the database by student roll number and returns position of student in database
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : search_by_roll
*
*   Parameters : STUDENT *stud		-	structure that contains student data
*				 int s_roll			-	roll number to find in database
*
*   Return     : position of found student or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if SBR_DEBUG

int search_by_roll( STUDENT* stud, int s_roll )
{
	int s_num = 0, pos = -1;

	//Searching for student in database
	for ( s_num = 0; (stud + s_num)->name != NULL; s_num++ )
	{
		if ( (stud + s_num)->r_no == s_roll )		
		{
			pos = s_num;	//Saving position of found name
			break;
		} 
	}
	
	return pos;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function sorts student database based on name or roll number
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : sort_student
*
*   Parameters : STUDENT **stud		-	structure that contains student data
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if SORT_DEBUG

int sort_student( STUDENT** stud )
{
	int option, flag = PASS;

	printf("\n\n\t\t\t1. Sort student data by name\
	 	 \n\t\t\t2. Sort student data by roll number\n\
	 	 \n\t\t\tENTER YOUR CHOICE : ");
	
	if ( int_input_validate( &option ) == FAIL )
	{											
		return FAIL;
	}	
											
	if ( option == SORT_BY_NAME ) 
	{
		flag = sort_by_name( stud );
	}
	else if ( option == SORT_BY_RNO )
	{
		flag = sort_by_roll( stud );
	}
	else
	{
		printf("Invalid option\n");
		return FAIL;
	}
	
	printf("\nDatabase has been sorted successfully\n");

	return flag;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function sorts student database based on name of student
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : sort_by_name
*
*   Parameters : STUDENT **stud		-	structure that contains student data
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if SOBN_DEBUG

int sort_by_name( STUDENT **stud )
{
	int size = 0, s_num;

	STUDENT tmp_stud;

	size = student_count( *stud );

	while ( NOT_ZERO( size ) )
	{
		for ( s_num = 0; s_num < size ; s_num++ )
		{	
			if ( (*(stud) + s_num + 1)->name != NULL )
			{
				if ( string_compare( (*(stud) + s_num )->name, (*(stud) + s_num + 1 )->name ) == STRING_1 )
				{
					//swapping the strings
					tmp_stud = *(*(stud) + s_num ) ; 
					*(*(stud) + s_num ) = *(*(stud) + s_num + 1 );
					*(*(stud) + s_num + 1 ) = tmp_stud;				
				}
			}
		}

		size--;	//Every time an iteration is done, the greatest string goes to the last 
	}					//position of names. So we dont need to check that for future iterations

	return PASS;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function sorts student database based on roll number of student
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : sort_by_roll
*
*   Parameters : STUDENT **stud		-	structure that contains student data
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if SOBR_DEBUG

int sort_by_roll( STUDENT **stud )
{
	int size = 0, s_num;

	STUDENT tmp_stud;

	size = student_count( *stud );

	while ( NOT_ZERO( size ) )
	{
		for ( s_num = 0; ( *(stud) + s_num )->name != NULL ; s_num++ )
		{	
			if ( (*(stud) + s_num + 1)->name != NULL )
			{
				if ( (*(stud) + s_num )->r_no > ( *(stud) + s_num + 1 )->r_no )
				{
					//swapping the strings
					tmp_stud = *(*(stud) + s_num ) ; 
					*(*(stud) + s_num ) = *(*(stud) + s_num + 1 );
					*(*(stud) + s_num + 1 ) = tmp_stud;				
				}
			}
		}

		size--;	//Every time an iteration is done, the greatest string goes to the last 
	}					//position of names. So we dont need to check that for future iterations

	return PASS;
}

#endif

/*--------------------------------------------------------------------------------------------------------
	Function gives total marks of a particular student
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : marks_student
*
*   Parameters : STUDENT *stud		-	structure containing student data
*				 int mark_type		-	Total or average
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

#if MARKS_DEBUG

int marks_student( STUDENT *stud, int mark_type )
{
	int option, s_roll, flag = 0, *pos = NULL, mark_sum, s_num;
	char *s_name = NULL;

	//Allocating memory dynamically and checking if it was properly allocated

	s_name = (char *)malloc( NAME_SIZE * sizeof(char) );
	if (s_name == NULL)
	{
		printf("Could not allocate memory\n");
		return FAIL;
	}

	pos = (int *)malloc( 100 * sizeof(int) );
	if (pos == NULL)
	{
		printf("Could not allocate memory\n");
		return FAIL;	
	}
	
	while(1)
	{
		if ( mark_type == TOTAL_MARKS )
		{
			printf("\n\n1. Get marks by student name\
					\n2. Get marks by student roll number\
					\n\nENTER YOUR CHOICE : ");
		}
		else if ( mark_type == AVG_MARKS )
		{
			printf("\n\n1. Get average by student name\
					\n2. Get average by student roll number\
					\n\nENTER YOUR CHOICE : ");
		}

		if ( int_input_validate( &option ) == PASS )
		{
			if ( option == SEARCH_BY_NAME ) 
			{
				//Getting student name to search in database	
				printf("\nEnter name of student : ");
				scanf("%[^\n]s", s_name);

				//Getting position of student in database
				search_by_name( stud, s_name, pos );
			}
			else if ( option == SEARCH_BY_RNO )
			{
				//Getting student roll number to search in database	
				printf("\nEnter roll number of student : ");
				if ( int_input_validate( &s_roll ) == FAIL )
				{
					continue;
				}	
				
				//Getting position of student in database
				*pos = search_by_roll( stud, s_roll );		
			}
			else
			{
				flag = FAIL;
				printf("Invalid option\n");
				continue;
			}

			if ( *pos == NOT_FOUND )
			{
				printf("Student not present in database\n");
				break;

			}
			else
			{
				for ( s_num = 0; *( pos + s_num ) != -1; s_num++ )
				{
					mark_sum = (stud + *( pos + s_num ))->marks[0] + (stud + *( pos + s_num ))->marks[1] + (stud + *( pos + s_num ))->marks[2];

					if (mark_type == TOTAL_MARKS)
					{
						printf("Total marks of %s ( Roll number %d ) : %d\n", (stud + *( pos + s_num ))->name, 
							(stud + *( pos + s_num ))->r_no, mark_sum);					
					}

					else
					{
						printf("Average of %s ( Roll number %d ) : %0.2f\n", (stud + *( pos + s_num ))->name,
						(stud + *( pos + s_num ))->r_no, (float)(mark_sum) / 3);
					}

					if ( option == SEARCH_BY_RNO )
					{
						break;
					}
				}

				break;
			}
		}
	}

	//Freeing heap memory 
	if (s_name != NULL)
	{
		free(s_name);
		s_name = NULL;
	}

	if (pos != NULL)
	{
		free(pos);
		pos = NULL;
	}


	return flag;
}

#endif










/**********************************************************************************************************
								   	    HELPER FUNCTION DEFINITIONS
**********************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------
	Function receives a file and stores it's contents in the given struct object
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : get_file_contents
*
*   Parameters : FILE *fp			-	File to get contents from
*				 STUDENT **stud		-	structure to store file contents
*
*   Return     : position of last object or FAIL
*-------------------------------------------------------------------------------------------------------*/

int get_file_contents( FILE *fp, STUDENT **stud )
{
	int valid_check = 0;	//Used to check fscanf status
	int s_num = 0, max_stud = STUDENTS_COUNT;				

	while(1)
	{
		if ( (s_num) >= max_stud )
		{
			*stud = realloc( *stud, ( max_stud + 10 ) * sizeof( STUDENT ) );
			if ( *stud == NULL )
			{
				printf("Could not re-allocate memory\n");
				return EXIT_FAILURE;
			}
			
			max_stud = max_stud + 10;
		}		
	
		//Allocating memory dynamically and checking if it is allocated properly
		
		(*(stud) + s_num)->name = (char*)malloc( NAME_SIZE * sizeof(char) );
		if ( (*(stud) + s_num)->name == NULL )
		{
			printf("Could not allocate memory\n");
			return FAIL;
		}

		(*(stud) + s_num)->marks = (int*)malloc( NUMBER_OF_MARKS * sizeof(int) );
		if ( (*(stud) + s_num)->marks == NULL )
		{
			printf("Could not allocate memory\n");
			return FAIL;
		}

		//Getting input from file

		valid_check = fscanf( fp, "\n%[^,], %d, %d, %d, %d, %d;", (*(stud) + s_num)->name, &(*(stud) + s_num)->age,
							 &(*(stud) + s_num)->r_no, (*(stud) + s_num)->marks, 
							 &(*(stud) + s_num)->marks[1], &(*(stud) + s_num)->marks[2] );

		if ( valid_check == EOF )
		{
			if ( IS_ZERO( s_num ) )
			{
				printf("\nFile is empty\n");
				return FIRST_POSITION;
			}
			
			(*(stud) + s_num)->name = NULL;
			(*(stud) + s_num)->marks = NULL;
			break;
		}

		s_num++;
	}

	return s_num;

}

/*--------------------------------------------------------------------------------------------------------
	Function receives a structure and stores it's contents in the given file
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : add_to_file
*
*   Parameters : FILE *fp			-	File to store contents
*				 STUDENT *stud		-	structure to get contents
*
*   Return     : PASS or FAIL
*-------------------------------------------------------------------------------------------------------*/

int add_to_file( FILE *fp, STUDENT *stud )
{
	int s_num = 0;				

	for( s_num = 0; (stud + s_num)->name != NULL ; s_num++ )
	{
 		fprintf( fp, "%s, %d, %d, %d, %d, %d\n", (stud + s_num)->name, (stud + s_num)->age,
					 (stud + s_num)->r_no, (stud + s_num)->marks[0], 
					 (stud + s_num)->marks[1], (stud + s_num)->marks[2] );
	}

	return PASS;
}

/*--------------------------------------------------------------------------------------------------------
	Function receives a structure and frees it structure elements dynamic memory
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : free_students
*
*   Parameters : STUDENT *stud
*
*   Return     : NONE
*-------------------------------------------------------------------------------------------------------*/

void free_students( STUDENT *stud )
{
	int s_num;		//Temporary iteration variable				

	for( s_num = 0; (stud + s_num)->name != NULL ; s_num++ )
	{
		free( (stud + s_num)->name );
		free( (stud + s_num)->marks ); 		
	}
}

/*--------------------------------------------------------------------------------------------------------
	Function receives a string and returns its size
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : char_count
*
*   Parameters : char *str	- string whose size we need
*
*   Return     : string size
*-------------------------------------------------------------------------------------------------------*/

int char_count(char *str)
{
  int size = 0;

  while ( *(str + size) != NULL_CHAR )
  {
    size++;
  }
 
  return size;
}

/*--------------------------------------------------------------------------------------------------------
	Function receives a structure pointer and returns number of elements
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : student_count
*
*   Parameters : STUDENT *stud
*
*   Return     : number of STUDENT objects
*-------------------------------------------------------------------------------------------------------*/

int student_count( STUDENT *stud )
{
	int s_num = 0, size = 0;

	for (s_num = 0; (stud + s_num)->name != NULL; s_num++)
	{
		size++;
	}
	
	return size;
}

/*--------------------------------------------------------------------------------------------------------
	Function receives two strings and checks if they are equal
----------------------------------------------------------------------------------------------------------
*   
*   Function Name : string_compare
*
*   Parameters : char *str1		- String 1
*				 char *str2		- String 2
*
*   Return     : STRING_EQUAL / STRING1 / STRING2 / STRING_FAIL
*-------------------------------------------------------------------------------------------------------*/

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

/*********************************************************************************************************/

