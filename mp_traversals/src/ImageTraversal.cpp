#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

using namespace std;

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  int exist(std::deque<Point> & work_list,const Point & point){
    for (int i=0; i < (int)work_list.size(); i++){
      if (work_list[i] == point){
        return i;
      }
    }
    return -1;
  }
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    if (exist(work_list,point) != -1){
      return;
    }
    else {
      work_list.push_front(point);
    }
    
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    if (exist(work_list,point)!=-1){
      work_list.erase(work_list.begin()+exist(work_list,point));
    }
    work_list.push_back(point);
  }

  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if (work_list.empty()){
      return Point(-1,-1);
    }
    Point temp = work_list.back();
    work_list.pop_back();
    return temp;
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if (work_list.empty()){
      return Point(-1,-1);
    }
    Point temp = work_list.back();
    work_list.pop_back();
    return temp;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {  
    /** @todo [Part 1] */
    Png_ = png;
    Start = start;
    tolerance_ = tolerance;
    add = traversal_add;
    pop = traversal_pop;

  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(&Png_, Start, tolerance_ , add, pop);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    pop = NULL;
    add =NULL;
    Png = NULL;
    tolerance_ = 0;
  }

  ImageTraversal::Iterator::Iterator(PNG* png, Point start, double tolerance, add_function traversal_add, pop_function traversal_pop) {
    pop = traversal_pop;
    add = traversal_add;
    tolerance_ = tolerance;
    Png = png;
    work_list.push_back(start);
    for (int i=0; i<(int)((png->width()) * (png->height()));i++){
      footprint.push_back(0);
    }
    footprint[start.x+png->width()*start.y] = 1;
    
    Start = start;
  }

  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    if (work_list.size()==0){
      return *this;
    }
    
    Point next=work_list.back();
    pop(work_list);
    footprint[next.x + (next.y)*(Png->width())]=1;
    if (next.x < Png->width()-1){
      Point temp(next.x+1,next.y);
      if (footprint[temp.x+(temp.y*(Png->width()))]==0 && calculateDelta(Png->getPixel(temp.x,temp.y),Png->getPixel(Start.x,Start.y))< tolerance_){
        add(work_list,temp);
      }
    }
    if (next.y < Png->height()-1){
      Point temp(next.x,next.y+1);
      if (footprint[temp.x+(temp.y*(Png->width()))]==0 && calculateDelta(Png->getPixel(temp.x,temp.y),Png->getPixel(Start.x,Start.y))<tolerance_){
        add(work_list,temp);
      }
    }
    if (next.x>0){
      Point temp(next.x-1,next.y);
      if (footprint[temp.x+(temp.y*(Png->width()))]==0 && calculateDelta(Png->getPixel(temp.x,temp.y),Png->getPixel(Start.x,Start.y))<tolerance_){
        add(work_list,temp);
      }
    }
    if (next.y){
      Point temp(next.x,next.y-1);
      if (footprint[temp.x+(temp.y*(Png->width()))]==0 && calculateDelta(Png->getPixel(temp.x,temp.y),Png->getPixel(Start.x,Start.y))<tolerance_){
        add(work_list,temp);
      }
    }
    // if (work_list.empty()) {
    //   pop = NULL;
    // }

    return *this;
  }

  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    if ((int)work_list.size() == 0){
      //cout << "empty" << endl;
      return Point();
    }
    return work_list.back();
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    if ((this->work_list.size() == 0)){
      return false;
    }
    // if (this->work_list.back() == other.work_list.back()){
    //   return false;
    // }
    return true;
  }

}