/* Xinyu Liu, xinyuliu
 * CS 152, Spring 2019
 * Project 1
 */

// Some comments
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
    board* res = (board*)malloc(sizeof(board));
    if (res == NULL) {
        fprintf(stderr, "board_new: unable to allocate memory\n");
        exit(1);
    }
    res->side = side;
    switch (type) {
        case (CELLS):
            res->type = CELLS;
            enum square** cells = (enum square**)
                malloc(side * sizeof(enum square*));
            if (cells == NULL) {
                fprintf(stderr, "board_new: unable to allocate memory\n");
                exit(1);
            }
            unsigned int i,j;
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
            fprintf(stderr, "board_new: BITS representation not yet "
                    "implemented\n");
            exit(1);
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
            fprintf(stderr, "board_free: BITS representation not yet "
                    "implemented\n");
            exit(1);
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
void square_show(enum square cell)
{
    switch (cell) {
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
}

/* row_show: print a single row to the screen, along with a number on the
 * left */
void row_show(enum square* row, unsigned int n_row, unsigned int side)
{
    number_show(n_row);
    printf(" ");
    unsigned int i;
    for (i = 0; i < side/2; i++) {
        square_show(row[i]);
    }
    printf(" ");
    for (i = side/2; i < side; i++) {
        square_show(row[i]);
    }
    printf("\n");
}

/* board_show: print the board to the screen, along with row and column
 * headers */
void board_show(board* b)
{
    unsigned int i;
    switch (b->type) {
        case (CELLS):
            printf("  ");
            for (i = 0; i < b->side/2; i++) {
                number_show(i);
            }
            printf(" ");
            for (i = b->side/2; i < b->side; i++) {
                number_show(i);
            }
            printf("\n\n");
            for (i = 0; i < b->side/2; i++) {
                row_show(b->u.cells[i], i, b->side);
            }
            printf("\n");
            for (i = b->side/2; i < b->side; i++) {
                row_show(b->u.cells[i], i, b->side);
            }
            break;
        case (BITS):
            fprintf(stderr, "board_show: BITS representation not yet "
                    "implemented\n");
            exit(1);
        default:
            fprintf(stderr, "board_show: invalid tag\n");
            exit(1);
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
            fprintf(stderr, "board_get: BITS representation not yet "
                    "implemented\n");
            exit(1);
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
            fprintf(stderr, "board_set: BITS representation not yet "
                    "implemented\n");
            exit(1);
        default:
            fprintf(stderr, "board_set: invalid tag\n");
            exit(1);
    }
}
