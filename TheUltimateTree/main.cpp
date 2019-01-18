#include <iostream>
#include "Trie.h"
#include <string>

void addWord(Trie<string> * tree);

void findWord(Trie<string> * tree);

void iterateAll(Trie<string> * tree);

void listMenu();

using namespace std;
int main() {
    Trie<string> tree;
    pair<string, string> toAdd = pair<string, string>("sind", "are");

    pair<string, string> toAdd2 = pair<string, string>("weis", "know");
    pair<string, string> toAdd3 = pair<string, string>("wer", "who");
    pair<string, string> toAdd4 = pair<string, string>("wir", "we");
    pair<string, string> toAdd5 = pair<string, string>("wird", "will");
    pair<string, string> toAdd6 = pair<string, string>("wo", "where");
    pair<string, string> toAdd7 = pair<string, string>("test","test");
    pair<string, string> toAdd8 = pair<string, string>("hallo","hello");
    pair<string, string> toAdd9 = pair<string, string>("schoen","nice");

    tree.insert(toAdd2);
    tree.insert(toAdd3);
    tree.insert(toAdd);
    tree.insert(toAdd6);
    tree.insert(toAdd4);
    tree.insert(toAdd5);
    tree.insert(toAdd8);
    tree.insert(toAdd9);
    tree.insert(toAdd7);
    std::string answer = "";
    while (answer != "5") {
        std::cout << "Was wollen Sie tun? (Menüpunkte --> 0)" << std::endl;

        std::cin >> answer;

        switch (std::stoi(answer)) {
            case 0: listMenu();
                break;
            case 1: addWord(&tree);
                break;
            case 2: findWord(&tree);
                break;
            case 5: break;
            default: std::cout << answer << " ist kein Menüpunkt!";
        }
    }
    return 0;
}

void addWord(Trie<string> * tree) {
    string key;
    string word;

    std::cout << "Eingabe des deutschen Worts" << std::endl;
    std::cin >> key;
    std::cout << "Übersetzung" << std::endl;
    std::cin >> word;

    pair<string, string> element = pair<string, string>(key, word);
    tree->insert(element);
    std::cout << key << " mit Übersetzung: " << word << " wurde hinzugefügt." << std::endl;
}

void findWord(Trie<string> * tree) {
    string key;

    std::cout << "Welches Wort soll übersetzt werden?" << std::endl;
    std::cin >> key;
    auto it = tree->find(key);
    if (it == tree->end()) {
        std::cout << "Es tut mir leid, aber ich kann für " << key << " leider keine Übersetzung finden." << std::endl;
    } else {
        std::cout << key << " übersetzt bedeutet: " << *it << std::endl;
    }
}

void iterateAll(Trie<string> * tree) {
    for (auto i = tree->begin(); i != tree->end(); ++i) {
        std::cout << *i << std::endl;
    }
}

void listMenu() {
    std::cout << "Menü:" << std::endl;
    std::cout << " 0: Menü" << std::endl;
    std::cout << " 1: Wort hinzufügen" << std::endl;
    std::cout << " 2: Suchen einer Übersetzung" << std::endl;
    std::cout << " 5: Beenden" << std::endl;
}
