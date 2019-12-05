#ifndef ARTGALLERY_HPP_
#define ARTGALLERY_HPP_

#include <iostream>
#include <vector>
#include <cmath>
#include "Graph.hpp"

class ArtGallery
{
private:
    Graph m_gallery;
public:
    ArtGallery(const Graph &gallery);
    void solve();
};

ArtGallery::ArtGallery(const Graph &gallery) :
    m_gallery(gallery)
{
}

void ArtGallery::solve() {
    vector<Point>* solution = m_gallery.triangulate();

    std::cout << "Place Security Cameras at the points: ";
    for (int i = 0; i < solution->size(); i++) {
        std::cout << "["
            << (*solution)[i].x << ", "
            << (*solution)[i].y << "] ";
    }
    std::cout << std::endl;
}

#endif //ARTGALLERY_HPP_