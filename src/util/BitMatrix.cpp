#include <iostream>
#include <cmath>
#include <fstream>
#include "BitMatrix.h"

namespace gameoflife {
    BitMatrix::BitMatrix(const BitMatrix &m) :
            rows(m.rows), columns(m.columns), size(m.size), bits(new group_type[m.size]{}) {
        for (int i = 0; i < m.size; i++) {
            bits[i] = m.bits[i];
        }
    }

    BitMatrix::BitMatrix(BitMatrix &&m) noexcept : rows(m.rows), columns(m.columns), size(m.size), bits(m.bits) {
        m.bits = nullptr;
    }

    BitMatrix::BitMatrix(int r, int c) {
        rows = r;
        columns = c;
        size = ceil((rows * columns) / (BITS_PER_GROUP * 1.0));
        bits = new group_type[size]{};
    }

    BitMatrix::~BitMatrix() {
        delete[] bits;
    }

    BitMatrix &BitMatrix::operator=(const BitMatrix &m) {
        if (this == &m)
            return *this;
        delete[] bits;
        rows = m.rows;
        columns = m.columns;
        size = m.size;
        bits = new group_type[m.size]{};
        for (int i = 0; i < m.size; i++) {
            bits[i] = m.bits[i];
        }
        return *this;
    }

    BitMatrix &BitMatrix::operator=(BitMatrix &&matrix) noexcept {
        delete[] bits;
        rows = matrix.rows;
        columns = matrix.columns;
        size = matrix.size;
        bits = matrix.bits;
        matrix.bits = nullptr;
        return *this;
    }

    std::ifstream &operator>>(std::ifstream &fs, BitMatrix &matrix) {
        int row, col;
        while (!fs.eof()) {
            fs >> row >> col;
            matrix.set(row, col);
        }
        return fs;
    }

    int BitMatrix::getRows() const {
        return rows;
    }

    int BitMatrix::getColumns() const {
        return columns;
    }

    bool BitMatrix::get(int row, int col) const {
        auto bit = toBitGroup(row, col);
        return bit.group & bit.masked;
    }

    void BitMatrix::set(int row, int col) {
        auto bit = toBitGroup(row, col);
        bit.group |= bit.masked;
    }

    BitMatrix::BitGroup BitMatrix::toBitGroup(int row, int col) const {
        int idx = row * columns + col;
        int group = idx / BITS_PER_GROUP;
        int offset = idx % BITS_PER_GROUP;
        group_type bit = static_cast<group_type>(1) << static_cast<group_type>(offset);
        return {bits[group], bit};
    }
}