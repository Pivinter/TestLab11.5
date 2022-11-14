#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Posada { ROBITNYK, INZHENER, SLUZHBOVETS};
string posadaStr[] = {"Туди", "Назад", "Туди-назад"};
enum day{ d1, d2, d3 };
string dayStr[] = { "Понеділок", "Вівторок", "Середа"};
struct Pracivnyk
{
	string prizv;
	unsigned rik_nar;
	Posada posada;
	day dy;
	union
	{
		double taryf;
		int stavka;
		int program;
		int program2;
		int pedagog;
	};
};
void Create(Pracivnyk* p, const int N);
void Print(Pracivnyk* p, const int N);
int BinSearch(Pracivnyk* p, const int N, const int program, const Posada posada, int stavka);
int BinSearch1(Pracivnyk* p, const int N, const string prizv, const Posada posada, int rik_nar);
int BinSearch2(Pracivnyk* p, const int N, const string prizv, const Posada posada);
int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть N: "; cin >> N;

	Pracivnyk* p = new Pracivnyk[N];
	int iposada;
	Posada posada;
	day dy;
	string prizv;
	double taryf;
	int rik_nar;
	int found;
	int stavka;
	int program;
	Create(p, N);
	Print(p, N);
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - визначити номери авіаційних рейсів заданого напрямку з мінімальною вартістю квитків" << endl;
		cout << " [2] - визначити літак і сумарну кількість посадкових місць у заданому напрямку по днях тижня" << endl;
		cout << " [3] - про рейси, кількість польотів на тиждень менше двох" << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "Напрям польоту (Туди, Назад, Туди - назад):";
			cin >> iposada;
			posada = (Posada)iposada;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << endl;
			cout << " Номер аварійного рейсу: "; cin >> program;
			cout << " вартість квитка: "; cin >> stavka;
			cout << endl;

			if ((found = BinSearch(p, N, program, posada, stavka)) != -1)
				cout << "Знайдено авіаційних рейсів в позиції " << found + 1 << endl;
			else
				cout << "Шуканого авіаційних рейсів не знайдено" << endl;
			break;
		case 2:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "Напрям польоту (Туди, Назад, Туди - назад):";
			cin >> iposada;
			posada = (Posada)iposada;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << endl;
			cout << " Літак: "; getline(cin, prizv);
			cout << " кількість посадкових місць: "; cin >> rik_nar;
			cout << endl;
			if ((found = BinSearch1(p, N, prizv, posada, rik_nar)) != -1)
				cout << "Знайдено літак в позиції " << found + 1 << endl;
			else
				cout << "Шуканого літак не знайдено" << endl;
			break;
		case 3:
			cout << "Введіть ключі пошуку:" << endl;
			cout << "Напрям польоту (Туди, Назад, Туди - назад):";
			cin >> iposada;
			posada = (Posada)iposada;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << endl;
			cout << " Літак: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch2(p, N, prizv, posada)) != -1)
				cout << "Знайдено літак в позиції " << found + 1 << endl;
			else
				cout << "Шуканого літак не знайдено" << endl;
			break;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Pracivnyk* p, const int N)
{
	int posada;
	for (int i = 0; i < N; i++)
	{
		cout << "Працівник № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " Літак: "; getline(cin, p[i].prizv);
		cout << " кількість посадкових місць: "; cin >> p[i].rik_nar;
		cout << " Напрям польоту (Туди, Назад, Туди - назад): ";
		cin >> posada;
		p[i].posada = (Posada)posada;
		switch (p[i].posada)
		{
		case ROBITNYK:
			cout << " Льотні дні : "; cin >> p[i].taryf;
			cout << " вартість квитка : "; cin >> p[i].stavka;
			cout << " Номер аварійного рейсу : "; cin >> p[i].program;
			break;
		case INZHENER:
			cout << " Льотні дні : "; cin >> p[i].taryf;
			cout << " вартість квитка : "; cin >> p[i].stavka;
			cout << " Номер аварійного рейсу : "; cin >> p[i].program2;
			break;
		case SLUZHBOVETS:
			cout << " Льотні дні : "; cin >> p[i].taryf;
			cout << " вартість квитка : "; cin >> p[i].stavka;
			cout << " Номер аварійного рейсу : "; cin >> p[i].pedagog;
			break;
		}
		cout << endl;
	}
}
void Print(Pracivnyk* p, const int N)
{
	cout << "================================================================================================================="
		<< endl;
	cout << "| № | Літак | кількість посадкових місць | Напрям польоту | Номер аварійного рейсу | Льотні дні | вартість квитка"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------"
		<< endl;
	int h = 0, m = 0, a = 0, g = 0;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].rik_nar << " "
			<< "| " << setw(11) << left << posadaStr[p[i].posada];
		switch (p[i].posada)
		{
		case ROBITNYK:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[i].taryf << " |" << setw(4) << right << " " << setw(4) << right
				<< p[i].stavka << " |" << setw(4) << " " << setw(6)
				<< p[i].program << " |" << endl;
			break;
		case INZHENER:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[i].taryf << " |" << setw(4) << right << " " << setw(4) << right
				<< p[i].stavka << " |" << setw(4) << " " << setw(6)
				<< p[i].program2 << " |" << endl;
			break;
		case SLUZHBOVETS:
			cout << "| " << setw(9) << setprecision(2) << fixed << right
				<< p[i].taryf << " |" << setw(4) << right << " " << setw(4) << right
				<< p[i].stavka << " |" << setw(4) << " " << setw(6)
				<< p[i].pedagog << " |" << endl;
			break;
		}
	}
	cout << "================================================================================================================"
		<< endl;
	cout << endl;
}
int BinSearch(Pracivnyk* p, const int N, const int rik_nar, const Posada posada, int stavka)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].rik_nar == rik_nar && p[m].posada == posada && p[m].stavka == stavka)
			return m;
		if ((p[m].posada < posada)
			||
			(p[m].posada == posada &&
				p[m].rik_nar < rik_nar && p[m].stavka < stavka))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int BinSearch1(Pracivnyk* p, const int N, const string prizv, const Posada posada, int stavka)
{
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].posada == posada && p[m].stavka == stavka)
			return m;
		if ((p[m].posada < posada)
			||
			(p[m].posada == posada &&
				p[m].prizv < prizv && p[m].stavka < stavka))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
int BinSearch2(Pracivnyk* p, const int N, const string prizv, const Posada posada)
{ 
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].posada == posada)
			return m;
		if ((p[m].posada < posada)
			||
			(p[m].posada == posada &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
