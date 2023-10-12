#include <iostream>
using namespace std;

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

int main()
{
    srand(time(NULL));
    char** tableplship = new char* [10];
    char** tableplshoot = new char* [10];
    char** tablebotship = new char* [10];
    char** tablebotshoot = new char* [10];
    filling(tableplship);
    filling(tableplshoot);
    filling(tablebotship);
    filling(tablebotshoot);
    fillShips(tableplship);
    print(tableplship);
}
