#include "fem.h"
#include "linalg.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

double TwoDimensionTriangularFiniteElementMethod::eachAreaA(int i, int j, int k)
{
  double A = 0.5 * abs((triCoordinates[j][0] - triCoordinates[i][0]) * (triCoordinates[k][1] - triCoordinates[i][1]) -
                      (triCoordinates[k][0] - triCoordinates[i][0]) * (triCoordinates[j][1] - triCoordinates[i][1]));
  return A;
};

vector< vector<double> > TwoDimensionTriangularFiniteElementMethod::eachDmatrix()
{
  /*
  D = C*[
    [1, mu, 0],
    [mu, 1, 0],
    [0, 0, (1-mu)/2]
  ]
  C = E / 1-mu^2
  */
  double coef = (modulus / (1 - pow(poissonRatio, 2)));

  vector<vector<double> > D {
    {
      {coef * 1, coef * poissonRatio, 0},
      {coef * poissonRatio, coef * 1, 0},
      {0, 0, coef * (1 - poissonRatio)/2}
    }
  };

  return D;
};
vector< vector<double> > TwoDimensionTriangularFiniteElementMethod::eachBmatrix(int i, int j, int k)
{
  vector<vector<double> > B {
    {
      {triCoordinates[j][1] - triCoordinates[k][1], 0, triCoordinates[k][1] - triCoordinates[i][1], 0, triCoordinates[i][1] - triCoordinates[j][1], 0},
      {0, triCoordinates[k][0] - triCoordinates[j][0], 0, triCoordinates[i][0] - triCoordinates[k][0], 0, triCoordinates[j][0] - triCoordinates[i][0]},
      {triCoordinates[k][0] - triCoordinates[j][0], triCoordinates[j][1] - triCoordinates[k][1], triCoordinates[i][0] - triCoordinates[k][0], triCoordinates[k][1] - triCoordinates[i][1], triCoordinates[j][0] - triCoordinates[i][0], triCoordinates[i][1] - triCoordinates[j][1]}
    }
  };

  for (int a = 0; a < 3; a++)
  {
    for (int b = 0; b < 5; b++)
    {
      B[a][b] = (1 / 2 * eachAreaA(i, j, k)) * B[a][b];
    };
  };
  return B;
};
vector<vector<double>> TwoDimensionTriangularFiniteElementMethod::eachStiffnessMatrix(vector<vector<double>> K, int num)
{
  vector<double> ijk = triIndeces[num];
  int i = ijk[0];
  int j = ijk[1];
  int k = ijk[2];
  LinAlg lin; // linear algebra library

  vector< vector<double> > tempK;
  vector< vector<double> > B = eachBmatrix(i, j, k);
  vector< vector<double> > D = eachDmatrix();
  vector< vector<double> > B_T = lin.transpose(B);
  double A = eachAreaA(i, j, k); // e.g. i, j, k: 1 -> 2 -> 4
  double t = thickness;
  double a = thickness * A;

  tempK = lin.scalar(a, lin.mul(B_T, lin.mul(D, B))); // tA B^T D B;



  // assemble global stiffness matrix
  // this logic is on my iPad
  for (int index = 1; index < 4; index++) // i or j or k: three patterns
  {
    //////////////////////
    // from i to j
    int startRow_i = 2 * i;
    int interRow_j = 2 * j;
    int EndRow_k = 2 * k;
    ///////////////////////
    int startCol_i = 2 * i;
    int startCol_j = 2 * j;
    int startCol_k = 2 * k;
    ///////////////////////

    int assingTimes = 0;

    for (int a = startRow_i; a < EndRow_k + 3; a++)
    {
      if (a == interRow_j && a == interRow_j + 1)
      {
        for (int tempColIndex = 0; tempColIndex < tempK.size(); tempColIndex++) // b 0 ~ 6
        {
          // i
          K[a][startCol_i] = tempK[assingTimes][0];     // x_i
          K[a][startCol_i + 1] = tempK[assingTimes][1]; //y_i
          // j
          K[a][startCol_j] = tempK[assingTimes][2];     // x_j
          K[a][startCol_j + 1] = tempK[assingTimes][3]; // y_j
          // k
          K[a][startCol_k] = tempK[assingTimes][4];     // x_k
          K[a][startCol_k + 1] = tempK[assingTimes][5]; // y_k

          assingTimes += 1;
        }
      }
    }
  }
  return K;
};
vector< vector<double> > TwoDimensionTriangularFiniteElementMethod::stiffnessMatrix()
{
  vector< vector<double> > globalK(elements, vector<double>(elements, 0.0));
  vector<vector<double>> eachK(elements, vector<double>(elements, 0.0));
  LinAlg lin; // linear algebra library

  for (int num = 0; num < elements; num++)
  {
    eachK = eachStiffnessMatrix(eachK, num);
    globalK = lin.add(globalK, eachK);
  }
  return globalK;
};

vector<vector<double>> TwoDimensionTriangularFiniteElementMethod::displacements()
{
  vector<double> F(elements, 0.0);
  vector<vector<double>> U(elements, vector<double>(1, 0.0));
  LinAlg lin; // linear algebra library

  vector<vector<double>> K = stiffnessMatrix();
  vector<vector<double>> K_inverse(K.size(), vector<double>(K[0].size(), 0.0));
  K_inverse = lin.inverse(K);
  U = lin.mul(K_inverse, F);
  return U;
};
