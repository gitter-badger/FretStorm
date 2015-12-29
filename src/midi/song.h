#ifndef SONG_H
#define SONG_H

#include <string>

#include <MidiFile.h>

#include "track.h"

using namespace std;

class MidiSong {
public:
    MidiSong(MidiFile      _midiFile);
    MidiSong(MidiFile     *_midiFile);
    MidiSong(const char*    filename);
    MidiSong(const string&  filename);
   ~MidiSong();

    static string getName();
    void print();
    void printMidiHeader();
    void initTracks();



protected:
    MidiFile midiFile;

    vector<MidiTrack*>      trackList;

    int AlltrackCount;
    int NotetracksCount;


private:
    // Called by the constructors
    MidiSong();

};



#endif
