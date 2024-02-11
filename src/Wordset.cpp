#include "Wordset.hpp"

#include <cstddef>
#include <string>

namespace shindler::ics46::project3 {

// returns s, as a number in the given base, mod the given modulus
size_t polynomialHashFunction(const std::string &string, unsigned int base,
                              unsigned int mod) {
    size_t hash_index = 0;
    for(const auto&str:string)
    {
        int value = str - 'a' + 1; 
        hash_index = (hash_index * base + value)%mod;
    }
    return hash_index;
}

}  // namespace shindler::ics46::project3
