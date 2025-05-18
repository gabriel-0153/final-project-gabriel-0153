 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Interface for the class "Capacitor"
// Prototypes are implemented in "Capacitor.cpp"

// Capacitor is derived from "Component.h"

// Capacitor adds a Capacitance(C) data member, overrides calcImpedance() to Z = 1/iwC, and printData() to display these

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include"Component.h"
#include<complex>

using std::complex;

class Capacitor : public Component
{
  protected:
    // DATA MEMBER
    double capacitance{0}; // Coulombs/Volt

  public:
    // Constructor/Destructor
    Capacitor(const double C_in) : capacitance{C_in} {};
    ~Capacitor() = default;

    // Overrides
    void const printData();
    complex<double> setFreq_calcImpedance(const double freq_in_Hz);

    // Public Setters/Getters
    void setCapacitance(const double C_in) {capacitance = C_in;};
    double getCapacitance() const {return capacitance;}; 
};

#endif