#include "event.h"
#include <iostream>
using namespace std;


FretMidiEvent::FretMidiEvent(MidiEvent& event)
: event         (event),
  tick          (event.tick) {

    int commandbyte = event[0];

    switch (commandbyte) {
    case 0x90:
        eventType = NOTE_ON;
        note = (e_notes) event[1];
        break;

    case 0x80:
        eventType = NOTE_OFF;
        note = (e_notes) event[1];
        break;

    case 0xff:
        eventType = META;
        setMetaFromEvent();
        break;


    default:
        cout<< "Unknown commandbyte : "
            << event[0]
            << endl;
        break;
    }
}


void FretMidiEvent::setMetaFromEvent() {
    int metaType = event[1];
    switch (metaType) {
    case 0x01:
        eventType = META_TEXT;
        setTextFromEvent();
        break;
    case 0x03:
        eventType = META_TRACKNAME;
        setTextFromEvent();
        break;
    case 0x51:
        eventType = META_TEMPO_SET;
        setTempoFromEvent();
        break;
    case 0x58:
        eventType = META_TIME_SIG;
        setTimeSigFromEvent();
        break;
    case 0x2f:
        eventType = META_END_OF_TRACK;
        break;
    default:
        cout<< "Unknown meta event : "
            << metaType
            << endl;
        break;
    }
}

void FretMidiEvent::setTextFromEvent() {
    int metaSize = event[2];
    text.clear();
    for (int i = 0; i < metaSize; ++i)
        text+=event[i+3];
}
void FretMidiEvent::setTempoFromEvent() {
    int metaSize = event[2];
    tempo = 0;
    for (int i = 0; i < metaSize; ++i)
        tempo = tempo * 10 + (int)event[i+3];

}
void FretMidiEvent::setTimeSigFromEvent() {
    int metaSize = event[2];
    timeSig = 0;
    for (int i = 0; i < metaSize; ++i)
        timeSig = timeSig * 10 + (int)event[i+3];
}


void FretMidiEvent::print(){
    cout<< "Time="<<tick<<", \t";
    switch(eventType) {
    case NOTE_ON:
        cout<< "NoteOn  "
            << note
            << "\t"
            << printNote(note);
        break;
    case NOTE_OFF:
        cout<< "NoteOff "
            << note
            << "\t"
            << printNote(note);
        break;
    case META_TEXT:
        cout<< "Text "
            << text;
        break;
    case META_TRACKNAME:
        cout<< "TrackName "
            << text;
        break;
    case META_TEMPO_SET:
        cout<< "Set Tempo "
            << tempo;
        break;
    case META_TIME_SIG:
        cout<< "Time Signature"
            << timeSig;
        break;
    case META_END_OF_TRACK:
        cout<< "End Of Track !";
        break;

    case META:
        cout<< "Unknown meta event "
            << endl;
        break;
    default:
        cout<< "TODO";
    }
    cout<<endl;
}


char* FretMidiEvent::printNote(int note) {
    switch (note) {
    case 60:
        return "Easy   A";
        break;
    case 61:
        return "Easy   B";
        break;
    case 62:
        return "Easy   C";
        break;
    case 63:
        return "Easy   D";
        break;
    case 64:
        return "Easy   E";
        break;
    case 72:
        return "Medium A";
        break;
    case 73:
        return "Medium B";
        break;
    case 74:
        return "Medium C";
        break;
    case 75:
        return "Medium D";
        break;
    case 76:
        return "Medium E";
        break;
    case 84:
        return "Hard   A";
        break;
    case 85:
        return "Hard   B";
        break;
    case 86:
        return "Hard   C";
        break;
    case 87:
        return "Hard   D";
        break;
    case 88:
        return "Hard   E";
        break;
    case 96:
        return "Expert A";
        break;
    case 97:
        return "Expert B";
        break;
    case 98:
        return "Expert C";
        break;
    case 99:
        return "Expert D";
        break;
    case 100:
        return "Expert E";
        break;
    default:
        return "ERROR, unknwon note";
        break;
    }
}
