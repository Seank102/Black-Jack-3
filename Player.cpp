#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "GameLogic.h"
#include <iostream>
using namespace std;

bool playerTurn(Deck& deck, vector<Card>& playerHand, bool& playerDoubledDown) {
    while (true) {
        // Display player's hand
        cout << "\nPlayer's hand:" << endl;
        for (const auto& card : playerHand) card.displayCard();
        int total = calculateHandValue(playerHand);
        cout << "Total: " << total << endl;

        if (total > 21) {
            return false; // Player busts
        }

        // Check for doubling down
        if (playerHand.size() == 2 && !playerDoubledDown) {
            cout << "\nDo you want to double down? (Y/N): ";
            char doubleChoice;
            cin >> doubleChoice;

            if (doubleChoice == 'Y' || doubleChoice == 'y') {
                playerHand.push_back(deck.dealCard());
                cout << "\nYou drew:" << endl;
                playerHand.back().displayCard();

                total = calculateHandValue(playerHand);
                cout << "Total: " << total << endl;

                return total <= 21; // End turn after double down
            }
        }

        // Hit or stand
        cout << "\nDo you want to (H)it or (S)tand? ";
        char choice;
        cin >> choice;

        if (choice == 'H' || choice == 'h') {
            playerHand.push_back(deck.dealCard());
        } else if (choice == 'S' || choice == 's') {
            return true; // Player stands
        }
    }
}