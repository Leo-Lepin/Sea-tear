#pragma once;
#include "prepare.hpp";


void aiIfShot(char **tableBot, char **tablePl) {
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
    possible.push_back({y, xl - 1});
  if (r && xr + 1 < 10)
    possible.push_back({y, xr + 1});
  if (u && yu - 1 >= 0)
    possible.push_back({yu - 1, x});
  if (d && yd + 1 < 10)
    possible.push_back({yd + 1, x});
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
    } else {
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
  } else {
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

void aiRnd(char **tableBot, char **tablePl) {
  vector<pair<int, int>> free;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (tableBot[i][j] == '.') {
        free.push_back({i, j});
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
