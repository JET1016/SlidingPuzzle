
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* constants */
#define up_move 'w'
#define down_move 's'
#define left_move 'a'
#define right_move 'd'
#define time 60

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

void setTimeout(int milliseconds)
{
    // If milliseconds is less or equal to 0
    // will be simple return from function without throw error
    if (milliseconds <= 0) {
        fprintf(stderr, "Count milliseconds for timeout is less or equal to 0\n");
        return;
    }

    // a current time of milliseconds
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;

    // needed count milliseconds of return from this timeout
    int end = milliseconds_since + milliseconds;

    // wait while until needed time comes
    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}

// Will display a number in a font
void displayNumber(int number) {
	switch(number) {
  	case 0:
      printf(" _____\n");
      printf("| 	|\n");
      printf("|     |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 1:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  1  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 2:
 	  printf(" _____\n");
      printf("|     |\n");
      printf("|  2  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 3:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  3  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 4:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  4  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 5:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  5  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 6:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  6  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 7:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  7  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 8:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  8  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
    case 9:
      printf(" _____\n");
      printf("|     |\n");
      printf("|  9  |\n");
      printf("|     |\n");
      printf(" _____");
    	break;
  }
}




// For now, display board on the terminal to visuallize the algorithm
void displayBoard(int **board, int size) {
  for(i=0; i<size; i++) {
    for(j=0; j<size; j++) {
      // displayNumber(board[i][j]);
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
  int stage = 1;
  do {
  	  int **board;
	  int size = determineSize(stage); // determine the board size depending on the stage
	  int timer = time; // set initial value of timer to 60 seconds or 1 minute for stage one

	  // allocate memory space for board (stage one for now)
	    board = (int **)malloc(sizeof(int *)*size);
	    for (i=0; i<size; i++) {
	      board[i]= (int *)malloc(sizeof(int)*size);
	      
	    }
	  
	  // Assign random values to board   
	  board[0][0] = size*size; //save space for initial position
	  // srand(time(NULL)); 
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
	    

  	do {
  		// erase the previous line and display remain of the delay
        printf("Time left: %d\n", timer);
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


        // a timeout for display
        setTimeout(1000);

        // decrease the delay to 1
        timer--;

	} while (timer >= 0);

	stage++;

  } while(isGameOver(stage) != 0);	
  
  
  return 0;
}//end of main