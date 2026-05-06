#pragma once

#ifndef SPROCESSOR_ALU_H
#define SPROCESSOR_ALU_H
#include <cstdint>

struct AluResult {
    uint8_t value;
    bool    zero;
    bool    carry;
};

class ALU {
public:
    enum class Op { ADD, AND, OR, XOR, NOT_A };

    AluResult execute(uint8_t a, uint8_t b, Op op);

private:
    struct BitSum { bool sum; bool carry; };
    BitSum fullAdder(bool a, bool b, bool cin);
};

#endif //SPROCESSOR_ALU_H