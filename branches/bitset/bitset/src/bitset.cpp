#include "bitset.h"
#include <stdio.h>
#include <mili/mili.h>

namespace utils
{
    using namespace std;
    /*bit
    */
 
    class BitSetExceptionHierarchy {};
    
    typedef GenericException<BitSetExceptionHierarchy> BitsetException;
    
    DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidSizeException,
                                   BitSetExceptionHierarchy,
                                   "Bitsets sizes don't match");
    
    DEFINE_SPECIFIC_EXCEPTION_TEXT(IndexOutOfRangeException,
                                   BitSetExceptionHierarchy,
                                   "Index out of range");
    
    bitset::bit::bit() : value(false) {}
    bitset::bit::bit(bool v) : value(v) {}
    
    const bitset::bit bitset::bit::false_bit = bit(false);
    const bitset::bit bitset::bit::true_bit = bit(true);
    
    bitset::bit& bitset::bit::operator=(bool v) { value = v; return *this; }
    bitset::bit& bitset::bit::operator=(const bitset::bit::bit& b) { value = b.value; return *this; }
    
    bitset::bit& bitset::bit::operator|=(bool v) { value = value || v; return *this; }
    bitset::bit& bitset::bit::operator&=(bool v) { value = value && v; return *this; }
    bitset::bit& bitset::bit::operator^=(bool v) { if(v) value = !value; return *this; }
    bitset::bit& bitset::bit::operator-=(bool v) { if(v) value = false; return *this; }
    
    bool bitset::bit::operator~() const { return !value; }
    bitset::bit::operator bool() const { return value; }
    bitset::bit& bitset::bit::flip() { value = !value; return *this;}
    
    
    bitset::bitset() { }
    
    bitset::bitset(size_t size) { resize(size); } 
    
    bitset::bitset(const bitset& b) 
    {
        bits.resize(b.size());
        
        for(unsigned int i = 0; i < b.size(); i++)
            bits[i] = b[i];
    } 
     
    
    bitset& bitset::operator=(const bitset& b) 
    { 
        bits.clear();
        resize(b.size());

        for(unsigned int i = 0; i < bits.size(); i++)
        {
            bits[i] = b[i];
        }
        return *this; 
        
    }
    
    void bitset::resize(size_t n, const bit& v) { bits.resize(n, v); }
    void bitset::clear() { bits.clear(); }
    
    bitset& bitset::operator&=(const bitset& b)
    {
        if(b.size() != this->size()) throw InvalidSizeException();
       
        for(unsigned int i = 0; i < b.size(); i++)
            bits[i] &= b[i];
        return *this;
    }
    
    bitset& bitset::operator|=(const bitset& b)
    {
        if(b.size() != this->size()) throw InvalidSizeException();
        
        for(unsigned int i = 0; i < b.size(); i++)
            bits[i] |= b[i];
        return *this;
    }
    
    bitset& bitset::operator^=(const bitset& b)
    {
        if(b.size() != this->size()) throw InvalidSizeException();
        
        for(unsigned int i = 0; i < b.size(); i++)
            bits[i] ^= b[i];
        return *this;
    }
    
    bitset& bitset::operator-=(const bitset& b)
    {
        if(b.size() != this->size()) throw InvalidSizeException();
        
        for(unsigned int i = 0; i < b.size(); i++)
            bits[i] -= b[i];
        return *this;
    }
    
    bitset& bitset::operator<<=(size_t n)
    {
        if(n >= this->size()) throw IndexOutOfRangeException();
        
        for(unsigned int i = 0; i < n; i++)
        {
            bitset::bit last;
            bits.erase(bits.begin());
            bits.push_back(last);
        }
        return *this;
    }
    
    bitset& bitset::operator>>=(size_t n)
    {
        if(n >= this->size()) throw IndexOutOfRangeException();
        
        for(unsigned int i = 0; i < n; i++)
        {
            bitset::bit first;
            bits.erase(bits.end());
            bits.insert(bits.begin(), first);    
        }       
        
        return *this;
    }
    
    bitset bitset::operator<<(size_t n) const
    {
        bitset b(*this);
        b <<= n;
        return b;
    }
    
    bitset bitset::operator>>(size_t n) const
    {
        bitset b(*this);
        b >>= n;
        return b;
    }
    
    bitset& bitset::set()
    {
        for(unsigned int i = 0; i < this->size(); i++)
            bits[i] = true;
        return *this;
    }    
    
    bitset& bitset::set(size_t index, const bit& value)
    {
        if(index >= this->size()) throw IndexOutOfRangeException();

        bits[index] = value;
        return *this;
    }
    
    bitset& bitset::set(size_t from, size_t to, const bit& value)
    {
        if(from >= this->size() || to >= this->size() || from > to ) 
            throw IndexOutOfRangeException();
        
        for(unsigned int i = from; i <= to; i++)
        {
            bits[i] = value;    
        }
               
        return *this;
    }
    
    bitset& bitset::reset()
    {
        for(unsigned int i = 0; i < this->size(); i++)
            bits[i] = false;
        return *this;
    }
    
    bitset& bitset::reset(size_t n)
    {
        if(n >= this->size() ) throw IndexOutOfRangeException();
        
        bits[n] = false;
        return *this;
    }
    
    bitset& bitset::reset(size_t from, size_t to)
    {
        return set(from, to, bitset::bit::false_bit);
    }
      
    bitset& bitset::flip()
    {
        for(unsigned int i = 0; i < this->size(); i++)
            bits[i] = bits[i].flip();
        return *this;
    }
    
    bitset& bitset::flip(size_t index)
    {
        if(index >= this->size() ) throw IndexOutOfRangeException();
        
        bits[index] = bits[index].flip();
        return *this;
    }
    
    bitset& bitset::flip(size_t from, size_t to)
    {
        if(from >= this->size() || to >= this->size() || from > to ) 
            throw IndexOutOfRangeException();
        
        for(unsigned int i = from; i <= to; i++)
        {
            bits[i] = bits[i].flip();
        }
        
        return *this;
    }
    
    bitset bitset::operator~() const
    {
        bitset b(*this);
        for(unsigned int i = 0; i < b.size(); i++)
            b.bits[i] = ~b.bits[i];
        return b;
    }
    
    const bitset::bit bitset::operator[](size_t pos)
    {
        if(pos >= this->size()) throw IndexOutOfRangeException();
        
        return bits[pos];
    }
    
    bitset::bit bitset::operator[](size_t pos) const
    {
        if(pos >= this->size()) throw IndexOutOfRangeException();
        
        return bits[pos];
    }
    
    size_t bitset::size() const
    {
        return bits.size();
    }
    
    bool bitset::empty() const
    {
        return bits.empty();
    }
    
    bool operator==(const bitset& a, const bitset& b)
    {
        if(a.size() != b.size()) throw InvalidSizeException();
        
        for(unsigned int i = 0; i < a.size(); i++)
            if(a[i] != b[i])
                return false;
        return true;
    }
    
    bool operator!=(const bitset& a, const bitset& b)
    {
        return !(a == b);
    }   
}

