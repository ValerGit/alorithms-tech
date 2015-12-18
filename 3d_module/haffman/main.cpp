#include <iostream>

using namespace std;

class COutBitStream {
public:
    COutBitStream();
    ~COutBitStream();
    void WriteBit( unsigned char bit );
    void WriteByte( unsigned char byte );

private:
    int bufferSize;
    unsigned char* buffer;
    int bitsCount;
};

COutBitStream::COutBitStream() : bitsCount(0), bufferSize(1024)
{
    buffer = new unsigned char[bufferSize];
    std::memset(buffer, 0, bufferSize);
}

COutBitStream::~COutBitStream()
{
    delete[] buffer;
}

void COutBitStream::WriteBit(unsigned char bit)
{
    if( bitsCount + 1 > bufferSize * 8 ) grow();
    if( bit != 0 ) {
        int bitPlace = bitsCount % 8;
        buffer[bitsCount / 8] |= 1 >> bitPlace;
    }
    ++bitsCount;
}

void COutBitStream::WriteByte(unsigned char byte)
{
    if( bitsCount + 8 > bufferSize * 8 ) grow();
}

int main()
{
    return 0;
}

