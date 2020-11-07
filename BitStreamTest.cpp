#include "BitStreamW.cpp"
#include "BitStreamR.cpp"
#include <boost/dynamic_bitset.hpp> 
using namespace std;

int main(int argc, char* argv[]){
    BitStreamW bsw;
    bsw.writeNBits(512,10);
    bsw.close();
    BitStreamR bsr;
    cout<<bsr.readNBits(10)<<endl;  
    return 0;
};