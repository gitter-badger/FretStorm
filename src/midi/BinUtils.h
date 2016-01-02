
#ifndef _BINUTILS_H_INCLUDED
#define _BINUTILS_H_INCLUDED

#include <iostream>

using namespace std;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

#define VLV_MAX_SIZE 4

class BinUtils {
public:
    BinUtils        (void);
   ~BinUtils        ();

    static int  readVLV         (istream& infile, int* trackbytes);
    static int  writeVLV        (uchar bytes[VLV_MAX_SIZE], int number);
    static void printVLV        (uchar bytes[VLV_MAX_SIZE]);
    static int  checkFoundChar  (char c, char expected, string* filename);

      // static functions:
    static uchar    readByte                (istream& input);
    static ushort   readLittleEndian2Bytes  (istream& input);
    static ulong    readLittleEndian4Bytes  (istream& input);
    static ostream& writeLittleEndianUShort (ostream& out, ushort value);
    static ostream& writeBigEndianUShort    (ostream& out, ushort value);
    static ostream& writeLittleEndianShort  (ostream& out, short  value);
    static ostream& writeBigEndianShort     (ostream& out, short  value);
    static ostream& writeLittleEndianULong  (ostream& out, ulong  value);
    static ostream& writeBigEndianULong     (ostream& out, ulong  value);
    static ostream& writeLittleEndianLong   (ostream& out, long   value);
    static ostream& writeBigEndianLong      (ostream& out, long   value);
    static ostream& writeLittleEndianFloat  (ostream& out, float  value);
    static ostream& writeBigEndianFloat     (ostream& out, float  value);
    static ostream& writeLittleEndianDouble (ostream& out, double value);
    static ostream& writeBigEndianDouble    (ostream& out, double value);

protected:

private:

};


#endif /* _BINUTILS_H_INCLUDED */



