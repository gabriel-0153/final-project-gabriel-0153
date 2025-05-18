 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 06/05/25

// Interface for the class "Circuit"
// Prototypes are implemented in "Circuit.cpp"

// Circuit is derived from "Component.h"

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include"Component.h"
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
    template <class c_type> void emplaceComponent(const double value);
    // Overload to allow push_back of already wrapped components
    void emplaceComponent(const std::shared_ptr<Component> comp_in);
    // NOTE: users should wrap emplaceComponent() in a try block:- both overloads may throw std::invalid_argument
    
    // Virtuals - base class hooks overridden by derived classes: SeriesCircuit and ParallelCircuit 
    virtual std::string isSeries_or_Parallel() = 0;
    // overridden to return circuit type as a string
    virtual complex<double> combineImpedance(const complex<double> impedance_1, const complex<double> impedance_2) = 0;
    // overridden to implement series/parallel Impedance formula

    // Overrides
    void const printData(); // prints circuit info header, then iterates through components, calling itself
    complex<double> setFreq_calcImpedance(const double freq_in_Hz); // sets frequency, then iterates components, calling itself
};


#endif