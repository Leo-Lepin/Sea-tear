#pragma once
#include "Bot.hpp"

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

void movePl(Table& tablePlSi, Table& tablePlSo, Table& tableOppSi, int num)// Ход игрока, принимает корабли соперника и свои + свое поле стрельбы для num-го игрока
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

void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void beforeMoves()// Переход хода
{
    cout << "Предыдущий игрок, введите любой символ + enter\n";
    char ch; cin >> ch;
    ClearScreen();
    cout << "Следующий игрок, нажмите любой сивол + enter\n";
    cin >> ch;
    ClearScreen();
}

void game(int num)
{
    if (num == 1) {
        while (!(tableplship.win() || tablebotship.win()))
        {
            movePl(tableplship, tableplshoot, tablebotship, 1);
            if (tablebotship.win())
            {
                cout << "Победа первого игрока\n";
                break;
            }
            beforeMoves();
            movePl(tablebotship, tablebotshoot, tableplship, 2);
            if (tableplship.win())
            {
                cout << "Победа второго игрока\n";
                break;
            }
            beforeMoves();
        }
    }
    else {
        while (!(tableplship.win() || tablebotship.win()))
        {
            movePl(tableplship, tableplshoot, tablebotship, 1);
            if (tablebotship.win())
            {
                cout << "Победа первого игрока\n";
                break;
            }
            aiHub();
            if (tableplship.win())
            {
                cout << "Победа второго игрока\n";
                break;
            }
        }
    }
}
