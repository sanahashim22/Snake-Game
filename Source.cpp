#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<ctime>
#include<iomanip>
using namespace std;

enum DIRECTION { UP, DOWN, LEFT, RIGHT };
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct position {
	int ri, ci;
};
struct snake {

	position* pS;
	DIRECTION dir;
	int size;
	char sym;
	int score = 0;
	int LEFTKEY, RIGHTKEY, UPKEY, DOWNKEY;
	int ALEFTKEY, DRIGHTKEY, SUPKEY, ZDOWNKEY;
	int GLEFTKEY, JRIGHTKEY, HUPKEY, BDOWNKEY;
	int XLEFTKEY, VRIGHTKEY, FUPKEY, CDOWNKEY;

	string pName;

};
struct food {
	position fp;
	bool isAlive;
	int score = 0;
	char sym;
};
void drawbox1(int row, int col, int height, int width, int color) {
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < width; c++) {
				if (r == 0 || c == 0 || r == height - 1 || c == width - 1) {

					SetClr(color);
					gotoRowCol(row + r, col + c);
					cout << char(-37);
				}
		}
	}

}
void printbox1(int brow, int bcol) {
	for (int r = 0; r < 1; r++) {
		//for (int c = 0; c < bcol ; c++) {
		drawbox1(0 * brow, 0 * bcol, brow, bcol, 9);
		//}
	}
}
bool isLegalCoordinate(position p, snake& s,int height,int width) {

	for (int i = 0; i < s.size; i++) {
		if (s.pS[i].ri == p.ri && s.pS[i].ci == p.ci) {
			return false;
		}
	}
	if ((p.ri == 0 || p.ci == 0 ||
		p.ci == width-1 || p.ri == height-1)) {
		return false;
	}
	return true;
}
void generateFood(food& f, int height, int width, snake& s) {
	do {
		f.fp.ri = rand() % (height);
		f.fp.ci = rand() % (width);
	} while (!isLegalCoordinate(f.fp, s,height,width));
	f.isAlive = true;
	f.score = 1;

}
void initsnake1(snake& s, food& f, int height, int width) {
	SetClr(7);

	gotoRowCol(65, 0);
	cout << "Player Name : ";
	cin >> s.pName;

	s.pS = new position[3];
	s.pS[0].ri = height / 2;
	s.pS[0].ci = width / 2;

	s.pS[1].ri = height / 2;
	s.pS[1].ci = width / 2 - 1;

	s.pS[2].ri = height / 2;
	s.pS[2].ci = width / 2 - 2;

	s.size = 3;
	s.sym = -37;
	s.score = 0;
	s.dir = RIGHT;
	s.RIGHTKEY = 77;
	s.LEFTKEY = 75;
	s.UPKEY = 72;
	s.DOWNKEY = 80;
	generateFood(f, height, width, s);
	f.sym = -37;
}
void initsnake2(snake& s, food& f, int height, int width) {
	SetClr(7);
	gotoRowCol(66, 0);
	cout << "2nd Player Name : ";
	cin >> s.pName;

	s.pS = new position[3];
	s.pS[0].ri = height / 4;
	s.pS[0].ci = width / 4;

	s.pS[1].ri = height / 4;
	s.pS[1].ci = width / 4 - 1;

	s.pS[2].ri = height / 4;
	s.pS[2].ci = width / 4 - 2;

	s.size = 3;
	s.sym = 'o';
	s.score = 0;
	s.dir = LEFT;
	s.DRIGHTKEY = 100;
	s.ALEFTKEY = 97;
	s.SUPKEY = 115;
	s.ZDOWNKEY = 122;
	generateFood(f, height, width, s);
	f.sym = -37;
}
void initsnake3(snake& s, food& f, int height, int width) {
	SetClr(7);
	gotoRowCol(67, 0);
	cout << "3rd Player Name : ";
	cin >> s.pName;

	s.pS = new position[3];
	s.pS[0].ri = height / 3;
	s.pS[0].ci = width / 3;

	s.pS[1].ri = height / 3;
	s.pS[1].ci = width / 3 - 1;

	s.pS[2].ri = height / 3;
	s.pS[2].ci = width / 3 - 2;

	s.size = 3;
	s.sym = '@';
	s.score = 0;
	s.dir = LEFT;
	s.JRIGHTKEY = 106;
	s.GLEFTKEY = 103;
	s.HUPKEY = 104;
	s.BDOWNKEY = 98;
	generateFood(f, height, width, s);
	f.sym = -37;
}
void initsnake4(snake& s, food& f, int height, int width) {
	SetClr(7);
	gotoRowCol(68, 0);
	cout << "4th Player Name : ";
	cin >> s.pName;

	s.pS = new position[3];
	s.pS[0].ri = 10;
	s.pS[0].ci = 10 / 3;

	s.pS[1].ri = 10 / 3;
	s.pS[1].ci = 10 / 3 - 1;

	s.pS[2].ri = 10 / 3;
	s.pS[2].ci = 10 / 3 - 2;

	s.size = 3;
	s.sym = 'E';
	s.score = 0;
	s.dir = RIGHT;
	s.VRIGHTKEY = 118;
	s.XLEFTKEY = 120;
	s.FUPKEY = 102;
	s.CDOWNKEY = 99;
	generateFood(f, height, width, s);
	f.sym = -37;
}

//void init(snake& s, food& f, int height, int width) {
//	initsnake1(s, f, height, width);
//}
void displayFood(food f) {
	gotoRowCol(f.fp.ri, f.fp.ci);
	SetClr(4);
	cout << f.sym;
}
void displaySnake(const snake& s, int height, int width) {
	for (int i = 0; i < s.size; i++) {
		if (i == 0) {
			gotoRowCol(s.pS[i].ri, s.pS[i].ci);
			SetClr(5);
			cout << s.sym;
		}
		else {
			gotoRowCol(s.pS[i].ri, s.pS[i].ci);
			SetClr(6);
			cout << s.sym;
		}

	}
}
void moveSnake(snake& s, int height, int width) {
	for (int i = s.size - 1; i - 1 >= 0; i--) {
		s.pS[i] = s.pS[i - 1];
	}

	switch (s.dir) {
	case UP:
		s.pS[0].ri--;
		if (s.pS[0].ri == -1) {
			s.pS[0].ri = height - 1;
		}
		break;
	case DOWN:
		s.pS[0].ri++;
		if (s.pS[0].ri == height) {
			s.pS[0].ri = 0;
		}
		break;
	case RIGHT:
		s.pS[0].ci++;
		if (s.pS[0].ci == width) {
			s.pS[0].ci = 0;
		}
		break;
	case LEFT:
		s.pS[0].ci--;
		if (s.pS[0].ci == -1) {
			s.pS[0].ci = width - 1;
		}
		break;
	}

	/*if (s.pS[s.size-1].ri == height-3 || s.pS[0].ri == 2 ||
		s.pS[s.size-1].ci == width-3 || s.pS[s.size-1].ri == 3
		|| s.pS[0].ci == 2 || s.pS[0].ci == width-3 ||
		s.pS[0].ri == height-1 || s.pS[s.size-1].ci == 2) {
		printbox1(height, width);
	}*/
}
void changeDirection(snake& s, char key) {
	if (key == s.UPKEY) {
		if (s.dir != DOWN) {
			s.dir = UP;
		}
	}
	if (key == s.DOWNKEY) {
		if (s.dir != UP) {
			s.dir = DOWN;
		}
	}
	if (key == s.RIGHTKEY) {
		if (s.dir != LEFT) {
			s.dir = RIGHT;
		}
	}
	if (key == s.LEFTKEY) {
		if (s.dir != RIGHT) {
			s.dir = LEFT;
		}
	}
}
void changeDirection2(snake& s, char key) {
	if (key == s.SUPKEY) {
		if (s.dir != DOWN) {
			s.dir = UP;
		}
	}
	if (key == s.ZDOWNKEY) {
		if (s.dir != UP) {
			s.dir = DOWN;
		}
	}
	if (key == s.DRIGHTKEY) {
		if (s.dir != LEFT) {
			s.dir = RIGHT;
		}
	}
	if (key == s.ALEFTKEY) {
		if (s.dir != RIGHT) {
			s.dir = LEFT;
		}
	}

}
void changeDirection3(snake& s, char key) {
	if (key == s.HUPKEY) {
		if (s.dir != DOWN) {
			s.dir = UP;
		}
	}
	if (key == s.BDOWNKEY) {
		if (s.dir != UP) {
			s.dir = DOWN;
		}
	}
	if (key == s.JRIGHTKEY) {
		if (s.dir != LEFT) {
			s.dir = RIGHT;
		}
	}
	if (key == s.GLEFTKEY) {
		if (s.dir != RIGHT) {
			s.dir = LEFT;
		}
	}
}
void changeDirection4(snake& s, char key) {
	if (key == s.FUPKEY) {
		if (s.dir != DOWN) {
			s.dir = UP;
		}
	}
	if (key == s.CDOWNKEY) {
		if (s.dir != UP) {
			s.dir = DOWN;
		}
	}
	if (key == s.VRIGHTKEY) {
		if (s.dir != LEFT) {
			s.dir = RIGHT;
		}
	}
	if (key == s.XLEFTKEY) {
		if (s.dir != RIGHT) {
			s.dir = LEFT;
		}
	}

}
void eraseSnake(const snake& s) {
	for (int i = 0; i < s.size; i++) {
		if (i == 0) {
			gotoRowCol(s.pS[i].ri, s.pS[i].ci);
			SetClr(5);
			cout << ' ';
		}
		else {
			gotoRowCol(s.pS[i].ri, s.pS[i].ci);
			cout << ' ';
		}
	}
}
bool foodIsEaten(snake& s, food f) {
	return s.pS[0].ri == f.fp.ri && s.pS[0].ci == f.fp.ci;
}
void expandSnake(snake& s) {
	position* HP = new position[s.size + 1];
	for (int i = 0; i < s.size; i++) {
		HP[i] = s.pS[i];
	}
	HP[s.size] = s.pS[s.size - 1];
	s.size++;
	delete[] s.pS;
	s.pS = HP;

}
bool killSnake(snake& s) {
	for (int i = 3; i < s.size; i++) {
		if (s.pS[0].ri == s.pS[i].ri && s.pS[0].ci == s.pS[i].ci) {
			return true;
		}
	}
	return false;
}
bool snakekilling(snake& s,snake& a) {
	for (int i = 0; i < s.size; i++) {
		for (int j = 0; j < a.size; j++) {
			if (s.pS[i].ri == a.pS[j].ri && s.pS[i].ci == a.pS[j].ci) {
				return true;
			}
		}
	}
	return false;
}
bool snakekilling2(snake& s, snake& a,snake& q) {
	for (int i = 0; i < s.size; i++) {
		for (int j = 0; j < a.size; j++) {
			if (s.pS[i].ri == a.pS[j].ri && s.pS[i].ci == a.pS[j].ci) {
				return true;
			}
		}
	}
	for (int i = 0; i < s.size; i++) {
		for (int j = 0; j < q.size; j++) {
			if (s.pS[i].ri == q.pS[j].ri && s.pS[i].ci == q.pS[j].ci) {
				return true;
			}
		}
	}
	for (int i = 0; i < q.size; i++) {
		for (int j = 0; j < a.size; j++) {
			if (q.pS[i].ri == a.pS[j].ri && q.pS[i].ci == a.pS[j].ci) {
				return true;
			}
		}
	}
	return false;
}
bool snakekilling3(snake& s, snake& a, snake& q,snake& r) {
	for (int i = 0; i < s.size; i++) {
		for (int j = 0; j < a.size; j++) {
			if (s.pS[i].ri == a.pS[j].ri && s.pS[i].ci == a.pS[j].ci) {
				return true;
			}
		}
	}
	for (int i = 0; i < s.size; i++) {
		for (int j = 0; j < q.size; j++) {
			if (s.pS[i].ri == q.pS[j].ri && s.pS[i].ci == q.pS[j].ci) {
				return true;
			}
		}
	}
	for (int i = 0; i < q.size; i++) {
		for (int j = 0; j < a.size; j++) {
			if (q.pS[i].ri == a.pS[j].ri && q.pS[i].ci == a.pS[j].ci) {
				return true;
			}
		}
	}
	for (int i = 0; i < q.size; i++) {
		for (int j = 0; j < r.size; j++) {
			if (q.pS[i].ri == r.pS[j].ri && q.pS[i].ci == r.pS[j].ci) {
				return true;
			}
		}
	}

    for (int i = 0; i < s.size; i++) {
     	for (int j = 0; j < r.size; j++) {
		    if (s.pS[i].ri == r.pS[j].ri && s.pS[i].ci == r.pS[j].ci) {
			return true;
		    }
	    }
    }
	for (int i = 0; i < a.size; i++) {
		for (int j = 0; j < r.size; j++) {
			if (a.pS[i].ri == r.pS[j].ri && a.pS[i].ci == r.pS[j].ci) {
				return true;
			}
		}
	}
	return false;
}
void sleep(double l) {
	for (int m = 0; m < 3; m++) {
		for (int m = 0; m < l * 1000000000; m++);
	}
}
void drawbox2(int sr, int sc, int brow, int bcol, int color) {
	int c = 0;
	for (int r = 0; r < brow; r++) {
		//for (int c = 0; c < bcol; c++) {
			
			if (r == 0 || c == 0 || r == brow - 1 || c == bcol - 1) {

				SetClr(color);
				gotoRowCol(sr + r, sc + c);
				cout << char(-37);
			}
			
		//}
	}

}


int main() {
	sndPlaySound(TEXT("bscs22101-input.wav"), SND_ASYNC);

	srand(time(0));
	int height = 60, width = 80;
	snake s[4];
	int choice = 0;
	cout << "ENTER 1 for 1 player game: " << endl;
	cout << "ENTER 2 for 2 player game: " << endl;
	cout << "ENTER 3 for 3 palyer game: " << endl;
	cout << "ENTER 4 for 4 player game: " << endl;
	cout << "Enter choice: " << endl;
	cin >> choice;
	
	if (choice == 1) {

		system("cls");
		//main1();
		char ch;
		food f;
		int x = 1;
		initsnake1(s[0], f, height, width);
		displayFood(f);
		gotoRowCol(66, 0);
		SetClr(15);
		cout << "Score ";
		cout << s[0].score;
		int h = 0, m = 0, sec = 0;
		gotoRowCol(72, 0);
		SetClr(15);
		cout << "Targeted Score: 20" << endl << endl;
		cout << "Timer : " << endl;
		
		while (true) {
			
			gotoRowCol(75,0);
			SetClr(15);
			cout << h << ":" << m << ":" << sec;
			sec++;
			if (sec == 60) {
				m++;
				sec = 0;
				if (m == 59) {
					h++;
					m = 0;
					if (h == 24) {
						h = 0;
					}
				}
			}
			gotoRowCol(68, 0);
			SetClr(15);
			cout << "\nLevel: " << x;
			if (_kbhit()) {
				ch = _getch();
				//cout << "key pressed " << ch << " has ascii value " << int(ch) << endl;
				if (ch == -32) {
					ch = _getch();
					changeDirection(s[0], ch);
				}
			}
			displaySnake(s[0], height, width);
			Sleep(100);
			eraseSnake(s[0]);
			moveSnake(s[0], height, width);
			if (s[0].score >= 5) {
				if (s[0].pS[s[0].size - 1].ci == width - 2 || s[0].pS[s[0].size - 1].ri == 1
					|| s[0].pS[s[0].size - 1].ri == height - 2 || s[0].pS[s[0].size - 1].ci == 1) {
					printbox1(height, width);
				}
			}
			//time based food
		/*	if (sec == 59) {
				system("cls");
				gotoRowCol(66, 0);
				SetClr(15);
				cout << "Score ";
				cout << s[0].score;
				generateFood(f, height, width, s[0]);
				displayFood(f);
			}*/
			if (foodIsEaten(s[0], f)) {
				generateFood(f, height, width, s[0]);
				displayFood(f);
				expandSnake(s[0]);
				gotoRowCol(66, 0);
				SetClr(15);
				cout << "Score ";
				s[0].score++;
				cout << s[0].score;
				if (s[0].score == 5) {
					printbox1(60, 80);
					x++;
				}
				if (s[0].score == 10) {
					gotoRowCol(67, 0);
					SetClr(15);
					cout << "\nLevel up.... Don't touch the walls " << endl;
					x++;
				}
			}
			if (s[0].score >= 10) {
				if (s[0].pS[0].ci == width || s[0].pS[0].ri == height
					|| s[0].pS[0].ri == 0 || s[0].pS[0].ci == 0) {
					break;
				}
			}
			if (s[0].score == 15) {
				gotoRowCol(67, 0);
				SetClr(15);
				cout << "\nLevel up.... Don't touch the walls and hurdle" << endl;
				drawbox2(25, 34, 10, 0, 9);
			}
			if (s[0].score >= 15) {
				//drawbox2(25, 34, 10, 0, 9);
				if (s[0].pS[0].ri == 25 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 26 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 27 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 28 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 29 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 30 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 31 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 32 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 33 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 34 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 35 && s[0].pS[0].ci == 35) {
					break;
				}
			}
			if (killSnake(s[0]) == true) {
				break;
			}
			if (s[0].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "YOU WIN THE GAME :) " << endl;
				break;
			}
		}
		//gotoRowCol(69, 0);
		//cout << "GAME OVER !!!" << endl;
		if (s[0].score != 20) {
			system("cls");
			char a = -37;
			cout << endl << endl << endl;
			cout << "-------------------------------------------------------";
			cout << "\n|" << a << a << a << a << " " << a << a << a << " " << a << "\\   /" << a << " " << a << a << a
				<< "     " << a << a << a << " " << a << "        " << a << " " << a << a << a << " "
				<< a << a << a << a << "     |" << endl;

			cout << "|" << a << "    " << a << " " << a << " " << a << " " << a << " " << a << " " << a << " " << a <<
				"       " << a << " " << a << "  " << a << "      " << a << "  " << a << "   "
				<< a << "  " << a << "     |" << endl;

			cout << "|" << a << "    " << a << a << a << " " << a << "  " << a << "  " << a << " " << a << a << a <<
				"     " << a << " " << a << "   " << a << "    " << a << "   " << a << a << a << " "
				<< a << a << a << a << "     |" << endl;

			cout << "|" << a << "  " << a << " " << a << " " << a << " " << a << "     " << a << " " << a <<
				"       " << a << " " << a << "    " << a << "  " << a << "    " << a << "   "
				<< a << a << "       |" << endl;

			cout << "|" << a << a << a << a << " " << a << " " << a << " " << a << "     " << a << " " << a << a << a << "     "
				<< a << a << a << "     " << a << a << "     " << a << a << a << " " << a << " " << a << "      |" << endl;
			cout << "-------------------------------------------------------";

			cout << endl << endl << endl;
		}
		else {
			char a = -37;
			cout << endl << endl << endl;
			cout << "-------------------------------------------------------";
			cout << "\n|" << a << a << a << a << " " << a << a << a << " " << a << "\\   /" << a << " " << a << a << a
				<< "     " << a << a << a << " " << a << "        " << a << " " << a << a << a << " "
				<< a << a << a << a << "     |" << endl;

			cout << "|" << a << "    " << a << " " << a << " " << a << " " << a << " " << a << " " << a << " " << a <<
				"       " << a << " " << a << "  " << a << "      " << a << "  " << a << "   "
				<< a << "  " << a << "     |" << endl;

			cout << "|" << a << "    " << a << a << a << " " << a << "  " << a << "  " << a << " " << a << a << a <<
				"     " << a << " " << a << "   " << a << "    " << a << "   " << a << a << a << " "
				<< a << a << a << a << "     |" << endl;

			cout << "|" << a << "  " << a << " " << a << " " << a << " " << a << "     " << a << " " << a <<
				"       " << a << " " << a << "    " << a << "  " << a << "    " << a << "   "
				<< a << a << "       |" << endl;

			cout << "|" << a << a << a << a << " " << a << " " << a << " " << a << "     " << a << " " << a << a << a << "     "
				<< a << a << a << "     " << a << a << "     " << a << a << a << " " << a << " " << a << "      |" << endl;
			cout << "-------------------------------------------------------";

			cout << endl << endl << endl;
		
		}
		_getch();

	}
	if (choice == 2) {
		system("cls");
		char ch;
		food f;
		int x = 1;
		int h = 0, m = 0, sec = 0;
		initsnake1(s[0], f, height, width);
		initsnake2(s[1], f, height, width);

		displayFood(f);
		gotoRowCol(67, 0);
		SetClr(15);
		cout << "Score player 1: ";
		cout << s[0].score;
		cout << "\nScore player 2: ";
		cout << s[1].score;
		gotoRowCol(74, 0);
		SetClr(15);
		cout << "Targeted Score: 20" << endl << endl;
		cout << "Timer : " << endl;
	
		
		while (true) {
			
			gotoRowCol(77, 0);
			SetClr(15);
			cout << h << ":" << m << ":" << sec;
			sec++;
			if (sec == 60) {
				m++;
				sec = 0;
				if (m == 59) {
					h++;
					m = 0;
					if (h == 24) {
						h = 0;
					}
				}
			}
			gotoRowCol(70, 0);
			SetClr(15);
			cout << "\nLevel: " << x;
			if (_kbhit()) {
				ch = _getch();
				//cout << "key pressed " << ch << " has ascii value " << int(ch) << endl;
				if (ch == -32) {
					ch = _getch();
					changeDirection(s[0], ch);
				}
				if (ch == 97 || ch == 115 || ch == 100 || ch == 122) {
					changeDirection2(s[1], ch);
				}
			}
			displaySnake(s[0], height, width);
			displaySnake(s[1], height, width);

			Sleep(100);
			eraseSnake(s[0]);
			moveSnake(s[0], height, width);
			Sleep(1);
			eraseSnake(s[1]);
			moveSnake(s[1], height, width);
			if (s[0].score >= 5 || s[1].score >= 5) {
				if (s[0].pS[s[0].size - 1].ci == width - 2 || s[0].pS[s[0].size - 1].ri == 1
					|| s[0].pS[s[0].size - 1].ri == height - 2 || s[0].pS[s[0].size - 1].ci == 1) {
					printbox1(height, width);
				}
				if (s[1].pS[s[1].size - 1].ci == width - 2 || s[1].pS[s[1].size - 1].ri == 1
					|| s[1].pS[s[1].size - 1].ri == height - 2 || s[1].pS[s[1].size - 1].ci == 1) {
					printbox1(height, width);
				}
			}

			if (foodIsEaten(s[0], f)) {
				generateFood(f, height, width, s[1]);
				displayFood(f);
				expandSnake(s[0]);
				gotoRowCol(67, 0);
				SetClr(15);
				cout << "Score player 1: ";
				s[0].score++;
				cout << s[0].score;
				if (s[0].score == 5 || (s[1].score == 5)) {
					printbox1(60, 80);
					x++;
				}
				if (s[0].score == 10 || (s[1].score == 10)) {
					gotoRowCol(71, 0);
					SetClr(15);
					cout << "\nLevel up.... Don't touch the walls " << endl;
					x++;
				}
			}
			if (foodIsEaten(s[1], f)) {
				generateFood(f, height, width, s[1]);
				displayFood(f);
				expandSnake(s[1]);
				gotoRowCol(68, 0);
				SetClr(15);
				cout << "Score player 2: ";
				s[1].score++;
				cout << s[1].score;

			}
			if (s[0].score >= 10 || s[1].score >= 10) {
				if (s[0].pS[0].ci == width || s[0].pS[0].ri == height
					|| s[0].pS[0].ri == 0 || s[0].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 2 is winner..." << endl;
					break;
				}
				if (s[1].pS[0].ci == width || s[1].pS[0].ri == height
					|| s[1].pS[0].ri == 0 || s[1].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 1 is winner..." << endl;
					break;
				}
			}
			if (s[0].score == 15 || s[1].score == 15) {
				gotoRowCol(71, 0);
				SetClr(15);
				cout << "\nLevel up.... Don't touch the walls and hurdle" << endl;
				drawbox2(25, 34, 10, 0, 9);
			}
			if (s[0].score >= 15 || s[1].score == 15) {
				//drawbox2(25, 34, 10, 0, 9);
				if (s[0].pS[0].ri == 25 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 26 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 27 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 28 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 29 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 30 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 31 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 32 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 33 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 34 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 35 && s[0].pS[0].ci == 35 ||
					
					s[1].pS[0].ri == 25 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 26 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 27 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 28 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 29 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 30 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 31 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 32 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 33 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 34 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 35 && s[1].pS[0].ci == 35) {
					system("cls");
					break;
				}
			}
			if (killSnake(s[0]) == true) {
				system("cls");
				cout << "\nPlayer 2 is winner..." << endl;
				break;
			}
			if (killSnake(s[1]) == true) {
				system("cls");
				cout << "\nPlayer 1 is winner..." << endl;
				break;
			}
			if (snakekilling(s[0], s[1]) == true) {
				break;
			}
			if (s[0].score == 20 ) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 1 WIN THE GAME :) " << endl;
				break;
			}
			if (s[1].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 2 WIN THE GAME :) " << endl;
				break;
			}


		}

		//	system("cls");
			//gotoRowCol(69, 0);
			//cout << "GAME OVER !!!" << endl;

		char a = -37;
		cout << endl << endl << endl;
		cout << "-------------------------------------------------------";
		cout << "\n|" << a << a << a << a << " " << a << a << a << " " << a << "\\   /" << a << " " << a << a << a
			<< "     " << a << a << a << " " << a << "        " << a << " " << a << a << a << " "
			<< a << a << a << a << "     |" << endl;

		cout << "|" << a << "    " << a << " " << a << " " << a << " " << a << " " << a << " " << a << " " << a <<
			"       " << a << " " << a << "  " << a << "      " << a << "  " << a << "   "
			<< a << "  " << a << "     |" << endl;

		cout << "|" << a << "    " << a << a << a << " " << a << "  " << a << "  " << a << " " << a << a << a <<
			"     " << a << " " << a << "   " << a << "    " << a << "   " << a << a << a << " "
			<< a << a << a << a << "     |" << endl;

		cout << "|" << a << "  " << a << " " << a << " " << a << " " << a << "     " << a << " " << a <<
			"       " << a << " " << a << "    " << a << "  " << a << "    " << a << "   "
			<< a << a << "       |" << endl;

		cout << "|" << a << a << a << a << " " << a << " " << a << " " << a << "     " << a << " " << a << a << a << "     "
			<< a << a << a << "     " << a << a << "     " << a << a << a << " " << a << " " << a << "      |" << endl;
		cout << "-------------------------------------------------------";

		cout << endl << endl << endl;
		_getch();

	}
	if (choice == 3) {
		system("cls");
		char ch;
		food f;
		int x = 1;
		initsnake1(s[0], f, height, width);
		initsnake2(s[1], f, height, width);
		initsnake3(s[2], f, height, width);
		int h = 0, m = 0, sec = 0;
		displayFood(f);
		gotoRowCol(68, 0);
		SetClr(15);
		cout << "Score player 1: ";
		cout << s[0].score;
		cout << "\nScore player 2: ";
		cout << s[1].score;
		cout << "\nScore player 3: ";
		cout << s[2].score;
		gotoRowCol(76, 0);
		SetClr(15);
		cout << "Targeted Score: 20" << endl << endl;
		cout << "Timer : " << endl;

		while (true) {
			gotoRowCol(79, 0);
			SetClr(15);
			cout << h << ":" << m << ":" << sec;
			sec++;
			if (sec == 60) {
				m++;
				sec = 0;
				if (m == 59) {
					h++;
					m = 0;
					if (h == 24) {
						h = 0;
					}
				}
			}
			gotoRowCol(71, 0);
			SetClr(15);
			cout << "\nLevel: " << x;
			if (_kbhit()) {
				ch = _getch();
				//cout << "key pressed " << ch << " has ascii value " << int(ch) << endl;
				if (ch == -32) {
					ch = _getch();
					changeDirection(s[0], ch);
				}
				if (ch == 97 || ch == 115 || ch == 100 || ch == 122) {
					changeDirection2(s[1], ch);

				}
				if (ch == 98 || ch == 106 || ch == 104 || ch == 103) {
					changeDirection3(s[2], ch);

				}
			}
			displaySnake(s[0], height, width);
			displaySnake(s[1], height, width);
			displaySnake(s[2], height, width);

			Sleep(100);
			eraseSnake(s[0]);
			moveSnake(s[0], height, width);
			Sleep(1);
			eraseSnake(s[1]);
			moveSnake(s[1], height, width);
			Sleep(1);
			eraseSnake(s[2]);
			moveSnake(s[2], height, width);
			if (s[0].score >= 5 || s[1].score >= 5 || s[2].score >= 5) {
				if (s[0].pS[s[0].size - 1].ci == width - 2 || s[0].pS[s[0].size - 1].ri == 1
					|| s[0].pS[s[0].size - 1].ri == height - 2 || s[0].pS[s[0].size - 1].ci == 1) {
					printbox1(height, width);
				}
				if (s[1].pS[s[1].size - 1].ci == width - 2 || s[1].pS[s[1].size - 1].ri == 1
					|| s[1].pS[s[1].size - 1].ri == height - 2 || s[1].pS[s[1].size - 1].ci == 1) {
					printbox1(height, width);
				}
				if (s[2].pS[s[2].size - 1].ci == width - 2 || s[2].pS[s[2].size - 1].ri == 1
					|| s[2].pS[s[2].size - 1].ri == height - 2 || s[2].pS[s[2].size - 1].ci == 1) {
					printbox1(height, width);
				}
			}

			if (foodIsEaten(s[0], f)) {
				generateFood(f, height, width, s[0]);
				displayFood(f);
				expandSnake(s[0]);
				gotoRowCol(68, 0);
				SetClr(15);
				cout << "Score player 1: ";
				s[0].score++;
				cout << s[0].score;
				if (s[0].score == 5 || (s[1].score == 5) || s[2].score == 5) {
					printbox1(60, 80);
					x++;
					gotoRowCol(71, 0);
					SetClr(15);
					cout << "\nLevel: " << x;
				}
				if (s[0].score == 10 || (s[1].score == 10) || s[2].score == 10) {
					gotoRowCol(72, 0);
					SetClr(15);
					cout << "\nLevel up.... Don't touch the walls " << endl;
					x++;
					
				}

			}
			if (foodIsEaten(s[1], f)) {
				generateFood(f, height, width, s[1]);
				displayFood(f);
				expandSnake(s[1]);
				gotoRowCol(69, 0);
				SetClr(15);
				cout << "Score player 2: ";
				s[1].score++;
				cout << s[1].score;

			}
			if (foodIsEaten(s[2], f)) {
				generateFood(f, height, width, s[2]);
				displayFood(f);
				expandSnake(s[2]);
				gotoRowCol(70, 0);
				SetClr(15);
				cout << "Score player 3: ";
				s[2].score++;
				cout << s[2].score;

			}
			if (s[0].score >= 10 || s[1].score >= 10 || s[2].score >= 10) {
				if (s[0].pS[0].ci == width || s[0].pS[0].ri == height
					|| s[0].pS[0].ri == 0 || s[0].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 2 and 3 is winner..." << endl;
					break;
				}
				if (s[1].pS[0].ci == width || s[1].pS[0].ri == height
					|| s[1].pS[0].ri == 0 || s[1].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 1 and 3 is winner..." << endl;
					break;
				}
				if (s[2].pS[0].ci == width || s[2].pS[0].ri == height
					|| s[2].pS[0].ri == 0 || s[2].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 1 and 2 is winner..." << endl;
					break;
				}
			}
			if (s[0].score == 15 || s[1].score == 15 || s[2].score == 15) {
				gotoRowCol(72, 0);
				SetClr(15);
				cout << "\nLevel up.... Don't touch the walls and hurdle" << endl;
				drawbox2(25, 34, 10, 0, 9);
			}
			if (s[0].score >= 15 || s[1].score == 15 || s[2].score == 15) {
				//drawbox2(25, 34, 10, 0, 9);
				if (s[0].pS[0].ri == 25 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 26 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 27 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 28 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 29 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 30 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 31 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 32 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 33 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 34 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 35 && s[0].pS[0].ci == 35 ||
					
					s[1].pS[0].ri == 25 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 26 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 27 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 28 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 29 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 30 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 31 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 32 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 33 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 34 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 35 && s[1].pS[0].ci == 35 ||
					
					s[2].pS[0].ri == 25 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 26 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 27 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 28 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 29 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 30 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 31 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 32 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 33 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 34 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 35 && s[2].pS[0].ci == 35) {
					system("cls");
					break;
				}
			}

			if (killSnake(s[0]) == true) {
				system("cls");
				cout << "\nPlayer 2 and 3 is winner..." << endl;
				break;
			}
			if (killSnake(s[1]) == true) {
				system("cls");
				cout << "\nPlayer 1 and 3 is winner..." << endl;
				break;
			}
			if (killSnake(s[2]) == true) {
				system("cls");
				cout << "\nPlayer 1 and 2 is winner..." << endl;
				break;
			}
			if (snakekilling2(s[0], s[1],s[2]) == true) {
				break;
			}

			if (s[0].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 1 WIN THE GAME :) " << endl;
				break;
			}
			if (s[1].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 2 WIN THE GAME :) " << endl;
				break;
			}
			if (s[2].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 3 WIN THE GAME :) " << endl;
				break;
			}
		}

		char a = -37;
		cout << endl << endl << endl;
		cout << "-------------------------------------------------------";
		cout << "\n|" << a << a << a << a << " " << a << a << a << " " << a << "\\   /" << a << " " << a << a << a
			<< "     " << a << a << a << " " << a << "        " << a << " " << a << a << a << " "
			<< a << a << a << a << "     |" << endl;

		cout << "|" << a << "    " << a << " " << a << " " << a << " " << a << " " << a << " " << a << " " << a <<
			"       " << a << " " << a << "  " << a << "      " << a << "  " << a << "   "
			<< a << "  " << a << "     |" << endl;

		cout << "|" << a << "    " << a << a << a << " " << a << "  " << a << "  " << a << " " << a << a << a <<
			"     " << a << " " << a << "   " << a << "    " << a << "   " << a << a << a << " "
			<< a << a << a << a << "     |" << endl;

		cout << "|" << a << "  " << a << " " << a << " " << a << " " << a << "     " << a << " " << a <<
			"       " << a << " " << a << "    " << a << "  " << a << "    " << a << "   "
			<< a << a << "       |" << endl;

		cout << "|" << a << a << a << a << " " << a << " " << a << " " << a << "     " << a << " " << a << a << a << "     "
			<< a << a << a << "     " << a << a << "     " << a << a << a << " " << a << " " << a << "      |" << endl;
		cout << "-------------------------------------------------------";

		cout << endl << endl << endl;
		_getch();

	}
	if (choice == 4) {
		system("cls");
		char ch;
		food f;
		int x = 1;
		initsnake1(s[0], f, height, width);
		initsnake2(s[1], f, height, width);
		initsnake3(s[2], f, height, width);
		initsnake4(s[3], f, height, width);
		int h = 0, m = 0, sec = 0;
		displayFood(f);
		gotoRowCol(69, 0);
		SetClr(15);
		cout << "Score player 1: ";
		cout << s[0].score;
		cout << "\nScore player 2: ";
		cout << s[1].score;
		cout << "\nScore player 3: ";
		cout << s[2].score;
		cout << "\nScore player 4: ";
		cout << s[3].score;
		gotoRowCol(77, 0);
		SetClr(15);
		cout << "Targeted Score: 20" << endl << endl;
		cout << "Timer : " << endl;

		while (true) {
			gotoRowCol(80, 0);
			SetClr(15);
			cout << h << ":" << m << ":" << sec;
			sec++;
			if (sec == 60) {
				m++;
				sec = 0;
				if (m == 59) {
					h++;
					m = 0;
					if (h == 24) {
						h = 0;
					}
				}
			}
			gotoRowCol(73, 0);
			SetClr(15);
			cout << "\nLevel: " << x;
			if (_kbhit()) {
				ch = _getch();
				//cout << "key pressed " << ch << " has ascii value " << int(ch) << endl;
				if (ch == -32) {
					ch = _getch();
					changeDirection(s[0], ch);
				}
				if (ch == 97 || ch == 115 || ch == 100 || ch == 122) {
					changeDirection2(s[1], ch);

				}
				if (ch == 98 || ch == 106 || ch == 104 || ch == 103) {
					changeDirection3(s[2], ch);
				}
				if (ch == 120 || ch == 102 || ch == 99 || ch == 118) {
					changeDirection4(s[3], ch);

				}
			}
			displaySnake(s[0], height, width);
			displaySnake(s[1], height, width);
			displaySnake(s[2], height, width);
			displaySnake(s[3], height, width);

			Sleep(100);
			eraseSnake(s[0]);
			moveSnake(s[0], height, width);
			Sleep(1);
			eraseSnake(s[1]);
			moveSnake(s[1], height, width);
			Sleep(1);
			eraseSnake(s[2]);
			moveSnake(s[2], height, width);
			Sleep(1);
			eraseSnake(s[3]);
			moveSnake(s[3], height, width);

			if (s[0].score >= 5 || s[1].score >= 5 || s[2].score >= 5 || s[3].score >= 5) {
				if (s[0].pS[s[0].size - 1].ci == width - 2 || s[0].pS[s[0].size - 1].ri == 1
					|| s[0].pS[s[0].size - 1].ri == height - 2 || s[0].pS[s[0].size - 1].ci == 1) {
					printbox1(height, width);
				}
				if (s[1].pS[s[1].size - 1].ci == width - 2 || s[1].pS[s[1].size - 1].ri == 1
					|| s[1].pS[s[1].size - 1].ri == height - 2 || s[1].pS[s[1].size - 1].ci == 1) {
					printbox1(height, width);
				}
				if (s[2].pS[s[2].size - 1].ci == width - 2 || s[2].pS[s[2].size - 1].ri == 1
					|| s[2].pS[s[2].size - 1].ri == height - 2 || s[2].pS[s[2].size - 1].ci == 1) {
					printbox1(height, width);
				}
				if (s[3].pS[s[3].size - 1].ci == width - 2 || s[3].pS[s[3].size - 1].ri == 1
					|| s[3].pS[s[3].size - 1].ri == height - 2 || s[3].pS[s[3].size - 1].ci == 1) {
					printbox1(height, width);
				}
			}

			if (foodIsEaten(s[0], f)) {
				generateFood(f, height, width, s[0]);
				displayFood(f);
				expandSnake(s[0]);
				gotoRowCol(69, 0);
				SetClr(15);
				cout << "Score player 1: ";
				s[0].score++;
				cout << s[0].score;
				if (s[0].score == 5 || (s[1].score == 5) || s[2].score == 5 || s[3].score == 5) {
					printbox1(60, 80);
					x++;
					gotoRowCol(73, 0);
					SetClr(15);
					cout << "\nLevel: " << x;
				}
				if (s[0].score == 10 || (s[1].score == 10) || s[2].score == 10 || s[3].score == 10) {
					gotoRowCol(74, 0);
					SetClr(15);
					cout << "\nLevel up.... Don't touch the walls " << endl;
					x++;

				}

			}
			if (foodIsEaten(s[1], f)) {
				generateFood(f, height, width, s[1]);
				displayFood(f);
				expandSnake(s[1]);
				gotoRowCol(70, 0);
				SetClr(15);
				cout << "Score player 2: ";
				s[1].score++;
				cout << s[1].score;

			}
			if (foodIsEaten(s[2], f)) {
				generateFood(f, height, width, s[2]);
				displayFood(f);
				expandSnake(s[2]);
				gotoRowCol(71, 0);
				SetClr(15);
				cout << "Score player 3: ";
				s[2].score++;
				cout << s[2].score;
			}
			if (foodIsEaten(s[3], f)) {
				generateFood(f, height, width, s[3]);
				displayFood(f);
				expandSnake(s[3]);
				gotoRowCol(72, 0);
				SetClr(15);
				cout << "Score player 4: ";
				s[3].score++;
				cout << s[3].score;

			}
			if (s[0].score >= 10 || s[1].score >= 10 || s[2].score >= 10 || s[3].score >= 10) {
				if (s[0].pS[0].ci == width || s[0].pS[0].ri == height
					|| s[0].pS[0].ri == 0 || s[0].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 2,3 and 4 is winner..." << endl;
					break;
				}
				if (s[1].pS[0].ci == width || s[1].pS[0].ri == height
					|| s[1].pS[0].ri == 0 || s[1].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 1,3 and 4 is winner..." << endl;
					break;
				}
				if (s[2].pS[0].ci == width || s[2].pS[0].ri == height
					|| s[2].pS[0].ri == 0 || s[2].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 1,2 and 4 is winner..." << endl;
					break;
				}
				if (s[3].pS[0].ci == width || s[3].pS[0].ri == height
					|| s[3].pS[0].ri == 0 || s[3].pS[0].ci == 0) {
					system("cls");
					cout << "\nPlayer 1,2 and 3 is winner..." << endl;
					break;
				}

			}

			if (s[0].score == 15 || s[1].score == 15 || s[2].score == 15 || s[3].score == 15) {
				gotoRowCol(74, 0);
				SetClr(15);
				cout << "\nLevel up.... Don't touch the walls and hurdle" << endl;
				drawbox2(25, 34, 10, 0, 9);
			}
			if (s[0].score >= 15 || s[1].score == 15 || s[2].score == 15 || s[3].score == 15) {
				//drawbox2(25, 34, 10, 0, 9);
				if (s[0].pS[0].ri == 25 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 26 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 27 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 28 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 29 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 30 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 31 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 32 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 33 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 34 && s[0].pS[0].ci == 35 ||
					s[0].pS[0].ri == 35 && s[0].pS[0].ci == 35 ||


					s[1].pS[0].ri == 25 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 26 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 27 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 28 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 29 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 30 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 31 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 32 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 33 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 34 && s[1].pS[0].ci == 35 ||
					s[1].pS[0].ri == 35 && s[1].pS[0].ci == 35 ||

					s[2].pS[0].ri == 25 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 26 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 27 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 28 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 29 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 30 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 31 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 32 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 33 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 34 && s[2].pS[0].ci == 35 ||
					s[2].pS[0].ri == 35 && s[2].pS[0].ci == 35 ||
					
					s[3].pS[0].ri == 25 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 26 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 27 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 28 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 29 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 30 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 31 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 32 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 33 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 34 && s[3].pS[0].ci == 35 ||
					s[3].pS[0].ri == 35 && s[3].pS[0].ci == 35) {
					system("cls");
					break;
				}
			}



			if (killSnake(s[0]) == true) {
				system("cls");
				cout << "\nPlayer 2,3 and 4 is winner..." << endl;
				break;
			}
			if (killSnake(s[1]) == true) {
				system("cls");
				cout << "\nPlayer 1,3 and 4 is winner..." << endl;
				break;
			}
			if (killSnake(s[2]) == true) {
				system("cls");
				cout << "\nPlayer 1,2 and 4 is winner..." << endl;
				break;
			}
			if (killSnake(s[3]) == true) {
				system("cls");
				cout << "\nPlayer 1,2 and 3 is winner..." << endl;
				break;
			}
			if (snakekilling3(s[0], s[1], s[2],s[3]) == true) {
				break;
			}
			if (s[0].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 1 WIN THE GAME :) " << endl;
				break;
			}
			if (s[1].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 2 WIN THE GAME :) " << endl;
				break;
			}
			if (s[2].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 3 WIN THE GAME :) " << endl;
				break;
			}
			if (s[3].score == 20) {
				system("cls");
				SetClr(15);
				cout << "YOU REACHED THE TARGETED SCORE......" << endl;
				cout << "PLAYER 4 WIN THE GAME :) " << endl;
				break;
			}
		}

		char a = -37;
		cout << endl << endl << endl;
		cout << "-------------------------------------------------------";
		cout << "\n|" << a << a << a << a << " " << a << a << a << " " << a << "\\   /" << a << " " << a << a << a
			<< "     " << a << a << a << " " << a << "        " << a << " " << a << a << a << " "
			<< a << a << a << a << "     |" << endl;

		cout << "|" << a << "    " << a << " " << a << " " << a << " " << a << " " << a << " " << a << " " << a <<
			"       " << a << " " << a << "  " << a << "      " << a << "  " << a << "   "
			<< a << "  " << a << "     |" << endl;

		cout << "|" << a << "    " << a << a << a << " " << a << "  " << a << "  " << a << " " << a << a << a <<
			"     " << a << " " << a << "   " << a << "    " << a << "   " << a << a << a << " "
			<< a << a << a << a << "     |" << endl;

		cout << "|" << a << "  " << a << " " << a << " " << a << " " << a << "     " << a << " " << a <<
			"       " << a << " " << a << "    " << a << "  " << a << "    " << a << "   "
			<< a << a << "       |" << endl;

		cout << "|" << a << a << a << a << " " << a << " " << a << " " << a << "     " << a << " " << a << a << a << "     "
			<< a << a << a << "     " << a << a << "     " << a << a << a << " " << a << " " << a << "      |" << endl;
		cout << "-------------------------------------------------------";

		cout << endl << endl << endl;
		_getch();

	}

	//return 0;
}


