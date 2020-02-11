#include "utils.h"
#include "linalg.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// check whether a new point exist inside circumvent circle or not. for all triangles.
// if do not, return false
bool Utils::checkInsideCircumvent(vector<vector<double>> tris, vector<double> newP)
{
  std::cout << " -------------------------------------------------------------------\n";
  std::cout << "checkInsideCircumvent";
  std::cout << " TRIS +++++++++++++++++++++++++++++++++++++++++++++\n";
  for (int num = 0; num < tris.size(); num++)
  {
    std::cout << "[ ";
    for (int nem = 0; nem < tris[num].size(); nem++)
    {
      std::cout <<  tris[num][nem] << ", ";
    }
    std::cout << "]\n";
  }
  std::cout << " --------------------------------------------------------------------\n";

  if (tris[0].size() < 6)
  {

    std::cout << " -------------------------------------------------------------------\n";
    std::cout << "tris.size() error: tris[0].size() must be 6 ->" << tris[0].size() << "\n";
    return false;
  }

  for (int i = 0; i < tris.size(); ++i)
  {
    vector<double> center;
    double Sx, Sy, a, b, r;
    double Ax = tris[i][0];
    double Ay = tris[i][1];
    double Bx = tris[i][2];
    double By = tris[i][3];
    double Cx = tris[i][4];
    double Cy = tris[i][5];
    double Apow = Ax * Ax + Ay * Ay;
    double Bpow = Bx * Bx + By * By;
    double Cpow = Cx * Cx + Cy * Cy;

    LinAlg lin;

    Sx = 0.5 * lin.det({{Apow, Ay, 1},
                        {Bpow, By, 1},
                        {Cpow, Cy, 1}});
    Sy = 0.5 * lin.det({{Ax, Apow, 1},
                        {Bx, Bpow, 1},
                        {Cx, Cpow, 1}});
    a = lin.det({{Ax, Ay, 1},
                 {Bx, By, 1},
                 {Cx, Cy, 1}});
    b = lin.det({{Ax, Ay, Apow},
                 {Bx, By, Bpow},
                 {Cx, Cy, Cpow}});

    double Spow = Sx * Sx + Sy * Sy;

    center = {Sx / a, Sy / a};
    r = pow( ((b/a) + (Spow / pow(a, 2))), 0.5);

    // std::cout << "Ax = " << triangles[i][0] << "\n";
    // std::cout << "Ay = " << triangles[i][1] << "\n";
    // std::cout << "Bx = " << triangles[i][2] << "\n";
    // std::cout << "By = " << triangles[i][3] << "\n";
    // std::cout << "Cx = " << triangles[i][4] << "\n";
    // std::cout << "Cy = " << triangles[i][5] << "\n\n";

    // std::cout << "Apow = " << Apow << "\n";
    // std::cout << "Bpow = " << Bpow << "\n";
    // std::cout << "Cpow = " << Cpow << "\n\n";

    // std::cout << "Sx = " << Sx << "\n";
    // std::cout << "Sy = " << Sy << "\n";
    // std::cout << "a = " << a << "\n";
    // std::cout << "b = " << b << "\n\n";

    // std::cout << "r = " << r << "\n";
    // std::cout << "center x = " << center[0] << "\n";
    // std::cout << "       y = " << center[1] << "\n";

    // std::cout << "newP x = " << newP[0] << "\n";
    // std::cout << "         y = " << newP[1] << "\n\n";

    // std::cout << "distance = " << distance(center, newP) << "\n";
    // std::cout << "r = " << r << "\n\n";

    // if (distance(center, newP) < r)
    // if (distance(center, newP) < r)
    // {
      // return false;
    // }
    // else
    // {
      return true;
    // }
  };
};

vector<double> Utils::arrangeCounterClockwise(vector<double> coords)
{
  vector<double> triclock;
  std::cout << "This is something happens. \n";
  std::cout << " --------------------------------------------------------------------\n";
  std::cout << " BEFORE ARRANGEMENT TRIANGLE +++++++++++++++++++++++++++++++++++++++++++++\n";
  for (int num = 0; num < coords.size(); num++)
  {
    std::cout << "[ " << coords[num] << " ] \n";
  }
  std::cout << " --------------------------------------------------------------------\n";
  // set both x and y min as i th coordinate
  if ( (coords[0] < coords[2] and coords[0] < coords[4]) or (coords[1] < coords[3] and coords[1] < coords[5]))
  {
    triclock.push_back(coords[0]); // ith 
    triclock.push_back(coords[1]); // ith
    // set y min as j th
    if (coords[3] < coords[5])
    {
      triclock.push_back(coords[2]); // jth
      triclock.push_back(coords[3]); // jth
      triclock.push_back(coords[4]); // kth
      triclock.push_back(coords[5]); // kth
    }
    else
    {
      triclock.push_back(coords[4]);
      triclock.push_back(coords[5]);
      triclock.push_back(coords[2]);
      triclock.push_back(coords[3]);
    }
  }
  else if ((coords[2] < coords[0] and coords[2] < coords[4]) or (coords[3] < coords[1] and coords[3] < coords[5]))
  {
    triclock.push_back(coords[2]);
    triclock.push_back(coords[3]);
    // set y min as j th
    if (coords[1] < coords[5])
    {
      triclock.push_back(coords[0]);
      triclock.push_back(coords[1]);
      triclock.push_back(coords[4]);
      triclock.push_back(coords[5]);
    }
    else
    {
      triclock.push_back(coords[4]);
      triclock.push_back(coords[5]);
      triclock.push_back(coords[0]);
      triclock.push_back(coords[1]);
    }
  }
  else if ((coords[4] < coords[0] and coords[4] < coords[2]) or (coords[5] < coords[1] and coords[5] < coords[3]))
  {
    triclock.push_back(coords[4]);
    triclock.push_back(coords[5]);
    // set y min as j th
    if (coords[3] < coords[1])
    {
      triclock.push_back(coords[2]);
      triclock.push_back(coords[3]);
      triclock.push_back(coords[0]);
      triclock.push_back(coords[1]);
    }
    else
    {
      triclock.push_back(coords[0]);
      triclock.push_back(coords[1]);
      triclock.push_back(coords[2]);
      triclock.push_back(coords[3]);
    }
  }

  if (triclock.size() < 6)
  {
    std::cout << " --------------------------------------------------------------------\n";
    std::cout << " FAILED TO GENERATE NEW TRIANGLE ++++++++++++++++++++++++++++++++++++\n";
    std::cout << " triangle.size() = " << triclock.size()  << "\n";
    std::cout << " --------------------------------------------------------------------\n";
  }

  std::cout << " --------------------------------------------------------------------\n";
  std::cout << " generated NEW triangle +++++++++++++++++++++++++++++++++++++++++++++\n";
  for (int num = 0; num < triclock.size(); num++)
  {
    std::cout << "[ " << triclock[num] << " ] \n";
  }
  std::cout << " --------------------------------------------------------------------\n";

  return triclock;
    // return coords;
}

vector<double> Utils::findTriangle(vector<vector<double>> triangles, vector<double> newPoint)
{
  std::cout << "I entered findTriangle \n";
  vector<double> tempTriangle;
  int nearestIndex = 0;
  double distSum = 90000000000.0;

  // find nearest triangle
  for (int i = 0; i < triangles.size(); i++)
  {
    vector<double> tempCoord1 = {triangles[i][0], triangles[i][1]}; // [x1, y1]
    vector<double> tempCoord2 = {triangles[i][2], triangles[i][3]}; // [x2, y2]
    vector<double> tempCoord3 = {triangles[i][4], triangles[i][5]}; // [x3, y3]

    double dist1 = distance(tempCoord1, newPoint);
    double dist2 = distance(tempCoord2, newPoint);
    double dist3 = distance(tempCoord3, newPoint);
    if (distSum > dist1 + dist2 + dist3)
    {
      double distSum = dist1 + dist2 + dist3;
      nearestIndex = i;
    }
  }

  // get nearest triangle;
  vector<double> nearestCoord1 = {triangles[nearestIndex][0], triangles[nearestIndex][1]}; // [x1, y1]
  vector<double> nearestCoord2 = {triangles[nearestIndex][2], triangles[nearestIndex][3]}; // [x2, y2]
  vector<double> nearestCoord3 = {triangles[nearestIndex][4], triangles[nearestIndex][5]}; // [x3, y3]

  double neardist1 = distance(nearestCoord1, newPoint);
  double neardist2 = distance(nearestCoord2, newPoint);
  double neardist3 = distance(nearestCoord3, newPoint);

  if (neardist1 > neardist2 && neardist1 > neardist3)
  {
    tempTriangle = arrangeCounterClockwise({
        nearestCoord2[0],
        nearestCoord2[1],
        nearestCoord3[0],
        nearestCoord3[1],
        newPoint[0],
        newPoint[1],
    });
    return tempTriangle;
  }
  if (neardist2 > neardist1 && neardist2 > neardist3)
  {
    tempTriangle = arrangeCounterClockwise({
        nearestCoord1[0],
        nearestCoord1[1],
        nearestCoord3[0],
        nearestCoord3[1],
        newPoint[0],
        newPoint[1],
    });
    return tempTriangle;
  }
  else if (neardist3 > neardist2 && neardist3 > neardist1)
  {
    tempTriangle = arrangeCounterClockwise({
        nearestCoord2[0],
        nearestCoord2[1],
        nearestCoord1[0],
        nearestCoord1[1],
        newPoint[0],
        newPoint[1],
    });
  }
  return tempTriangle;
}

double Utils::distance(vector<double> p1, vector<double> p2)
{
  return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
}