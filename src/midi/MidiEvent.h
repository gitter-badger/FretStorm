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
    META_EVENT  =   0xF0
};

enum e_meta_event_type {
    META_SEQUENCE_NUMBER    = 0x00,      // Sequence number
    META_TEXT_EVENT         = 0x01,      // Text Event
    META_COPYRIGHT          = 0x02,      // Copyright Notice
    META_TRACK_NAME         = 0x03,      // Sequence or track name
    META_INSTRUMENT_NAME    = 0x04,      // Instrument name
    META_LYRIC_TEXT         = 0x05,      // Lyric text
    META_MARKER_TEXT        = 0x06,      // Marker text
    META_CUE_POINT          = 0x07,      // Cue point
    META_CHANN_PREFIX       = 0x20,      // MIDI channel prefix assignment
    META_END_OF_TRACK       = 0x2F,      // End of track
    META_TEMPO_SET          = 0x51,      // Tempo Setting
    META_SMPTE_OFFSET       = 0x54,      // SMPTE offset
    META_TIME_SIG           = 0x58,      // Time signature
    META_KEY_SIG            = 0x59,      // Key signature
    META_SEQ_SPEC_EVENT     = 0x7F       // Sequencer specific event

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
    long    deltaTicks;

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
