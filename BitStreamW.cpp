#include <bitset>
#include <iostream>
#include <fstream>
#include <math.h> 
#include <vector> 
#include <boost/dynamic_bitset.hpp> 

using namespace std;
using namespace boost;
/*!
    BitStreamW (W de writter) é uma classe para escrever bits num ficheiro.
*/

class BitStreamW{

    public:
    //!bitset to Store up to 8 bits
    dynamic_bitset<> BitStorage;
    //!Position to store the next bit
    int InsertPosition=0;
    //!Write to file
    ofstream wf;
    //!Contrutor abre o ficheiro para guardar informação
    BitStreamW(){
        wf.open("../bitFile.bin",ios::binary);
        
    }

    /*!
        Inserts a bit in the storage
        Check if the bitset if full and writes to the file in that case.
        Resets the InsertPosition and the storage
    */
    void writeOneBit(u_char bit){
        BitStorage.push_back(bit);
        InsertPosition++;
        if(InsertPosition==8){
            char n = BitStorage.to_ulong();
            wf.write( reinterpret_cast<const char*>(&n), sizeof(n));
            InsertPosition=0;
            BitStorage.clear();
        }
    }
    /*!
        writes n bits by writting one bit n times
    */
    void writeNBits(dynamic_bitset<> value, int numberOfBits){
        for(int i=0; i<numberOfBits;i++){
            writeOneBit(value[i]);
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