FROM centos:8
MAINTAINER Vili Petal <vi1i.petal@protonmail.com>

RUN dnf -y update && \
    dnf -y install git cmake make gcc-c++ systemd-devel && \
    git clone https://github.com/Vi1i/fount.git && \
    cd fount/build && \
    cmake .. && \
    make && \
    dnf -y remove cmake make git gcc-c++ systemd-devel

ADD content/ /

RUN chmod u+x /opt/run.sh

ENTRYPOINT ["/opt/run.sh"]

cmd ["./fount/build/fountd/fountd"]
