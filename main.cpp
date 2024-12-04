#include "Deck.h"
#include "Player.h"
#include <vector>
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

// Helper function for dealer's turn
bool dealerTurn(Deck& deck, vector<Card>& dealerHand) {
    cout << "\nDealer's hand:" << endl;
    for (const auto& card : dealerHand) card.displayCard();

    while (calculateHandValue(dealerHand) < 17) {
        cout << "\nDealer hits." << endl;
        // Dealer draws a new card
        Card newCard = deck.dealCard();
        dealerHand.push_back(newCard);

        // Display the new card
        cout << "Dealer drew: ";
        newCard.displayCard();

        // Display the updated total
        int total = calculateHandValue(dealerHand);
        cout << "Dealer's total: " << total << endl;
    }

    int total = calculateHandValue(dealerHand);
    cout << "\nDealer stands with a total of " << total << ".\n";

    if (total > 21) {
        cout << "\nDealer busts! Player wins.\n";
        return false; // Dealer loses
    }

    return true; // Dealer stands
}

// Helper function to evaluate the winner
void evaluateWinner(const vector<Card>& playerHand, const vector<Card>& dealerHand) {
    int playerTotal = calculateHandValue(playerHand);
    int dealerTotal = calculateHandValue(dealerHand);

    if (playerTotal > 21) {
        cout << "You bust! Dealer wins.\n";
    } else if (dealerTotal > 21) {
        cout << "Dealer busts! Player wins.\n";
    } else if (playerTotal > dealerTotal) {
        cout << "Player wins!\n";
    } else if (playerTotal < dealerTotal) {
        cout << "Dealer wins.\n";
    } else {
        cout << "It's a tie!\n";
    }
}

int main() {
    Deck deck; // Create and shuffle the deck
    deck.shuffleDeck();

    char playAgain = 'Y';
    while (playAgain == 'Y' || playAgain == 'y') {
        
        // Reset and shuffle the deck if needed
        if (deck.getDeckSize() < 10) {
            cout << "Reshuffling the deck...\n";
            deck.resetDeck();
            deck.shuffleDeck();
        }
        // Clear player and dealer hands for a fresh round
        vector<Card> playerHand;
        vector<Card> dealerHand;

        // Deal new cards
        playerHand = {deck.dealCard(), deck.dealCard()};
        dealerHand = {deck.dealCard(), deck.dealCard()};
        
        cout << "\nDealer's visible card:" << endl;
        dealerHand[0].displayCard();

        // Check for Blackjack
        int playerTotal = calculateHandValue(playerHand);
        int dealerTotal = calculateHandValue(dealerHand);

        if (playerTotal == 21 && dealerTotal == 21) {
            cout << "\nBoth the player and dealer have Blackjack! It's a tie.\n";
        } else if (playerTotal == 21) {
            cout << "\nPlayer has Blackjack! Player wins.\n";
        } else if (dealerTotal == 21) {
            cout << "\nDealer has Blackjack! Dealer wins.\n";
        } else {
            // Handle splitting
            if (playerHand[0].getRank() == playerHand[1].getRank()) {
                cout << "\nYou have a pair of " << playerHand[0].getRank() << "s. Do you want to split? (Y/N): ";
                char splitChoice;
                cin >> splitChoice;

                if (splitChoice == 'Y' || splitChoice == 'y') {
                    splitHands(deck, playerHand);
                    continue; // Skip to the next round
                }
            }

            //Player's main turn
            bool playerDoubledDown = false;
            bool playerInGame = playerTurn(deck, playerHand, playerDoubledDown);

            if (playerInGame) {
                if (dealerTurn(deck, dealerHand)) {
                    evaluateWinner(playerHand, dealerHand);
                }
            } else {
                cout << "\nTotal: " << calculateHandValue(playerHand) << endl;
                cout << "You bust! Dealer wins.\n";
            }
        }
        //Replay option
        cout << "\nDo you want to play another round? (Y/N): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}