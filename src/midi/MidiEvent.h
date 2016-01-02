#ifndef _MIDIEVENT_H
#define _MIDIEVENT_H

#include <vector>
#include <string>

using namespace std;

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;


enum e_event_type {
    NOTE_ON     =   0x90,
    NOTE_OFF    =   0x80,
    AFTERTOUCH  =   0xA0,
    CONTCHANGE  =   0xB0,
    PROGCHANGE  =   0xC0,
    CHANNPRESS  =   0xD0,
    PITCHWHEEL  =   0xE0,
    META_EVENT  =   0xF0,

    META_TEXT           = 201,
    META_TRACKNAME      = 203,
    META_TEMPO_SET      = 281,
    META_TIME_SIG       = 288,
    META_END_OF_TRACK   = 247
};

#define META_END_OF_TRACK 0x2f

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


class MidiFile;
class MidiTrack;

class MidiEvent {
public:
    MidiEvent               ();
    MidiEvent               (MidiFile& file, MidiTrack& track);

    int     read            (istream& input, int& rwErrorFlag, const MidiEvent* lastEvent);

    void    print           (void);

    int     getAbsTicks     (void);
    bool    isEndOfTrack    (void);
    int     extractMidiData (istream& input, vector<uchar>& array, uchar& runningCommand);

protected:
    int     eventByteLength;
    ulong   deltaTicks;

    e_event_type eventType;
    int          channel;

    // Here, only one group is not NULL
    e_notes note;
    int     velocity;

    int     meta_eventType;


    int pressure;
    int controller;
    int cont_value;
    int program;

    int pitch_low;
    int pitch_high;
    int meta_length;

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

    void printNote(int note);

};


#endif
