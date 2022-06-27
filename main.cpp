#define CRC_01 0x47000000046dd228
#define CRC_02 0x6687616bb2cfff28
#define CRC_03 0xee3c21481634ff28
#define CRC_04 0x3622616bb37fff28
#define CRC_05 0xa800000ce9553c28
#define CRC_06 0xffffffffffffffff
#define CRC_07 0x0000000000000000
#include <iostream>

using namespace std;
int main()
{
  uint64_t dataIn[] = {CRC_01, CRC_02, CRC_03, CRC_04, CRC_05, CRC_06, CRC_07};
  cout << "Line " << __LINE__ << endl;

  for (uint8_t dataInSeqNo = 0; dataInSeqNo < sizeof(dataIn) / sizeof(uint64_t); ++dataInSeqNo)
  {

    uint8_t *data = (uint8_t *)&dataIn[dataInSeqNo]; // chop 64-bit number to seqence of 8 bit numbers
    uint8_t crc = 0;
    uint8_t byteCtr;
    const uint8_t nbrOfBytes = 8; // 8-th byte is received crc to compare
    // calculates 8-Bit checksum with given polynomial
    for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
      cout << "data[" << (int)dataInSeqNo << "] = 0x" << hex << (int)data[byteCtr] << "\t";

      crc ^= (data[byteCtr]);
      for (uint8_t bit = 0; bit < 8; ++bit)
      {
        if (crc & 0x01)
          crc = (crc >> 1) ^ 0x8c;
        else
          crc = (crc >> 1);
      }
      cout << "crc byte <" << (int)byteCtr << "> = 0x" << hex << (int)crc << endl;
    }
    cout << "crc <" << (int)dataInSeqNo << "> = 0x" << hex << (int)crc << endl;
  }
}
