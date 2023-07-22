/*******************************************************************************************************************************************************
*   TASK :
*   
*   Given two matrices, we have to output the multiplied product. Also verify input validations.
*
*
*	Date : 30/09/2021
*
********************************************************************HEADER FILES**********************************************************************/

#include <stdio.h>

/******************************************************************MACRO DEFINITIONS*******************************************************************/

#define PASS		0
#define FAIL		1

#define MATRIX_ONE	1
#define MATRIX_TWO	2

#define ONE_ARGUMENT	1
#define TWO_ARGUMENTS	2

#define NEGATIVE(x)	        (x < 0)				            // Checks if a given value is negative
#define INVALID_RC(x)	    (x != TWO_ARGUMENTS)			// Used to check if rows and columns are entered correctly 
#define INVALID_M(x)	    (x != ONE_ARGUMENT)		    	// Used to check if matrix elements are entered correctly
#define IS_ZERO(x)          (x == 0)                  		// Checks if number is equal to zero
#define LIMIT_EXCEED(x)     (x >= 100)                		// Checks if matrix size if exceeded 


/*************************************************************FUNCTION PROTOTYPES*********************************************************************/

int input_matrix(int m[100][100], int, int, int);		
void display_matrix(int m[100][100], int , int );
void multiply_matrix(int m1[100][100], int, int, int m2[100][100], int, int, int mat_mul[100][100]);
int input_row_col( int*, int*, int );

/*****************************************************************MAIN FUNCTION************************************************************************/

int main( void )
{
 
 int mat1[100][100], mat2[100][100], mat_mul[100][100];				//Matrices used in the program
 
 int row_m1 = 0, col_m1 = 0, row_m2 = 0, col_m2 = 0;	 			//Rows and columns of matrices

 int flag = PASS;  								//Flag variable for finding function status

 if ( input_row_col( &row_m1, &col_m1, MATRIX_ONE ) == PASS ) 		//Getting input of matrix 1 rows and columns from user and validating it
 { 	
    if ( input_matrix( mat1, row_m1, col_m1, MATRIX_ONE ) == PASS )
    {
    	if ( input_row_col( &row_m2, &col_m2, MATRIX_TWO ) == PASS )	//Getting input of matrix 1 from user and validating it
 	    {
     		if ( col_m1 != row_m2 )										//Checking matrix multiplication condition
   		    {
    			    printf("Matrix multiplication cannot be performed...enter valid matrix sizes\n");

       		    flag = FAIL;
       	  	}
          
          	if ( flag == PASS )
          	{  
            	if ( input_matrix( mat2, row_m2, col_m2, MATRIX_TWO ) == PASS )
            	{
                	multiply_matrix( mat1, row_m1, col_m1, mat2, row_m2, col_m2, mat_mul );   //Multiplying matrices

               		printf("\n\n   MATRIX MULTIPLICATION OUTPUT :\n\n");        //Displaying output matrix
                	display_matrix( mat_mul, row_m1, col_m2 );  
              	}				
       	  	}
  	   	}
    }
 }

}
 
/*************************************************************FUNCTION PROTOTYPES*********************************************************************/
  

/* This function is used to get matrix from user and also validate user's input values
*   
*   Function Name : input_matrix
*
*   Parameters : int m[100][100] 	- Matrix 
*                int row       		- number of rows in matrix 
*		 		 int col			- number of columns in matrix
*				 int mat_num		- Matrix number
*   
*   Return     : returns PASS or FAIL
*/
    
int input_matrix(int m[100][100], int row, int col, int mat_num)
{
  int i,j, valid_check;     		//temp variables

  printf("Enter MATRIX %d elements\n", mat_num);
  
  for ( i = 0; i < row; i++ )
  {
   	for( j = 0; j < col; j++ )
   	{
     	valid_check = scanf( "%d", &m[i][j] );

  		if ( INVALID_M( valid_check ) )
   		{
			printf("\nInvalid elements in matrix\n");
	   		return FAIL;
     	}
   	}
  }

  return PASS;  
}



/* This function is used to display matrix 
*   
*   Function Name : display_matrix
*
*   Parameters : int m[100][100] 	- Matrix 
*                int row       		- number of rows in matrix 
*		 		 int col			- number of columns in matrix
*   
*   Return     : no return type
*/

void display_matrix(int mat[100][100], int row, int col)
{
  int r,c;     //temp variables
 
  for ( r = 0; r < row; r++ )
  {
   	for( c = 0; c < col; c++ )
   	{
     		printf("\t%d   ", mat[r][c] );
  	}

   	printf("\n\n");
  } 

  printf("\n");
}




/* This function is used to multiply two given matrices
*   
*   Function Name : multiply_matrix
*
*   Parameters : int m1[100][100] 		- Matrix 1
*                int r1       			- number of rows in matrix 1
*		 		 int c1					- number of columns in matrix 1
*		 		 int m2[100][100]		- Matrix 2
*                int r2       			- number of rows in matrix 2
*		 		 int c2					- number of columns in matrix 2	
*				 int mat_mul[100][100] 	- Matrix to store product
*   
*   Return     : no return type
*/

void multiply_matrix(int m1[100][100], int r1, int c1, int m2[100][100], int r2, int c2, int mat_mul[100][100])
{

  int row, col, mul;     	//r - row | c - col | m - multiply
  
  for ( row = 0; row < r1; row++ )
  {
   for ( col = 0; col < c2; col++ )
   {
     mat_mul[row][col] = 0;
    
     for ( mul = 0; mul < r2 ; mul++ )
     { 
        mat_mul[row][col] = mat_mul[row][col] + ( m1[row][mul] * m2[mul][col] );
     } 
   }
  }
  
} 




/* This function is used to get rows and columns from the user and also validate their inputs
*   
*   Function Name : input_row_col
*
*   Parameters : int m[100][100] 	- Matrix 
*                int *row       	- number of rows in matrix 
*		 		 int *col			- number of columns in matrix 
*		 		 int mat_num		- Matrix number
*   
*   Return     : returns PASS or FAIL
*/

int input_row_col( int *row, int *col, int mat_num )
{
  int valid_check;

  printf("Enter number of rows and columns for MATRIX %d ( Max value - 100 rows and 100 cols ) : ", mat_num); 

  valid_check = scanf("%d %d", row, col) ;

  if ( INVALID_RC( valid_check ) )					//Checking if non-integer values
  {
     	printf( "Enter integer values\n" );
     	return FAIL;
  }

  if ( ( IS_ZERO( *row ) || IS_ZERO( *col ) ) )		//Checking if zero is entered
  {
      printf("Enter non-zero values\n");
      return FAIL;
  }

  if ( ( LIMIT_EXCEED( *row ) || LIMIT_EXCEED( *col ) ) )		//Checking if user entered size greater than 100
  {
      if ( LIMIT_EXCEED( *row ) )
      {
          printf( "Rows entered is greater than MAX VALUE (100) \n" );  
      }

      if ( LIMIT_EXCEED( *col ) )
      {
          printf( "Columns entered is greater than MAX VALUE (100) \n" );  
      }

      return FAIL;
  }

  if ( NEGATIVE( *row ) || NEGATIVE( *col ) )		//Checking if negative values are entered for rows or columns
  {
      if ( NEGATIVE( *row ) )
      {
          printf( "Enter positive values for rows\n" );  
      }

      if ( NEGATIVE( *col ) )
      {
          printf( "Enter positive values for columns\n" );
      }
     	
      return FAIL;
  }

  return PASS;

}

/******************************************************************************************************************************************************/


