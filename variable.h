#include <iostream>
#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>

using namespace std;

struct Variable
{
    string name;
    double value;

    Variable (string n, double v)
        : name{ n }, value{ v }
    { }
};

double get_value (string s);
void set_value (string s, double d);
bool is_declared (string s);
double define_name (string var, double val);

extern vector <Variable> var_table;

#endif // VARIABLE_H
