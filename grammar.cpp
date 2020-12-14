#include "grammar.h"
#include "token.h"
#include "variable.h"
#include <sstream>

#include "../Graph_lib/Simple_window.h"
#include "../Graph_lib/Graph.h"

using namespace Graph_lib;

extern bool funk_mode;

double expression (Token_stream& ts);


void help__()
{
    cout << endl << "calculator got +, -, *, %, ^, !, / ,() operations" << endl
         <<"every expretion must have an ';' at ones end.  " <<endl<<endl;
}


double fact(int x)
{
    if (x == 0)
        return 1;
    else if (x < 0)
        error("negative under factorial");
    else
        return x * fact(x - 1);

    return 0;
}


double primary (Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind)
    {
    case t_kind::lef:
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != t_kind::rig)
            error("')' expected");
        return d;
    }

    case t_kind::mn:
    {
        Token n = ts.get();
        if ((n.kind == t_kind::mn) || (n.kind == t_kind::plus))
            error("unknown operation");
        ts.putback(n);
        return -primary(ts);
    }
    case t_kind::plus:
    {
        Token n = ts.get();
        if ((n.kind ==t_kind::mn) || (n.kind == t_kind::plus))
            error("unknown operation");
        ts.putback(n);
        return primary(ts);
    }
    case t_kind::number:
        return t.value;

    case t_kind::name:
        return get_value(t.name);
    default:
        error("primary expected\n>");
    }
}

double define_name (string var, double val)
{
    if (is_declared(var))
        throw std::runtime_error(var + " declared twice");

    var_table.push_back (Variable{ var, val });

    return val;
}

double subterm_for_fact(Token_stream& ts)
{
    double result = primary(ts);

    while (true)
    {
        Token t = ts.get();
        switch (t.kind)
        {
        case t_kind::fac:
        {
            Token n = ts.get();
            if (n.kind==t_kind::fac)
            {
                error("double factorial");
                ts.putback(n);
            }
            ts.putback(n);
            result = fact(result);
            break;
        }
        default:
            ts.putback(t);
            return result;
        }
    }
}


double subterm_for_power(Token_stream& ts)
{

    double result = subterm_for_fact(ts);

    while (true)
    {
        Token t = ts.get();
        switch (t.kind)
        {
        case t_kind::pw:
            if (result < 0)
                error("invalid power base");

            result = pow(result, subterm_for_fact(ts));
            break;
        default:
            ts.putback(t);
            return result;
        }
    }
}


double term(Token_stream& ts)
{
    double result = subterm_for_power(ts);;

    while (true)
    {
        Token t = ts.get();
        switch (t.kind)
        {
        case t_kind::ml:
            result *= subterm_for_power(ts);
            break;
        case t_kind::dv:
        {
            double operand = subterm_for_power(ts);

            if (operand == 0)
            {
                error("divide by zero");
            }

            result /= operand;

            break;
        }
        case t_kind::pr:
        {
            int res1 = result;
            int res2 = subterm_for_power(ts);
            result = res1 % res2;

            double right = subterm_for_power(ts);

            if (right == 0)
            {
                error("%: divide by zero");
            }

            result = fmod(result, right);
            break;
        }

        default: ts.putback(t); return result;
        }
    }
}


double expression (Token_stream& ts)
{
    double result = term(ts);
    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case t_kind::plus:
            result += term(ts);
            break;

        case t_kind::mn:
            result -= term(ts);
            break;

        default:
            ts.putback(t);
            return result;
        }
    }
}


double declaration (Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind != t_kind::name)
        error("name expected in declaration");

    string var = t.name;
    if (is_declared(var))
        error(var, " declared twice");

    t = ts.get();
    if (t.kind != t_kind::eq)
        error("'=' missing in declaration of ", var);

    return define_name (var, expression(ts));
}

double statement (Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind)
    {
    case t_kind::let:
        return declaration(ts);
        //    case funk:
        //        ts.putback(t);
        //        print_funk(ts);
        return 0;
    default:
        ts.putback(t);
        return expression(ts);
    }
}


void clean_up_mess (Token_stream& ts)
{
    ts.ignore (print);
}


void calculate (Token_stream& ts)
{
    while (cin || funk_mode)
    {
        try
        {
            cout << '\r' << prompt;
            Token t = ts.get();

            switch (t.kind)
            {
            case t_kind::error:
                error("Bad Input");
                break;
            case t_kind::help:
                help__();
                // fallthrough
            case t_kind::print:
                continue;
            case t_kind::quit:
                return;
            }

            ts.putback(t);

            if (!funk_mode)
            {
                double x = statement(ts);
                cout << '\r' << result << x << endl;
            }
        }
        catch (runtime_error& e)
        {
            cerr << e.what() << endl;
            clean_up_mess(ts);
        }
    }
}

