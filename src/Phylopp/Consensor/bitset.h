// Copyright (C) 2011, FuDePAN


#ifndef BITSET_H
#define BITSET_H

#include <vector>

namespace Consensus
{
    class bitset
    {
    public:

        class bit
        {
        private:
            bool value;
        public:

            static const bit false_bit;
            static const bit true_bit;

            bit();
            bit(bool v);

            bit& operator=(bool value);
            bit& operator=(const bit& b);

            bit& operator|=(bool value);
            bit& operator&=(bool value);
            bit& operator^=(bool value);
            bit& operator-=(bool value);

            bool operator~() const;
            operator bool() const;
            bit& flip();
        };


        bitset();

        bitset(size_t size);

        bitset(const bitset& b);

        bitset& operator=(const bitset& b);

        void resize(size_t n, const bit& value = bit::false_bit);
        void clear();

        bitset& operator&=(const bitset& b);
        bitset& operator|=(const bitset& b);
        bitset& operator^=(const bitset& b);
        bitset& operator-=(const bitset& b);
        bitset& operator<<=(size_t n);
        bitset& operator>>=(size_t n);
        bitset operator<<(size_t n) const;
        bitset operator>>(size_t n) const;

        bitset operator&(const bitset& b);

        bitset& set(size_t index, const bit& value = bit::true_bit);
        bitset& set(size_t from, size_t to, const bit& value = bit::true_bit);
        bitset& set();
        bitset& reset(size_t index);
        bitset& reset(size_t from, size_t to);
        bitset& reset();
        bitset& flip(size_t index);
        bitset& flip(size_t from, size_t to);
        bitset& flip();

        bitset operator~() const;

        const bit operator[](size_t pos);
        bit operator[](size_t pos) const;

        size_t size() const;
        bool empty() const;
        void print();

    private:
        std::vector<bitset::bit> bits;
    };

bool operator==(const bitset& a, const bitset& b);
bool operator<(const bitset& a, const bitset& b);
bool operator!=(const bitset& a, const bitset& b);

}

#endif
