#include <iostream>
#include<conio.h>
#include <windows.h>
using namespace std;
bool gameover;
const int width = 40;
const int hieght = 20;
int snake_head, snake_bottom, fruit_x, fruit_y, score;//x is head , y is tail
int TailX[100], TailY[100];
int nTail;

enum edirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
edirection direct;
void setup() {
	gameover = false;
	direct = STOP;
	snake_head = width / 2;// so the head is in the middle
	snake_bottom = hieght / 2;// so the tail is in the middle
	fruit_x = rand() % width;
	fruit_y = rand() % hieght;
	score = 0;
}
void draw() {
	system("cls");
	for (int i = 0; i < (width + 4); i++)
	{
		cout << "*";

	}
	cout << endl;
	for (int i = 0; i < (width + 4); i++)
	{

		cout << "@";
	}

	cout << endl;
	for (int i = 0; i < hieght; i++) {
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "*@";
			if (i == snake_bottom && j == snake_head)
				cout << "8";
			else if (i == fruit_y && j == fruit_x)
				cout << "$";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {

					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "s";
						print = true;
					}

				}
				if (!print)
				{
					cout << " ";
				}
			}


			if (j == width - 1)
				cout << "@*";
		}
		cout << endl;
	}

	for (int i = 0; i < (width + 4); i++)
	{
		cout << "@";

	}
	cout << endl;
	for (int i = 0; i < (width + 4); i++)
	{

		cout << "*";
	}
	cout << endl;
	cout << "Money: " << score << endl;
}


void input() {
	if (_kbhit()) {         //w is up  , s is down, a is left, d is right
		switch (_getch()) {
		case 'a':
			direct = LEFT;
			break;
		case 'd':
			direct = RIGHT;
			break;
		case 's':
			direct = DOWN;
			break;
		case 'w':
			direct = UP;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}

}
int logic() {
	int prevX = TailX[0];
	int prevy = TailY[0];
	int prev2X, prev2Y;
	TailX[0] = snake_head;
	TailY[0] = snake_bottom;
	for (int i = 1; i < nTail; i++) {
		prev2X = TailX[i];
		prev2Y = TailY[i];
		TailX[i] = prevX;
		TailY[i] = prevy;
		prevX = prev2X;
		prevy = prev2Y;
	}

	switch (direct) {
	case LEFT:
		snake_head--;  //head
		break;
	case RIGHT:
		snake_head++;
		break;
	case UP:
		snake_bottom--;
		break;
	case DOWN:
		snake_bottom++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0|| y>hieght ||y<0)
		//gameover = true;

	if (snake_head >= width)
		snake_head = 0;
	else if (snake_head < 0)
		snake_head = width - 1;

	if (snake_bottom >= hieght)
		snake_bottom = 0;
	else if (snake_bottom < 0)
		snake_bottom = hieght - 1;

	for (int i = 0; i < nTail; i++) {
		if (TailX[i] == snake_head && TailY[i] == snake_bottom)
			gameover = true;
	}
	if (snake_head == fruit_x && snake_bottom == fruit_y)
	{
		score = score + 10;
		fruit_x = rand() % width;
		fruit_y = rand() % hieght;
		nTail++;
	}
	return score;
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
	system("color 0E");
	int difficuty_level;
	cout << "--------Welcome to The Snake Game---------" << endl << endl;

	cout << "If you collect enough money you difficulty level will increase." << endl << "Select your difficulty level (1-3): ";

	cin >> difficuty_level;
	if (difficuty_level < 1 || difficuty_level > 3)
	{
		cout << "Incorrect Input" << endl;
		cout << "Select your difficulty level (1-3): ";
		cin >> difficuty_level;

	}

	ShowConsoleCursor(false);
	if (difficuty_level == 1)
	{
		setup();
		while (!gameover) {
			draw();
			input();
			if (logic() == 200) {
				cout << "The level of difficulty is: 2" << endl;
				Sleep(50);
			}
			else if (logic() == 400) {
				cout << "The level of difficulty is: 3" << endl;
				Sleep(1);
			}
			else
			{
				cout << "The level of difficulty is: 1" << endl;
				Sleep(300);
			}

			logic();
		}
	}


	else if (difficuty_level == 2)
	{
		setup();
		while (!gameover) {
			draw();
			input();

			if (logic() == 200) {
				cout << "The level of difficulty is: 3" << endl;
				Sleep(1);
			}
			else {
				cout << "The level of difficulty is: 2" << endl;
				Sleep(50);
			}
			logic();

		}

	}
	else if (difficuty_level == 3)
	{
		setup();
		while (!gameover) {
			draw();
			input();
			logic();

		}

	}

	return 0;
}

