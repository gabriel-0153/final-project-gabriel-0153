 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Implementation for the class "Capacitor"
// Interface is in "Capacitor.h"

// Capacitor is derived from "Component.h"

#include"Component.h"
#include"Capacitor.h"
#include"TUI.h"
#include<iostream>
#include<complex>
#include<sstream>

using std::complex;

// Overrides
complex<double> Capacitor::setFreq_calcImpedance(const double freq_in_Hz)
{
  frequency = 2*pi*freq_in_Hz; // Hz to rad/s
  impedance = 1.0 / (i*frequency*capacitance);
  return impedance;
};

void const Capacitor::printData()
{
  TUI::CentredPrint<<"Capacitor:    capacitance = "<<capacitance<<" Coulombs/Volt | impedance = "<<real(impedance)<<" + "<<imag(impedance)<<"i (Ohms)"<<std::endl;
};