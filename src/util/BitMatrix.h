#ifndef GAMEOFLIFE_BITMATRIX_H
#define GAMEOFLIFE_BITMATRIX_H

#import <iostream>
#import <cstdint>

namespace gameoflife {
    class BitMatrix {
    public:
        BitMatrix(const BitMatrix &m);
        BitMatrix(BitMatrix &&matrix) noexcept;
        BitMatrix(int rows, int cols);
        ~BitMatrix();
        BitMatrix &operator=(const BitMatrix &m);
        BitMatrix &operator=(BitMatrix &&matrix) noexcept;
        friend std::ifstream &operator>>(std::ifstream &fs, BitMatrix &matrix);
        [[nodiscard]] int getRows() const;
        [[nodiscard]] int getColumns() const;
        [[nodiscard]] bool get(int row, int col) const;
        void set(int row, int col);
    private:
        static constexpr int BITS_PER_GROUP = 32;
        using group_type = std::uint_least32_t;
        struct BitGroup {
            group_type &group;
            group_type masked;
        };
        int rows;
        int columns;
        int size;
        group_type *bits;
        [[nodiscard]] BitGroup toBitGroup(int row, int col) const;
    };
}

#endif
