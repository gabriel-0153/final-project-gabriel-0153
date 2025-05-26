 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Module of terminal printing functions - used by Screen classes to produce the terminal user interface
// Using ANSI escape codes - should be supported by modern windows/mac terminals

// Every print function ultimately passes std::endl, flushing the output buffer and inserting newline

// Current screen dimensions are held by a class ***, so that setters can prevent dimensions
// being 0 and size_t can be used internally with dedicated casting from external ints
// Encapsulation was chosen (over struct e.g.) because TUI:: functions really don't work with these errors, so should be internally protected

// "TUI.h" contains the module interface
// Function implementations are found in "TUI.cpp" 

#ifndef TUI_H
#define TUI_H

#include<string>

using std::string;

namespace TUI
{
  // Screen Size config
  class Dimension                              // ***Encapsulated dimension values
  {
    private:
      size_t value;                            // width or height
      size_t throw0AndCast(int value_in);      // throws an exception when value_in < 1, then returns a static_cast to size_t
    
    public:
      Dimension(const int value_in) : value{throw0AndCast(value_in)} {}; // constructor
      void set(const int value_in)  {value = throw0AndCast(value_in);};  // setter
      size_t const get() {return value;};                                // getter
  };

  inline Dimension screenWidth{110}; // set by user at program start - lowball defaults
  inline Dimension screenHeight{30}; // inline keeps these as single-instance (without declaring them externally)

  
  // Terminal Output
  static const size_t one{static_cast<size_t>(1)};
  // defined size_t 1 for convenience, const so doesn't need external linkage, 
  // but scope should be program lifetime (tied to publicly-used functions), so static

  void clear(const size_t row=one, const size_t column=one);      // clear text and move cursor to (row;column) - defaulting to (1;1)

  void moveCursor(const size_t row=one, const size_t column=one); // move cursor to (row; column)

  void centredPrint(const string& string_in);                     // truncates long input strings to screenWidth

  void printFullRow(const string& string_in);                     // repeatedly print a string to row(row) until screenWidth is reached
};

#endif