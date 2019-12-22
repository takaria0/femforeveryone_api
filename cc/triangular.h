#ifndef TWO_DIM_DELAUNAY_H
#define TWO_DIM_DELAUNAY_H

#include <vector>
using namespace std;

class Delaunay
{
public:
  const int dims = 2;
  vector<vector<double>> coordinates; // [[x1, y1], [x2, y2], ... ]

  void triangulate(vector<vector<double>> &points);
};

#endif