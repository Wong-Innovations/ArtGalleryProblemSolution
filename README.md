TEST123

# ArtGalleryProblemSolution
A C++ solution to the 2D Art Gallery Problem https://en.wikipedia.org/wiki/Art_gallery_problem

## Objective
Given an closed set of 2D points (which represent the walls of an art gallery), output a set of points where 360 degree cameras could be installed to monitor every wall of the gallery.

## Our Solution
We decided to approach the AGP using graph theory, many papers have been written on the triangulation and colorization of graphs which is the basis for our solution. The procedure goes as follows:
1. Store the user inputted points in a graph data structure.
2. Check that the graph is closed and has no intersecting edges.
3. Generate a new graph by triangulating the given points.
4. Colorize the vertices using as few colors as possible (no more than 3).
5. Return the colored set of vertices with the fewest nodes.

This sequence is performed by our driver program `main.cpp`.

### Graph.hpp
This C++ header file contains many helper classes and structs to be utilized by `ArtGallery.hpp`. Point, Edge, and Vertex all serve as abstraction layers over the relationship between integer pairings in a set of 2D points. The Graph class contains an array of Vertex objects which each point to other points in the graph.

### ArtGallery.hpp
This C++ header file contains a singular class which is a very simple interface for the Graph class. The class only includes a constructor which simply copies a Graph into `m_gallery`, and a solve method which calls Graph class methods to solve the graph stored in `m_gallery`.

```c++
class ArtGallery
{
private:
    Graph m_gallery;
public:
    ArtGallery(const Graph &gallery);
    vector<Point> solve();
};
```

## The Group
[@Wong-Innovations](https://github.com/Wong-Innovations)
[]()
[]()
[]()
[]()
