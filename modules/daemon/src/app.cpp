// Copyright 2020
// Author: Vi1i

#include <cstdlib>

#include "daemonize_systemd.hpp"
#include <yjorn/fount/Configuration.hpp>

auto main(void) -> int {
    daemonize();
    for (;;) {
        std::cout << "Sleeping..." << std::endl;
        sleep(1);
    }
    return EXIT_SUCCESS;
}
