
#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

int saha[80][23] = { 0 };
int kuyrukSutun[500];
int kuyrukSatir[500];
int maap[80][23] = { 0 };

void gotoxy(short x, short y) {
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = { x - 1, y - 1 };

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void cerceve(int x1, int y1, int x2, int y2, int tur)
{
	int i;
	for (i = x1; i <= x2;i++)
	{
		saha[i][y1] = tur;

		saha[i][y2] = tur;

	}
	for (i = y1; i <= y2;i++)
	{
		saha[x1][i] = tur;

		saha[x2][i] = tur;

	}
}

void ekrani_bas()
{
	int x, y;
	for (x = 0;x < 80;x++)
	{


		for (y = 0;y < 23;y++)
		{
			gotoxy(x + 1, y + 1);
			if (saha[x][y] == 1)
			{
				printf("%c", 219);
			}

			else if (saha[x][y] == 2)
			{
				printf("%c", 176);
			}
			else if (saha[x][y] == 3)
				printf("%c", 88);

		}
	}
}

int k, l;
void randomAta()
{
	srand(time(NULL));
	k = 4 + rand() % 65;
	l = 4 + rand() % 15;


}

void main()
{
	randomAta();
	cerceve(0, 0, 79, 22, 2);
	ekrani_bas();
	int sx = 40, sy = 12;
	int dy = 0, dx = 0;
	unsigned char tus;
	int a = 0;
	int devam = 0;




	do
	{
		if (_kbhit())
		{
			tus = _getch();
			if (tus == 224)
			{
				tus = _getch();
				switch (tus)
				{
				case 72:dy = -1; dx = 0;
					break;
				case 80:dy = 1; dx = 0;
					break;
				case 77: dx = 1; dy = 0;
					break;
				case 75: dx = -1; dy = 0;
				}
			}
		}

		sx = sx + dx;
		sy = sy + dy;
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <list>
#include <algorithm>

		using namespace std;

		const int s�ra = 24;
		const int s�tun = 40;

		enum Y�N { SOL, SA�, YUKARI, A�A�I };

		void Ekran�Temizle(const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
			//GetStdHandle=>Belirtilen standart ayg�ta bir tan�t�c� al�r
			// GetStdHandle(STD_OUTPUT_HANDLE) => bulundu�um konsol ekran�n� belirtir.
			_CONSOLE_SCREEN_BUFFER_INFO buffInfo;//Konsol ekran� arabelle�i hakk�nda bilgi i�erir.
			COORD koordinat = { 0, 0 };//Konsol ekran arabelle�indeki bir karakter h�cresinin koordinatlar�n� tan�mlar.
			DWORD var;//int gibi 64 bit yer kapsar gibi.
			GetConsoleScreenBufferInfo(hOut, &buffInfo);//Belirtilen konsol ekran� arabelle�i hakk�nda bilgi al�r.
			FillConsoleOutputCharacter(hOut, ' ', buffInfo.dwSize.X * buffInfo.dwSize.Y, koordinat, &var);//FillConsoleOutputCharacter=>Belirtilen koordinatlardan ba�layarak belirtilen say�da karakter yazar.
			SetConsoleCursorPosition(hOut, koordinat);//Mevcut imle� pozisyonunu ayarlar.(Windowsla ileti�ime ge�meyi sa�lar.)
			//ilk parametresi hangi konsol ekran�n�n parametresini de�i�tirece�ini belirtir.
			//ikinci parametresi hangi koordinatlar� de�i�tirmek istedi�ini belirtir.
			//Koordinat� de�i�tirmek istersek bunu kullanmam�z gerekir.
		}

		void KoordinatTa��ma(const int&x, const int&y, const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
			//setCursorPos => �mleci belirtilen ekran koordinatlar�na ta��r
			COORD koordinat = { x, y };
			SetConsoleCursorPosition(hOut, koordinat);
		}

		void Tabloyu�iz() {
			int karakter = 219;
			for (int i = 0; i < s�ra; ++i) {
				for (int j = 0; j < s�tun; ++j) {
					if (i == 0 || i == (s�ra - 1))
						cout << (char)karakter;
					else if (i > 0 && i < (s�ra - 1) && (j == 0 || j == (s�tun - 1)))
						cout << (char)karakter;
					else
						cout << ' ';
				}
				cout << endl;
			}
		}

		void YerineKoy(const int&x, const int&y, const char&ch, const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
			COORD koordinat = { x, y };
			DWORD var;
			SetConsoleCursorPosition(hOut, koordinat);
			FillConsoleOutputCharacter(hOut, ch, 1, koordinat, &var);
		}

		void Y�ld�z�iz(const int&x, const int&y) {
			YerineKoy(y, x, '*');
		}

		class Koordinat {
		public:
			int x, y;
			Y�N y�n;
			Koordinat(const int&x, const int&y, const Y�N&y�n = SOL) :x(x), y(y), y�n(y�n) {}
			Koordinat&operator++() {
				switch (y�n) {
				case SOL:--y;
					break;
				case SA�:++y;
					break;
				case YUKARI:--x;
					break;
				case A�A�I:++x;
					break;
				}
				return *this;
			}
			bool operator==(const Koordinat&sa�)const {
				if (x == sa�.x && y == sa�.y)
					return true;
				return false;
			}
		};

		class Snake {
		public:
			list <Koordinat> snake;
			Snake() {
				for (int i = 1; i < 6; ++i) {
					snake.push_back(Koordinat(1, i, SA�));
				}
			}
			void hareket() {
				YerineKoy(snake.front().y, snake.front().x, ' ');
				for (auto i = snake.begin(); i != snake.end(); ++i) {//Auto deyimi e�er de�i�ken tan�mlan�rken de�er al�yorsa kullan�l�r.
					auto temp = i;//koordinat tipinde list in elemanlar�n� g�steren temp ad�nda iterator tan�mlamas� yap�ld�.
					++temp;
					++(*i);
					if (temp != snake.end())
						i->y�n = temp->y�n;
				}
				YerineKoy(snake.back().y, snake.back().x, 'o');
			}
			void D�n(const Y�N&y�n) {
				snake.back().y�n = y�n;
			}
			void B�y�t() {
				Koordinat temp(snake.back());
				++temp;
				snake.push_back(temp);
				YerineKoy(snake.back().y, snake.back().x, 'o');
			}
			void Yazd�r() {
				for (auto ptr = snake.cbegin(); ptr != snake.cend(); ++ptr) {// vekt�r�n ba�lang�c�na i�aret eder.//vekt�r�n i�eri�ini de�i�tiremez.
					YerineKoy(ptr->y, ptr->x, 'o');
				}
			}
		};

		class Game {
		public:
			int randX, randY, puan;
			Snake snake;
			Game() :puan(0) {
				srand((unsigned int)time(NULL));// sadece pozitif de�erler al�r.
				randX = rand() % (s�ra - 2) + 1;
				randY = rand() % (s�tun - 2) + 1;
			}
			void oyna() {
				CONSOLE_CURSOR_INFO curInfo;
				curInfo.bVisible = FALSE;
				curInfo.dwSize = 1;
				SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
				Tabloyu�iz();
				Y�ld�z�iz(randX, randY);
				snake.Yazd�r();
				KoordinatTa��ma(0, s�ra);
				cout << "Puan: " << puan;
				while (true) {
					Sleep(65);
					if (GetAsyncKeyState(32)) {//�a�r�s�ndan sonra tu�a bas�l�p bas�lmayaca��n� belirler
						KoordinatTa��ma((s�tun / 2) - 3, s�ra / 2);
						cout << "PAUSED";
						Sleep(250);
						while (true) {
							Sleep(250);
							if (GetAsyncKeyState(32)) {
								KoordinatTa��ma((s�tun / 2) - 3, s�ra / 2);
								cout << "      ";
								break;
							}
						}
					}
					if (_kbhit()) {//Klavyeden bir tu�a bas�l�p bas�lmad�p�n� kontrol eder.
						char tu� = _getch();//Kullan�c�dan bir karakter almam�za yarar fakat karakteri ekrana yazmaz.
						switch (tu�) {
						case 'a':
							if (snake.snake.back().y�n != SA�)
								snake.D�n(SOL);
							break;
						case 'd':
							if (snake.snake.back().y�n != SOL)
								snake.D�n(SA�);
							break;
						case 'w':
							if (snake.snake.back().y�n != A�A�I)
								snake.D�n(YUKARI);
							break;
						case 's':
							if (snake.snake.back().y�n != YUKARI)
								snake.D�n(A�A�I);
							break;
						}
					}
					snake.hareket();
					if (snake.snake.back().x == randX && snake.snake.back().y == randY) {
						++puan;
						snake.B�y�t();
						YerineKoy(randY, randX, 'o');
						while (find(snake.snake.cbegin(), snake.snake.cend(), Koordinat(randX, randY)) != snake.snake.cend()) {
							randX = rand() % (s�ra - 2) + 1;
							randY = rand() % (s�tun - 2) + 1;
						}
						Y�ld�z�iz(randX, randY);
						KoordinatTa��ma(0, s�ra);
						cout << "Puan: " << puan;
					}
					if (count(snake.snake.cbegin(), snake.snake.cend(), snake.snake.back()) == 2) {
						Sleep(1000);//1000 milisaniye uyumas�n� sa�l�yor sonra devam ediyor.
						Ekran�Temizle();
						cout << "GAME OVER!" << endl;
						cout << "Puan: " << puan << endl;
						break;
					}
					else if (snake.snake.back().x == 0 || snake.snake.back().x == (s�ra - 1) || snake.snake.back().y == 0 || snake.snake.back().y == (s�tun - 1)) {
						Sleep(1000);
						Ekran�Temizle();
						cout << "GAME OVER!" << endl;
						cout << "Puan: " << puan << endl;
						break;
					}
				}
			}
		};


		int main() 
		{
			Game a;
			a.oyna();

			getchar();
			return 0;
		}
