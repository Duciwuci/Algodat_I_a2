//
// Created by Viet Duc Mai on 03.12.18.
//

#ifndef THEULTIMATETREE_TRIE_H
#define THEULTIMATETREE_TRIE_H

#include <stdio.h>
#include <string>
#include <cstring>
#include <list>
#include <stack>
#include <map>

using namespace std;
class TrieIterator;
class AbstractNode;
class InnerNode;
class Leaf;
template <class T, class E=char>
class Trie {
public:
    /* Konstruktor von Trie */
    Trie() {
        root = new InnerNode(leafToken);
    }


    /* Typedefs */
    typedef basic_string<E> key_type; // string=basic_string<char>
    typedef pair<basic_string<E>, T> value_type;
    typedef T mapped_type;
    typedef TrieIterator *iterator;


    /* Methoden */
    bool empty() const {
        return root->getSons().empty();
    }

    iterator insert(const value_type value) {
        return insertRecursive(value, root);
    }

    // erase, build up stack and build it down
    void erase(const key_type& value) {
        AbstractNode *path = root;
        int popCounter = 0;
        // build up stack
        for(char point : value) {
            if(path->getSons().find(point) == path->getSons().end()) {
                for(int i = 0; i < stackToTrack.size(); --i) {
                    stackToTrack.pop();
                }
                return;
            }
            stackToTrack.push(pair <AbstractNode*, char>(path->getSons().find(point)->second, path->getSons().find(point)->first));
            path = path->getSons().find(point)->second;
        }
        key_type debug = "";

        // pop elements and delete if needed
        int toPop = stackToTrack.size();
        bool continueRemoving = true;
        char removeChar = leafToken;
        for(int i = 0; i < toPop; ++i) {
            pair<AbstractNode *, char> &tmp = stackToTrack.top();
            if(continueRemoving) {
                tmp.first->getSons().erase(removeChar);
                debug = removeChar + debug;
                if (tmp.first->getSons().empty()) {
                    delete tmp.first;
                    removeChar = tmp.second;
                } else {
                    continueRemoving = false;
                }
            }
            stackToTrack.pop();
        }
        if(continueRemoving) {
            root->getSons().erase(removeChar);
            debug = removeChar + debug;
        }
        cout << "deleted " << debug << endl;
    };

    /* clear all leafs and keys */
    void clear() {
        this->root->getSons().clear();
    };

    /* Iteratorabhängige Methoden */
    // TODO: implement
    iterator lower_bound(const key_type& testElement); // first element >= testElement
    // TODO: implement
    iterator upper_bound(const key_type& testElement); // first element > testElement
    // TODO: implement
    iterator find(const key_type& testElement); // first element == testElement

    /* "returns end() if not found" */
    // TODO: implement
    iterator begin() {
        return TrieIterator(this);
    }

    // TODO: implement
    iterator end();

    /* Abstrakte Knotenklasse
     * Innere Knoten und Blätter werden von dieser abgeleitet */
    class AbstractNode {
    private:
        char letter;
        AbstractNode *parent;
        map<E, AbstractNode*> sons;
    public:
        /* Konstruktoren */
        AbstractNode(char sign) {
            letter = sign;
            parent = nullptr;
        }

        AbstractNode(char keyPart, AbstractNode father): letter(keyPart), parent(&father) {};

        /* Virtual Methoden können von erbbaren Klassen überschrieben werden */
        virtual char getValue() {
            return this->letter;
        }

        map<E, AbstractNode*>& getSons() {
            return sons;
        }

        bool isLonely() {
            return this->getSons().size() == 1;
        }
    };

    /* Innere Knoten */

    class Leaf;
    class InnerNode: public AbstractNode {
    public:
        /* Konstruktor */
        InnerNode(char input): AbstractNode(input) {};

        bool isEmpty() {
            return this->getSons().empty();
        }

        void clear() {
            this->getSons()->clear();
        }

        void addInner(InnerNode node) {
            this->nodes->insert(node);
            this->nodes->sort();
        };

        void addLeaf(Leaf leaf) {
            this->nodes->insert(leaf);
            // TODO: implement sort method
            this->nodes->sort();
        };

        void removeNode(char toRemove) {
            // TODO: implement
        }

        bool gotKeyPart(char toCheck) {
            // TODO: implement
        }

        // TODO: Was und wie funktioniert der Destruktor in cpp?!
        ~InnerNode();
    };

    /* Blatt zum abspeichern der Values */
    // TODO: implement all methods
    class Leaf: public AbstractNode {
    private:
        T value;
        char leafToken = '$';
    public:
        /* Konstruktor */
        Leaf(T inputValue): AbstractNode(leafToken), value(inputValue) {};

        /* Überschreiben der Methode, standardisiert für alle Leafs */
        char getValue() {
            return leafToken;
        }

        mapped_type getObject() {
            return this->value;
        }
    };

    /* Iterator für einen Trie */
    // TODO: implement
    class TrieIterator {
    private:
        Trie tree;
        T element;
    public:
        /* Konstruktoren */
        TrieIterator() {};
        TrieIterator(Trie &treeInput): tree(treeInput) {};
        TrieIterator(Trie &treeInput, T inputElement): tree(treeInput), element(inputElement) {};
    };

private:
    InnerNode *root;
    stack<pair <AbstractNode*, char>> stackToTrack;
    char leafToken = '$';

    // recursive method to insert
    iterator insertRecursive(const value_type value, AbstractNode *current) {
        key_type key = value.first;

        // key is empty
        if(key.length() == 0) {
            current->getSons().insert(make_pair(leafToken, new Leaf(value.second)));
            cout << "inserted " << value.second << " into " << current->getValue() << endl;
            return iterator();

            // try to find key, false if get end(), see map operations
        } else if(current->getSons().find(key[0]) == current->getSons().end()) {
            auto nextCurrent = current->getSons().insert(make_pair(key[0], new InnerNode(key[0])));
            insertRecursive(make_pair(key.substr(1, key.length()), value.second), nextCurrent.first->second);

            // else, if there is a mapped son
        } else {
            insertRecursive(make_pair(key.substr(1, key.length()), value.second), current->getSons().find(key[0])->second);
        }

        // return iterator
        // TODO: give iterator an value
        return iterator();
    };
};

#endif //THEULTIMATETREE_TRIE_H
