// matrix operations (0-index based)

#include <cassert>

#include <iostream>
#include <stdexcept>

template <typename T>
class matrix final {
   public:
    matrix(unsigned rows, unsigned columns) : m_{rows}, n_{columns} {
        mat_ = new T*[rows];
        for (unsigned i = 0; i < rows; i++) {
            mat_[i] = new T[columns];
        }
    }

    matrix(unsigned rows,
           unsigned columns,
           const std::initializer_list<std::initializer_list<T>> mat)
        : m_{rows}, n_{columns} {
        auto it = std::cbegin(mat);
        mat_ = new T*[rows];
        for (unsigned i = 0; i < rows; i++, ++it) {
            mat_[i] = new T[columns];
            std::copy(std::cbegin(*it), std::cend(*it), mat_[i]);
        }
    }

    ~matrix() noexcept {
        for (unsigned i = 0; i < m_; i++)
            delete mat_[i];
        delete mat_;
    }

    static auto zero(unsigned rows, unsigned columns) -> matrix {
        matrix<T> z{rows, columns};
        for (unsigned i = 0; i < rows; i++)
            for (unsigned j = 0; j < columns; j++)
                z.mat_[i][j] = T{};
        return z;
    }

    static auto identity(unsigned rows, unsigned columns) -> matrix {
        matrix<T> id{rows, columns};
        for (unsigned i = 0; i < rows; i++)
            for (unsigned j = 0; j < columns; j++)
                id.mat_[i][j] = i == j ? T{1} : T{};
        return id;
    }

    auto at(unsigned row, unsigned column) -> T& {
        if (row > m_ || column > n_)
            throw std::exception{};
        return mat_[row][column];
    }

    auto at(unsigned row, unsigned column) const -> const T& {
        if (row > m_ || column > n_)
            throw std::exception{};
        return mat_[row][column];
    }

    auto operator==(const matrix<T>& other) const -> bool {
        if (m_ != other.m_ || n_ != other.n_)
            return false;
        for (unsigned i = 0; i < m_; i++)
            for (unsigned j = 0; j < n_; j++)
                if (mat_[i][j] != other.mat_[i][j])
                    return false;
        return true;
    }

    auto operator!=(const matrix<T>& other) const -> bool { return !(*this == other); }

    auto operator+(const matrix<T>& other) const -> matrix<T> {
        if (m_ != other.m_ || n_ != other.n_)
            throw std::exception{};
        matrix<T> r(m_, n_);
        for (unsigned i = 0; i < m_; i++)
            for (unsigned j = 0; j < n_; j++)
                r.at(i, j) = mat_[i][j] + other.mat_[i][j];
        return r;
    }

    auto transpose() const -> matrix<T> {
        matrix<T> t{n_, m_};
        for (unsigned i = 0; i < m_; i++)
            for (unsigned j = 0; j < n_; j++)
                t.mat_[j][i] = mat_[i][j];
        return t;
    }

    auto rotate_clockwise() const -> matrix<T> {
        matrix<T> r{m_, n_};
        for (unsigned i = 0; i < m_; i++) {
            auto j2 = m_ - i - 1;
            for (unsigned j = 0; j < n_; j++) {
                auto i2 = j;
                r.mat_[i2][j2] = mat_[i][j];
            }
        }
        return r;
    }

    auto print() const noexcept -> void {
        for (unsigned i = 0; i < m_; i++) {
            std::cout << "| ";
            for (unsigned j = 0; j < n_; j++) {
                std::cout << mat_[i][j] << " ";
            }
            std::cout << "|" << std::endl;
        }
    }

   private:
    const unsigned m_;
    const unsigned n_;
    T** mat_;

    friend auto operator*<T>(const T& value, const matrix<T>& mat) -> matrix<T>;
    friend auto operator*<T>(const matrix<T>& mat, const T& value) -> matrix<T>;
    friend auto operator*<T>(const matrix<T>& a, const matrix<T>& b) -> matrix<T>;
};

// scalar multiplication x.A
template <typename T>
auto operator*(const T& value, const matrix<T>& mat) -> matrix<T> {
    return mat * value;
}

// scalar multiplication A.x
template <typename T>
auto operator*(const matrix<T>& mat, const T& value) -> matrix<T> {
    matrix<T> r{mat.m_, mat.n_};
    for (unsigned i = 0; i < mat.m_; i++)
        for (unsigned j = 0; j < mat.n_; j++)
            r.mat_[i][j] = value * mat.mat_[i][j];
    return r;
}

// matrix multiplication A.B
template <typename T>
auto operator*(const matrix<T>& a, const matrix<T>& b) -> matrix<T> {
    if (a.n_ != b.m_)
        throw std::exception{};
    auto c = matrix<T>::zero(a.m_, b.n_);
    for (unsigned i = 0; i < a.m_; i++)
        for (unsigned j = 0; j < b.n_; j++)
            for (unsigned k = 0; k < a.n_; k++)
                c.mat_[i][j] += a.mat_[i][k] * b.mat_[k][j];
    return c;
}

int main() {
    auto id1 = matrix<float>::identity(3, 3);
    assert(id1.at(1, 1) == 1.0f);
    assert(id1 == id1);
    auto id2 = matrix<float>::zero(3, 3);
    assert(id1 != id2);
    id2.at(0, 0) = 1.0f;
    id2.at(1, 1) = 1.0f;
    id2.at(2, 2) = 1.0f;
    assert(id1 == id2);

    auto zero = matrix<float>::zero(3, 3);
    assert(id1 + zero == id1);
    auto m1 = matrix<float>::zero(3, 3);
    m1.at(0, 0) = 2.0f;
    m1.at(1, 1) = 2.0f;
    m1.at(2, 2) = 2.0f;
    assert(id1 + id1 == m1);

    matrix<int> m2{2,
                   3,
                   {
                       {1, 8, -3},
                       {4, -2, 5},
                   }};
    assert(2 * m2 == m2 * 2);
    matrix<int> m3{2,
                   3,
                   {
                       {2, 16, -6},
                       {8, -4, 10},
                   }};
    assert(2 * m2 == m3);

    matrix<int> ma{2,
                   3,
                   {
                       {2, 3, 4},
                       {1, 0, 0},
                   }};
    matrix<int> mb{3,
                   2,
                   {
                       {0, 1000},
                       {1, 100},
                       {0, 10},
                   }};

    matrix<int> mc{2,
                   2,
                   {
                       {3, 2340},
                       {0, 1000},
                   }};
    assert(ma * mb == mc);
    try {
        assert(mc * mb == mc);
        assert(false);
    } catch (...) {
    }

    matrix<int> mx{2,
                   3,
                   {
                       {1, 2, 3},
                       {0, -6, 7},
                   }};
    matrix<int> mt{3,
                   2,
                   {
                       {1, 0},
                       {2, -6},
                       {3, 7},
                   }};
    assert(mx.transpose() == mt);
    assert(id1.transpose() == id1);

    matrix<int> my{3,
                   3,
                   {
                       {1, 2, 3},
                       {4, 5, 6},
                       {7, 8, 9},
                   }};
    matrix<int> mr{3,
                   3,
                   {
                       {7, 4, 1},
                       {8, 5, 2},
                       {9, 6, 3},
                   }};
    assert(my.rotate_clockwise() == mr);

    std::cout << "OK" << std::endl;
}
