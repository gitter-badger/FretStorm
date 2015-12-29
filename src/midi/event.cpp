#include "event.h"
#include <iostream>
using namespace std;


FretMidiEvent::FretMidiEvent(MidiEvent& event)
: event         (event),
  commandbyte   (event[0]),
  tick          (event.tick),
  note          (event.note) {

}

void FretMidiEvent::print(){
    printHexByte(commandbyte);
    cout << "note " << tick << endl;
}


printHexByte(commandbyte);
int i;

switch (commandbyte & 0xf0) {
case 0x90:
case 0x80:
    printNote(event[1]);
    for (i=1; i<(int)event.size(); i++) {
        cout << " ";
        cout << "'" << (int)event[i];
    }
    break;
default:
    if (commandbyte == 0xff) {
        cout << " ";
        printHexByte(event[1]);
        printMetaEvent(event);

    } else
        for (i=1; i<(int)event.size(); i++) {
            cout << " ";
            printHexByte(event[i]);
        }
}

cout << endl;
