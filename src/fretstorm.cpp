#include "scanner/node.hpp"
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
using namespace boost;
using namespace std;

#define PATH "/home/salamandar/FoF/songs/Odino Hero/"

class A {};
class B : public A {};
class C : public A {};

int main(int argc, char const *argv[]) {

    std::vector<A> vec;
    vec.push_back(B());
    vec.push_back(C());

    B instance;
    vec.push_back(instance);

    node root_node(PATH);
    directory root_dir(root_node);
    //root_dir.list_dir();
    cout << root_dir.count_dir_musics(true);

    return 0;
}
