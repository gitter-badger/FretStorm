

#include "BinUtils.h"
#include <sstream>
#include <string.h>
#include <bitset>

using namespace std;


///////////////////////////////
//
// BinUtils::*VLV -- Variable-Length Value from/to file
//

int BinUtils::readVLV(istream& infile, int* trackbytes) {
    int output = 0;
    int length = 0;
    uchar ch;
    do {
        infile.read((char*)&ch, 1);
        output = (output << 7) | (0x7f & ch);
        (*trackbytes)++;
        length++;
    } while (ch >> 7 && length < 4);
    if (ch >> 7) {
        cerr << "Error: VLV value was too long" << endl;
        return -1;
    }

    return output;
}

int BinUtils::writeVLV(uchar bytes[VLV_MAX_SIZE], int number) {
    unsigned long value = (unsigned long)number;
    if (value >= (1 << (7*VLV_MAX_SIZE))) {
        cout << "Error: number too large to handle" << endl;
        exit(1);
    }

    uchar temp[VLV_MAX_SIZE];
    int length;
    for(length = 0; value > 0; length++) {
        temp[length]  = (value & 0x7f) | 0x80;
        value >>= 7;
    }

    temp[0] -= 0x80;

    for (int i = 0;      i <= length;        ++i)
        bytes[i] = temp[length-i-1];
    for (int i = length; i <= VLV_MAX_SIZE;  ++i)
        bytes[i] = 0;

    return length;
}

void BinUtils::printVLVHex(uchar bytes[VLV_MAX_SIZE]) {
    int i = 0;
    do {
        cout << hex << ((int) bytes[i]) << " ";
        i++;
    } while ((i < VLV_MAX_SIZE) && (bytes[i-1] >> 7));
}

void BinUtils::printVLVBin(uchar bytes[VLV_MAX_SIZE]) {
    int i = 0;
    do {
        cout << hex << bitset<8>((int) bytes[i]) << " ";
        i++;
    } while ((i < VLV_MAX_SIZE) && (bytes[i-1] >> 7));
}

int getVlvSize(int value) {
    if (value < 0x80) {
        return 1;
    } if (value < 0x4000) {
        return 2;
    } else if (value < 0x200000) {
        return 3;
    } else if (value < 0x10000000) {
        return 4;
    } else {
        return 5;
    }
}



///////////////////////////////////////////////////////////////////////////
//
// Static functions:
//


int    BinUtils::checkFoundChar(char character, char expected, string* filename) {
    if (character == EOF) {
        cerr << "In file "      << filename << ": unexpected end of file." << endl;
        cerr << "Expecting '"   << expected << "', but found nothing." << endl;
        return 1;
    } else if (character != expected) {
        cerr << "File "         << filename << " is not a MIDI file" << endl;
        cerr << "Expecting '"   << expected << "', but found '"
        << character << "'" << endl;
        return 1;
    }
    return 0;
}

uchar  BinUtils::readByte(istream& input) {
    uchar buffer[1] = {0};
    input.read((char*)buffer, 1);
    if (input.eof()) {
        cerr << "Error: unexpected end of file." << endl;
        exit(1);
    }
    return buffer[0];
}
ushort BinUtils::readLittleEndian2Bytes(istream& input) {
    uchar buffer[2] = {0};
    input.read((char*)buffer, 2);
    if (input.eof()) {
        cerr << "Error: unexpected end of file." << endl;
        exit(1);
    }
    return buffer[1] | (buffer[0] << 8);
}
ulong  BinUtils::readLittleEndian4Bytes(istream& input) {
    uchar buffer[4] = {0};
    input.read((char*)buffer, 4);
    if (input.eof()) {
        cerr << "Error: unexpected end of file." << endl;
        exit(1);
    }
    return buffer[3] | (buffer[2] << 8) | (buffer[1] << 16) | (buffer[0] << 24);
}


ostream& BinUtils::writeLittleEndianUShort(ostream& out, ushort value) {
    union { char bytes[2]; ushort us; } data;
    data.us = value;
    out << data.bytes[0];
    out << data.bytes[1];
    return out;
}
ostream& BinUtils::writeBigEndianUShort(ostream& out, ushort value) {
    union { char bytes[2]; ushort us; } data;
    data.us = value;
    out << data.bytes[1];
    out << data.bytes[0];
    return out;
}

ostream& BinUtils::writeLittleEndianShort(ostream& out, short value) {
    union { char bytes[2]; short s; } data;
    data.s = value;
    out << data.bytes[0];
    out << data.bytes[1];
    return out;
}
ostream& BinUtils::writeBigEndianShort(ostream& out, short value) {
    union { char bytes[2]; short s; } data;
    data.s = value;
    out << data.bytes[1];
    out << data.bytes[0];
    return out;
}

ostream& BinUtils::writeLittleEndianULong(ostream& out, ulong value) {
    union { char bytes[4]; ulong ul; } data;
    data.ul = value;
    out << data.bytes[0];
    out << data.bytes[1];
    out << data.bytes[2];
    out << data.bytes[3];
    return out;
}
ostream& BinUtils::writeBigEndianULong(ostream& out, ulong value) {
    union { char bytes[4]; long ul; } data;
    data.ul = value;
    out << data.bytes[3];
    out << data.bytes[2];
    out << data.bytes[1];
    out << data.bytes[0];
    return out;
}

ostream& BinUtils::writeLittleEndianLong(ostream& out, long value) {
    union { char bytes[4]; long l; } data;
    data.l = value;
    out << data.bytes[0];
    out << data.bytes[1];
    out << data.bytes[2];
    out << data.bytes[3];
    return out;
}
ostream& BinUtils::writeBigEndianLong(ostream& out, long value) {
    union { char bytes[4]; long l; } data;
    data.l = value;
    out << data.bytes[3];
    out << data.bytes[2];
    out << data.bytes[1];
    out << data.bytes[0];
    return out;
}

ostream& BinUtils::writeBigEndianFloat(ostream& out, float value) {
    union { char bytes[4]; float f; } data;
    data.f = value;
    out << data.bytes[3];
    out << data.bytes[2];
    out << data.bytes[1];
    out << data.bytes[0];
    return out;
}
ostream& BinUtils::writeLittleEndianFloat(ostream& out, float value) {
    union { char bytes[4]; float f; } data;
    data.f = value;
    out << data.bytes[0];
    out << data.bytes[1];
    out << data.bytes[2];
    out << data.bytes[3];
    return out;
}

ostream& BinUtils::writeBigEndianDouble(ostream& out, double value) {
    union { char bytes[8]; double d; } data;
    data.d = value;
    out << data.bytes[7];
    out << data.bytes[6];
    out << data.bytes[5];
    out << data.bytes[4];
    out << data.bytes[3];
    out << data.bytes[2];
    out << data.bytes[1];
    out << data.bytes[0];
    return out;
}
ostream& BinUtils::writeLittleEndianDouble(ostream& out, double value) {
    union { char bytes[8]; double d; } data;
    data.d = value;
    out << data.bytes[0];
    out << data.bytes[1];
    out << data.bytes[2];
    out << data.bytes[3];
    out << data.bytes[4];
    out << data.bytes[5];
    out << data.bytes[6];
    out << data.bytes[7];
    return out;
}
