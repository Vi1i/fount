#pragma once

#include <yjorn/asol/configuration.hpp>

namespace yorn::asol {
    class Simulate {
        public:
            Simulate(configuration conf);
            Simulate();

            ~Simulate();

            auto Configure(configuration conf) -> bool;
            auto Run() -> void;

        private:
            configuration _conf;
    }
}
