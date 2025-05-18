 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Implementation for the class "Inductor"
// Interface is in "Inductor.h"

// Inductor is derived from "Component.h"

#include"Component.h"
#include"Inductor.h"
#include<iostream>
#include<complex>

using std::complex;

// Overrides
complex<double> Inductor::setFreq_calcImpedance(const double freq_in_Hz)
{
  frequency = 2*pi*freq_in_Hz; // Hz to rad/s
  impedance = i*frequency*inductance;
  return impedance;
};

void const Inductor::printData()
{
  std::cout<<"Inductor:    inductance = "<<inductance<<" Henry | impedance = "<<impedance<<" Ohms"<<std::endl; 
};