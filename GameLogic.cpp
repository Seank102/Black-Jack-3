#include "GameLogic.h"
#include "Card.h"
#include "Player.h"
#include <iostream>

using namespace std;

// Function to calculate the value of a hand
int calculateHandValue(const vector<Card>& hand) {
    int total = 0;  // Total hand value
    int aces = 0;   // Count of Aces in the hand

    for (const auto& card : hand) {
        string rank = card.getRank();

        if (rank == "Jack" || rank == "Queen" || rank == "King") {
            total += 10;  // Face cards are worth 10
        } else if (rank == "Ace") {
            total += 11;  // Assume Ace is worth 11 initially
            aces++;
        } else {
            total += stoi(rank);  // Convert numeric ranks (e.g., "2") to integers
        }
    }

    // Adjust for Aces if total exceeds 21
    while (total > 21 && aces > 0) {
        total -= 10;  // Change an Ace from 11 to 1
        aces--;
    }

    return total;
}

// Helper function for splitting
void splitHands(Deck& deck, vector<Card>& hand) {
    vector<Card> splitHand1 = {hand[0], deck.dealCard()};
    vector<Card> splitHand2 = {hand[1], deck.dealCard()};

    // Dummy flag for doubling down (not applicable during splits)
    bool dummyDoubledDown = false;

    cout << "\nPlaying first split hand:" << endl;
    if (playerTurn(deck, splitHand1, dummyDoubledDown)) {
        cout << "Final total for first hand: " << calculateHandValue(splitHand1) << endl;
    }

    cout << "\nPlaying second split hand:" << endl;
    if (playerTurn(deck, splitHand2, dummyDoubledDown)) {
        cout << "Final total for second hand: " << calculateHandValue(splitHand2) << endl;
    }
}
