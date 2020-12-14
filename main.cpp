#include "variable.h"
#include "grammar.h"
#include "iostream"


extern Token_stream ts;

int main ()
try
{
//    Token_stream ts;
    define_name ("pi", 3.141592653589793);
    define_name ("e",  2.718281828459045);
    calculate(ts);
}
catch (exception& e)
{
    cerr << "exception: " << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Oops, unknown exception" << endl;
    return 1;
}
