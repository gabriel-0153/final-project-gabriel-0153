 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Implementation for the class "Circuit"
// Interface is in "Circuit.h"

// Circuit is derived from "Component.h"

#include"Component.h"
#include"Resistor.h"
#include"Capacitor.h"
#include"Inductor.h"
#include"Circuit.h"
#include<iostream>
#include<memory>
#include<complex>
#include<vector>

using std::complex;

// Name/description setters
void Circuit::setName(const std::string name_in)
{
  if(name_in.size() > 10) throw std::out_of_range("character limit (10) exceeded"); // try-catch logic used to reprompt end user
  name = name_in;
};

void Circuit::setDescription(const std::string desc_in)
{
  if(desc_in.size() > 20) throw std::out_of_range("character limit (20) exceeded"); // try-catch logic used to reprompt end user
  description = desc_in;
};

// Setter for components
// first setter is a template that takes a basic leaf class and constructs it within a shared_ptr 
// function signature is (double), as all 3 leaves (Resistor/Capacitor/Inductor) take 1 double as constructor argument
template <class c_type> void Circuit::emplaceComponent(const double comp_parameter)
{
  if (!(typeid(c_type) == typeid(Resistor) || typeid(c_type) == typeid(Capacitor) || typeid(c_type) == typeid(Inductor)))
  // virtual base means typeid will look to derived class typename
  {
    throw std::invalid_argument("must construct a leaf class (Resistor/Capacitor/Inductor) derived from Component");
  } // custom exception supercedes an exception if c_type lacks a constructor of this signature, or unintended behaviour if it does
  components.push_back(std::make_shared<c_type>(comp_parameter));
};

// second setter overloads emplaceComponent to take a shared_ptr and directly add it to the components vector, bumping ref_count
// function signature is (shared_ptr<Component>) so no ambiguity
void Circuit::emplaceComponent(const std::shared_ptr<Component> comp_in) // const is ok:-ref_count bump is during copy construction (before function block)
{
  if(comp_in == nullptr) throw std::invalid_argument("passed null_pointer - emplace is disallowed");
  components.push_back(comp_in);
};

// This function factors out the vector iteration logic for SeriesCircuit and ParallelCircuit into a common inherited function
// it combines the impedances via combine(), VIRTUALLY DECLARED IN CIRCUIT
complex<double> Circuit::setFreq_calcImpedance(const double freq_in_Hz)
{
  frequency = 2*pi*freq_in_Hz;
  if(components.empty()) return {0.0, 0.0}; // empty vector escape (otherwise division by 0 errors)
  // set total variable to first impedance explicitly - (trying) to avoid other possible empty vector edge cases
  complex<double> z_total = components[0]->setFreq_calcImpedance(freq_in_Hz); // recursive call sub-objects()
  for(size_t i{1}; i<components.size(); i++)
  {
    z_total = combineImpedance(z_total, components[i]->setFreq_calcImpedance(freq_in_Hz)); // overridden by derived classes to implement series/parallel behaviour
  };
  impedance = z_total;
  return impedance;
};

// printData() override 
void const Circuit::printData()
{
  if(components.empty()) // not strictly necessary - setFreq_calcImpedance() should be called first and will catch this issue
  {
    std::cout<<"Trying to display null circuit - something went wrong!"<<std::endl;
    return;
  }
  // print circuit header information
  std::cout<<"Name: "<<name<<" | "<<description<<"\n"
           <<isSeries_or_Parallel()<<" circuit | AC Frequency = "<<frequency/(2*pi)<<" Hz |/n"
           <<"Calculated Impedance:  Magnitude = "<<abs(impedance)<<" Ohms | Phase = "<<arg(impedance)<<" rad/n"
           <<"This circuit contains "<<components.size()<<" components:"<<std::endl;
  // then call printData() on each component
    for(size_t i{0}; i<components.size(); i++)
  {
    std::cout<<"Component "<<i<<"./n"<<"----------------------------------------"<<std::endl;
    components[i]->printData();
    std::cout<<"----------------------------------------"<<std::endl;
  }
};