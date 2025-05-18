 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Interface for the class "Resistor"
// Prototypes are implemented in "Resistor.cpp"

// Resistor is derived from "Resistor.h"

// Resistor adds a resistance(R) data member, overrides calcImpedance() to Z = R, and printData() to display these

#ifndef RESISTOR_H
#define RESISTOR_H

#include"Component.h"
#include<complex>

using std::complex;

class Resistor : public Component
{
  protected:
    // DATA MEMBER
    double resistance{0}; // Ohms

  public:
    // Constructor/Destructor
    Resistor(const double R_in) : resistance{R_in} {};
    ~Resistor() = default;

    // Overrides
    void const printData();
    complex<double> setFreq_calcImpedance(const double freq_in_Hz);

    // Public Setters/Getters
    void setResistance(const double R_in) {resistance = R_in;};
    double getResistance() const {return resistance;}; 
};

#endif