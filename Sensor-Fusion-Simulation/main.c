#include <stdlib.h>

#include "scenario.h"

int main(void) {
    srand(42);

    run_scenario(SC_NORMAL);
    run_scenario(SC_PACKET_LOSS);
    run_scenario(SC_CORRUPT_PACKET);
    run_scenario(SC_DELAYED_PACKET);

    return 0;
}
