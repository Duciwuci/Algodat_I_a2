#include <iostream>
#include "Trie.h"

using namespace std;
int main() {
    // TODO: why this didnt work?
    Trie<basic_string<string>> *tree = Trie<string>();
    std::cout << "Trie erstellt" << std::endl;
    return 0;
}