#ifndef _XOR_BITSET_H
#define _XOR_BITSET_H
#include <iostream>

#define _XOR_BITSET_BITS_PER_WORD  (__CHAR_BIT__ * __SIZEOF_LONG_LONG__)
#define _XOR_BITSET_WORDS(__n) \
  ((__n) / _XOR_BITSET_BITS_PER_WORD + \
   ((__n) % _XOR_BITSET_BITS_PER_WORD == 0 ? 0 : 1))
#define _ULL_ONE ull(1)

typedef unsigned long long ull;

template<size_t N>
class xor_bitset
{
    ull words[_XOR_BITSET_WORDS(N)] {0};
    friend class xor_reference;
public:
    template<size_t M>
    xor_bitset& operator ^= (const xor_bitset<M> &r) {
        for(ull i = 0; i < _XOR_BITSET_WORDS(N); i++) {
            words[i] ^= r.words[i];
        }
        return *this;
    }

    class xor_reference
    {
        size_t _pos;
        size_t _offset;
        ull* _bit;
    public:
        xor_reference(xor_bitset &bitset, size_t pos, size_t offset): _pos(pos), _offset(offset) {
            _bit = &bitset.words[_pos];
        }

        xor_reference operator=(bool b) {
            if(b)
                *_bit |= (_ULL_ONE << _offset);
            else
                *_bit &= ~(_ULL_ONE << _offset);
            return *this;
        }

        operator bool() {
            return *_bit & (_ULL_ONE << _offset);
        }

        friend std::ostream& operator<< (std::ostream& stream, const xor_reference& ref) {
            return stream << bool(*ref._bit & (_ULL_ONE << ref._offset));
        }
    };

    xor_reference operator[](size_t index) {
        size_t i = index / _XOR_BITSET_BITS_PER_WORD;
        size_t j = index % _XOR_BITSET_BITS_PER_WORD;
        return xor_reference(*this, i, j);
    }
};


#endif
