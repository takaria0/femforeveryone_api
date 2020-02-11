#ifndef UTILS_H
#define UTILS_H

#include <vector>
using namespace std;

class Utils
{
private:

public:
  bool checkInsideCircumvent(vector<vector<double>> tris, vector<double> newP);
  vector<double> findTriangle(vector<vector<double>> triangles, vector<double> newPoint);
  vector<double> arrangeCounterClockwise(vector<double> coords);
  double distance(vector<double> p1, vector<double> p2);
  // template <class T, class U> vector<vector<double>> mul(T A, U B);
  // vector<vector<double>> scalar(double a, vector<vector<double>> matrix);
  // vector<vector<double>> add(vector<vector<double>> A, vector<vector<double>> B);
  // vector<vector<double>> transpose(vector<vector<double>> matrix);
  // vector<vector<double>> inverse(vector<vector<double>> matrix);
};

#endif