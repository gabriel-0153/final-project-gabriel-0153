 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Interface for the class "Component"

// Component is an abstract base class, providing the frequency (double) and impedance (complex) member data common to all Components.
// It also contains pure virtual functions printData() and calcImpedance(), that can be called recursively on nested Component objects.

// Resistor, Inductor and Capacitor derive directly, adding a data member for resistance/inductance/capacitance, then overridding
// calcImpedance() with the relevant formula and printData() with a std::cout statement. Recursive calls terminate at these leaves.

// SeriesCircuit and ParallelCircuit derive through a template, they contain a vector of base class pointers (of Component type), with
// calcImpedance() overridden to iterate through the vector and combine impedances with the relevant formula. Recursive calls
// propagate to children of these composites.

#ifndef COMPONENT_H
#define COMPONENT_H

#include<complex>

using std::complex;

class Component
{
  protected:
    // Pi constant defined for all instances of component, constexpr is implicitly inline (C++ 17 onwards)
    static constexpr double pi{3.1415926535};
    static constexpr complex<double> i{0.0 ,1.0};
    // COMMON MEMBER DATA:
    double frequency{0};       // measured in rad/s
    complex<double> impedance; // magnitude measured in Ohms, phase in rad

  public:
    // Constructor/Destructor
    Component() = default;          // Only the default Constructor is required: frequency is only ever set after instantiation  
    virtual ~Component() = default; // default Destructor: no memory management here, virtual Destructor called after derived Destructors

    // Copy/Move
    Component(const Component&) = default;            // memory management is handled by smart-pointers, and shallow copy behaviour is
    Component& operator=(const Component&) = default; // desired in the case that a Circuit object holds a shared_ptr to another Circuit is
    Component(Component&&) noexcept = default;        // copy constructed (so that editing the original can modify circuits containing it)
    // also, std::complex<> is always deep-copied - avoids potential for editing R/C/L values on one circuit propagating to copies

    // Pure Virtual functions - shared by all derived classes and overridden to return data at leaves, and propagate to children at composites 
    virtual void const printData() = 0;
    virtual complex<double> setFreq_calcImpedance(const double freq_in_Hz) = 0;

    // Public Setters/Getters
    void setFrequency(const double freq_in_Hz) {frequency = 2*pi*freq_in_Hz;}; // formulae naturally use rad/s, allow entry in Hz
    double getFreq_in_rad() const {return frequency;};
    double getFreq_in_Hz() const {return frequency / (2*pi);};

    complex<double> getImpedance() const {return impedance;}; 
};
#endif