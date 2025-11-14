#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define gridRows 4
#define gridCols 4
#define EMPTY 0

int score=0;
int game_over=0;



void initRand () {
	srand(time(NULL));
}

int getEmptCells(int Board[gridRows][gridCols], int emptcells[gridRows*gridCols][2]) {
	int count=0;
	for (int i=0; i<gridRows; i++) {
		for (int j=0; j<gridCols; j++) {
			if (Board[i][j]== EMPTY) {
				emptcells[count][0]=i;
				emptcells[count][1]=j;
				count++;
			}
		}
	}
	return count;
}

int maxTile(int Board[gridRows][gridCols]) {
	int Max=0;
	for (int i=0; i< gridRows; i++) {
		for (int j=0; j<gridCols; j++) {
			if (Board [i][j]>Max) {
				Max=Board[i][j];
			}
		}
	}
	return Max;
}


int TileVal (int Board[gridRows][gridCols]) {
	int MaxTile=maxTile(Board);
	if (MaxTile<=64) {
		return (rand() % 10==0) ? 4 :2;
	}
	else if (MaxTile<=256) {
		int r=rand() % 100;
		if (r<80){return 2;}
		if (r<95){return 4;}
		return 8;
	}
	else {
		int r=rand()% 100;
		if (r < 70) return 2;
        if (r < 85) return 4;
        if (r < 95) return 8;
        if (r < 99) return 16;
        return 32;
	}
}

void AddTile (int Board[gridRows][gridCols]) {
	int emptcells[gridRows*gridCols][2];
	int empt_Count=getEmptCells(Board,emptcells);
	if (empt_Count==0){
		return;
	}
	
	int randi=rand() % empt_Count;
	int row=emptcells[randi][0];
	int col=emptcells[randi][1];
	
	int value=TileVal(Board);
	
	
	Board[row][col]=value;
}



void Boardinit (int Board[gridRows][gridCols]) {
	for (int i=0; i<gridRows; i++) {
		for (int j=0; j<gridCols; j++) {
			Board[i][j]= EMPTY;
		}
	}
	AddTile(Board);
	AddTile(Board);
}


void displayBoard (int Board[gridRows][gridCols]) {	
	printf("\n");
	for (int i=0;i<gridRows; i++){
	    printf("+------+------+------+------+\n");
        printf("|");
        for (int j=0; j<gridCols; j++){
        	if (Board[i][j]==EMPTY) {
        		printf("      |");
			} else {
				printf(" %d |", Board[i][j]);
			}
		}
		printf("\n");
	}
	printf("+------+------+------+------+\n\n");
	printf("Controls:\n");
    printf("W - Up\n");
    printf("A - Left\n");
    printf("S - Down\n");
    printf("D - Right\n");
    printf("Q - Quit\n\n");
}

int GameStateCheck (int Board[gridRows][gridCols]){
	for (int i=0;i<gridRows; i++){
		for (int j=0;j<gridCols; j++){
			if (Board[i][j]==EMPTY){
				return 0;
			}
		}
	}
	
	    for (int i = 0; i < gridRows; i++) {
            for (int j = 0; j < gridCols; j++) {
                if (j < gridCols - 1 && Board[i][j] == Board[i][j + 1]) {
                return 0;
            }
                if (i < gridRows - 1 && Board[i][j] == Board[i + 1][j]) {
                return 0;
            }
        }
    }
    
    return 1;
}

int check_win(int Board[gridRows][gridCols]) {
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols; j++) {
            if (Board[i][j] == 2048) {
                return 1;
            }
        }
    }
    return 0;
}

int move_left(int Board[gridRows][gridCols]) {
    int moved = 0;
    
    for (int i = 0; i < gridRows; i++) {
        for (int j = 0; j < gridCols - 1; j++) {
            if (Board[i][j] == EMPTY) {
                for (int k = j + 1; k < gridCols; k++) {
                    if (Board[i][k] != EMPTY) {
                        Board[i][j] = Board[i][k];
                        Board[i][k] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
        for (int j = 0; j < gridCols - 1; j++) {
            if (Board[i][j] != EMPTY && Board[i][j] == Board[i][j + 1]) {
                Board[i][j] *= 2;
                score += Board[i][j];
                Board[i][j + 1] = EMPTY;
                moved = 1;
            }
    }
        for (int j = 0; j < gridCols - 1; j++) {
            if (Board[i][j] == EMPTY) {
                for (int k = j + 1; k < gridCols; k++) {
                    if (Board[i][k] != EMPTY) {
                        Board[i][j] = Board[i][k];
                        Board[i][k] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }
    
    return moved;
}
int move_right(int Board[gridRows][gridCols]) {
    int moved = 0;
    
    for (int i = 0; i < gridRows; i++) {
        for (int j = gridCols - 1; j > 0; j--) {
            if (Board[i][j] == EMPTY) {
                for (int k = j - 1; k >= 0; k--) {
                    if (Board[i][k] != EMPTY) {
                        Board[i][j] = Board[i][k];
                        Board[i][k] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
        for (int j = gridCols - 1; j > 0; j--) {
            if (Board[i][j] != EMPTY && Board[i][j] == Board[i][j - 1]) {
                Board[i][j] *= 2;
                score += Board[i][j];
                Board[i][j - 1] = EMPTY;
                moved = 1;
            }
        }
        for (int j = gridCols - 1; j > 0; j--) {
            if (Board[i][j] == EMPTY) {
                for (int k = j - 1; k >= 0; k--) {
                    if (Board[i][k] != EMPTY) {
                        Board[i][j] = Board[i][k];
                        Board[i][k] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }
    
    return moved;
}

int move_up(int Board[gridRows][gridCols]) {
    int moved = 0;
    
    for (int j = 0; j < gridCols; j++) {
        for (int i = 0; i < gridRows - 1; i++) {
            if (Board[i][j] == EMPTY) {
                for (int k = i + 1; k < gridRows; k++) {
                    if (Board[k][j] != EMPTY) {
                        Board[i][j] = Board[k][j];
                        Board[k][j] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < gridRows - 1; i++) {
            if (Board[i][j] != EMPTY && Board[i][j] == Board[i + 1][j]) {
                Board[i][j] *= 2;
                score += Board[i][j];
                Board[i + 1][j] = EMPTY;
                moved = 1;
            }
        }
        for (int i = 0; i < gridRows - 1; i++) {
            if (Board[i][j] == EMPTY) {
                for (int k = i + 1; k < gridRows; k++) {
                    if (Board[k][j] != EMPTY) {
                        Board[i][j] = Board[k][j];
                        Board[k][j] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }
    
    return moved;
}

int move_down(int Board[gridRows][gridCols]) {
    int moved = 0;
    
    for (int j = 0; j < gridCols; j++) {
        for (int i = gridRows - 1; i > 0; i--) {
            if (Board[i][j] == EMPTY) {
                for (int k = i - 1; k >= 0; k--) {
                    if (Board[k][j] != EMPTY) {
                        Board[i][j] = Board[k][j];
                        Board[k][j] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
        for (int i = gridRows - 1; i > 0; i--) {
            if (Board[i][j] != EMPTY && Board[i][j] == Board[i - 1][j]) {
                Board[i][j] *= 2;
                score += Board[i][j];
                Board[i - 1][j] = EMPTY;
                moved = 1;
            }
        }
        for (int i = gridRows - 1; i > 0; i--) {
            if (Board[i][j] == EMPTY) {
                for (int k = i - 1; k >= 0; k--) {
                    if (Board[k][j] != EMPTY) {
                        Board[i][j] = Board[k][j];
                        Board[k][j] = EMPTY;
                        moved = 1;
                        break;
                    }
                }
            }
        }
    }
    
    return moved;
}

int process_input(int Board[gridRows][gridCols]) {
    char input;

    input = getch();
    printf("%c", input);
    
    int moved = 0;

    switch(input) {
        case 'w':
        case 'W':
        case 72:
            if (!GameStateCheck(Board) && !check_win(Board)) {
                moved = move_up(Board);
            }
            break;
            
        case 'a':
        case 'A':
        case 75:
            if (!GameStateCheck(Board) && !check_win(Board)) {
                moved = move_left(Board);
            }
            break;
            
        case 's':
        case 'S':
        case 80:
            if (!GameStateCheck(Board) && !check_win(Board)) {
                moved = move_down(Board);
            }
            break;
            
        case 'd':
        case 'D':
        case 77:
            if (!GameStateCheck(Board) && !check_win(Board)) {
                moved = move_right(Board);
            }
            break;
            
        case 'r':
        case 'R':
            return -1;
            
        case 'q':
        case 'Q':
            return -2;
            
        default:
            printf("\nInvalid input! Use W/A/S/D to move, R to restart, Q to quit.\n");
            printf("Press any key to continue...");
            getch();
            return 0;
    }
    
    return moved;
}



int main() {
    int Board[gridRows][gridCols];
    
    initRand();

    Boardinit(Board);
    
    printf("Welcome to 2048!\n");
    printf("Combine tiles to reach 2048!\n");
    printf("Press any key to start...");
    getch();

    while (1) {
        system("cls");
        
        printf("=== 2048 GAME ===\n");
        printf("Score: %d\n", score);
        printf("Max Tile: %d\n\n", maxTile(Board));
        
        displayBoard(Board);

        if (check_win(Board)) {
            printf("?? CONGRATULATIONS! YOU REACHED 2048! ??\n");
            printf("Final Score: %d\n", score);
            printf("Press R to restart or Q to quit: ");
        }
        else if (GameStateCheck(Board)) {
            printf("?? GAME OVER! No more moves possible. ??\n");
            printf("Final Score: %d\n", score);
            printf("Press R to restart or Q to quit: ");
        }
        else {
            printf("Enter move (W/A/S/D/R/Q): ");
        }

        int result = process_input(Board);
 
        switch(result) {
            case -1:
                score = 0;
                game_over = 0;
                Boardinit(Board);
                printf("\n?? Game restarted!\n");
                Sleep(1000);
                break;
                
            case -2:
                printf("\n?? Thanks for playing! Final score: %d\n", score);
                return 0;
                
            case 0:
                break;
                
            default:
                if (!GameStateCheck(Board) && !check_win(Board)) {
                    AddTile(Board);
                }
                break;
        }
        Sleep(100);
    }
    
    return 0;

}
