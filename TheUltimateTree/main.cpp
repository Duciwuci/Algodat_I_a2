#include <iostream>
#include "Trie.h"
#include <string>

void addWord(Trie<string> * tree);

void findWord(Trie<string> * tree);

void iterateAll(Trie<string> * tree);

void eraseWord(Trie<string> * tree);

void writeTree(Trie<string> * tree);

void clearTree(Trie<string> * tree);

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
    pair<string, string> toAdd9 = pair<string, string>("schoen","beautiful");

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

    int key;
    while (answer != "7") {
        std::cout << "Was wollen Sie tun? (Menüpunkte --> 0)" << std::endl;

        std::cin >> answer;

        try {
            key = std::stoi(answer);
        } catch (std::invalid_argument& e) {
            std::cout << answer << " ist kein Menüpunkt!" << std::endl;
            continue;
        }

        switch (key) {
            case 0: listMenu();
                break;
            case 1: addWord(&tree);
                break;
            case 2: findWord(&tree);
                break;
            case 3: eraseWord(&tree);
                break;
            case 4: writeTree(&tree);
                break;
            case 5: clearTree(&tree);
                break;
            case 6: iterateAll(&tree);
                break;
            case 7: break;
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

void eraseWord(Trie<string> * tree) {
    string key;
    std::cout << "Welches Wort soll gelöscht werden?" << std::endl;
    std::cin >> key;
    if (tree->find(key) == tree->end()) {
        std::cout << "Das Wort '" << key << "' ist nicht im Wörterbuch vorhanden.";
        return;
    }
    tree->erase(key);
    std::cout << key << " wurde aus dem Wörterbuch gelöscht.";
}

void iterateAll(Trie<string> * tree) {
    if (tree->begin() == tree->end()) {
        std::cout << "Das Wörterbuch ist leer" << std::endl;
    }
    for (auto i = tree->begin(); i != tree->end(); ++i) {
        std::cout << *i << std::endl;
    }
}

void writeTree(Trie<string> * tree) {
    if (tree->begin() == tree->end()) {
        std::cout << "Das Wörterbuch ist leer." << std::endl;
        return;
    }
    tree->output();
}

void clearTree(Trie<string> * tree) {
    tree->clear();
    std::cout << "Das Wörterbuch wurde geleert." << std::endl;
}

void listMenu() {
    std::cout << "Menü:" << std::endl;
    std::cout << " 0: Menü" << std::endl;
    std::cout << " 1: Wort hinzufügen" << std::endl;
    std::cout << " 2: Suchen einer Übersetzung" << std::endl;
    std::cout << " 3: Entfernen einen Wortes" << std::endl;
    std::cout << " 4: Ausgabe des kompletten Baum in primtiver Ansicht" << std::endl;
    std::cout << " 5: Leeren des Wörterbuchs" << std::endl;
    std::cout << " 6: Ausgabe aller English Wörtern" << std::endl;
    std::cout << " 7: Beenden" << std::endl;
}
