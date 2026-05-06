#include "transistor.h"

Transistor::Transistor(TransistorType type) : type_(type) {}

void Transistor::setGate(bool signal) { gate_ = signal; }
void Transistor::setDrain(bool signal) { drain_ = signal; }

bool Transistor::isConducting() const {
    return (type_ == TransistorType::NMOS) ? gate_ : !gate_;
}

bool Transistor::getSource() const {
    return isConducting() ? drain_ : false;
}