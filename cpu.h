#ifndef SPROCESSOR_CPU_H
#define SPROCESSOR_CPU_H

#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <string>
#include "alu.h"

enum class Opcode : uint8_t {
    LOAD  = 0x01,
    MOV   = 0x02,
    ADD   = 0x10,
    AND   = 0x11,
    OR    = 0x12,
    XOR   = 0x13,
    NOT   = 0x14,
    JMP   = 0x20,
    JZ    = 0x21,
    HALT  = 0xFF,
    PRINT = 0xF0,
};

struct Flags {
    bool zero  = false;
    bool carry = false;
};

class CPU {
public:
    static constexpr int NUM_REGS = 4;
    static constexpr int MEM_SIZE = 256;

    CPU();

    void loadProgram(const std::vector<uint8_t>& program);

    bool step();

    void run(int maxCycles = 10000);

    void dumpState() const;

    uint8_t getReg(int i) const { return regs_[i]; }
    uint8_t getPC()       const { return pc_; }
    Flags   getFlags()    const { return flags_; }

private:
    uint8_t fetch();
    uint8_t& reg(uint8_t idx);

    std::array<uint8_t, NUM_REGS> regs_ = {};
    std::array<uint8_t, MEM_SIZE> mem_  = {};
    uint8_t  pc_    = 0;
    bool     halted_ = false;
    Flags    flags_;
    ALU      alu_;
    int      cycles_ = 0;
};

#endif //SPROCESSOR_CPU_H