/* Xinyu Liu, xinyuliu
 * CS 152, Spring 2019
 * Project 2
 */

#include <stdlib.h>
#include <stdio.h>
#include "pos.h"
#include "board.h"
#include "logic.h"
#include <string.h>

/* start_game: print the instruction of the game to the screen */
void start_game(game* game)
{
    printf("*** Welcome to Pentago! ***\n");
    printf("Instructions: Each player takes turns to place marbles on "
            "the board, and then \nrotate one of the four quadrants (NW,NE,"
            "SW,SE) either clockwise (CW) or \ncounterclockwise (CCW). NW "
            "stands for the upper left quadrant, NE stands for \nthe upper "
            "right quadrant, SW stands for the lower left quadrant, and "
            "SE stands \nfor the lower right quadrant. The first player "
            "who has %d marbles in a row wins \nthe game. Start playing "
            "now!\n", game->b->side - 1);
}

/* print_prompt: print the message on the screen, asking for either black
 * or white to play */
void print_prompt(game* game)
{
    if (game->next == BLACK_NEXT) {
        printf("Black: ");
    } else {
        printf("White: ");
    }
}

/* valid_char: check if the character is a either a letter or a number */
int valid_char(char index)
{
    int number = index >= 48 && index <= 57;
    int upper_case = index >= 65 && index <= 90;
    int lower_case = index >= 97 && index <= 122;
    return number || upper_case || lower_case;
}

/* char_to_int: turn a character into an integer by arithmetic using ASCII
 * character codes */
int char_to_int(char index)
{
    if (index >= 48 && index <= 57) {
        return index - 48;
    } else if (index >= 65 && index <= 90) {
        return index - 55;
    }
    return index - 61;
}

/* scan_pos: read in two characters until they represent a valid position,
 * and return the corresponding position */
pos scan_pos(game* game)
{
    char first_char,second_char;
    pos res;
    print_prompt(game);
    scanf(" %c%c",&first_char,&second_char);
    while (valid_char(first_char) == 0 || valid_char(second_char) == 0) {
        printf("Characters not valid! Try again.\n");
        print_prompt(game);
        scanf(" %c%c",&first_char,&second_char);
    }
    res.r = char_to_int(first_char);
    res.c = char_to_int(second_char);
    return res;
}

/* current_player_win: check if the player who just placed a marble is
 * the winner. This function is only called when game is over */
int current_player_win(game* game)
{
    outcome res = game_outcome(game);
    if (game->next == BLACK_NEXT) {
        if (res == BLACK_WIN) {
            return 1;
        }
        return 0;
    } else {
        if (res == WHITE_WIN) {
            return 1;
        }
        return 0;
    }
}

/* valid_quadrant: check if the two letters that the user types in form a
 * valid quadrant */
int valid_quadrant(char north_south, char west_east)
{
    return (north_south == 'N' || north_south == 'S')
        && (west_east == 'W' || west_east == 'E');
}

/* get_quadrant: return the quadrant that the two letters represent. This
 * function will only be called after valid_quadrant returns true */
quadrant get_quadrant(char north_south, char west_east)
{
    if (north_south == 'N') {
        if (west_east == 'W') {
            return NW;
        }
        return NE;
    } else {
        if (west_east == 'W') {
            return SW;
        }
        return SE;
    }
}

/* valid_direction: check if the string that the user types in is either
 * CW or CCW */
int valid_direction(char* string)
{
    return strcmp(string,"CCW") == 0 || strcmp(string,"CW") == 0;
}

/* get_direction: return the direction that the string represents. This
 * function will only be called after valid_direction returns true */
direction get_direction(char* string)
{
    if (strcmp(string,"CCW") == 0) {
        return CCW;
    }
    return CW;
}

/* perform_twist: read in the quadrant and direction of the twist until
 * they are valid, and perform this twist */
void perform_twist(game* game)
{
    board_show(game->b);
    char qua_NS, qua_WE, dir[4];
    printf("The quadrant you want to rotate is (NW,NE,SW,SE): ");
    scanf(" %c%c",&qua_NS,&qua_WE);
    while (valid_quadrant(qua_NS,qua_WE) == 0) {
        printf("Quadrant not valid! Try again.\n");
        printf("The quadrant you want to rotate is (NW,NE,SW,SE): ");
        scanf(" %c%c",&qua_NS,&qua_WE);
    }
    quadrant q = get_quadrant(qua_NS,qua_WE);
    printf("The direction to rotate your quadrant is (CW,CCW): ");
    scanf(" %s",dir);
    while (valid_direction(dir) == 0) {
        printf("Direction not valid! Try again.\n");
        printf("The direction to rotate your quadrant is (CW,CCW): ");
        scanf(" %s",dir);
    }
    direction d = get_direction(dir);
    twist_quadrant(game,q,d);
}

/* print_outcome: print the outcome of the game */
void print_outcome(game* game)
{
    outcome res = game_outcome(game);
    if (res == BLACK_WIN) {
        printf("The game is over. Black wins!\n");
    } else if (res == WHITE_WIN) {
        printf("The game is over. White wins!\n");
    } else {
        printf("The game is over. It is a draw!\n");
    }
    printf("The final board is:\n");
    board_show(game->b);
}

/* play_game: create a game with given side and type, and play the game */
void play_game(unsigned int side, enum type type)
{
    game* game = new_game(side,type);
    start_game(game);
    while (game_over(game) == 0) {
        board_show(game->b);
        pos marble = scan_pos(game);
        while (marble.r >= side || marble.c >= side ||
                place_marble(game,marble) == 0) {
            printf("The move is not legal! Try again.\n");
            marble = scan_pos(game);
        }
        if (game_over(game) == 0 || current_player_win(game) == 0) {
            perform_twist(game);
        }
    }
    print_outcome(game);
    game_free(game);
}

/* main: play the game according to the command line information */
int main(int argc, char** argv)
{
    unsigned int side;
    enum type type;
    int side_defined = 0, type_defined = 0;
    unsigned int i = 1;
    while (i < argc) {
        if (strcmp(argv[i],"-s") == 0) {
            if (side_defined == 1) {
                fprintf(stderr, "main: side is defined more than once\n");
                exit(1);
            }
            side = atoi(argv[i+1]);
            i++;
            side_defined = 1;
        } else if (strcmp(argv[i],"-c") == 0) {
            if (type_defined == 1) {
                fprintf(stderr, "main: type is defined more than once\n");
                exit(1);
            }
            type = CELLS;
            type_defined = 1;
        } else if (strcmp(argv[i],"-b") == 0) {
            if (type_defined == 1) {
                fprintf(stderr, "main: type is defined more than once\n");
                exit(1);
            }
            type = BITS;
            type_defined = 1;
        } else {
            fprintf(stderr, "main: the string %s not identified\n",argv[i]);
            exit(1);
        }
        i++;
    }
    if (side_defined == 0 || type_defined == 0) {
        fprintf(stderr, "main: side or type not yet defined\n");
        exit(1);
    }
    play_game(side,type);
    return 0;
}
