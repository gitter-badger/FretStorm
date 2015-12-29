#ifndef EVENT_H
#define EVENT_H

#include <MidiEvent.h>
#include <MidiEventList.h>
#include <MidiFile.h>
#include <vector>
#include <string>

using namespace std;

class FretMidiEvent {
public:
    FretMidiEvent(MidiEvent& event);
  // ~FretMidiEvent();

    void print();

protected:
    MidiEvent& event;

    int commandbyte;

    int     note;

    int     tick;
    int     track;
    double  seconds;

};

#endif
