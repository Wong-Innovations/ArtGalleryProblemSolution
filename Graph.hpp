#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <vector>

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

class Graph // The actual graph structure
{
private:
    vector<Vertex> m_adjList;
public:
    Graph(const vector<Edge> &edge);
    Vertex * findVertex(const Point &point);
    void linkVertices(const Edge &edge, bool toggleRecursion = true);
    bool isClosed(); // A method to check whether a graph is closed
    void triangulate();
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

void Graph::linkVertices(const Edge &edge, bool toggleRecursion) {
    // Check for vertex in graph with src == edge.src
    if (findVertex(edge.src)) {
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
        linkVertices(Edge { edge.dest , edge.src }, false);
    }
}

// // WIP
// Graph::triangulate() {
//     for (size_t i = 0; i < m_adjList.size(); i++) {
//         for (size_t j = 0; j < m_adjList[i].size(); j++) {
//             if (m_adjList)
//         }

//     }

// }

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
