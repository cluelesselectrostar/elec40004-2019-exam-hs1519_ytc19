#include "network.hpp"

Network R(float v)
{
    return {'R', v, {} };
}

Network C(float v)
{
    return {'C', v, {} };
}

Network L(float v)
{
    return {'L', v, {} };
}


bool operator==(const Network &a, const Network &b)
{
    if(a.type != b.type) return false;
    if(a.value != b.value) return false;
    return a.parts == b.parts;
}

Network operator|(const Network &a, const Network &b)
{
    return Network{'|', 0, {a,b} };
}

Network operator&(const Network &a, const Network &b)
{
    return Network{'&', 0, {a,b} };
}

bool is_primitive(const Network &a) //TODO: 
{
    if (a.type != 'R' || a.type !='L' || a.type != 'C') {
        return false;
    }

    if (a.value < 0 || a.value == 0) { //non primitive networks have value of 0.
        return false;
    }

    if (!a.parts.empty()) {
        return false;
    }

    return true; //Only return true for resistors, capacitors or inductors with positive values.
}

bool is_composite(const Network &a)
{
    return !is_primitive(a);
}


Network canonicalise(const Network &x) //TODO:
{
    exit(1);
}

istream &operator>>(istream &src, Network &c) 
{
    while (cin) {
        
    }
}
