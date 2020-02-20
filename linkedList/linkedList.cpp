// March 2019 - Jack Chauvin

// Singly Linked List of Elements which hold a key and a list
// The Elements in the list are ordered by the values of the keys
#pragma once
#include<iostream>
using std::cout; using std::endl; using std::boolalpha; using std::ostream;
#include<initializer_list>
using std::initializer_list;
#include <algorithm>
using std::max; using std::copy; using std::swap; using std::find;
#include <utility>
using std::make_pair; using std::pair;
#include <stdexcept>
using std::runtime_error;

#include<sstream>
using std::ostringstream;
#include<string>
using std::string;
#include<vector>
using std::vector;

const static size_t element_array_size = 5;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// ELEMENT ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Holds a key and list and points to the next element in a list
template<typename K, typename V>
struct Element{
public:
  K key_;
  V values_[element_array_size];
  Element* next_ = nullptr;
  size_t count_ = 0;

  Element()=default;
  Element(K, initializer_list<V>);
  Element(const Element&);
  bool operator==(const Element&)const;
  bool operator<(const K&) const;
  friend ostream& operator<<(ostream& os, Element& ele){
    //How the Element is printed
    os << ele.key_ << ":";
    ostringstream oss;
    for (auto i=0; i < ele.count_; i++){
        oss << ele.values_[i] << ",";
    }
    string str = oss.str();
    os << str.substr(0, str.size() - 1); // Gets rid of trailing comma         
    return os;
  }
};

template<typename K, typename V>
Element<K,V>::Element(K key, initializer_list<V> v){
    key_ = key;
    count_  = v.size();
    size_t index = 0;
        for (auto val : v)
            values_[index++] = val;
}

template<typename K, typename V>
bool Element<K,V>::operator==(const Element& e)const{
    if ( key_ == e.key_ && count_ == e.count_ ){
        for (auto i=0; i < count_; i++){
            if ( values_[i] != e.values_[i] ){ 
                // Makes sure every value in values_ is equal
                return false;
            }
        }
    }else{
        return false;
    }
    return true;
}

// Compares Keys
template<typename K, typename V>
bool Element<K,V>::operator<(const K& key1) const{  
    // Now can use ele < key
    if ( key_ < key1 ){
        return true;
    }else{
        return false;
    }
}

template<typename K, typename V>
Element<K,V>::Element(const Element& ele){
    count_ = ele.count_;
    key_ = ele.key_;
    next_ = nullptr;
    copy( ele.values_, ele.values_ + element_array_size, values_ );
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// LIST //////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// Contains a pointer to first Element and var for the number of Elements
template<typename K, typename V>
class MVM{
public:
  Element<K, V> * data_head_ = nullptr;
  size_t num_keys_ = 0;

  //Element<K, V> * data_tail_ = nullptr;
  //size_t num_elements_ = 0;

  pair <Element<K,V>*, Element<K,V> *> find_key(K);
  MVM find_value(V);

  //Constructors
  MVM()=default;
  MVM(initializer_list<Element<K,V>>);

  //Rule of Three
  MVM(const MVM&);
  MVM& operator=(const MVM& other);
  ~MVM();

  //Other Functions
  size_t size();
  bool add(K,V);
  bool remove_key(K);
  MVM remove_value(V);

  friend ostream& operator<<(ostream& os, MVM& mv){
    //Code for the ostream operator
    ostringstream oss;
    for(auto ptr = mv.data_head_; ptr != nullptr; ptr = ptr->next_){
        oss << *ptr << " ";
    }
    string str = oss.str();
    os << str.substr(0, str.size() - 1);
    return os;
  }
};

// Code for MVM functions
template<typename K, typename V>
MVM<K,V>::MVM( initializer_list<Element<K,V>> ls ){
    num_keys_ = ls.size();
    // To vector for indexing
    vector<Element<K,V>> vec = ls;
    // Ptr to new Element copy of vec[0]
    data_head_ = new Element<K,V>(vec[0]);
    // Ptr starts a data_head_
    Element<K, V> *ptr = data_head_; 
    for ( int i = 1; i < num_keys_; i++){
        // Adds next Element
        ptr->next_ = new Element<K, V>(vec[i]); 
        ptr = ptr->next_; // Moves ptr down
    }
}

template<typename K, typename V>
MVM<K,V>::MVM(const MVM& mv){
    if (mv.data_head_ == nullptr){
        data_head_ = nullptr; // Does this if mv is empty
    }else{
        Element<K,V>* ptr = mv.data_head_;
        data_head_ = new Element<K,V>( *ptr );
        Element<K,V>* new_ele = data_head_;
        // Copies from mv to new list and links like above
        while (ptr->next_ != nullptr){
            new_ele->next_ = new Element<K,V>( *ptr->next_ );
            new_ele = new_ele->next_;
            ptr = ptr->next_;
        }
    }
}

template<typename K, typename V>
MVM<K,V>& MVM<K,V>::operator=(const MVM& mv){
    // Creates new swapable MVM and swaps
    MVM<K,V> * mvm1 = new MVM<K,V>(mv);
    swap( data_head_, mvm1->data_head_ );
    swap( num_keys_, mvm1->num_keys_ );
    delete mvm1;
    return *this;
}

template<typename K, typename V>
MVM<K,V>::~MVM(){
    // Deletes every Element from the linked list
    Element<K,V> *to_del = data_head_;
    while ( to_del != nullptr ){
        data_head_ = data_head_->next_;
        delete to_del;
        to_del = data_head_;
    }
    data_head_ = nullptr;
}

template<typename K, typename V>
pair<Element<K,V>*, Element<K,V>*> MVM<K,V>::find_key(K key){
    if ( num_keys_ == 0 ){
        // If empty
        return {nullptr, nullptr};
    }else{
        Element<K,V> *first = nullptr;
        Element<K,V> *second = nullptr;
        // Goes through the list one Element at a time
        for(Element<K,V> *n = data_head_; n != nullptr; n = n->next_){
            if ( n->key_ < key ){
                first = n; // first assigned to any Element <
            }else{
                second = n; // second is 1st Element >=
                break; 
            }
        }
        // first = Element before; second = Element after
        return {first, second};
    }
}

template<typename K, typename V>
size_t MVM<K,V>::size(){ return num_keys_; }

template<typename K, typename V>
MVM<K,V> MVM<K,V>::find_value(V val){
    MVM<K,V> keys;
    int j = 0;
    Element<K, V> *ptr = nullptr;
    for(Element<K,V> *n = data_head_; n != nullptr; n = n->next_){
        for ( int i = 0; i < n->count_; i++ ){
            // Looks through each value of each Element
            if ( n->values_[i] == val ){ // If val == val
                if ( j == 0 ){ // If first val found
                    // New Element made, data_head_ points to
                    keys.data_head_ = new Element<K,V>( n->key_, {val} );
                    ptr = keys.data_head_;
                }else{ // Not first found
                    // Links new Element to previous
                    ptr->next_ = new Element<K,V>( n->key_, {val} );
                    ptr = ptr->next_;
                }
                // For each key found
                keys.num_keys_++;
                j++;
            }
        }
    }
    return keys;
}

template<typename K, typename V>
bool MVM<K,V>::remove_key(K key){
    pair<Element<K,V>*, Element<K,V>*> found_key = find_key(key);
    // If key exists in MVM
    if ( found_key.second != nullptr && found_key.second->key_ == key ){
        if ( found_key.first == nullptr ){ // If key is from first Element
            // Moves data_head_ to Element after deleted Element
            data_head_ = found_key.second->next_;
            delete found_key.second; // Deletes Element
        }else{ // If not first Element
            // Links Element before to Element after. Omits deleted Element
            found_key.first->next_ = found_key.second->next_;
            delete found_key.second;
        }
        // If key removed
        num_keys_--;
        return true;
    }else{
        return false;
    }
}

template<typename K, typename V>
MVM<K,V> MVM<K,V>::remove_value(V val){
    MVM<K,V> keys = find_value(val);
    for(Element<K,V> *n = data_head_; n != nullptr; n = n->next_){
        for(Element<K,V> *k = keys.data_head_; k != nullptr; k = k->next_){
            // Compares Each key from find_value with the key in the MVM
            if ( n->key_ == k->key_ ){ // If key (Element) w/ value in it...
                vector<V> vals;
                int j = 1;
                //Each value in values_
                for ( int i = 0; i < n->count_; i++ ){ 
                    // Adds all vals not removed to new temp vec vals
                    if ( n->values_[i] != val ){
                        vals.push_back(n->values_[i]);
                    }
                }
                n->count_--;
                // Copies vals back into its values_ pointer
                copy( vals.begin(), vals.end(), n->values_ );
            }
        }
    }
    return keys;
}

template<typename K, typename V>
bool MVM<K,V>::add(K key,V val){
    pair<Element<K,V>*, Element<K,V>*> found_key = find_key(key);
    if ( found_key.second->key_ == key ){ // If key already exists
        if ( found_key.second->count_ == element_array_size ){
            return false; // If values_ is full
        }
        for ( int i = 0; i < found_key.second->count_; i++ ){
            if ( found_key.second->values_[i] == val ){
                return false; // If val already in key
            }
        }
        // Adds val to end of array values_
        found_key.second->values_[found_key.second->count_] = val;
        found_key.second->count_++;
    }else{  // If key does not exist
        if ( found_key.first == nullptr ){ // If new first Element in list
            // data_head_ points to new Element
            data_head_ == new Element<K,V>( key, {val} );
            // New Element points to old first Element
            data_head_->next_ = found_key.second;
        }else{ // Not first
            // Previous Element points to new Element
            found_key.first->next_ = new Element<K,V>( key, {val} );
            // New Element points to next Element
            found_key.first->next_->next_ = found_key.second;
        }
        num_keys_++;
    }
    return true;
}





