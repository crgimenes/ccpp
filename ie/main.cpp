#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios old_tio, new_tio;
    unsigned char c[2];

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;

    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    while (1) {
        read(STDIN_FILENO, &c, 1);
        printf("Caractere lido: %s\n", c);
        if (c[0] == 'q') {
            break;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

    return 0;
}

