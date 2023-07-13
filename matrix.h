#include <iostream>
#include <vector>
#include <random>
#include <cassert>

using namespace std;

namespace mondongo {
    template <typename T>
    class Matrix { 
    public:
        int rows, cols;
        vector<vector<T>> at;
        Matrix() = default;
        Matrix(Matrix &other) {
            rows = other.rows;
            cols = other.cols;
            at = std::copy(other.at);
        }
        Matrix(Matrix &&other) {
            rows = other.rows;
            cols = other.cols;
            at = std::move(other.at);
        }
        Matrix(int r, int c) {
            assert(r > 0 && c > 0);
            rows = r; cols = c;
            at.resize(r, vector<T>(c));
        }
        Matrix& randomize(T min, T max) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<T> distribution(min, max);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    at[i][j] = distribution(gen);
                }
            }
            return *this;
        }
        friend Matrix flattened(const Matrix &other) {
            Matrix result(1, other.rows*other.cols);
            for (int i = 0; i < other.rows; ++i) {
                for (int j = 0; j < other.cols; ++j) {
                    result.at[0][i + other.rows*j]= other.at[i][j];
                }
            }
            return result;
        }
        Matrix transposed() const {
            Matrix result(cols, rows);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.at[j][i] = at[i][j];
                }
            }
            return result;
        }

        Matrix operator+(const Matrix& other) const {
            assert(rows == other.rows && cols == other.cols);
            Matrix result(rows, cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.at[i][j] = at[i][j] + other.at[i][j];
                }
            }
            return result;
        }

        Matrix operator-(const Matrix& other) const {
            assert(rows == other.rows && cols == other.cols);
            Matrix result(rows, cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.at[i][j] = at[i][j] - other.at[i][j];
                }
            }
            return result;
        }

        Matrix operator*(const Matrix& other) const {
            assert(cols == other.rows);
            Matrix result(rows, other.cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < other.cols; ++j) {
                    for (int k = 0; k < cols; ++k) {
                        result.at[i][j] += at[i][k] * other.at[k][j];
                    }
                }
            }
            return result;
        }

        Matrix elementwise_product(const Matrix& other) const {
            assert(rows == other.rows && cols == other.cols);
            Matrix result(rows, cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.at[i][j] = at[i][j] * other.at[i][j];
                }
            }
            return result;
        }

        friend ostream &operator<<(ostream &os, const Matrix &m) {
            for (int i = 0; i < m.rows; ++i) {
                for (int j = 0; j < m.cols; ++j) {
                    os << m.at[i][j] << " ";
                }
                os << endl;
            }
            return os;
        }
        Matrix &operator=(const Matrix &other) {
            rows = other.rows;
            cols = other.cols;
            at.clear();
            at.resize(rows, vector<T>(cols));
            at = other.at;
            return *this;
        }
        Matrix &operator=(Matrix &&other) {
            rows = other.rows;
            cols = other.cols;
            at.clear();
            at.resize(rows, vector<T>(cols));
            at = std::move(other.at);
            return *this;
        }
        ~Matrix(){}
    };

}

