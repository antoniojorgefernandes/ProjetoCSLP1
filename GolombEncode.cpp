#include <boost/dynamic_bitset.hpp> 
#include <math.h>
#include <iostream>
using namespace std;
using namespace boost;

/*!
    Implementação de codificação usando o método de Golomb 
*/

class GolombEncode{

    public:

    /*! 
        Codifica o inteiro fornecido. Para isso calcula os valores de q,r,c, converte q para unitario e r para binário e faz a concatenação q+r
    */
    dynamic_bitset<> encode(int value, int m){
        int q = value/m;
        int r = value-q*m;
        float c = ceil(log2(m));
        if(r<(pow(2,c)-1)){
            if(c-1<1){
                c=1;
            }
            else{
                c=c-1;
            }
        }
        else{
            r= r+(pow(2,c)-m);
        }
        dynamic_bitset<> codedValue(c,r);
        dynamic_bitset<> qToUnit = toUnit(q);
        for(int i=0; i<q+1;i++){
            codedValue.push_back(qToUnit[i]);
        }
        return codedValue;
    }
    /*!
        Converte o numero inteiro para unitário no formato n 1's e 0 como terminador
    */
    dynamic_bitset<> toUnit(int q){
        dynamic_bitset<> qUnit(q+1);
        qUnit.set(0);
        qUnit.flip();
        return qUnit;
    }
};