// Copyright 2020
// Author: Vi1i

#include <cstdlib>
#include <iostream>
#include <memory>

#include <yjorn/fount/core/Configuration.hpp>
#include <yjorn/sys/System.hpp>

auto printSystemInfo(std::shared_ptr<yjorn::sys::info> info) -> void {
    std::cout << "   System Name: " << info->sysName << std::endl;
    std::cout << "     Node Name: " << info->nodeName << std::endl;
    std::cout << "Kernel Release: " << info->kernelRelease << std::endl;
    std::cout << "Kernel Verison: " << info->kernelVersion << std::endl;
    std::cout << "       Machine: " << info->machine << std::endl;
    std::cout << "   Domain Name: " << info->domainName << std::endl;
}

auto printCpuInfo(std::shared_ptr<yjorn::sys::cpuinfo> cpuinfo) -> void {
    std::cout << "      Architecture: " << cpuinfo->architecture << std::endl;
    std::cout << "    CPU op-mode(s): " << cpuinfo->cpuOpModes << std::endl;
    std::cout << "        Byte Order: " << cpuinfo->byteOrder << std::endl;
    std::cout << "            CPU(s): " << cpuinfo->cpus << std::endl;
    std::cout << "     Online CPU(s): " << cpuinfo->onlineCpus << std::endl;
    std::cout << "Thread(s) Per Core: " << cpuinfo->threadsPerCore << std::endl; 
    std::cout << "Core(s) Per Socket: " << cpuinfo->coresPerSocket << std::endl; 
    std::cout << "         Socket(s): " << cpuinfo->sockets << std::endl; 
    std::cout << "      NUMA Node(s): " << cpuinfo->numaNodes << std::endl; 
    std::cout << " NUMA Node0 CPU(s): " << cpuinfo->numaNode0Cpus << std::endl; 
    std::cout << "         Vendor ID: " << cpuinfo->vendorId << std::endl; 
    std::cout << "        CPU Family: " << cpuinfo->cpuFamily << std::endl; 
    std::cout << "             Model: " << cpuinfo->model << std::endl; 
    std::cout << "        Model Name: " << cpuinfo->modelName << std::endl; 
    std::cout << "          Stepping: " << cpuinfo->stepping << std::endl; 
    std::cout << "           CPU MHz: " << cpuinfo->cpuMHz << std::endl; 
    std::cout << "       CPU Max MHz: " << cpuinfo->cpuMaxMHz << std::endl; 
    std::cout << "       CPU Min MHz: " << cpuinfo->cpuMinMHz << std::endl; 
    std::cout << "          BogoMIPS: " << cpuinfo->bogoMIPS << std::endl; 
    std::cout << "    Virtualization: " << cpuinfo->virtualization << std::endl; 
    std::cout << "         L1d Cache: " << cpuinfo->l1dCache << std::endl; 
    std::cout << "         L1i Cache: " << cpuinfo->l1iCache << std::endl; 
    std::cout << "          L2 Cache: " << cpuinfo->l2Cache << std::endl; 
    std::cout << "          L3 Cache: " << cpuinfo->l3Cache << std::endl; 
    std::cout << "         Microcode: " << cpuinfo->microcodeVersion << std::endl; 
    std::cout << "             Flags:";
    for (auto const &flag : cpuinfo->flags) {
        std::cout << " "  << flag;
    }
    std::cout << std::endl;
}

auto main(void) -> int {
    auto info = std::shared_ptr<yjorn::sys::info>(new yjorn::sys::info);
    auto cpuinfo = std::shared_ptr<yjorn::sys::cpuinfo>(new yjorn::sys::cpuinfo);

    yjorn::sys::GetSystemInfo(info);
    yjorn::sys::GetCpuInfo(cpuinfo);
    printSystemInfo(info);
    printCpuInfo(cpuinfo);

    return EXIT_SUCCESS;
}
