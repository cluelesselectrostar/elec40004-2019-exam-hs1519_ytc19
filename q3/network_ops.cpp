#include "network.hpp"
#include <map>

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

bool operator<(const Network &a, const Network &b) //TODO:
{ //assuming a valid input is given.

    map<char,int> weight;
    weight.insert({'&', 1});
    weight.insert({'C', 2});
    weight.insert({'L', 3});
    weight.insert({'R', 4});
    weight.insert({'|', 5});

    if (a.type == b.type) {
        if (a.value == b.value) {
            if (a.parts.size() == b.parts.size()) {

                if (a.parts.size()==0) { //b.parts.size has to be zero as well, then equal.
                    return false;
                }

                for (int i=0; i<a.parts.size(); i++) {
                    for (int j=0; j<b.parts.size(); j++) {
                        a.parts[i]<b.parts[j];
                    }   
                }

            } else {
                return a.parts.size()<b.parts.size();
            }
        } else {
            return a.value < b.value;
        }
    } else {
        return weight.find(a.type)->second < weight.find(b.type)->second;
    }

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
