#include <string>

class BitArray
{
    public:
        BitArray();
        ~BitArray();

        /// @brief creates BitArray of a given length and value
        /// @param num_bits number of bits in array
        /// @param value value that will be written to first sizeof(long) bits
        /// of array
        explicit BitArray(int num_bits, unsigned long value = 0);

        /// @brief creates BitArray by copying
        /// @param b bitArray to copy
        BitArray(const BitArray& b);

        /// @brief swaps BitArrays values
        /// @param b BitArray to swap with
        void swap(BitArray& b);

        /// @brief assignes value of another BitArray to this BitArray
        /// @param b BitArray that will be assigned
        /// @return this BitArray
        BitArray& operator=(const BitArray& b);

        /// @brief resizes BitArray
        /// @param num_bits new size
        /// @param value value to initialize new bits with
        void resize(int num_bits, bool value = false);

        /// @brief clears BitArray
        void clear();

        /// @brief adds new bit to the end of BitArray
        /// @param bit value of bit to add
        void push_back(bool bit);

        /// @brief bitwise AND, that changes original BitArray
        /// @param b second BitArray
        /// @return changed BitArray
        BitArray& operator&=(const BitArray& b);

        /// @brief bitwise OR, that changes original BitArray
        /// @param b second BitArray
        /// @return changed BitArray
        BitArray& operator|=(const BitArray& b);

        /// @brief bitwise XOR, that changes original BitArray
        /// @param b second BitArray
        /// @return changed BitArray
        BitArray& operator^=(const BitArray& b);

        /// @brief shifts bits to the left, new bits are 0
        /// @param n shift
        /// @return this BitArray
        BitArray& operator<<=(int n);

        /// @brief shifts bits to the right, new bits are 0
        /// @param n shift
        /// @return this BitArray
        BitArray& operator>>=(int n);

        /// @brief creates new BitArray with shifted to the left bits, new bits are 0
        /// @param n shift
        /// @return shifted BitArray
        BitArray operator<<(int n) const;

        /// @brief creates new BitArray with shifted to the right bits, new bits are 0
        /// @param n shift
        /// @return shifted BitArray
        BitArray operator>>(int n) const;

        /// @brief set n-th bit to passed value
        /// @param n index of bit to change
        /// @param val value to change bit
        /// @return this BitArray
        BitArray& set(int n, bool val = true);

        /// @brief set every bit to true
        /// @return this BitArray
        BitArray& set();

        /// @brief set n-th bit to false
        /// @param n index of bit to change
        /// @return this BitArray
        BitArray& reset(int n);

        /// @brief set every bit to false
        /// @return this BitArray
        BitArray& reset();

        /// @brief checks if any bit is true
        /// @return true - if there's true bit; false - otherwise
        bool any() const;

        /// @brief checks if all bits are false
        /// @return true - if all bits are false; false - otherwise
        bool none() const;

        /// @brief creates and returns BitArray with inversed bits
        /// @return BitArray with inversed bits
        BitArray operator~() const;

        /// @brief counts true bits
        /// @return amount of true bits in BitArray
        int count() const;

        bool operator[](int i) const;

        /// @brief wrapper class for index operations
        class Wrapper
        {
            public:
                int index;
                operator bool() const;
                Wrapper& operator=(bool value);                
        };

        Wrapper& operator[](int i);

        /// @brief returns number of bits in BitArray
        /// @return length of BitArray in bits
        int size() const;

        /// @brief returns if BitArray is empty
        /// @return true - if empty; false - if not empty
        bool empty() const;

        /// @brief returns BitArray as string of '0' and '1'
        /// @return string of '0' and '1' of a size() length
        std::string to_string() const;

    private:
        int length = 0;
        int blocks = 0;
        const int bitsInBlock = sizeof(unsigned int) * 8;
        
        struct Block
        {
            Block* next;
            Block* prev;
            unsigned int bitHolder;
        };

        Block* start = NULL;
        Block* end = NULL;

        bool readBit(int index) const;
        void changeBit(int index, bool value);

        void remove(int num_bits);
        void removeLastBlock();
        int getBitsLastBlock();
        void addNewBlock();
        void add(int num_bits);

};

/// @brief returns if two BitArrays have the same bits
/// @param a first BitArray
/// @param b second BitArray
/// @return true if BitArrays have the same bits; false - otherwise
bool operator==(const BitArray& a, const BitArray& b);

/// @brief returns if two BitArrays don't have the same bits
/// @param a first BitArray
/// @param b second BitArray
/// @return false if BitArrays have the same bits; true - otherwise
bool operator!=(const BitArray& a, const BitArray& b);

/// @brief bitwise AND, that creates new BitArray
/// @param b1 first BitArray
/// @param b2 second BitArray
/// @return BitArray result of bitwise AND
BitArray operator&(const BitArray& b1, const BitArray& b2);

/// @brief bitwise OR, that creates new BitArray
/// @param b1 first BitArray
/// @param b2 second BitArray
/// @return BitArray result of bitwise OR
BitArray operator|(const BitArray& b1, const BitArray& b2);

/// @brief bitwise XOR, that creates new BitArray
/// @param b1 first BitArray
/// @param b2 second BitArray
/// @return BitArray result of bitwise XOR
BitArray operator^(const BitArray& b1, const BitArray& b2);