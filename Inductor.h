 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Interface for the class "Inductor"
// Prototypes are implemented in "Inductor.cpp"

// Inductor is derived from "Component.h"

// Inductor adds a Inductance(L) data member, overrides calcImpedance() to Z = iwL, and printData() to display these

#ifndef INDUCTOR_H
#define INDUCTOR_H

#include"Component.h"
#include<complex>

using std::complex;

class Inductor : public Component
{
  protected:
    // DATA MEMBER
    double inductance{0}; // in Henry

  public:
    // Constructor/Destructor
    Inductor(const double L_in) : inductance{L_in} {};
    ~Inductor() = default;

    // Overrides
    void const printData();
    complex<double> setFreq_calcImpedance(const double freq_in_Hz);

    // Public Setters/Getters
    void setInductance(const double L_in) {inductance = L_in;};
    double getInductance() const {return inductance;}; 
};

#endif