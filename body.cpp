#include <iostream>
#include <vector>
using namespace std;

char** tableplship = new char* [10];
char** tableplshoot = new char* [10];
char** tablebotship = new char* [10];
char** tablebotshoot = new char* [10];
bool shot = 0, l = 0, r = 0, u = 0, d = 0;
int xl, xr, yu, yd;
int x, y;

void filling(char** table)// Заполнение таблицы
{
	for (int i = 0; i < 10; i++)
	{
		table[i] = new char[10];
		for (int a = 0; a < 10; a++)
		{
			table[i][a] = '.';
		}

	}
}

void print(char** table)// Вывод таблицы
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
			cout << table[i][a] << ' ';
		}
		cout << endl;

	}
	cout << "\n\n";
}

bool check(char** table, int y, int x)// Проверка сущуствования кораблей в радиусе 1 клетки
{
	for (int i = max(x - 1, 0); i <= min(x + 1, 9); i++) {
		for (int j = max(y - 1, 0); j <= min(y + 1, 9); j++) {
			if (table[j][i] == 'k')
				return 1;
		}
	}
	return 0;
}

void addShip(char** table, int len)// Добавление корабля рнд
{
	int rnd, ship = 1, xl, yu, xr, yd;
	bool d = 1, u = 1, l = 1, r = 1;
	do {
		y = rand() % 10;
		x = rand() % 10;
	} while (check(table, y, x));
	xl = x;
	xr = x;
	yu = y;
	yd = y;
	vector<pair<int, int>> filled = { {y, x} };
	while (ship++ < len) {
		vector<pair<int, int>> possible;
		if (l && xl - 1 >= 0 && !check(table, y, xl - 1)) {
			possible.push_back({ y, xl - 1 });// Лево
		}
		if (r && xr + 1 < 10 && !check(table, y, xr + 1)) {
			possible.push_back({ y, xr + 1 });// Право
		}
		if (u && yu - 1 >= 0 && !check(table, yu - 1, x)) {
			possible.push_back({ yu - 1, x });// Вверх
		}
		if (d && yd + 1 < 10 && !check(table, yd + 1, x)) {
			possible.push_back({ yd + 1, x });// Вниз
		}
		if (possible.size() == 0)
			return addShip(table, len);
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
			table[a][b] = 'k';
		}
	}
	else
		addShip(table, len);
}

void fillShips(char** table)// Заполнение кораблей
{
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			addShip(table, i);
		}
	}
}

void destroyShip(char** table, int yu1 = yu, int yd1 = yd, int xl1 = xl, int xr1 = xr)// Уничтожение корабля
{
	for (int yn = max(yu1 - 1, 0); yn <= min(yd1 + 1, 9); yn++)
	{
		for (int xn = max(xl1 - 1, 0); xn <= min(xr1 + 1, 9); xn++)
		{
			table[yn][xn] = (table[yn][xn] == 'x') ? 'x' : 'o';
		}
	}
}

void preparing_field()// Заполнение полей
{
	filling(tableplshoot);
	filling(tablebotship);
	filling(tablebotshoot);
	filling(tableplship);
	fillShips(tableplship);
	fillShips(tablebotship);
	// addShip(tableplship, 4);
	print(tableplship);
}

void del()// Удаление полей
{
	for (int i = 0; i < 10; i++)
	{
		delete[] tableplship[i];
		delete[] tableplshoot[i];
		delete[] tablebotship[i];
		delete[] tablebotshoot[i];
	}
	delete[] tableplship;
	delete[] tableplshoot;
	delete[] tablebotship;
	delete[] tablebotshoot;
}

bool isShipExist(char** table)// Проверка наличия корабля
{
	if ((xl > 0 && table[y][xl - 1] == 'k') ||
		(xr < 10 && table[y][xr + 1] == 'k') ||
		(yu > 0 && table[yu - 1][x] == 'k') ||
		(yd < 10 && table[yd + 1][x] == 'k'))
		return 1;
	return 0;
}

void aiIfShot(char** tableBot, char** tablePl)// Ход ИИ, если тот попал
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
		if (!isShipExist(tablePl)) {
			destroyShip(tableBot);
			destroyShip(tablePl);
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

void aiRnd(char** tableBot, char** tablePl)// рнд ход бота
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

bool win(char** tablepl1ship, char** tablepl2ship)// Проверка победы
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

void movePl(char** tablePlSi, char** tablePlSo, char** tableOppSi, int num)// Ход игрока, принимает корабли соперника и свои + свое поле стрельбы для num-го игрока
{
	cout << "ход игрок а №" << num << "\n";
	cout << "ваши корабли\n";
	print(tablePlSi);
	cout << "Поле стрельбы\n";
	print(tablePlSo);
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
			destroyShip(tableOppSi, yu, yd, xl, xr);
			destroyShip(tablePlSo, yu, yd, xl, xr);
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
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	preparing_field();// Инициализация полей
	for (int i = 0; i < 1000000000; i++) {
		beforeMoves();
		pair <int, int> p = enter();
		int y = p.first, x = p.second;
		cout << y << " " << x << endl;
	}
	del();
}
