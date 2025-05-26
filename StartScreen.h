 // PHYS30762 Programming in C++ - Final Project
// ID: 10897528
// Last edited: 19/05/25

// Interface for the class "StartScreen"

// 
// 
// 

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include<iostream>
#include<string>

using std::string;

class StartScreen
{
  protected:
    // MEMBER DATA - std::strings containing text to print to screen (terminal)
    const string clearScreen{"\033[2J\033[H"};   // Using ANSI escape sequences
    const string border{"================================================================================"};
    const string title{"                       Impedance Calculator - AC Circuits                       "};

  
  
  public:

};

#endif