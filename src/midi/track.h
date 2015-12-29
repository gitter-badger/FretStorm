#ifndef TRACK_H
#define TRACK_H

#include <MidiEvent.h>
#include <MidiEventList.h>
#include <MidiFile.h>
#include <vector>
#include <string>

#include "event.h"

using namespace std;

class MidiTrack {
public:
    MidiTrack(MidiFile& midiFile, int identifiant);
  // ~MidiTrack();

    void print();
    int  getTrackByteCount(MidiFile& midifile, int track);
    int  getVlvSize(int value);

    void simpleSearchForTitle();
    void initEvents();


protected:
    string  trackName;
    int     trackBytes;
    int     trackLength;

    MidiEventList& events;
    vector<FretMidiEvent*> eventList;



};

#endif
