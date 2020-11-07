#include "BitStreamW.cpp"
#include "BitStreamR.cpp"
#include <boost/dynamic_bitset.hpp> 
#include <math.h>
using namespace std;
using namespace boost;

/*!
    Implementação de codificação usando o método de Golomb
    Classe composta por métodos de codificação e descodificação 
*/

class Golomb{

    public:

    /*! 
        Codifica o inteiro fornecido. Para isso calcula os valores de q,r,c, converte q para unitario e r para binário e faz a concatenação q+r
    */
    dynamic_bitset<> encode(int value, int m){
        int q = value/m;
        int r = value-q*m;
        int c = ceil(log2(m));
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

    /*!
        Faz decode de um bitset codificado. 
    */
    int decode(dynamic_bitset<> encodedVal, int m){
        int q;
        int r=0;
        int value;
        int c = ceil(log2(m));
        int numberOfbits = encodedVal.size();
        for(int i=numberOfbits-1; i>0; i--){
            if(encodedVal[i]==0){
                q=numberOfbits-(i+1);
            }
        }
        encodedVal.resize(numberOfbits-q-1);
        if(encodedVal.size()==1){
            r+= encodedVal[0]*pow(2,c-1);
        }
        else{
            for(int i=encodedVal.size()-1; i>encodedVal.size()-1-c;i--){
                r+= encodedVal[i]*pow(2,c-1);
                c--;
            }
        }
        if(r<pow(2,c)-1){
            value= m*q +r;
        }
        else{
            encodedVal.resize(encodedVal.size()-1);
            for(int i=0; i<encodedVal.size();i++){
                r+= encodedVal[i]*pow(2,i);
            }
            value= m*q +r-(pow(2,c)-m);
        }
        return value;
    }
};