#include <iostream>
#include "Trie.h"
#include <string>

using namespace std;
int main() {
    Trie<string> tree = Trie<string>();
    std::cout << tree.empty() << std::endl;
    // TODO: refactor the bug
    pair<string, string> toAdd = pair<string, string>("Hallo", "Welt");
    tree.insert(toAdd);
    return 0;
}