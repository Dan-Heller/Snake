#ifndef HEADER
#define HEADER

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h> 
#include <dos.h>
#include <Windows.h>

#define ROWS 15
#define COLS 40
#define SnakeChar '@'
#define RIGHT 'd'
#define LEFT 'a'
#define UP 'w'
#define DOWN 's'
#define RIGHTKEY 77
#define LEFTKEY 75
#define UPKEY 72
#define DOWNKEY 80
#define FOOD '$'
#define WALL '#'
#define ESC 27

typedef struct Node
{
	int x;
	int y;
	char ch;
	struct Node* next;
}Node;

typedef struct SNAKE
{
	Node* head;
	Node* end;
}SNAKE;

/////headers
void sleep(float secs);
void printBoard();
void gotoxy(int x, int y);
void movesnake(SNAKE* snake, char NewDir, bool* game, char SnakeMatrix[][COLS + 1]);
void BuildSnake(SNAKE* snake, char SnakeMatrix[][COLS + 1]);
void MoveNodesXY(Node* head, int tempx, int tempy);
bool IsFoodEaten(Node* Head, int* FoodX, int* FoodY, int* score, char SnakeMatrix[][COLS + 1]);
void MoveHead(SNAKE* snake, char NewDir, bool* game);
void MakeSnakeBigger(SNAKE* snake, char NewDir, bool* game, char SnakeMatrix[][COLS + 1]);
bool HitWall(Node* head);
void AvoidRepeatSteps(char* NewDir, char CurrDir);
void FillMatrixWithSpaces(char SnakeMatrix[][COLS + 1]);
void WaitForPress();
void WonTheGame();
void FreeSnake(SNAKE* snake);
void GameOver(int score);
void DetermineDir(char* NewDir, char CurrDir, char key);


#endif // HEADER
