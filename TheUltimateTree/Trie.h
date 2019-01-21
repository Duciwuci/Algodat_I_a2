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
template <class T, class E=char>
class Trie {
public:
    /* Konstruktor von Trie */
    Trie() {
        root = new InnerNode(leafToken);
    }


    /* Typedefs */
    // string=basic_string<char>
    typedef basic_string<E> key_type;
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

        virtual char getLetter() {
            return this->letter;
        }

        map<E, AbstractNode*>& getSons() {
            return sons;
        }
    };

    /* Innere Knoten */
    class Leaf;
    class InnerNode: public AbstractNode {
    public:
        /* Konstruktor */
        InnerNode(char input): AbstractNode(input) {};

        // Destruktor
        ~InnerNode();

    };

    /* Blatt zum abspeichern der Values */
    class Leaf: public AbstractNode {
    private:
        T value;
        char leafToken = '$';
        Leaf * previous = nullptr;
        Leaf * next = nullptr;
    public:
        /* Konstruktor */
        Leaf(T inputValue): AbstractNode(leafToken), value(inputValue) {};

        /* Überschreiben der Methode, standardisiert für alle Leafs */
        char getLetter() {
            return leafToken;
        }

        T getValue() {
            return value;
        }

        void setPrevious(Leaf * previous1) {
            this->previous = previous1;
        }

        Leaf * getPrevious() {
            return (Leaf*) this->previous;
        }

        void setNext(Leaf * next1) {
            this->next = next1;
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
        Leaf * memory;
        char leafToken = '$';
    public:
        typedef TrieIterator iterator;

        /* Konstruktoren */
        TrieIterator(AbstractNode *treeInput): root(treeInput) {};

        TrieIterator(AbstractNode *treeInput, Leaf * leaf) {
            root = treeInput;
            memory = leaf;
        }

        iterator & find(const key_type key) {
            return recursiveFind(key, root);
        };

        Leaf * GetLeaf() {
            return memory;
        }

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

        iterator & end() {
            memory = nullptr;
            return *this;
        };

        iterator & operator++() {
            if(memory != nullptr) {
                this->memory = this->memory->getNext();
            }
            return *this;
        };

        iterator & operator--() {
            if(memory->getPrevious() != nullptr) {
                this->memory = this->memory->getPrevious();
            }
            return *this;
        };

        bool operator==(iterator it) {
            if (memory != nullptr && it.GetLeaf() == nullptr) return false;
            if (memory == nullptr && it.GetLeaf() != nullptr) return false;
            if (memory == nullptr && it.GetLeaf() == nullptr) return true;
            if (memory->getValue() != it.GetLeaf()->getValue()) return false;

            return true;
        }

        bool operator!=(iterator it) {
            return !(*this == it);
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
            auto sons = current->getSons();
            auto it = sons.find(key[0]);
            if (it == sons.end()) {
                return end();
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
        insertRecursive(value, root);
        return find(value.first);
    }

    // erase, build up stack and build it down
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
        if(toPop > 0) {
            unchainLeaf((Leaf*) stackToTrack.top().first->getSons().find(leafToken)->second);
        }
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
    };

    void output() {
        writeRecursive(root, 0);
    }

    /* clear all leafs and keys */
    void clear() {
        this->root->getSons().clear();
    };

    /* Iteratorabhängige Methoden */
    iterator lower_bound(const key_type& testElement) {
        auto it = find(testElement);
        if (it != end()) {
            return it;
        }
        int num;
        auto sons = root->getSons();
        for (int i = 0; i < testElement.length(); i++) {
            auto tmpIt = sons.find(i);
            if (tmpIt == sons.end()) {
                num = i;
                break;
            }
            sons = tmpIt->second->getSons();
        }

        return findBound(testElement.substr(num, testElement.length()), root);
    }

    iterator upper_bound(const key_type& testElement) {
        auto it = this->find(testElement);
        if (it != end()) {
            return ++it;
        }
        return lower_bound(testElement);
    }

    iterator end() {
        auto it = iterator(root);
        it.end();
        return it;
    }

    iterator find(const key_type& testElement) {
        iterator it = iterator(root);
        return it.find(testElement);
    };

    iterator begin() {
        return iterator(root).begin();
    };

private:
    InnerNode *root;
    stack<pair <AbstractNode*, char>> stackToTrack;
    char leafToken = '$';

    // recursive method to insert
    void insertRecursive(const value_type value, AbstractNode *current) {
        key_type key = value.first;

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
                    return;
                }
                leaf = (Leaf*) branchPair.second->getSons().find(leafToken)->second;
                next = false;
            } else {
                auto nextPair = GetNextOrPreviousLeaf(branchPair.second, branchPair.first);
                // if first is false, its a previous Leaf
                if (!nextPair.first) {
                    next = false;
                }
                leaf = nextPair.second;
            }
            this->setPrevOrNext(next, (Leaf*) current->getSons().find(leafToken)->second, leaf);

            stackToTrack = {};
            return;

            // try to find key, false if get end(), see map operations
        } else if(current->getSons().find(key[0]) == current->getSons().end()) {
            auto nextCurrent = current->getSons().insert(make_pair(key[0], new InnerNode(key[0])));
            auto tmpIt = current->getSons().find(key[0]);

            stackToTrack.push(pair <AbstractNode*, char>(tmpIt->second, tmpIt->first));

            return insertRecursive(make_pair(key.substr(1, key.length()), value.second), nextCurrent.first->second);

            // else, if there is a mapped son
        } else {
            auto cur = current->getSons().find(key[0])->second;
            stackToTrack.push(pair <AbstractNode*, char>(cur, cur->getLetter()));
            return insertRecursive(make_pair(key.substr(1, key.length()), value.second), cur);
        }
    };

    iterator & findBound(key_type key, AbstractNode* root) {
        auto sons = root->getSons();
        auto it = sons.find(key[0]);

        if (it == sons.end()) {
            for (auto i = sons.begin(); i != sons.end(); ++i) {
                if (i->first > it->first) {
                    it = i;
                    break;
                }
            }
        }
        sons = it->second->getSons();
        while (sons.find(leafToken) == sons.end()) {
            sons = sons.begin()->second->getSons();
        }

        auto result = new TrieIterator(root, (Leaf*) sons.find(leafToken)->second);
        return *result;
    }
   
   void writeRecursive(AbstractNode * node, int level) {
        auto sons = node->getSons();
        int curLev = level;

        for (auto it = sons.begin(); it != sons.end(); ++it) {
            AbstractNode * tmp = it->second;
            if (tmp->getLetter() == leafToken) {
                std::cout << std::string (curLev, ' ') << ": " << ((Leaf *) tmp)->getValue() << std::endl;
            } else{
                std::cout << std:: string (curLev, ' ') << tmp->getLetter() << std::endl;
            }
            writeRecursive(tmp, level + 1);
        }
    }

    Leaf * unchainLeaf(Leaf* toUnchain) {
        Leaf* previous = toUnchain->getPrevious();
        Leaf* next = toUnchain->getNext();
        if(previous != nullptr) previous->setNext(next);
        if(next != nullptr) next->setPrevious(previous);
        return toUnchain;
    }

    void setPrevOrNext(bool next, Leaf* leaf, Leaf* prevOrNext) {
        if (next) {
            Leaf* prev = prevOrNext->getPrevious();
            leaf->setPrevious(prev);
            if (prev != nullptr) {
                prev->setNext(leaf);}
            leaf->setNext(prevOrNext);
            prevOrNext->setPrevious(leaf);
        } else {
            Leaf* next = prevOrNext->getNext();
            if (next != nullptr) next->setPrevious(leaf);
            leaf->setNext(next);
            prevOrNext->setNext(leaf);
            leaf->setPrevious(prevOrNext);
        }
    }

    // Find next Branch, where we can iterate down.
    pair<char, AbstractNode *> GetNextBranch() {
        AbstractNode * tmp = stackToTrack.top().first;
        char c = tmp->getLetter();

        // Pop above the track, while its a solo Node
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

    // searching a Leaf, return true with Leaf, if Previous.s
    pair<bool, Leaf *> GetNextOrPreviousLeaf(AbstractNode * branchNode, char c) {
        auto sons = branchNode->getSons();
        auto mapIterator = sons.find(c);

        auto s = mapIterator->second->getSons();
        if (++mapIterator != sons.end()) {
            s = mapIterator->second->getSons();
            mapIterator = s.find(leafToken);
            while(mapIterator == s.end()) {
                s = s.begin()->second->getSons();
                mapIterator = s.find(leafToken);
            }
            return make_pair(true, (Leaf*) mapIterator->second);
        }
        mapIterator--;
        mapIterator--;
        s = mapIterator->second->getSons();
        mapIterator = s.find(leafToken);
        while (mapIterator == s.end() /*&& s.size() > 1*/) {
            auto tmpIt = s.rbegin();
            if (tmpIt->second->getLetter() == leafToken) {
                tmpIt--;
                s = tmpIt->second->getSons();
                continue;
            }
            s = tmpIt->second->getSons();
            mapIterator = s.find(leafToken);
        }
        return make_pair(false, (Leaf*) mapIterator->second);
    };
};

#endif //THEULTIMATETREE_TRIE_H
