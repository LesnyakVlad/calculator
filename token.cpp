#include "token.h"
#include "variable.h"
#include "iostream"
#include <sstream>

using namespace std;

bool funk_mode;
Token_stream ts;

void Token_stream::putback (Token t)
{
    if (full)
        throw std::runtime_error("putback() into a full buffer");

    buffer = t;
    full = true;
}


bool in(const vector<char>& sim , char s)
{
    for (int i{0} ; i< sim.size() ; ++i)
        if(sim[i]==s)
            return true;

    return false;
}

bool in2(const vector<char>& sim2 , char s)
{
    for (int i{0} ; i< sim2.size() ; ++i)
        if(sim2[i]==s)
            return true;

    return false;
}

bool in3(const vector<char>& sim3 , char s)
{
    for (int i{0} ; i< sim3.size() ; ++i)
        if(sim3[i]==s)
            return true;

    return false;
}

Token Token_stream::get ()
{
    funk_mode=false;
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    cin.get (ch);
    if (cin.eof()) return Token{ t_kind::quit };
    if (!(in(sim, ch) || in2(sim2,ch) || in3(sim3,ch)))
        while (ch!=';') cin.get(ch);
    if ((cin.eof() || !(isalpha(ch) || isdigit(ch))) && !in(sim , ch))
        return Token{ t_kind::error };


    switch (ch)
    {
    case '\n':
        return Token{ t_kind::print };
    case 'q':
        return Token{ t_kind::quit };
    case ';':
        return Token{ t_kind::print };
    case '(':
        return Token{ t_kind::lef };
    case ')':
        return Token{ t_kind::rig };
    case '+':
        return Token{ t_kind::plus };
    case '-':
        return Token{ t_kind::mn };
    case '*':
        return Token{ t_kind::ml};
    case '/':
        return Token{ t_kind::dv };
    case '%':
        return Token{ t_kind::pr };
    case '=':
        return Token{ t_kind::eq };
    case '^':
        return Token{ t_kind::pw };
    case '!':
        return Token{ t_kind::fac };

    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);
        double val;
        cin >> val;
        return Token{ t_kind::number, val };
    }

    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
                s += ch;
            cin.putback(ch);

            if (s == declkey) return Token{ t_kind::let };
            if (s == help_) return Token{ t_kind::help };
            if (s == "funk")
            {
                vector<char> funk_base;

                cin.get (ch);
                while ((ch!=';') and (ch!='\n'))
                {
                    funk_base.push_back(ch);
                    cin.get (ch);
                }
                funk_mode = true;
                return Token{ t_kind::funk , funk_base};
            }

            return Token { t_kind::name, s };
        }
        throw std::runtime_error("Bad token");
    }
}


void Token_stream::ignore (char c)//removes wrong simvols to continue work
{
    if (full && c == buffer.opr)
    {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (cin.get (ch))
        if (ch == c)
            return;
}
