/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include <vector>
#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
    map<Point<3>,TileImage*> map_;
    vector<Point<3>> points;

    for (auto i=theTiles.begin() ; i != theTiles.end() ; i++ ){
        LUVAPixel pixel_ = i->getAverageColor();
        Point<3> point_ = convertToXYZ(pixel_);
        points.push_back(point_);
        map_[point_] = &*i; 
    }
    KDTree<3>* tree_ = new KDTree<3>(points);
    for (int i=0 ; i<theSource.getRows();i++){
        for (int j=0 ; j<theSource.getColumns(); j++){
            LUVAPixel color_ = theSource.getRegionColor(i,j);
            Point<3> point_r = convertToXYZ(color_);
            Point<3> point_n = tree_ -> findNearestNeighbor(point_r);
            TileImage* k = map_[point_n];
            canvas->setTile(i,j,k);

        }
    }
    
    delete tree_;
    return canvas;

}

