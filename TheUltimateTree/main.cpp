#include <iostream>
#include "Trie.h"
#include <string>

using namespace std;
int main() {
    Trie<string> tree = Trie<string>();
    pair<string, string> toAdd = pair<string, string>("gbfd", "Welt");
    tree.insert(toAdd);
    std::cout << tree.empty() << std::endl;
    return 0;
}
