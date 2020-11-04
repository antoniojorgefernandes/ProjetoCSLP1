#include <bitset>
#include <iostream>
#include <fstream>
#include <math.h> 
#include <vector> 
#include <boost/dynamic_bitset.hpp> 
using namespace std;

class BitStream{

    public:
    //!bitset to Store up to 8 bits
    bitset<8> BitStorage;
    //!Position to store the next bit
    int InsertPosition=0;
    //!Position to read next bit
    int ReadPosition=0;
    //!Bits written to file 
    int bitsWrittenToFile=0;
    //!Write to file
    ofstream wf;
    //!Read from file
    ifstream rf;

    /*!
        Inserts a bit in the storage
        Check if the bitset if full and writes to the file in that case.
        Resets the InsertPosition and the storage
    */
    void writeOneBit(u_char bit){
        BitStorage.set(InsertPosition, bit);
        InsertPosition++;
        if(InsertPosition==8){
            wf.open("bitFile.bin", ios::binary | ios_base::app);
            char n = BitStorage.to_ulong();
            wf.write( reinterpret_cast<const char*>(&n), sizeof(n) );
            InsertPosition=0;
            BitStorage.reset();
            bitsWrittenToFile+=8;
            wf.close();
        }
    }

    /*!
        writes n bits by writting one bit n times
    */
    void writeNBits(int value, int numberOfBits){
        boost::dynamic_bitset<> valueBin(numberOfBits,value);
        for(int i=0; i<numberOfBits;i++){
            writeOneBit(valueBin[i]);
        }
    }


    /*!
        Read one bit either from a file or from the BitStorage
        Calculates the current byte position to read from file and the position of the bit to read from said byte
    */
    bool readOneBit(){
        bool bit;
        bitset<8> tempStorage;
        rf.open("bitFile.bin", ios::binary);
        if(bitsWrittenToFile<8 && InsertPosition>=ReadPosition){
            bit = BitStorage[ReadPosition];
            ReadPosition++;
            return bit;
        }
        float CurrentByte = ceil((ReadPosition+1)/8.0);
        int PositionToReadInCurrentByte = (ReadPosition)%8;
        if(CurrentByte>bitsWrittenToFile/8){
            if(PositionToReadInCurrentByte<InsertPosition){
                bit = BitStorage[PositionToReadInCurrentByte];
                ReadPosition++;
                return bit;
            }
            return 0;
        }
        char n ;
        rf.read( reinterpret_cast<char*>(&n), sizeof(n) ) ;
        tempStorage = n ;
        bit=tempStorage[PositionToReadInCurrentByte];
        rf.close();
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
};


int main( int argc, char** argv ) {

}