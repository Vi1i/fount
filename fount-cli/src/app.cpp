// Copyright 2020
// Author: Vi1i

#include <cstdlib>
#include <iostream>
#include <memory>

#include <yjorn/fount/Configuration.hpp>
#include <yjorn/fount/System.hpp>

auto printSystemInfo(std::shared_ptr<yjorn::fount::info> info) -> void {
    std::cout << "   System Name: " << info->sysName << std::endl;
    std::cout << "     Node Name: " << info->nodeName << std::endl;
    std::cout << "Kernel Release: " << info->kernelRelease << std::endl;
    std::cout << "Kernel Verison: " << info->kernelVersion << std::endl;
    std::cout << "       Machine: " << info->machine << std::endl;
    std::cout << "   Domain Name: " << info->domainName << std::endl;
}

auto main(void) -> int {
    auto info = std::shared_ptr<yjorn::fount::info>(new yjorn::fount::info);

    yjorn::fount::GetSystemInfo(info);
    printSystemInfo(info);

    return EXIT_SUCCESS;
}
