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
        int q=1;
        int r=0;
        int value;
        int c = ceil(log2(m));
        int sign = encodedVal[encodedVal.size()-1];
        encodedVal.pop_back();
        while(encodedVal[encodedVal.size()-1]!=0){
            encodedVal.pop_back();
            q++;
        }
        if(encodedVal.size()==1){
            r= encodedVal[0]*pow(2,0);
        }
        else{
            for(int i=c-1; i>=c;i--){
                r+= encodedVal[encodedVal.size()-1]*pow(2,i);
            }
        }
        if(r<pow(2,c)-1){
            if(sign==0){
                return m*q +r;
            }
            return (-m*q +r);
        }
        else{
            for(int i=0; i<encodedVal.size()-1;i++){
                r+= encodedVal[i]*pow(2,i);
            }
            value= m*q +r-(pow(2,c)-m);
            if(sign==0){
                value= m*q +r;
            }
            else{
                value= (-m*q +r);
            }
            
        }
        cout<<value<<endl;
        return value;
    }
};