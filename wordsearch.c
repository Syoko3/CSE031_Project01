#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize; //global variable to hold puzzle grid size

//helper function declarations go here 🐻😭😭🙏
int isSameChar(char a, char b); // purpose of this function is to make the code case insensitive AND to compare two letters (a letter from the puzzle grid compared with a letter from the user's word)
void markPath(int** path, int row, int col, int index); // purpose of this function is to mark the path in the result matrix

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block (ex., '5' would make a 5x5 puzzle grid)
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    // Did by Sohdai
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

int isSameChar(char a, char b){
	//input a : letter from puzzle grid
	//input b : letter from user's search word
	//the purpose of this function is to make the code case insensitive AND to compare a letter in a puzzle grid (input a) with a letter from the user's word (input b)
	//this works because in ASCII, the lowercase letters are always 32 higher than the uppercase letters
	if(a >= 'a' && a <= 'z'){
		a = a - 32;
	}
	if(b >= 'a' && b <= 'z'){
		b = b - 32;
	}
	return a == b; //returns 1 if characters match, otherwise returns 0

void markPath(int** path, int row, int col, int index){
    int current = *(*(path + row) + col);
    if(current == 0){
        *(*(path + row) + col) = index;
    } else{
        // Combine indices if multiple paths go through the same cell
        *(*(path + row) + col) = current * 10 + index;
    }
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    // search_path - 2D-array with all 0s initialized in each row and col
    int** search_path = (int**) malloc (bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        *(search_path + i) = (int*) malloc (bSize * sizeof(int));
        for (int j = 0; j < bSize; j++) {
            *(*(search_path + i) + j) = 0;
        }
    }
    
}
