#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

// Deck class represents a collection of cards
class Deck 
{
    private:
        std::vector<Card> cards; // Vector to store the cards in the deck
    public:
        // Constructor to initialize the deck with 52 cards
        Deck();

        // Function to shuffle the deck
        void shuffleDeck();

        // Function to deal one card (removes it from the deck)
        Card dealCard();

        // Function to display all cards in the deck (for debugging)
        void displayDeck() const;

        // Function that resets the deck after each round
        void resetDeck();

        int getDeckSize() const;
};

#endif