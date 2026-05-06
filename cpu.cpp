#include "cpu.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

CPU::CPU() { regs_.fill(0); mem_.fill(0); }

void CPU::loadProgram(const std::vector<uint8_t>& program) {
    if (program.size() > MEM_SIZE)
        throw std::runtime_error("No memory for prog");
    for (size_t i = 0; i < program.size(); ++i)
        mem_[i] = program[i];
    pc_ = 0; halted_ = false; cycles_ = 0;
    regs_.fill(0); flags_ = {};
}

uint8_t CPU::fetch() {
    if (pc_ >= MEM_SIZE) throw std::runtime_error("PC out of mem");
    return mem_[pc_++];
}

uint8_t& CPU::reg(uint8_t idx) {
    if (idx >= NUM_REGS) throw std::runtime_error("Invalid register index");
    return regs_[idx];
}

bool CPU::step() {
    if (halted_) return false;

    uint8_t opcode = fetch();
    ++cycles_;

    switch (static_cast<Opcode>(opcode)) {

    case Opcode::LOAD: {
        uint8_t rx  = fetch();
        uint8_t imm = fetch();
        reg(rx) = imm;
        break;
    }
    case Opcode::MOV: {
        uint8_t rx = fetch(), ry = fetch();
        reg(rx) = reg(ry);
        break;
    }
    case Opcode::ADD: {
        uint8_t rx = fetch(), ry = fetch();
        auto res = alu_.execute(reg(rx), reg(ry), ALU::Op::ADD);
        reg(rx) = res.value; flags_.zero = res.zero; flags_.carry = res.carry;
        break;
    }
    case Opcode::AND: {
        uint8_t rx = fetch(), ry = fetch();
        auto res = alu_.execute(reg(rx), reg(ry), ALU::Op::AND);
        reg(rx) = res.value; flags_.zero = res.zero;
        break;
    }
    case Opcode::OR: {
        uint8_t rx = fetch(), ry = fetch();
        auto res = alu_.execute(reg(rx), reg(ry), ALU::Op::OR);
        reg(rx) = res.value; flags_.zero = res.zero;
        break;
    }
    case Opcode::XOR: {
        uint8_t rx = fetch(), ry = fetch();
        auto res = alu_.execute(reg(rx), reg(ry), ALU::Op::XOR);
        reg(rx) = res.value; flags_.zero = res.zero;
        break;
    }
    case Opcode::NOT: {
        uint8_t rx = fetch();
        auto res = alu_.execute(reg(rx), 0, ALU::Op::NOT_A);
        reg(rx) = res.value; flags_.zero = res.zero;
        break;
    }
    case Opcode::JMP: {
        uint8_t addr = fetch();
        pc_ = addr;
        break;
    }
    case Opcode::JZ: {
        uint8_t addr = fetch();
        if (flags_.zero) pc_ = addr;
        break;
    }
    case Opcode::PRINT: {
        uint8_t rx = fetch();
        std::cout << "  [PRINT] R" << (int)rx
                  << " = " << (int)reg(rx)
                  << " (0x" << std::hex << std::setw(2) << std::setfill('0')
                  << (int)reg(rx) << std::dec << ")\n";
        break;
    }
    case Opcode::HALT:
        halted_ = true;
        return false;

    default:
        throw std::runtime_error(
            "Unknown opcode: 0x" +
            std::to_string(opcode));
    }

    return !halted_;
}

void CPU::run(int maxCycles) {
    while (!halted_ && cycles_ < maxCycles) {
        step();
    }
    if (cycles_ >= maxCycles)
        std::cout << "  [WARN] Limit  (" << maxCycles << ")\n";
}

void CPU::dumpState() const {
    std::cout << "─────────────────────────────\n";
    std::cout << " PC = " << std::setw(3) << (int)pc_
              << "  cycles: " << cycles_ << "\n";
    for (int i = 0; i < NUM_REGS; ++i) {
        std::cout << " R" << i << " = "
                  << std::setw(3) << (int)regs_[i]
                  << "  (0x" << std::hex << std::setw(2)
                  << std::setfill('0') << (int)regs_[i]
                  << std::dec << ")\n";
    }
    std::cout << " flags: Z=" << flags_.zero
              << "  C=" << flags_.carry << "\n";
    std::cout << " stat: " << (halted_ ? "HALT" : "work") << "\n";
    std::cout << "─────────────────────────────\n";
}