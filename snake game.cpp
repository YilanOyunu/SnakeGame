
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

		const int sýra = 24;
		const int sütun = 40;

		enum YÖN { SOL, SAÐ, YUKARI, AÞAÐI };

		void EkranýTemizle(const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
			//GetStdHandle=>Belirtilen standart aygýta bir tanýtýcý alýr
			// GetStdHandle(STD_OUTPUT_HANDLE) => bulunduðum konsol ekranýný belirtir.
			_CONSOLE_SCREEN_BUFFER_INFO buffInfo;//Konsol ekraný arabelleði hakkýnda bilgi içerir.
			COORD koordinat = { 0, 0 };//Konsol ekran arabelleðindeki bir karakter hücresinin koordinatlarýný tanýmlar.
			DWORD var;//int gibi 64 bit yer kapsar gibi.
			GetConsoleScreenBufferInfo(hOut, &buffInfo);//Belirtilen konsol ekraný arabelleði hakkýnda bilgi alýr.
			FillConsoleOutputCharacter(hOut, ' ', buffInfo.dwSize.X * buffInfo.dwSize.Y, koordinat, &var);//FillConsoleOutputCharacter=>Belirtilen koordinatlardan baþlayarak belirtilen sayýda karakter yazar.
			SetConsoleCursorPosition(hOut, koordinat);//Mevcut imleç pozisyonunu ayarlar.(Windowsla iletiþime geçmeyi saðlar.)
			//ilk parametresi hangi konsol ekranýnýn parametresini deðiþtireceðini belirtir.
			//ikinci parametresi hangi koordinatlarý deðiþtirmek istediðini belirtir.
			//Koordinatý deðiþtirmek istersek bunu kullanmamýz gerekir.
		}

		void KoordinatTaþýma(const int&x, const int&y, const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
			//setCursorPos => Ýmleci belirtilen ekran koordinatlarýna taþýr
			COORD koordinat = { x, y };
			SetConsoleCursorPosition(hOut, koordinat);
		}

		void TabloyuÇiz() {
			int karakter = 219;
			for (int i = 0; i < sýra; ++i) {
				for (int j = 0; j < sütun; ++j) {
					if (i == 0 || i == (sýra - 1))
						cout << (char)karakter;
					else if (i > 0 && i < (sýra - 1) && (j == 0 || j == (sütun - 1)))
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

		void YýldýzÇiz(const int&x, const int&y) {
			YerineKoy(y, x, '*');
		}

		class Koordinat {
		public:
			int x, y;
			YÖN yön;
			Koordinat(const int&x, const int&y, const YÖN&yön = SOL) :x(x), y(y), yön(yön) {}
			Koordinat&operator++() {
				switch (yön) {
				case SOL:--y;
					break;
				case SAÐ:++y;
					break;
				case YUKARI:--x;
					break;
				case AÞAÐI:++x;
					break;
				}
				return *this;
			}
			bool operator==(const Koordinat&sað)const {
				if (x == sað.x && y == sað.y)
					return true;
				return false;
			}
		};

		class Snake {
		public:
			list <Koordinat> snake;
			Snake() {
				for (int i = 1; i < 6; ++i) {
					snake.push_back(Koordinat(1, i, SAÐ));
				}
			}
			void hareket() {
				YerineKoy(snake.front().y, snake.front().x, ' ');
				for (auto i = snake.begin(); i != snake.end(); ++i) {//Auto deyimi eðer deðiþken tanýmlanýrken deðer alýyorsa kullanýlýr.
					auto temp = i;//koordinat tipinde list in elemanlarýný gösteren temp adýnda iterator tanýmlamasý yapýldý.
					++temp;
					++(*i);
					if (temp != snake.end())
						i->yön = temp->yön;
				}
				YerineKoy(snake.back().y, snake.back().x, 'o');
			}
			void Dön(const YÖN&yön) {
				snake.back().yön = yön;
			}
			void Büyüt() {
				Koordinat temp(snake.back());
				++temp;
				snake.push_back(temp);
				YerineKoy(snake.back().y, snake.back().x, 'o');
			}
			void Yazdýr() {
				for (auto ptr = snake.cbegin(); ptr != snake.cend(); ++ptr) {// vektörün baþlangýcýna iþaret eder.//vektörün içeriðini deðiþtiremez.
					YerineKoy(ptr->y, ptr->x, 'o');
				}
			}
		};

		class Game {
		public:
			int randX, randY, puan;
			Snake snake;
			Game() :puan(0) {
				srand((unsigned int)time(NULL));// sadece pozitif deðerler alýr.
				randX = rand() % (sýra - 2) + 1;
				randY = rand() % (sütun - 2) + 1;
			}
			void oyna() {
				CONSOLE_CURSOR_INFO curInfo;
				curInfo.bVisible = FALSE;
				curInfo.dwSize = 1;
				SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
				TabloyuÇiz();
				YýldýzÇiz(randX, randY);
				snake.Yazdýr();
				KoordinatTaþýma(0, sýra);
				cout << "Puan: " << puan;
				while (true) {
					Sleep(65);
					if (GetAsyncKeyState(32)) {//çaðrýsýndan sonra tuþa basýlýp basýlmayacaðýný belirler
						KoordinatTaþýma((sütun / 2) - 3, sýra / 2);
						cout << "PAUSED";
						Sleep(250);
						while (true) {
							Sleep(250);
							if (GetAsyncKeyState(32)) {
								KoordinatTaþýma((sütun / 2) - 3, sýra / 2);
								cout << "      ";
								break;
							}
						}
					}
					if (_kbhit()) {//Klavyeden bir tuþa basýlýp basýlmadýpýný kontrol eder.
						char tuþ = _getch();//Kullanýcýdan bir karakter almamýza yarar fakat karakteri ekrana yazmaz.
						switch (tuþ) {
						case 'a':
							if (snake.snake.back().yön != SAÐ)
								snake.Dön(SOL);
							break;
						case 'd':
							if (snake.snake.back().yön != SOL)
								snake.Dön(SAÐ);
							break;
						case 'w':
							if (snake.snake.back().yön != AÞAÐI)
								snake.Dön(YUKARI);
							break;
						case 's':
							if (snake.snake.back().yön != YUKARI)
								snake.Dön(AÞAÐI);
							break;
						}
					}
					snake.hareket();
					if (snake.snake.back().x == randX && snake.snake.back().y == randY) {
						++puan;
						snake.Büyüt();
						YerineKoy(randY, randX, 'o');
						while (find(snake.snake.cbegin(), snake.snake.cend(), Koordinat(randX, randY)) != snake.snake.cend()) {
							randX = rand() % (sýra - 2) + 1;
							randY = rand() % (sütun - 2) + 1;
						}
						YýldýzÇiz(randX, randY);
						KoordinatTaþýma(0, sýra);
						cout << "Puan: " << puan;
					}
					if (count(snake.snake.cbegin(), snake.snake.cend(), snake.snake.back()) == 2) {
						Sleep(1000);//1000 milisaniye uyumasýný saðlýyor sonra devam ediyor.
						EkranýTemizle();
						cout << "GAME OVER!" << endl;
						cout << "Puan: " << puan << endl;
						break;
					}
					else if (snake.snake.back().x == 0 || snake.snake.back().x == (sýra - 1) || snake.snake.back().y == 0 || snake.snake.back().y == (sütun - 1)) {
						Sleep(1000);
						EkranýTemizle();
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
