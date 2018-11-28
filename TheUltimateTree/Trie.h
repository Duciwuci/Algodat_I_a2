//
// Created by Viet Duc Mai on 28.11.18.
//

#ifndef THEULTIMATETREE_TRIE_H
#define THEULTIMATETREE_TRIE_H

template <class T, class E=char>
class Trie {
public:
    typedef basic_string<E> key_type; // string=basic_string<char>
    typedef pair<const key_type, T> value_type;
    typedef T mapped_type;
    // „...“ im folgenden typedef: keine C/C++ Ellipse, sondern von Ihnen
    // - am besten als innere Klasse - zu entwickeln…
    typedef ... iterator;
    bool empty() const;
    iterator insert(const value_type& value);

    void erase(const key_type& value);
    void clear(); // erase all
    iterator lower_bound(const key_type& testElement); // first element >= testElement
    iterator upper_bound(const key_type& testElement); // first element > testElement
    iterator find(const key_type& testElement); // first element == testElement
    iterator begin(); // returns end() if not found
    iterator end();
};

#endif //THEULTIMATETREE_TRIE_H
