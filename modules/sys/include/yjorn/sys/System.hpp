// Copyright 2020
// Author: Vi1i

#pragma once

#include <string>
#include <memory>

namespace yjorn::sys {
// TODO(Vi1i): Add more system information, memory, cpu, network, etc.
//             Make this a goddamn monitoring system if needed.
struct info {
    std::string sysName;
    std::string nodeName;
    std::string kernelRelease;
    std::string kernelVersion;
    std::string machine;
    std::string domainName;
};

// TODO(Vi1i): Rename to something easier. Allow a way to pass a
//             filter, as we may add methods later that modify the same
//             data that we may or may not want to overwrite.
auto GetSystemInfo(std::shared_ptr<info> info) -> void;
}  // namespace yjorn::sys
