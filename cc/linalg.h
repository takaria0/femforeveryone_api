#ifndef LINALG_H
#define LINALG_H

#include <vector>
using namespace std;

class LinAlg
{
private:

public:
  template <class T, class U> vector<vector<double>> mul(T A, U B);
  vector<vector<double>> scalar(double a, vector<vector<double>> matrix);
  vector<vector<double>> add(vector<vector<double>> A, vector<vector<double>> B);
  vector<vector<double>> transpose(vector<vector<double>> matrix);
  vector<vector<double>> inverse(vector<vector<double>> matrix);
  double det(vector<vector<double>> matrix);
};

#endif