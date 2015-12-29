#include <iostream>
#include "track.h"

using namespace std;

MidiTrack::MidiTrack(MidiFile& midiFile, int identifiant)
: trackBytes(getTrackByteCount(midiFile, identifiant)),
  trackLength(midiFile.getEventCount(identifiant)),
  events(midiFile[identifiant]) {
    initEvents();

}

void MidiTrack::simpleSearchForTitle() {

}

void MidiTrack::initEvents() {
    for (int i = 0; i < trackLength; ++i) {
        eventList.push_back(new FretMidiEvent(
            events[i]));
    }

}

void MidiTrack::print() {
    cout << "+M +T +r +k\t\t\t; Track chunk marker" << endl;
    // print number of bytes in track
    cout<< "4'"
        << trackBytes
        << "\t\t\t\t; number of bytes to follow in track"
        << endl;

    // print the list of events in the track
    for (int i = 0; i < trackLength; ++i) {
        eventList[i]->print();
    }

}

//////////////////////////////
//
// getTrackByteCount -- number of by the track after the track header.
//    Might need to keep track of End-of-track meta message.
//

int MidiTrack::getTrackByteCount(MidiFile& midifile, int track) {
    int sum = 0;
    int i;
    int eventcount = midifile.getEventCount(track);
    MidiEvent event;

    for (i=0; i<eventcount; i++) {
        event = midifile.getEvent(track, i);
        sum += getVlvSize(event.tick);
        sum += event.size();
    }
    return sum;
}

//////////////////////////////
//
// getVlvSize -- return the number of bytes in the VLV format for the
//    integer.
//

int MidiTrack::getVlvSize(int value) {
    if (value < 0x80) {
        return 1;
    } if (value < 0x4000) {
        return 2;
    } else if (value < 0x200000) {
        return 3;
    } else if (value < 0x10000000) {
        return 4;
    } else {
        return 5;
    }
}
