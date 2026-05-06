#ifndef SPROCESSOR_GATE_H
#define SPROCESSOR_GATE_H

#pragma once

#include "transistor.h"

class NotGate {
public:
    NotGate();
    bool evaluate(bool a);
private:
    Transistor pmos_;
    Transistor nmos_;
};

class NandGate {
public:
    NandGate();
    bool evaluate(bool a, bool b);
private:
    Transistor pmos_a_;
    Transistor pmos_b_;
    Transistor nmos_a_;
    Transistor nmos_b_;
};

class AndGate {
public:
    AndGate();
    bool evaluate(bool a, bool b);
private:
    NandGate nand_;
    NotGate  inv_;
};

class NorGate {
public:
    NorGate();
    bool evaluate(bool a, bool b);
private:
    Transistor pmos_a_;
    Transistor pmos_b_;
    Transistor nmos_a_;
    Transistor nmos_b_;
};

class OrGate {
public:
    OrGate();
    bool evaluate(bool a, bool b);
private:
    NorGate nor_;
    NotGate inv_;
};

class XorGate {
public:
    XorGate();
    bool evaluate(bool a, bool b);
private:
    NandGate n1_, n2_, n3_, n4_;
};


#endif //SPROCESSOR_GATE_H