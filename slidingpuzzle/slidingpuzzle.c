#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

/* constants */
#define up_move 'w'
#define down_move 's'
#define left_move 'a'
#define right_move 'd'
#define start '1'
#define quit '0'
#define chances 3
#define stages 5

/* global variables */
int temp, i, j, x, y, current_x, current_y;


// Checks if move is valid, 1: valid, 0: invalid
int checkMoveValidity(int new_x, int new_y, int size) {
  if(new_x < 0 || new_x > size - 1  || new_y < 0 || new_y > size - 1) return 0;
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

// Moves the tile, return 1 if successful
int moveTile(char move, int **board, int size) {
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

  if(checkMoveValidity(new_x, new_y, size) == 1) {
    updateBoard(board, size, current_x, current_y, new_x, new_y);
    temp = board[new_y][new_x]; //previous value in the new coordinate
    board[new_y][new_x] = 0; //move empty space to new coordinates
    board[current_y][current_x] = temp; //Update previous coordinate
    // Update current positions
    current_x = new_x;
    current_y = new_y;
    return 1;
  }
  return 0;
}


// Graphics functions



void displayMenu() {
  set_graphics(VGA_320X200X256);
  write_text("SLIDING PUZZLE", 20, 50, MAGENTA, 1);
  write_text("[1] Start", 20, 120, YELLOW, 0);
  write_text("[0] Quit", 20, 140, YELLOW, 0);
}
  // From vgademo.c - Joseph Anthony C. Hermocilla
void fill_rect(int x, int y, int w, int h, int color){
  int i,j;
  for (i=y;i<=(y+h);i++)
    for (j=x;j<=(x+w);j++)
      write_pixel(j,i, color);
} 

// Display board graphically
void displayGraphicBoard(int **board, int size) {
  char str[5];
  if(size <= 5) {
    for(i = 0; i < size; i ++) {
      for(j = 0; j < size; j ++) {    
        if(board[i][j] != 0) {
          sprintf(str, "%d", board[i][j]); // Convert integer to String
          write_text(str, 50 + (30 * j), 50 + (30 * i) , WHITE, 1);
        }
      }
    }
  } else {
    for(i = 0; i < size; i ++) {
      for(j = 0; j < size; j ++) {    
        if(board[i][j] != 0) {
          sprintf(str, "%d", board[i][j]); // Convert integer to String
          write_text(str, 50 + (20 * j), 50 + (20 * i) , WHITE, 0);
        }
      }
    }
  }
  
}

// Update board when making a move, called my moveTile()
void updateBoard(int **board, int size, int prev_x, int prev_y, int new_x, int new_y) {
  char str[5];
  sprintf(str, "%d", board[new_y][new_x]); //previous value in the new coordinate

  if(size <= 5) {
    fill_rect(50 + (30 * new_x), 50 + (30 * new_y), 20, 20, BLACK);
    write_text(str, 50 + (30 * prev_x), 50 + (30 * prev_y) , WHITE, 1);
  } else {
    fill_rect(50 + (30 * new_x), 60 + (30 * new_y), 15, 15, BLACK);
    // write_text(str, 30 + (20 * prev_x), 30 + (20 * prev_y) , WHITE, 0);
  }
  
}

// Display stage graphically based in parameters
void displayStage(int **board, int stage, int size) {
  char*stage_name = "";
  
  // Assign stage name
  switch(stage) {
    case 1:
      stage_name = "STAGE 1";
      break;
    case 2:
      stage_name = "STAGE 2";
      break;
    case 3:
      stage_name = "STAGE 3";
      break;
    case 4:
      stage_name = "STAGE 4";
      break;
    case 5:
      stage_name = "STAGE 5";
      break;
  }
  
  // Clear screen
  fill_rect(0, 0, 350, 200, BLACK);

  // Display stage name
  write_text(stage_name, 25, 20, WHITE, 0);

  // Display board
  displayGraphicBoard(board, size);
}

// Init board for stage, display board
void startStage(int stage) {
  int **board;
  int size = determineSize(stage);
  char keyPressed; 

  // allocate memory space for board (stage one for now)
  board = (int **)malloc(sizeof(int *)*size);
  for (i=0; i<size; i++) {
    board[i]= (int *)malloc(sizeof(int)*size);
    
  }

  // Assign random values to board   
  board[0][0] = size*size; //save space for initial position
  srand(time()); 
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

  // Display board graphically
  displayStage(board, stage, size);
  do {
      moveTile(keyPressed, board, size);
  // While puzzle is not solved
  } while((keyPressed = (char)getch()) != quit); 
}

// Run Game
void runGame() {
  // Variable to get input from user
  char keyPressed;

  displayMenu();

  // If input is start
  do {
    if(keyPressed == start) {
      startStage(3);
    }

  } while((keyPressed = (char)getch()) != quit);
  
  set_graphics(VGA_TEXT80X25X16);
  clrscr();
}

// Main function
int main() {

  runGame();

  return 0;
}//end of main