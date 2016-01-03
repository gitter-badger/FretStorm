#include <iostream>

#include "BinUtils.h"
#include "MidiTrack.h"
#include "MidiFile.h"

using namespace std;

MidiTrack::MidiTrack(MidiFile& file)
: midiFileRef(file){
    midiFileName = midiFileRef.getFilename();
}


int MidiTrack::read(istream& input, int& rwErrorFlag) {

    readHeader(input, rwErrorFlag);

    MidiEvent*  midiEvent;
    MidiEvent*  lastEvent = new MidiEvent();

    do {
        midiEvent = new MidiEvent(midiFileRef, *this);

        if (midiEvent->read(input, rwErrorFlag, lastEvent)) {
            return rwErrorFlag;
        }

        lastEvent = midiEvent;

        events.push_back(midiEvent);
        trackLength++;
    } while(!midiEvent->isEndOfTrack());

    return 0;
}

int MidiTrack::readHeader(istream& input, int& rwErrorFlag) {
    if (BinUtils::checkFoundChar(input.get(), 'M', &midiFileName))
        return (rwErrorFlag = 1);
    if (BinUtils::checkFoundChar(input.get(), 'T', &midiFileName))
        return (rwErrorFlag = 1);
    if (BinUtils::checkFoundChar(input.get(), 'r', &midiFileName))
        return (rwErrorFlag = 1);
    if (BinUtils::checkFoundChar(input.get(), 'k', &midiFileName))
        return (rwErrorFlag = 1);

    // Now read track chunk size and throw it away because it is
    // not really necessary since the track MUST end with an
    // end of track meta event, and many MIDI files found in the wild
    // do not correctly give the track size.
    trackChunkSize = (int) BinUtils::readLittleEndian4Bytes(input);

    return 0;
}

void MidiTrack::print() {
    cout << "+M +T +r +k\t\t\t; Track chunk marker" << endl;
    // print number of bytes in track
    cout<< "4'"
        << trackChunkSize
        << "\t\t\t\t; number of bytes to follow in track"
        << endl;

    // print the list of events in the track
    for (int i = 0; i < trackLength; ++i) {
        events[i]->print();
    }
}


//////////////////////////////
//
// MidiEventList::linkNotePairs -- Match note-ones and note-offs together
//   There are two models that can be done if two notes are overlapping
//   on the same pitch: the first note-off affects the last note-on,
//   or the first note-off affects the first note-on.  Currently  the
//   first note-off affects the last note-on, but both methods could
//   be implemented with user selectability.  The current state of the
//   track is assumed to be in time-sorted order.  Returns the number
//   of linked notes (note-on/note-off pairs).
//

int linkNotePairs(void) {
/*
    // dimension 1: MIDI channel (0-15)
    // dimension 2: MIDI key     (0-127)  (but 0 not used for note-ons)
    // dimension 3: List of active note-ons or note-offs.
    vector< vector< vector<MidiEvent*> > > noteons;
    noteons.resize(16);
    for (int i = 0; i < noteons.size(); ++i) {
        noteons[i].resize(128);
    }

    // Now iterate through the MidiEventList keeping track of note
    // states and linking notes as needed.
    int channel;
    int key;
    int counter = 0;
    MidiEvent* midiEvent;
    MidiEvent* noteon;

    for (int i = 0; i < trackLength; ++i) {
        midiEvent = events[i];
        midiEvent->unlinkEvent();
        if (midiEvent->) {
            // store the note-on to pair later with a note-off message.
            key = midiEvent->getKeyNumber();
            channel = midiEvent->getChannel();
            noteons[channel][key].push_back(midiEvent);
        } else if (midiEvent->isNoteOff()) {
            key = midiEvent->getKeyNumber();
            channel = midiEvent->getChannel();
            if (noteons[channel][key].size() > 0) {
                noteon = noteons[channel][key].back();
                noteons[channel][key].pop_back();
                noteon->linkEvent(midiEvent);
                counter++;
            }
        }
    }
    return counter;
*/
    return 0;
}
