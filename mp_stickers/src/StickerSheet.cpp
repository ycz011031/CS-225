#include "StickerSheet.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace cs225;

void StickerSheet::copy_(const StickerSheet & other){
    // if (picture != NULL){
    //     delete this -> picture;
    // }
    
    max_ = other.max_;
    
    // stickers = vector <Image*> (other.stickers.size());
    picture =new Image(*(other.picture));
    cnt = other.cnt;
    stickers = other.stickers;
    xcor = other.xcor;
    ycor = other.ycor;
    



    // for (unsigned i = 0;i<other.stickers.size();i++){
    //     stickers[i] = other.stickers[i];
    //     xcor[i] = other.xcor[i];
    //     ycor[i] = other.ycor[i];
    // }
}


// void StickerSheet::delete_(){
//     // for(int i=0; i<max_;i++){
//     //     delete stickers[i];
//     //     stickers[i] = NULL;
//     // }

//     //delete[] xcor;
//     //delete[] ycor;
//     delete stickers;
//     delete xcor;
//     delete ycor;
//     delete picture;

// }

StickerSheet::~StickerSheet(){
    
    // for (int i=0;i<max_;i++){
    //     delete stickers.at(i);
    // }
    
    // stickers.clear();
    // xcor.clear();
    // ycor.clear();
    delete picture;
    //delete[] xcor;
    //delete[] ycor;
    

}


StickerSheet::StickerSheet(const Image & picture_, unsigned max){
    picture = new Image(picture_);
    max_ = max;
    cnt = 0;
    stickers =  vector <Image*>(max_,NULL);
    xcor =  vector <int>(max_);
    ycor =  vector <int>(max_);
    
}
// StickerSheet::StickerSheet(const Image & picture_, unsigned max) {
// 	cnt = 0;
//     max_ = max;
//     xcor = new int[max_];
//     ycor = new int[max_];
//     stickers = new Image*[max_];
//     for (unsigned i = 0; i < max; i++) {
// 	     stickers[i] = NULL;
// 	     xcor[i] = 0;
// 	     ycor[i] = 0;
//     }
//     this->picture = new Image(picture_);
//   }



StickerSheet::StickerSheet (const StickerSheet & other){
    copy_(other);
}

int StickerSheet::addSticker(Image&sticker, int x, int y){
    for (int i =0; i<max_; i++ ){
        if(stickers.at(i)!=NULL){
            cnt=i+1;
        }
        if (stickers.at(i)==NULL){
            cnt = i;
            break;
        }
        
    }
    if (cnt>=max_){
        changeMaxStickers ( max_ + 1 );
    }
    
    //stickers[cnt] = new Image(sticker);
    stickers[cnt] = &sticker;
    xcor[cnt] = x;
    ycor[cnt] = y;
    return (cnt); 
    
    
}


void StickerSheet::changeMaxStickers (unsigned max){
    if ((unsigned) max_ == max){
        return;
    }
    // vector <Image*> tempstick = vector <Image*>(max);
    // vector <int> tempx=  vector <int> (max);
    // vector <int> tempy=  vector <int> (max);
    // // Image* temppic = new Image(*picture);
    xcor.resize(max);
    ycor.resize(max);
    stickers.resize(max);


    // if ((int)max < max_){
    //     for (unsigned j=0;j<max;j++){
    //         tempstick.at(j) = new Image(*stickers.at(j));
    //         tempx.at(j) = xcor.at(j);
    //         tempy.at(j) = ycor.at(j);
    //     }
    // }

    // if (max > (unsigned)max_){
    //     for (unsigned k =0; k<max;k++){
    //         if (k<(unsigned)max_){

    //             tempstick.at(k) = new Image(*stickers.at(k));
    //             tempx.at(k) = xcor.at(k);
    //             tempy.at(k) = ycor.at(k);
    //         }
    //         else {
    //             tempstick.at(k) = NULL;
    //         }
    //     }
        
        
    // }
    max_=(int)max;
    // stickers = tempstick;
    // xcor = tempx;
    // ycor = tempy;
    // cnt = 0;
    // picture = temppic;
    // delete temppic;
    // for (int i=0;i<max_;i++){
    //     delete tempstick.at(i);
    // }
  
    // tempx.clear();
    // tempy.clear();
    // delete temppic;
    // tempstick.clear();
}

Image * StickerSheet::getSticker(unsigned index){
    if (index >= stickers.size()){
        return NULL;
    }
    else {
        return stickers[index];
    }
}

int StickerSheet::layers() const{
    return int(max_);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
    for (int i=0;i<max_;i++){
        delete stickers.at(i);
    }

    stickers.clear();
    xcor.clear();
    ycor.clear();

    delete picture;

    copy_(other);
    return *this;
}

void StickerSheet::removeSticker (unsigned index){
    stickers.at(index) = NULL;
    xcor.at(index) = 0;
    ycor.at(index) = 0;

}

Image StickerSheet::render()const{
    Image result(*picture);
    int leftexpand = 0;
    int rightexpand =0;
    int upexpand = 0 ;
    int downexpand=0;
    for (int i =0; i<max_;i++){
        if (stickers.at(i)==NULL){
            continue;
        }
        int w = stickers.at(i)->width();
        int h = stickers.at(i)->height();
        if (xcor.at(i)<0 ){
            if (leftexpand < 0-xcor.at(i)){
                leftexpand = 0-xcor.at(i);
            }           
        }
        if (xcor.at(i)+w>(int)(result.width())){
            if ((unsigned)rightexpand < xcor.at(i)+w-result.width()){
                rightexpand = xcor.at(i)+w-result.width();
            }
        }
        if (ycor.at(i)<0){
            if (upexpand < 0-ycor.at(i)){
                upexpand = 0-ycor.at(i);
            }
        }
        if (ycor.at(i)+h>(int)(result.height())){
            if ((unsigned)downexpand < ycor.at(i)+h-result.height()){
                downexpand = ycor.at(i)+h-result.height();
            }
        }

    }
    
    int w2,h2;
    w2 = leftexpand+rightexpand+(int)result.width();
    h2 = upexpand+downexpand+(int)result.height();
    Image newstuff =  Image((unsigned)w2,(unsigned)h2);

    for (int a = 0; (unsigned)a<result.width();a++){
        for (int b = 0; (unsigned)b<result.height();b++){
            HSLAPixel & pix = newstuff.getPixel(a+leftexpand,b+upexpand);
            pix = result.getPixel(a,b);
        }
    }
    for (int t=0; t<max_;t++){
        if (stickers.at(t)==NULL){
            continue;
        }
         for (int j=0; (unsigned)j<stickers.at(t)->width();j++){
             for (int k=0; (unsigned)k<stickers.at(t)->height();k++){
            
                HSLAPixel & pix = newstuff.getPixel(j+leftexpand+xcor.at(t),ycor.at(t)+k+upexpand);
                HSLAPixel & valuepix = stickers.at(t) -> getPixel(j,k);
                if (valuepix.a != 0){
                    pix = stickers.at(t) -> getPixel(j,k);
                }
             }
         }
    }

    // result = newstuff;

    return newstuff;

}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if ((int)layer >= max_){
        return -1;
    }
    stickers.at(layer) = &sticker;
    xcor.at(layer) = x;
    ycor.at(layer) = y;
    return layer;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if (index >=(unsigned) max_ || stickers.at(index)==NULL){
        return false;
    }
    else {
        xcor.at(index) = x;
        ycor.at(index) = y;
        return true;
    }
}





