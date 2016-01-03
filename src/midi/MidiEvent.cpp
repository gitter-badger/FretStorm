#include <iostream>

#include "MidiEvent.h"
#include "MidiFile.h"
#include "BinUtils.h"

using namespace std;


MidiEvent::MidiEvent()
:   eventByteLength(0),
    deltaTicks(0),
    tick(0),
    seconds(0){ }

MidiEvent::MidiEvent(MidiFile&, MidiTrack&)
: MidiEvent() { }


int MidiEvent::read(istream& input, int& rwErrorFlag, const MidiEvent* lastEvent) {
    int countsize = 0;

    // Get Delta Ticks, always present
    deltaTicks = BinUtils::readVLV(input, &eventByteLength);
    if (deltaTicks == -1)
        return (rwErrorFlag = 1);

    if (lastEvent != NULL)
        tick = lastEvent->tick + deltaTicks;


    if (input.peek() < 0x80) {
        eventType   = lastEvent->eventType;
        channel     = lastEvent->channel;
    }
    else {
        eventType   = (e_event_type)input.get();
        channel     = (eventType & 0x0f);
    }

    switch (eventType & 0xf0) {
    case NOTE_OFF:      // note off           (2 more bytes)
    case NOTE_ON:       // note on            (2 more bytes)
        note        = (e_notes)BinUtils::readByte(input);
        velocity    = BinUtils::readByte(input);
        break;
    case AFTERTOUCH:    // aftertouch         (2 more bytes)
        note        = (e_notes)BinUtils::readByte(input);
        pressure    = BinUtils::readByte(input);
        break;
    case CONTCHANGE:    // cont. controller   (2 more bytes)
        controller  = BinUtils::readByte(input);
        cont_value  = BinUtils::readByte(input);
        break;
    case PROGCHANGE:    // patch change       (1 more byte)
        program     = BinUtils::readByte(input);
        break;
    case CHANNPRESS:    // channel pressure   (1 more byte)
        pressure    = BinUtils::readByte(input);
        break;
    case PITCHWHEEL:    // pitch wheel        (2 more bytes)
        pitch_low   = BinUtils::readByte(input);
        pitch_high  = BinUtils::readByte(input);
        break;
    case META_EVENT:
        if ((eventType == 0xf0) || (eventType == 0xf7))
            while (BinUtils::readByte(input) != 0xf7) {}

        meta_eventType = BinUtils::readByte(input);
        meta_length    = BinUtils::readVLV(input, &countsize);

        // TODO replace here
        for (int i=0; i<meta_length; i++)
            text +=(char)BinUtils::readByte(input);

        switch (meta_eventType) {
        case META_SEQUENCE_NUMBER:  // Sequence number
        case META_TEXT_EVENT:       // Text Event
        case META_COPYRIGHT:        // Copyright Notice
        case META_TRACK_NAME:       // Sequence or track name
        case META_INSTRUMENT_NAME:  // Instrument name
        case META_LYRIC_TEXT:       // Lyric text
        case META_MARKER_TEXT:      // Marker text
        case META_CUE_POINT:        // Cue point
        case META_CHANN_PREFIX:     // MIDI channel prefix assignment
        case META_END_OF_TRACK:     // End of track
        case META_TEMPO_SET:        // Tempo Setting
        case META_SMPTE_OFFSET:     // SMPTE offset
        case META_TIME_SIG:         // Time signature
        case META_KEY_SIG:          // Key signature
        case META_SEQ_SPEC_EVENT:   // Sequencer specific event
            break;
        default:
            cout << "Unknown meta type 0x" << meta_eventType << endl;
            return 1;
        }
        break;
    default:
        cout << "Error reading midifile" << endl;
        cout << "Command byte was " << (int)eventType << endl;
        return 0;
    }

    return 0;
}


void MidiEvent::print(){
    cout<< "Time="<<tick<<", \t";

    switch (eventType & 0xF0) {
    case NOTE_ON:
        cout<< "NoteOn  "   << note
            << "\t"
            << printNote(note);
        break;
    case NOTE_OFF:
        cout<< "NoteOff "   << note
            << "\t"
            << printNote(note);
        break;
    case AFTERTOUCH:
        cout<< "Aftertouch "<< note
            << "\t"
            << printNote(note);
        break;
    case CONTCHANGE:
        cout<< "Control Change " << controller << " to " << cont_value;
        break;
    case PROGCHANGE:
        cout<< "Program Change " << program;
        break;
    case CHANNPRESS:
        cout<< "Channel Pressure " << pressure;
        break;
    case PITCHWHEEL:
        cout<< "Pitch Wheel " << pitch_low << " " << pitch_high;
        break;
    case META_EVENT:
        switch (meta_eventType) {
        case 0x00:      // Sequence number
            break;
        case 0x01:      // Text Event
            cout<< "Text " << text;
            break;
        case 0x02:      // Copyright Notice
            break;
        case 0x03:      // Sequence or track name
            cout<< "TrackName " << text;
            break;
        case 0x04:      // Instrument name
            break;
        case 0x05:      // Lyric text
            break;
        case 0x06:      // Marker text
            break;
        case 0x07:      // Cue point
            break;
        case 0x20:      // MIDI channel prefix assignment
            break;
        case 0x2F:      // End of track
            cout<< "End Of Track !";
            break;
        case 0x51:      // Tempo Setting
            cout<< "Set Tempo " << tempo;
            break;
        case 0x54:      // SMPTE offset
            break;
        case 0x58:      // Time signature
            cout<< "Time Signature" << timeSig;
            break;
        case 0x59:      // Key signature
            break;
        case 0x7F:      // Sequencer specific event
            break;
        default:
            cout << "Unknown meta type 0x" << meta_eventType << endl;
            break;
        }
        break;
    default:
        cout<< "TODO";
        break;
    }
    cout << endl;
}


const string MidiEvent::printNote(int note) {
    switch (note) {
    case 60:    return "Easy   A";
    case 61:    return "Easy   B";
    case 62:    return "Easy   C";
    case 63:    return "Easy   D";
    case 64:    return "Easy   E";

    case 72:    return "Medium A";
    case 73:    return "Medium B";
    case 74:    return "Medium C";
    case 75:    return "Medium D";
    case 76:    return "Medium E";

    case 84:    return "Hard   A";
    case 85:    return "Hard   B";
    case 86:    return "Hard   C";
    case 87:    return "Hard   D";
    case 88:    return "Hard   E";

    case 96:    return "Expert A";
    case 97:    return "Expert B";
    case 98:    return "Expert C";
    case 99:    return "Expert D";
    case 100:   return "Expert E";

    default:    return "ERROR, unknown note";
    }
}



bool MidiEvent::isEndOfTrack() {
    return ((eventType & 0xf0) == META_EVENT && meta_eventType == META_END_OF_TRACK);
}

int MidiEvent::getAbsTicks() {
    return tick;
}


