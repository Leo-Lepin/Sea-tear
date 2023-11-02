#pragma once
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

bool shot = 0, l = 0, r = 0, u = 0, d = 0;
int xl, xr, yu, yd;
int x, y, cnt = 0;

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

class Table {
public:
    Table(vector <string> l) {
        arr.resize(10, "..........");
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
        srand(time(NULL) + cnt++);
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 5 - i; j++) {
                addShip(i);
            }
        }
    }
    Table() {
        arr.resize(10, "..........");
        fillShips();
    }
    Table(bool op) {

        arr.resize(10, "..........");
        return;
    }
    string& operator[](int ind) { // обращение к линии по индексу
        return arr[ind];
    }
    /*~Table() {
        delete[] arr;
    }*/
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
                switch (arr[i][a]) {
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
    bool isShipExist(int x, int y)// Проверка наличия корабля
    {
        int xl = x;
        while (xl > 9 && (arr[y][xl - 1] == 'x' || arr[y][xl - 1] == 'k')) {
            xl--;
            if (arr[y][xl] == 'k')
                return 1;
        }
        int xr = x;
        while (xr < 9 && (arr[y][xr + 1] == 'x' || arr[y][xr + 1] == 'k')) {
            xr++;
            if (arr[y][xr] == 'k')
                return 1;
        }
        int yu = y;
        while (yu > 0 && (arr[yu - 1][x] == 'x' || arr[yu - 1][x] == 'k')) {
            yu--;
            if (arr[yu][x] == 'k')
                return 1;
        }
        int yd = y;
        while (yd < 9 && (arr[yd + 1][x] == 'x' || arr[yd + 1][x] == 'k')) {
            yd++;
            if (arr[yd][x] == 'k')
                return 1;
        }
        return 0;
    }
    bool win() {
        for (int i = 0; i < 10; i++) {

            for (int j = 0; j < 10; j++) {
                if (arr[i][j] == 'k') {
                    return 0;
                }
                if (arr[i][j] == 'k') {
                    return 0;
                }
            }
        }
        return 1;
    }
private:
    vector <string> arr;
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

