#include "midi.h"
#include <iostream>

void printMidiFile(MidiFile& midifile) {
    midifile.absoluteTicks();
    printMidiHeader(midifile);
    int trackcount = midifile.getTrackCount();
    for (int i=0; i<trackcount; i++) {
        printTrack(midifile, i);
    }
}



//////////////////////////////
//
// printTrack --
//

void printTrack(MidiFile& midifile, int track) {
    cout << endl;

    // first print track header
    cout << "+M +T +r +k\t\t\t; Track chunk marker" << endl;
    // print number of bytes in track
    int trackbytes = getTrackByteCount(midifile, track);
    cout << "4'" << trackbytes << "\t\t\t\t; number of bytes to follow in track"
    << endl;

    cout << endl;

    // print the list of events in the track
    MidiEvent event;
    int eventcount = midifile.getEventCount(track);
    for (int i=0; i<eventcount; i++) {
        event = midifile.getEvent(track, i);
        printMidiEvent(event);
    }
}



//////////////////////////////
//
// printMidiEvent -- print a time/MIDI message pair.
//

void printMidiEvent(MidiEvent& event) {
    // print the time:
    cout << "v" << event.tick << "\t";

    // print the command byte in hex format (two digits):
    int commandbyte = event[0];
    printHexByte(commandbyte);
    int i;

    switch (commandbyte & 0xf0) {
    case 0x90:
    case 0x80:
        printNote(event[1]);
        for (i=1; i<(int)event.size(); i++) {
            cout << " ";
            cout << "'" << (int)event[i];
        }
        break;
    default:
        if (commandbyte == 0xff) {
            cout << " ";
            printHexByte(event[1]);
            printMetaEvent(event);

        } else
            for (i=1; i<(int)event.size(); i++) {
                cout << " ";
                printHexByte(event[i]);
            }
    }

    cout << endl;
}

void printNote(int note) {
    switch (note) {
    case 60:
        cout << "Easy   A";
        break;
    case 61:
        cout << "Easy   B";
        break;
    case 62:
        cout << "Easy   C";
        break;
    case 72:
        cout << "Medium A";
        break;
    case 73:
        cout << "Medium B";
        break;
    case 74:
        cout << "Medium C";
        break;
    case 75:
        cout << "Medium D";
        break;
    case 84:
        cout << "Hard   A";
        break;
    case 85:
        cout << "Hard   B";
        break;
    case 86:
        cout << "Hard   C";
        break;
    case 87:
        cout << "Hard   D";
        break;
    case 88:
        cout << "Hard   E";
        break;
    case 96:
        cout << "Expert A";
        break;
    case 97:
        cout << "Expert B";
        break;
    case 98:
        cout << "Expert C";
        break;
    case 99:
        cout << "Expert D";
        break;
    case 100:
        cout << "Expert E";
        break;
    default:
        cout << "ERROR, unknwon note";
        break;
    }
}

void printMetaEvent(MidiEvent& event) {
    int metaType = event[1];
    int metaSize = event[2];
    switch (metaType) {
    case 0x01:
        cout << " Text : ";
        for (int i = 0; i < metaSize; ++i)
            cout << event[i+3];
        break;
    case 0x03:
        cout << " Track Name : ";
        for (int i = 0; i < metaSize; ++i)
            cout << event[i+3];
        break;
    case 0x51:
        cout << " Tempo Setting : ";
        for (int i = 0; i < metaSize; ++i)
            cout << (int)event[i+3];
        break;
    case 0x58:
        cout << " Time Signature : ";
        for (int i = 0; i < metaSize; ++i)
            cout << (int)event[i+3];
        break;
    case 0x2f:
        cout << " End of Track.";
        break;

    default:
        break;
    }
}



//////////////////////////////
//
// printHexByte --
//

void printHexByte(int value) {
    if (value < 16) {
        cout << "0";
    } else if (value > 255) {
        cerr << "ERROR: value is too large: " << value << endl;
        exit(1);
    }
    cout << hex << value << dec;
}



//////////////////////////////
//
// getTrackByteCount -- number of by the track after the track header.
//    Might need to keep track of End-of-track meta message.
//

int getTrackByteCount(MidiFile& midifile, int track) {
    int sum = 0;
    int i;
    int eventcount = midifile.getEventCount(track);
    MidiEvent event;

    for (i=0; i<eventcount; i++) {
        event = midifile.getEvent(track, i);
        sum += getVlvSize(event.tick);
        sum += event.size();
    }
    return sum;
}



//////////////////////////////
//
// getVlvSize -- return the number of bytes in the VLV format for the
//    integer.
//

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



//////////////////////////////
//
// printMidiHeader --
//
// Example header:
//
// +M +T +h +d             ; MIDI file header chunk marker
// 4'6                     ; bytes in header to follow
// 2'0                     ; format: Type-0 (single track)
// 2'1                     ; track count: 1 track
// '-25 '40                ; divisions: SMPTE: 25 frames/sec 40 subframes/frame
//                         ;    in other words: 25 * 40 = 1000 ticks per second.
//

void printMidiHeader(MidiFile& midifile) {
    // print MIDI file header marker
    cout << "+M +T +h +d\t\t\t; MIDI file header chunk marker" << endl;
    // print the number of bytes in the MIDI file to follow (always 6):
    cout << "4'6\t\t\t\t; bytes in header to follow" << endl;
    // print the format (0 = single track, 1 = multitrack)
    // The MidiFile class does not exactly keep track of this value.
    // It will presume that a single track file is a type-0 MIDI file
    // (type-1 MIDI files can theoretically have a single track, but not
    // usually).
    if (midifile.getTrackCount() == 0) {
        cout << "2'0\t\t\t\t; format: Type-0 (single track)";
    } else {
        cout << "2'1\t\t\t\t; format: Type-1 (multi-track)";
    }
    cout << endl;
    // print track count
    cout << "2'" << midifile.getTrackCount();
    cout << "\t\t\t\t; track count: ";
    cout << midifile.getTrackCount() << " track";
    if (midifile.getTrackCount() != 1) {
        cout << "s";
    }
    cout << endl;

    // print the ticks per quarter note.  The ticks per quarter note
    // can be SMPTE or regular.  Assuming regular at the moment.
    int ticks = midifile.getTicksPerQuarterNote();
    cout << "2'" << ticks << "\t\t\t\t; ticks per quarter note" << endl;
}




//////////////////////////////
//
// example --
//

void example(void) {

}



//////////////////////////////
//
// usage --
//

void usage(const char* command) {
    cout << "Usage: " << command << " midifile" << endl;
}



