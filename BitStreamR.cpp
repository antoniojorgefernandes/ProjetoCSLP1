#include <bitset>
#include <iostream>
#include <fstream>
#include <math.h> 
#include <vector> 
#include <boost/dynamic_bitset.hpp> 
using namespace boost;
using namespace std;


/*!
    BitStreamR (R for Reader) is a class used to read bits from a file.
*/

class BitStreamR{

    public:
    //!bitset to Store up to 8 bits
    bitset<8> BitStorage;
    //!Position to store the next bit
    int ReadPosition=0;
    //!Current file byte
    int CurrentByte=0;
    //!File reader
    ifstream rf;
    //!Contrutor opens de file to read info from
    BitStreamR(){
        rf.open("../bitFile.bin", ios::binary);
    }

    /*!
        Reads one bit from the file
    */
    int readOneBit(){
        int bit;
        char tempStorage;
        if(ReadPosition==8){
            ReadPosition=0;
            CurrentByte++;
        }
        if(ReadPosition==0){
            rf.clear();
            rf.seekg(CurrentByte);
            rf.read( reinterpret_cast<char*>(&tempStorage), 8) ;
            BitStorage=tempStorage;
        }   

        bit= BitStorage[ReadPosition];
        ReadPosition++;
        return bit;
    }
    /*!
        Read n bits by reading one bit n times
    */
    dynamic_bitset<> readNBits(int numberOfBits){
        dynamic_bitset<> value(numberOfBits);
        for(int i=0; i<numberOfBits;i++){
            value.push_back(readOneBit());
        }
        return value;
    }
    //! Fecha o ficheiro de onde lemos os bits
    void close(){
        rf.close();
    }
};