#ifndef TEST_H
#define TEST_H

#include <stdio.h>

int char2int(char c) {
    int i = (int) c;
    if(i >= 0)
        return i;
    else
        return i+256;
}

#endif
