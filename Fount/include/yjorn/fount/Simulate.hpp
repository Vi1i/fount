// Copyright 2020
// Author: Vi1i

#pragma once

#include <yjorn/fount/Configuration.hpp>

namespace yjorn::fount {
class Simulate {
 public:
    explicit Simulate(Configuration conf);
    Simulate();

    ~Simulate();

    auto Configure(Configuration conf) -> bool;
    auto Run() -> void;

 private:
    Configuration _conf;
};
}  // namespace yjorn::fount
