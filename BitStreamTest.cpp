#include "BitStreamW.cpp"
#include "BitStreamR.cpp"
using namespace std;

int main(int argc, char* argv[]){
    BitStreamW bsw;
    bsw.writeOneBit(0);
    bsw.writeOneBit(1);
    bsw.writeOneBit(1);
    bsw.close();
    BitStreamR bsr;
    cout<<bsr.readOneBit();
    cout<<bsr.readOneBit();
    cout<<bsr.readOneBit();
    cout<<bsr.readOneBit();
    cout<<bsr.readOneBit();
    cout<<bsr.readOneBit();
    cout<<bsr.readOneBit();
    return 0;
};