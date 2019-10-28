#include <iostream>
#include <vector>
#include "ArtGallery.hpp"
#include "Graph.hpp"

using std::vector;
using std::cout;

void defineGallery(vector<Edge> &edges);

int main(void) {
  vector<Edge> edges;
  defineGallery(edges);
  Graph ag(edges);

  cout << ag;

  return 0;
}

void defineGallery(vector<Edge> &edges) {
  edges.push_back(
    Edge {
      Point {1, 1},
      Point {2, 4}
    }
  );
  edges.push_back(
    Edge {
      Point {2, 4},
      Point {3, 2}
    }
  );
  edges.push_back(
    Edge {
      Point {3, 2},
      Point {4, 2}
    }
  );
  edges.push_back(
    Edge {
      Point {4, 2},
      Point {4, 4}
    }
  );
  edges.push_back(
    Edge {
      Point {4, 4},
      Point {6, 1}
    }
  );
  edges.push_back(
    Edge {
      Point {6, 1},
      Point {1, 1}
    }
  );

  return;
}