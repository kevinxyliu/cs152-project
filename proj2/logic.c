/* Xinyu Liu, xinyuliu
 * CS 152, Spring 2019
 * Project 2
 */

#include <stdlib.h>
#include <stdio.h>
#include "pos.h"
#include "board.h"
#include "logic.h"

/* new_game: create a new game with the specified size and using the 
 * desired data representation */
game* new_game(unsigned int side, enum type type)
{
    game* res = (game*)malloc(sizeof(game));
    if (res == NULL) {
        fprintf(stderr, "new_game: unable to allocate memory\n");
        exit(1);
    }
    res->b = board_new(side,type);
    res->next = WHITE_NEXT;
    return res;
}

/* game_free: fully free the game, including whichever internal
 * representation it is using */
void game_free(game* g)
{
    board_free(g->b);
    free(g);
}

/* place_marble: place a marble belonging to the player whose turn it is
 * at the specified location */
int place_marble(game* g, pos p)
{
    /* No need to check whether the position is outside the board, because
     * the implementation of board_set and board_get already does this */
    if (board_get(g->b,p) == EMPTY) {
        switch (g->next) {
            case (BLACK_NEXT):
                board_set(g->b,p,BLACK);
                break;
            case (WHITE_NEXT):
                board_set(g->b,p,WHITE);
                break;
            default:
                fprintf(stderr, "place_marble: invalid tag\n");
                exit(1);
        }
        return 1;
    }
    return 0;
}

/* rotate: rotate a quadrant either clockwise or counterclockwise, and the
 * given position represents the upper left corner of the quadrant we want
 * to rotate */
void rotate(board* b, direction d, pos p)
{
    /* Make a copy of the original cells */
    board* cpy = board_new(b->side,b->type);
    unsigned int i,j;
    for (i = 0; i < b->side; i++) {
        for (j = 0; j < b->side; j++) {
            board_set(cpy,make_pos(i,j),board_get(b,make_pos(i,j)));
        }
    }
    /* Rotate a quadrant clockwise or counterclockwise */
    for (i = 0; i < b->side/2; i++) {
        for (j = 0; j < b->side/2; j++) {
            switch (d) {
                case (CW):
                    board_set(b,make_pos(p.r+i,p.c+j),board_get(cpy,
                                make_pos(p.r+b->side/2-j-1,p.c+i)));
                    break;
                case (CCW):
                    board_set(b,make_pos(p.r+i,p.c+j),board_get(cpy,
                                make_pos(p.r+j,p.c+b->side/2-i-1)));
                    break;
                default:
                    fprintf(stderr, "rotate: invalid tag\n");
                    exit(1);
            }
        }
    }
    /* Free the copy of matrix */
    board_free(cpy);
}

/* twist_quadrant: perform a twist and flip the player whose turn it is */
void twist_quadrant(game* g, quadrant q, direction d)
{
    if (g->next == BLACK_NEXT) {
        g->next = WHITE_NEXT;
    } else {
        g->next = BLACK_NEXT;
    }
    pos pos_nw = {0,0};
    pos pos_ne = {0,g->b->side/2};
    pos pos_sw = {g->b->side/2,0};
    pos pos_se = {g->b->side/2,g->b->side/2};
    switch (q) {
        case (NW):
            rotate(g->b, d, pos_nw);
            break;
        case (NE):
            rotate(g->b, d, pos_ne);
            break;
        case (SW):
            rotate(g->b, d, pos_sw);
            break;
        case (SE):
            rotate(g->b, d, pos_se);
            break;
        default:
            fprintf(stderr, "twist_quadrant: invalid tag\n");
            exit(1);
    }
}

/* make_dir: a convenience function to create a dir value */
dir make_dir(unsigned int r, unsigned int c)
{
    dir dir_new = {r,c};
    return dir_new;
}

/* consecutive: check if there are (side-1) consecutive black/white squares
 * from the starting position along the given moving direction. Return 1 
 * if there are consecutive black squares, return 2 if there are consecutive
 * white squares, and return 0 otherwise. */
int consecutive(board* b, pos init, dir d)
{
    unsigned int i;
    int color = board_get(b,init);
    if (color == 0) {
        return 0;
    }
    for (i = 1; i < b->side-1; i++) {
        if (board_get(b,make_pos(init.r+i*d.r, init.c+i*d.c)) != color) {
            return 0;
        }
    }
    return color;
}

/* check_row_col: check if there are (side-1) consecutive black/white 
 * squares in a row or a column. Return a structure that indicates whether
 * black wins, and whether white wins */
who_win check_row_col(board* b)
{
    unsigned int i,res1,res2,res3,res4;
    who_win outcome = {0,0};
    for (i = 0; i < b->side; i++) {
        /* Check each row at a time */
        res1 = consecutive(b,make_pos(i,0),make_dir(0,1));
        res2 = consecutive(b,make_pos(i,1),make_dir(0,1));
        /* Check each column at a time */
        res3 = consecutive(b,make_pos(0,i),make_dir(1,0));
        res4 = consecutive(b,make_pos(1,i),make_dir(1,0));
        if (res1 == 1 || res2 == 1 || res3 == 1 || res4 == 1) {
            outcome.black_win = 1;
        } 
        if (res1 == 2 || res2 == 2 || res3 == 2 || res4 == 2) {
            outcome.white_win = 1;
        }
    }
    return outcome;
}

/* check_dia: check if there are (side-1) consecutive black/white squares
 * in the two diagonals. Return a structure that indicates whether black
 * wins, and whether white wins */
who_win check_dia(board* b)
{
    who_win outcome = {0,0};
    unsigned int res0 = consecutive(b,make_pos(0,1),make_dir(1,1));
    unsigned int res1 = consecutive(b,make_pos(1,0),make_dir(1,1));
    unsigned int res2 = consecutive(b,make_pos(0,0),make_dir(1,1));
    unsigned int res3 = consecutive(b,make_pos(1,1),make_dir(1,1));
    unsigned int res4 = consecutive(b,make_pos(0,b->side-2),make_dir(1,-1));
    unsigned int res5 = consecutive(b,make_pos(1,b->side-1),make_dir(1,-1));
    unsigned int res6 = consecutive(b,make_pos(0,b->side-1),make_dir(1,-1));
    unsigned int res7 = consecutive(b,make_pos(1,b->side-2),make_dir(1,-1));
    unsigned int res[] = {res0,res1,res2,res3,res4,res5,res6,res7};
    unsigned int i;
    for (i = 0; i < 8; i++) {
        if (res[i] == 1) {
            outcome.black_win = 1;
        } 
        if (res[i] == 2) {
            outcome.white_win = 1;
        }
    }
    return outcome;
}

/* game_over: return true or false to indicate whether the game is over
 * according to the rules */
int game_over(game* g)
{
    who_win res_row_col = check_row_col(g->b);
    who_win res_dia = check_dia(g->b);
    int board_full = 1;
    unsigned int i,j;
    for (i = 0; i < g->b->side; i++) {
        for (j = 0; j < g->b->side; j++) {
            if (board_get(g->b,make_pos(i,j)) == EMPTY) {
                board_full = 0;
            }
        }
    }
    return res_row_col.black_win || res_row_col.white_win ||
        res_dia.black_win || res_dia.white_win || board_full;
}

/* game_outcome: report the actual outcome */
outcome game_outcome(game* g)
{
    who_win res_row_col = check_row_col(g->b);
    who_win res_dia = check_dia(g->b);
    int black_win = res_row_col.black_win || res_dia.black_win;
    int white_win = res_row_col.white_win || res_dia.white_win;
    if (black_win && white_win) {
        return DRAW;
    } else if (black_win) {
        return BLACK_WIN;
    } else if (white_win) {
        return WHITE_WIN;
    }
    return DRAW;
}
