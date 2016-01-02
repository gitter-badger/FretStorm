#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "MidiFile.h"
#include "BinUtils.h"

using namespace std;

MidiFile::MidiFile(void)
:   rwErrorFlag(0),
    theTrackState(TRACK_STATE_SPLIT),   // joined or split
    theTimeState(TIME_STATE_ABSOLUTE),  // absolute or delta
    ticksPerQuarterNote(120),           // TPQ time base of file
    trackCount(1)                       // # of tracks in file
    {
}

MidiFile::MidiFile(const string* filename)
: MidiFile() {
    this->filename = *filename;
    read();
}
MidiFile::MidiFile(const char* filename)
: MidiFile(new string(filename)) { }


MidiFile::MidiFile(istream& input)
: MidiFile() {
    read(input);
}


MidiFile::~MidiFile() {/*
   readFileName.clear();
   clear();
   if (events[0] != NULL) {
      delete events[0];
      events[0] = NULL;
   }
   events.resize(0);
   rwstatus = 0;
   timemap.clear();
   timemapvalid = 0;*/
}

//////////////////////////////
//
// MidiFile::read -- Parse a Standard MIDI File and store its contents
//      in the object.
//

int MidiFile::read() {
    fstream input;
    input.open(filename, ios::binary | ios::in);

    if (input.is_open())
        return read(input);
    else
        return (rwErrorFlag = 1);
}

int MidiFile::read(istream& input) {
    if (input.peek() != 'M') {
        // If the first byte in the input stream is not 'M', then presume that
        // the MIDI file is in the binasc format which is an ASCII representation
        // of the MIDI file.  Convert the binasc content into binary content and
        // then continue reading with this function.
        stringstream binarydata;
       // Binasc binasc;
       // binasc.writeToBinary(binarydata, input);
        binarydata.seekg(0, ios_base::beg);
        if (binarydata.peek() != 'M') {
            cerr << "Bad MIDI data input" << endl;
            return (rwErrorFlag = 2);
        } else {
            cout << "binary file" << endl;
            return read(binarydata);
        }
    }

    // We assume it's a valid MIDI file, so we start reading

    if (readHeader(input))
        return rwErrorFlag;

    //TODO some check for trackcount here ?
    trackCount = trackCountInHeader;

    for (int i = 0; i < trackCountInHeader; ++i) {
        MidiTrack* midiTrack = new MidiTrack(*this);

        if (midiTrack->read(input, rwErrorFlag))
            return rwErrorFlag;

        tracks.push_back(midiTrack);
    }

    return 0;
}

int MidiFile::readHeader(istream& input) {
    // Read the MIDI header
    // (4 bytes of ID, 4 byte data size, anticipated 6 bytes of data.)

    if (BinUtils::checkFoundChar(input.get(), 'M', &filename))
        return (rwErrorFlag = 1);
    if (BinUtils::checkFoundChar(input.get(), 'T', &filename))
        return (rwErrorFlag = 1);
    if (BinUtils::checkFoundChar(input.get(), 'h', &filename))
        return (rwErrorFlag = 1);
    if (BinUtils::checkFoundChar(input.get(), 'd', &filename))
        return (rwErrorFlag = 1);

    // read header size (allow larger header size?)
    headerSize = BinUtils::readLittleEndian4Bytes(input);
    if (headerSize != 6) {
        cerr<< "File " << filename
            << " is not a MIDI 1.0 Standard MIDI file." << endl
            << "The header size is " << headerSize << " bytes." << endl;
        return (rwErrorFlag = 1);
    }

    // Header parameter #1: format type
    formatType = BinUtils::readLittleEndian2Bytes(input);
    switch (formatType) {
    case 0:
        formatType = 0;
        break;
    case 1:
        formatType = 1;
        break;
    case 2:    // Type-2 MIDI files should probably be allowed as well.
    default:
        cerr<< "Error: cannot handle a type-" << formatType
            << " MIDI file" << endl;
        return (rwErrorFlag = 1);
    }

    // Header parameter #2: track count
    trackCountInHeader = BinUtils::readLittleEndian2Bytes(input);
    if (formatType == 0 && trackCountInHeader != 1) {
        cerr<< "Error: Type 0 MIDI file can only contain one track" << endl
            << "Instead track count is: " << trackCountInHeader << endl;
        return (rwErrorFlag = 1);
    }

    // Header parameter #3: Ticks per quarter note
    ticksPerQuarterNote = BinUtils::readLittleEndian2Bytes(input);
    if (ticksPerQuarterNote >= 0x8000) {
        int framespersecond = ((!(ticksPerQuarterNote >> 8))+1) & 0x00ff;
        int resolution      = ticksPerQuarterNote & 0x00ff;
        switch (framespersecond) {
        case 232:  framespersecond = 24; break;
        case 231:  framespersecond = 25; break;
        case 227:  framespersecond = 29; break;
        case 226:  framespersecond = 30; break;
        default:
            cerr << "Warning: unknown FPS: " << framespersecond << endl;
            framespersecond = 255 - framespersecond + 1;
            cerr << "Setting FPS to " << framespersecond << endl;
        }
        // actually ticks per second (except for frame=29 (drop frame)):

        cerr << "SMPTE ticks: " << ticksPerQuarterNote << " ticks/sec" << endl;
        cerr << "SMPTE frames per second: " << framespersecond << endl;
        cerr << "SMPTE frame resolution per frame: " << resolution << endl;
    }

    return 0;
}




void MidiFile::print() {
    printMidiHeader();
    for (int i = 0; i < trackCount; ++i){
        tracks[i]->print();
    }
}

void MidiFile::printMidiHeader() {
    // print MIDI file header marker
    cout << "+M +T +h +d\t\t\t; MIDI file header chunk marker" << endl;
    // print the number of bytes in the MIDI file to follow (always 6):
    cout << "4'6\t\t\t\t; bytes in header to follow" << endl;
    // print the format (0 = single track, 1 = multitrack)
    // The MidiFile class does not exactly keep track of this value.
    // It will presume that a single track file is a type-0 MIDI file
    // (type-1 MIDI files can theoretically have a single track, but not
    // usually).
    cout<< "2'" << formatType << "\t\t\t\t; format: Type-0 (single track)"
        << endl;
    // print track count
    cout<< "2'" << trackCount
        << "\t\t\t\t; track count: "
        << trackCount << " track";
    if (trackCount > 1)
        cout << "s";

    cout << endl;

    // print the ticks per quarter note.  The ticks per quarter note
    // can be SMPTE or regular.  Assuming regular at the moment.
    cout << "2'" << ticksPerQuarterNote << "\t\t\t\t; ticks per quarter note" << endl;
}

const string MidiFile::getFilename() {
    return filename;
}
