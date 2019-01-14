#include <iostream>
#include "Trie.h"
#include <string>

using namespace std;
int main() {
    Trie<string> tree = Trie<string>();
    pair<string, string> toAdd = pair<string, string>("Welt", "World");

    pair<string, string> toAdd2 = pair<string, string>("Wel", "Wooorld");

    tree.insert(toAdd);
    tree.insert(toAdd2);

    auto bla = tree.find("Welt");
    auto blub = tree.find("Wel");

    tree.insert(toAdd2);

    std::cout << bla.operator*() << std::endl;
    std::cout << blub.operator*() << std::endl;


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
