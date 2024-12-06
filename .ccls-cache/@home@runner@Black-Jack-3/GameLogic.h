#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <vector>

int calculateHandValue(const std::vector<Card>& hand);
void splitHands(Deck& deck, std::vector<Card>& originalHand, std::vector<Card>& dealerHand);
bool dealerTurn(Deck& deck, std::vector<Card>& dealerHand);
void evaluateWinner(const std::vector<Card>& playerHand, const std::vector<Card>& dealerHand);
void calculateWinningProbability(const std::vector<Card>& playerHand, const std::vector<Card>& dealerHand, const Deck& deck, double& probabilityWinIfHit, double& probabilityWinIfStand, double& probabilityBustIfHit);
int simulateDealer(const std::vector<Card>& dealerHand, const std::vector<Card>& remainingCards);
int simulateDealerRecursive(const std::vector<Card>* dealerHand, const std::vector<Card>* remainingCards);

#endif