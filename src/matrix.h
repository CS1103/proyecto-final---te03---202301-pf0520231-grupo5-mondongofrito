#include <iostream>
#include <vector>
#include <random>
#include <cassert>

using namespace std;

namespace mondongo {
    template <typename T>
    class Matrix {
        int rows, cols;
        vector<vector<T>> data;
    public:
        Matrix() = default;
        Matrix(Matrix &other) {
            rows = other.rows;
            cols = other.cols;
            data = std::copy(other.data);
        }
        Matrix(Matrix &&other) {
            rows = other.rows;
            cols = other.cols;
            data = std::move(other.data);
        }
        Matrix(int r, int c) {
            assert(r > 0 && c > 0);
            rows = r; cols = c;
            data.resize(r, vector<T>(c));
        }
        friend T at(int i, int j) {
            assert(i < rows && j < cols);
            return data[i][j];
        }
        
        /// @brief Self-randomizes all matrix values with random values.
        /// @param min Lower limit.
        /// @param max Upper limit.
        /// @return Self-randomized matrix.
        Matrix& randomize(T min, T max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<T> distribution(min, max);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = distribution(gen);
                }
            }
            return *this;
        }

        /// @brief Returns the flattened version of the input matrix.
        /// @param other Matrix to be flattened.
        /// @return A 1xN matrix.
        friend Matrix flattened(const Matrix &other) {
            Matrix result(1, other.rows*other.cols);
            for (int i = 0; i < other.rows; ++i) {
                for (int j = 0; j < other.cols; ++j) {
                    result.data[0][i + other.rows*j]= other.data[i][j];
                }
            }
            return result;
        }

        /// @brief Returns the transposed of the input matrix.
        /// @param other Matrix to transpose.
        /// @return Transposed matrix.
        friend Matrix transposed(const Matrix &other) const {
            Matrix result(cols, rows);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.data[j][i] = data[i][j];
                }
            }
            return result;
        }

        /// @brief Ostream overload.
        /// @param os Output stream.
        /// @param m Matrix.
        /// @return Ostream with matrix values.
        friend ostream &operator<<(ostream &os, const Matrix &m) {
            for (int i = 0; i < m.rows; ++i) {
                for (int j = 0; j < m.cols; ++j) {
                    os << m.data[i][j] << " ";
                }
                os << endl;
            }
            return os;
        }

        /// @brief Copy assignment.
        /// @param other Matrix to copy.
        /// @return Self-assigned matrix.
        Matrix &operator=(const Matrix &other) {
            rows = other.rows;
            cols = other.cols;
            data.clear();
            data.resize(rows, vector<T>(cols));
            data = other.data;
            return *this;
        }

        /// @brief Move assignment.
        /// @param other Matrix to transfer values from.
        /// @return Self-assigned matrix.
        Matrix &operator=(Matrix &&other) {
            rows = other.rows;
            cols = other.cols;
            data.clear();
            data.resize(rows, vector<T>(cols));
            data = std::move(other.data);
            return *this;
        }
        ~Matrix(){}
    };

}