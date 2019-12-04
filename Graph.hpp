#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <vector>
#include "delaunator.hpp"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

using std::vector;
using std::cout;
using std::ostream;

enum Color { None, Red, Yellow, Blue };

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
    Point src;
    vector<Point> dest;
    int color = Color(None);
    
    inline Vertex& operator= (const Vertex &rhs);
    friend ostream& operator<< (ostream &os, const Vertex &v);
};

class Graph // The actual graph structure
{
private:
    vector<Vertex> m_adjList;
protected:
    void linkVerticesUtil(const Edge &edge, bool toggleRecursion = true);
public:
    Graph(const vector<Edge> &edge);
    Vertex * findVertex(const Point &point);
    void linkVertices(const Edge &edge);
    bool isClosed(); // A method to check whether a graph is closed
    vector<Point> triangulate();
    friend ostream& operator<< (ostream &os, const Graph &obj);
};

/* 
 * 
 * Function Definitions
 * 
 */

bool operator== (const Point &lhs, const Point &rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator== ( const Edge &lhs, const Edge &rhs) {
    return (lhs.src == rhs.src && lhs.dest == rhs.dest);
}

Graph::Graph(const vector<Edge> &edges)
{
    for (size_t i = 0; i < edges.size(); i++)
        linkVertices(edges[i]);
}

Vertex * Graph::findVertex(const Point &point) {
    for (size_t i = 0; i < m_adjList.size(); i++) {
        if (m_adjList[i].src == point)
            return &m_adjList[i];
    }
    return nullptr;
}

void Graph::linkVertices(const Edge &edge) {
    linkVerticesUtil(edge);
}

void Graph::linkVerticesUtil(const Edge &edge, bool toggleRecursion) {
    // Check for vertex in graph with src == edge.src
    if (findVertex(edge.src)) {
        for (size_t i = 0; i < m_adjList.size(); i++) {
            if (m_adjList[i].src == edge.src) {
                m_adjList[i].dest.push_back(edge.dest);
            }
        }
    } else {
        Vertex newVertex;
        newVertex.src = edge.src;
        newVertex.dest.push_back(edge.dest);
        m_adjList.push_back(newVertex);
    }

    if (toggleRecursion) {
        linkVerticesUtil(Edge { edge.dest , edge.src }, false);
    }
}

// WIP
vector<Point> Graph::triangulate() {
    vector<double> coords;

    for (int i = 0; i < m_adjList.size(); i++) {
        coords.push_back(m_adjList[i].src.x);
        coords.push_back(m_adjList[i].src.y);
    }

    //triangulation happens here
    delaunator::Delaunator d(coords);

    vector<Point> solution;

    for (int i = 0; d.triangles.size(); i += 3) {
        Point temp;
        temp.x = d.coords[2 * d.triangles[i]];
        temp.y = d.coords[2 * d.triangles[i] + 1];
        solution.push_back(temp);
    }
    
    return solution;
}

ostream& operator<< (ostream &os, const Vertex &v) {
    os << "{ " << v.src.x << " , " << v.src.y << " } --> ";
    for (size_t i = 0; i < v.dest.size(); i++)
        os << "{ " << v.dest[i].x << " , " << v.dest[i].y << " } ";

    return os;
}

ostream& operator<< (ostream &os, const Graph &obj) {
    for(size_t i = 0; i < obj.m_adjList.size(); i++) {
        os << obj.m_adjList[i];
        os << '\n';
    }

    return os;
}

#endif //GRAPH_HPP_