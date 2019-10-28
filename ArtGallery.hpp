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
    vector<Point> solve();
};

ArtGallery::ArtGallery(const Graph &gallery) :
    m_gallery(gallery)
{
}

#endif //ARTGALLERY_HPP_