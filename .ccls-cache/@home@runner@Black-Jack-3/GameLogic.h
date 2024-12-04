#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <vector>

int calculateHandValue(const std::vector<Card>& hand);
void splitHands(Deck& deck, std::vector<Card>& hand);
bool dealerTurn(Deck& deck, std::vector<Card>& dealerHand);
void evaluateWinner(const std::vector<Card>& playerHand, const std::vector<Card>& dealerHand);

#endif