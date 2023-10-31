#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

bool shot = 0, l = 0, r = 0, u = 0, d = 0;
int xl, xr, yu, yd;
int x, y;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


class Line {
public:
	char& operator[](int ind) { // обращение по индексу к элементу линии
		return arr[ind];
	}
	void fillLine() { // заполнение линии
		for (int a = 0; a < 10; a++)
		{
			arr[a] = '.';
		}
	}


	~Line() {
		delete[] arr;
	}
	Line() {
		fillLine();
	}

private:
	char* arr = new char[10];
};

class Table {
public:
	Table(Line* l) {
		for (int i = 0; i < 10; i++) {
			arr[i] = l[i];
		}
	}
	void addShip(int len)// Добавление корабля рнд
	{
		int ship = 1, xl, yu, xr, yd;
		bool d = 1, u = 1, l = 1, r = 1;
		do {
			y = rand() % 10;
			x = rand() % 10;
		} while (check(y, x));
		xl = x;
		xr = x;
		yu = y;
		yd = y;
		vector<pair<int, int>> filled = { {y, x} };
		while (ship++ < len) {
			vector<pair<int, int>> possible;
			if (l && xl - 1 >= 0 && !check(y, xl - 1)) {
				possible.push_back({ y, xl - 1 });// Лево
			}
			if (r && xr + 1 < 10 && !check(y, xr + 1)) {
				possible.push_back({ y, xr + 1 });// Право
			}
			if (u && yu - 1 >= 0 && !check(yu - 1, x)) {
				possible.push_back({ yu - 1, x });// Вверх
			}
			if (d && yd + 1 < 10 && !check(yd + 1, x)) {
				possible.push_back({ yd + 1, x });// Вниз
			}
			if (possible.size() == 0)
				return addShip(len);
			int rnd = rand() % possible.size();// Рандом
			int yn = possible[rnd].first, xn = possible[rnd].second;
			if (yn == y) {
				u = 0;
				d = 0;
				if (xn == xl - 1)
					xl--;
				else
					xr++;
			}
			else {
				l = 0;
				r = 0;
				if (yn == yu - 1)
					yu--;
				else
					yd++;
			}
			filled.push_back({ yn, xn });
		}
		if (filled.size() == len) {
			for (auto i : filled) {
				int a = i.first, b = i.second;
				arr[a][b] = 'k';
			}
		}
		else
			addShip(len);
	}
	void fillShips()// Заполнение кораблей
	{
		for (int i = 1; i < 5; i++) {
			for (int j = 0; j < 5 - i; j++) {
				addShip(i);
			}
		}
	}
	Table() {
		fillShips();
	}
	Table(bool op) {
		return;
	}
	Line operator[](int ind) { // обращение к линии по индексу
		return arr[ind];
	}
	~Table() {
		delete[] arr;
	}
	void print()// Вывод таблицы
	{
		cout << "  ";
		for (int i = 1; i < 11; i++)
			cout << i << " ";
		cout << endl;
		string s = "abcdefghij";
		for (int i = 0; i < 10; i++)
		{
			cout << s[i] << " ";
			for (int a = 0; a < 10; a++)
			{
				switch(arr[i][a]){
				case 'x':
					SetColor(Red, Black);
					break;
				case 'k':
					SetColor(LightGreen, Black);
					break;
				default:
					SetColor(Blue, Black);
					break;

				}
				cout << arr[i][a] << ' ';

				SetColor(White, Black);
			}
			cout << endl;

		}
		cout << "\n\n";
	}
	void destroyShip(int yu1 = yu, int yd1 = yd, int xl1 = xl, int xr1 = xr)// Уничтожение корабля
	{
		for (int yn = max(yu1 - 1, 0); yn <= min(yd1 + 1, 9); yn++)
		{
			for (int xn = max(xl1 - 1, 0); xn <= min(xr1 + 1, 9); xn++)
			{
				arr[yn][xn] = (arr[yn][xn] == 'x') ? 'x' : 'o';
			}
		}
	}
	bool isShipExist()// Проверка наличия корабля
	{
		if ((xl > 0 && arr[y][xl - 1] == 'k') ||
			(xr < 10 && arr[y][xr + 1] == 'k') ||
			(yu > 0 && arr[yu - 1][x] == 'k') ||
			(yd < 10 && arr[yd + 1][x] == 'k'))
			return 1;
		return 0;
	}

private:
	Line* arr = new Line[10];
	bool check(int y, int x)// Проверка сущуствования кораблей в радиусе 1 клетки
	{
		for (int i = max(x - 1, 0); i <= min(x + 1, 9); i++) {
			for (int j = max(y - 1, 0); j <= min(y + 1, 9); j++) {
				if (arr[j][i] == 'k')
					return 1;
			}
		}
		return 0;
	}
}; 

Table tableplship;
Table tableplshoot(false);
Table tablebotship;
Table tablebotshoot(false);



void aiIfShot(Table tableBot, Table tablePl)// Ход ИИ, если тот попал
{
	if ((l || r || d || u) == 0) {
		l = 1;
		r = 1;
		u = 1;
		d = 1;
		yu = y;
		yd = y;
		xr = x;
		xl = x;
	}
	vector<pair<int, int>> possible;
	if (l && xl - 1 >= 0)
		possible.push_back({ y, xl - 1 });// Лево
	if (r && xr + 1 < 10)
		possible.push_back({ y, xr + 1 });// Право
	if (u && yu - 1 >= 0)
		possible.push_back({ yu - 1, x });// Вверх
	if (d && yd + 1 < 10)
		possible.push_back({ yd + 1, x });// Вниз
	if (possible.size() == 0) {
		cout << "ERROR\n";
		return;
	}
	int rnd = rand() % possible.size();
	int yn = possible[rnd].first, xn = possible[rnd].second;
	if (tablePl[yn][xn] == 'k') {
		if (yn == y) {
			u = d = 0;
			if (xn == xl - 1)
				xl--;
			else
				xr++;
		}
		else {
			r = l = 0;
			if (yn == yu - 1)
				yu--;
			else
				yd++;
		}
		tablePl[yn][xn] = 'x';
		tableBot[yn][xn] = 'x';
		if (!tablePl.isShipExist()) {
			tableBot.destroyShip();
			tablePl.destroyShip();
			shot = 0;
			l = 0;
			r = 0;
			d = 0;
			u = 0;
		}
	}
	else {
		if (xn == xl - 1)
			l = 0;
		else if (xn == xr + 1)
			r = 0;
		else if (yn == yu - 1)
			u = 0;
		else if (yn == yd + 1)
			d = 0;
		tablePl[yn][xn] = 'o';
		tableBot[yn][xn] = 'o';
	}
}

void aiRnd(Table tableBot, Table tablePl)// рнд ход бота
{
	vector<pair<int, int>> free;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (tableBot[i][j] == '.') {
				free.push_back({ i, j });
			}
		}
	}
	int rnd = rand() % free.size();// Рандом координаты
	y = free[rnd].first;
	x = free[rnd].second;
	tableBot[y][x] = (tablePl[y][x] == 'k') ? 'x' : 'o';
	tablePl[y][x] = (tablePl[y][x] == 'k') ? 'x' : 'o';
	if (tableBot[y][x] == 'x')
		shot = 1;
}

void aiHub()// Ход ИИ
{
	if (shot)
		aiIfShot(tablebotshoot, tableplship);
	else
		aiRnd(tablebotshoot, tableplship);
}

bool win(Table tablepl1ship, Table tablepl2ship)// Проверка победы
{
	bool pl1 = 1, pl2 = 1;
	for (int i = 0; i < 10; i++) {

		for (int j = 0; j < 10; j++) {
			if (tablepl1ship[i][j] == 'k') {
				pl1 = 0;
			}
			if (tablepl2ship[i][j] == 'k') {
				pl2 = 0;
			}
		}
	}
	if (pl1) {
		cout << "Player 2 wins";// Победа игрока №2
		return 1;
	}
	if (pl2) {
		cout << "Player 1 wins";// Победа игрока №1
		return 1;
	}
	return 0;
}

pair <int, int> enter()// Ввод координат
{
	string s;
	char le; int num = 0;
	cout << "Введите через пробел номер строки и ячейки:\n";
	cin >> le >> s;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 48 && s[i] <= 57) {
			num = num * 10 + s[i] - 48;
		}
		else if (s[i] != ' ')// Проверка на корректность ввода
		{
			cout << "Error in input\n";
			return enter();
			break;
		}
		if (num > 10) {
			cout << "Number is too big\n";
			return enter();
		}
	}
	while (le < 97 || le > 107)
	{
		cout << "Буква\"" << le << "\" не доступна, введи букву от a до j" << endl;
		cin >> le;
	}
	int y, x;
	x = num - 1;
	y = le - 97;
	return { y, x };
}

void movePl(Table tablePlSi, Table tablePlSo, Table tableOppSi, int num)// Ход игрока, принимает корабли соперника и свои + свое поле стрельбы для num-го игрока
{
	cout << "ход игрок а №" << num << "\n";
	cout << "ваши корабли\n";
	tablePlSi.print();
	cout << "Поле стрельбы\n";
	tablePlSo.print();
	int y, x;
	pair <int, int> p = enter();
	y = p.first;
	x = p.second;
	if (tableOppSi[y][x] == 'k')//    ранен/убит
	{
		int xl = x, xr = x, yu = y, yd = y;
		tableOppSi[y][x] = 'x';
		tablePlSo[y][x] = 'x';
		bool sh = 0;
		while (xl > 0 && (tableOppSi[y][xl - 1] == 'k' || tableOppSi[y][xl - 1] == 'x'))// X - левая
		{
			xl--;
			if (tableOppSi[y][xl] == 'k')
			{
				sh = 1;
				break;
			}
		}
		while (xr < 9 && (tableOppSi[y][xr + 1] == 'k' || tableOppSi[y][xr + 1] == 'x'))// X - правая
		{
			xr++;
			if (tableOppSi[y][xr] == 'k')
			{
				sh = 1;
				break;
			}
		}
		while (yu > 0 && (tableOppSi[yu - 1][x] == 'k' || tableOppSi[yu - 1][x] == 'x'))// Y - верхняя
		{
			yu--;
			if (tableOppSi[yu][x] == 'k')
			{
				sh = 1;
				break;
			}
		}
		while (yd < 9 && (tableOppSi[yd + 1][x] == 'k' || tableOppSi[yd + 1][x] == 'x'))// Y - нижняя
		{
			yd++;
			if (tableOppSi[yd][x] == 'k')
			{
				sh = 1;
				break;
			}
		}
		if (sh)
		{
			cout << "корабль ранен\n";
		}
		else
		{

			cout << "корабль уничтожен\n";
			printf("%d %d %d %d\n", xl, xr, yu, yd);
			tableOppSi.destroyShip(yu, yd, xl, xr);
			tablePlSo.destroyShip(yu, yd, xl, xr);
		}
		movePl(tablePlSi, tablePlSo, tableOppSi, num);
	}

	else    // Мимо
	{
		tableOppSi[y][x] = 'o';
		tablePlSo[y][x] = 'o';
		cout << "мимо\n";
	}

}

void beforeMoves()// Переход хода
{
	cout << "Предыдущий игрок, введите любой символ + enter\n";
	char ch; cin >> ch;
	system("cls");
	cout << "Следующий игрок, нажмите любой сивол + enter\n";
	cin >> ch;
	system("cls");

}

int main() {
	tablebotship.print();
}
