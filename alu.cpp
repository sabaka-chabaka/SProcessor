#include "alu.h"
#include "gate.h"

ALU::BitSum ALU::fullAdder(bool a, bool b, bool cin) {
    XorGate xor1, xor2;
    AndGate and1, and2;
    OrGate  or1;

    bool sum  = xor2.evaluate(xor1.evaluate(a, b), cin);
    bool cout = or1.evaluate(
        and1.evaluate(a, b),
        and2.evaluate(xor1.evaluate(a, b), cin)
    );
    return {sum, cout};
}

AluResult ALU::execute(uint8_t a, uint8_t b, Op op) {
    uint8_t result = 0;
    bool    carry  = false;

    if (op == Op::ADD) {
        bool c = false;
        for (int i = 0; i < 8; ++i) {
            bool ai = (a >> i) & 1;
            bool bi = (b >> i) & 1;
            auto [s, co] = fullAdder(ai, bi, c);
            if (s) result |= (1 << i);
            c = co;
        }
        carry = c;
    } else {
        for (int i = 0; i < 8; ++i) {
            bool ai = (a >> i) & 1;
            bool bi = (b >> i) & 1;
            bool bit = false;

            if (op == Op::AND) {
                AndGate g; bit = g.evaluate(ai, bi);
            } else if (op == Op::OR) {
                OrGate  g; bit = g.evaluate(ai, bi);
            } else if (op == Op::XOR) {
                XorGate g; bit = g.evaluate(ai, bi);
            } else if (op == Op::NOT_A) {
                NotGate g; bit = g.evaluate(ai);
            }

            if (bit) result |= (1 << i);
        }
        carry = false;
    }

    return { result, result == 0, carry };
}