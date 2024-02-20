#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma;
  Image i;
  alma.readFromFile("../data/alma.png");
  alma.readFromFile("../data/i.png");
  StickerSheet sheet(alma, 1);
  sheet.addSticker(i,10,10);
  sheet.render().writeToFile("myImage.png");
  

  return 0;
}
