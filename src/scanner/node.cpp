#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "node.hpp"
#include <iostream>
using namespace std;
#include <boost/filesystem.hpp>
using namespace boost;


bool node::is_a_directory() {
    return exists(node_path) && is_directory(node_path);
}

bool node::contains_song_ini() {
    filesystem::path
        song_ini("song.ini"),
        sub_song_ini = node_path / "song.ini";

    if (exists(node_path) && is_directory(node_path)) {
        return (exists(node_path/"song.ini") && is_regular_file(node_path/"song.ini"))
            || (exists(node_path/"Song.ini") && is_regular_file(node_path/"Song.ini"));
    }
    return false;
}

bool node::is_a_trackdir() {
    return contains_song_ini();
}

void directory::list_dir(int indent, bool recursive) {
    if (exists(this->node_path) && is_directory(this->node_path)){
        //cout << node_path.string() << endl;

        typedef vector<filesystem::path> vec;
        vec v;

        copy(filesystem::directory_iterator(node_path), filesystem::directory_iterator(), back_inserter(v));

        sort(v.begin(), v.end());

        for (vec::const_iterator it (v.begin()); it != v.end(); ++it){
            for (int i = 0; i <= indent; ++i)
                cout << "| ";
            cout << (*it).filename().string();

            if (is_directory(*it)) {
                directory this_is_a_dir(*it);

                if (this_is_a_dir.is_a_trackdir()) {
                    cout << " : Musique" << endl;
                }else {
                    cout <<"/" << endl;
                    this_is_a_dir.list_dir(indent+1);
                    for (int i = 0; i <= indent; ++i)
                        cout << "| ";
                    cout << "‾‾";
                    cout << endl;
                }

            }
            else
                cout << endl;
        }
    }

}

// We may add int depth to control the recursive depth
int directory::count_dir_musics(bool recursive) {
    int count = 0;
    if (exists(this->node_path) && is_directory(this->node_path))
        for(filesystem::directory_iterator it(this->node_path); it != filesystem::directory_iterator(); ++it)
            if (is_directory(*it)) {
                directory subdir(*it);
                if (subdir.contains_song_ini()) {
                    count++;
                } else if(recursive) {
                    count+=subdir.count_dir_musics(true);
                }
            }

    return count;
}
