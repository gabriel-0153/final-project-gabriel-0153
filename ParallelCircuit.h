 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Interface for the class "ParallelCircuit.h"

// ParallelCircuit is derived from "Circuit.h"

#ifndef PARLLELCIRCUIT_H
#define PARLLELCIRCUIT_H

#include"Component.h"
#include"Circuit.h"
#include<complex>

using std::complex;

class ParallelCircuit : public Circuit
{
  public:
    // Constructor/Destructor
    ParallelCircuit() = default;  // no member data to initialise,
    ~ParallelCircuit() = default; // or release

    // Overriddes
    std::string isSeries_or_Parallel() {return "Parallel";};
    // overridden to return circuit type as a string
    complex<double> combineImpedance(const complex<double> z1, const complex<double> z2) {return 1.0 / ((1.0 / z1)+(1.0 / z2));};
    // overridden to implement parallel Impedance formula
};

#endif