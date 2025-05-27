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
  // DIMENSION PRIVATE HELPER DEFINITION
  size_t Dimension::throw0AndCast(int value_in)
  {
    if(value_in < 1) throw std::invalid_argument("Screen dimensions must be positive.");
    return static_cast<size_t>(value_in);
  }

  
  // LEFT-PRINT BUFFER DEFINITIONS
  void LeftPrintbuf::flush_buffer()                     // when overflow sees newline it calls here - formats the buffer and passes to std::cout
  {
    const string formatted_buf = formatLine(buffer);
    std::cout<<formatted_buf<<std::endl;                // makes sure std::cout actuallly prints, and then enters a newline
    buffer.clear();                                     // empty buffer for the next line
  }


  string LeftPrintbuf::formatLine(string& buffer_in)  // here is the custom formatting function - empty for left print
  {
    const size_t width = screenWidth.get();
    const size_t length = buffer_in.size();
    if(length > width) buffer_in.resize(width);         // truncates what's in the buffer to the screenWidth
      
    // we want to pad the buffer with whitespace, so that it sits centre-aligned in a row of screenWidth

    const size_t n_whitespace = static_cast<size_t> (width - length) / 2;  // when we're halfway through the length of string,
    const string whitespace = string(n_whitespace, ' ');                   // we're halfway along the width (=  w/2 - l/2)
    return whitespace + buffer_in; 
  }


  int LeftPrintbuf::overflow(int c)                     // here we override the built-in std::streambuf overflow 
  {
    if(c != traits_type::eof())                         // I think this means if end of file or error is not being signalled, we handle it (type::eof check was in every example)
    {
      if(c == '\n') flush_buffer();                     // if we see newline, flush the buffer to std::cout via our formatting function
      else buffer.push_back(char(c));                   // explicit char constructor because I don't know anything about .push_back()
    }
    return c;
  }

  int LeftPrintbuf::sync()                              // this overrides what std::streambuf does when it sees std::flush
  {
    flush_buffer();
    return 0;                                           // type is int so i assume it wants 0 on success
  }


  // FORMATTING OVERRIDES - classes derived from LeftPrintbuf can override formatLine() to add any line formatting option
  // CENTRE-PRINT formatter
  string CentrePrintbuf::formatLine(string& buffer_in)
  {
    const size_t width = screenWidth.get();
    const size_t length = buffer_in.size();
    if(length > width) buffer_in.resize(width);         // truncates what's in the buffer to the screenWidth
      
    // we want to pad the buffer with whitespace, so that it sits centre-aligned in a row of screenWidth

    const size_t n_whitespace = static_cast<size_t> (width - length) / 2;  // when we're halfway through the length of string,
    const string whitespace = string(n_whitespace, ' ');                   // we're halfway along the width (=  w/2 - l/2)
    return whitespace + buffer_in; 
  }
  // RIGHT-PRINT formatter
  string RightPrintbuf::formatLine(string& buffer_in)
  {
    const size_t width = screenWidth.get();
    const size_t length = buffer_in.size();
    if(length > width) buffer_in.resize(width);         // begins the same as centre...

    const size_t n_whitespace = static_cast<size_t> (width - length);      // this time we pad to the full width
    const string whitespace = string(n_whitespace, ' ');
    return whitespace + buffer_in; 
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


  void printFullRow(const string& pad, const string& first)
  {
    const size_t width = screenWidth.get();
    const size_t firstlength = first.size();
    const size_t padlength = pad.size();

    // number of repeats needed is (screenWidth-firstlength)/paddingLength - integer
    // division is floor but we want to overshoot the number of characters: ceiling division formula
    const size_t n_repeats = static_cast<size_t>((width - firstlength + padlength - 1) / padlength);

    string padding{""};                                                // declare padding string
    for(size_t i{0}; i < n_repeats; ++i)                               // loop adding pad to padding
    {
      padding += pad;
    };
    string result{first + padding};
    result.resize(width);                                              // truncate to exact size
    std::cout<<result<<std::flush;
  };
}