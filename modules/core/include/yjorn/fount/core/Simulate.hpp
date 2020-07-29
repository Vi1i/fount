// Copyright 2020
// Author: Vi1i

#pragma once

#include <yjorn/fount/core/Configuration.hpp>

namespace yjorn::fount::core {
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
}  // namespace yjorn::fount::core
