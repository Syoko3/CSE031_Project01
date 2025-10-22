#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //I genuinely don't think that this does anything lol but I'm not gonna remove it just yet

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize; //global variable to hold puzzle grid size

//helper function declarations go here 🐻😭😭🙏
int wordlength(char* word); // purpose of this function is to count the user's word length
int isSameChar(char a, char b); // purpose of this function is to make the code case insensitive AND to compare two letters (a letter from the puzzle grid compared with a letter from the user's word)
int searchWord(char** arr, char* word, int row, int col, int** path, int step, int wordLen); //purpose of this function is to search for the word recursively
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
    for (int i = 0; i < bSize; i++) {
        for (int j = 0; j < bSize; j++) {
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}

int wordlength(char* word) {
    int length = 0;
    int i = 0;
    
    // Counting each letter of the word
    while (*(word + i) != NULL) {
        length += 1;
        i += 1;
    }
    
    return length;
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
}

void markPath(int** path, int row, int col, int index){
    int current = *(*(path + row) + col);
    if(current == 0){
        *(*(path + row) + col) = index;
    } else{
        // Combine indices if multiple paths go through the same cell
        *(*(path + row) + col) = current * 10 + index;
    }
}

int searchWord(char** arr, char* word, int row, int col, int** path, int step, int wordLen){
    // here is the base case where we check if we've found all characters
    if (step == wordLen){
        return 1;
    }
    
    // here we check the bounds
    if (row < 0 || row >= bSize || col < 0 || col >= bSize){
        return 0;
    }
    
    // here we check if the current cell matches the current character
    if (!isSameChar(*(*(arr + row) + col), *(word + step))){
        return 0;
    }
    
    // this line saves the current value in case we need to do some backtracking
    int currentValue = *(*(path + row) + col);
    
    // this marks the current step in the path using the markPath function
    markPath(path, row, col, step + 1);
    
    // defining all 8 directions
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    // trying all directions
    for (int i = 0; i < 8; i++){
        int newRow = row + *(dr + i);
        int newCol = col + *(dc + i);
        
        if (searchWord(arr, word, newRow, newCol, path, step + 1, wordLen)){
            return 1;
        }
    }
    
    // if no direction worked we unmark this cell (ie. we backtrack)
    if (currentValue == 0){
        *(*(path + row) + col) = 0;
    } else{
        // this restores the original value
        *(*(path + row) + col) = currentValue;
    }
    
    return 0;
}

void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

	int wordLen = wordlength(word); //I changed it from wordLength to wordlength (with a lowercase l)
	
    // search_path - 2D-array with all 0s initialized in each row and col
    int** search_path = (int**) malloc (bSize * sizeof(int*));
    for (int i = 0; i < bSize; i++) {
        *(search_path + i) = (int*) malloc (bSize * sizeof(int));
        for (int j = 0; j < bSize; j++) {
            *(*(search_path + i) + j) = 0;
        }
    }
    
    //int word_length = wordlength(word);
    int found = 0;
    // This was the code that needed to be fixed. I made a revised version of it. But I am leaving this here just for future reference.
    // for (int k = 0; k < word_length; k++) {
    //     char curr_letter = *(word + k);
    //     int curr_index_found = 0;
    //     for (int i = 0; i < bSize; i++) {
    //         for (int j = 0; j < bSize; j++) {
    //             int same = isSameChar(*(*(arr + i) + j), curr_letter);
    //             if (same == 1) {
    //                 markPath(search_path, i, j, k + 1);
    //                 curr_index_found = 1;
    //             }
    //         }
    //     }
    //     if (curr_index_found == 0) {
    //         found = 0;
    //         break;
    //     }
    //     else {
    //         found = 1;
    //     }
    // }
	for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            if(isSameChar(*(*(arr + i) + j), *word)){
                // this creates a temporary path for this search
                int** temp_path = (int**) malloc (bSize * sizeof(int*));
                for(int x = 0; x < bSize; x++){
                    *(temp_path + x) = (int*) malloc (bSize * sizeof(int));
                    for(int y = 0; y < bSize; y++){
                        *(*(temp_path + x) + y) = *(*(search_path + x) + y);
                    }
                }
                
                if(searchWord(arr, word, i, j, temp_path, 0, wordLen)){
                    found = 1;
                    // this copies temp_path to search_path
                    for(int x = 0; x < bSize; x++){
                        for (int y = 0; y < bSize; y++){
                            *(*(search_path + x) + y) = *(*(temp_path + x) + y);
                        }
                    }
                }
                
                // this frees the temporary path
                for(int x = 0; x < bSize; x++){
                    free(*(temp_path + x));
                }
                free(temp_path);
                
                if(found){
                    break;
                }
            }
        }
        if(found){
            break;
        }
    }

	//I modified the code here because the previous output was slanted, and this one is straight
    if(found){
        printf("Word found!\n");
		printf("Printing the search path:\n");
		for(int i = 0; i < bSize; i++){
			for(int j = 0; j < bSize; j++){
				printf("%d\t", *(*(search_path + i) + j));
			}
			printf("\n");
    	}
	} else{
		printf("Word not found!\n");
	}

	//frees up memory because why not lol
	for(int i = 0; i < bSize; i++){
		free(*(search_path + i));
	}
	free(search_path);
}

    
