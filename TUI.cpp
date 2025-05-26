 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Implementation of terminal output functions declared in "TUI.h" 

#include"TUI.h"
#include<iostream>
#include<iomanip>
#include<stdexcept>
#include<string>

using std::string;

namespace TUI
{

  size_t Dimension::throw0AndCast(int value_in) // Dimension class private helper
  {
    if(value_in < 1) throw std::invalid_argument("Screen dimensions must be positive.");
    return static_cast<size_t>(value_in);
  }


  // Terminal Output

  void clear(const size_t row, const size_t column)
  {                                                                    // std::flush empties the output buffer to the screen
    std::cout<<std::flush<<"\033[2J\033["<<row<<";"<<column<<"H";      // "\033" is a C-style escape sequence, then "2J"
  };                                                                   // clears the screen and  ["row";"column"H  moves the cursor


  void moveCursor(const size_t row, const size_t column)
  {
    std::cout<<"\033["<<row<<";"<<column<<"H";
  };

  
  void centredPrint(const string& string_in)
  {
    string string_in_local = string_in;           // .resizing an lvalue local copy lets centredPrint() expect const (so it can take const rvalues)
    const size_t width = screenWidth.get();
    const size_t length = string_in_local.size();
    string_in_local.resize(width);                // .resize() is truncating string_in, so it doesn't spillover into the next line

    size_t n = static_cast<size_t>((width / 2) + (length / 2)); 
//  size_t m = static_cast<size_t>((width / 2) - (length / 2)); 

//  std::cout<<"\033["<<row<<";"<<m<<"H"<<string_in<<std::endl // is **potentially** easier if escape codes are working on uni computers

    std::cout<<std::setw(n)          // setw(n) packs empty characters to the left of the next packet until its length is n
             <<string_in_local<<std::endl; // the formula means that each end of the string is half its length away from the middle of the screen
  };


  void printFullRow(const string& string_in)
  {
    const size_t width = screenWidth.get();
    const size_t length = string_in.size();

    // number of repeats needed is screenWidth/stringLength - int division is floor but we want to overshoot the number of characters:
    const size_t n_repeats = static_cast<size_t>((width + length - 1) / length);                           // ceiling division formula

    string result{""};                    // declare result string
    for(size_t i{0}; i < n_repeats; ++i)
    {
      result += string_in;                // repeatedly add string_in to result
    };
    result.resize(width);                 // truncate to exact size
    
    std::cout<<result<<std::endl;
  };
};