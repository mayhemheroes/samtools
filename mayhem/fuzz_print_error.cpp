#include <stdint.h>
#include <stdio.h>
#include <climits>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
    #include "samtools.h"
}
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    std::string subcommand = provider.ConsumeRandomLengthString(1000);
    std::string message = provider.ConsumeRemainingBytesAsString();

    print_error(subcommand.c_str(), "%s", message.c_str());

    return 0;
}
