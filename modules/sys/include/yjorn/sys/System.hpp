// Copyright 2020
// Author: Vi1i

#pragma once

#include <string>
#include <vector>
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

struct cpuinfo {
    std::string architecture;
    std::string cpuOpModes;
    std::string byteOrder;
    int cpus;
    std::string onlineCpus;  // (Vi1i) Perhaps make this a boolean array sizeof(cpus)
    int threadsPerCore;
    int coresPerSocket;
    int sockets;
    int numaNodes;
    std::string vendorId;
    int cpuFamily;
    std::string model;
    std::string modelName;
    int stepping;
    float cpuMHz;
    float cpuMaxMHz;
    float cpuMinMHz;
    float bogoMIPS;
    std::string virtualization;
    int l1dCache;
    int l1iCache;
    int l2Cache;
    int l3Cache;
    std::string numaNode0Cpus;  // (Vi1i) Perhaps make this a boolean array sizeof(cpus)
    std::string microcodeVersion;
    std::vector<std::string> flags;
};

// TODO(Vi1i): Rename to something easier. Allow a way to pass a
//             filter, as we may add methods later that modify the same
//             data that we may or may not want to overwrite.
auto GetSystemInfo(std::shared_ptr<info> info) -> void;
auto GetCpuInfo(std::shared_ptr<cpuinfo> cpuinfo) -> void;
}  // namespace yjorn::sys
