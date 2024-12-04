#include "Deck.h"
#include "Player.h"
#include "GameLogic.h"
#include "Card.h"
#include <vector>
#include <iostream>
using namespace std;


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
            cout << "\nBoth the player and dealer have Blackjack! It's a tie.\n";}
        else if (playerTotal == 21) {
            cout << "\nPlayer has Blackjack! Player wins.\n";}
        else if (dealerTotal == 21) {
            cout << "\nDealer has Blackjack! Dealer wins.\n";}
        else {
            // Check if the player can split
        if (playerHand.size() == 2 && playerHand[0].getRank() == playerHand[1].getRank()) {
            cout << "You have a pair! Would you like to split? (y/n): ";
            char choice;
            cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                splitHands(deck, playerHand, dealerHand);
             
            // Ask if the player wants to play again once they finish the split logic
        char playAgainSplit;
        cout << "\nDo you want to play another round? (Y/N): ";
        cin >> playAgainSplit;
                    if (playAgainSplit == 'Y' || playAgainSplit == 'y') {
                    continue; // Starts a new round
                    } else {
                    break; // Exits the game
                }
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