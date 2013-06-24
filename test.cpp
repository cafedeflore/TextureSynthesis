#include <stdio.h>
int char2int(int c) {
    int i = (int) c;
    if(c > 0)
        return i;
    else
        return -i+127;
}
