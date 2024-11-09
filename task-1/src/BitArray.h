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

        /// @brief wrapper class for index operations
        class Wrapper
        {
            public:
                operator bool() const;
                void operator=(bool value);
        };

        Wrapper& operator[](int index);

        /// @brief returns number of bits in BitArray
        /// @return length of BitArray in bits
        int size() const;

        /// @brief returns if BitArray is empty
        /// @return true - if empty; false - if not empty
        bool empty() const;

        /// @brief returns BitArray as string of '0' and '1'
        /// @return string of '0' and '1' of a size() length
        std::string to_string() const;
};