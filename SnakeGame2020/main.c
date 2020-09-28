#include "header.h"

void main() {
	system("cls");
	srand((unsigned int)time(NULL));
	bool game = true, IsEat = false, Won = false, pressed;
	char NewDir = RIGHT, CurrDir = RIGHT, key;

	char SnakeMatrix[ROWS + 1][COLS + 1]; // matrix saves the snake location.
	FillMatrixWithSpaces(SnakeMatrix);

	int FoodX = (rand() % (ROWS - 2)) + 2;
	int FoodY = (rand() % (COLS - 2)) + 2;
	int score = 0;

	printBoard();
	WaitForPress(); //wait for key to be pressed

	SNAKE Snake;
	BuildSnake(&Snake, SnakeMatrix);
	
	gotoxy(1, COLS + 2); //print initial score
	printf("Score = %d", score);

	gotoxy(FoodX, FoodY); //print first food.
	printf("%c", FOOD);
	gotoxy(ROWS + 1, 1);

	while (game) {
		
			if (_kbhit()) {  //check if a key was pressed.
				key = _getch();
				DetermineDir(&NewDir, CurrDir, key);
				AvoidRepeatSteps(&NewDir, CurrDir); //snake wont go to opposite dir.
			}

			IsEat = IsFoodEaten(Snake.head, &FoodX, &FoodY, &score, SnakeMatrix);
			if (IsEat == true) {
				if (score % 10 == 0) { //makes sound when eating
					Beep(523.25, 50);
					Beep(783.99, 50);
				}
				else{ Beep(523.25, 50); }
				
				if (score == (ROWS - 2) * (COLS - 2)) { //win the game option.
					game = false;
					Won = true;
				}
				else {
					MakeSnakeBigger(&Snake, NewDir, &game, SnakeMatrix);
					if (game != false) { 
						gotoxy(FoodX, FoodY); //print new food.
						printf("%c", FOOD);
						gotoxy(ROWS + 1, 1);
						IsEat = false;
					}	
				}
			}
			else {
				movesnake(&Snake, NewDir, &game, SnakeMatrix);
			}
			CurrDir = NewDir;
			sleep(0.11);

			if (!game) {  
				FreeSnake(&Snake);
				FillMatrixWithSpaces(SnakeMatrix);

				if (Won == true) {
					WonTheGame();
				}
				else {
					GameOver(score);

					pressed = false;
					while (pressed != true) { //wait for player to choose if to play again or not.
						if (_kbhit()) {
							
							key = _getch();
							if (key == DOWN || key == 13) { //want to play again , iniate values.
								system("cls");
								pressed = true;
								game = true;
								IsEat = false;
								Won = false;
								NewDir = RIGHT;
								CurrDir = RIGHT;
								score = 0;
								printBoard();
								BuildSnake(&Snake, SnakeMatrix);
								gotoxy(1, COLS + 2); //print initial score
								printf("Score = %d", score);
								gotoxy(FoodX, FoodY); //print first food.
								printf("%c", FOOD);
								gotoxy(ROWS + 1, 1);
							}
							else if (key == ESC){ //exit
								pressed = true;
							}
						}
					}	
				}
			}
	}
}

