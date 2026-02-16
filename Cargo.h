#ifndef CARGO_H
#define CARGO_H

#include <string>

// One cargo item loaded onto a train
template <typename T>
struct Cargo {
    T    name;       // e.g. "Steel Beams"
    T    type;       // e.g. "Industrial"
    int  weight;     // in tons

    Cargo() : name(""), type(""), weight(0) {}
    Cargo(T name, T type, int weight)
        : name(name), type(type), weight(weight) {}
};

#endif
