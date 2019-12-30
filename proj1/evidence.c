/* Xinyu Liu, xinyuliu
 * CS 152, Spring 2019
 * Project 1
 */

#include <stdlib.h>
#include <stdio.h>
#include "pos.h"
#include "board.h"
#include "logic.h"

/* evidence_make_pos: test make_pos */
void evidence_make_pos()
{
    printf("*** testing make_pos\n");
    pos test_pos_1 = make_pos(0,0);
    pos test_pos_2 = make_pos(0,1);
    pos test_pos_3 = make_pos(1,0);
    pos test_pos_4 = make_pos(1,1);
    printf("- expecting 0 0: %u %u\n", test_pos_1.r, test_pos_1.c);
    printf("- expecting 0 1: %u %u\n", test_pos_2.r, test_pos_2.c);
    printf("- expecting 1 0: %u %u\n", test_pos_3.r, test_pos_3.c);
    printf("- expecting 1 1: %u %u\n", test_pos_4.r, test_pos_4.c);
}

/* evidence_board_new: test board_new */
void evidence_board_new()
{
    printf("*** testing board_new\n");
    board* test_board_1 = board_new(4,CELLS);
    board* test_board_2 = board_new(6,CELLS);
    board* test_board_3 = board_new(8,CELLS);
    board* test_board_4 = board_new(10,CELLS);
    printf("- expecting a 4*4 empty board:\n");
    board_show(test_board_1);
    printf("- expecting a 6*6 empty board:\n");
    board_show(test_board_2);
    printf("- expecting an 8*8 empty board:\n");
    board_show(test_board_3);
    printf("- expecting a 10*10 empty board:\n");
    board_show(test_board_4);
    board_free(test_board_1);
    board_free(test_board_2);
    board_free(test_board_3);
    board_free(test_board_4);
}

/* evidence_board_show: test board_show */
void evidence_board_show()
{
    printf("*** testing board_show\n");
    board* test_board_1 = board_new(10,CELLS);
    board* test_board_2 = board_new(20,CELLS);
    board* test_board_3 = board_new(40,CELLS);
    board* test_board_4 = board_new(70,CELLS);
    printf("- expecting a 10*10 empty board:\n");
    board_show(test_board_1);
    printf("- expecting a 20*20 empty board:\n");
    board_show(test_board_2);
    printf("- expecting a 40*40 empty board:\n");
    board_show(test_board_3);
    printf("- expecting a 70*70 empty board:\n");
    board_show(test_board_4);
    board_free(test_board_1);
    board_free(test_board_2);
    board_free(test_board_3);
    board_free(test_board_4);
}

/* evidence_board_get: test board_get */
void evidence_board_get()
{
    printf("*** testing board_get\n");
    board* test_board_1 = board_new(4,CELLS);
    board* test_board_2 = board_new(6,CELLS);
    pos pos_00 = make_pos(0,0);
    pos pos_01 = make_pos(0,1);
    pos pos_10 = make_pos(1,0);
    pos pos_11 = make_pos(1,1);
    pos pos_12 = make_pos(1,2);
    pos pos_21 = make_pos(2,1);
    pos pos_22 = make_pos(2,2);
    board_set(test_board_1, pos_00, BLACK);
    board_set(test_board_1, pos_01, WHITE);
    board_set(test_board_1, pos_10, BLACK);
    board_set(test_board_1, pos_11, WHITE);
    board_set(test_board_1, pos_12, BLACK);
    board_set(test_board_1, pos_21, WHITE);
    board_set(test_board_1, pos_22, BLACK);
    board_set(test_board_2, pos_00, WHITE);
    board_set(test_board_2, pos_01, BLACK);
    board_set(test_board_2, pos_10, WHITE);
    board_set(test_board_2, pos_11, BLACK);
    board_set(test_board_2, pos_12, WHITE);
    board_set(test_board_2, pos_21, BLACK);
    board_set(test_board_2, pos_22, WHITE);
    printf("- expecting 1: %d\n", board_get(test_board_1, pos_00) == BLACK);
    printf("- expecting 0: %d\n", board_get(test_board_1, pos_01) == BLACK);
    printf("- expecting 1: %d\n", board_get(test_board_1, pos_10) == BLACK);
    printf("- expecting 0: %d\n", board_get(test_board_1, pos_11) == BLACK);
    printf("- expecting 1: %d\n", board_get(test_board_1, pos_12) == BLACK);
    printf("- expecting 0: %d\n", board_get(test_board_1, pos_21) == BLACK);
    printf("- expecting 1: %d\n", board_get(test_board_1, pos_22) == BLACK);
    printf("- expecting 0: %d\n", board_get(test_board_2, pos_00) == BLACK);
    printf("- expecting 1: %d\n", board_get(test_board_2, pos_01) == BLACK);
    printf("- expecting 0: %d\n", board_get(test_board_2, pos_10) == EMPTY);
    printf("- expecting 1: %d\n", board_get(test_board_2, pos_11) == BLACK);
    printf("- expecting 0: %d\n", board_get(test_board_2, pos_12) == EMPTY);
    printf("- expecting 1: %d\n", board_get(test_board_2, pos_21) == BLACK);
    printf("- expecting 0: %d\n", board_get(test_board_2, pos_22) == EMPTY);
    board_free(test_board_1);
    board_free(test_board_2);
}

/* evidence_board_set: test board_set */
void evidence_board_set()
{
    printf("*** testing board_set\n");
    board* test_board_1 = board_new(4,CELLS);
    board* test_board_2 = board_new(6,CELLS);
    pos pos_00 = make_pos(0,0);
    pos pos_01 = make_pos(0,1);
    pos pos_10 = make_pos(1,0);
    pos pos_11 = make_pos(1,1);
    pos pos_12 = make_pos(1,2);
    pos pos_21 = make_pos(2,1);
    pos pos_22 = make_pos(2,2);
    board_set(test_board_1, pos_00, BLACK);
    board_set(test_board_1, pos_01, WHITE);
    board_set(test_board_1, pos_10, BLACK);
    printf("- expecting *o..\\n*...\\n....\\n....:\n");
    board_show(test_board_1);
    board_set(test_board_1, pos_11, WHITE);
    board_set(test_board_1, pos_12, BLACK);
    board_set(test_board_1, pos_21, WHITE);
    board_set(test_board_1, pos_22, BLACK);
    printf("- expecting *o..\\n*o*.\\n.o*.\\n....:\n");
    board_show(test_board_1);
    board_set(test_board_2, pos_00, WHITE);
    board_set(test_board_2, pos_01, BLACK);
    board_set(test_board_2, pos_10, WHITE);
    printf("- expecting o*....\\no.....\\n......\\n......\\n......\\n"
            "......:\n");
    board_show(test_board_2);
    board_set(test_board_2, pos_11, BLACK);
    board_set(test_board_2, pos_12, WHITE);
    board_set(test_board_2, pos_21, BLACK);
    board_set(test_board_2, pos_22, WHITE);
    printf("- expecting o*....\\no*o...\\n.*o...\\n......\\n......\\n"
            "......:\n");
    board_show(test_board_2);
    board_free(test_board_1);
    board_free(test_board_2);
}

/* evidence_new_game: test new_game */
void evidence_new_game()
{
    printf("*** testing new_game\n");
    game* test_game_1 = new_game(4, CELLS);
    game* test_game_2 = new_game(6, CELLS);
    game* test_game_3 = new_game(8, CELLS);
    printf("- expecting 1: %d\n", test_game_1->next == WHITE_NEXT);
    printf("- expecting 0: %d\n", test_game_2->next == BLACK_NEXT);
    printf("- expecting 1: %d\n", test_game_3->next == WHITE_NEXT);
    printf("- expecting a 4*4 empty board:\n");
    board_show(test_game_1->b);
    printf("- expecting a 6*6 empty board:\n");
    board_show(test_game_2->b);
    printf("- expecting an 8*8 empty board:\n");
    board_show(test_game_3->b);
    game_free(test_game_1);
    game_free(test_game_2);
    game_free(test_game_3);
}

/* evidence_place_marble: test place_marble */
void evidence_place_marble()
{
    printf("*** testing place_marble\n");
    game* test_game_1 = new_game(4, CELLS);
    game* test_game_2 = new_game(6, CELLS);
    pos test_pos_1 = {0,0};
    pos test_pos_2 = {1,1};
    pos test_pos_3 = {2,2};
    pos test_pos_4 = {3,3};
    printf("- expecting 1: %d\n", place_marble(test_game_1, test_pos_1));
    printf("- expecting 0: %d\n", place_marble(test_game_1, test_pos_1));
    printf("- expecting o...\\n....\\n....\\n....:\n");
    board_show(test_game_1->b);
    printf("- expecting 1: %d\n", place_marble(test_game_1, test_pos_2));
    printf("- expecting 0: %d\n", place_marble(test_game_1, test_pos_2));
    printf("- expecting o...\\n.o..\\n....\\n....:\n");
    board_show(test_game_1->b);
    printf("- expecting 1: %d\n", place_marble(test_game_1, test_pos_3));
    printf("- expecting 0: %d\n", place_marble(test_game_1, test_pos_3));
    printf("- expecting o...\\n.o..\\n..o.\\n....:\n");
    board_show(test_game_1->b);
    printf("- expecting 1: %d\n", place_marble(test_game_1, test_pos_4));
    printf("- expecting 0: %d\n", place_marble(test_game_1, test_pos_4));
    printf("- expecting o...\\n.o..\\n..o.\\n...o:\n");
    board_show(test_game_1->b);
    printf("- expecting 1: %d\n", place_marble(test_game_2, test_pos_1));
    printf("- expecting 0: %d\n", place_marble(test_game_2, test_pos_1));
    printf("- expecting o.....\\n......\\n......\\n......\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    printf("- expecting 1: %d\n", place_marble(test_game_2, test_pos_2));
    printf("- expecting 0: %d\n", place_marble(test_game_2, test_pos_2));
    printf("- expecting o.....\\n.o....\\n......\\n......\\n......"
            "\\n......:\n"); 
    board_show(test_game_2->b);
    printf("- expecting 1: %d\n", place_marble(test_game_2, test_pos_3));
    printf("- expecting 0: %d\n", place_marble(test_game_2, test_pos_3));
    printf("- expecting o.....\\n.o....\\n..o...\\n......\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    printf("- expecting 1: %d\n", place_marble(test_game_2, test_pos_4));
    printf("- expecting 0: %d\n", place_marble(test_game_2, test_pos_4));
    printf("- expecting o.....\\n.o....\\n..o...\\n...o..\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    game_free(test_game_1);
    game_free(test_game_2);
}

/* evidence_twist_quadrant: test twist_quadrant */
void evidence_twist_quadrant()
{
    printf("*** testing twist_quadrant\n");
    game* test_game_1 = new_game(4, CELLS);
    game* test_game_2 = new_game(6, CELLS);
    pos test_pos_1 = {0,1};
    pos test_pos_2 = {0,2};
    pos test_pos_3 = {0,3};
    pos test_pos_4 = {1,3};
    pos test_pos_5 = {3,3};
    pos test_pos_6 = {5,0};
    place_marble(test_game_1, test_pos_1);
    twist_quadrant(test_game_1, NW, CW);
    printf("- expecting 1: %d\n", test_game_1->next == BLACK_NEXT);
    printf("- expecting ....\\n.o..\\n....\\n....:\n");
    board_show(test_game_1->b);
    place_marble(test_game_1, test_pos_2);
    twist_quadrant(test_game_1, NW, CCW);
    printf("- expecting 0: %d\n", test_game_1->next == BLACK_NEXT);
    printf("- expecting .o*.\\n....\\n....\\n....:\n");
    board_show(test_game_1->b);
    place_marble(test_game_1, test_pos_3);
    twist_quadrant(test_game_1, NE, CW);
    printf("- expecting 1: %d\n", test_game_1->next == BLACK_NEXT);
    printf("- expecting .o.*\\n...o\\n....\\n....:\n");
    board_show(test_game_1->b);
    place_marble(test_game_1, test_pos_5);
    twist_quadrant(test_game_1, SE, CCW);
    printf("- expecting 0: %d\n", test_game_1->next == BLACK_NEXT);
    printf("- expecting .o.*\\n...o\\n...*\\n....:\n");
    board_show(test_game_1->b);
    place_marble(test_game_2, test_pos_1);
    twist_quadrant(test_game_2, NW, CCW);
    printf("- expecting 1: %d\n", test_game_2->next == BLACK_NEXT);
    printf("- expecting ......\\no.....\\n......\\n......\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    place_marble(test_game_2, test_pos_2);
    twist_quadrant(test_game_2, NW, CCW);
    printf("- expecting 0: %d\n", test_game_2->next == BLACK_NEXT);
    printf("- expecting *.....\\n......\\n.o....\\n......\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    place_marble(test_game_2, test_pos_3);
    twist_quadrant(test_game_2, NE, CCW);
    printf("- expecting 1: %d\n", test_game_2->next == BLACK_NEXT);
    printf("- expecting *.....\\n......\\n.o.o..\\n......\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    place_marble(test_game_2, test_pos_4);
    twist_quadrant(test_game_2, NE, CW);
    printf("- expecting 0: %d\n", test_game_2->next == BLACK_NEXT);
    printf("- expecting *..o*.\\n......\\n.o....\\n......\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    place_marble(test_game_2, test_pos_5);
    twist_quadrant(test_game_2, SE, CW);
    printf("- expecting 1: %d\n", test_game_2->next == BLACK_NEXT);
    printf("- expecting *..o*.\\n......\\n.o....\\n.....o\\n......"
            "\\n......:\n");
    board_show(test_game_2->b);
    place_marble(test_game_2, test_pos_6);
    twist_quadrant(test_game_2, SW, CCW);
    printf("- expecting 0: %d\n", test_game_2->next == BLACK_NEXT);
    printf("- expecting *..o*.\\n......\\n.o....\\n.....o\\n......"
            "\\n..*...:\n");
    board_show(test_game_2->b);
    game_free(test_game_1);
    game_free(test_game_2);
}

/* evidence_game_over: test game_over */
void evidence_game_over()
{
    printf("*** testing game_over\n");
    game* test_game = new_game(4, CELLS);
    unsigned int i;
    for (i = 0; i < 2; i++) {
        board_set(test_game->b,make_pos(0,i),WHITE);
    }
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(0,2),BLACK);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(1,0),WHITE);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(1,1),WHITE);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(0,2),WHITE);
    printf("- expecting 1: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(0,2),EMPTY);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(2,0),WHITE);
    printf("- expecting 1: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(2,0),EMPTY);
    board_set(test_game->b,make_pos(2,2),WHITE);
    printf("- expecting 1: %d\n", game_over(test_game));
    game_free(test_game);
    test_game = new_game(4, CELLS);
    for (i = 1; i < 3; i++) {
        board_set(test_game->b,make_pos(0,i),BLACK);
    }
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(1,1),BLACK);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(1,2),BLACK);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(0,3),BLACK);
    printf("- expecting 1: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(0,3),EMPTY);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(2,1),BLACK);
    printf("- expecting 1: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(2,1),EMPTY);
    board_set(test_game->b,make_pos(2,3),BLACK);
    printf("- expecting 1: %d\n", game_over(test_game));
    game_free(test_game);
    test_game = new_game(4, CELLS);
    for (i = 1; i < 3; i++) {
        board_set(test_game->b,make_pos(1,i),WHITE);
    }
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(2,1),WHITE);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(2,2),WHITE);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(1,3),WHITE);
    printf("- expecting 1: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(1,3),EMPTY);
    printf("- expecting 0: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(3,1),WHITE);
    printf("- expecting 1: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(3,1),EMPTY);
    board_set(test_game->b,make_pos(3,3),WHITE);
    printf("- expecting 1: %d\n", game_over(test_game));
    game_free(test_game);
    test_game = new_game(4, CELLS);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(3,i),BLACK);
    }
    printf("- expecting 1: %d\n", game_over(test_game));
    board_set(test_game->b,make_pos(3,2),EMPTY);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(i,3),WHITE);
    }
    printf("- expecting 1: %d\n", game_over(test_game));
    game_free(test_game);
    test_game = new_game(4, CELLS);
    unsigned int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if ((i < 2 && j % 2 == 0) || (i >= 2 && j % 2)) {
                board_set(test_game->b,make_pos(i,j),BLACK);
            } else {
                board_set(test_game->b,make_pos(i,j),WHITE);
            }
        }
    }
    printf("- expecting 1: %d\n",game_over(test_game));
    board_set(test_game->b,make_pos(0,0),EMPTY);
    printf("- expecting 0: %d\n",game_over(test_game));
    game_free(test_game);
}

/* evidence_game_outcome: test game_outcome */
void evidence_game_outcome()
{
    printf("*** testing game_outcome\n");
    game* test_game = new_game(4,CELLS);
    unsigned int i;
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(i,0),BLACK);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == BLACK_WIN);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(3,i),WHITE);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == DRAW);
    game_free(test_game);
    test_game = new_game(4, CELLS);
    for (i = 1; i < 4; i++) {
        board_set(test_game->b,make_pos(i,3),WHITE);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == WHITE_WIN);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(0,i),BLACK);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == DRAW);
    game_free(test_game);
    test_game = new_game(4, CELLS);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(i,i),BLACK);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == BLACK_WIN);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(3-i,i),WHITE);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == DRAW);
    game_free(test_game);
    test_game = new_game(4, CELLS);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(i,i),WHITE);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == WHITE_WIN);
    for (i = 0; i < 3; i++) {
        board_set(test_game->b,make_pos(3,i),BLACK);
    }
    printf("- expecting 1: %d\n",game_outcome(test_game) == DRAW);
    game_free(test_game); 
}

/* main: run the evidence functions above */
int main(int argc, char** argv)
{
    evidence_make_pos();
    evidence_board_new();
    evidence_board_show();
    evidence_board_get();
    evidence_board_set();
    evidence_new_game();
    evidence_place_marble();
    evidence_twist_quadrant();
    evidence_game_over();
    evidence_game_outcome();
    return 0;
}

