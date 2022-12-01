#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#define MERGER // Если не нужно слияние одинаковых элементов, то закоментировать эту строку

// Функиця проверки на неправильный ввод
bool RUF()
{
	int n, ni, m, mi;
	ifstream fin("input1.txt");
	fin >> n;
	if (n <= 0 || n >= 30)
		return true;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			fin >> ni;
			if (ni < 0 || ni > n)
				return true;
		}
	fin >> m;
	if (m < 1)
		return true;
	for (int i = 0; i < m; i++)
	{
		fin >> mi;
		if (mi < 0 || mi > n)
			return true;
	}
	return false;
	fin.close();
}

// Функция выделения памяти для матрицы взаимодействий
int** memoryArr(int n)
{
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	return a;
}

// Функция создания матрицы взаимодействия
void createArr(int n, int** a, ifstream& f)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			f >> a[i][j];
}

// Функция очищения памяти от матрицы взаимодейтсвия и пробирки
void clearMemory(int n, int** a, int* b)
{
	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[] a;
	delete[] b;
}

// Функция определяет не закончилась ли реакция
bool is_end(int m, int* b, int** a)
{
	for (int i = 0; i < m - 1; i++)
	{
		if (b[i] * b[i + 1])
			if (a[b[i] - 1][b[i + 1] - 1])
				return false;
	}
	return true;
}

// Функция реакции
int* react(int m, int* b, int** a)
{
	for (int i = 0; i < m - 1; i++)
		if (a[b[i] - 1][b[i + 1] - 1])          // Если есть взаимодействие
		{
			b[i] = a[b[i] - 1][b[i + 1] - 1];   // Получаем результат реакции
			for (int j = i + 1; j < m - 1; j++) // |
				b[j] = b[j + 1];                // | Утрамбовываем вещества в пробирке
			b[m - 1] = 0;                       // |
			return b;
		}
#ifdef MERGER
		else if (b[i] == b[i + 1])              // Если одинаковые элементы
		{                                       // не дают нового вещества,
			for (int j = i + 1; j < m - 1; j++) // | то
				b[j] = b[j + 1];                // | утрамбовываем их в одно
			b[m - 1] = 0;                       // |
			return b;
		}
#endif
}

// Функция вывода на консоль
void Output(int m, int* b)
{
	cout << "В пробирке останутся вещества с номерами: " << b[0] << " ";
	for (int i = 1; i < m && b[i]; i++)
#ifdef MERGER
		if (b[i] != b[i - 1])
#endif
			cout << b[i] << " ";
	cout << endl;
}

int main()
{
	SetConsoleOutputCP(1251);
	int n, m;
	if (RUF())
		cout << "Неверный ввод!";
	else
	{
		ifstream f("input1.txt");
		f >> n;
		int** a = memoryArr(n);
		createArr(n, a, f);

		f >> m;
		int* b = new int[m];
		for (int i = 0; i < m; i++)
			f >> b[i];
		while (!is_end(m, b, a))
			b = react(m, b, a);

		Output(m, b);
		clearMemory(n, a, b);
		f.close();
	}
	//system("pause");
	return 0;
}
