#include "GolombEncode.cpp"
#include "GolombDecode.cpp"
#include <boost/dynamic_bitset.hpp> 
#include <iostream>
using namespace std;
using namespace boost;

int main(int argc, char* argv[]){
    GolombEncode golombEnc;
    cout<<"number 10 encoded with m=5: ";
    dynamic_bitset<> ten = golombEnc.encode(10,5);
    cout<<ten<<endl;
    cout<<"number 100.000 encoded with m=50000: ";
    dynamic_bitset<> onehund = golombEnc.encode(100000,50000);
    cout<<onehund<<endl;
    cout<<"number 12 encoded with m=2: ";
    dynamic_bitset<> twelve = golombEnc.encode(12,2);
    cout<<twelve<<endl;
    dynamic_bitset<> five = golombEnc.encode(5,2);
    cout<<"number 5 encoded with m=2: ";
    cout<<five<<endl;
    dynamic_bitset<> thirty5 = golombEnc.encode(35,2);
    cout<<"number 35 encoded with m=2: ";
    cout<<thirty5<<endl;
    dynamic_bitset<> thirty52 = golombEnc.encode(35,5);
    cout<<"number 35 encoded with m=5: ";
    cout<<thirty52<<endl;
    GolombDecode golombDec;
    int f;
    cout<<ten<<" decoded: ";
    f = golombDec.decode(ten,5);
    cout<<f<<endl;
    cout<<onehund<<" decoded with m=50000: ";
    f = golombDec.decode(onehund,50000);
    cout<<f<<endl;
    cout<<twelve<<" decoded: ";
    f = golombDec.decode(twelve,2);
    cout<<f<<endl;
    cout<<five<<" decoded: ";
    f = golombDec.decode(five,2);
    cout<<f<<endl;
    cout<<thirty5<<" decoded with m=2: ";
    f = golombDec.decode(thirty5,2);
    cout<<f<<endl;
    cout<<thirty52<<" decoded with m=5: ";
    f = golombDec.decode(thirty52,5);
    cout<<f<<endl;

    return 0;
};