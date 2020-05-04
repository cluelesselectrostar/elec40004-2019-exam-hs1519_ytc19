#include "network.hpp"
#include <map>
#include <algorithm> 

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

bool net_vec_compare(const Network &a, const Network &b) { //parameter for sorting networks (not sure if works for |/&)
    map<char,int> weight;
    weight.insert({'&', 1});
    weight.insert({'C', 2});
    weight.insert({'L', 3});
    weight.insert({'R', 4});
    weight.insert({'|', 5});

    int i=-1;
    if (a.type != b.type) { // if different type, C<L<R
        return weight.find(a.type)->second < weight.find(b.type)->second;
    } else { //if same type, compare value.

        if ((a.type == b.type) && (a.value == 0 && b.value ==0)) { //both series or both parallel
            i++;
            net_vec_compare(a.parts[i], b.parts[i]);
        }

        return a.value < b.value;
    }
}

bool operator<(const Network &a, const Network &b) //TODO:
{ //assuming a valid input is given.
    map<char,int> weight;
    weight.insert({'&', 1});
    weight.insert({'C', 2});
    weight.insert({'L', 3});
    weight.insert({'R', 4});
    weight.insert({'|', 5});

    if ( is_primitive(a) && is_primitive(b) ) { //CASE 1: both primitives
        if (a.type != b.type) { // if different type, C<L<R
            return weight.find(a.type)->second < weight.find(b.type)->second;
        } else { //if same type, compare value.
            return a.value < b.value;
        }
    } else if (b.type == '|' && a.type != '|') { // CASE 2a: b must be larger than a
        return true;
    } else if (a.type == '|' && b.type != '|') { // CASE 2b: a must be larger than b
        return false;
    }else { //CASE 3: both are parallel or both are series. assume everything inside is primitive.

        vector<Network> a_parts = a.parts;
        vector<Network> b_parts = b.parts;

        sort(a_parts.begin(), a_parts.end(), net_vec_compare);
        sort(b_parts.begin(), b_parts.end(), net_vec_compare);

        return (a.parts[0] < b.parts[0]);
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
    if (a.type != 'R' && a.type !='L' && a.type != 'C') {
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

void flatten(char type, const vector<Network> &parts, vector<Network> res){
    
    for (int i=0; i< parts.size(); i++) {
       if (type == parts[i].type) {
           flatten(type, parts[i].parts, res);
       } else { 
           //if not the same type (e.g. type is parallel but part is series, or vice versa)
           //or if its a primitive.
           res.push_back(parts[i]); 
       }

   }
}

vector<Network> sort(vector<Network> parts) {
    vector<Network> sorted;
    sort(parts.begin(), parts.end(), net_vec_compare);
    return sorted = parts;
}


Network canonicalise(const Network &x) //TODO:
{
    if (is_primitive(x)) {
        return x;
    }

    vector<Network> parts = x.parts;

    for (int i=0; i<x.parts.size(); i++) {
        parts[i]= canonicalise(parts[i]);
    }

    vector<Network> mod;
    flatten(x.type, parts, mod);
    mod = sort(mod);

    Network y;
    y.type = x.type;
    y.parts = parts;

    return y;
}
