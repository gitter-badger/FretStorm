#include "scanner/node.hpp"
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
using namespace boost;
using namespace std;

#define PATH "/home/salamandar/FoF/songs/Odino Hero/Tier 1"

int main(int argc, char const *argv[]) {


    node root_node(PATH);
    directory root_dir(root_node);
    //root_dir.list_dir();
    cout << root_dir.count_dir_musics(false) << endl;

    return 0;
}
