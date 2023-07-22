/*******************************************************************************************************************************************************
*   TASK :
*   
*	1. Convert a given decimal number to binary. 
*	2. Find number of ones and zeroes in that number
*	3. Set bit 
*	4. Toggle bit
*	5. Toggle next bit if equal to current bit
*
*
*	Date : 01/10/2021
*
*********************************************************************HEADER FILES**********************************************************************/

#include<stdio.h>

#include "validate.h"

/******************************************************************MACRO DEFINITIONS*******************************************************************/

#define SET							1
#define CLEAR						0

#define BIT_MASK					1
#define BIT_SHIFT					1

#define INT_SIZE					31

#define ONE_ARGUMENT				1

#define IS_ZERO(x)          	( x == 0 )                  // Checks if number is equal to zero
#define INVALID(x)				( x != ONE_ARGUMENT )	  // Checks if scanf returned one successful argument
#define INVALID_RANGE(x,y)		( x >= y )			

#define ALREADY_SET(x,y)		( ( x >> y ) & SET )	
#define BIT_SET(x,y)			( ( 1 << y ) | x )
#define BIT_TOGGLE(x,y)			( ( 1 << y ) ^ x )
#define NEXT_BIT_EQUAL(x,y)		( ( ( num >> bit ) & 1 ) ^ ( ( num >> (bit + 1) ) & 1 ) )

enum options {
		CONVERT = 1, 
		PRINT_0_1,
		SET_BIT,
		TOGGLE_BIT,
		TOGGLE_NXT,
		EXIT,
	     };				

/*************************************************************FUNCTION PROTOTYPES*********************************************************************/

void convert_to_bin( int );
void print_bit_count( int );
void set_bits( int );
void toggle_bits( int );
void toggle_next_bit( int );
int get_size( int );
void display_bin( int num_b[], int );

/*****************************************************************MAIN FUNCTION************************************************************************/

int main()
{
 int num, status = VALID;
	
 int opt;

 printf( "\nEnter a number : " );
 
 if ( int_input_validate( &num ) == PASS )
 {
 	do{
		printf("\n\n\t\tBIT OPERATIONS\n\n\
			1. Convert to binary\n\
			2. Print number of ones and zeroes of that number\n\
			3. Set given bit\n\
			4. Toggle given bit\n\
			5. Toggle next bit if equal to current bit\n\
			6. Exit\n\n\
			ENTER YOUR CHOICE ( 1 (or) 2 (or) 3 (or) 4 (or) 5 (or) 6 ) : ");
		
			if ( int_input_validate( &opt ) == PASS )
			{
				switch( opt )
				{
					case  CONVERT 	  : 	convert_to_bin( num );
							    			break;
	
					case  PRINT_0_1   : 	print_bit_count( num );
						            		break;											
			
					case  SET_BIT     : 	set_bits( num );
							    			break;
	
					case  TOGGLE_BIT  : 	toggle_bits( num );
						            		break;		
	
					case  TOGGLE_NXT  : 	toggle_next_bit( num );
							    			break;
	
					case  EXIT	  	  : 	status = EXIT_PROGRAM ; 
							    			break;	
	
					default		  	  : 	printf("Enter valid choice ( 1 to 6 )");
	                	          			break;
				}
			}
	
			if ( status == EXIT_PROGRAM )
			{
				printf( "\n\n\t\tSEE YOU LATER \n\n" );
				break;
			}
  
 	 }while(1);
 
 }
 
 else
 {
	return FAIL;
 }

 return PASS;

}


/*************************************************************FUNCTION PROTOTYPES********************************************************************/  

/* Function receives a number from user and returns number of bits
*   
*   Function Name : get_size
*
*   Parameters : int num	-	Number  
*   
*   Return     : returns number of bits in number
*/


int get_size( int num )
{ 
	int size = 0;

	//Number is shifted bit by bit until it becomes zero
  	while ( num > 0 )		
  	{
  		size++;	
 		num = ( num >> 1 );
  	} 
  
  	return size;
}



/* Function receives a binary string from user and prints it
*   
*   Function Name : display_bin
*
*   Parameters : int num_b[] 		- 	Binary string 
*                int size       	- 	size of string 
*
*   Return     : NONE
*/

void display_bin( int num_b[], int size )
{
	int bit = 0;
	printf( "\n\t\tBinary number   : ");
  
	for( bit = 0; bit < size; bit++ )
  	{
		printf("%d", num_b[ bit ]);
  	}

	return;
}
  
  
 

/* Function receives number from user and converts it to binary 
*   
*   Function Name : convert_to_bin
*
*   Parameters 	  : int num 	- 	Number to convert  
*   
*   Return     	  : NONE
*/

void convert_to_bin( int num)
{
 	int size, bit, cur_bit, bin[INT_SIZE];		

 	size = get_size( num );

 	for ( cur_bit = size - 1; num > 0; cur_bit-- )
 	{
		bit =  ( num & BIT_MASK );		//Masking bit
		bin[ cur_bit ] = bit;			//storing bit in array
		num = ( num >> BIT_SHIFT );		//shifting bit
 	}

 	display_bin( bin, size ); 			//Displays binary sequence

 	return;		
}



/* Function receives number from user and finds number of 1s and 0s in its binary form
*   
*   Function Name : print_bit_count
*
*   Parameters : int num	- Number 
*   
*   Return     : NONE
*/

void print_bit_count( int num )
{
 	int count_0 = 0, count_1 = 0;
 	int bit=0, temp=0;

	temp = num; 

 	for( bit = 0; temp > 0; bit++)
 	{
  		bit = temp & BIT_MASK;
 	
		if ( bit == 0 )
		{
			count_0++;
		}
		else
		{
			count_1++;
		}

		temp = temp >> BIT_SHIFT ;
 	}

 	convert_to_bin( num );

 	printf("\n\t\tNumber          : %d", num);
 	printf("\n\t\tCount of zeroes : %d\n\t\tCount of ones   : %d\n", count_0, count_1);

 	return;	 
}	   



/* Function receives number from user and sets given bit
*   
*   Function Name : set_bits
*
*   Parameters : int num 	- Number 
*   
*   Return     : NONE
*/

void set_bits( int num )
{
	 int valid_check, bit;

	 printf("\n\t\tNumber          : %d", num);
	 convert_to_bin(num);
	 printf("\n\t\tEnter bit position : ");

	 valid_check = scanf( "%d", &bit );

	 if ( INVALID_RANGE( bit, INT_SIZE ) || INVALID( valid_check ) )
	 {
		printf("\n\t\tInvalid bit\n"); 
	 }
	 
	 else
	 {
	 	if ( ALREADY_SET( num, bit ) )
		{
			printf("\n\t\tBit already set\n");
	   	}
		else
		{
			num = BIT_SET( num, bit );
			printf("\n\t\tNumber          : %d", num);
			convert_to_bin( num );
		}
	 }
	 return;
}



/* Function receives number from user and toggles given bit
*   
*   Function Name : toggle_bits
*
*   Parameters : int num	-	Number
*   
*   Return     : NONE
*/


void toggle_bits( int num )
{
 	int valid_check, bit;

 	printf("\n\t\tNumber          : %d", num);
 	convert_to_bin(num);

	printf("\n\t\tEnter bit position : ");

 	valid_check = scanf( "%d", &bit );

 	if ( INVALID_RANGE( bit, INT_SIZE ) || INVALID( valid_check ) )
 	{
		printf("\n\t\tInvalid bit\n"); 
 	}
 
 	else	
 	{
		num = BIT_TOGGLE( num, bit );
		printf("\n\t\tNumber : %d", num);
    	convert_to_bin( num );
 	}
 	return;
}



/* Function receives number from user and toggles next bit
*   
*   Function Name : toggle_next_bit
*
*   Parameters 	  : int num	- Number 
*   
*   Return     	  : NONE
*/


void toggle_next_bit( int num )
{
	int valid_check, bit;
 
 	printf("\n\t\tNumber          : %d", num);
 	convert_to_bin(num);
 	printf("\n\t\tEnter bit position : ");

 	valid_check = scanf( "%d", &bit );

 	if ( INVALID_RANGE( bit, INT_SIZE ) || INVALID( valid_check ) )
	{
		printf("\n\t\tInvalid bit\n"); 
 	}
 	else
 	{
 		if ( NEXT_BIT_EQUAL( num, (bit + 1) )  == PASS )
 		{
			printf("\n\t\tNext bit is same as bit %d\n", bit);
   		}

   		else
   		{
   			num = BIT_TOGGLE( num, (bit + 1) );
			printf("\n\t\tNumber : %d", num);
    	    convert_to_bin( num );
   		}
 	}
	return;
}
 

/*******************************************************************************************************************************************************/
