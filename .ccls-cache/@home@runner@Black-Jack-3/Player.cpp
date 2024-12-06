#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include "GameLogic.h"
#include <iostream>
using namespace std;

bool playerTurn(Deck& deck, std::vector<Card>& playerHand, std::vector<Card>& dealerHand, bool& playerDoubledDown) 
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

        double probabilityWinIfHit = 0.0;
        double probabilityWinIfStand = 0.0;
        double probabilityBustIfHit = 0.0;

        calculateWinningProbability(playerHand, dealerHand, deck, probabilityWinIfHit, probabilityWinIfStand, probabilityBustIfHit);

        // Display the probabilities
        std::cout << "Probability of winning if you hit: " << probabilityWinIfHit * 100 << "%\n";
        std::cout << "Probability of winning if you stand: " << probabilityWinIfStand * 100 << "%\n";
        std::cout << "Probability of busting if you hit: " << probabilityBustIfHit * 100 << "%\n";
        
        while (true) 
        {   // Loop until valid input
            cout << "\nDo you want to (H)it or (S)tand? ";
            cin >> choice;
            cin.clear(); // Clears potential errors
            cin.ignore(100, '\n'); // Clears buffer before input

            if (choice == 'H' || choice == 'h') 
            {
                playerHand.push_back(deck.dealCard());
                std::cout << "\nYou drew:\n";
                playerHand.back().displayCard(); // Display the new card
                if (calculateHandValue(playerHand) > 21) 
                {
                    return false; // End the turn
                }
                // **Recalculate probabilities after the hit**
                double probabilityWinIfHit = 0.0;
                double probabilityWinIfStand = 0.0;
                double probabilityBustIfHit = 0.0;

                calculateWinningProbability(playerHand, dealerHand, deck, probabilityWinIfHit, probabilityWinIfStand, probabilityBustIfHit);

                // Display the probabilities
                std::cout << "Probability of winning if you hit: " << probabilityWinIfHit * 100 << "%\n";
                std::cout << "Probability of winning if you stand: " << probabilityWinIfStand * 100 << "%\n";
                std::cout << "Probability of busting if you hit: " << probabilityBustIfHit * 100 << "%\n";
                
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