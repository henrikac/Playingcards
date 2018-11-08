/*
 * Programmer: Henrik A. Christensen     Date Completed: in progress
 * Instructor: Kurt Nørmark              Class:          Imperative Programming
 *
 * Coming soon...
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define DECK_SIZE 55
#define NUM_SUITS 4
#define NUM_VALUES 13

typedef enum { CLUBS, DIAMONDS, HEARTS, SPADES, NONE } suit;
typedef enum { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, A, JOKER } rank;

typedef struct {
  suit kuloer;
  rank vaerdi;
} card;

void create_deck(card *deck);
void shuffle_deck(card *deck, size_t deck_size);
void swap_cards(card *c1, card *c2);
void display_deck(const char *title, const card *deck);
card *Calloc(size_t num_cards);

int main(void)
{
  card *deck = Calloc(DECK_SIZE);

  system(CLEAR);

  create_deck(deck);
  display_deck("\nNew Deck:\n", deck);

  shuffle_deck(deck, DECK_SIZE);
  display_deck("\n\nShuffled Deck:\n", deck);

  printf("\n\n");

  if (deck)
    free(deck);

  return EXIT_SUCCESS;
}

void create_deck(card *deck)
{
  int i, j;
  size_t num_cards = 0;
  card card;

  for (i = 0; i < NUM_SUITS; i++)
  {
    for (j = 0; j < NUM_VALUES; j++)
    {
      card.kuloer = (suit)i;
      card.vaerdi = (rank)j + 2;
      deck[num_cards++] = card;
    }

    if (i == 3)
    {
      card.kuloer = NONE;
      card.vaerdi = JOKER;

      for (j = num_cards; j < DECK_SIZE; j++)
      {
        deck[num_cards++] = card;
      }
    }
  }
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

void display_deck(const char *title, const card *deck)
{
  int i;

  printf(title);
  for (i = 0; i < DECK_SIZE; i++)
  {
    if (i % 13 == 0)
      printf("\n");
    printf(" %d |", deck[i].vaerdi);
  }
}

card *Calloc(size_t num_cards)
{
  card *c = (card*)calloc(num_cards, sizeof(card));
  if (c == NULL)
  {
    printf("\nCouldn't allocate memory");
    exit(EXIT_FAILURE);
  }
  return c;
}
