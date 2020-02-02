///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        (name of file with main function)
// This File:        (name of this file)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           (your name)
// Email:            (your wisc email address)
// CS Login:         (your CS login name)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *COMMA = ",";  
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, COMMA);
    *size = atoi(token);
}       
 
   
  
/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {

	if(size % 2 == 0) {
		return 0;
	}
	int num_x = 0;
	int num_o = 0;
	for (int i = 0; i < size*size; i++) {
		if(*((*board) + i) == 1) {
			num_x++;
		}
		if(*((*board) + i) == 2) {
			num_o++;
		}
	} 
	if(!(num_x == num_o) && !(num_x == (num_o + 1))) {
		return 0;
	}
	
	int wins_x = 0;
	int wins_o = 0;
	// counting wins in rows
	for (int rows = 0; rows < size; rows++) {
		int first = *(board + rows*size);
		if(first == 0) {
			continue;
		}
		for (int cols = 1; cols < size; cols++) {
			if(*(board + rows*size + cols) != first) {
				break;
			}	
			if(first == 1) {
				wins_x++;
			}
			if(first == 2) {
				wins_o++;
			}	
		}
	}




    return 1;   
}    
  
 
   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    if(argc != 2) {
	    printf("Please enter exactly one (1) argument.\n");
	    exit(1);
    }
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;

    get_dimensions(fp, &size); // assigns dimesions to size

    int *board;
    board = (int *)malloc(sizeof(int)*size*size);  // Dynamically allocate a 2D array of dimensions retrieved above.

    //Read the file line by line.
    //Tokenize each line wrt comma to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, COMMA);
        for (int j = 0; j < size; j++) {
            //Completes the line of code below
            //to initialize your 2D array.
            *(board + (i*size) + j) = atoi(token);
            token = strtok(NULL, COMMA);
        }
    }

    //calling the method n_in_a_row to find if the board in our array is 
    //valid.

    int validity = n_in_a_row(&board, size);

    if(validity == 0) {
	    printf("invalid\n");
    }
    else {
	    printf("valid\n");
    }


    // Free all dynamically allocated memory.
	free(board);
	board = NULL;
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       
