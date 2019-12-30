/* Xinyu Liu, xinyuliu
 * CS 152, Spring 2019
 * Project 2
 */

#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "pos.h"

/* board_new: create a fully-empty board of the desired size, which must
 * be of acceptable dimensions */
board* board_new(unsigned int side, enum type type)
{
    if (side % 2 != 0) {
        fprintf(stderr, "board_new: the dimension is not even\n");
        exit(1);
    } else if (side == 2) {
        fprintf(stderr, "board_new: the dimension should be greater than "
                "two\n");
        exit(1);
    }
    board* res;
    unsigned int i,j;
    switch (type) {
        case (CELLS):
            res = (board*)malloc(sizeof(board));
            if (res == NULL) {
                fprintf(stderr, "board_new: unable to allocate memory\n");
                exit(1);
            }
            res->side = side;
            res->type = CELLS;
            enum square** cells = 
                (enum square**)malloc(side * sizeof(enum square*));
            if (cells == NULL) {
                fprintf(stderr, "board_new: unable to allocate memory\n");
                exit(1);
            }
            for (i = 0; i < side; i++) {
                cells[i] = (enum square*)malloc(side * sizeof(enum square));
                if (cells[i] == NULL) {
                    fprintf(stderr, "board_new: unable to allocate "
                            "memory\n");
                    exit(1);
                }
                for (j = 0; j < side; j++) {
                    cells[i][j] = EMPTY;
                }
            }
            res->u.cells = cells;
            return res;
        case (BITS):
            res = (board*)malloc(sizeof(board));
            if (res == NULL) {
                fprintf(stderr, "board_new: unable to allocate memory\n");
                exit(1);
            }
            res->side = side;
            res->type = BITS;
            unsigned int len = (side * side + 15) / 16;
            unsigned int* board = 
                (unsigned int*)malloc(len * sizeof(unsigned int));
            if (board == NULL) {
                fprintf(stderr, "board_new: unable to allocate memory\n");
                exit(1);
            }
            for (i = 0; i < len; i++) {
                board[i] = 0;
            }
            res->u.bits = board;
            return res;
        default:
            fprintf(stderr, "board_new: invalid tag\n");
            exit(1);
    }
}

/* board_free: fully free the board, including whichever internal
 * representation it is using */
void board_free(board* b)
{
    unsigned int i;
    switch (b->type) {
        case (CELLS):
            for (i = 0; i < b->side; i++) {
                free(b->u.cells[i]);
            }
            free(b->u.cells);
            free(b);
            break;
        case (BITS):
            free(b->u.bits);
            free(b);
            break;
        default:
            fprintf(stderr, "board_free: invalid tag\n");
            exit(1);
    }
}

/* number_show: print a number to the screen, using capital letters,
 * lower-case letters or question marks for numbers outside the range */
void number_show(unsigned int num)
{
    if (num <= 9) {
        printf("%u", num);
    } else if (num <= 35) {
        printf("%c", num + 55);
    } else if (num <= 61) {
        printf("%c", num + 61);
    } else {
        printf("?");
    }
}

/* square_show: print a square to the screen */
void square_show(board* b, pos p)
{
    switch (b->type) {
        case (CELLS):
            switch (b->u.cells[p.r][p.c]) {
                case (EMPTY):
                    printf(".");
                    break;
                case (BLACK):
                    printf("*");
                    break;
                case (WHITE):
                    printf("o");
                    break;
                default:
                    fprintf(stderr, "square_show: invalid square tag\n");
                    exit(1);
            }
            break;
        case (BITS):
            switch ((b->u.bits[(p.r * b->side + p.c) / 16] >> 
                    (2 * ((p.r * b->side + p.c) % 16))) & 3) {
                case 0:
                    printf(".");
                    break;
                case 1:
                    printf("*");
                    break;
                case 2:
                    printf("o");
                    break;
                default:
                    fprintf(stderr, "square_show: invalid square tag\n");
                    exit(1);
            }
            break;
        default:
            fprintf(stderr, "square_show: invalid tag\n");
            exit(1);
    }
}

/* row_show: print a single row to the screen, along with a number on the
 * left */
void row_show(board* b, unsigned int n_row)
{
    number_show(n_row);
    printf(" ");
    unsigned int i;
    for (i = 0; i < b->side; i++) {
        if (i == b->side/2) {
            printf(" ");
        }
        square_show(b,make_pos(n_row,i));
    }
    printf("\n");
}

/* board_show: print the board to the screen, along with row and column
 * headers */
void board_show(board* b)
{
    unsigned int i;
    printf("  ");
    for (i = 0; i < b->side; i++) {
        if (i == b->side/2) {
            printf(" ");
        }
        number_show(i);
    }
    printf("\n\n");
    for (i = 0; i < b->side; i++) {
        if (i == b->side/2) {
            printf("\n");
        }
        row_show(b,i);
    }
}

/* board_get: retrieve squares within the board */
square board_get(board* b, pos p)
{
    if (p.r >= b->side || p.c >= b->side) {
        fprintf(stderr, "board_get: the position is outside the board\n");
        exit(1);
    }
    switch (b->type) {
        case (CELLS):
            return b->u.cells[p.r][p.c];
        case (BITS):
            return ((b->u.bits[(p.r * b->side + p.c) / 16] >> 
                    (2 * ((p.r * b->side + p.c) % 16))) & 3);
        default:
            fprintf(stderr, "board_get: invalid tag\n");
            exit(1);
    }
}

/* board_set: modify squares within the board */
void board_set(board* b, pos p, square s)
{
    if (p.r >= b->side || p.c >= b->side) {
        fprintf(stderr, "board_set: the position is outside the board\n");
        exit(1);
    }
    switch (b->type) {
        case (CELLS):
            b->u.cells[p.r][p.c] = s;
            break;
        case (BITS):
            /* Clear the original bits in the desired position */
            b->u.bits[(p.r * b->side + p.c) / 16] &= ~(3 << 
                    (2 * ((p.r * b->side + p.c) % 16)));
            /* Set the correct square */
            b->u.bits[(p.r * b->side + p.c) / 16] |= (s <<
                    (2 * ((p.r * b->side + p.c) % 16)));
            break;
        default:
            fprintf(stderr, "board_set: invalid tag\n");
            exit(1);
    }
}
