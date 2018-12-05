//
// Created by Viet Duc Mai on 03.12.18.
//

#ifndef THEULTIMATETREE_TRIE_H
#define THEULTIMATETREE_TRIE_H

#include <stdio.h>
#include <string>
#include <cstring>
#include <list>

using namespace std;
class TrieIterator;
class AbstractNode;
class InnerNode;
class Leaf;
template <class T, class E=char>
class Trie {
private:
    InnerNode *root;

public:
    /* Konstruktor von Trie */
    Trie() {
        root = InnerNode();
    }
    /* Typedefs */
    typedef basic_string<E> key_type; // string=basic_string<char>
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;
    typedef TrieIterator iterator;
    /* Methoden */
    bool empty() const {
        return this->root->isEmpty();
    }

    // TODO: implement
    iterator insert(const value_type& value);
    // TODO: implement
    void erase(const key_type& value);

    /* clear all leafs and keys */
    void clear() {
        this->root->clear();
    };

    /* Iteratorabhänginge Methoden */
    // TODO: implement
    iterator lower_bound(const key_type& testElement); // first element >= testElement
    // TODO: implement
    iterator upper_bound(const key_type& testElement); // first element > testElement
    // TODO: implement
    iterator find(const key_type& testElement); // first element == testElement

    /* "returns end() if not found" */
    // TODO: implement
    iterator begin();

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
        AbstractNode() {
            letter = "";
            parent = nullptr;
        }

        AbstractNode(char keyPart, AbstractNode father): letter(keyPart), parent(&father) {};

        /* Virtual Methoden können von erbbaren Klassen überschrieben werden */
        virtual char getValue() {
            return this->letter;
        }
    };

    /* Innere Knoten */
    class InnerNode: AbstractNode {
    private:
        list<AbstractNode> *nodes;
    public:
        /* Konstruktor */
        InnerNode() {
            nodes = list<string>();
        }

        bool isEmpty() {
            return this->nodes->empty();
        }

        void clear() {
            nodes->clear();
        }

        // TODO: braucht man hier zwingend die Adressoperation?
        void addInner(InnerNode& node) {
            this->nodes->insert(node);
        };

        void addLeaf(Leaf& leaf) {
            this->nodes->insert(leaf);
        };

        // TODO: Was und wie funktioniert der Destruktor in cpp?!
        ~InnerNode();
    };

    /* Blatt zum abspeichern der Values */
    // TODO: implement all methods
    class Leaf: AbstractNode {
    private:
        mapped_type value;
    public:
        /* Konstruktor */
        Leaf(mapped_type * finalValue): value(finalValue) {};

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
        mapped_type element;
    public:
        /* Konstruktoren */
        TrieIterator(Trie treeInput): tree(&treeInput) {};
        TrieIterator(Trie treeInput, mapped_type inputElement): tree(&treeInput), element(inputElement) {};
    };
};

#endif //THEULTIMATETREE_TRIE_H
