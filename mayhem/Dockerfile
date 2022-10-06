FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libz-dev libbz2-dev liblzma-dev libcurl3-dev build-essential automake git libncurses5-dev

RUN git clone --recursive https://github.com/samtools/htslib.git
WORKDIR /htslib
RUN autoreconf -i
RUN ./configure
RUN make -j8
ENV LD_LIBRARY_PATH=/htslib

COPY . /repo
WORKDIR /repo
RUN autoreconf
RUN ./configure
RUN make -j8

FROM ubuntu:20.04 as package
COPY --from=builder /repo/samtools /

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libz-dev libbz2-dev liblzma-dev build-essential automake git libcurl3-dev
RUN git clone --recursive https://github.com/samtools/htslib.git
WORKDIR /htslib
RUN autoreconf -i
RUN ./configure
RUN make -j8
ENV LD_LIBRARY_PATH=/htslib
