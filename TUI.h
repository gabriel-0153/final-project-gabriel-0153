 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 18/05/25

// Module of terminal printing functions - used by Screen classes to produce the terminal user interface
// Using ANSI escape codes - should be supported by modern windows/mac terminals

// Every print function ultimately passes std::endl, flushing the output buffer and inserting newline

// For external use, having to format lines first and pass concatonated strings is inefficient, and not very encapsulated
// so based on these articles: "https://stackoverflow.com/questions/22042414/c-stream-insert-string-after-newline",
// "https://stackoverflow.com/questions/25019067/overridden-stdostream-flush-function-not-called-by-stdflush"
// and the example given in a gcc reference page: "https://gcc.gnu.org/onlinedocs/libstdc%2B%2B/manual/streambufs.html"
// I derived a custom stream buffer that waits for a newline or std::flush, then inserts a formatting routine and sends the line to cout
// I wrapped this in an ostream that sinks to the buffer, so it can be used in place of std::cout 

// Current screen dimensions are held by a class, so that setters can prevent dimensions
// being 0 and size_t can be used internally with dedicated casting from external ints
// Encapsulation was chosen (over struct e.g.) because TUI:: functions really don't work with these errors, so should be internally protected

// "TUI.h" contains the module interface
// Function implementations are found in "TUI.cpp" 

#ifndef TUI_H
#define TUI_H

#include<string>
#include<ostream>
#include<streambuf>

using std::string;
// using std::streambuf;

namespace TUI
{
  // SCREEN SIZE CONFIG
  class Dimension                                   // Encapsulated dimension values
  {
    private:
      size_t value;                                 // width or height
      size_t throw0AndCast(int value_in);           // throws an exception when value_in < 1, then returns a static_cast to size_t
    
    public:
      Dimension(const int value_in) : value{throw0AndCast(value_in)} {}; // constructor
      void set(const int value_in)  {value = throw0AndCast(value_in);};  // setter
      size_t const get() {return value;};                                // getter
  }; // end of Dimension class

  inline Dimension screenWidth{110}; // set by user at program start - lowball defaults
  inline Dimension screenHeight{30}; // inline keeps these as single-instance (without declaring them externally)


  // CUSTOM OSTREAM - to print left-, centre-, and right- aligned strings
  // buffer:
  class LeftPrintbuf : public std::streambuf        // the buffer is designed here, with an empty format function -
  {                                                 // then derived classes override the formatting
    private:
      string buffer{""};                            // declare a simple buffer to hold 1 line at a time

      // without setting up the normal buffer in streambuf classes through the provided setp(),
      // each char goes to overflow instead and we can send it to our buffer from there

      void flush_buffer();                          // when overflow sees newline it calls here - formats the buffer and passes to std::cout

    protected:                                      // in theory... derived classes from this one could need access to sync() and overflow()
      virtual string formatLine(string& buffer_in); // here is the custom formatting function
      virtual int overflow(int c) override;         // here we override the built-in overflow to route to *our* buffer, or *our* flush on newline
      virtual int sync() override;                  // this overrides what std::streambuf does when it sees std::flush - now it calls *our* flush
  }; // end of left-print buffer class

  class CentrePrintbuf : public LeftPrintbuf
  {
    protected:
      virtual string formatLine(string& buffer_in) override;
  };
  class RightPrintbuf : public LeftPrintbuf
  {
    protected:
      virtual string formatLine(string& buffer_in) override;
  };

  // ostream wrappers - std::ostream is completely polymorphic so we can just patch in a pointer to our custom buffer
  class LeftPrinter : public std::ostream
  {
    private:
      LeftPrintbuf lbuf;
    public:
      LeftPrinter() : std::ostream(&lbuf) {};        // pass by address - otherwise derived behaviour is sliced :(
  };
  class CentrePrinter : public std::ostream
  {
    private:
      CentrePrintbuf cbuf;
    public:
      CentrePrinter() : std::ostream(&cbuf) {};
  };
  class RightPrinter : public std::ostream
  {
    private:
      RightPrintbuf rbuf;
    public:
      RightPrinter() : std::ostream(&rbuf) {};
  };

  inline LeftPrinter LeftPrint;                     // expose a single instance of each to use publicly (I love inline)
  inline CentrePrinter CentredPrint;
  inline RightPrinter RightPrint;

  
  // Direct Terminal Output
  static const size_t one{size_t(1)};               // defined static size_t one for convenience
  void clear(const size_t row=one, const size_t column=one);       // clear text and move cursor to (row;column) - defaulting to (1;1)
  void moveCursor(const size_t row=one, const size_t column=one);  // move cursor to (row; column)
  void printFullRow(const string& pad, const string& first= "");   // repeatedly print padding to row(row), until screenWidth is reached
};

#endif