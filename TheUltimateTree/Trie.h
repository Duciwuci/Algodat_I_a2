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


    /* Iterator für einen Trie */
    class AbstractNode;
    class TrieIterator {
    private:
        AbstractNode& root;
        stack<pair<AbstractNode*, E>> leafPath;
        Leaf &memory;
        char leafToken = '$';
    public:
        typedef TrieIterator iterator;

        /* Konstruktoren */
        TrieIterator(AbstractNode &treeInput, Leaf& start): root(treeInput), memory(start) {};
        iterator & find(const key_type key) {
            return recursiveFind(key, root);
        }; // and find
        // TODO: implement
        iterator & begin(); // iterate always first first()
        // TODO: implement right way
        iterator & end() {
            leafPath = {};
            return *this;
        };

        iterator & operator++() {
            // TODO: null checks
            memory = Leaf::memory.getNext();
            return this;
        }; // build down and up stack

        iterator & operator--() {
            // TODO: null checks
            memory = Leaf::memory.getPrevious();
            return this;
        }; // build down and up stack

        E getValue() {
            return this->memory->getValue();
        }

        T& operator*() {
            return memory;
        }
    private:
        iterator & recursiveFind(key_type key, AbstractNode* current) {
            if(key.length() <= 0) {
                this->memory = current->getSonNode(leafToken);
                return *this;
            }
            return recursiveFind(key.substr(1, key.length()), current->getSonNode(key[0]));
        }
    };
    typedef TrieIterator iterator;

    /* Methoden */
    bool empty() const {
        return root->getSons().empty();
    }

    iterator insert(const value_type value) {
        return insertRecursive(value, root);
    }

    // erase, build up stack and build it down
    // TODO: unchain Leafs
    void erase(const key_type& value) {
        AbstractNode *path = root;
        int popCounter = 0;
        // build up stack
        for(char point : value) {
            if(path->getSons().find(point) == path->getSons().end()) {
                stackToTrack = {};
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
        cout << "clear tree" << endl;
        this->root->getSons().clear();
    };

    /* Iteratorabhängige Methoden */
    // TODO: implement
    iterator lower_bound(const key_type& testElement); // first element >= testElement
    // TODO: implement
    iterator upper_bound(const key_type& testElement); // first element > testElement

    iterator find(const key_type& testElement) {
        iterator it = iterator(*this);
        return it.find(testElement);
    }; // first element == testElement

    /* returns default iterator, if empty */
    iterator begin() {
        AbstractNode* path = root;
        if(empty()) {
            cout << "begin not found" << endl;
            return iterator();
        } else {
            char proof = ' ';
            while (proof != leafToken) {

                if(path->getSons().begin()->first != '$') {
                    path = path->getSons().begin()->second;
                } else {
                    proof = leafToken;
                }
            }
        }
        return iterator(path->getSons().begin()->second);
    };

    /*
     * returns default, if empty
     */
    // TODO: add operators to iterator and use them
    iterator end() {
        return iterator();
    };

    /* Abstrakte Knotenklasse
     * Innere Knoten und Blätter werden von dieser abgeleitet */
    class AbstractNode {
    private:
        map<E, AbstractNode*> sons;
    public:
        char letter;
        /* Konstruktoren */
        AbstractNode(char sign) {
            letter = sign;
        }

        AbstractNode* getSonNode(char c) {
            map<E, AbstractNode*> sons = this->getSons();
            auto iter = sons.find(c);
            if (iter == sons.end()) {
                return nullptr;
            }
            return iter->second;
        }

        /* Virtual Methoden können von erbbaren Klassen überschrieben werden */
        virtual char getValue() {
            return this->letter;
        }

        map<E, AbstractNode*>& getSons() {
            return sons;
        }
/*
        virtual void setPrevious(Leaf & previous) {
            return;
        }

        virtual Leaf & getPrevious() {return Leaf();};

        virtual void setNext(Leaf & next) {
            return;
        }

        virtual Leaf & getNext() {return Leaf();};*/
    };

    /* Innere Knoten */

    class Leaf;
    class InnerNode: public AbstractNode {
    public:
        /* Konstruktor */
        InnerNode(char input): AbstractNode(input) {};

        ~InnerNode();

    };

    /* Blatt zum abspeichern der Values */
    // TODO: implement all methods
    class Leaf: public AbstractNode {
    private:
        T value;
        char leafToken = '$';
        Leaf & previous;
        Leaf & next;
    public:
        /* Konstruktor */
        Leaf(T inputValue, Leaf& previous, Leaf & next): AbstractNode(leafToken), value(inputValue), previous(previous), next(next) {

        };

        /* Überschreiben der Methode, standardisiert für alle Leafs */
        char getValue() {
            return leafToken;
        }

        void setPrevious(Leaf & previous1) {
            previous = previous1;
        }

        Leaf & getPrevious() {
            return (Leaf&) this->previous;
        }

        void setNext(Leaf & next1) {
            next = next1;
        }

        Leaf & getNext() {
            return this->next;
        }

        void operator= (Leaf & leaf) {
            this->value = leaf.value;
            this->next = leaf.next;
            this->leafToken = leaf.leafToken;
            this->previous = leaf.previous;

        }

        bool operator!=(const Leaf * value) {
            if(value ==  nullptr) {
                return true;
            }
            return false;
        }
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
            Leaf & tmp = findNextLeafFromStack();
            current->getSons().insert(make_pair(leafToken, new Leaf(value.second, tmp.getPrevious(), tmp)));
            if(tmp != nullptr) {
                // TODO: null checks
                Leaf & currentLeaf = (Leaf&) (current->getSons().find(leafToken))->second;
                tmp.getPrevious().setNext(currentLeaf);
                ((Leaf&) current->getSons().find(leafToken)->second).setPrevious(tmp.getPrevious());
                tmp.setPrevious((Leaf&) current->getSons().find(leafToken)->second);
                ((Leaf&) current->getSons().find(leafToken)->second).setNext(tmp);
            }
            cout << "inserted " << value.second << " into " << current->getValue() << endl;
            return TrieIterator(this->root, (Leaf&) current->getSons().find(leafToken)->second);

            // try to find key, false if get end(), see map operations
        } else if(current->getSons().find(key[0]) == current->getSons().end()) {
            auto nextCurrent = current->getSons().insert(make_pair(key[0], new InnerNode(key[0])));
            stackToTrack.push(pair <AbstractNode*, char>(current, current->getValue()));

            return insertRecursive(make_pair(key.substr(1, key.length()), value.second), nextCurrent.first->second);

            // else, if there is a mapped son
        } else {

            stackToTrack.push(pair <AbstractNode*, char>(current, current->getValue()));
            return insertRecursive(make_pair(key.substr(1, key.length()), value.second), current->getSons().find(key[0])->second);
        }
    };

    Leaf & findNextLeafFromStack() {
        AbstractNode * tmp = stackToTrack.top().first;
        auto sons = tmp->getSons();
        if(tmp->getSons().size() > 1) {
            return findNextLeaf(leafToken);
        } else if (tmp->getSons().size() == 1) {
            char newChar = tmp->getValue();
            stackToTrack.pop();
            return findNexLeafFromStackRecursive(newChar);
        }
    }

    Leaf & findNextLeaf(char input) {
        AbstractNode * tmp = stackToTrack.top().first;
        if(input == leafToken) {
            tmp = tmp->getSons().begin()->second;
        } else {
            if(tmp->getSons().find(leafToken) != tmp->getSons().end()) {
                return (Leaf&) tmp->getSons().find(leafToken)->second;
            }
        }
        // iterier always first
        while(tmp->getValue() != leafToken) {
            tmp = tmp->getSons().begin()->second;
        }
        stackToTrack = {};
        return (Leaf&) tmp;
    };

    Leaf & findNexLeafFromStackRecursive(char input) {
        AbstractNode * tmp = stackToTrack.top().first;
        if(tmp->getSons().size() > 1) {
            if(tmp->getSons().find(leafToken) != tmp->getSons().end()) {
                stackToTrack.pop();
                tmp = stackToTrack.top().first;
            }
            return findNextLeaf(tmp->getValue());
        }
        else {
            stackToTrack.pop();
            return findNextLeafFromStack();
        }
    }
};

#endif //THEULTIMATETREE_TRIE_H
