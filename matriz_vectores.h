#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Matrix {
private:
  int cols = 0;
  int rows = 0;
  std::vector<std::vector<int>> data;

public:
  Matrix(int nrows, int ncols) : rows(nrows), cols(ncols) {
    data.resize(rows, vector<int>(cols, 0));
  }

  void setData(vector<vector<int>> &newData) {
    if (newData.size() != rows ||
        (newData.size() > 0 && newData[0].size() != cols)) {
      std::cout
          << "Error: las dimensiones de los datos no coinciden con la matriz"
          << endl;
      return;
    }
    data = newData;
  }

  void CreateMatrix(vector<int> values) {
    int layers = values.size() / (rows * cols);
    int index = 0;
    for (int i = 0; i < layers; i++) {
      for (int j = i; j < cols - i; j++) {
        data[i][j] = values[index++];
      }
      for (int j = i + 1; j < rows - i; j++) {
        data[j][cols - i - 1] = values[index++];
      }
      for (int j = cols - i - 2; j >= i; j--) {
        data[rows - i - 1][j] = values[index++];
      }
      for (int j = rows - i - 2; j > i; j--) {
        data[j][i] = values[index++];
      }
    }
  }

  void ShowMatrix() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << data[i][j] << " ";
      }
      cout << endl;
    }
  }

  Matrix multiply(const Matrix &b) {
    if (cols != b.rows) {
      throw std::invalid_argument("Matrices no pueden ser multiplicadas");
    }

    Matrix result(rows, b.cols);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < b.cols; j++) {
        for (int k = 0; k < cols; k++) {
          result.data[i][j] += data[i][k] * b.data[k][j];
        }
      }
    }
    // gaaaa
    return result;
  }
  Matrix transpose() {
    Matrix transposed(cols, rows);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        transposed.data[j][i] = data[i][j];
      }
    }
    return transposed;
  }

//falta el otro aparte de transpose cuma
//hola
  ~Matrix(){};
};
