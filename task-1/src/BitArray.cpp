#include "BitArray.h"
#include <stdexcept>

void BitArray::removeLastBlock()
{
    Block *new_end = end->prev;
    delete end;
    end = new_end;
    if (blocks != 1) {
        end->next = NULL;
    } else {
        start = NULL;
    }

    blocks -= 1;
}

void BitArray::addNewBlock()
{
    Block *new_end = new Block;
    new_end->next = NULL;
    new_end->prev = end;
    new_end->bitHolder = 0;
    if (blocks != 0) {
        end->next = new_end;
    } else {
        start = new_end;
    }

    end = new_end;
    blocks += 1;
}

void BitArray::add(int num_bits)
{
    int new_length = length + num_bits;
    while (blocks * bitsInBlock < new_length) {
        addNewBlock();
    }
    length = new_length;
}

void BitArray::remove(int num_bits)
{
    int new_length = length - num_bits;
    while (blocks != 0 && (blocks - 1) * bitsInBlock >= new_length) {
        removeLastBlock();
    }
    length = new_length;
}

bool BitArray::readBit(int index) const
{
    int index_in_block = index % bitsInBlock;
    int shift = bitsInBlock - index_in_block - 1;
    unsigned int sample = 1;
    sample <<= shift;

    int index_of_cur_block = 0;
    Block *current_block = start;
    while ((index_of_cur_block + 1) * bitsInBlock <= index) {
        current_block = current_block->next;
        index_of_cur_block++;
    }

    sample &= current_block->bitHolder;
    if (sample == 0) {
        return false;
    } else {
        return true;
    }
}

void BitArray::changeBit(int index, bool value)
{
    int index_in_block = index % bitsInBlock;
    int shift = bitsInBlock - index_in_block - 1;
    unsigned int sample = 1;
    sample <<= shift;

    int index_of_cur_block = 0;
    Block *current_block = start;
    while ((index_of_cur_block + 1) * bitsInBlock <= index) {
        current_block = current_block->next;
        index_of_cur_block++;
    }

    if (value) {
        current_block->bitHolder |= sample;
    } else {
        current_block->bitHolder &= ~sample;
    }
}

BitArray::BitArray()
{
    length = 0;
    blocks = 0;
    start = NULL;
    end = NULL;
}

BitArray::~BitArray() { clear(); }

explicit BitArray::BitArray(int num_bits, unsigned long value)
{
    if (num_bits < 0) {
        throw std::invalid_argument("bad length");
    }
    if (num_bits == 0) {
        BitArray();
    } else {
        add(num_bits);
        start->bitHolder = value;
    }
}

BitArray::BitArray(const BitArray& b)
{
    length = b.length;
    blocks = b.blocks;
    Block *current_block_b = b.start;
    for (int i = 0; i < blocks; i++) {
        addNewBlock();
        end->bitHolder = current_block_b->bitHolder;
        current_block_b = current_block_b->next;
    }
}

BitArray& BitArray::operator=(const BitArray& b)
{
    BitArray new_bitarray(b);
    swap(new_bitarray);
    return *this;
}

void BitArray::swap(BitArray& b)
{
    std::swap(this->length, b.length);
    std::swap(this->blocks, b.blocks);
    std::swap(this->start, b.start);
    std::swap(this->end, b.end);
}

void BitArray::resize(int num_bits, bool value)
{
    if (num_bits < 0) {
        throw std::invalid_argument("bad length");
    }
    if (num_bits > length) {
        int old_length = length;
        add(num_bits - length);

        for (int i = old_length; i < length; i++) {
            changeBit(i, value);
        }
    } else if (num_bits < length) {
        remove(length - num_bits);
    }
}

void BitArray::clear() { remove(length); }

void BitArray::push_back(bool bit)
{
    add(1);
    changeBit(length - 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b)
{
    if (length != b.size()) {
        throw std::length_error("BitArrays have different size");
    }
    for (int i = 0; i < length; i++) {
        changeBit(i, readBit(i) & b[i]);
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b)
{
    if (length != b.size()) {
        throw std::length_error("BitArrays have different size");
    }
    for (int i = 0; i < length; i++) {
        changeBit(i, readBit(i) | b[i]);
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b)
{
    if (length != b.size()) {
        throw std::length_error("BitArrays have different size");
    }
    for (int i = 0; i < length; i++) {
        changeBit(i, readBit(i) ^ b[i]);
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n)
{
    if (n < 0) {
        throw std::invalid_argument("bad shift");
    } else if (n == 0) {
        return *this;
    }

    for (int i = 0; i < length - n; i++) {
        bool bit = readBit(i + n);
        changeBit(i, bit);
    }

    for (int i = length - n; i < length; i++) {
        changeBit(i, false);
    }
}

BitArray& BitArray::operator>>=(int n)
{
    if (n < 0) {
        throw std::invalid_argument("bad shift");
    } else if (n == 0) {
        return *this;
    }

    for (int i = length - n - 1; i >= 0; i--) {
        bool bit = readBit(i);
        changeBit(i + n, bit);
    }

    for (int i = 0; i < n; i++) {
        changeBit(i, false);
    }
}

// переполнение n?
BitArray BitArray::operator<<(int n) const
{
    if (n < 0) {
        throw std::invalid_argument("bad shift");
    }
    BitArray new_bitarray(*this);
    new_bitarray <<= n;
}

BitArray BitArray::operator>>(int n) const
{
    if (n < 0) {
        throw std::invalid_argument("bad shift");
    }
    BitArray new_bitarray(*this);
    new_bitarray <<= n;
}

BitArray& BitArray::set(int n, bool val)
{
    if (n < 0 || n > length - 1) {
        throw std::out_of_range("bad index");
    }
    changeBit(n, val);
    return *this;
}

BitArray& BitArray::set()
{
    for (int i = 0; i < length; i++) {
        changeBit(i, true);
    }
    return *this;
}

BitArray& BitArray::reset(int n)
{
    if (n < 0 || n > length - 1) {
        throw std::out_of_range("bad index");
    }
    changeBit(n, false);
    return *this;
}

BitArray& BitArray::reset()
{
    for (int i = 0; i < length; i++) {
        changeBit(i, false);
    }
    return *this;
}

bool BitArray::any() const
{
    bool result = false;
    for (int i = 0; i < length; i++) {
        if (readBit(i)) {
            result = true;
            break;
        }
    }
    return result;
}

bool BitArray::none() const { return !any(); }

BitArray BitArray::operator~() const
{
    BitArray result(length);
    for (int i = 0; i < length; i++) {
        result.changeBit(i, ~readBit(i));
    }
    return result;
}

int BitArray::count() const
{
    int counter = 0;
    for (int i = 0; i < length; i++) {
        if (readBit(i)) {
            counter++;
        }
    }

    return counter;
}

bool BitArray::operator[](int i) const
{
    if (i < 0 || i > length - 1) {
        throw std::out_of_range("bad index");
    }

    return readBit(i);
}

BitArray::Wrapper::Wrapper(BitArray& bitarray, int index)
    : bitarray(bitarray), index(index) {}

BitArray::Wrapper::operator bool() const { return bitarray.readBit(index); }

BitArray::Wrapper& BitArray::Wrapper::operator=(bool value)
{
    bitarray.changeBit(index, value);
    return *this;
}

BitArray::Wrapper& BitArray::operator[](int i)
{
    if (i < 0 || i > length - 1) {
        throw std::out_of_range("bad index");
    }
    Wrapper wrapper(*this, i);

    return wrapper;
}

int BitArray::size() const { return length; }

bool BitArray::empty() const { return length == 0; }

std::string BitArray::to_string() const
{
    std::string result(length, '0');
    for (int i = 0; i < length; i++) {
        if (readBit(i)) {
            result[i] = '1';
        }
    }
}

BitArray operator&(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b2.size()) {
        throw std::length_error("BitArrays have different size");
    }
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b2.size()) {
        throw std::length_error("BitArrays have different size");
    }
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() != b2.size()) {
        throw std::length_error("BitArrays have different size");
    }
    BitArray result(b1);
    result &= b2;
    return result;
}

bool operator==(const BitArray& a, const BitArray& b)
{
    if (a.size() != b.size()) {
        throw std::length_error("BitArrays have different size");
    }
    bool is_equal = true;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            is_equal = false;
            break;
        }
    }
    return is_equal;
}

bool operator!=(const BitArray& a, const BitArray& b) { return !(a == b); }