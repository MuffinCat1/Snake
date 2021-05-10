#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <tchar.h>

using namespace std;

bool gameOver;

const int width = 35;
const int height = 20;

int  x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

#pragma warning ( disable : 26812 4551 4996)
void Setup() {

	SetConsoleTitle(_T("Snake"));

	gameOver = false;

	dir = STOP;

	x = width / 2;
	y = height / 2;
	
	fruitX = rand() % width;
	fruitY = rand() % height;
	
	score = 0;
}

void Draw() {

	//update the program to not make copies of the game when doing something
	system("cls");

	for (int i = 0; i < width + 2; i++)
		cout << "#";

	cout << endl;

	for (int i = 0; i < height; i++) {
		
		for (int j = 0; j < width; j++) {
			
			if (j == 0)
				cout << "#";

			if (i == y && j == x)
				cout << "O";

			else if (i == fruitY && j == fruitX)
				cout << "$";

			else {
				
				bool print = false;

				for (int k = 0; k < nTail; k++) {

					if (tailX[k] == j && tailY[k] == i) {
						
						cout << "o";
						print = true;
					}
				}

				if (!print)
					cout << " ";
			}
			
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";

	cout << endl;

	cout << "Score: " << score << "$" << endl;
	cout << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'x':
			gameOver = true;
			break;
		}
	}
}	

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {

		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case UP:
		y--;
		break;

	case DOWN:
		y++;
		break;

	default:
		break;
	}

	//if you want to die when hiting the walls
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;
	
	//if you want not to die by the walls
	//if (x >= width) x = 0; else if (x < 0) x = width - 1;
	//if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++) {
		
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true; 
		}
	}

	if (x == fruitX && y == fruitY) {
		
		score += 5;

		fruitX = rand() % width;
		fruitY = rand() % height;

		nTail++;
	}
}

int main() {

	time_t now = time(0);
	tm* local_time = localtime(&now);

	ofstream scoreLog;

	Setup();

	while (!gameOver) {

		Draw();
		Input();
		Logic();

		Sleep(10);
	}
	
	//create a text file that stores the time you played, the date in your computer, the time in your computer and your score from the last game 
	scoreLog.open("score.txt", ios::out | ios::app);
	scoreLog << "[" << "Date: " << 0 << local_time->tm_mday << "/" << 0 << 1 + local_time->tm_mon << "/" << 1900 + local_time->tm_year << "  Time: " <<  1 + local_time->tm_hour << ":" << 1 + local_time->tm_min << "  Timer: " << 1 + local_time->tm_sec << " sec in game" << "] " << score << " points" << endl;
	scoreLog.close();

	Sleep(2);

	return 0;
}
