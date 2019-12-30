#ifndef _LOGIC_H
#define _LOGIC_H

#include "board.h"

enum turn {
    BLACK_NEXT,
    WHITE_NEXT
};

typedef enum turn turn;

enum outcome {
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

typedef enum outcome outcome;

enum quadrant {
    NW, NE, SW, SE
};

typedef enum quadrant quadrant;

enum direction {
    CW, CCW
};

typedef enum direction direction;

struct game {
    board* b;
    turn next;
};

typedef struct game game;

/* This is a structure that stores whether black wins and whether white
 * wins. If both values are 1, then it represents a draw */
struct who_win {
    unsigned int black_win,white_win;
};

typedef struct who_win who_win;

/* new_game: create a new game with the specified size and using the
 * desired data representation */
game* new_game(unsigned int side, enum type type);

/* game_free: fully free the game, including whichever internal
 * representation it is using */
void game_free(game* g);

/* place_marble: place a marble belonging to the player whose turn it is
 * at the specified location */
int place_marble(game* g, pos p);

/* twist_quadrant: perform a twist and flip the player whose turn it is */
void twist_quadrant(game* g, quadrant q, direction d);

/* game_over: return true or false to indicate whether the game is over
 * according to the rules */
int game_over(game* g);

/* game_outcome: report the actual outcome */
outcome game_outcome(game* g);

#endif /* _LOGIC_H */
