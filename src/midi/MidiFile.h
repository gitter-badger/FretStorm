#ifndef _MIDIFILE_H
#define _MIDIFILE_H

#include <vector>
#include <istream>
#include <fstream>

#include "MidiTrack.h"

using namespace std;

#define TIME_STATE_DELTA       0
#define TIME_STATE_ABSOLUTE    1

#define TRACK_STATE_SPLIT      0
#define TRACK_STATE_JOINED     1

class _TickTime {
public:
    int    tick;
    double seconds;
};


class MidiFile {
public:
    MidiFile                    (void);
    MidiFile                    (const string* aFile);
    MidiFile                    (const char* filename);
    MidiFile                    (istream& input);
   ~MidiFile                    ();

    void print();
    void printMidiHeader();

    // reading functions:
    int     read                    ();
    int     read                    (istream& istream);
    int     readHeader              (istream& input);

    const string getFilename             (void);

protected:
    // read/write error flag
    int rwErrorFlag;

    // Header Data
    ulong   headerSize;
    ushort  formatType;
    ushort  trackCountInHeader;

    // General
    string  filename;
    int     theTrackState;          // joined or split
    int     theTimeState;           // absolute or delta

    int     ticksPerQuarterNote;    // time base of file

    // Tracks
    vector<MidiTrack*>  tracks;
    int     trackCount;             // # of tracks in file TODO useful ?
    int     noteTrackCount;
};





#endif /* _MIDIFILE_H */
