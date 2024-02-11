#ifndef __WORD_SET___HPP
#define __WORD_SET___HPP

#include <cstddef>
#include <string>
#include <cmath>

namespace shindler::ics46::project3 {

// You may assume, in writing this function, that the given
// string consists solely of lower-case letters.

// To get the "number" that a letter-digit represents,
// subtract 'a' from it.
// e.g., (s[0]-'a') is the most significant "digit" of s.
// That would give you a 0 for a, etc;  add one to get 'a' = 1, 'b' = 2, etc.

// After every "digit" is processed, mod the current value by mod.
// This will keep you from having overflow.
[[nodiscard]] size_t polynomialHashFunction(const std::string &string,
                                            unsigned base, unsigned mod);

// These are value template parameters. You can pass in a value rather than a
// type into the parameter and use its value. This allows them to be set
// dynamically rather than having static constants within the class.
// Think of them as class constants (you can just use them like a variables
// named H1, H2, and EvictThreshold)
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
class BaseWordSet {
   private:
    // You may declare private functions and member variables here.
    size_t num_string;
    size_t num_capacity;
    std::string *uppertable;
    std::string *lowertable;
   public:
    explicit BaseWordSet(size_t initialCapacity);
    ~BaseWordSet();

    // You do not need to worry about implementing these. They are only
    // here to ensure that we let the compiler know these functions
    // should not exist.
    BaseWordSet(const BaseWordSet &) = delete;
    BaseWordSet(BaseWordSet &&) = delete;
    BaseWordSet &operator=(const BaseWordSet &) = delete;
    BaseWordSet &operator=(BaseWordSet &&) = delete;

    // adds the given string to the WordSet, so that any
    // future calls to contains(s) will return true, unless that is later
    // removed.
    void insert(const std::string &string);

    [[nodiscard]] bool contains(const std::string &string) const;

    // return how many distinct strings are in the set
    [[nodiscard]] size_t size() const noexcept;

    // return how large the underlying array is.
    [[nodiscard]] size_t capacity() const noexcept;

    void erase(const std::string &string);
};

// You Should not use anything within the _impl namespace in your code.
// Instead reference the H1, H2, and EvictThreshold template parameters
namespace _impl {
const static unsigned int BASE_H1 = 37;
const static unsigned int BASE_H2 = 41;
const unsigned int BASE_EVICTION_THRESHOLD = 5;
}  // namespace _impl

// Add a usings statement with the default values for the project.
using WordSet =
    BaseWordSet<_impl::BASE_H1, _impl::BASE_H2, _impl::BASE_EVICTION_THRESHOLD>;

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::BaseWordSet(size_t initialCapacity):num_string(0), num_capacity(initialCapacity), 
      uppertable(new std::string[initialCapacity]), 
      lowertable(new std::string[initialCapacity]){

}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
BaseWordSet<H1, H2, EvictThreshold>::~BaseWordSet() {
    delete[] uppertable;
    delete[] lowertable;
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::insert(const std::string &string) {
    if(contains(string))
    {return;}
    std::string temp = string;
    unsigned int evictCount = 0;
    while(evictCount<EvictThreshold){
        size_t hash1 = polynomialHashFunction(temp, H1, num_capacity);
        if (uppertable[hash1].empty()){
            uppertable[hash1] = temp;
            num_string++;
            return;
        }
        std::swap(temp, uppertable[hash1]);
        evictCount++;
        size_t hash2 = polynomialHashFunction(temp, H2, num_capacity);
        if(lowertable[hash2].empty()){
            lowertable[hash2] = temp;
            num_string++;
            return;
        }
        std::swap(temp, lowertable[hash2]);
        evictCount++;
    }
    //rehash
    size_t candidate  = 2*num_capacity;
    while(true){
        bool isPrime = true;
        for (int i = 2; i <= std::sqrt(candidate); ++i) {
            if (candidate % i == 0) {
                isPrime = false;
                break;
            }
        }
        if(isPrime){
            break;
        }
        ++candidate;
    }
    std::string* new_uppertable = new std::string[candidate];
    std::string* new_lowertable = new std::string[candidate];
    std::swap(new_uppertable, uppertable);
    std::swap(new_lowertable, lowertable);
    size_t temp_size = num_capacity;
    num_capacity = candidate;
    num_string=0;
    for(size_t i = 0; i<temp_size; ++i){
        if(!new_uppertable[i].empty())
        {insert(new_uppertable[i]);}
        if(!new_lowertable[i].empty())
        {insert(new_lowertable[i]);}
    }
    delete[] new_uppertable;
    delete[] new_lowertable;
    //insert new
    insert(temp);
}

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
bool BaseWordSet<H1, H2, EvictThreshold>::contains(
    const std::string &string) const {
    size_t hash1 = polynomialHashFunction(string, H1, num_capacity);
    if(uppertable[hash1]==string)
    {
        return true;
    }
    size_t hash2 = polynomialHashFunction(string, H2, num_capacity);
    return lowertable[hash2]==string;
}

// return how many distinct strings are in the set
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::size() const noexcept {
    return num_string;
}

// return how large the underlying array is.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
size_t BaseWordSet<H1, H2, EvictThreshold>::capacity() const noexcept {
    return num_capacity;
}

// removes this word if it is in the wordset.
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void BaseWordSet<H1, H2, EvictThreshold>::erase(const std::string &string) {
    size_t hash1 = polynomialHashFunction(string, H1, num_capacity);
    if(uppertable[hash1]==string)
    {
        uppertable[hash1]="";
    }
    size_t hash2 = polynomialHashFunction(string, H2, num_capacity);
    if(lowertable[hash2]==string)
    {
        lowertable[hash2]="";
    }
}

}  // namespace shindler::ics46::project3

#endif
