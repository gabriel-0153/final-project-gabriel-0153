 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

#include<complex>
#include<iostream>
#include<memory>
#include<iomanip>
#include"TUI.h"
#include"Component.h"
#include"Resistor.h"
#include"Capacitor.h"
#include"Inductor.h"
#include"Circuit.h"
#include"SeriesCircuit.h"
#include"ParallelCircuit.h"

#include <chrono>
#include <thread>

using std::complex;

main() // testing
{
  TUI::screenWidth.set(150); TUI::screenHeight.set(40);

  std::shared_ptr<Circuit> Circuit1 = std::make_shared<ParallelCircuit>();
  std::shared_ptr<Circuit> Circuit2 = std::make_shared<SeriesCircuit>();

  Circuit2->emplaceComponent<Capacitor>(301);
  Circuit2->emplaceComponent<Capacitor>(0.002);

  Circuit1->emplaceComponent(Circuit2);
  Circuit1->emplaceComponent<Capacitor>(201.0);
  Circuit1->emplaceComponent<Capacitor>(33.0);
  Circuit1->emplaceComponent<Capacitor>(1.77);
  Circuit1->emplaceComponent<Capacitor>(103.0);
  Circuit1->setName("Jorge");
  Circuit1->setDescription("1 series, 4 capacitors");


  Circuit1->setFreq_calcImpedance(60);

  TUI::clear();
  Circuit1->printData();
  TUI::printFullRow("|_|");
  // std::this_thread::sleep_for(std::chrono::seconds(20));
  // TUI::clear();
};    