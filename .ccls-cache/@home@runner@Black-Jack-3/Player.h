#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include <vector>

bool playerTurn(Deck& deck, std::vector<Card>& playerHand, bool& playerDoubledDown);

#endif