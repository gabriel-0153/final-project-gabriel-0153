 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Implementation for the class "Resistor"
// Interface is in "Resistor.h"

// Resistor is derived from "Component.h"

#include"Component.h"
#include"Resistor.h"
#include<iostream>
#include<complex>

using std::complex;

// Overrides
complex<double> Resistor::setFreq_calcImpedance(const double freq_in_Hz)
{
  frequency = 2*pi*freq_in_Hz; 
  impedance = {resistance, 0};
  return impedance;
};

void const Resistor::printData()
{
  std::cout<<"Resistor:    resistance = "<<resistance<<" Ohms | impedance = "<<impedance<<" Ohms"<<std::endl; 
};