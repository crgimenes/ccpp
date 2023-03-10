#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios old_tio, new_tio;
    unsigned char c;

    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;

    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    while (1) {
        if (read(STDIN_FILENO, &c, 1) == 1) {
            printf("Caractere lido: %c\n", c);
            if (c == 'q') {
                break;
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

    return 0;
}

