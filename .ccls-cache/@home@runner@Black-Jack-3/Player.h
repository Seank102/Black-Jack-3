#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include "Deck.h"
#include "GameLogic.h"
#include <vector>

bool playerTurn(Deck& deck, std::vector<Card>& playerHand, std::vector<Card>& dealerHand, bool& playerDoubledDown);
int calculateHandValue(const std::vector<Card>& hand);
void recalculateAndDisplayProbabilities(const std::vector<Card>& playerHand, const std::vector<Card>& dealerHand, const Deck& deck);

#endif