#pragma once

#include <yjorn/fount/configuration.hpp>

namespace yjorn::fount {
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
