#include "Image.h"
#include <iostream>

using namespace std;
using namespace cs225;

Image::Image():PNG(){};

Image::Image(unsigned int width, unsigned int height):PNG(width,height){};

void Image::darken(){
    for (int i = 0; i <(int)width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.l-=0.1;
            if(pix.l<0){
                pix.l = 0;
            }
        }
    }

}

void Image::darken(double amount){
    for (int i = 0; i <(int) width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.l-=amount;
            if(pix.l<0){
                pix.l = 0;
            }
        }
    }
}

void Image::desaturate(){
    for (int i = 0; i < (int)width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.s-=0.1;
            if(pix.s<0){
                pix.s = 0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for (int i = 0; i < (int)width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.s-=amount;
            if(pix.s<0){
                pix.s = 0;
            }
        }
    }
}


void Image::grayscale(){
    for (int i = 0; i <(int) width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.s=0;
        }
    }
}

void Image::illinify(){
    for (int i = 0; i < (int)width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            if (pix.h>113.5 && pix.h<=293.5){
                pix.h = 216;
            } 
            else {
                pix.h = 11;
            }
        }
    }
}

void Image::lighten(){
    for (int i = 0; i <(int) width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.l+=0.1;
            if(pix.l>1){
                pix.l =1;
            }
        }
    }
}

void Image::lighten(double amount){
    for (int i = 0; i <(int) width();i++){
        for (int j=0; j <(int) height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.l+=amount;
            if(pix.l>1){
                pix.l = 1;
            }
        }
    }
}

void Image::rotateColor( double degrees){
    for (int i = 0; i <(int) width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.h+=degrees;
            while (pix.h<0){
                pix.h += 360;
            }
            while (pix.h>360){
                pix.h-=360;
            }
        }
    }

}

void Image::saturate(){
    for (int i = 0; i < (int)width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.s+=0.1;
            if(pix.s>1){
                pix.s = 1;
            }
        }
    }
}

void Image::saturate(double amount){
    for (int i = 0; i < (int)width();i++){
        for (int j=0; j < (int)height();j++){
            HSLAPixel & pix = getPixel(i,j);
            pix.s+=amount;
            if(pix.s>1){
                pix.s = 1;
            }
        }
    }
}

void Image::scale(double factor){
    double w = (double)width()*factor;
    double h = (double)height()*factor;
    Image *valueimg = new Image();
    *valueimg = *this;
    resize (w,h);
    for (double i=0;i<w;i++){
        for (double j=0; j<h;j++){
            HSLAPixel & targetpix = getPixel(i,j);
            HSLAPixel & valuepix = valueimg -> getPixel(i/factor, j/factor);
            targetpix = valuepix;
        }

    }
    delete valueimg;    
}


void Image::scale(unsigned w, unsigned h){
    double wfac = (double)w/(double)width();
    double hfac = (double)h/(double)height();
    double factor;
    if (wfac > hfac){
        factor = hfac;
    }
    else {
        factor = wfac;
    }
    double w1 = (double)width()*factor;
    double h1 = (double)height()*factor;
    Image *valueimg = new Image();
    *valueimg = *this;
    resize (w1,h1);
    for (double i=0;i<w1;i++){
        for (double j=0; j<h1;j++){
            HSLAPixel & targetpix = getPixel(i,j);
            HSLAPixel & valuepix = valueimg -> getPixel(i/factor, j/factor);
            targetpix = valuepix;
        }

    }
    delete valueimg;   
    



   
}