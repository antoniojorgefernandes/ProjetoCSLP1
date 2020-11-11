#include <boost/dynamic_bitset.hpp> 
#include <math.h>
using namespace std;
using namespace boost;


class GolombDecode{
    public:
    /*!
        Faz decode de um bitset codificado. 
    */
    int decode(dynamic_bitset<> encodedVal, int m){
        int q;
        int r=0;
        int value;
        int c = ceil(log2(m));
        int numberOfbits = encodedVal.size();
        for(int i=numberOfbits-1; i>=0; i--){
            if(encodedVal[i]==0){
                q=numberOfbits-(i+1);   
                break;
            }
        }
        encodedVal.resize(numberOfbits-q-1);
        if(encodedVal.size()==1){
            r= encodedVal[0]*pow(2,0);
        }
        else{
            for(int i=encodedVal.size()-1; i>encodedVal.size()-1-c;i--){
                r+= encodedVal[i]*pow(2,c-1);
                c--;
            }
        }
        if(r<pow(2,c)-1){
            return m*q +r;
        }
        else{
            for(int i=0; i<encodedVal.size()-1;i++){
                r+= encodedVal[i]*pow(2,i);
            }
            value= m*q +r-(pow(2,c)-m);
        }
        return value;
    }
};