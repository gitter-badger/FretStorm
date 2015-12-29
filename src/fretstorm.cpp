#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include <MidiFile.h>

#include "scanner/node.hpp"
#include "midi/midi.h"
#include "midi/song.h"

using namespace boost;
using namespace std;

#define PATH "MusicExamples"
//#define MIDIFILE "/home/salamandar/FoF/songs/Odino Hero/Tier 8/08.3 Seventh Wonder - Alley Cat/notes.mid"
#define MIDIFILE "MusicExamples/Kamelot - Nights of Arabia/notes_orig.mid"


int main(int argc, char const *argv[]) {
    node root_node(PATH);
    directory root_dir(root_node);
    //root_dir.list_dir();
    cout<< "Nombre de musiques dans '" << PATH << "' : "
        << root_dir.count_dir_musics(false)
        << endl;
    cout<< "Nombre de musiques dans '" << PATH << "' (récursivement) : "
        << root_dir.count_dir_musics(true)
        << endl;

    MidiFile midifile(MIDIFILE);
    MidiSong midiSong(MIDIFILE);
//    printMidiFile(midifile);

    midiSong.print();



    return 0;
}
