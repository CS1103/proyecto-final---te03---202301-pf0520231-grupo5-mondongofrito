#include "matriz_vectores.h"
#include<iostream>

using namespace std;


int main() {
  std::vector<int> data = {};
  Matrix matriz(100, 20);
  matriz.CreateMatrix(data);
  matriz.ShowMatrix();

  return 0;
}
