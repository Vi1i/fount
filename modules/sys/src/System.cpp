// Copyright 2020
// Author: Vi1i

// TODO(Vi1i): Check if this is really the best way to gather some of
//             this information
#include <sys/utsname.h>
#include <errno.h>

#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

#include <yjorn/sys/System.hpp>

namespace {
    // const std::string WHITESPACE = " \n\r\t\f\v";
    const char WHITESPACE[] = " \n\r\t\f\v";

    std::string ltrim(const std::string& s) {
        size_t start = s.find_first_not_of(WHITESPACE);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    std::string rtrim(const std::string& s) {
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    std::string trim(const std::string& s) {
        return rtrim(ltrim(s));
    }

    auto SetCpuInfo(std::shared_ptr<yjorn::sys::cpuinfo> cpuinfo, std::pair<std::string, std::string> p) -> void {
        if (p.first == "processor") {
            cpuinfo->cpus++;
        } else if (p.first == "vendor_id") {
            cpuinfo->vendorId = p.second;
        } else if (p.first == "cpu family") {
            cpuinfo->cpuFamily = std::stoi(p.second, nullptr, 10);
        } else if (p.first == "model") {
            cpuinfo->model = std::stoi(p.second, nullptr, 10);
        } else if (p.first == "model name") {
            cpuinfo->modelName = p.second;
        } else if (p.first == "stepping") {
            cpuinfo->stepping = std::stoi(p.second, nullptr, 10);
        } else if (p.first == "microcode") {
            cpuinfo->microcodeVersion = p.second;
        } else if (p.first == "cpu MHz") {
            cpuinfo->cpuMHz = std::stof(p.second, nullptr);
        } else if (p.first == "cache size") {
            cpuinfo->l3Cache = std::stoi(p.second, nullptr, 10);
        } else if (p.first == "physical id") {
        } else if (p.first == "siblings") {
        } else if (p.first == "core id") {
        } else if (p.first == "cpu cores") {
            cpuinfo->coresPerSocket = std::stoi(p.second, nullptr, 10);
        } else if (p.first == "apicid") {
        } else if (p.first == "initial apicid") {
        } else if (p.first == "fpu") {
        } else if (p.first == "fpu_exception") {
        } else if (p.first == "cpuid level") {
        } else if (p.first == "wp") {
        } else if (p.first == "flags") {
            char delimeter = ' ';
            std::stringstream ss(p.second);
            std::string token;
            while (std::getline(ss, token, delimeter)) {
                cpuinfo->flags.push_back(p.second);
            }
        } else if (p.first == "bugs") {
        } else if (p.first == "bogomips") {
            cpuinfo->bogoMIPS = std::stof(p.second, nullptr);
        } else if (p.first == "clflush size") {
        } else if (p.first == "cache_alignment") {
        } else if (p.first == "address sizes") {
        } else if (p.first == "power management") {
        } else if (p.first == "vmx flags") {
        } else {
            std::cerr << "cpuinfo key(" << p.first << ") does not exist: ";
            // TODO(Vi1i): This throw is only here for development catching unknowns
            //             Will need to remove eventually
            throw std::runtime_error(p.first);
        }
    }
}  // namespace

namespace yjorn::sys {
    auto GetSystemInfo(std::shared_ptr<info> info) -> void {
        if (!info.get()) {
            std::cerr << "shared_ptr: ";
        }

        struct utsname buffer;

        errno = 0;
        if (uname(&buffer) != 0) {
            std::cerr << "uname: ";
        }

        info->sysName = std::string(buffer.sysname);
        info->nodeName = std::string(buffer.nodename);
        info->kernelRelease = std::string(buffer.release);
        info->kernelVersion = std::string(buffer.version);
        info->machine = std::string(buffer.machine);
        info->domainName = std::string(buffer.domainname);
    }

    auto GetCpuInfo(std::shared_ptr<cpuinfo> cpuinfo) -> void {
        if (!cpuinfo.get()) {
            std::cerr << "shared_ptr: ";
        }

        std::filesystem::path fd("/proc/cpuinfo");
        if (!std::filesystem::exists(fd)) {
            std::cerr << "file (" << fd << ") does not exist: ";
            throw std::runtime_error(fd);
        }

        std::ifstream f("/proc/cpuinfo");
        if (f.is_open()) {
            std::string line;
            char delimeter = ':';
            while (std::getline(f, line)) {
                if (line == "") {
                    continue;
                }
                std::stringstream ss;
                std::string varName;
                std::string varVal;
                ss.str(line);
                std::getline(ss, varName, delimeter);
                std::getline(ss, varVal, delimeter);
                // auto p = std::make_pair<std::string, std::string>(trim(varName), trim(varVal));
                auto p = std::make_pair(trim(varName), trim(varVal));
                SetCpuInfo(cpuinfo, p);
            }

            std::set<std::string> s;
            auto vsize = cpuinfo->flags.size();
            for (auto i = 0; i < vsize; ++i) {
                s.insert(cpuinfo->flags[i]);
            }
            cpuinfo->flags.assign(s.begin(), s.end());
            // cpuinfo->threadsPerCore = () ?
        }
    }
}  // namespace yjorn::sys
