#include "song.h"

#include <iostream>
using namespace std;

MidiSong::MidiSong(MidiFile *_midiFile)
: midiFile(*_midiFile) {
    midiFile.absoluteTicks();
    AlltrackCount = midiFile.getTrackCount();
    initTracks();

}

MidiSong::MidiSong(MidiFile _midiFile)
    : MidiSong(&_midiFile) { }

MidiSong::MidiSong(const char* filename)
    : MidiSong(new MidiFile(filename)) { }

MidiSong::MidiSong(const string& filename)
    : MidiSong(new MidiFile(filename)) { }

MidiSong::~MidiSong() {
}


void MidiSong::initTracks() {
    for (int i = 0; i < AlltrackCount; ++i) {
        //track
        trackList.push_back(new MidiTrack(midiFile, i));
    }

}



void MidiSong::print() {
    printMidiHeader();
    for (int i = 0; i < AlltrackCount; ++i){
        //cout << "auie" << endl;
        trackList[i]->print();
    }
}

void MidiSong::printMidiHeader() {
    // print MIDI file header marker
    cout << "+M +T +h +d\t\t\t; MIDI file header chunk marker" << endl;
    // print the number of bytes in the MIDI file to follow (always 6):
    cout << "4'6\t\t\t\t; bytes in header to follow" << endl;
    // print the format (0 = single track, 1 = multitrack)
    // The MidiFile class does not exactly keep track of this value.
    // It will presume that a single track file is a type-0 MIDI file
    // (type-1 MIDI files can theoretically have a single track, but not
    // usually).
    if (midiFile.getTrackCount() == 0)
        cout << "2'0\t\t\t\t; format: Type-0 (single track)";
    else
        cout << "2'1\t\t\t\t; format: Type-1 (multi-track)";

    cout << endl;
    // print track count
    cout << "2'" << midiFile.getTrackCount();
    cout << "\t\t\t\t; track count: ";
    cout << midiFile.getTrackCount() << " track";
    if (midiFile.getTrackCount() != 1)
        cout << "s";

    cout << endl;

    // print the ticks per quarter note.  The ticks per quarter note
    // can be SMPTE or regular.  Assuming regular at the moment.
    int ticks = midiFile.getTicksPerQuarterNote();
    cout << "2'" << ticks << "\t\t\t\t; ticks per quarter note" << endl;
}
