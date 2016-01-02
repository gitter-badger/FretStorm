#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include <MidiFile.h>

#include "scanner/node.hpp"
#include "midi/MidiFile.h"
#include "midi/BinUtils.h"

using namespace boost;
using namespace std;

#define PATH "MusicExamples"
#define MIDIFILE "/home/salamandar/FoF/songs/Odino Hero/Tier 8/08.3 Seventh Wonder - Alley Cat/notes.mid"
//#define MIDIFILE "MusicExamples/Kamelot - Nights of Arabia/notes_orig.mid"
//#define MIDIFILE "/home/salamandar/FoF/NewSongs/Kamelot - Center of the universe/notes.mid"
string filename;


int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " [-|midifile]" << endl;
        exit(0);
    } else {
        char arg = *argv[1];
        if (arg == '-')
            filename = MIDIFILE;
        else
            filename = argv[1];
    }

    node root_node(PATH);
    directory root_dir(root_node);
    //root_dir.list_dir();
    cout<< "Nombre de musiques dans '" << PATH << "' : "
        << root_dir.count_dir_musics(false)
        << endl;
    cout<< "Nombre de musiques dans '" << PATH << "' (récursivement) : "
        << root_dir.count_dir_musics(true)
        << endl;

    MidiFile midifile(&filename);
    midifile.print();
//    MidiSong midiSong(filename);
//    midiSong.print();

//    printMidiFile(midifile);
/*
    uchar bytes[5];
    BinUtils::writeVLV(bytes, 0x08000000);
    BinUtils::printVLV(bytes);
    uchar bytes2[5];
    BinUtils::writeVLV(bytes2, 137);
    BinUtils::printVLV(bytes2);
    uchar bytes3[5];
    BinUtils::writeVLV(bytes3, 0x00003FFF);
    BinUtils::printVLV(bytes3);
*/

    return 0;
}
