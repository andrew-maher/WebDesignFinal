#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum Rank {
  TWO = 2,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE
};

struct Card {
  Suit suit;
  Rank rank;
};

class Deck {
public:
  Deck() {
    for (int suit = CLUBS; suit <= SPADES; ++suit) {
      for (int rank = TWO; rank <= ACE; ++rank) {
        cards.push_back({static_cast<Suit>(suit), static_cast<Rank>(rank)});
      }
    }
    shuffle();
  }

  void shuffle() {
    srand(time(0));
    std::random_shuffle(cards.begin(), cards.end());
  }

  Card draw() {
    Card card = cards.back();
    cards.pop_back();
    return card;
  }

private:
  std::vector<Card> cards;
};

int cardValue(Card card) {
  if (card.rank >= JACK && card.rank <= KING) {
    return 10;
  } else if (card.rank == ACE) {
    return 11;
  } else {
    return card.rank;
  }
}

bool isAce(Card card) { return card.rank == ACE; }

int handValue(vector<Card> hand) {
  int value = 0;
  int aceCount = 0;
  for (Card card : hand) {
    value += cardValue(card);
    if (isAce(card))
      aceCount++;
  }
  while (value > 21 && aceCount > 0) {
    value -= 10;
    aceCount--;
  }
  return value;
}

void printCard(Card card) {
  const char *rankNames[] = {"2", "3",  "4", "5", "6", "7", "8",
                             "9", "10", "J", "Q", "K", "A"};
  const char *suitNames[] = {"C", "D", "H", "S"};
  cout << rankNames[card.rank - 2] << suitNames[card.suit] << " ";
}

void printHand(vector<Card> hand) {
  for (Card card : hand) {
    printCard(card);
  }
  cout << " (" << handValue(hand) << ")" << endl;
}

void dealerPlay(vector<Card> &dealerHand, Deck &deck) {
  while (handValue(dealerHand) < 17) {
    dealerHand.push_back(deck.draw());
  }
}

void playerPlay(vector<Card> &playerHand, Deck &deck) {
  char choice;
  do {
    cout << "Your hand: ";
    printHand(playerHand);
    cout << "Do you want to hit or stand? (h/s): ";
    cin >> choice;
    if (choice == 'h') {
      playerHand.push_back(deck.draw());
    }
  } while (choice != 's' && handValue(playerHand) <= 21);
}

void displayInstructions() {
  cout << "\n\n\n\t\t     ************************************\n";
  cout << "\t\t     *           Blackjack Rules           *\n";
  cout << "\t\t     ************************************\n\n";
  cout << "The goal of Blackjack is to have a hand value closer to 21 than the "
          "dealer, without going over 21."
       << endl;
  cout << "Card Values:" << endl;
  cout << "  - Number Cards (2-10): Face Value" << endl;
  cout << "  - Jack, Queen, King: 10" << endl;
  cout << "  - Ace: 1 or 11 (player chooses)" << endl;
  cout << "\nGameplay:" << endl;
  cout << "1. You and the dealer each receive two cards." << endl;
  cout << "2. The dealer's first card is face up, the second is face down."
       << endl;
  cout << "3. You can choose to 'hit' (take another card) or 'stand' (keep "
          "your hand)."
       << endl;
  cout << "4. If your hand value goes over 21, you 'bust' and lose." << endl;
  cout << "5. After you stand, the dealer reveals their hidden card and hits "
          "until their hand value is 17 or higher."
       << endl;
  cout << "6. If the dealer busts, you win." << endl;
  cout << "7. If you and the dealer both have a hand value less than 21, the "
          "player with the higher value wins."
       << endl;
  cout << "8. If you and the dealer have the same hand value, it's a tie."
       << endl;
  cout << "\nPress any key to return to the main menu." << endl;
  cin.ignore(); // Clear the buffer
  cin.get();    // Wait for a key press
}

int main() {
  // Blackjack Title
  cout << "\n\n\n\t\t     ************************************\n";
  cout << "\t\t     *      Welcome to Blackjack!       *\n";
  cout << "\t\t     ************************************\n\n";

  char choice;
  do {
    cout << "1. Play Blackjack" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case '1': {
      double balance = 0;
      cout << "Enter your buy-in amount: $";
      cin >> balance;
      while (balance <= 0) {
        cout << "Please enter a positive amount: $";
        cin >> balance;
      }

      char playAgain;
      do {
        if (balance <= 0) {
          break;
        }
        cout << "\033[2J\033[1;1H"; // Resets Console
        double bet;
        cout << "You have $" << balance << ". Enter your bet: $";
        cin >> bet;
        while (bet <= 0 || bet > balance) {
          cout << "Invalid bet. Please enter a positive amount less than or "
                  "equal "
                  "to your balance: $";
          cin >> bet;
        }

        Deck deck;
        vector<Card> playerHand;
        vector<Card> dealerHand;

        playerHand.push_back(deck.draw());
        playerHand.push_back(deck.draw());
        dealerHand.push_back(deck.draw());
        dealerHand.push_back(deck.draw());

        cout << "Dealer's hand: ";
        printCard(dealerHand[0]);
        cout << " ?" << endl;

        playerPlay(playerHand, deck);
        if (handValue(playerHand) > 21) {
          cout << "You busted! Dealer wins." << endl;
          balance -= bet;
        } else {
          dealerPlay(dealerHand, deck);
          cout << "Dealer's hand: ";
          printHand(dealerHand);
          if (handValue(dealerHand) > 21 ||
              handValue(playerHand) > handValue(dealerHand)) {
            cout << "You win!" << endl;
            balance += bet;
          } else if (handValue(playerHand) == handValue(dealerHand)) {
            cout << "It's a tie!" << endl;
          } else {
            cout << "Dealer wins." << endl;
            balance -= bet;
          }
        }

        cout << "Your balance is now $" << balance << endl;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
      } while (playAgain == 'y');

      cout << "Thank you for playing! You leave with $" << balance << "."
           << endl;
      break;
    }
    case '2':
      displayInstructions();
      break;
    case '3':
      cout << "Exiting the game..." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
  } while (choice != '3');

  return 0;
}
