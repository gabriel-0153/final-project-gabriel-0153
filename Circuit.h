 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 06/05/25

// Interface for the class "Circuit"
// Prototypes are implemented in "Circuit.cpp"

// Circuit is derived from "Component.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include"Component.h"
#include"Resistor.h"
#include"Capacitor.h"
#include"Inductor.h"
#include<string>
#include<memory>
#include<complex>
#include<vector>

using std::complex;

class Circuit : public Component
{
  protected:
    // MEMBER DATA:
    std::vector<std::shared_ptr<Component>> components;
    std::string name;
    std::string description;

  public:
    // Constructor/Destructor
    Circuit() = default;  // Components are only to be added after instantiation, calls empty vector constructor- no dangling pointers
    ~Circuit() = default; // automatic memory handling- shared_ptr correctly releases memory/bumps ref_count when default destructor is called

    // Name/description setters
    void setName(const std::string name_in);
    void setDescription(const std::string desc_in);

    // Setter for components - handles shared_ptr creation behind interface - user passes Component class and constructor argument
    // template function signature is (double), as all 3 leaves (Resistor/Capacitor/Inductor) take 1 double as constructor argument
    template <class c_type> void emplaceComponent(const double comp_parameter)
    {
      if (!(typeid(c_type) == typeid(Resistor) || typeid(c_type) == typeid(Capacitor) || typeid(c_type) == typeid(Inductor)))
      // virtual base means typeid will look to derived class typename
      {
        throw std::invalid_argument("must construct a leaf class (Resistor/Capacitor/Inductor) derived from Component");
      } // custom exception supercedes an exception if c_type lacks a constructor of this signature, or unintended behaviour if it does
      components.push_back(std::make_shared<c_type>(comp_parameter));
    };
    // Overload to allow push_back of already wrapped components - signature is (std::shared_ptr<>) so no ambiguity
    void emplaceComponent(const std::shared_ptr<Component> comp_in);
    // NOTE: users should wrap emplaceComponent() in a try block:- both overloads may throw std::invalid_argument
    
    // Virtuals - base class hooks overridden by derived classes: SeriesCircuit and ParallelCircuit 
    inline virtual std::string isSeries_or_Parallel() = 0;
    // overridden to return circuit type as a string
    inline virtual complex<double> combineImpedance(const complex<double> impedance_1, const complex<double> impedance_2) = 0;
    // overridden to implement series/parallel Impedance formula

    // Overrides
    void const printData(); // prints circuit info header, then iterates through components, calling itself
    complex<double> setFreq_calcImpedance(const double freq_in_Hz); // sets frequency, then iterates components, calling itself
};


#endif