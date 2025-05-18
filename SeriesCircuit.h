 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Interface for the class "SeriesCircuit"

// SeriesCircuit is derived from "Circuit.h"

#ifndef SERIESCIRCUIT_H
#define SERIESCIRCUIT_H

#include"Component.h"
#include"Circuit.h"
#include<complex>

using std::complex;

class SeriesCircuit : public Circuit
{
  public:
    // Constructor/Destructor
    SeriesCircuit() = default;  // no member data to initialise,
    ~SeriesCircuit();           // or release

    // Overriddes
    std::string isSeries_or_Parallel() {return "Series";};
    // overridden to return circuit type as a string
    complex<double> combineImpedance(const complex<double> z1, const complex<double> z2) {return z1 + z2;};
    // overridden to implement series Impedance formula
};

#endif