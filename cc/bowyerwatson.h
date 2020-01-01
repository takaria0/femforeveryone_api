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

  Delaunay() = default;
  // Delaunay(const Delaunay &) = delete;
  // Delaunay(Delaunay &&) = delete;

  const vector<vector<double>> &triangulate(vector<vector<double>> &vertices, int number);
  const vector<vector<double>> &getTriangles() const;
  const vector<vector<double>> &getEdges() const;
  const vector<vector<double>> &getVertices() const;

  // Delaunay &operator=(const Delaunay &) = delete;
  // Delaunay &operator=(Delaunay &&) = delete;

private:
  vector<vector<double>> _triangles;
  vector<vector<double>> _edges;
  vector<vector<double>> _vertices;
};

#endif
