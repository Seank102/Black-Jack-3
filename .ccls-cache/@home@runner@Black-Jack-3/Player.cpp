#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "GameLogic.h"
#include <iostream>
using namespace std;

bool playerTurn(Deck& deck, vector<Card>& playerHand, bool& playerDoubledDown) 
{
    while (true) 
    {
        // Display player's hand
        cout << "\nPlayer's hand:" << endl;
        for (const auto& card : playerHand) card.displayCard();
        int total = calculateHandValue(playerHand);
        cout << "Total: " << total << endl;

        if (total > 21) 
        {
            return false; // Player busts
        }

        // Check for doubling down
        if (playerHand.size() == 2 && !playerDoubledDown) 
        {
            char doubleChoice;
            while (true) 
            {   // Loop until valid input
                cout << "\nDo you want to double down? (Y/N): ";
                cin >> doubleChoice;
                cin.clear(); // Clears potential errors
                cin.ignore(100, '\n'); // Clears buffer before input

                if (doubleChoice == 'Y' || doubleChoice == 'y') 
                {
                    playerHand.push_back(deck.dealCard());
                    cout << "\nYou drew:" << endl;
                    playerHand.back().displayCard();

                    total = calculateHandValue(playerHand);
                    cout << "Total: " << total << endl;

                    return total <= 21; // End turn after double down
                } 
                else if (doubleChoice == 'N' || doubleChoice == 'n') 
                {
                    break; // Exit the loop for doubling down
                } 
                else 
                {
                    cout << "Invalid input, please enter Y or N.\n";
                }
            }
        }

        char choice;
        while (true) 
        {   // Loop until valid input
            cout << "\nDo you want to (H)it or (S)tand? ";
            cin >> choice;
            cin.clear(); // Clears potential errors
            cin.ignore(100, '\n'); // Clears buffer before input

            if (choice == 'H' || choice == 'h') 
            {
                playerHand.push_back(deck.dealCard());
                break; // Exit loop to handle the new card
            } 
            else if (choice == 'S' || choice == 's') 
            {
                return true; // Player stands
            } 
            else 
            {
                cout << "Invalid input, please enter H or S.\n";
            }
        }
    }
}