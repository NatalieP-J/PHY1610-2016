// hw.cc - prints ’Hello world.’
#include <iostream> // to define input/output routines 
int main() // called first
{ // braces delimit a code block
   std::string message = "Hello world."; // a variable
   std::cout << message    // print to console out
             << std::endl; // end of line
   // semicolon after statement
return 0;
   // return value to shell
}