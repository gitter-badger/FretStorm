#ifndef EVENT_H
#define EVENT_H

#include <MidiEvent.h>
#include <MidiEventList.h>
#include <MidiFile.h>
#include <vector>
#include <string>

using namespace std;

enum e_event_type {

    NOTE_ON  =  90,
    NOTE_OFF =  80,

    META                = 200,
    META_TEXT           = 201,
    META_TRACKNAME      = 203,
    META_TEMPO_SET      = 281,
    META_TIME_SIG       = 288,
    META_END_OF_TRACK   = 247
};

enum e_notes {
    Easy_A  = 60,
    Easy_B  = 61,
    Easy_C  = 62,
    Easy_D  = 63,
    Easy_E  = 64,

    Medium_A = 72,
    Medium_B = 73,
    Medium_C = 74,
    Medium_D = 75,
    Medium_E = 76,

    Hard_A = 84,
    Hard_B = 85,
    Hard_C = 86,
    Hard_D = 87,
    Hard_E = 88,

    Expert_A = 96,
    Expert_B = 97,
    Expert_C = 98,
    Expert_D = 99,
    Expert_E = 100
};




class FretMidiEvent {
public:
    FretMidiEvent(MidiEvent& event);
  // ~FretMidiEvent();


    void print();

protected:
    MidiEvent& event;

    e_event_type eventType;

    // Here, only one is not NULL
    e_notes note;
    string  text;
    int     tempo;
    int     timeSig;


    int     tick;
    int     track;
    double  seconds;

    void setMetaFromEvent();
    void setTextFromEvent();
    void setTempoFromEvent();
    void setTimeSigFromEvent();

    char* printNote(int note);
};

#endif
