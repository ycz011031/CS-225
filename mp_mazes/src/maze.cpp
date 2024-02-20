/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
using namespace std;
using namespace cs225;


SquareMaze :: SquareMaze(){
    _width = 0;
    _height = 0;
}

void SquareMaze::makeMaze(int width, int height){
    _width = width;
    _height = height;
    if (!maze_.empty()){
        maze_.clear();
    }
    
    DisjointSets connected;
    connected.addelements(_width*_height);
    
    for (int i =0; i<_width*_height; i++){
        maze_.push_back(square(false,false));
    }
    
    while(connected.size(0)<_width*_height){
        int x = rand()% _width;
        int y = rand()% _height;
        int direc = rand()%2;
        if (direc == 0 && x != _width-1 && connected.find(y*_width+x) != connected.find(y*_width+x+1)){
            maze_[_width*y+x].set_right();
            connected.setunion(y*_width+x,  y*_width+x+1);
        }
        if (direc == 1 && y != _height-1 && connected.find(y*_width+x) != connected.find((y+1)*_width+x)){
            maze_[_width*y+x].set_down();
            connected.setunion(y*_width+x, (y+1)*_width+x);
        }

    }

}




bool SquareMaze::canTravel(int x, int y, int dir) const{
    if (x < 0 || y < 0 || dir > 3 || x>=_width || y>=_height) {
    return false;
    }

    if (dir==0 && x==_width-1){
        return false;
    }
    if (dir==1 && y==_height-1){
        return false;
    }
    if (dir==2 && x==0){
        return false;
    }
    if (dir==3 && y==0){
        return false;
    }

    if (dir == 0){
        return maze_[y*_width+x].right_;
    }
    if (dir == 1){
        return maze_[y*_width+x].down_;
    }
    if (dir == 2){
        return maze_[y*_width+x-1].right_;
    }
    if (dir == 3){
        return maze_[(y-1)*_width+x].down_;
    }
       
    return false;

}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if (x < 0 || y < 0 || dir > 1 || x>=_width || y>=_height) {
    return;}
    if(dir == 0){
        maze_[y*_width+x].right_ = !exists;
    }
    if(dir == 1){
        maze_[y*_width+x].down_ = !exists;
    }
}

vector<int> SquareMaze::solveMaze(){
    vector<int> path;

    for(int i=0; i<_width;i++){
        vector<int> temp;
        pathfinder(0,0,i,_height-1,3,temp);
        //cout << temp.size() << endl;
        if(temp.size()>path.size()){
            path = temp;
        }
    }
    reverse(path.begin(),path.end());
    //for (int i=0;i<(int)path.size();i++){
        //cout << path[i] <<endl;
    //}
    return path;
}

int SquareMaze::pathfinder(int x, int y, const int x_, const int y_, int dir,vector<int> &path){
    if (x < 0 || y < 0 || dir > 4 || x>=_width || y>=_height){
        return -1;
    }

    if (x == x_ && y==y_){
        //cout << "the width is" <<  _width << endl;
        //cout << x <<endl;
        // int a[4] = {2,3,0,1};
        // path.push_back(a[dir]);
        return 1;
    }      
    int r,l,u,d;
    if (dir != 0 && canTravel(x,y,0)){
        r = pathfinder(x+1,y,x_,y_,2,path);
    }
    else{
        r = -1;
    }
    if (dir != 1 && canTravel(x,y,1)){
        d = pathfinder(x,y+1,x_,y_,3,path);
    }
    else{
        d = -1;
    }
    if (dir != 2 && canTravel(x,y,2)){
        l = pathfinder(x-1,y,x_,y_,0,path);
    }
    else{
        l = -1;
    }
    if (dir != 3 && canTravel(x,y,3)){
        u = pathfinder(x,y-1,x_,y_,1,path);
    }
    else{
        u = -1;
    }
    
    if (r==1){
        path.push_back(0);
        //cout << "triggered" << endl;
        return 1;
    }
    if (d==1){
        path.push_back(1);
        //cout << "triggered" << endl;
        return 1;
    }
    if (l==1){
        path.push_back(2);
        //cout << "triggered" << endl;
        return 1;
    }
    if (u==1){
        path.push_back(3);
        //cout << "triggered" << endl;
        return 1;
    }
    else{
        return -1;
    }
}


PNG* SquareMaze::drawMaze() const{
    PNG* canvas = new PNG(_width*10+1,_height*10+1);
    for (unsigned x=10; x<canvas->width();x++ ){
        canvas->getPixel(x,0).l=0;
    }
    for (unsigned y=0; y<canvas->height();y++){
        canvas->getPixel(0,y).l=0;
    }
    for (int i = 0; i<_width*_height;i++){
        if (!maze_[i].down_){
            for (int j=0;j<11;j++){
                canvas->getPixel((i%_width)*10+j,(i/_height)*10+10).l=0;
            }
        }
        if (!maze_[i].right_){
            for (int j=0;j<11;j++){
                canvas->getPixel((i%_width)*10+10,(i/_height)*10+j).l=0;
            }
        }
    }
    return canvas;

}

PNG* SquareMaze::drawMazeWithSolution(){
    cs225::PNG* canvas = drawMaze();
    vector<int> solution = solveMaze();
    int x = 5;
    int y = 5;
    cs225::HSLAPixel red(0,1,0.5,1);
    for (int i=0; i<(int)solution.size(); i++){
        if (solution[i] == 0){
            for (int j = 0; j<11; j++){
                canvas->getPixel(x+j,y) = red;
            }
            x=x+10;
        }
        if (solution[i] == 1){
            for (int j = 0; j<11; j++){
                canvas->getPixel(x,y+j) = red;
            }
            y=y+10;
        }
        if (solution[i] == 2){
            for (int j = 0; j<11; j++){
                canvas->getPixel(x-j,y) = red;
            }
            x=x-10;
        }
        if (solution[i] == 3){
            for (int j=0;j<11;j++){
                canvas->getPixel(x,y-j) = red;
            }
            y=y-10;
        }
    }
    for (int k = -4; k <= 4; k++) {
        cs225::HSLAPixel & pixel = canvas->getPixel(x+k, y+5);
        pixel.l = 1;
    }
    return canvas;
}
