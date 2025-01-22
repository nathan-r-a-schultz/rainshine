#include "rainshine.h"



int main (int argc, char *argv[]) {

    if (argc > 1) {
        if (strcmp(argv[1], "today") == 0) {
            today();
        }
    }

    return 0;
}