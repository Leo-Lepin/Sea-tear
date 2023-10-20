#pragma once;

#include <iostream>
#include <vector>

using namespace std;

char **tableplship = new char *[10];
char **tableplshoot = new char *[10];
char **tablebotship = new char *[10];
char **tablebotshoot = new char *[10];
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

void print(char **table) 
{
  for (int i = 0; i < 10; i++) {
    for (int a = 0; a < 10; a++) {
      cout << table[i][a] << ' ';
    }
    cout << endl;
  }
  cout << "\n\n";
}

bool check(char **table, int y, int x) 
{
  for (int i = max(x - 1, 0); i <= min(x + 1, 9); i++) {
    for (int j = max(y - 1, 0); j <= min(y + 1, 9); j++) {
      if (table[j][i] == 'k')
        return 1;
    }
  }
  return 0;
}

void addShip(char **table, int len) 
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
  vector<pair<int, int>> filled = {{y, x}};
  while (ship++ < len) {
    vector<pair<int, int>> possible;
    if (l && xl - 1 >= 0 && !check(table, y, xl - 1)) {
      possible.push_back({y, xl - 1});
    }
    if (r && xr + 1 < 10 && !check(table, y, xr + 1)) {
      possible.push_back({y, xr + 1});
    }
    if (u && yu - 1 >= 0 && !check(table, yu - 1, x)) {
      possible.push_back({yu - 1, x});
    }
    if (d && yd + 1 < 10 && !check(table, yd + 1, x)) {
      possible.push_back({yd + 1, x});
    }
    if (possible.size() == 0)
      return addShip(table, len);
    int rnd = rand() % possible.size();
    int yn = possible[rnd].first, xn = possible[rnd].second;
    if (yn == y) {
      u = 0;
      d = 0;
      if (xn == xl - 1)
        xl--;
      else
        xr++;
    } else {
      l = 0;
      r = 0;
      if (yn == yu - 1)
        yu--;
      else
        yd++;
    }
    filled.push_back({yn, xn});
  }
  if (filled.size() == len) {
    for (auto i : filled) {
      int a = i.first, b = i.second;
      table[a][b] = 'k';
    }
  } else
    addShip(table, len);
}

void fillShips(char **table) 
{
  for (int i = 1; i < 5; i++) {
    for (int j = 0; j < 5 - i; j++) {
      addShip(table, i);
    }
  }
}


bool isShipExist(char **table) 
{
  if ((xl > 0 && table[y][xl - 1] == 'k') ||
      (xr < 10 && table[y][xr + 1] == 'k') ||
      (yu > 0 && table[yu - 1][x] == 'k') ||
      (yd < 10 && table[yd + 1][x] == 'k'))
    return 1;
  return 0;
}

void destroyShip(char **table) 
{
  for (int yn = max(yu - 1, 0); yn <= min(yd + 1, 9); yn++) {
    for (int xn = max(xl - 1, 0); xn <= min(xr + 1, 9); xn++) {
      table[yn][xn] = (table[yn][xn] == 'x') ? 'x' : 'o';
    }
  }
}

void preparing_field() {
  filling(tableplshoot);
  filling(tablebotship);
  filling(tablebotshoot);
  filling(tableplship);
  fillShips(tableplship);
  fillShips(tablebotship);
  // addShip(tableplship, 4);
  print(tableplship);
}

void del() {
  for (int i = 0; i < 10; i++) {
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
