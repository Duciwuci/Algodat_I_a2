#include <iostream>
#include "Trie.h"
#include <string>

using namespace std;
int main() {
    Trie<string> tree;
    pair<string, string> toAdd = pair<string, string>("sind", "are");

    pair<string, string> toAdd2 = pair<string, string>("weis", "know");
    pair<string, string> toAdd3 = pair<string, string>("wer", "who");
    pair<string, string> toAdd4 = pair<string, string>("wir", "we");
    pair<string, string> toAdd5 = pair<string, string>("wird", "will");
    pair<string, string> toAdd6 = pair<string, string>("wo", "where");

    tree.insert(toAdd);
    tree.insert(toAdd2);
    tree.insert(toAdd3);
    tree.insert(toAdd4);
    tree.insert(toAdd5);
    /*tree.insert(toAdd6);

    */auto it = tree.begin();
    std::cout << *it << std::endl;
    ++it;
    --it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << *it << std::endl;
    ++it;
    std::cout << it.operator*() << std::endl;
    /*it.operator++();
    std::cout << it.operator*() << std::endl;
    it.operator++();
    std::cout << it.operator*() << std::endl;


    auto bla = tree.find("sind");
    //auto blub = tree.find("Wird");

    std::cout << bla.operator*() << std::endl;
    bla = tree.find("weis");
    std::cout << bla.operator*() << std::endl;
    bla = tree.find("wer");
    std::cout << bla.operator*() << std::endl;
    bla = tree.find("wir");
    std::cout << bla.operator*() << std::endl;
    bla = tree.find("wird");
    std::cout << bla.operator*() << std::endl;
    bla = tree.find("wo");
    std::cout << bla.operator*() << std::endl;
 */
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