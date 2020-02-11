#include "bowyerwatson.h"
#include "utils.h"
#include <random>
#include <iostream>
using namespace std;

vector<vector<double>> Delaunay::triangulate(vector<vector<double>> vertices, int number)
{
  // Initialization
  double minX = vertices[0][0];
  double minY = vertices[0][1];
  double maxX = minX;
  double maxY = minY;

  // find min X, Y and max X, Y and update
  for (std::size_t i = 0; i < vertices.size(); ++i)
  {
    if (vertices[i][0] < minX)
      minX = vertices[i][0];
    if (vertices[i][1] < minY)
      minY = vertices[i][1];
    if (vertices[i][0] > maxX)
      maxX = vertices[i][0];
    if (vertices[i][1] > maxY)
      maxY = vertices[i][1];
  }

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<> distX(minX, maxX);
  std::uniform_real_distribution<> distY(minY, maxY);
  // std::cout << dist6(rng) << std::endl;

  // add random coordinates
  for (int i = 0; i < number * 2; i++)
  {
    _vertices.push_back({distX(rng), distY(rng)});
  }

  // have to add a super triangle first
  // init
  // Store the vertices locally
  _borders = vertices;
  _triangles.push_back({
      _borders[3][0],
      _borders[3][1],
      _borders[1][0],
      _borders[1][1],
      _borders[0][0],
      _borders[0][1],
  });
  _triangles.push_back({
      _borders[3][0],
      _borders[3][1],
      _borders[2][0],
      _borders[2][1],
      _borders[1][0],
      _borders[1][1],
  });

  Utils util;

  // test
  // for (int i = 0; i < _vertices.size(); ++i)
  // {
  //   vector<double> newpoints = {_vertices[i][0], _vertices[i][1]};
  //   vector<double> tempTri = util.findTriangle(_triangles, newpoints);
  //   _triangles.push_back(tempTri);
  // }
  //////////////////


  int i = 0; // don't change until make an super triangle
  int loopCount = _vertices.size();
  bool result;
  while (i < loopCount)
  {
    std::cout << "here is -> " << i << "\n";
    std::cout << "_vertices size is -> " << _vertices.size() << "\n";
    //////////////////////////////////////
    // Here is the cause of this problem
    std::cout << "before abe\n";
    double abe = _vertices[i][1];
    std::cout << "before create tempVertex\n";
    vector<double> tempVertex = {_vertices[i][0], _vertices[i][1]};
    std::cout << "before checkInsideCircumvent \n";
    result = util.checkInsideCircumvent(_triangles, tempVertex);
    // result = true;
    //////////////////////////////////////

    if (i > _vertices.size())
    {
      break;
    }
    if (result)
    {
      // good triangle
      std::cout << " --------------------------------------------------------------------\n";
      std::cout << " good +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
      std::cout << " --------------------------------------------------------------------\n";
      vector<double> newpoints = {_vertices[i][0], _vertices[i][1]};
      vector<double> tempTri = util.findTriangle(_triangles, newpoints);
      _triangles.push_back(tempTri);
      i += 1;
    }
    else
    {
      // bad triangle
      std::cout << " --------------------------------------------------------------------\n";
      std::cout << " bad ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| \n";
      std::cout << " --------------------------------------------------------------------\n";
      _vertices.push_back({distX(rng), distY(rng)});
      ++i;
      loopCount += 1;
    }
    // std::cout << "_triangles max_size: " << _triangles.max_size() << "\n";
    // std::cout << "_vertices max_size: " << _vertices.max_size() << "\n";
  }
  // _triangles = _vertices;
  return _triangles;
}

vector<vector<double>> Delaunay::getTriangles()
{
  return _triangles;
}

vector<vector<double>> Delaunay::getEdges()
{
  return _edges;
}

vector<vector<double>> Delaunay::getVertices()
{
  return _vertices;
}
