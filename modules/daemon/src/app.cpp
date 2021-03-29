// Copyright 2020
// Author: Vi1i

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <systemd/sd-daemon.h>
#include <systemd/sd-journal.h>
#include <unistd.h>
#include <vector>

#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/systemd_sink.h"
#include "spdlog/spdlog.h"

#include <yjorn/fount/core/Configuration.hpp>
#include <yjorn/net/Socket.hpp>
#include <yjorn/sys/System.hpp>

auto setup_logging() -> void {
    spdlog::init_thread_pool(8192, 1);
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    auto systemd_sink = std::make_shared<spdlog::sinks::systemd_sink_mt>();

    std::vector<spdlog::sink_ptr> sinks {stdout_sink, systemd_sink};
    auto logger = std::make_shared<spdlog::async_logger>("fountd", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    spdlog::register_logger(logger);
    logger->set_level(spdlog::level::debug);
}

auto signalHandler(int signum) -> void {
    spdlog::get("fountd")->warn("signal({}) received", signum);
    exit(signum);
}

auto daemonize() -> int {
    signal(SIGTERM, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGINT, signalHandler);

    auto ret = sd_notify(0, "READY=1");

    return ret;
}

auto main(int argc, char* argv[]) -> int {
    setup_logging();

    int port(32000);

    if(argc > 2) {
        exit(1);
    } else {
        if(argc == 2) {
            port = std::stoi(argv[1]);
            if(port < 1024) {
                spdlog::get("fountd")->error("privileged port({}) used", port);
                exit(1);
            }
        }
    }

    daemonize();
    auto info = std::shared_ptr<yjorn::sys::info>(new yjorn::sys::info);
    auto cpuinfo = std::shared_ptr<yjorn::sys::cpuinfo>(new yjorn::sys::cpuinfo);
    yjorn::sys::GetSystemInfo(info);
    yjorn::sys::GetCpuInfo(cpuinfo);

    auto send = yjorn::Socket();
    auto recv = yjorn::Socket();

    recv.create();
    recv.bind(32000);
    recv.listen();
    for (;;) {
        spdlog::get("fountd")->debug("sleeping 1s");
        sleep(1);
    }
    return EXIT_SUCCESS;
}

// If SIGTERM is received, shut down the daemon and exit cleanly.
// If SIGHUP is received, reload the configuration files, if this applies.
// TODO(Vi1i): The skeleton code is done above.

// Provide a correct exit code from the main daemon process, as this is
// used by the init system to detect service errors and problems. It is
// recommended to follow the exit code scheme as defined in the LSB
// recommendations for SysV init scripts.
// TODO(Vi1i): Setup/look into the exit codes.

// If possible and applicable, expose the daemon's control interface via
// the D-Bus IPC system and grab a bus name as last step of
// initialization.
// TODO(Vi1i): This is definitly a use case we will need. So we will have
//             to investigate it, I believe there are some ...

// For integration in systemd, provide a .service unit file that carries
// information about starting, stopping and otherwise maintaining the
// daemon. See systemd.service(5) for details.
// As much as possible, rely on the init system's functionality to limit
// the access of the daemon to files, services and other resources, i.e.
// in the case of systemd, rely on systemd's resource limit control
// instead of implementing your own, rely on systemd's privilege dropping
// code instead of implementing it in the daemon, and similar. See
// systemd.exec(5) for the available controls.
// TODO(Vi1i): This means that we don't handle the PID, forking, etc.
//             that used to be required in the older init systems.

// If D-Bus is used, make your daemon bus-activatable by supplying a
// D-Bus service activation configuration file. This has multiple
// advantages: your daemon may be started lazily on-demand; it may be
// started in parallel to other daemons requiring it — which maximizes
// parallelization and boot-up speed; your daemon can be restarted on
// failure without losing any bus requests, as the bus queues requests
// for activatable services. See below for details.
// TODO(Vi1i): See the previous bus todo. This section gives another
//             reason to do this.

// If your daemon provides services to other local processes or remote
// clients via a socket, it should be made socket-activatable following
// the scheme pointed out below. Like D-Bus activation, this enables
// on-demand starting of services as well as it allows improved
// parallelization of service start-up. Also, for state-less protocols
// (such as syslog, DNS), a daemon implementing socket-based activation
// can be restarted without losing a single request. See below for
// details.
// TODO(Vi1i): We will in the future atleast need this, so might as well
//             get cracking.

// If applicable, a daemon should notify the init system about startup
// completion or status updates via the sd_notify(3) interface.
// TODO(Vi1i): Shown above, but really we need this to be manageable in
//             any place that can determine state.

// Instead of using the syslog() call to log directly to the system syslog
// service, a new-style daemon may choose to simply log to standard error
// via fprintf(), which is then forwarded to syslog by the init system. If
// log levels are necessary, these can be encoded by prefixing individual
// log lines with strings like "<4>" (for log level 4 "WARNING" in the
// syslog priority scheme), following a similar style as the Linux
// kernel's printk() level system. For details, see sd-daemon(3) and
// systemd.exec(5).
// TODO(Vi1i): Basic setup above, two sinks, console and systemd.
//             Will need to setup a flag to enable a console mode?
