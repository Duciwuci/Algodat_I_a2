#include <iostream>
#include "Trie.h"
#include <string>

using namespace std;
int main() {
    Trie<string> tree = Trie<string>();
    pair<string, string> toAdd = pair<string, string>("abcd", "Welt");

    pair<string, string> toAdd2 = pair<string, string>("abcdf", "Welt");

    tree.insert(toAdd);
    /*
    std::cout << tree.empty() << std::endl;
    tree.erase("abcd");
    std::cout << tree.empty() << std::endl;
    tree.insert(toAdd);
    tree.insert(toAdd2);

    cout << "find " << tree.find("abcdf").getValue() << endl;


    tree.erase("abcdf");

    std::cout << tree.empty() << std::endl;
    tree.erase("abcd");
    std::cout << tree.empty() << std::endl;

*/
    return 0;
}
