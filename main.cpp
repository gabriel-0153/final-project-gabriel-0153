 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

#include<complex>
#include<iostream>
#include<memory>
#include"Component.h"
#include"Resistor.h"
#include"Capacitor.h"
#include"Inductor.h"
#include"Circuit.h"
#include"SeriesCircuit.h"
#include"ParallelCircuit.h"

using std::complex;

main() // test
{
  std::shared_ptr<Circuit> myCircuit = std::make_shared<ParallelCircuit>();
  myCircuit->emplaceComponent<Resistor>(57.0);
  myCircuit->emplaceComponent<Capacitor>(57.0);
  myCircuit->emplaceComponent<Inductor>(57.0);
  myCircuit->emplaceComponent<Resistor>(103.0);
  myCircuit->setName("Jorge");
  myCircuit->setDescription("2 resistors, 1 inductor, 1 capacitor");
  myCircuit->setFreq_calcImpedance(60);
  std::cout.precision(3);
  myCircuit->printData();
};