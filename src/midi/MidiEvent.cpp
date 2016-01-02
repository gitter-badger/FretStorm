#include <iostream>

#include "MidiEvent.h"
#include "MidiFile.h"
#include "BinUtils.h"

using namespace std;


MidiEvent::MidiEvent() {
/*
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
    */
}

MidiEvent::MidiEvent(MidiFile&, MidiTrack&) {

}



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


    //cout << "eventtype 0x" <<hex << eventType;

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
        meta_eventType = BinUtils::readByte(input);
        meta_length    = BinUtils::readVLV(input, &countsize);
    //    cout<< " metaType 0x"   << hex << meta_eventType
    //        << " size "         << dec << meta_length       << " ";

        // TODO replace here
        for (int i=0; i<meta_length; i++) {
            //cout <<
            text +=(char)BinUtils::readByte(input);
        }
        switch (meta_eventType) {
        case 0x00:      // Sequence number
        case 0x01:      // Text Event
        case 0x02:      // Copyright Notice
        case 0x03:      // Sequence or track name
        case 0x04:      // Instrument name
        case 0x05:      // Lyric text
        case 0x06:      // Marker text
        case 0x07:      // Cue point
        case 0x20:      // MIDI channel prefix assignment
        case 0x2F:      // End of track
        case 0x51:      // Tempo Setting
        case 0x54:      // SMPTE offset
        case 0x58:      // Time signature
        case 0x59:      // Key signature
        case 0x7F:      // Sequencer specific event
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
    //cout << endl;

    return 0;
}

/*
        case 0x0f:                 // meta event
            byte = BinUtils::readByte(input); // meta type
            array.push_back(byte);

            metai = BinUtils::readByte(input); // meta type
            array.push_back(metai);
            for (uchar j=0; j<metai; j++) {
                byte = BinUtils::readByte(input); // meta type
                array.push_back(byte);
            }
            break;
            // The 0xf0 and 0xf7 meta commands deal with system-exclusive
            // messages. 0xf0 is used to either start a message or to store
            // a complete message.  The 0xf0 is part of the outgoing MIDI
            // bytes.  The 0xf7 message is used to send arbitrary bytes,
            // typically the middle or ends of system exclusive messages.  The
            // 0xf7 byte at the start of the message is not part of the
            // outgoing raw MIDI bytes, but is kept in the MidiFile message
            // to indicate a raw MIDI byte message (typically a partial
            // system exclusive message).
        case 0x07:                // Raw bytes. 0xf7 is not part of the raw
            // bytes, but are included to indicate
            // that this is a raw byte message.
        case 0x00:                // System Exclusive message
                                  // (complete, or start of message).
            int length = BinUtils::readVLV(input, NULL);
            for (int i=0; i<length; i++) {
                byte = BinUtils::readByte(input);
                array.push_back(byte);
            }
            break;
            // other "F" MIDI commands are not expected, but can be
            // handled here if they exist.
*/

void MidiEvent::print(){
    cout<< "Time="<<tick<<", \t";

    switch (eventType & 0xF0) {
    case NOTE_ON:
        cout<< "NoteOn  "   << note
            << "\t";
        printNote(note);
        break;
    case NOTE_OFF:
        cout<< "NoteOff "   << note
            << "\t";
        printNote(note);
        break;
    case AFTERTOUCH:
        cout<< "NoteOff "   << note
            << "\t";
        printNote(note);
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


void MidiEvent::printNote(int note) {
    switch (note) {
    case 60:
        cout << "Easy   A";
        break;
    case 61:
        cout << "Easy   B";
        break;
    case 62:
        cout << "Easy   C";
        break;
    case 63:
        cout << "Easy   D";
        break;
    case 64:
        cout << "Easy   E";
        break;
    case 72:
        cout << "Medium A";

        break;
    case 73:
        cout << "Medium B";
        break;
    case 74:
        cout << "Medium C";
        break;
    case 75:
        cout << "Medium D";
        break;
    case 76:
        cout << "Medium E";
        break;
    case 84:
        cout << "Hard   A";
        break;
    case 85:
        cout << "Hard   B";
        break;
    case 86:
        cout << "Hard   C";
        break;
    case 87:
        cout << "Hard   D";
        break;
    case 88:
        cout << "Hard   E";
        break;
    case 96:
        cout << "Expert A";
        break;
    case 97:
        cout << "Expert B";
        break;
    case 98:
        cout << "Expert C";
        break;
    case 99:
        cout << "Expert D";
        break;
    case 100:
        cout << "Expert E";
        break;
    default:
        cout << "ERROR, unknwon note";
        break;
    }
}



bool MidiEvent::isEndOfTrack() {
    return ((eventType & 0xf0) == META_EVENT && meta_eventType == META_END_OF_TRACK);
}

int MidiEvent::getAbsTicks() {
    return tick;
}


