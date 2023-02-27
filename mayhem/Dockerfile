FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libz-dev libbz2-dev liblzma-dev libcurl3-dev build-essential automake git libncurses5-dev clang

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
RUN clang++ /repo/mayhem/fuzz_print_error.cpp -fsanitize=fuzzer,address -I /repo/ -I /htslib/ ./libst.a /htslib/libhts.a -lpthread -lz -lm -lbz2 -llzma -lcurl  -lz  -lpthread -o /fuzz

FROM ubuntu:20.04 as package
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libz-dev libbz2-dev liblzma-dev libcurl3-dev
COPY --from=builder /repo/samtools /
COPY --from=builder /fuzz /fuzz_print_error
