#include <iostream>
#include "Trie.h"

using namespace std;
int main() {
    // TODO: why this didnt work?
    Trie<string> tree = Trie<string>();
    std::cout << tree.empty() << std::endl;
    return 0;
}