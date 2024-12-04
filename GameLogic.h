#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Deck.h"
#include "Card.h"
#include <vector>

int calculateHandValue(const std::vector<Card>& hand);
void splitHands(Deck& deck, std::vector<Card>& hand);

#endif