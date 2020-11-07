#include "Golomb.cpp"
#include <boost/dynamic_bitset.hpp> 
using namespace std;
using namespace boost;

int main(int argc, char* argv[]){
    Golomb golombEnc;
    dynamic_bitset<> ten = golombEnc.encode(10,2);
    cout<<ten<<endl;
    dynamic_bitset<> twelve = golombEnc.encode(12,2);
    cout<<twelve<<endl;
    dynamic_bitset<> five = golombEnc.encode(5,2);
    cout<<five<<endl;
    dynamic_bitset<> thirty5 = golombEnc.encode(35,2);
    cout<<thirty5<<endl;
    Golomb golombDec;
    int f;
    f = golombDec.decode(ten,2);
    cout<<f<<endl;
    f = golombDec.decode(twelve,2);
    cout<<f<<endl;
    f = golombDec.decode(five,2);
    cout<<f<<endl;
    f = golombDec.decode(thirty5,2);
    cout<<f<<endl;

    return 0;
};