#include <stdio.h>
#include <stdlib.h>
#include "battle.h"

int whowinbattlegotchi(Tamagotchi *player0, Tamagotchi *player1) {
  int life0, life1, rintelligenceinbase0, rstrengthinbase0, ragilityinbase0,
      rdefendinbase0, rlifeinbase0, attack, ram0, ram1;

 ram0 = rand() % 3;
 ram1 = rand() % 3;

  life0 = player0->life * player0->evolution;
  life1 = player1->life * player1->evolution;
  rlifeinbase0 = life0 - life1;
  rintelligenceinbase0 = (player0->intelligence * ram0) - (player1->intelligence * ram1);
  rstrengthinbase0 =
      ((player0->strength + ((player0->strength / 2)) * (player0->critic + ram0)) -
      ((player1->strength + ((player1->strength / 2)) * (player1->critic + ram1))));
  ragilityinbase0 = (player0->agility * ram0) - (player1->agility * ram1);
  rdefendinbase0 = (player0->defend + (player0->critic + ram0)) - player1->defend + (player1->critic + ram1);
  attack = rlifeinbase0 + rstrengthinbase0 + ragilityinbase0 + rdefendinbase0 +
           rlifeinbase0;
  if (attack <= 0)
    return 1;
  else
    return 0;
}