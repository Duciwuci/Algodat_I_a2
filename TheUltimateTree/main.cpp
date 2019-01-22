#include <iostream>
#include "Trie.h"
#include <string>
#include <vector>
#include <queue>

void addWord(Trie<string> * tree);

void findWord(Trie<string> * tree);

void iterateAll(Trie<string> * tree);

void eraseWord(Trie<string> * tree);

void writeTree(Trie<string> * tree);

void clearTree(Trie<string> * tree);

void lowerAndUpperBound(Trie<string> * tree);

void listMenu();

void DucÜbung();

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

    string answer = "";

    int key;
    while (answer != "8") {
        cout << "Was wollen Sie tun? (Menüpunkte --> 0)" << endl;

        cin >> answer;

        try {
            key = std::stoi(answer);
        } catch (std::invalid_argument& e) {
            cout << answer << " ist kein Menüpunkt!" << endl;
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
            case 7: lowerAndUpperBound(&tree);
                break;
            case 8: break;
            case 9: DucÜbung();
                break;
            default: cout << answer << " ist kein Menüpunkt!" << endl;
        }
    }
    return 0;
}

void addWord(Trie<string> * tree) {
    string key;
    string word;

    cout << "Eingabe des deutschen Worts" << endl;
    cin >> key;
    cout << "Übersetzung" << endl;
    cin >> word;

    pair<string, string> element = pair<string, string>(key, word);
    tree->insert(element);
    cout << key << " mit Übersetzung: " << word << " wurde hinzugefügt." << endl;
}

void findWord(Trie<string> * tree) {
    string key;

    cout << "Welches Wort soll übersetzt werden?" << endl;
    cin >> key;
    auto it = tree->find(key);
    if (it == tree->end()) {
        cout << "Es tut mir leid, aber ich kann für " << key << " leider keine Übersetzung finden." << endl;
    } else {
        cout << key << " übersetzt bedeutet: " << *it << endl;
    }
}

void eraseWord(Trie<string> * tree) {
    string key;
    cout << "Welches Wort soll gelöscht werden?" << endl;
    cin >> key;
    if (tree->find(key) == tree->end()) {
        cout << "Das Wort '" << key << "' ist nicht im Wörterbuch vorhanden." << endl;
        return;
    }
    tree->erase(key);
    cout << key << " wurde aus dem Wörterbuch gelöscht." << endl;
}

void iterateAll(Trie<string> * tree) {
    if (tree->begin() == tree->end()) {
        cout << "Das Wörterbuch ist leer" << endl;
    }
    for (auto i = tree->begin(); i != tree->end(); ++i) {
        cout << *i << endl;
    }
}

void writeTree(Trie<string> * tree) {
    if (tree->begin() == tree->end()) {
        cout << "Das Wörterbuch ist leer." << endl;
        return;
    }
    tree->output();
}

void clearTree(Trie<string> * tree) {
    tree->clear();
    cout << "Das Wörterbuch wurde geleert." << endl;
}

void lowerAndUpperBound(Trie<string> *tree) {
    if(tree->empty()) {
        cout << "Tree ist leer" << endl;
        return;
    }
    string bound = "";
    cout << "Suchwort eingeben:" << endl;
    cin >> bound;

    cout << "lower_bound: " << *tree->lower_bound(bound) << endl;
    cout << "upper_bound: " << *tree->upper_bound(bound) << endl;
}

void listMenu() {
    cout << "Menü:" << endl;
    cout << " 0: Menü" << endl;
    cout << " 1: Wort hinzufügen" << endl;
    cout << " 2: Suchen einer Übersetzung" << endl;
    cout << " 3: Entfernen einen Wortes" << endl;
    cout << " 4: Ausgabe des kompletten Baum in primtiver Ansicht" << endl;
    cout << " 5: Leeren des Wörterbuchs" << endl;
    cout << " 6: Ausgabe aller English Wörtern" << endl;
    cout << " 7: Suche von Lower- und Upper-Bound" << endl;
    cout << " 8: Beenden" << endl;
    cout << " 9: Duc Übung" << endl;
}

list<int> * bubblesort(list<int> * toSort);
void DucÜbung() {

    // TODO: Hr Fischer fragen: Liste initialisiert hier eine 2 am Ende? Wieso? Vielleicht weil index.
    list<int> duc;

    duc.insert(duc.begin(), 3);
    duc.insert(duc.begin(), 78);
    duc.insert(duc.begin(), 4);
    duc.insert(duc.begin(), 42);
    duc.insert(duc.begin(), -5);
    duc.insert(duc.begin(), 124);
    duc.insert(duc.begin(), 1);
    duc.insert(duc.begin(), 100);

    // bubblesort
    for(auto top = duc.end(); top != duc.begin(); --top) {
        for (auto i = duc.begin(); i != top; ++i) {

            // get iterator, which ist greater
            auto compare = duc.begin();
            for (compare; compare != i; ++compare);
            compare++;

            // swap if encessary
            if(*i > *compare && compare != duc.end()) {
                swap(*i, *compare);
            }
        }
    }

    for(int i : duc) {
        cout << i << endl;
    }
/*
    cout << *++++duc.begin() << endl;
    auto it =duc.begin();
    ++it;
    ++it;
    if(it == duc.end()) {
        cout << "true" << endl;
    }
    cout << *it << endl;

    // TODO: Vector Übung
    vector<int> duc2 (0, 2);

    duc2.push_back(2);
    duc2.push_back(34);
    duc2.insert(duc2.begin(), 0);
    for(int i : duc2) {
        cout << i << endl;
    }

    cout << duc2.front() << endl;

    // TODO: Queue Übung

    queue<int> duc3;
    duc3.push(2);
    cout << duc3.back() << endl; */
}


