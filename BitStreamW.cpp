#include <bitset>
#include <iostream>
#include <fstream>
#include <math.h> 
#include <vector> 
#include <boost/dynamic_bitset.hpp> 

using namespace std;

/*!
    BitStreamW (W de writter) é uma classe para escrever bits num ficheiro.
*/

class BitStreamW{

    public:
    //!bitset to Store up to 8 bits
    bitset<8> BitStorage;
    //!Position to store the next bit
    int InsertPosition=0;
    //!Write to file
    ofstream wf;
    //!Contrutor abre o ficheiro para guardar informação
    BitStreamW(){
        wf.open("bitFile.bin", ios::binary | ios::out);
    }

    /*!
        Inserts a bit in the storage
        Check if the bitset if full and writes to the file in that case.
        Resets the InsertPosition and the storage
    */
    void writeOneBit(u_char bit){
        BitStorage.set(InsertPosition, bit);
        InsertPosition++;
        if(InsertPosition==8){
            char n = BitStorage.to_ulong();
            wf.write( reinterpret_cast<const char*>(&n), sizeof(n) );
            InsertPosition=0;
            BitStorage.reset();
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
        Escreve o que resta no Storage no ficheiro e fecha-o
    */
    void close(){
        char n = BitStorage.to_ulong();
        wf.write( reinterpret_cast<const char*>(&n), sizeof(n) );
        wf.close();
    }
};