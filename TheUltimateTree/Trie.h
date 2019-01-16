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
        virtual char getLetter() {
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
        Leaf * previous;
        Leaf * next;
    public:
        /* Konstruktor */
        Leaf(T inputValue): AbstractNode(leafToken), value(inputValue) {

        };

        /* Überschreiben der Methode, standardisiert für alle Leafs */
        char getLetter() {
            return leafToken;
        }

        T getValue() {
            return value;
        }

        void setPrevious(Leaf * previous1) {
            previous = previous1;
        }

        Leaf * getPrevious() {
            return (Leaf*) this->previous;
        }

        void setNext(Leaf * next1) {
            next = next1;
        }

        Leaf * getNext() {
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

    /* Iterator für einen Trie */
    class AbstractNode;
    class TrieIterator {
    private:
        AbstractNode* root;
        stack<pair<AbstractNode*, E>> leafPath;
        Leaf * memory;
        char leafToken = '$';
    public:
        typedef TrieIterator iterator;

        /* Konstruktoren */
        TrieIterator(AbstractNode *treeInput): root(treeInput) {};

        iterator & find(const key_type key) {
            return recursiveFind(key, root);
        }; // and find
        // TODO: implement
        iterator & begin() {
            auto it = root->getSons().begin();
            if (it == root->getSons().end()) {
                return end();
            }
            while (it->first != leafToken) {
                it = it->second->getSons().begin();
            }
            memory = (Leaf*) it->second;
            return *this;
        }

        // TODO: implement right way
        iterator & end() {
            leafPath = {};
            return *this;
        };

        iterator & operator++() {
            // TODO: null checks
            memory = (Leaf*) memory->getNext();
            return *this;
        }; // build down and up stack

        iterator & operator--() {
            // TODO: null checks
            memory = memory->getPrevious();
            return *this;
        }; // build down and up stack

        E getValue() {
            return this->memory->getValue();
        }

        T operator*() {
            return memory->getValue();
        }
    private:
        iterator & recursiveFind(key_type key, AbstractNode* current) {
            if(key.length() <= 0) {
                this->memory = (Leaf*) current->getSonNode(leafToken);
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
        iterator it = iterator(root);
        return it.find(testElement);
    }; // first element == testElement

    /* returns default iterator, if empty */
    iterator begin() {
        AbstractNode* path = root;
        /*if(empty()) {
            cout << "begin not found" << endl;
            return iterator(this->root);
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
        return iterator(path->getSons().begin()->second);*/
        return iterator(root).begin();
    };

    /*
     * returns default, if empty
     */
    // TODO: add operators to iterator and use them
    iterator end() {
        return iterator(this->root);
    };


private:
    InnerNode *root;
    stack<pair <AbstractNode*, char>> stackToTrack;
    char leafToken = '$';

    // recursive method to insert
    iterator insertRecursive(const value_type value, AbstractNode *current) {
        key_type key = value.first;

        //auto bla = GetNextBranch();
        //auto blub = GetNextOrPreviousLeaf(bla.second, bla.first);



        // key is empty
        if(key.length() == 0) {
            auto p = make_pair(leafToken, new Leaf(value.second));
            current->getSons().insert(p);

            auto branchPair = GetNextBranch();
            Leaf * leaf;
            bool next = true;
            //if there is a word which is almost the same (only shorter)
            // wir - wird -> wir is previous
            if (branchPair.first == leafToken) {
                leaf = (Leaf*) branchPair.second;
                // first Word in list
                if (leaf->getLetter() == leafToken) {
                    return TrieIterator(root);
                }
                next = false;
            } else {
                auto nextPair = GetNextOrPreviousLeaf(branchPair.second, branchPair.first);
                // if first is false, its a previous Leaf
                if (!nextPair.first) {
                    next = false;
                }
                leaf = nextPair.second;
            }
            this->setPrevOrNext(next, (Leaf*) current, leaf);

            /*Leaf * tmp = findNextLeafFromStack();
            current->getSons().insert(make_pair(leafToken, new Leaf(value.second)));
            if(tmp != nullptr) {
                // TODO: null checks, Verknüpfung schlägt fehl
                Leaf * currentLeaf = (Leaf*) (current->getSons().find(leafToken))->second;
                tmp->getPrevious()->setNext(currentLeaf);
                ((Leaf*) current->getSons().find(leafToken)->second)->setPrevious(tmp->getPrevious());
                tmp->setPrevious((Leaf*) current->getSons().find(leafToken)->second);
                ((Leaf*) current->getSons().find(leafToken)->second)->setNext(tmp);
            }*/
            cout << "inserted " << value.second << " into " << current->getLetter() << endl;
            stackToTrack = {};
            return TrieIterator(root);

            // try to find key, false if get end(), see map operations
        } else if(current->getSons().find(key[0]) == current->getSons().end()) {
            auto nextCurrent = current->getSons().insert(make_pair(key[0], new InnerNode(key[0])));
            //TODO: Wenn der richtige iterator zurückgegeben wird muss die nachfolgende Zeilen gelöscht werden
            // und der Wert des iterators benutzt werden...
            auto tmpIt = current->getSons().find(key[0]);

            stackToTrack.push(pair <AbstractNode*, char>(tmpIt->second, tmpIt->first));

            return insertRecursive(make_pair(key.substr(1, key.length()), value.second), nextCurrent.first->second);

            // else, if there is a mapped son
        } else {
            auto cur = current->getSons().find(key[0])->second;
            stackToTrack.push(pair <AbstractNode*, char>(cur, cur->getLetter()));
            return insertRecursive(make_pair(key.substr(1, key.length()), value.second), cur);
            //stackToTrack.push(pair <AbstractNode*, char>(current, current->getLetter()));
            //return insertRecursive(make_pair(key.substr(1, key.length()), value.second), current->getSons().find(key[0])->second);
        }
    };

    void setPrevOrNext(bool next, Leaf* leaf, Leaf* prevOrNext) {
        if (next) {
            auto prev = prevOrNext->getPrevious();
            leaf->setPrevious(prev);
            if (prev != nullptr) prev->setNext(leaf);
            leaf->setNext(prevOrNext);
            prevOrNext->setPrevious(leaf);
        } else {
            auto next = prevOrNext->getNext();
            if (next != nullptr) next->setPrevious(leaf);
            leaf->setNext(next);
            prevOrNext->setNext(leaf);
            leaf->setPrevious(prevOrNext);
        }
    }

    Leaf * findNextLeafFromStack() {
        AbstractNode * tmp = stackToTrack.top().first;
        auto sons = tmp->getSons();
        if(tmp->getSons().size() > 1) {
            return findNextLeaf(leafToken);
        } else if (tmp->getSons().size() == 1) {
            char newChar = tmp->getLetter();
            stackToTrack.pop();
            return findNexLeafFromStackRecursive(newChar);
        }
    }

    pair<char, AbstractNode *> GetNextBranch() {
        AbstractNode * tmp = stackToTrack.top().first;
        char c = tmp->getLetter();
        while(tmp->getSons().size() == 1) {
            c = tmp->getLetter();
            stackToTrack.pop();

            //case --> first Word of Trie
            if (stackToTrack.size() == 0) {
                if (root->getSons().size() > 1) {
                    return make_pair(c, root);
                }
                return make_pair(leafToken, root);
            }
            tmp = stackToTrack.top().first;
        }

        auto it = tmp->getSons();
        if (it.find(leafToken) != it.end()) {
            return make_pair(leafToken, tmp);
        }

        return make_pair(c, tmp);
    }

    pair<bool, Leaf *> GetNextOrPreviousLeaf(AbstractNode * branchNode, char c) {
        auto sons = branchNode->getSons();
        auto mapIterator = sons.find(c);

        //AbstractNode * tmp = stackToTrack.top().first;
        auto s = mapIterator->second->getSons();
        if (++mapIterator != sons.end()) {
            mapIterator = s.find(leafToken);
            while(mapIterator == s.end()) {
                s = s.begin()->second->getSons();
                mapIterator = s.find(leafToken);
            }
            return make_pair(true, (Leaf*) mapIterator->second);
            //return make_pair(true, mapIterator*.second);
        }
        mapIterator--;
        mapIterator--;
        s = mapIterator->second->getSons();
        mapIterator = s.find(leafToken);
        while (mapIterator == s.end() /*&& s.size() > 1*/) {
            s = s.rbegin()->second->getSons();
            mapIterator = s.find(leafToken);
        }
        return make_pair(false, (Leaf*) mapIterator->second);
    };

    Leaf * findNextLeaf(char input) {
        AbstractNode * tmp = stackToTrack.top().first;
        if(input == leafToken) {
            tmp = tmp->getSons().begin()->second;
        } else {
            if(tmp->getSons().find(leafToken) != tmp->getSons().end()) {
                return (Leaf*) tmp->getSons().find(leafToken)->second;
            }
        }
        // iterier always first
        while(tmp->getLetter() != leafToken) {
            tmp = tmp->getSons().begin()->second;
        }
        stackToTrack = {};
        return (Leaf*) tmp;
    };

    Leaf * findNexLeafFromStackRecursive(char input) {
        AbstractNode * tmp = stackToTrack.top().first;
        if (tmp->letter == leafToken) {
            // root
            return nullptr;
        }
        if(tmp->getSons().size() > 1) {
            if(tmp->getSons().find(leafToken) != tmp->getSons().end()) {
                stackToTrack.pop();
                tmp = stackToTrack.top().first;
            }
            return findNextLeaf(tmp->getLetter());
        } else {
            stackToTrack.pop();
            return findNextLeafFromStack();
        }
    }
};

#endif //THEULTIMATETREE_TRIE_H
