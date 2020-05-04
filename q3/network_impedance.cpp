#include "network.hpp"

complex<float> impedance(const Network &c, float omega)
{
    if(c.type == 'R'){
      return {c.value, 0};

    }else if(c.type == 'C'){
      return {0, -1/(omega*c.value) };

    }else if(c.type == 'L'){
      return {0, omega*c.value};
    }else if(c.type == '&'){
      complex<float> tmp = {0, 0};
      for(int i=0; i<c.parts.size(); i=i+1){
        complex<float> imp = impedance(c.parts[i], omega);
        tmp = tmp + imp;
        //cerr << "The value of imp is: " << i << imp << endl;
      }
      return tmp;
    }else if(c.type == '|'){
      complex<float> tmp = {0, 0};
      complex<float> one = {1, 0};
      for(int i=0; i<c.parts.size(); i++){
        if(i==0){
          tmp = impedance(c.parts[i], omega);
        }else{
          tmp = one/((one/tmp) + (one/impedance(c.parts[i], omega)));
        }
      }
      return tmp;
    }
}

vector<complex<float>> transfer_function(const Network &v1, const Network &v2, const vector<float> &omega)
{
    vector<complex<float>> res;

    // TODO:

    return res;
}

vector<float> make_log10_space(float xLo, float xHi, int points)
{
    vector<float> res;

    // TODO:

    return res;
}
