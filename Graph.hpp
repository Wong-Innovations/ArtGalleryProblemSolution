#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <vector>
#include <cmath>

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

using std::vector;
using std::cout;
using std::ostream;

enum Color { None, Red, Yellow, Blue }; //Color limited to these values (Enumeration declaration)

struct Point // A tuple containing two ints
{
    int x, y;
    friend bool operator== (const Point &lhs, const Point &rhs);
};

struct Edge // A tuple containing two Points
{
    Point src, dest;
    friend bool operator== (const Edge &lhs, const Edge &rhs);
};

struct Vertex // A Point which is connected to one or more other points
{
    Point src; //root point
    vector<Point> dest; //vector of connected points
    int color = Color(None);

    inline Vertex& operator= (const Vertex &rhs);
    friend ostream& operator<< (ostream &os, const Vertex &v);
};

double dot(Point a, Point b, Point c) {
    int segment1_x = a.x-b.x, segment1_y = a.y-b.y;
    int segment2_x = c.x-b.x, segment2_y = c.y-b.y;
    return (segment1_x*segment2_x + segment1_y*segment2_y);
}

// Given three colinear points a, b, p, the function checks if
// point p lies on line segment 'ab'
bool onSegment(Point a, Point b, Point p)
{
    if (p.x < MAX(a.x, b.x) && p.x > MIN(a.x, b.x) &&
        p.y < MAX(a.y, b.y) && p.y > MIN(a.y, b.y))
    {
      return true;
    }
    return false;
}

// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'a1b1'
// and 'a2b2' intersect.
bool doIntersect(Point a1, Point b1, Point a2, Point b2)
{
    //FIX SO IT IGNORES COMMON VERTEX
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(a1, b1, a2);
    int o2 = orientation(a1, b1, b2);
    int o3 = orientation(a2, b2, a1);
    int o4 = orientation(a2, b2, b1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // a1, b1 and a2 are colinear and a2 lies on segment a1b1
    if (o1 == 0 && onSegment(a1, a2, b1)) return true;

    // a1, b1 and b2 are colinear and b2 lies on segment a1q1
    if (o2 == 0 && onSegment(a1, b2, b1)) return true;

    // a2, b2 and a1 are colinear and a1 lies on segment a2b2
    if (o3 == 0 && onSegment(a2, a1, b2)) return true;

     // a2, b2 and b1 are colinear and b1 lies on segment a2b2
    if (o4 == 0 && onSegment(a2, b1, b2)) return true;

    return false; // Doesn't fall in any of the above cases
}

class Graph // The actual graph structure
{
private:
    vector<Vertex> m_adjList;
protected:
    void linkVerticesUtil(const Edge &edge, bool toggleRecursion = true);
    double interiorAngle(Point a, Point b, Point c) const; // returns interior angle ABC
    bool midpointInGraph(Point a, Point b) const;
public:
    Graph(const vector<Edge> &edge);
    Vertex * findVertex(const Point &point);
    void linkVertices(const Edge &edge);
    bool isClosed(); // A method to check whether a graph is closed
    void triangulate();
    friend ostream& operator<< (ostream &os, const Graph &obj);
};

/*
 *
 * Function Definitions
 *
 */

bool operator== (const Point &lhs, const Point &rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator== ( const Edge &lhs, const Edge &rhs)
{
    return (lhs.src == rhs.src && lhs.dest == rhs.dest);
}

Graph::Graph(const vector<Edge> &edges)
{
    for (size_t i = 0; i < edges.size(); i++)
        linkVertices(edges[i]);
}

Vertex * Graph::findVertex(const Point &point)
{
    for (size_t i = 0; i < m_adjList.size(); i++) {
        if (m_adjList[i].src == point)
            return &m_adjList[i];
    }
    return nullptr;
}

void Graph::linkVertices(const Edge &edge) {
    linkVerticesUtil(edge);
}

bool Graph::midpointInGraph(Point a, Point b) const {
    int counter = 0;
    int i, N = m_adjList.size();
    double xinters;
    Point p1,p2;

    double mid_x = (a.x + b.x)/2, mid_y = (a.y + b.y)/2;

    p1 = m_adjList[0].src;
    for (i = 1; i <= N; i++) {
        p2 = m_adjList[i % N].src;
        if (mid_y > MIN(p1.y,p2.y)) {
            if (mid_y <= MAX(p1.y,p2.y)) {
                if (mid_y <= MAX(p1.x,p2.x)) {
                    if (p1.y != p2.y) {
                        xinters = (mid_y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
                        if (p1.x == p2.x || mid_y <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    return (counter % 2 == 0)? false : true;
}

double Graph::interiorAngle(Point a, Point b, Point c) const {
    int segment1_x = a.x-b.x, segment1_y = a.y-b.y;
    int segment2_x = c.x-b.x, segment2_y = c.y-b.y;
    double segment1 = sqrt(pow(segment1_x, 2) + pow(segment1_y, 2));
    double segment2 = sqrt(pow(segment2_x, 2) + pow(segment2_y, 2));

    double theta = acos(dot(a,b,c) / (segment1*segment2));
    return (midpointInGraph(a,c))? theta : (360-theta);
}

void Graph::linkVerticesUtil(const Edge &edge, bool toggleRecursion) {
    // Check for vertex in graph with src == edge.src
    if (findVertex(edge.src))
    {
        for (size_t i = 0; i < m_adjList.size(); i++) {
            if (m_adjList[i].src == edge.src) {
                m_adjList[i].dest.push_back(edge.dest);
            }
        }
    }
    else
    {
        // Spawning new vertex and inserting data
        Vertex newVertex;
        newVertex.src = edge.src;
        newVertex.dest.push_back(edge.dest);
        m_adjList.push_back(newVertex);
    }

    if (toggleRecursion) {
        linkVerticesUtil(Edge { edge.dest , edge.src }, false);
    }
}

//each vertex should have 2 destination vertices
//must check for overlapping
bool Graph::isClosed()
{
  //check each vertex has 2 destination points
  for(int i = 0 ; i < m_adjList.size();i++)
  {
    if(m_adjList[i].dest.size()!=2)
    {
      return false;
    }
  }
  //check if any edges cross
  for(int i = 0 ; i < m_adjList.size()-1;i++)
  {
      for(int j= 0 ; j < m_adjList.size()-1;j++)
      {
        if(doIntersect(m_adjList[i].src, m_adjList[i].dest[0], m_adjList[i+1].src, m_adjList[i+1].dest[0]))
        {
          //BUG: int doIntersect: since connected at one point they are intersecting
          cout << m_adjList[i] << std::endl;
          cout << m_adjList[i+1] << std::endl;
          return false;
        }
      }
  }

  return true;
}

// WIP
// void Graph::triangulate() {

// }

ostream& operator<< (ostream &os, const Vertex &v)
{
    os << "{ " << v.src.x << " , " << v.src.y << " } --> ";
    for (size_t i = 0; i < v.dest.size(); i++)
        os << "{ " << v.dest[i].x << " , " << v.dest[i].y << " } ";

    return os;
}

ostream& operator<< (ostream &os, const Graph &obj) {
    for(size_t i = 0; i < obj.m_adjList.size(); i++)
    {
        os << obj.m_adjList[i];
        os << '\n';
    }

    return os;
}

#endif //GRAPH_HPP_
