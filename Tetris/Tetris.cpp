
/* Программа реализует игру тетрис на консоли. 
В данной реализации:
   - можно 
         перемещать фигуру влево/вправо по мере ее падения, 
		 увеличивать скорость падение фигуры, 
		 переворачивать фигуру
   - если собирается непрерывная линия из крестиков, совпадающая с шириной поля, линия исчезает
   - с течением времени скорость падения фигур увеличивается
   - игра завершается (проигрыш), если ваше построение из фигур достигло максимально возможной высоты
   - игру можно завершить самому в любой момент
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <ctime>	

using namespace std;

const int n = 12;
const int m = 22;
const char line = '.';
const char el_fig = 'x';

class Tetris
{
	char **pole;
	int score;
	int a;
	int b;
	int c;
	int d;
	int e;
	int view;
public:
	Tetris()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		view = 0;
		score = 0;
		pole = new char*[m];
		for (int i = 0; i < m; i++)
			pole[i] = new char[n];
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				pole[i][j] = line;
		for (int i = 0; i < m; i++)
		{
			pole[i][0] = '|';
			pole[i][n - 1] = '|';
		}
		for (int j = 0; j < n; j++)
		{
			pole[0][j] = '_';
			pole[m - 1][j] = '_';
		}
	}
	~Tetris()
	{
		for (int i = 0; i < m; i++)
			delete pole[i];
		delete[]pole;
	}

	void fast(int count);   
	void output();           
	void end();
	void game();
	void begin();
	void kvadr(int count);
	void linee(int count);
	void sered(int count);
	void ugol_1(int count);
	void ugol_2(int count);
	void zigzag_1(int count);
};
                            // увеличение скорости падения фигуры
void Tetris:: fast(int count)
{
	if (count <= 10)
	{
		Sleep(500);
	}
	else if (10 < count <= 20)
	{
		Sleep(350);
	}
	else if (20 < count <= 30)
	{
		Sleep(200);
	}
	else if (30 < count <= 40)
	{
		Sleep(50);
	}
	else if (40 < count)
	{
		Sleep(25);
	}
}
                            // вывод поля и текущих очков
void Tetris:: output()
{
	system("cls");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << setw(2) << pole[i][j];
		cout << endl;
	}
	cout << endl << endl << "   ОЧКИ: " << score << endl;
}
                            // завершение игры
void Tetris:: end()
{
	system("cls");
	cout << endl << endl << endl << endl << endl << "              ВЫ ЗАВЕРШИЛИ ИГРУ :)" << endl << endl;
	cout << endl << endl << endl << endl << endl << "                  ваши очки: " << score << endl << endl << endl << endl << endl;
	exit(0);
}

                            /* методы для фигур (квадрат, линия, два вида углов, зигзаг и пирамидка)
                               для каждой фигуры в зависимости от нажатой клавиши 
							   прописаны возможные положения появления и при повороте, а так же возможности перемещения
							*/
void Tetris:: kvadr(int count)
{
	a = 1, b = 5, c = 2, d = 6;
	pole[a][b] = el_fig;
	pole[a][d] = el_fig;
	pole[c][b] = el_fig;
	pole[c][d] = el_fig;
	output();
	while (true)
	{
		while (!_kbhit())
		{
			fast(count);
			pole[a][b] = line;
			pole[a][d] = line;
			a++;
			c++;
			pole[c][b] = el_fig;
			pole[c][d] = el_fig;
			output();
			if (c == m - 2 || pole[c + 1][b] == el_fig || pole[c + 1][d] == el_fig)
				break;
		}
		if (c == m - 2 || pole[c + 1][b] == el_fig || pole[c + 1][d] == el_fig)
			break;
		int moove;
		moove = _getch();
		switch (moove)
		{
		case 80:
			pole[a][b] = line;
			pole[a][d] = line;
			a++;
			c++;
			pole[c][b] = el_fig;
			pole[c][d] = el_fig;
			output();
			break;
		case 75:
			if (b - 1 == 0 || pole[c][b - 1] == el_fig)
				break;
			pole[a][d] = line;
			pole[c][d] = line;
			d = b;
			b--;
			pole[a][b] = el_fig;
			pole[c][b] = el_fig;
			output();
			break;
		case 77:
			if (d + 1 == n - 1 || pole[c][d + 1] == el_fig)
				break;
			pole[a][b] = line;
			pole[c][b] = line;
			b = d;
			d++;
			pole[a][d] = el_fig;
			pole[c][d] = el_fig;
			output();
			break;
		case 27:
			end();
			return;
			break;
		}

		if (c == m - 2 || pole[c + 1][b] == el_fig || pole[c + 1][d] == el_fig)
			break;

	}
}
void Tetris:: linee(int count)
{
	a = 1, b = 2, c = 3, d = 4, e = 5;
	pole[a][e] = el_fig;
	pole[b][e] = el_fig;
	pole[c][e] = el_fig;
	pole[d][e] = el_fig;
	output();
	view = 1;
	while (true)
	{
		while (!_kbhit())
		{
			fast(count);
			if (view)
			{
				pole[a][e] = line;
				a++;
				b++;
				c++;
				d++;
				pole[d][e] = el_fig;
				output();
			}
			else
			{
				pole[e][a] = line;
				pole[e][b] = line;
				pole[e][c] = line;
				pole[e][d] = line;
				e++;
				pole[e][a] = el_fig;
				pole[e][b] = el_fig;
				pole[e][c] = el_fig;
				pole[e][d] = el_fig;
				output();
			}
			if ((view && d == m - 2) || (!view && e == m - 2) || (view && pole[d + 1][e] == el_fig) || (!view && (pole[e + 1][a] == el_fig || pole[e + 1][b] == el_fig || pole[e + 1][c] == el_fig || pole[e + 1][d] == el_fig)))
				break;
		}
		if ((view && d == m - 2) || (!view && e == m - 2) || (view && pole[d + 1][e] == el_fig) || (!view && (pole[e + 1][a] == el_fig || pole[e + 1][b] == el_fig || pole[e + 1][c] == el_fig || pole[e + 1][d] == el_fig)))
			break;
		int moove;
		moove = _getch();
		if (view)
		{
			switch (moove)
			{
			case 80:
				pole[a][e] = line;
				a++;
				b++;
				c++;
				d++;
				pole[d][e] = el_fig;
				output();
				break;
			case 75:
				if (pole[a][e - 1] == el_fig || pole[b][e - 1] == el_fig || pole[c][e - 1] == el_fig || pole[d][e - 1] == el_fig || e - 1 == 0)
					break;
				pole[a][e] = line;
				pole[b][e] = line;
				pole[c][e] = line;
				pole[d][e] = line;
				e--;
				pole[a][e] = el_fig;
				pole[b][e] = el_fig;
				pole[c][e] = el_fig;
				pole[d][e] = el_fig;
				output();
				break;
			case 77:
				if (pole[a][e + 1] == el_fig || pole[b][e + 1] == el_fig || pole[c][e + 1] == el_fig || pole[d][e + 1] == el_fig || e + 1 == n - 1)
					break;
				pole[a][e] = line;
				pole[b][e] = line;
				pole[c][e] = line;
				pole[d][e] = line;
				e++;
				pole[a][e] = el_fig;
				pole[b][e] = el_fig;
				pole[c][e] = el_fig;
				pole[d][e] = el_fig;
				output();
				break;
			case 32:
				if (pole[a][e - 1] != el_fig&&e - 1 != 0 && pole[a][e + 1] != el_fig&&e + 1 != n - 1 && pole[a][e + 2] != el_fig&&e + 2 != n - 1)
				{
					pole[a][e] = line;
					pole[b][e] = line;
					pole[c][e] = line;
					pole[d][e] = line;
					int q = a;
					a = e - 1;
					b = e;
					c = e + 1;
					d = e + 2;
					e = q;
					pole[e][a] = el_fig;
					pole[e][b] = el_fig;
					pole[e][c] = el_fig;
					pole[e][d] = el_fig;
					view = 0;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else
		{
			switch (moove)
			{
			case 80:
				pole[e][a] = line;
				pole[e][b] = line;
				pole[e][c] = line;
				pole[e][d] = line;
				e++;
				pole[e][a] = el_fig;
				pole[e][b] = el_fig;
				pole[e][c] = el_fig;
				pole[e][d] = el_fig;
				output();
				break;
			case 75:
				if (pole[e][a - 1] == el_fig || a - 1 == 0)
					break;
				pole[e][d] = line;
				a--;
				b--;
				c--;
				d--;
				pole[e][a] = el_fig;
				output();
				break;
			case 77:
				if (pole[e][d + 1] == el_fig || d + 1 == n - 1)
					break;
				pole[e][a] = line;
				a++;
				b++;
				c++;
				d++;
				pole[e][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[e + 2][b] != el_fig&&e + 2 != m - 1 && pole[e + 3][b] != el_fig&&e + 3 != m - 1)
				{
					pole[e][a] = line;
					pole[e][b] = line;
					pole[e][c] = line;
					pole[e][d] = line;
					int q = b;
					a = e;
					b = a + 1;
					c = a + 2;
					d = a + 3;
					e = q;
					pole[a][e] = el_fig;
					pole[b][e] = el_fig;
					pole[c][e] = el_fig;
					pole[d][e] = el_fig;
					view = 1;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}

		}
		if ((view && d == m - 2) || (!view && e == m - 2) || (view && pole[d + 1][e] == el_fig) || (!view && (pole[e + 1][a] == el_fig || pole[e + 1][b] == el_fig || pole[e + 1][c] == el_fig || pole[e + 1][d] == el_fig)))
			break;
	}
}
void Tetris:: sered(int count)
{
	a = 1; b = 4;
	c = 2; d = 5; e = 6;
	pole[a][d] = el_fig;
	pole[c][d] = el_fig;
	pole[c][b] = el_fig;
	pole[c][e] = el_fig;
	view = 1;
	output();
	while (true)
	{
		while (!_kbhit())
		{
			fast(count);
			if (view == 1)
			{
				pole[a][d] = line;
				a++;
				c++;
				pole[a][b] = line;
				pole[a][e] = line;
				pole[c][b] = el_fig;
				pole[c][d] = el_fig;
				pole[c][e] = el_fig;
				output();
			}
			else if (view == 2)
			{
				pole[a][d] = line;
				pole[b][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[b][e] = el_fig;
				output();
			}
			else if (view == 3)
			{
				pole[d][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				d++;
				e++;
				pole[d][a] = el_fig;
				pole[d][c] = el_fig;
				pole[e][b] = el_fig;
				output();
			}
			else if (view == 4)
			{
				pole[a][d] = line;
				pole[b][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[b][e] = el_fig;
				output();
			}
			if ((view == 1 && (c + 1 == m - 1 || pole[c + 1][b] == el_fig || pole[c + 1][d] == el_fig || pole[c + 1][e] == el_fig)) ||
				(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig)) ||
				(view == 3 && (e + 1 == m - 1 || pole[e + 1][b] == el_fig)) ||
				(view == 4 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig))) break;
		}
		if ((view == 1 && (c + 1 == m - 1 || pole[c + 1][b] == el_fig || pole[c + 1][d] == el_fig || pole[c + 1][e] == el_fig)) ||
			(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig)) ||
			(view == 3 && (e + 1 == m - 1 || pole[e + 1][b] == el_fig)) ||
			(view == 4 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig))) break;
		int moove;
		moove = _getch();
		if (view == 1)
		{
			switch (moove)
			{
			case 80:
				pole[a][d] = line;
				a++;
				c++;
				pole[a][b] = line;
				pole[a][e] = line;
				pole[c][b] = el_fig;
				pole[c][d] = el_fig;
				pole[c][e] = el_fig;
				output();
				break;
			case 75:
				if (b - 1 == 0 || pole[c][b - 1] == el_fig)
					break;
				pole[c][e] = line;
				pole[a][d] = line;
				b--;
				d--;
				e--;
				pole[a][d] = el_fig;
				pole[c][b] = el_fig;
				output();
				break;
			case 77:
				if (e + 1 == n - 1 || pole[c][e + 1] == el_fig)
					break;
				pole[c][b] = line;
				pole[a][d] = line;
				b++;
				d++;
				e++;
				pole[a][d] = el_fig;
				pole[c][e] = el_fig;
				output();
				break;
			case 32:
				pole[c][b] = line;
				pole[c + 1][d] = el_fig;

				b = c;
				c++;
				view = 2;
				output();
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else if (view == 2)
		{
			switch (moove)
			{
			case 80:
				pole[a][d] = line;
				pole[b][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[b][e] = el_fig;
				output();
				break;
			case 75:
				if (d - 1 == 0 || pole[a][d - 1] == el_fig || pole[b][d - 1] == el_fig || pole[c][d - 1] == el_fig)
					break;
				pole[b][e] = line;
				pole[a][d] = line;
				pole[c][d] = line;
				d--;
				e--;
				pole[a][d] = el_fig;
				pole[b][d] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 77:
				if (e + 1 == n - 1 || pole[b][e + 1] == el_fig)
					break;
				pole[b][d] = line;
				pole[a][d] = line;
				pole[c][d] = line;
				d++;
				e++;
				pole[a][d] = el_fig;
				pole[b][e] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[b][d - 1] != el_fig && d - 1 != 0)
				{
					pole[a][d] = line;
					pole[b][d - 1] = el_fig;
					a = d - 1;
					d = b;
					e = c;
					b = a + 1;
					c = a + 2;
					view = 3;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else if (view == 3)
		{
			switch (moove)
			{
			case 80:
				pole[d][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				d++;
				e++;
				pole[d][a] = el_fig;
				pole[d][c] = el_fig;
				pole[e][b] = el_fig;
				output();
				break;
			case 75:
				if (a - 1 == 0 || pole[d][a - 1] == el_fig)
					break;
				pole[d][c] = line;
				pole[e][b] = line;
				a--;
				b--;
				c--;
				pole[d][a] = el_fig;
				pole[e][b] = el_fig;
				output();
				break;
			case 77:
				if (c + 1 == n - 1 || pole[d][c + 1] == el_fig)
					break;
				pole[d][a] = line;
				pole[e][b] = line;
				a++;
				b++;
				c++;
				pole[d][c] = el_fig;
				pole[e][b] = el_fig;
				output();
				break;
			case 32:
				pole[d][c] = line;
				pole[d - 1][b] = el_fig;
				c = e;
				b = d;
				e = a;
				d = e + 1;
				a = b - 1;
				view = 4;
				output();
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else if (view == 4)
		{
			switch (moove)
			{
			case 80:
				pole[a][d] = line;
				pole[b][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[b][e] = el_fig;
				output();
				break;
			case 75:
				if (e - 1 == 0 || pole[b][e - 1] == el_fig)
					break;
				pole[a][d] = line;
				pole[b][d] = line;
				pole[c][d] = line;
				e--;
				d--;
				pole[a][d] = el_fig;
				pole[c][d] = el_fig;
				pole[b][e] = el_fig;
				output();
				break;
			case 77:
				if (d + 1 == n - 1 || pole[a][d + 1] == el_fig || pole[b][d + 1] == el_fig || pole[c][d + 1] == el_fig)
					break;
				pole[a][d] = line;
				pole[b][e] = line;
				pole[c][d] = line;
				e++;
				d++;
				pole[a][d] = el_fig;
				pole[c][d] = el_fig;
				pole[b][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[b][d + 1] != el_fig&&d + 1 != n - 1)
				{
					pole[c][d] = line;
					pole[b][d + 1] = el_fig;
					c--;
					b = e;
					e = b + 2;
					view = 1;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		if ((view == 1 && (c + 1 == m - 1 || pole[c + 1][b] == el_fig || pole[c + 1][d] == el_fig || pole[c + 1][e] == el_fig)) ||
			(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig)) ||
			(view == 3 && (e + 1 == m - 1 || pole[e + 1][b] == el_fig)) ||
			(view == 4 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig))) break;
	}
}
void Tetris:: ugol_1(int count)
{
	a = 4;
	b = 5;
	c = 6;
	d = 2;
	e = 1;
	pole[e][a] = el_fig;
	pole[d][a] = el_fig;
	pole[d][b] = el_fig;
	pole[d][c] = el_fig;
	view = 1;
	output();
	while (true)
	{
		while (!_kbhit())
		{
			fast(count);
			if (view == 1)
			{
				pole[e][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				e++;
				d++;
				pole[d][a] = el_fig;
				pole[d][b] = el_fig;
				pole[d][c] = el_fig;
				output();
			}
			else if (view == 2)
			{
				pole[a][d] = line;
				pole[a][e] = line;
				a++;
				b++;
				c++;
				pole[a][e] = el_fig;
				pole[c][d] = el_fig;
				output();
			}
			else if (view == 3)
			{
				pole[d][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				d++;
				e++;
				pole[d][a] = el_fig;
				pole[d][b] = el_fig;
				pole[e][c] = el_fig;
				output();
			}
			else if (view == 4)
			{
				pole[a][d] = line;
				pole[c][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[c][e] = el_fig;
				output();
			}
			if ((view == 1 && (d + 1 == m - 1 || pole[d + 1][a] == el_fig || pole[d + 1][b] == el_fig || pole[d + 1][c] == el_fig)) ||
				(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[b][e] == el_fig)) ||
				(view == 3 && (e + 1 == m - 1 || pole[e + 1][c] == el_fig)) ||
				(view == 4 && (c + 1 == m - 1 || pole[c + 1][e] == el_fig || pole[c + 1][d] == el_fig))) break;
		}
		if ((view == 1 && (d + 1 == m - 1 || pole[d + 1][a] == el_fig || pole[d + 1][b] == el_fig || pole[d + 1][c] == el_fig)) ||
			(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[b][e] == el_fig)) ||
			(view == 3 && (e + 1 == m - 1 || pole[e + 1][c] == el_fig)) ||
			(view == 4 && (c + 1 == m - 1 || pole[c + 1][e] == el_fig || pole[c + 1][d] == el_fig))) break;
		int moove;
		moove = _getch();
		if (view == 1)
		{
			switch (moove)
			{
			case 80:
				pole[e][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				e++;
				d++;
				pole[d][a] = el_fig;
				pole[d][b] = el_fig;
				pole[d][c] = el_fig;
				output();
				break;
			case 75:
				if (a - 1 == 0 || pole[e][a - 1] == el_fig || pole[d][a - 1] == el_fig)
					break;
				pole[e][a] = line;
				pole[d][c] = line;
				a--;
				b--;
				c--;
				pole[d][a] = el_fig;
				pole[e][a] = el_fig;
				output();
				break;
			case 77:
				if (c + 1 == n - 1 || pole[d][c + 1] == el_fig)
					break;
				pole[e][a] = line;
				pole[d][a] = line;
				a++;
				b++;
				c++;
				pole[d][c] = el_fig;
				pole[e][a] = el_fig;
				output();
				break;
			case 32:
				pole[e][a] = line;
				pole[d][a] = line;
				pole[d][c] = line;
				pole[e][b] = el_fig;
				pole[d + 1][b] = el_fig;
				pole[e][c] = el_fig;
				a = e;
				d = b;
				e = d + 1;
				c = a + 2;
				b = a + 1;
				view = 2;
				output();
				break;
			case 27:
				end();
				return;
				break;

			}
		}
		else if (view == 2)
		{
			switch (moove)
			{
			case 80:
				pole[a][d] = line;
				pole[a][e] = line;
				a++;
				b++;
				c++;
				pole[a][e] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 75:
				if (d - 1 == 0 || pole[a][d - 1] == el_fig || pole[b][d - 1] == el_fig || pole[c][d - 1] == el_fig)
					break;
				pole[a][e] = line;
				pole[b][d] = line;
				pole[c][d] = line;
				d--;
				e--;
				pole[a][d] = el_fig;
				pole[b][d] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 77:
				if (e + 1 == n - 1 || pole[a][e + 1] == el_fig)
					break;
				pole[a][d] = line;
				pole[b][d] = line;
				pole[c][d] = line;
				d++;
				e++;
				pole[a][e] = el_fig;
				pole[b][d] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[a][d - 1] != el_fig&&d - 1 != 0)
				{
					pole[a][d - 1] = el_fig;
					pole[c][d] = line;
					pole[b][d] = line;
					pole[b][d + 1] = el_fig;
					a = d - 1;
					d = b - 1;
					e = b;
					b = a + 1;
					c = b + 1;
					view = 3;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else if (view == 3)
		{
			switch (moove)
			{
			case 80:
				pole[d][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				d++;
				e++;
				pole[d][a] = el_fig;
				pole[d][b] = el_fig;
				pole[e][c] = el_fig;
				output();
				break;
			case 75:
				if (a - 1 == 0 || pole[d][a - 1] == el_fig)
					break;
				pole[d][c] = line;
				pole[e][c] = line;
				a--;
				b--;
				c--;
				pole[d][a] = el_fig;
				pole[e][c] = el_fig;
				output();
				break;
			case 77:
				if (c + 1 == n - 1 || pole[d][c + 1] == el_fig || pole[e][c + 1] == el_fig)
					break;
				pole[d][a] = line;
				pole[e][c] = line;
				a++;
				b++;
				c++;
				pole[d][c] = el_fig;
				pole[e][c] = el_fig;
				output();
				break;
			case 32:
				pole[d][a] = line;
				pole[d][c] = line;
				pole[e][c] = line;
				pole[e][b] = el_fig;
				pole[e + 1][b] = el_fig;
				pole[e + 1][a] = el_fig;
				a = d;
				d = b;
				e = d - 1;
				b = a + 1;
				c = b + 1;
				view = 4;
				output();
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else if (view == 4)
		{
			switch (moove)
			{
			case 80:
				pole[a][d] = line;
				pole[c][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[c][e] = el_fig;
				output();
				break;
			case 75:
				if (e - 1 == 0 || pole[c][e - 1] == el_fig)
					break;
				pole[a][d] = line;
				pole[b][d] = line;
				pole[c][d] = line;
				d--;
				e--;
				pole[a][d] = el_fig;
				pole[b][d] = el_fig;
				pole[c][e] = el_fig;
				output();
				break;
			case 77:
				if (d + 1 == n - 1 || pole[a][d + 1] == el_fig || pole[b][d + 1] == el_fig || pole[c][d + 1] == el_fig)
					break;
				pole[a][d] = line;
				pole[b][d] = line;
				pole[c][e] = line;
				e++;
				d++;
				pole[a][d] = el_fig;
				pole[b][d] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[b][d + 1] != el_fig&&d + 1 != n - 1)
				{
					pole[a][d] = line;
					pole[b][e] = el_fig;
					pole[a][e] = el_fig;
					pole[c][e] = line;
					pole[c][d] = line;
					pole[b][d + 1] = el_fig;
					d = b;
					a = e;
					b = a + 1;
					c = b + 1;
					e = d - 1;
					view = 1;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		if ((view == 1 && (d + 1 == m - 1 || pole[d + 1][a] == el_fig || pole[d + 1][b] == el_fig || pole[d + 1][c] == el_fig)) ||
			(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[b][e] == el_fig)) ||
			(view == 3 && (e + 1 == m - 1 || pole[e + 1][c] == el_fig || pole[e][a] == el_fig || pole[e][b] == el_fig)) ||
			(view == 4 && (c + 1 == m - 1 || pole[c + 1][e] == el_fig || pole[c + 1][d] == el_fig))) break;
	}
}
void Tetris:: ugol_2(int count)
{
	a = 4;
	b = 5;
	c = 6;
	d = 2;
	e = 1;
	pole[e][c] = el_fig;
	pole[d][a] = el_fig;
	pole[d][b] = el_fig;
	pole[d][c] = el_fig;
	view = 1;
	output();
	while (true)
	{
		while (!_kbhit())
		{
			fast(count);
			if (view == 1)
			{
				pole[e][c] = line;
				pole[d][b] = line;
				pole[d][a] = line;
				e++;
				d++;
				pole[d][a] = el_fig;
				pole[d][b] = el_fig;
				pole[d][c] = el_fig;
				output();
			}
			else if (view == 2)
			{
				pole[a][d] = line;
				pole[c][e] = line;
				a++;
				b++;
				c++;
				pole[c][e] = el_fig;
				pole[c][d] = el_fig;
				output();
			}
			else if (view == 3)
			{
				pole[d][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				d++;
				e++;
				pole[d][c] = el_fig;
				pole[d][b] = el_fig;
				pole[e][a] = el_fig;
				output();
			}
			else if (view == 4)
			{
				pole[a][d] = line;
				pole[a][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[a][e] = el_fig;
				output();
			}
			if ((view == 1 && (d + 1 == m - 1 || pole[d + 1][a] == el_fig || pole[d + 1][b] == el_fig || pole[d + 1][c] == el_fig)) ||
				(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[c + 1][e] == el_fig)) ||
				(view == 3 && (e + 1 == m - 1 || pole[e + 1][a] == el_fig || pole[e][b] == el_fig || pole[e][c] == el_fig)) ||
				(view == 4 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[b][e] == el_fig))) break;
		}
		if ((view == 1 && (d + 1 == m - 1 || pole[d + 1][a] == el_fig || pole[d + 1][b] == el_fig || pole[d + 1][c] == el_fig)) ||
			(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[c + 1][e] == el_fig)) ||
			(view == 3 && (e + 1 == m - 1 || pole[e + 1][a] == el_fig || pole[e][b] == el_fig || pole[e][c] == el_fig)) ||
			(view == 4 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[b][e] == el_fig))) break;
		int moove;
		moove = _getch();
		if (view == 1)
		{
			switch (moove)
			{
			case 80:
				pole[e][c] = line;
				pole[d][b] = line;
				pole[d][a] = line;
				e++;
				d++;
				pole[d][a] = el_fig;
				pole[d][b] = el_fig;
				pole[d][c] = el_fig;
				output();
				break;
			case 75:
				if (a - 1 == 0 || pole[d][a - 1] == el_fig)
					break;
				pole[e][c] = line;
				pole[d][c] = line;
				a--;
				b--;
				c--;
				pole[d][a] = el_fig;
				pole[e][c] = el_fig;
				output();
				break;
			case 77:
				if (c + 1 == n - 1 || pole[d][c + 1] == el_fig || pole[e][c + 1] == el_fig)
					break;
				pole[e][c] = line;
				pole[d][a] = line;
				a++;
				b++;
				c++;
				pole[d][c] = el_fig;
				pole[e][c] = el_fig;
				output();
				break;
			case 32:
				pole[d][a] = line;
				pole[d][c] = line;
				pole[e][c] = line;
				pole[e][b] = el_fig;
				pole[d + 1][b] = el_fig;
				pole[d + 1][c] = el_fig;
				a = e;
				d = b;
				e = d + 1;
				b = a + 1;
				c = b + 1;
				view = 2;
				output();
				break;
			case 27:
				end();
				return;
				break;

			}
		}
		else if (view == 2)
		{
			switch (moove)
			{
			case 80:
				pole[a][d] = line;
				pole[c][e] = line;
				a++;
				b++;
				c++;
				pole[c][e] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 75:
				if (d - 1 == 0 || pole[a][d - 1] == el_fig || pole[b][d - 1] == el_fig || pole[c][d - 1] == el_fig)
					break;
				pole[c][e] = line;
				pole[b][d] = line;
				pole[a][d] = line;
				d--;
				e--;
				pole[a][d] = el_fig;
				pole[b][d] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 77:
				if (e + 1 == n - 1 || pole[c][e + 1] == el_fig)
					break;
				pole[a][d] = line;
				pole[b][d] = line;
				pole[c][d] = line;
				d++;
				e++;
				pole[c][e] = el_fig;
				pole[b][d] = el_fig;
				pole[a][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[a][d - 1] != el_fig && pole[b][d - 1] != el_fig && d - 1 != 0)
				{
					pole[a][d - 1] = el_fig;
					pole[b][d - 1] = el_fig;
					pole[a][e] = el_fig;
					pole[b][d] = line;
					pole[c][d] = line;
					pole[c][e] = line;
					a = d - 1;
					e = b;
					d = e - 1;
					b = a + 1;
					c = b + 1;
					view = 3;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else if (view == 3)
		{
			switch (moove)
			{
			case 80:
				pole[d][a] = line;
				pole[d][b] = line;
				pole[d][c] = line;
				d++;
				e++;
				pole[d][c] = el_fig;
				pole[d][b] = el_fig;
				pole[e][a] = el_fig;
				output();
				break;
			case 75:
				if (a - 1 == 0 || pole[d][a - 1] == el_fig || pole[e][a - 1] == el_fig)
					break;
				pole[d][c] = line;
				pole[e][a] = line;
				a--;
				b--;
				c--;
				pole[e][a] = el_fig;
				pole[d][a] = el_fig;
				pole[d][c] = el_fig;
				output();
				break;
			case 77:
				if (c + 1 == n - 1 || pole[d][c + 1] == el_fig)
					break;
				pole[d][a] = line;
				pole[e][a] = line;
				a++;
				b++;
				c++;
				pole[d][c] = el_fig;
				pole[e][a] = el_fig;
				output();
				break;
			case 32:
				pole[e][a] = line;
				pole[d][c] = line;
				pole[e][b] = el_fig;
				pole[e + 1][b] = el_fig;
				a = d;
				d = b;
				e = d - 1;
				b = a + 1;
				c = b + 1;
				view = 4;
				output();
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else if (view == 4)
		{
			switch (moove)
			{
			case 80:
				pole[a][d] = line;
				pole[a][e] = line;
				a++;
				b++;
				c++;
				pole[c][d] = el_fig;
				pole[a][e] = el_fig;
				output();
				break;
			case 75:
				if (e - 1 == 0 || pole[a][e - 1] == el_fig)
					break;
				pole[a][d] = line;
				pole[b][d] = line;
				pole[c][d] = line;
				d--;
				e--;
				pole[c][d] = el_fig;
				pole[b][d] = el_fig;
				pole[a][e] = el_fig;
				output();
				break;
			case 77:
				if (d + 1 == n - 1 || pole[a][d + 1] == el_fig || pole[b][d + 1] == el_fig || pole[c][d + 1] == el_fig)
					break;
				pole[c][d] = line;
				pole[b][d] = line;
				pole[a][e] = line;
				e++;
				d++;
				pole[a][d] = el_fig;
				pole[b][d] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[a][d + 1] != el_fig && d + 1 != n - 1 && pole[b][d + 1] != el_fig)
				{
					pole[a][e] = line;
					pole[a][d] = line;
					pole[c][d] = line;
					pole[b][e] = el_fig;
					pole[b][d + 1] = el_fig;
					pole[a][d + 1] = el_fig;
					a = e;
					d = b;
					e = d - 1;
					b = a + 1;
					c = b + 1;
					view = 1;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		if ((view == 1 && (d + 1 == m - 1 || pole[d + 1][a] == el_fig || pole[d + 1][b] == el_fig || pole[d + 1][c] == el_fig)) ||
			(view == 2 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[c + 1][e] == el_fig)) ||
			(view == 3 && (e + 1 == m - 1 || pole[e + 1][a] == el_fig || pole[e][b] == el_fig || pole[e][c] == el_fig)) ||
			(view == 4 && (c + 1 == m - 1 || pole[c + 1][d] == el_fig || pole[b][e] == el_fig))) break;
	}
}
void Tetris:: zigzag_1(int count)
{
	a = 4; b = 5; c = 6; d = 1; e = 2;
	pole[d][a] = el_fig;
	pole[d][b] = el_fig;
	pole[e][b] = el_fig;
	pole[e][c] = el_fig;
	view = 1;
	output();
	while (true)
	{
		while (!_kbhit())
		{
			fast(count);
			if (view)
			{
				pole[d][a] = line;
				pole[d][b] = line;
				pole[e][c] = line;
				e++;
				d++;
				pole[d][a] = el_fig;
				pole[e][b] = el_fig;
				pole[e][c] = el_fig;
				output();
			}
			else
			{
				pole[a][e] = line;
				pole[b][d] = line;
				a++;
				b++;
				c++;
				pole[b][e] = el_fig;
				pole[c][d] = el_fig;
				output();
			}
			if ((view && (pole[e][a] == el_fig || pole[e + 1][b] == el_fig || pole[e + 1][c] == el_fig || e + 1 == m - 1)) || (!view && (pole[c + 1][d] == el_fig || pole[c][e] == el_fig || c + 1 == 0)))
				break;
		}
		if ((view && (pole[e][a] == el_fig || pole[e + 1][b] == el_fig || pole[e + 1][c] == el_fig || e + 1 == m - 1)) || (!view && (pole[c + 1][d] == el_fig || pole[c][e] == el_fig || c + 1 == 0)))
			break;
		int moove;
		moove = _getch();
		if (view)
		{
			switch (moove)
			{
			case 80:
				pole[d][a] = line;
				pole[d][b] = line;
				pole[e][c] = line;
				e++;
				d++;
				pole[d][a] = el_fig;
				pole[e][b] = el_fig;
				pole[e][c] = el_fig;
				output();
				break;
			case 75:
				if (pole[a - 1][d] == el_fig || a - 1 == 0)
					break;
				pole[d][b] = line;
				pole[e][c] = line;
				a--;
				b--;
				c--;
				pole[d][a] = el_fig;
				pole[e][b] = el_fig;
				output();
				break;
			case 77:
				if (pole[e][c + 1] == el_fig || c + 1 == n - 1)
					break;
				pole[d][a] = line;
				pole[e][b] = line;
				a++;
				b++;
				c++;
				pole[d][b] = el_fig;
				pole[e][c] = el_fig;
				output();
				break;
			case 32:
				pole[e][c] = line;
				pole[e][b] = line;
				pole[d - 1][b] = el_fig;
				pole[e][a] = el_fig;
				a = d - 1;
				e = b;
				d = e - 1;
				b = a + 1;
				c = b + 1;
				view = 0;
				output();
				break;
			case 27:
				end();
				return;
				break;
			}
		}
		else
		{
			switch (moove)
			{
			case 80:
				pole[a][e] = line;
				pole[b][d] = line;
				a++;
				b++;
				c++;
				pole[b][e] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 75:
				if (pole[b][d - 1] == el_fig || pole[c][d - 1] == el_fig || d - 1 == 0)
					break;
				pole[a][e] = line;
				pole[b][e] = line;
				pole[c][d] = line;
				e--;
				d--;
				pole[a][e] = el_fig;
				pole[b][d] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 77:
				if (pole[a][e + 1] == el_fig || pole[b][e + 1] == el_fig || e + 1 == n - 1)
					break;
				pole[a][e] = line;
				pole[b][d] = line;
				pole[c][d] = line;
				e++;
				d++;
				pole[a][e] = el_fig;
				pole[b][e] = el_fig;
				pole[c][d] = el_fig;
				output();
				break;
			case 32:
				if (pole[b][e + 1] != el_fig&&e + 1 != n - 1 && pole[a][d - 1] != el_fig&& d - 1 != 0)
				{
					pole[a][e] = line;
					pole[b][e] = line;
					pole[c][d] = line;
					pole[b][d - 1] = el_fig;
					pole[c][d] = el_fig;
					pole[c][e] = el_fig;
					a = d - 1;
					d = b;
					e = d + 1;
					b = a + 1;
					c = b + 1;
					view = 1;
					output();
				}
				break;
			case 27:
				end();
				return;
				break;
			}

		}
		if ((view && (pole[e][a] == el_fig || pole[e + 1][b] == el_fig || pole[e + 1][c] == el_fig || e + 1 == m - 1)) || (!view && (pole[c + 1][d] == el_fig || pole[c][e] == el_fig || c + 1 == 0)))
			break;
	}
}

                      /* сама игра
					     каждой фигуре соответствует число, программа на каждом этапе генерирует рандомное число и создает соответствующую фигуру
						 если вся горизонтальная линия заполнена, удаляем ее, а остальные смещаем вниз
                      */
void Tetris:: game()
{
	int a, b, c, d, e;
	int count = 0;
	bool pol_2, pol_6;
	int pol_3, pol_4, pol_5;
	int input;
	Sleep(800);
	while (true)
	{
		for (int i = 1; i <= 2; i++)
			for (int j = 4; j <=6; j++)
				if (pole[i][j] == el_fig)
				{
					end();
					return;
				}
		input = rand() % 7;
		count++;
		switch (input)
		{
		case 1:
			kvadr(count);
			break;
		case 2:
			linee(count);
			break;
        case 3:
			sered(count);
		    break;
		case 4:
			ugol_1(count);
			break;
        case 5:
			ugol_2(count);
			break;
		case 6:
			zigzag_1(count);
			break;
		}
		for (int i = 1; i < m-1; i++)
		{
			bool t;
			for (int j = 1; j < n-1; j++)
			{
				t = 1;
				if (pole[i][j] == line)
				{
					t = 0;
					break;
				}
			}
			if (t)
			{
				for (int j = 1; j < n-1; j++)
					pole[i][j] = line;
				int k = i;
				for (int q = i - 1; q > 0; q--)
				{
					for (int j = 0; j < n; j++)
					{
						pole[k][j] = pole[q][j];
					}
					k--;
				}
				score += 5;
				output();
			}
		}
		output();
	}
}

                      // начало игры
void Tetris:: begin()
{
	Sleep(800);
	cout << endl << "            TETRIS" << endl;
	Sleep(1300);
	cout << endl << "    ДОБРО ПОЖАЛОВАТЬ В ИГРУ :)" << endl;
	Sleep(1300);
	cout << endl << " для управления фигурами используйте стрелочки" << endl;
	Sleep(1300);
	cout << endl << " для переворачивания фигур используйте space" << endl;
	Sleep(1300);
	cout << endl << " для завершения игры нажмите Escape" << endl;
	Sleep(1300);
	cout << endl << " для начала игры нажмите Enter" << endl;
	int input;
	input = _getch();
	switch (input)
	{
	case 13:
		output();
		game();
		break;
	case 27:
		end();
		return;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	Tetris T;
	T.begin();
    return 0;
}

