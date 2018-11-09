/*
 * Programmer: Henrik A. Christensen     Date Completed: in progress
 * Instructor: Kurt Nørmark              Class:          Imperative Programming
 *
 * Coming soon...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define DECK_SIZE 55
#define NUM_SUITS 4
#define NUM_VALUES 13

typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES, NONE } suit; /**< NONE for jokers */
typedef enum { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, A, JOKER } rank;

typedef struct {
  suit suit; /* kuloer */
  rank rank; /* vaerdi */
} card;

void create_deck(card *deck);
void add_suit(card *deck, size_t *counter, suit suit);
card create_card(suit suit, rank rank);
void shuffle_deck(card *deck);
void swap_cards(card *c1, card *c2);
void display_deck(const char *title, card *deck);
char *get_card(const card *card);
void sort_deck(card *deck);
int cmp_cards(const void *c1, const void *c2);
void *Calloc(size_t nitems, size_t size);

int main(void)
{
  card *deck = (card*)Calloc(DECK_SIZE, sizeof(card));

  system(CLEAR);

  create_deck(deck);
  display_deck("\nNew Deck:\n", deck);

  shuffle_deck(deck);
  display_deck("\n\nShuffled Deck:\n", deck);

  sort_deck(deck);
  display_deck("\n\nSorted Deck:\n", deck);

  printf("\n\n");

  if (deck)
    free(deck);

  return EXIT_SUCCESS;
}

/**
 * creates a deck of playing cards
 * @param[in] deck Deck to add cards to
*/
void create_deck(card *deck)
{
  int i;
  size_t num_cards = 0;

  for (i = 0; i < NUM_SUITS; i++)
    add_suit(deck, &num_cards, (suit)i);

  if (num_cards < DECK_SIZE)
    for (i = num_cards; i < DECK_SIZE; i++)
      deck[num_cards++] = create_card(NONE, JOKER);
}

/**
 * adds a suit with cards ranking from 2 to A (ace) to the deck
 * @param[in] deck The deck to add the suit to
 * @param[in, out] counter Variable that keeps track of the number of cards current in the deck
 * @param[in] suit The suit to add to the cards
*/
void add_suit(card *deck, size_t *counter, suit suit)
{
  int i;

  for (i = 0; i < NUM_VALUES; i++)
    deck[(*counter)++] = create_card(suit, (rank)(i + 2));
}

/**
 * create a card
 * @param[in] suit The suit of the card
 * @param[in] rank The rank of the card
 * @return a card with suit and rank
*/
card create_card(suit suit, rank rank)
{
  card c;

  c.suit = suit;
  c.rank = rank;

  return c;
}

/**
 * shuffles a deck of playing cards
 * @param[in] deck Deck to shuffle
*/
void shuffle_deck(card *deck)
{
  int i, new_index;

  srand(time(NULL));

  for (i = 0; i < DECK_SIZE; i++)
  {
    new_index = rand() % DECK_SIZE;
    swap_cards(&deck[i], &deck[new_index]);
  }
}

/**
 * swaps two cards
 * @param[in] c1 Card number 1
 * @param[in] c2 Card number 2
*/
void swap_cards(card *c1, card *c2)
{
  card tmp = *c2;
  *c2 = *c1;
  *c1 = tmp;
}

/**
 * Displays a deck to the user
 * @param[in] title Text to describe state of the deck (new deck, shuffled deck etc..)
 * @param[in] deck Deck to display
*/
void display_deck(const char *title, card *deck)
{
  int i;
  char *card_value;

  printf(title);
  for (i = 0; i < DECK_SIZE; i++)
  {
    card_value = get_card(&deck[i]);

    if (i % 13 == 0)
      printf("\n");
    printf(" %s |", card_value);

    if (card_value)
      free(card_value);
  }
}

/**
 * Get suit and rank of a card
 * @param[in] card Card to get suit and rank of
 * @return a single card represented by a letter and a number
*/
char *get_card(const card *card)
{
  char *c = (char*)Calloc(6, sizeof(char));

  switch (card->suit)
  {
    case CLUBS:
      sprintf(c, "C%d", card->rank);
      break;
    case DIAMONDS:
      sprintf(c, "D%d", card->rank);
      break;
    case HEARTS:
      sprintf(c, "H%d", card->rank);
      break;
    case SPADES:
      sprintf(c, "S%d", card->rank);
      break;
    case NONE:
      strcpy(c, "JOKER");
      break;
  }

  return c;
}

/**
 * sort cards in a deck
 * @param[in] deck Deck to sort
*/
void sort_deck(card *deck) /* sorter_kort */
{
  qsort(deck, DECK_SIZE, sizeof(card), cmp_cards);
}

/**
 * compare two cards
 * @param[in] c1 Card number 1
 * @param[in] c2 Card number 2
 * @return an integer that tells if c1 > c2, c1 < c2 or c1 == c2
*/
int cmp_cards(const void *c1, const void *c2)
{
  card *card1 = (card*)c1,
       *card2 = (card*)c2;

  if (card1->suit < card2->suit)
    return -1;
  else if (card1->suit > card2->suit)
    return 1;
  else
  {
    if (card1->rank < card2->rank)
      return -1;
    else if (card1->rank > card2->rank)
      return 1;
    else
      return 0;
  }
}

/**
 * allocate nitems * size memory
 * @param[in] nitems Number of items to allocate memory for
 * @param[in] size Size of each item
 * @return void *
*/
void *Calloc(size_t nitems, size_t size)
{
  void *c = calloc(nitems, size);
  if (c == NULL)
  {
    printf("\nCouldn't allocate memory");
    exit(EXIT_FAILURE);
  }
  return c;
}
