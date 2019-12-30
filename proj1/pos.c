/* Xinyu Liu, xinyuliu
 * CS 152, Spring 2019
 * Project 1
 */

#include <stdlib.h>
#include <stdio.h>
#include "pos.h"

/* make_pos: a convenience function to create a pos value */
pos make_pos(unsigned int r, unsigned int c)
{
    pos pos_new = {r,c};
    return pos_new;
}
