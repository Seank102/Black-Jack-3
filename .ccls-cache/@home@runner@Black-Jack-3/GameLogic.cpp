#include "GameLogic.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Helper function to evaluate the winner
void evaluateWinner(const vector<Card>& playerHand, const vector<Card>& dealerHand) 
{
    int playerTotal = calculateHandValue(playerHand);
    int dealerTotal = calculateHandValue(dealerHand);

    if (playerTotal > 21) 
    {
        cout << "You bust! Dealer wins.\n";
    }
    else if (dealerTotal > 21) 
    {
        cout << "Dealer busts! Player wins.\n";
    }
    else if (playerTotal > dealerTotal) 
    {
        cout << "Player wins with " << playerTotal << "!\n";
    }
    else if (playerTotal < dealerTotal) 
    {
        cout << "Dealer wins.\n";
    }
    else 
    {
        cout << "It's a push!\n";
    }
}

// Function to calculate the value of a hand
int calculateHandValue(const vector<Card>& hand) 
{
    int total = 0;  // Total hand value
    int aces = 0;   // Count of Aces in the hand

    for (const auto& card : hand) 
    {
        string rank = card.getRank();

        if (rank == "Jack" || rank == "Queen" || rank == "King") 
        {
            total += 10;  // Face cards are worth 10
        } 
        else if (rank == "Ace") 
        {
            total += 11;  // Assume Ace is worth 11 initially
            aces++;
        } 
        else 
        {
            total += stoi(rank);  // Convert numeric ranks (e.g., "2") to integers
        }
    }

    // Adjust for Aces if total exceeds 21
    while (total > 21 && aces > 0) 
    {
        total -= 10;  // Change an Ace from 11 to 1
        aces--;
    }

    return total;
}
//Dealer's Turn
bool dealerTurn(Deck& deck, vector<Card>& dealerHand) 
{
    cout << "\nDealer's hand:" << endl;
    for (const auto& card : dealerHand) card.displayCard();

    while (calculateHandValue(dealerHand) < 17) 
    {
        cout << "\nDealer hits." << endl;

        // Dealer draws a card
        Card newCard = deck.dealCard();
        dealerHand.push_back(newCard);

        // Show the new card
        cout << "Dealer drew: ";
        newCard.displayCard();

        // Show updated total
        int total = calculateHandValue(dealerHand);
        cout << "Dealer's total: " << total << endl;
    }

    int total = calculateHandValue(dealerHand);
    cout << "\nDealer stands with a total of " << total << ".\n";

    if (total > 21) 
    {
        cout << "\nDealer busts. Player wins!\n";
        return false; // Dealer loses
    }
    else return true; // Dealer stands
    
}

// Helper function for splitting
void splitHands(Deck& deck, vector<Card>& originalHand, vector<Card>& dealerHand) 
{
    if (originalHand.size() != 2 || originalHand[0].getRank() != originalHand[1].getRank()) 
    {
        cout << "Splitting not possible. Hands must contain two cards of the same rank.\n";
        return;
    }

    // Create two split hands
    vector<Card> hand1 = {originalHand[0], deck.dealCard()};
    vector<Card> hand2 = {originalHand[1], deck.dealCard()};

    // Play the first split hand
    cout << "\nPlaying first split hand:\n";
    bool playerDoubledDown1 = false;
    bool hand1InGame = playerTurn(deck, hand1, dealerHand, playerDoubledDown1);
    int total1 = calculateHandValue(hand1);
    
    if (hand1InGame) 
    {
        cout << "Final total for first hand: " << total1 << endl;
    }
    else 
    {
        cout << "First hand busts with a total of " << total1 << endl;
    }

    // Play the second split hand
    cout << "\nPlaying second split hand:\n";
    bool playerDoubledDown2 = false;
    bool hand2InGame = playerTurn(deck, hand2, dealerHand, playerDoubledDown2);
    int total2 = calculateHandValue(hand2);
    
    if (hand2InGame) 
    {
        cout << "Final total for second hand: " << total2 << endl;
    }
    else 
    {
        cout << "Second hand busts with a total of " << total2 << endl;
    }

    // Dealer's turn and evaluation
    cout << "\nDealer's turn:\n";
    bool dealerStand = dealerTurn(deck, dealerHand);
    int dealerTotal = calculateHandValue(dealerHand);
    
    if (!dealerStand) 
    {
        cout << "Dealer busts! ";
        if (hand1InGame) cout << "First hand wins. ";
        if (hand2InGame) cout << "Second hand wins.\n";
    }
    else 
    {
        if (hand1InGame && total1 > dealerTotal && total1 <= 21) 
        {
            cout << "First hand wins against the dealer.\n";
        }
        else if (hand1InGame && total1 == dealerTotal) 
        {
            cout << "First hand ties with the dealer.\n";
        }
        else if (total1 > 21 || total1 < dealerTotal) 
        {
            cout << "First hand loses to the dealer.\n";
        }

        if (hand2InGame && total2 > dealerTotal && total2 <= 21) 
        {
            cout << "Second hand wins against the dealer.\n";
        }
        else if (hand2InGame && total2 == dealerTotal) 
        {
            cout << "Second hand ties with the dealer.\n";
        }
        else if (total2 > 21 || total2 < dealerTotal) 
        {
            cout << "Second hand loses to the dealer.\n";
        }
    }
    //Clears all hands
    originalHand.clear();
}

int simulateDealerRecursive(const std::vector<Card>* dealerHand, const std::vector<Card>* remainingCards, int depth = 0, int maxDepth = 10) 
{
    int dealerTotal = calculateHandValue(*dealerHand);

    // Base cases: Dealer stands, busts, or recursion limit reached
    if (dealerTotal >= 17 || depth >= maxDepth) {
        return dealerTotal; // Dealer stands or recursion limit
    }
    if (dealerTotal > 21) {
        return 0; // Dealer busts
    }

    int bestOutcome = 0; // Track the best valid dealer outcome

    for (size_t i = 0; i < remainingCards->size(); ++i) {
        // Create local copies for this branch
        std::vector<Card> nextHand = *dealerHand;
        std::vector<Card> nextDeck = *remainingCards;

        nextHand.push_back((*remainingCards)[i]); // Add card to dealer's hand
        nextDeck.erase(nextDeck.begin() + i);    // Remove card from deck

        int outcome = simulateDealerRecursive(&nextHand, &nextDeck, depth + 1, maxDepth);

        if (outcome <= 21) {
            bestOutcome = std::max(bestOutcome, outcome);
        }
    }

    return bestOutcome;
}

int simulateDealer(const std::vector<Card>& dealerHand, const std::vector<Card>& remainingCards) 
{
    return simulateDealerRecursive(&dealerHand, &remainingCards, 0, 10); // Start recursion with depth 0
}

void simulatePlayerRecursive(
    const std::vector<Card>* playerHand,
    const std::vector<Card>* dealerHand,
    const std::vector<Card>* remainingCards,
    int& winsIfHit,
    int& bustsIfHit,
    int& totalSimulationsForHit,
    int depth = 0,
    int maxDepth = 10)
{
    int playerTotal = calculateHandValue(*playerHand);

    // Base case: Player busts or max recursion depth reached
    if (playerTotal > 21 || depth >= maxDepth) {
        if (playerTotal > 21) {
            bustsIfHit++;
        }
        totalSimulationsForHit++;
        return;
    }

    for (size_t i = 0; i < remainingCards->size(); ++i) {
        // Create local copies for this branch
        std::vector<Card> nextPlayerHand = *playerHand;
        std::vector<Card> nextDeck = *remainingCards;

        nextPlayerHand.push_back((*remainingCards)[i]);  // Add card to player's hand
        nextDeck.erase(nextDeck.begin() + i);           // Remove card from deck

        // Simulate dealer outcomes for this branch
        if (calculateHandValue(nextPlayerHand) <= 21) {
            int simulatedDealerTotal = simulateDealer(*dealerHand, nextDeck);

            if (simulatedDealerTotal == 0 || calculateHandValue(nextPlayerHand) > simulatedDealerTotal) {
                winsIfHit++;
            }
        }

        // Recurse for the next card
        simulatePlayerRecursive(&nextPlayerHand, dealerHand, &nextDeck, winsIfHit, bustsIfHit, totalSimulationsForHit, depth + 1, maxDepth);
    }

    totalSimulationsForHit++; // Count this path as one simulation
}

// Wrapper function to calculate winning probabilities with recursive player simulation
void calculateWinningProbability(
    const std::vector<Card>& playerHand,
    const std::vector<Card>& dealerHand,
    const Deck& deck,
    double& probabilityWinIfHit,
    double& probabilityWinIfStand,
    double& probabilityBustIfHit)
{
    int totalSimulationsForHit = 0;
    int totalSimulationsForStand = 1; // Only one simulation for standing
    int winsIfHit = 0;
    int winsIfStand = 0;
    int bustsIfHit = 0;

    auto remainingCards = deck.getRemainingCards();

    int playerTotal = calculateHandValue(playerHand);

    // Simulate standing
    {
        int simulatedDealerTotal = simulateDealer(dealerHand, remainingCards);
        if (playerTotal > simulatedDealerTotal || simulatedDealerTotal == 0) {
            winsIfStand++;
        }
    }

    // Simulate hitting
    simulatePlayerRecursive(&playerHand, &dealerHand, &remainingCards, winsIfHit, bustsIfHit, totalSimulationsForHit);

    // Calculate probabilities
    probabilityWinIfHit = (totalSimulationsForHit > 0) ? static_cast<double>(winsIfHit) / totalSimulationsForHit : 0.0;
    probabilityWinIfStand = static_cast<double>(winsIfStand) / totalSimulationsForStand;
    probabilityBustIfHit = (totalSimulationsForHit > 0) ? static_cast<double>(bustsIfHit) / totalSimulationsForHit : 0.0;
}