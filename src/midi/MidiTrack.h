#ifndef _MIDITRACK_H
#define _MIDITRACK_H

#include <vector>

#include "MidiEvent.h"

using namespace std;

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

class MidiFile;

class MidiTrack {
public:
    MidiTrack(MidiFile& file);
    int     getTrackByteCount       (int track);
    int     read                    (istream& input, int& rwErrorFlag);
    int     readHeader              (istream& input, int& rwErrorFlag);

    void    linkNotePairs           (void);

    void    print                   (void);

protected:
    MidiFile& midiFileRef;
    string    midiFileName;

    string  trackName;
    int     trackChunkSize;
    int     trackLength;

    vector<MidiEvent*> events;
};





#endif /* _MIDITRACK_H */
