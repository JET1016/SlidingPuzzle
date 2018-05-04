#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

/* constants */
#define up_move 'w'
#define down_move 's'
#define left_move 'a'
#define right_move 'd'
#define chances 3

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
        temp = board[i][j];
      } else {
        return 0; // return 0 if condition is not satisfied
      }
      
    }
  } 
  return 1;
}


// Checks if the timer has run out indicating end of game; 1 if true, 0 if false
int isGameOver(int stage) {
  if(stage == 5) return 0;
  return 1;
}

int determineSize(int stage) {
  switch(stage) {
    case 1:
      return 3; break;
    case 2:
      return 5; break;
    case 3:
      return 7; break;
    case 4:
      return 9; break;
    case 5:
      return 10; break;
    default:
      return 0; break;
  }
}


// For now, display board on the terminal to visuallize the algorithm
void displayBoard(int **board, int size) {
  // Create borders
  char border_1[200] = "";
  char border_2[200] = "";
  char init_space_1[5] = "  ";
  char init_space_2[5] = " ";
  char mid_space_1[10] = "       ";
  char mid_space_2[10] = "     ";
  char box[10] = "|     |";
  char top[10] = "_____";
  strcat(border_1, init_space_1);
  strcat(border_2, init_space_2);
  for(i=0; i <size; i++) {
    strcat(border_1, top);
    strcat(border_2, box);
    strcat(border_1, mid_space_1);
    strcat(border_2, mid_space_2);
  }

  // Print puzzle 
  for(i=0; i<size; i++) {
    printf("%s\n", border_1);
    printf("%s\n", border_2);
    printf(" ");
    for(j=0; j<size; j++) {
      if(board[i][j] != 0) printf("|  %d  |", board[i][j]);
      else printf("|     |");
      printf("     ");
    }
    printf("\n");
    printf("%s\n", border_2);
    printf("%s\n", border_1);
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
  int stage = 1, timer = 6000; // initialize stage and timer
  int size = determineSize(stage); // determine the board size depending on the value of the stage

  
  // allocate memory space for board (stage one for now)
    board = (int **)malloc(sizeof(int *)*size);
    for (i=0; i<size; i++) {
      board[i]= (int *)malloc(sizeof(int)*size);
      
    }
  
  // Assign random values to board   
  board[0][0] = size*size; //save space for initial position
  srand(time(NULL)); 
  for(i = 1; i < size*size; i++) { // For numbers 1 to 8, 
    // randomize position in board     
    do{
      x = rand() % size;    
      y = rand() % size;  
    } while(board[x][y] != 0);
    board[x][y] = i;
  }
  
  // update initial position
  board[0][0] = 0;
  current_x = 0;
  current_y = 0;
  
  char move;
  time_t start, end;
  start = clock(); // get current time

  do {
     printf("Timer: %ld\n", (clock()-start));
    displayBoard(board, size);
  
    // ask input from user (this is for now, we'll research more about key event handling)
    
    printf("Enter your move [q to exit]: ");
    scanf("%c", &move);
    getchar();
    if(move == 'q') {
      printf("Thank you for playing! Bye!\n");
      break;
    }

    moveTile(move, board, size);
   
  } while((clock() - start) < timer*stage); // loop while puzzle is solved
  


  return 0;
}//end of main