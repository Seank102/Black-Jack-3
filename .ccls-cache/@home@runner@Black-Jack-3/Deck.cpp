#include "Deck.h"
#include <stdexcept>
#include <random>
#include <algorithm>
using namespace std;

// Initializes the deck with all 52 cards
Deck::Deck() {
    for (int s = CLUBS; s <= DIAMONDS; ++s) {  // Loop through all suits
        for (int r = TWO; r <= ACE; ++r) {    // Loop through all ranks
            cards.push_back(Card(static_cast<Rank>(r), static_cast<Suit>(s)));
        }
    }
}

// Shuffles the deck using a random number generator
void Deck::shuffleDeck() {
    random_device rd;    // Seed for random number generator
    mt19937 g(rd());     // Mersenne Twister RNG
    shuffle(cards.begin(), cards.end(), g); // Shuffle the cards
}

// Deals one card from the deck (removes it and returns it)
Card Deck::dealCard() {
    if (!cards.empty()) {              // Check if the deck is not empty
        Card dealtCard = cards.back(); // Get the top card
        cards.pop_back();              // Remove the top card
        return dealtCard;              // Return the dealt card
    }
    throw runtime_error("No cards left in the deck!"); // Error if deck is empty
}

// Displays all cards in the deck (useful for debugging)
void Deck::displayDeck() const {
    for (const auto& card : cards) {
        card.displayCard();
    }
}
