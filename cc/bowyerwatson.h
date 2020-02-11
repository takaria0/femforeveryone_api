#ifndef H_DELAUNAY
#define H_DELAUNAY

#include <vector>
#include <algorithm>

using namespace std;

class Delaunay
{
public:
  // using TriangleType = Triangle;
  // using EdgeType = Edge;
  // using VertexType = Vector2;

  // Delaunay() = default;
  // Delaunay(const Delaunay &) = delete;
  // Delaunay(Delaunay &&) = delete;

  vector<vector<double>> triangulate(vector<vector<double>> vertices, int number);
  vector<vector<double>> getTriangles();
  vector<vector<double>> getEdges();
  vector<vector<double>> getVertices();
  
  // Delaunay &operator=(const Delaunay &) = delete;
  // Delaunay &operator=(Delaunay &&) = delete;

private:
  vector<vector<double>> _triangles;
  vector<vector<double>> _borders;
  vector<vector<double>> _edges;
  vector<vector<double>> _vertices;
};

#endif
