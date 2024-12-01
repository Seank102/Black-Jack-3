#ifndef CARD_H
#define CARD_H

#include <string>

// Enum for the rank of a card (e.g., 2, 3, ..., Ace)
enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };

// Enum for the suit of a card (e.g., Hearts, Spades, etc.)
enum Suit { CLUBS, SPADES, HEARTS, DIAMONDS };

// Card class represents a single card in the deck
class Card {
private:
    Rank rank; // Rank of the card
    Suit suit; // Suit of the card
public:
    // Constructor to initialize the card with a rank and suit
    Card(Rank r, Suit s);

    // Function to return the rank as a string (e.g., "10", "Ace")
    std::string getRank() const;

    // Function to return the suit as a string (e.g., "Hearts", "Clubs")
    std::string getSuit() const;

    // Function to display the card as "Rank of Suit" (e.g., "10 of Hearts")
    void displayCard() const;
};

#endif
