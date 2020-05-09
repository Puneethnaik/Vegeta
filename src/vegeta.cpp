
#include "vegeta_log.h"



int main(int argc, char **argv) {
    if(init_log() != VEGETA_OK) {
        write(STDERR_FILENO, "error occured", 13);
        return 1;
    }

    return VEGETA_OK;
}