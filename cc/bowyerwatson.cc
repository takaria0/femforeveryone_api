#include "bowyerwatson.h"
#include <random>
#include <iostream>
using namespace std;

const vector<vector<double>> &Delaunay::triangulate(vector<vector<double>> &vertices, int number)
{
  // Store the vertices locally
  _vertices = vertices;

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
  for (int i = 0; i < number; i++)
  {
    vertices.push_back({distX(rng), distY(rng)});
  }

  // I don't know whats going on
  const double dx = maxX - minX;
  const double dy = maxY - minY;
  const double deltaMax = std::max(dx, dy);
  const double midx = 0.5 * (minX + maxX);
  const double midy = 0.5 * (minY + maxY);

  // initialize first triangle
  const vector<double> p1 = {midx - 20 * deltaMax, midy - deltaMax};
  const vector<double> p2 = {midx, midy + 20 * deltaMax};
  const vector<double> p3 = {midx + 20 * deltaMax, midy - deltaMax};

  // const VertexType p1(midx - 20 * deltaMax, midy - deltaMax);
  // const VertexType p2(midx, midy + 20 * deltaMax);
  // const VertexType p3(midx + 20 * deltaMax, midy - deltaMax);

  // // Create a list of triangles, and add the supertriangle in it
  // _triangles.push_back(p1);
  // _triangles.push_back(p2);
  // _triangles.push_back(p3);

  // for (auto p = begin(vertices); p != end(vertices); p++)
  // {
    // std::vector<EdgeType> polygon;

    // for (auto &t : _triangles)
    // {
    //   if (t.circumCircleContains(*p))
    //   {
    //     t.isBad = true;
    //     polygon.push_back(Edge{*t.a, *t.b});
    //     polygon.push_back(Edge{*t.b, *t.c});
    //     polygon.push_back(Edge{*t.c, *t.a});
    //   }
    // }

    // _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [](TriangleType &t) {
    //                    return t.isBad;
    //                  }),
    //                  end(_triangles));

    // for (auto e1 = begin(polygon); e1 != end(polygon); ++e1)
    // {
    //   for (auto e2 = e1 + 1; e2 != end(polygon); ++e2)
    //   {
    //     if (almost_equal(*e1, *e2))
    //     {
    //       e1->isBad = true;
    //       e2->isBad = true;
    //     }
    //   }
    // }

    // polygon.erase(std::remove_if(begin(polygon), end(polygon), [](EdgeType &e) {
    //                 return e.isBad;
    //               }),
    //               end(polygon));

    // for (const auto e : polygon)
    //   _triangles.push_back(TriangleType(*e.v, *e.w, *p));
  // }

  // _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3](TriangleType &t) {
  //                    return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
  //                  }),
  //                  end(_triangles));

  // for (const auto t : _triangles)
  // {
  //   _edges.push_back(Edge{*t.a, *t.b});
  //   _edges.push_back(Edge{*t.b, *t.c});
  //   _edges.push_back(Edge{*t.c, *t.a});
  // }

  _triangles = vertices;
  return _triangles;
}

const vector<vector<double>> &
Delaunay::getTriangles() const
{
  return _triangles;
}

const vector<vector<double>> &
Delaunay::getEdges() const
{
  return _edges;
}

const vector<vector<double>> &
Delaunay::getVertices() const
{
  return _vertices;
}
