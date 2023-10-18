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
	if ((xl > 0 && table[xl][y] != 'k') && (xr < 10 && table[xr][y] != 'k') &&
		(yu > 0 && table[x][yu] != 'k') && (yd < 10 && table[x][yd] != 'k'))
		return 0;
	return 1;
}

void aiIfShot(char** tableBot, char** tablePl) {
	int xn = -1, yn = -1;
	if ((l || r || u || d) == 0) {
		l = 1; r = 1; d = 1; u = 1;
		yd = yu = y;
		xr = xl = x;
	}
	int rnd = rand() % 2;

	if (rnd && (yu - 1 > 0 || yd + 1 < 10) || (l + r == 0)) {
		rnd = rand() % 2;
		if (rnd && u && yu - 1 >= 0) {
			xn = x; yn = yu-1;
			if (tablePl[yu-1][x] == 'k')
			{

				yu--;
				tablePl[yu][x] = 'x';
				tableBot[yu][x] = 'x';
				l = r = 0;
				return;
			}
			else
				u = 0;
		}
		else if (d && yd + 1 <= 10) {
			xn = x; yn = ++yd;
			if (tablePl[yd][x] == 'k')
			{
				tablePl[yd][x] = 'x';
				tableBot[yd][x] = 'x';
				l = r = 0;
				return;
			}
			else
				d = 0;
		}

	}
	else {
		rnd = rand() % 2;
		if (rnd && l && xl - 1 >= 0) {
			xn = xl-1; yn = y;
			if (tablePl[y][xl - 1] == 'k')
			{
				xl--;
				tablePl[y][xl] = 'x';
				tableBot[y][xl] = 'x';
				u = d = 0;
				return;
			}
			else
				l = 0;
		}
		else if (d && xr + 1 <= 10) {
			xn = xr+1; yn = y;
			if (tablePl[y][xr + 1] == 'k')
			{
				xr++;
				tablePl[y][xr] = 'x';
				tableBot[y][xr] = 'x';
				u = d = 0;
				return;
			}
			else
				r = 0;
		}
	}
	tableBot[yn][xn] = 'o';
	tablePl[yn][xn] = 'o';
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
	int y = free[rnd].first;
	int x = free[rnd].second;
	tableBot[y][x] = (tablePl[y][x] == 'k') ? 'x' : 'o';
}

void aiHub() {
	if (shot && !isShipExist(tableplship))
		shot = 0;
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
	tableplship[1][0] = 'k';
	tableplship[1][1] = 'x';
	tablebotshoot[1][1] = 'x';
	tableplship[1][2] = 'k';
	tableplship[1][3] = 'k';
	y = 1; x = 1;
	shot = 1;
	aiIfShot(tablebotshoot, tableplship);
	aiIfShot(tablebotshoot, tableplship);
	print(tableplship);
	print(tablebotshoot);
}
