#include "Deck.h"
#include <iostream>
#include <set> // For ensuring unique cards
using namespace std;

int main() {
    // Step 1: Initialize the Deck
    Deck deck;
    cout << "Initial Deck:" << endl;
    deck.displayDeck();

    // Step 2: Verify Deck Contains 52 Cards
    cout << "\nTest 1: Verify Initial Deck Size" << endl;
    if (deck.getDeckSize() == 52) {
        cout << "PASS: Deck has 52 cards." << endl;
    } else {
        cout << "FAIL: Deck does not have 52 cards." << endl;
    }

    // Step 3: Shuffle the Deck and Check Order
    cout << "\nTest 2: Shuffle the Deck" << endl;
    deck.shuffleDeck();
    cout << "Shuffled Deck:" << endl;
    deck.displayDeck();

    // Step 4: Deal a Card and Verify Deck Size Reduces
    cout << "\nTest 3: Deal One Card" << endl;
    Card dealtCard = deck.dealCard();
    cout << "Dealt Card: ";
    dealtCard.displayCard();
    if (deck.getDeckSize() == 51) {
        cout << "PASS: Deck size is now 51." << endl;
    } else {
        cout << "FAIL: Deck size is not 51." << endl;
    }

    // Step 5: Reset the Deck
    cout << "\nTest 4: Reset the Deck" << endl;
    deck.resetDeck();
    cout << "Reset Deck:" << endl;
    deck.displayDeck();
    if (deck.getDeckSize() == 52) {
        cout << "PASS: Deck is reset to 52 cards." << endl;
    } else {
        cout << "FAIL: Deck size after reset is not 52." << endl;
    }

    return 0;
}