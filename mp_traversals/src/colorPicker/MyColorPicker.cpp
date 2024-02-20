#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  int rand1 = rand()%360;
  int rand2 = rand()%360;

  double h = static_cast<double>(rand1);
  double s = static_cast<double>(rand2);
  double l = 1;

  return HSLAPixel(h,s,l);
}
