#include "header.h"


void DetermineDir(char* NewDir, char CurrDir, char key) {

	if (key == 0 || key == -32) { // if the first value is esc

		key = _getch();
		switch (key) { // the real value
		case UPKEY:
			*NewDir = UP;
			break;
		case DOWNKEY:
			*NewDir = DOWN;
			break;
		case RIGHTKEY:
			*NewDir = RIGHT;
			break;
		case LEFTKEY:
			*NewDir = LEFT;
			break;
		}
	}

	else {
		if (key == RIGHT || key == 'D') {
			*NewDir = RIGHT;
		}
		else if (key == LEFT || key == 'A') {
			*NewDir = LEFT;
		}
		else if (key == UP || key == 'W') {
			*NewDir = UP;
		}
		else if (key == DOWN || key == 'S') {
			*NewDir = DOWN;
		}
		else {
			*NewDir = CurrDir;
		}
	}

}

void FreeSnake(SNAKE* snake) {
	Node* temp = snake->head, * Del;
	while (temp != NULL) {
		Del = temp;
		temp = temp->next;
		free(Del);
	}
}

void GameOver(int score) {
	system("cls");
	printBoard();
	gotoxy(ROWS / 2, (COLS / 2) - 4);
	printf("GAME OVER");
	gotoxy((ROWS / 2) + 1, (COLS / 2) - 6);
	printf("Your score is %d", score);
	gotoxy(ROWS + 1, 1);

	gotoxy((ROWS / 2) + 3, (COLS / 2) - 12);
	printf("Press S or Enter to play again");
	gotoxy(ROWS + 1, 1);
	gotoxy((ROWS / 2) + 4, (COLS / 2) - 12);
	printf("Press ESC to exit");
	gotoxy(ROWS + 1, 1);
}

void WonTheGame() {
	system("cls");
	printBoard();
	gotoxy(ROWS / 2, (COLS / 2) - 3);
	printf("You Won");
	gotoxy(ROWS + 1, 1);
}


void WaitForPress()
{
	gotoxy(ROWS / 2, (COLS / 2) - 6);
	printf("Press any key");
	gotoxy(ROWS + 1, 1);
	bool pressed = false;
	while (pressed != true) {
		if (_kbhit()) {
			pressed = true;
			system("cls");
			printBoard();
		}
	}
}

void FillMatrixWithSpaces(char SnakeMatrix[][COLS + 1]) {
	for (int i = 0; i < ROWS + 1; i++) {
		for (int j = 0; j < COLS + 1; j++) {
			SnakeMatrix[i][j] = ' ';
		}
	}
}

void AvoidRepeatSteps(char* NewDir, char CurrDir) {
	if (*NewDir == RIGHT && CurrDir == LEFT) {
		*NewDir = LEFT;
	}
	else if (*NewDir == LEFT && CurrDir == RIGHT) {
		*NewDir = RIGHT;
	}
	else if (*NewDir == UP && CurrDir == DOWN) {
		*NewDir = DOWN;
	}
	else if (*NewDir == DOWN && CurrDir == UP) {
		*NewDir = UP;
	}
}

bool HitWall(Node* head) {

	if (head->y == 1 || head->y == COLS || head->x == 1 || head->x == ROWS) {

		return true;
	}
	return false;
}

bool IsFoodEaten(Node* Head, int* FoodX, int* FoodY, int* score, char SnakeMatrix[][COLS + 1]) {
	if (Head->x == *FoodX && Head->y == *FoodY) {
		gotoxy(*FoodX, *FoodY);
		printf("%c", SnakeChar);
		*FoodX = (rand() % (ROWS - 2)) + 2;
		*FoodY = (rand() % (COLS - 2)) + 2;
		while (SnakeMatrix[*FoodX][*FoodY] == SnakeChar) {
			*FoodX = (rand() % (ROWS - 2)) + 2;
			*FoodY = (rand() % (COLS - 2)) + 2;
		}
		(*score)++;
		gotoxy(1, COLS + 2);
		printf("Score = %d", *score);
		gotoxy(ROWS + 1, 1);
		return true;
	}
	return false;
}

void MakeSnakeBigger(SNAKE* snake, char NewDir, bool* game, char SnakeMatrix[][COLS + 1]) {
	int tempx = snake->head->x, tempy = snake->head->y;
	int Endx = snake->end->x, Endy = snake->end->y;

	MoveHead(snake, NewDir, game);
	if (SnakeMatrix[snake->head->x][snake->head->y] == SnakeChar || HitWall(snake->head)) {
		*game = false;
		Beep(100, 70);
	}
	else {
		gotoxy(snake->head->x, snake->head->y);
		printf("%c", snake->head->ch);
		gotoxy(ROWS + 1, 1);
		SnakeMatrix[snake->head->x][snake->head->y] = SnakeChar;

		MoveNodesXY(snake->head, tempx, tempy);

		gotoxy(snake->end->x, snake->end->y);
		snake->end->ch = SnakeChar;
		printf("%c", snake->end->ch);
		SnakeMatrix[snake->end->x][snake->end->y] = snake->end->ch;

		Node* NewEndNode = (Node*)malloc(sizeof(Node));
		NewEndNode->next = NULL;
		snake->end->next = NewEndNode;
		NewEndNode->ch = ' ';
		NewEndNode->x = Endx;
		NewEndNode->y = Endy;
		snake->end = NewEndNode;

		gotoxy(ROWS + 1, 1);
	}
}

void movesnake(SNAKE* snake, char NewDir, bool* game, char SnakeMatrix[][COLS + 1]) {
	int tempx = snake->head->x;
	int tempy = snake->head->y;

	MoveHead(snake, NewDir, game);
	if (SnakeMatrix[snake->head->x][snake->head->y] == SnakeChar || HitWall(snake->head)) {
		*game = false;
		Beep(100, 70);
	}
	else {
		gotoxy(snake->head->x, snake->head->y);
		printf("%c", snake->head->ch);
		gotoxy(ROWS + 1, 1);
		SnakeMatrix[snake->head->x][snake->head->y] = SnakeChar;

		MoveNodesXY(snake->head, tempx, tempy);

		gotoxy(snake->end->x, snake->end->y);
		printf("%c", snake->end->ch);
		SnakeMatrix[snake->end->x][snake->end->y] = snake->end->ch;

		gotoxy(ROWS + 1, 1);
	}
}

void BuildSnake(SNAKE* snake, char SnakeMatrix[][COLS + 1]) {
	Node* EndOfSnake = (Node*)malloc(sizeof(Node));
	EndOfSnake->next = NULL;
	EndOfSnake->x = ROWS / 2;
	EndOfSnake->y = (COLS / 2) - 1;
	EndOfSnake->ch = ' ';

	Node* Head = (Node*)malloc(sizeof(Node));
	Head->next = EndOfSnake;
	Head->x = ROWS / 2;
	Head->y = COLS / 2;
	Head->ch = SnakeChar;

	SnakeMatrix[Head->x][Head->y];
	snake->head = Head;
	snake->end = EndOfSnake;
}



void MoveHead(SNAKE* snake, char NewDir, bool* game) {
	if (NewDir == RIGHT) {
		(snake->head->y)++;
	}
	else if (NewDir == LEFT) {
		(snake->head->y)--;
	}
	else if (NewDir == UP) {
		(snake->head->x)--;
	}
	else if (NewDir == DOWN) {
		(snake->head->x)++;
	}
}

void MoveNodesXY(Node* head, int tempx, int tempy) {
	int neckx, necky;
	int newx = tempx, newy = tempy;
	Node* temp = head;

	while (temp->next != NULL) {
		neckx = temp->next->x;
		necky = temp->next->y;

		temp->next->x = newx;
		temp->next->y = newy;

		newx = neckx;
		newy = necky;

		temp = temp->next;
	}

}

void printBoard() {
	int i, j;
	for (i = 0; i < COLS; i++) {
		printf("%c", WALL);
	}
	for (j = 0; j < (ROWS - 2); j++) {
		gotoxy(j + 2, 1);
		printf("%c", WALL);
		gotoxy(j + 2, COLS);
		printf("%c", WALL);
	}
	gotoxy(ROWS, 1);
	for (i = 0; i < COLS; i++) {
		printf("%c", WALL);
	}
}

void gotoxy(int x, int y) {
	printf("\x1b[%d;%df", x, y);
}

void sleep(float secs) {
	clock_t clocks_start = clock();
	while (clock() - clocks_start < secs * CLOCKS_PER_SEC)
		;
}