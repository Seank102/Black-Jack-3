#include "Deck.h"
#include "Card.h"
#include <iostream>
#include <vector>

using namespace std;

// Function prototypes
int calculateHandValue(const vector<Card>& hand);
void splitHands(Deck& deck, vector<Card>& hand);

// Test function for Ace handling
void testAces() {
    cout << "=== Testing Ace Handling ===\n";

    vector<Card> hand1 = {Card(ACE, HEARTS), Card(EIGHT, DIAMONDS)};
    cout << "Hand: Ace of Hearts, 8 of Diamonds\n";
    cout << "Expected Total: 19\n";
    cout << "Calculated Total: " << calculateHandValue(hand1) << "\n\n";

    vector<Card> hand2 = {Card(ACE, HEARTS), Card(EIGHT, DIAMONDS), Card(FIVE, CLUBS)};
    cout << "Hand: Ace of Hearts, 8 of Diamonds, 5 of Clubs\n";
    cout << "Expected Total: 14\n";
    cout << "Calculated Total: " << calculateHandValue(hand2) << "\n\n";

    vector<Card> hand3 = {Card(ACE, HEARTS), Card(ACE, CLUBS), Card(EIGHT, DIAMONDS)};
    cout << "Hand: Ace of Hearts, Ace of Clubs, 8 of Diamonds\n";
    cout << "Expected Total: 20\n";
    cout << "Calculated Total: " << calculateHandValue(hand3) << "\n\n";

    vector<Card> hand4 = {Card(ACE, HEARTS), Card(ACE, CLUBS), Card(ACE, SPADES), Card(NINE, DIAMONDS)};
    cout << "Hand: Ace of Hearts, Ace of Clubs, Ace of Spades, 9 of Diamonds\n";
    cout << "Expected Total: 12\n";
    cout << "Calculated Total: " << calculateHandValue(hand4) << "\n\n";
}

// Test function for Splitting
void testSplitting() {
    cout << "=== Testing Splitting ===\n";

    Deck deck;
    deck.shuffleDeck();

    vector<Card> playerHand = {Card(EIGHT, SPADES), Card(EIGHT, HEARTS)};
    cout << "Original Hand: 8 of Spades, 8 of Hearts\n";
    cout << "Splitting hand...\n";

    splitHands(deck, playerHand); // This function should handle playing both hands
    cout << "Split completed. Verify gameplay behavior manually.\n\n";

    vector<Card> acesHand = {Card(ACE, SPADES), Card(ACE, CLUBS)};
    cout << "Original Hand: Ace of Spades, Ace of Clubs\n";
    cout << "Splitting hand...\n";

    splitHands(deck, acesHand); // Test splitting with Aces
    cout << "Split completed. Verify gameplay behavior manually.\n\n";
}
//Main
int main() {
    // Test Ace Handling
    testAces();

    // Test Splitting Logic
    testSplitting();

    return 0;
}