#include "gate.h"

NotGate::NotGate()
    : pmos_(TransistorType::PMOS),
      nmos_(TransistorType::NMOS)
{}

bool NotGate::evaluate(bool a) {
    pmos_.setDrain(true);
    pmos_.setGate(a);

    nmos_.setDrain(pmos_.getSource());
    nmos_.setGate(a);

    if (nmos_.isConducting()) return false;
    if (pmos_.isConducting()) return true;
    return false;
}

NandGate::NandGate()
    : pmos_a_(TransistorType::PMOS), pmos_b_(TransistorType::PMOS),
      nmos_a_(TransistorType::NMOS), nmos_b_(TransistorType::NMOS)
{}

bool NandGate::evaluate(bool a, bool b) {
    pmos_a_.setGate(a); pmos_a_.setDrain(true);
    pmos_b_.setGate(b); pmos_b_.setDrain(true);

    nmos_a_.setGate(a); nmos_a_.setDrain(true);
    nmos_b_.setGate(b); nmos_b_.setDrain(nmos_a_.getSource());

    if (nmos_b_.isConducting() && nmos_a_.isConducting()) return false;
    return true;
}

AndGate::AndGate() : nand_(), inv_() {}

bool AndGate::evaluate(bool a, bool b) {
    return inv_.evaluate(nand_.evaluate(a, b));
}

NorGate::NorGate()
    : pmos_a_(TransistorType::PMOS), pmos_b_(TransistorType::PMOS),
      nmos_a_(TransistorType::NMOS), nmos_b_(TransistorType::NMOS)
{}

bool NorGate::evaluate(bool a, bool b) {
    pmos_a_.setGate(a); pmos_a_.setDrain(true);
    pmos_b_.setGate(b); pmos_b_.setDrain(pmos_a_.getSource());

    nmos_a_.setGate(a); nmos_a_.setDrain(true);
    nmos_b_.setGate(b); nmos_b_.setDrain(true);

    if (nmos_a_.isConducting() || nmos_b_.isConducting()) return false;
    if (pmos_b_.getSource()) return true;
    return false;
}

OrGate::OrGate() : nor_(), inv_() {}

bool OrGate::evaluate(bool a, bool b) {
    return inv_.evaluate(nor_.evaluate(a, b));
}

XorGate::XorGate() : n1_(), n2_(), n3_(), n4_() {}

bool XorGate::evaluate(bool a, bool b) {
    bool n1 = n1_.evaluate(a, b);        // NAND(a,b)
    bool n2 = n2_.evaluate(a, n1);       // NAND(a, n1)
    bool n3 = n3_.evaluate(b, n1);       // NAND(b, n1)
    bool n4 = n4_.evaluate(n2, n3);      // NAND(n2, n3)
    return n4;
}