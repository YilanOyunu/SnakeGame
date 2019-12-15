#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <list>
#include <algorithm>

using namespace std;

const int sıra = 24;
const int sütun = 40;

enum YÖN { SOL, SAĞ, YUKARI, AŞAĞI };

void EkranıTemizle(const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
	//GetStdHandle=>Belirtilen standart aygıta bir tanıtıcı alır
	// GetStdHandle(STD_OUTPUT_HANDLE) => bulunduğum konsol ekranını belirtir.
	_CONSOLE_SCREEN_BUFFER_INFO buffInfo;//Konsol ekranı arabelleği hakkında bilgi içerir.
	COORD koordinat = { 0, 0 };//Konsol ekran arabelleğindeki bir karakter hücresinin koordinatlarını tanımlar.
	DWORD var;//int gibi 64 bit yer kapsar gibi.
	GetConsoleScreenBufferInfo(hOut, &buffInfo);//Belirtilen konsol ekranı arabelleği hakkında bilgi alır.
	FillConsoleOutputCharacter(hOut, ' ', buffInfo.dwSize.X * buffInfo.dwSize.Y, koordinat, &var);//FillConsoleOutputCharacter=>Belirtilen koordinatlardan başlayarak belirtilen sayıda karakter yazar.
	SetConsoleCursorPosition(hOut, koordinat);//Mevcut imleç pozisyonunu ayarlar.(Windowsla iletişime geçmeyi sağlar.)
	//ilk parametresi hangi konsol ekranının parametresini değiştireceğini belirtir.
	//ikinci parametresi hangi koordinatları değiştirmek istediğini belirtir.
	//Koordinatı değiştirmek istersek bunu kullanmamız gerekir.
}

void KoordinatTaşıma(const int&x, const int&y, const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
	//setCursorPos => İmleci belirtilen ekran koordinatlarına taşır
	COORD koordinat = { x, y };
	SetConsoleCursorPosition(hOut, koordinat);
}

void TabloyuÇiz() {
	int karakter = 219;
	for (int i = 0; i < sıra; ++i) {
		for (int j = 0; j < sütun; ++j) {
			if (i == 0 || i == (sıra - 1))
				cout << (char)karakter;
			else if (i > 0 && i < (sıra - 1) && (j == 0 || j == (sütun - 1)))
				cout << (char)karakter;
			else
				cout << ' ';
		}
		cout << endl;
		system("color 4f");
	}
}

void YerineKoy(const int&x, const int&y, const char&ch, const HANDLE&hOut = GetStdHandle(STD_OUTPUT_HANDLE)) {
	COORD koordinat = { x, y };
	DWORD var;
	SetConsoleCursorPosition(hOut, koordinat);
	FillConsoleOutputCharacter(hOut, ch, 1, koordinat, &var);
}

void YıldızÇiz(const int&x, const int&y) {
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
		case SAĞ:++y;
			break;
		case YUKARI:--x;
			break;
		case AŞAĞI:++x;
			break;
		}
		return *this;
	}
	bool operator==(const Koordinat&sağ)const {
		if (x == sağ.x && y == sağ.y)
			return true;
		return false;
	}
};

class Snake {
public:
	list <Koordinat> snake;
	Snake() {
		for (int i = 1; i < 6; ++i) {
			snake.push_back(Koordinat(1, i, SAĞ));
		}
	}
	void hareket() {
		YerineKoy(snake.front().y, snake.front().x, ' ');
		for (auto i = snake.begin(); i != snake.end(); ++i) {//Auto deyimi eğer değişken tanımlanırken değer alıyorsa kullanılır.
			auto temp = i;//koordinat tipinde list in elemanlarını gösteren temp adında iterator tanımlaması yapıldı.
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
	void Yazdır() {
		for (auto ptr = snake.cbegin(); ptr != snake.cend(); ++ptr) {// vektörün başlangıcına işaret eder.//vektörün içeriğini değiştiremez.
			YerineKoy(ptr->y, ptr->x, 'o');
		}
	}
};

class Game {
public:
	int randX, randY, puan;
	Snake snake;
	Game() :puan(0) {
		srand((unsigned int)time(NULL));// sadece pozitif değerler alır.
		randX = rand() % (sıra - 2) + 1;
		randY = rand() % (sütun - 2) + 1;
	}
	void oyna() {
		CONSOLE_CURSOR_INFO curInfo;
		curInfo.bVisible = FALSE;
		curInfo.dwSize = 1;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
		TabloyuÇiz();
		YıldızÇiz(randX, randY);
		snake.Yazdır();
		KoordinatTaşıma(0, sıra);
		cout << "Puan: " << puan;
		while (true) {
			Sleep(65);
			if (GetAsyncKeyState(32)) {//çağrısından sonra tuşa basılıp basılmayacağını belirler
				KoordinatTaşıma((sütun / 2) - 3, sıra / 2);
				cout << "PAUSED";
				Sleep(250);
				while (true) {
					Sleep(250);
					if (GetAsyncKeyState(32)) {
						KoordinatTaşıma((sütun / 2) - 3, sıra / 2);
						cout << "      ";
						break;
					}
				}
			}
			if (_kbhit()) {//Klavyeden bir tuşa basılıp basılmadıpını kontrol eder.
				char tuş = _getch();//Kullanıcıdan bir karakter almamıza yarar fakat karakteri ekrana yazmaz.
				switch (tuş) {
				case 'a':
					if (snake.snake.back().yön != SAĞ)
						snake.Dön(SOL);
					break;
				case 'd':
					if (snake.snake.back().yön != SOL)
						snake.Dön(SAĞ);
					break;
				case 'w':
					if (snake.snake.back().yön != AŞAĞI)
						snake.Dön(YUKARI);
					break;
				case 's':
					if (snake.snake.back().yön != YUKARI)
						snake.Dön(AŞAĞI);
					break;
				}
			}
			snake.hareket();
			if (snake.snake.back().x == randX && snake.snake.back().y == randY) {
				++puan;
				snake.Büyüt();
				YerineKoy(randY, randX, 'o');
				while (find(snake.snake.cbegin(), snake.snake.cend(), Koordinat(randX, randY)) != snake.snake.cend()) {
					randX = rand() % (sıra - 2) + 1;
					randY = rand() % (sütun - 2) + 1;
				}
				YıldızÇiz(randX, randY);
				KoordinatTaşıma(0, sıra);
				cout << "Puan: " << puan;
			}
			if (count(snake.snake.cbegin(), snake.snake.cend(), snake.snake.back()) == 2) {
				Sleep(1000);//1000 milisaniye uyumasını sağlıyor sonra devam ediyor.
				EkranıTemizle();
				cout << "GAME OVER!" << endl;
				cout << "Puan: " << puan << endl;
				break;
			}
			else if (snake.snake.back().x == 0 || snake.snake.back().x == (sıra - 1) || snake.snake.back().y == 0 || snake.snake.back().y == (sütun - 1)) {
				Sleep(1000);
				EkranıTemizle();
				cout << "GAME OVER!" << endl;
				cout << "Puan: " << puan << endl;
				break;
			}
		}
	}
};

int main() {
	Game a;
	a.oyna();

	getchar();
	return 0;
}