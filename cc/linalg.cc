#include "linalg.h"
#include <vector>

using namespace std;

vector<vector<double>> LinAlg::transpose(vector<vector<double>> matrix)
{
  vector<vector<double>> matrix_t(matrix.size(), vector<double>(matrix[0].size(), 0));

  for (int i=0; i<matrix.size(); i++)
  {
    for (int j = 0; j < matrix[j].size(); j++)
    {
      matrix_t[j][i] = matrix[i][j];
    }
  }
  return matrix_t;
}

vector<vector<double>> LinAlg::inverse(vector<vector<double>> matrix)
{
  vector<vector<double>> matrix_t(matrix.size(), vector<double>(matrix[0].size(), 0));

  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[j].size(); j++)
    {
      matrix_t[j][i] = matrix[i][j];
    }
  }
  return matrix_t;
}

template <class T, class U>
vector<vector<double>> LinAlg::mul(T A, U B)
{
  // C = A * B

  vector<vector<double>> C(A.size(), vector<double>(B[0].size(), 0.0));

  for (int i = 0; i < A.size(); i++)
  {
    for (int j = 0; j < B[0].size(); j++)
    {
      for (int k = 0; k < A[0].size(); k++) // A[0].size() === B.size()
      {
        C[i][j] += A[i][k] * B[j][k];
      }
    }
  }

  return C;
}

vector<vector<double>> LinAlg::scalar(double a, vector<vector<double>> matrix)
{
  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[j].size(); j++)
    {
      matrix[j][i] = a * matrix[i][j];
    }
  }
  return matrix;
}

vector<vector<double>> LinAlg::add(vector<vector<double>> A, vector<vector<double>> B)
{
  // C = A + B
  if (A.size() != B.size() || A[0].size() != B[0].size())
  {
    return ;
  }

  vector<vector<double>> C(A.size(), vector<double>(B[0].size(), 0.0));
  for (int i = 0; i < A.size(); i++)
  {
    for (int j = 0; j < B[0].size(); j++)
    {
      C[i][j] = A[i][j] + B[i][j];
    }
  }
  return C;
}