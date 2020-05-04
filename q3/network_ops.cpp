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

    if( is_primitive(a) && is_primitive(b) ) { //CASE 1: both primitives
        if (a.type != b.type) { // if different type, C<L<R
          return weight.find(a.type)->second < weight.find(b.type)->second;
        } else { //if same type, compare value.
          return a.value < b.value;
        }
    }else if(a.type == '&' && is_primitive(b)){ // CASE 2a: b must be larger than a
      return true;
    }else if(b.type == '&' && is_primitive(a)){ // CASE 2b: a must be larger than b
      return false;
    }else if(a.type == '|' && is_primitive(b)){
      return false;
    }else if(b.type == '|' && is_primitive(a)){
      return true;
    }else if(a.type == '&' && b.type == '|'){
      return true;
    }else if(b.type == '&' && a.type == '|'){
      return false;
    }else if(a.type == '&' && b.type == '&'){
      if(a.parts.size() > b.parts.size()){
        for(int i=0; i<b.parts.size(); i++){
          if(a.parts[i] < b.parts[i]){
            return true;
          }
        }
        return false;
      }else if(a.parts.size() <= b.parts.size()){
        for(int i=0; i<a.parts.size(); i++){
          if(a.parts[i] < b.parts[i]){
            return true;
          }
        }
        return false;
      }
    }else if(a.type == '|' && b.type == '|'){
      if(a.parts.size() > b.parts.size()){
        for(int i=0; i<b.parts.size(); i++){
          if(a.parts[i] < b.parts[i]){
            return true;
          }
        }
        return false;
      }else if(a.parts.size() <= b.parts.size()){
        for(int i=0; i<a.parts.size(); i++){
          if(a.parts[i] < b.parts[i]){
            return true;
          }
        }
        return false;
      }
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

void flatten(char type, const vector<Network> &parts)
{

    /*for (int i=0; i< parts.size(); i++) {
       if (type == parts[i].type) {
           flatten(type, parts[i].parts, res);
       } else {
           //if not the same type (e.g. type is parallel but part is series, or vice versa)
           //or if its a primitive.
           res.push_back(parts[i]);
       }

   }*/
}

bool is_sorted(vector<Network> a)
{
    for(int i=0; i<a.size()-1; i++){
      if(!(a[i]<a[i+1])){
        return false;
      }
    }
    return true;
}

vector<Network> sort_terms(vector<Network> parts)
{
  if(is_sorted(parts)){
    return parts;
  }else{
    Network tmp;
    for(int i=0; i<parts.size()-1; i++){
      if(!(parts[i] < parts[i+1])){
        tmp = parts[i+1];
        parts[i+1] = parts[i];
        parts[i] = tmp;
      }
    }
    return sort_terms(parts);
  }
}


Network canonicalise(const Network &x) //TODO:
{
    /*if (is_primitive(x)) {
        return x;
    }

    vector<Network> parts = x.parts;

    for (int i=0; i<x.parts.size(); i++) {
        parts[i]= canonicalise(parts[i]);
    }

    parts = flatten(x.type, parts, );
    parts = sort_terms(parts);

    Network y;
    y.type = x.type;
    y.parts = parts;

    return y;*/
}
