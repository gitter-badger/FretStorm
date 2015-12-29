#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include <MidiFile.h>

#include "scanner/node.hpp"
#include "midi/midi.h"

using namespace boost;
using namespace std;

#define PATH "MusicExamples"
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

    cout<< "nombre de tracks dans '" << MIDIFILE << "' : "
        << midifile.getTrackCount()
        << endl;

    printMidiFile(midifile);


    return 0;
}
