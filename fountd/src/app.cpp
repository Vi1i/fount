#include "daemonize_systemd.hpp"

#include <yjorn/fount/configuration.hpp>

#include <cstdlib>


auto main(void) -> int {
    daemonize();
    for(;;) {
        std::cout << "Sleeping..." << std::endl;
        sleep(1);
    }
    return EXIT_SUCCESS;
}
