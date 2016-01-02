#ifndef _MIDIFILE_H
#define _MIDIFILE_H

#include <vector>
#include <istream>
#include <fstream>

#include "MidiTrack.h"

using namespace std;

#define TIME_STATE_DELTA       0
#define TIME_STATE_ABSOLUTE    1

#define TRACK_STATE_SPLIT      0
#define TRACK_STATE_JOINED     1

class _TickTime {
public:
    int    tick;
    double seconds;
};


class MidiFile {
public:
    MidiFile                    (void);
    MidiFile                    (const string* aFile);
    MidiFile                    (const char* filename);
    MidiFile                    (istream& input);
    ~MidiFile                   ();

    static string getName();
    void print();
    void printMidiHeader();

    // writing functions:
    int     write                   (const char* aFile);
    int     write                   (const string& aFile);
    int     write                   (ostream& out);
    int     writeHex                (const char* aFile,   int width = 25);
    int     writeHex                (const string& aFile, int width = 25);
    int     writeHex                (ostream& out,        int width = 25);
    int     writeBinasc             (const char* aFile);
    int     writeBinasc             (const string& aFile);
    int     writeBinasc             (ostream& out);
    int     status                  (void);


    // track-related functions
    int     getTrackCount           (void);
    MidiTrack*  getTrack            (int number);
    MidiTrack*  operator[]          (int number) { return getTrack(number); }

      // join/split track functionality:
    void      joinTracks                (void);
    void      splitTracks               (void);
    int       getTrackState             (void);
    int       hasJoinedTracks           (void);
    int       hasSplitTracks            (void);
    int       getSplitTrack             (int track, int index);
    int       getSplitTrack             (int index);

   // void      sortTrack                 (MidiEventList& trackData);
    void      sortTracks                (void);

    int       addTrack                  (void);
    int       addTrack                  (int count);
    void      deleteTrack               (int aTrack);
    void      mergeTracks               (int aTrack1, int aTrack2);
    int       getTrackCountAsType1      (void);

    int       getEventCount             (int aTrack);
    void      allocateEvents            (int track, int aSize);
    int       getNumEvents              (int aTrack);

      // tick-related functions:
    void      deltaTicks                (void);
    void      absoluteTicks             (void);
    int       getTickState              (void);
    int       isDeltaTicks              (void);
    int       isAbsoluteTicks           (void);

      // ticks-per-quarter related functions:
    void      setMillisecondTicks       (void);
    int       getTicksPerQuarterNote    (void);
    int       getTPQ                    (void);
    void      setTicksPerQuarterNote    (int ticks);
    void      setTPQ                    (int ticks);

      // physical-time analysis functions:
    void      doTimeAnalysis            (void);
    double    getTimeInSeconds          (int aTrack, int anIndex);
    double    getTimeInSeconds          (int tickvalue);
    int       getAbsoluteTickTime       (double starttime);

      // note-analysis functions:
    int     linkNotePairs             (void);
    void      clearLinks                (void);

      // filename functions:
    void      setFilename               (const char* aname);
    void      setFilename               (const string& aname);
    const string getFilename             (void);


protected:
    // read/write error flag
    int rwErrorFlag;

    // Header Data
    ulong   headerSize;
    ushort  formatType;
    ushort  trackCountInHeader;

    // General
    string  filename;
    int     theTrackState;          // joined or split
    int     theTimeState;           // absolute or delta

    int     ticksPerQuarterNote;    // time base of file

    // Tracks
    vector<MidiTrack*>  tracks;
    int     trackCount;             // # of tracks in file TODO useful ?
    int     noteTrackCount;


    // reading functions:
    int     read                    ();
    int     read                    (istream& istream);
    int     readHeader              (istream& input);



};





#endif /* _MIDIFILE_H */
