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

void filling(char** table)
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

void print(char** table)
{
	for (int i = 0; i < 10; i++)
	{
		for (int a = 0; a < 10; a++)
		{
			cout << table[i][a] << ' ';
		}
		cout << endl;

	}
	cout << "\n\n";
}

bool check(char** table, int y, int x) {
	for (int i = max(x - 1, 0); i <= min(x + 1, 9); i++)
	{
		for (int j = max(y - 1, 0); j <= min(y + 1, 9); j++) {
			if (table[j][i] == 'k')
				return 1;
		}
	}
	return 0;
}

void addShip(char** table, int len) {
	int y, x, rnd, ship = 1, c = 0;
	bool d = 1, u = 1, l = 1, r = 1;
	do {
		y = rand() % 10;
		x = rand() % 10;
	} while (check(table, y, x));
	rnd = rand() % 2;

	if (rnd) {
		int yu = y, yd = y;
		while ((u || d) && ship++ < len) {
			rnd = rand() % 2;
			if (rnd && u && yu - 1 > 0) {
				if (!check(table, yu - 1, x))
					yu--;
				else
					u = 0;
			}
			else if (d && yd + 1 < 10) {
				if (!check(table, yd + 1, x))
					yd++;
				else
					d = 0;
			}
		}
		if (yd - yu == len - 1) {
			for (int i = yu; i <= yd; i++) {
				table[i][x] = 'k';
			}
		}
		else
			addShip(table, len);
		return;
	}
	else {
		int xl = y, xr = y;
		while ((u || d) && ship++ < len) {
			rnd = rand() % 2;
			if (rnd && u && xl - 1 > 0) {
				if (!check(table, x, xl - 1))
					xl--;
				else
					u = 0;
			}
			else if (d && xr + 1 < 10) {
				if (!check(table, x, xr + 1))
					xr++;
				else
					d = 0;
			}
		}
		if (xr - xl == len - 1) {
			for (int i = xl; i <= xr; i++) {
				table[x][i] = 'k';
			}
		}
		else
			addShip(table, len);
		return;
	}
}

void fillShips(char** table) {
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			addShip(table, i);
		}
	}
}

bool win(char** tablepl1ship, char** tablepl2ship) {
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
		cout << "Player 2 wins";
		return 1;
	}
	if (pl2) {
		cout << "Player 1 wins";
		return 1;
	}
	return 0;
}

bool isShipExist(char** table) {
	if ((xl > 0 && table[y][xl-1] == 'k') || (xr < 10 && table[y][xr+1] == 'k') ||
		(yu > 0 && table[yu-1][x] == 'k') || (yd < 10 && table[yd+1][x] == 'k'))
		return 1;
	return 0;
}

void aiIfShot(char** tableBot, char** tablePl) {
	if ((l || r || d || u) == 0) {
		l = 1; r = 1; u = 1; d = 1;
		yu = y; yd = y; xr = x; xl = x;
	}
	vector <pair <int, int>> possible;
	if (l && xl - 1 >= 0)
		possible.push_back({ y, xl - 1 });
	if (r && xr + 1 < 10)
		possible.push_back({ y, xr + 1 });
	if (u && yu - 1 >= 0)
		possible.push_back({ yu - 1, x });
	if (d && yd + 1 < 10)
		possible.push_back({ yd + 1, x });
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
			shot = 0;
			l = 0; r = 0; d = 0; u = 0;
		}
	}
	else {
		if (xn == xl-1)
			l = 0;
		else if (xn == xr+1)
			r = 0;
		else if (yn == yu-1)
			u = 0;
		else if (yn == yd+1)
			d = 0;
		tablePl[yn][xn] = 'o';
		tableBot[yn][xn] = 'o';

	}
}

void aiRnd(char** tableBot, char** tablePl)
{
	vector<pair<int, int>> free;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (tableBot[i][j] == '.')
			{
				free.push_back({ i,j });
			}
		}
	}
	int rnd = rand() % free.size();
	y = free[rnd].first;
	x = free[rnd].second;
	tableBot[y][x] = (tablePl[y][x] == 'k') ? 'x' : 'o';
	tablePl[y][x] = (tablePl[y][x] == 'k') ? 'x' : 'o';
	if (tableBot[y][x] == 'x')
		shot = 1;
}

void aiHub() {
	if (shot)
		aiIfShot(tablebotshoot, tableplship);
	else
		aiRnd(tablebotshoot, tableplship);
}

void preparing_field() {
	filling(tableplshoot);
	filling(tablebotship);
	filling(tablebotshoot);
	filling(tableplship);
	fillShips(tableplship);
	print(tableplship);
}

int main()
{
	srand(time(NULL));
	//preparing_field();
	filling(tableplship);
	filling(tablebotshoot);
	tableplship[1][1+1] = 'k';
	tableplship[1][4+1] = 'k';
	tableplship[1][3+1] = 'k';
	tableplship[1][2+1] = 'k';
	do {
		aiHub();
	} while (!shot);
	do {
		aiHub();
	} while (shot);
	print(tableplship);
	print(tablebotshoot);
}
