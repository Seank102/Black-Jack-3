#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include "Deck.h"
#include "GameLogic.h"
#include <vector>

bool playerTurn(Deck& deck, std::vector<Card>& playerHand, bool& playerDoubledDown);
int calculateHandValue(const std::vector<Card>& hand);

#endif