#include "Player.h"
#include <iostream>
using namespace std;

bool playerTurn(Deck& deck, vector<Card>& playerHand, bool& playerDoubledDown) {
    while (true) {
        cout << "\nPlayer's hand:" << endl;
        for (const auto& card : playerHand) card.displayCard();
        int total = calculateHandValue(playerHand);
        cout << "Total: " << total << endl;

        if (total > 21) {
            cout << "You bust! Dealer wins.\n";
            return false; // Player loses
        }

        // Check for doubling down (only allowed on the first turn)
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

                if (total > 21) {
                    cout << "You bust! Dealer wins.\n";
                    return false; // Player loses
                }

                cout << "Your turn ends after doubling down.\n";
                playerDoubledDown = true;
                return true; // Player stands after doubling down
            }
        }

        // Regular actions: Hit or Stand
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