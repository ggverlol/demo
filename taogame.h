#pragma once
//TAT CAC CAC HAM TRONG NAY DEU DUNG CHO THANG start trong file cpp ay
#include<iostream>
#include"mylib.h"
#include<random>
#include<ctime>
#include<string>
#include<Windows.h>
using namespace std;
//chieu ngang/doc cua mang xuli
#define ngang 29 
#define doc 12 
//chieu ngang/doc cua mang ui
#define yy ngang*4+1
#define xx  doc*2+1
#define dk 5  
char xuli[doc][ngang];
struct tungo
{
	char kt;
	int mau;
};
tungo ui[xx][yy];
//3 dong dau khong can hieu, chi can hieu ouput dc a random trong khoang [1,14], 0 la mau den nen t ko lay, 15 xau nen ko lay not
random_device seed;
mt19937 tree(seed());
uniform_int_distribution<int> form(1, 14);
int a = form(tree);
//hien thi thang ui ra , doc tu ham hien_thi
void set_ui(int x, int y, char kt, int mau = a)
{
	ui[x][y].kt = kt;
	ui[x][y].mau = mau;
}
void khoi_tao_ui()
{
	for (int i = 0; i < xx; i++)
	{
		for (int j = 0; j < yy; j++)
		{
			set_ui(i, j,' ');
		}
	}
}
void ve_khung()
{
	for (int i = 0; i < xx; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j < yy; j++)
			{
				if (j % 4 == 0)
				{
					set_ui(i, j, 197);
				}
				else(set_ui(i, j, 196));
			}
		}
		else
		{
			for (int j = 0; j < yy; j++)
			{
				if (j % 4 == 0)
				{
					set_ui(i, j, 179);
				}
			}
		}
	}
	for (int i = 0; i < yy; i++)
	{
		if (i % 4 == 0)
		{
			set_ui(0, i, 194);
			set_ui(xx - 1, i, 193);
		}
	}
	for (int i = 0; i < xx; i++)
	{
		if (i % 2 == 0)
		{
			set_ui(i, 0, 195);
			set_ui(i, yy - 1, 180);
		}
	} 
	set_ui(0, 0, 218);
	set_ui(0, yy - 1, 191);
	set_ui(xx - 1, 0, 192);
	set_ui(xx - 1, yy - 1, 217);
	
}
void push()
{
	for (int i = 0; i < doc; i++)
	{
		for (int j = 0; j < ngang; j++) {
			set_ui(i * 2 + 1, j * 4 + 2, xuli[i][j], 15);
		}
	}
}
void tao_cursor(int x_dau, int y_dau)//con tro  
{
	set_ui(y_dau, x_dau - 1, ui[y_dau][x_dau - 1].kt, 176);
	set_ui(y_dau, x_dau, ui[y_dau][x_dau].kt, 176);
	set_ui(y_dau, x_dau + 1, ui[y_dau][x_dau + 1].kt, 176);
}
void tbao()
{
	TextColor(15);
	gotoXY(0, xx + 1);
	cout << "SO LUOT DA DI: ";
	gotoXY(40, xx + 1);
	cout << "NEXT TURN: ";
	gotoXY(80, xx + 1);
	cout << "NHAN PHIM S DE DUNG CHOI!!!";
}
void hien_thi(int x_dau, int y_dau, bool check)
{
	ShowCur(0);
	//khoi tao ui
	khoi_tao_ui();
	//ve khung
	ve_khung();
	//sau khi tao khung, moi o trong ae nhin thay se la ' '' '' ', cai ' ' o giua t se gan phan tu tuong ung cua mang xuli vao
	push();
	//tao con tro di chuyen
	if (check)
	{
		tao_cursor(x_dau, y_dau);
	}
	//di chuyen
	gotoXY(0, 0); 
//hien thi manh ui len man hinh bang putchar
	for (int i = 0; i < xx; i++)
	{
		for (int j = 0; j < yy; j++) {
			TextColor(ui[i][j].mau);
			putchar(ui[i][j].kt);
		}
		if (i < xx - 1)
			putchar('\n');
	}
}
//dieu khien
int dieu_khien(int& x, int& y, char& nguoi, int& cnt)
{
	int inner = inputKey();
	if (inner == 115)
	{
		return 2;
	}
	else if (inner == key_Up && y >= 3) { y -= 2; return 1; }
	else if (inner == key_Down && y <= xx - 4) { y += 2; return 1; }
	else if (inner == key_Left && x >= 6) { x -= 4; return 1; }
	else if (inner == key_Right && x <= yy - 7) { x += 4; return 1; }
	else if (inner == 13)
	{
		int a = (x - 2) / 4;
		int b = (y - 1) / 2;
		if (xuli[b][a] == ' ')
		{
			if (nguoi == 'X')
			{
				++cnt;
				xuli[b][a] = nguoi;
				nguoi = 'O';
				gotoXY(53, xx + 1);
				TextColor(15);
				cout << nguoi;
				return 1;
			}
			else if (nguoi == 'O')
			{
				xuli[b][a] = nguoi;
				nguoi = 'X';
				gotoXY(53, xx + 1);
				TextColor(15);
				cout << nguoi;
				return 1;
			}
		}
	}
	return 0;
}
//xet thang thua
int xet_thang_thua(int x, int y)
{
	//1 -> x thang 0->O thang 3->hoa
	int dem, i, j, h, c;
	c = (x - 2) / 4;
	h = (y - 1) / 2;
	if (xuli[h][c] == ' ') return 2;
	//xet hang ngang
	dem = 0;
	for (j = c; j >= 0; j--)
		if (xuli[h][j] != xuli[h][c]) break;
		else dem++;
	for (j = c + 1; j < ngang; j++)
		if (xuli[h][j] != xuli[h][c]) break;
		else dem++;
	if (dem >= 5)
	{
		if (xuli[h][c] == 'X') return 1;
		else return 0;
	}
	//xet hang doc
	dem = 0;
	for (int i = h; i >= 0; i--)
		if (xuli[i][c] != xuli[h][c]) break;
		else dem++;
	for (i = h + 1; i < doc; i++)
		if (xuli[i][c] != xuli[h][c]) break;
		else dem++;
	if (dem >= 5)
	{
		if (xuli[h][c] == 'X') return 1;
		else return 0;
	}
	//xet duong cheo len
	dem = 0;
	for (i = h, j = c; i >= 0 && j < ngang; i--, j++)//doi
		if (xuli[i][j] != xuli[h][c]) break;
		else dem++;
	for (i = h + 1, j = c - 1; i < doc, j >= 0; i++, j--)
		if (xuli[i][j] != xuli[h][c]) break;
		else dem++;
	if (dem >= 5)
	{
		if (xuli[h][c] == 'X') return 1;
		else return 0;
	}
	//xet duong cheo xuong
	dem = 0;
	for (i = h, j = c; i < doc && j < ngang; i++, j++)//doi
		if (xuli[i][j] != xuli[h][c]) break;
		else dem++;
	for (i = h - 1, j = c - 1; i >= 0, j >= 0; i--, j--)
		if (xuli[i][j] != xuli[h][c]) break;
		else dem++;
	if (dem >= 5)
	{
		if (xuli[h][c] == 'X') return 1;
		else return 0;
	}
	for (i = 0; i < doc; i++)
		for (j = 0; j < ngang; j++)
			if (xuli[i][j] == ' ') return 2;
	return 3;
}
void  Bling(char k, int &i)
{
	string show = "NGUOI THANG LA  ";
	if (k != 'X' && k != 'O')
	{
		show = "";
		show += "VAN CO NAY HOA";
	}
	else
	{
		show += k;
	}
	int cnt = 0;
	while (true)
	{
		++cnt;
		if (cnt % 2 == 0)
		{
			TextColor(Color_Cyan);
		}
		else
		{
			TextColor(Color_BLACK);
		}
		gotoXY(52, 12);
		cout << show;
		gotoXY(45, 13);
		cout << "NHAN PHIM BAT KI DE TIEP TUC...";
		Sleep(600);
		if (_kbhit())
		{
			i = 1;
			break;
		}
	}
}
