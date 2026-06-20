#ifndef AFFINE_H
#define AFFINE_H

#include <cstdint>
#include <cstddef>

extern "C" {
    void ProcessData(uint8_t* data, size_t len, int key_a, int key_b, bool encrypt);
    void ProcessDataVerbose(uint8_t* data, size_t len, int key_a, int key_b, bool encrypt);
}

#endif
