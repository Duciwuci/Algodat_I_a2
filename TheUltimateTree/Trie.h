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
        root = new InnerNode('$');
    }


    /* Typedefs */
    typedef basic_string<E> key_type; // string=basic_string<char>
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;
    typedef TrieIterator *iterator;


    /* Methoden */
    bool empty() const {
        return this->root->isEmpty();
    }

    // TODO: solve inverse
    iterator insert(const value_type& value) {
        InnerNode toIterate = *root;
        for (char key : value.first) {
            if(!toIterate.gotKeyPart(key)) {
                // wenn er einen weiteren Pfad hat, iterier weiter
                toIterate = toIterate.getNext(key);
            } else {
                // wenn er keinen hat, adde und iterier weiter
                toIterate.addInner(InnerNode(key));
                toIterate =  toIterate.getNext(key);
            }
        }
        // add leaf, wenn er er durch ist
        toIterate.addLeaf(Leaf('$', value.second));
        // return iterator
        // TODO: give iterator an value
        return iterator();
    };

    // TODO: solve erase without getNext(), solve with new stack
    void erase(const key_type& value) {
        InnerNode toIterate = root;
        for(char key : *value) {
            if(toIterate.gotKeyPart(key)) {
                // lösche Pfad, falls er nur einen Child hat
                if(toIterate.isLonely()) {
                    InnerNode tmp = toIterate.getNext(key);
                    toIterate.removeNode(key);
                    toIterate = tmp;
                } else {
                    toIterate = toIterate.getNext(key);
                }
            }
        }
        if(toIterate.getNext('$')) {
            toIterate.removeNode('$');
        }
    };

    /* clear all leafs and keys */
    void clear() {
        this->root->clear();
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
    };

    /* Innere Knoten */

    class Leaf;
    class InnerNode: AbstractNode {
    private:
        list<AbstractNode> *nodes;
    public:
        /* Konstruktor */
        InnerNode(char input): AbstractNode(input) {
            nodes = new list<AbstractNode>();
        }

        bool isEmpty() {
            return this->nodes->empty();
        }

        bool isLonely() {
            return this->nodes->size() == 1;
        }

        void clear() {
            nodes->clear();
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
            for(AbstractNode remove : *nodes) {
                if(remove.getValue() == toRemove) {
                    nodes->remove(remove);
                }
            }
        }

        AbstractNode getNext(char toReturn) {
            if(gotKeyPart(toReturn)) {
                for(AbstractNode abs : *nodes) {
                    if(abs.getValue() == toReturn) {
                        return abs;
                    }
                }
            }
        }

        bool gotKeyPart(char toCheck) {
            for(AbstractNode n : *nodes) {
                if(n.getValue() == toCheck) {
                    return true;
                }
            }
            return false;
        }

        // TODO: Was und wie funktioniert der Destruktor in cpp?!
        ~InnerNode();
    };

    /* Blatt zum abspeichern der Values */
    // TODO: implement all methods
    class Leaf: AbstractNode {
    private:
        T value;
    public:
        /* Konstruktor */
        Leaf(char input, T inputValue): AbstractNode(input), value(inputValue) {};

        /* Überschreiben der Methode, standardisiert für alle Leafs */
        char getValue() {
            return '$';
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
};

#endif //THEULTIMATETREE_TRIE_H
