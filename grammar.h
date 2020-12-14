#ifndef GRAMMAR_H
#include "token.h"
#include "variable.h"
#define GRAMMAR_H


double expression (Token_stream& ts);

double fact(int x);

double primary (Token_stream& ts);

double subterm_for_fact(Token_stream& ts);

double subterm_for_power(Token_stream& ts);

double term(Token_stream& ts);

double expression (Token_stream& ts);

double declaration (Token_stream& ts);

double statement (Token_stream& ts);

void clean_up_mess (Token_stream& ts);

void calculate (Token_stream& ts);

#endif // GRAMMAR_H
