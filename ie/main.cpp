#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include <cstdio>

union b {
    unsigned char c;
    struct {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;
    } bits;
};

int main() {
    struct termios old_tio, new_tio;
    unsigned char c[3];

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;

    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    while (1) {
        read(STDIN_FILENO, &c, 1);
        b a;
        a.c = c[0];

        printf("byte: %d, bits: %d%d%d%d%d%d%d%d\n", c[0], a.bits.b7, a.bits.b6,
               a.bits.b5, a.bits.b4, a.bits.b3, a.bits.b2, a.bits.b1,
               a.bits.b0);

        if (c[0] == 'q') {
            break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

    return 0;
}

