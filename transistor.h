#ifndef SPROCESSOR_TRANSISTOR_H
#define SPROCESSOR_TRANSISTOR_H

#pragma once


enum class TransistorType { NMOS, PMOS };

class Transistor {
public:
    explicit Transistor(TransistorType);

    void setGate(bool signal);
    void setDrain(bool signal);

    bool getSource() const;
    bool isConducting() const;

    TransistorType getType() const { return type_; }

private:
    TransistorType type_;
    bool gate_  = false;
    bool drain_ = false;
};

#endif //SPROCESSOR_TRANSISTOR_H