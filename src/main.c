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
  suit kuloer;
  rank vaerdi;
} card;

void create_deck(card *deck);
void add_suit(card *deck, size_t *counter, suit suit);
card create_card(suit suit, rank rank);
void shuffle_deck(card *deck, size_t deck_size);
void swap_cards(card *c1, card *c2);
void display_deck(const char *title, card *deck);
char *get_card(const card *card);
void *Calloc(size_t nitems, size_t size);

int main(void)
{
  card *deck = (card*)Calloc(DECK_SIZE, sizeof(card));

  system(CLEAR);

  create_deck(deck);
  display_deck("\nNew Deck:\n", deck);

  shuffle_deck(deck, DECK_SIZE);
  display_deck("\n\nShuffled Deck:\n", deck);

  printf("\n\n");

  free(deck);

  return EXIT_SUCCESS;
}

void create_deck(card *deck)
{
  int i;
  size_t num_cards = 0;

  for (i = 0; i < NUM_SUITS; i++)
    add_suit(deck, &num_cards, (suit)i);

  for (i = num_cards; i < DECK_SIZE; i++)
    deck[num_cards++] = create_card(NONE, JOKER);
}

void add_suit(card *deck, size_t *counter, suit suit)
{
  int i;

  for (i = 0; i < NUM_VALUES; i++)
    deck[(*counter)++] = create_card(suit, (rank)(i + 2));
}

card create_card(suit suit, rank rank)
{
  card c;

  c.kuloer = suit;
  c.vaerdi = rank;

  return c;
}

void shuffle_deck(card *deck, size_t deck_size)
{
  int i, new_index;

  srand(time(NULL));

  for (i = 0; i < deck_size; i++)
  {
    new_index = rand() % deck_size;
    swap_cards(&deck[i], &deck[new_index]);
  }
}

void swap_cards(card *c1, card *c2)
{
  card tmp = *c2;
  *c2 = *c1;
  *c1 = tmp;
}

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

    free(card_value);
  }
}

char *get_card(const card *card)
{
  char *c = (char*)Calloc(6, sizeof(char));

  switch (card->kuloer)
  {
    case CLUBS:
      sprintf(c, "C%d", card->vaerdi);
      break;
    case DIAMONDS:
      sprintf(c, "D%d", card->vaerdi);
      break;
    case HEARTS:
      sprintf(c, "H%d", card->vaerdi);
      break;
    case SPADES:
      sprintf(c, "S%d", card->vaerdi);
      break;
    case NONE:
      strcpy(c, "JOKER");
      break;
  }

  return c;
}

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
