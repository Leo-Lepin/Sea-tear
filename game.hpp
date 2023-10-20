#pragma once;
#include "bot.hpp";


bool win(char **tablepl1ship, char **tablepl2ship) {
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
