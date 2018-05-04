
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* constants */
#define up_move 'w'
#define down_move 's'
#define left_move 'a'
#define right_move 'd'

/* global variables */
int temp, i, j, x, y, current_x, current_y;


// Checks if move is valid, 1: valid, 0: invalid
int checkMoveValidity(int new_x, int new_y) {
  if(new_x < 0 || new_x > 2 || new_y < 0 || new_y > 2) return 0;
  return 1;
}

// For now, game will end when user solved the puzzle, no time constraints
int isPuzzleSolved(int **board, int size) {
  int temp=0;
  for(i=0; i<size; i++) {
    for(j=0; j<size; j++) {
      if(temp <= board[i][j]) { // check if the previous tile is less than the current tile
        printf("%d %d\n", temp, board[i][j]);
        temp = board[i][j];
      } else {
        return 0; // return 0 if condition is not satisfied
      }
      
    }
  } 
  return 1;
}

// For now, display board on the terminal to visuallize the algorithm
void displayBoard(int **board, int size) {
  for(i=0; i<size; i++) {
    for(j=0; j<size; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  } 
}

// Moves the tile
void moveTile(char move, int **board, int size) {
  int new_x, new_y;

  switch(move) {
    case 'w': //if up, check down piece,move it up, empty space will move to up
      new_y = current_y + 1;
      new_x = current_x;
      break;
    case 's':
      new_y = current_y - 1;
      new_x = current_x;
      break;
    case 'a': //if left, check right piece, move it left, empty space will move to right
      new_y = current_y;
      new_x = current_x + 1;
      break;
    case 'd':
      new_y = current_y;
      new_x = current_x - 1;
      break;
  }

  if(checkMoveValidity(new_x, new_y) == 1) {
    temp = board[new_y][new_x]; //previous value in the new coordinate
    board[new_y][new_x] = 0; //move empty space to new coordinates
    board[current_y][current_x] = temp; //Update previous coordinate
    // Update current positions
    current_x = new_x;
    current_y = new_y;
  }
}


// Main function
int main() {
  int **board;
  int size = 3;
  
  // allocate memory space for board (stage one for now)
    board = (int **)malloc(sizeof(int *)*size);
    for (i=0; i<3; i++) {
      board[i]= (int *)malloc(sizeof(int)*size);
      
    }
  
  // Assign random values to board   
  board[0][0] = 9; //save space for initial position
  srand(time(NULL)); 
  for(i = 1; i < 9; i++) { // For numbers 1 to 8, 
    // randomize position in board     
    do{
      x = rand() % 3;    
      y = rand() % 3;  
    } while(board[x][y] != 0);
    board[x][y] = i;
  }
  
  // update initial position
  board[0][0] = 0;
  current_x = 0;
  current_y = 0;
  
  do {
    displayBoard(board, size);   
  
    // ask input from user (this is for now, we'll research more about key event handling)
    char move;
    printf("Enter your move [q to exit]: ");
    if(move == 'q') {
      printf("Thank you for playing! Bye!\n");
      break;
    }
    scanf("%c", &move);
    moveTile(move, board, size);
 

    
  } while(isPuzzleSolved(board, size) != 1); // loop while puzzle is solved
  
  return 0;
}//end of main