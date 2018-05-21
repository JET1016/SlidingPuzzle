#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

/* constants */
#define up_move 'w'
#define down_move 's'
#define left_move 'a'
#define right_move 'd'
#define start '1'
#define instruction '2'
#define quit '0'
#define stages 5

/* global variables */
int temp, i, j, x, y, current_x, current_y;
int chances = 3;


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
  write_text("[2] Instructions", 20, 140, YELLOW, 0);
  write_text("[0] Quit", 20, 160, YELLOW, 0);
}

void displayInstructions() {
  set_graphics(VGA_320X200X256);
  write_text("SLIDING PUZZLE", 20, 50, MAGENTA, 1);
  write_text("Sort tiles in ascending order", 20, 120, WHITE, 0);
  write_text("W - UP ", 20, 130, WHITE, 0);
  write_text("S - DOWN ", 20, 140, WHITE, 0);
  write_text("A - LEFT ", 20, 150, WHITE, 0);
  write_text("D - RIGHT ", 20, 160, WHITE, 0);
  write_text("[0] Back", 20, 170, WHITE, 0);
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

  // Stage 1 or Stage 2
  if(size <= 5) {
    for(i = 0; i < size; i ++) {
      for(j = 0; j < size; j ++) {    
        if(board[i][j] != 0) {
          sprintf(str, "%d", board[i][j]); // Convert integer to String
          write_text(str, 50 + (30 * j), 50 + (30 * i) , WHITE, 1);
        }
      }
    }
  // Stage 3
  } else if(size == 7) {
    for(i = 0; i < size; i ++) {
      for(j = 0; j < size; j ++) {    
        if(board[i][j] != 0) {
          sprintf(str, "%d", board[i][j]); // Convert integer to String
          write_text(str, 50 + (40 * j), 50 + (20 * i) , WHITE, 0);
        }
      }
    }
  // Stage 4
  } else if(size == 9) {
    for(i = 0; i < size; i ++) {
      for(j = 0; j < size; j ++) {    
        if(board[i][j] != 0) {
          sprintf(str, "%d", board[i][j]); // Convert integer to String
          write_text(str, 50 + (30 * j), 50 + (15 * i) , WHITE, 0);
        }
      }
    }
  // Stage 5
  } else {
    for(i = 0; i < size; i ++) {
      for(j = 0; j < size; j ++) {    
        if(board[i][j] != 0) {
          sprintf(str, "%d", board[i][j]); // Convert integer to String
          write_text(str, 50 + (25 * j), 50 + (15 * i) , WHITE, 0);
        }
      }
    }
  }
}

// Update board when making a move, called my moveTile()
void updateBoard(int **board, int size, int prev_x, int prev_y, int new_x, int new_y) {
  char str[5];
  sprintf(str, "%d", board[new_y][new_x]); //previous value in the new coordinate

  // Stage 1 or Stage 2
  if(size <= 5) {
    fill_rect(50 + (30 * new_x), 50 + (30 * new_y), 20, 20, BLACK);
    write_text(str, 50 + (30 * prev_x), 50 + (30 * prev_y) , WHITE, 1);
  // Stage 3
  } else if(size == 7) {
    fill_rect(50 + (40 * new_x), 50 + (20 * new_y), 15, 13, BLACK);
    write_text(str, 50 + (40 * prev_x), 50 + (20 * prev_y) , WHITE, 0);
  // Stage 4
  } else if(size == 9) {
    fill_rect(50 + (30 * new_x), 50 + (15 * new_y), 15, 13, BLACK);
    write_text(str, 50 + (30 * prev_x), 50 + (15 * prev_y) , WHITE, 0);
  // Stage 5
  } else {
    fill_rect(50 + (25 * new_x), 50 + (15 * new_y), 15, 13, BLACK);
    write_text(str, 50 + (25 * prev_x), 50 + (15 * prev_y) , WHITE, 0);
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

void displayOptions() {
  // Clear screen
  fill_rect(0, 0, 350, 200, BLACK);

  // Display stage name
  write_text("Do you want to quit?", 50, 30, WHITE, 0);
  write_text("[1] Resume [0] Quit", 50, 60, WHITE, 0);
}

void displayOptionsStages() {
  // Clear screen
  fill_rect(0, 0, 350, 200, BLACK);

  // Display stage name
  write_text("Do you really want to quit?", 50, 30, WHITE, 0);
  write_text("[1] Continue [0] Quit", 50, 60, WHITE, 0);
}

// Init board for stage, display board
// Return 0 if failed stage
// Return 1 if successful stage
// Return 2 if chose to quit
int startStage(int stage) {
  // Board variables
  int **board;
  int size = determineSize(stage);
  char keyPressed; 

  // Timer variables
  dex32_datetime time_start, time_curr;
  int time_limit, time_diff=0, time_left;
  
  // variables used for writing/display
  char timeleft_str[20];
  char chance[20];

 
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
  
 
  get_date_time(&time_start);  // get starting time for every turn
  time_limit = 10*stage;  // Initialize time limit according to stage
  
  do {
    // Get key pressed
    keyPressed = (char)getch();

    // If player chose to quit, 0
    if(keyPressed == quit) {

      // Display options for player Resume or quit
      displayOptions();

      // If chose to resume
      if(keyPressed = (char)getch() == '1') {

        // Redisplay board graphically
        displayStage(board, stage, size);

      // If chose to quit
      } else return 2;
    } else {
       // Function call for moving tile
      moveTile(keyPressed, board, size);
      // Get current time
      get_date_time(&time_curr); 
      // Compute for the seconds equivalence of the current minute
      int min = time_curr.min * 60;
      // Compute for time difference between starting time and the current time
      time_diff = (time_curr.sec + min) - (time_start.sec + min);
      // Compute for the time left
      time_left = time_limit - time_diff;


      // Converts the chance to string for display
      sprintf(chance,"Chances: %d",chances);
      // clears the score part on the screen for a new score display
      fill_rect(279, 30, 15, 13, BLACK); 
    
      // Check if there is time left
      if(time_left <= 0) {
        write_text("0", 279, 30, RED, 0);    // display a zero with color red if time is up
      } else {
        sprintf(timeleft_str, "Time left: %d",time_left); // else, convert time to string for display
        write_text(timeleft_str, 180, 30, WHITE, 0); // display the time left
      }
        write_text(chance, 180, 20, WHITE, 0);    // display chances left as well
    
        // Check if the time difference bet. the start and current time exceeds the time limit 
        if(time_diff > time_limit) {
            write_text("TIME IS OVER", 200, 40, MAGENTA, 1); // if so, prompt player that time is up
            chances = chances - 1; // then, decrease the chances to play
            delay(30); 
            return 0;
        }
      }
    
  // While puzzle is not solved, 
  } while(isPuzzleSolved(board, size) != 1);

  // If successfully solved,
  return 1;
}

// Go through stages
// return 0 if game over
// Return 1 if won game, finished all stages
int runStages() {
  int stage = 1, value;
  // Stages are only until 5
  while(stage < 6) {
    value = startStage(stage);
    // If failed stage
    if(value == 0)  {
      // Clear screen
      fill_rect(0, 0, 350, 200, BLACK);
      // If still has chance
      if(chances > 0) {

        // New stage
        continue;
      } else return 0;

    // If successful stage
    } else if(value == 1){
      // Clear screen
      fill_rect(0, 0, 350, 200, GREEN);
      // Update stage
      stage ++;
      // Reset stage
      chances = 3;

    // value = 2, chose to quit
    } else {
      return 0;
    }
  }
  return 1;
}

// Run Game
void runGame() {
  // Variable to get input from user
  char keyPressed;

  displayMenu();

  do {

    // If input is start
    if(keyPressed == start) {

      // Start stages
      runStages();

     // Else if chose to display instructions
    } else if (keyPressed == instruction) {
    	while((keyPressed = (char)getch()) != quit) {
    		displayInstructions();
    	}
    }

    displayMenu();

    chances = 3;

  } while((keyPressed = (char)getch()) != quit);
  
  set_graphics(VGA_TEXT80X25X16);
  clrscr();
}

// Main function
int main() {

  runGame();

  return 0;
}//end of main
