#include <bitset>
#include <iostream>
#include <fstream>
#include <math.h> 
#include <vector> 
#include <boost/dynamic_bitset.hpp> 

using namespace std;

class BitStreamR{

    public:
    //!bitset to Store up to 8 bits
    bitset<8> BitStorage;
    //!Position to store the next bit
    int ReadPosition=0;
    //!Write to file
    ifstream rf;
    //!Contrutor abre o ficheiro para guardar informação
    BitStreamR(){
        rf.open("bitFile.bin", ios::binary | ios_base::app);
    }

    /*!
        Reads one bit from the file
    */
    bool readOneBit(){
        bool bit;
        if(ReadPosition==8){
            ReadPosition=0;
        }
        else if(ReadPosition==0){
            char tempStorage;
            rf.read( reinterpret_cast<char*>(&tempStorage), 8) ;
            BitStorage=tempStorage;
            cout<<BitStorage<<endl;
        }   
        bit= BitStorage[ReadPosition];
        ReadPosition++;
        return bit;
    }
    /*!
        Read n bits by reading one bit n times
    */
    boost::dynamic_bitset<> readNBits(int numberOfBits){
        boost::dynamic_bitset<> Bits(numberOfBits);
        for(int i=0; i<numberOfBits;i++){
            Bits[i]=readOneBit();
        }
        return Bits;
    }
    //! Fecha o ficheiro de onde lemos os bits
    void close(){
        rf.close();
    }
};