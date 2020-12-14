#include "variable.h"
#include "grammar.h"
#include "iostream"
#include "vector"
#include "token.h"
#include <sstream>

vector <Variable> var_table;

double get_value (string s)
{
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    throw std::runtime_error ("get: undefined name  " + s);
}


void set_value (string s, double d)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == s)
        {
            var_table[i].value = d;
            return;
        }
    }

    throw std::runtime_error("get: undefined name  " + s);
}


bool is_declared (string s )
{
    for (int i = 0; i < var_table.size(); ++i)      //error
        if (var_table[i].name == s) return true;
    return false;
}



