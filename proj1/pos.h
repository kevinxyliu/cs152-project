#ifndef _POS_H
#define _POS_H

struct pos {
    unsigned int r, c;
};

typedef struct pos pos;

/* make_pos: a convenient function to create a pos value */
pos make_pos(unsigned int r, unsigned int c);

#endif /* _POS_H */
