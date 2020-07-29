// Copyright 2020
// Author: Vi1i

// TODO(Vi1i): Check if this is really the best way to gather some of
//             this information
#include <sys/utsname.h>
#include <errno.h>

#include <string>
#include <iostream>
#include <memory>

#include <yjorn/sys/System.hpp>

namespace yjorn::sys {
auto GetSystemInfo(std::shared_ptr<info> info) -> void {
    if (!info.get()) {
        std::cerr << "shared_ptr";
    }

    struct utsname buffer;

    errno = 0;
    if (uname(&buffer) != 0) {
        std::cerr << "uname";
    }

    info->sysName = std::string(buffer.sysname);
    info->nodeName = std::string(buffer.nodename);
    info->kernelRelease = std::string(buffer.release);
    info->kernelVersion = std::string(buffer.version);
    info->machine = std::string(buffer.machine);
    info->domainName = std::string(buffer.domainname);
}
}  // namespace yjorn::sys
