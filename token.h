#ifndef TOKEN_H
#define TOKEN_H
#include "iostream"
#include "vector"

using namespace std;


enum class t_kind
{
    number,
    name,
    let,
    error,
    help,
    funk,
    quit,
    print,
    eq,
    plus,
    mn,
    ml,
    dv,
    pw,
    pr,
    fac,
    lef,
    rig,
};


struct Token
{
    t_kind kind;
    double value;
    char opr;
    string name;
    vector<char> base;

    Token (t_kind ch)
        : kind{ ch }, value{ 0 }
    { }

    Token (t_kind ch, double val)
        : kind{ ch }, value{ val }
    { }
    Token (t_kind ch, string n)
        : kind{ ch }, name{ n }
    { }
    Token (char opr)
        : opr{ opr }, value{ 0 }
    { }
    Token (t_kind ch , vector<char> funk_base)
        : kind { ch } , base{ funk_base }
    { }
};


class Token_stream
{
    bool full{ false };
    Token buffer{ '\0' };

public:
    Token_stream () { }

    Token get ();
    void putback (Token t);

    void ignore (char);
};

const vector<char> sim{';','.','+','-','*','/','^','%','!','(',')','\n'};
const vector <char> sim2{'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g',
                         'h','j','k','l','z','x','c','v','b','n','m'};
const vector <char> sim3{'1','2','3','4','5','6','7','8','9','0'};

constexpr char quit = 'q';
constexpr char print = ';';

const string help_ = "help";
const string prompt = "> ";
const string result = "= ";
const string declkey = "let";

#endif //TOKEN_H
