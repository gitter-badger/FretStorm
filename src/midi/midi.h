#include <MidiFile.h>

typedef unsigned char uchar;

void    printMidiFile         (MidiFile& midifile);
void    printMidiHeader         (MidiFile& midifile);
void    printTrack              (MidiFile& midifile, int track);
int     getVlvSize              (int value);
int     getTrackByteCount       (MidiFile& midifile, int track);
void    printMidiEvent          (MidiEvent& event);
void    printNote               (int note);
void    printMetaEvent          (MidiEvent& event);
void    printHexByte            (int value);
void    usage                   (const char* command);
void    example                 (void);
