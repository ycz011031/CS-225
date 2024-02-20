/* Your code here! */
#include "dsets.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void DisjointSets::addelements(int num){
    for (int i=0; i<num; i++){
        elements_.push_back(-1);
    }
    return;    
}

int DisjointSets::find(int elem){
    if (elem >= (int)elements_.size()){
        return 0;
    }
    if (elements_[elem] < 0){
        return elem;
    }
    int temp = elem;
    while (elements_[elem] >= 0){
        elem = elements_[elem];
    }
    elements_[temp] = elem;
    return elem;

}

void DisjointSets::setunion(int a, int b){
    int root_a = find(a);
    int root_b = find(b);
    if (root_a == root_b){
        return;
    }
    if (elements_[root_a]>elements_[root_b]){
        elements_[root_b] = elements_[root_a] + elements_[root_b];
        elements_[root_a] = root_b;
        return;
    }
    else{
        elements_[root_a] = elements_[root_a] + elements_[root_b];
        elements_[root_b] = root_a;
        return;
    }
}

int DisjointSets::size(int elem){
    int root_index = find(elem);
    return elements_[root_index]*(-1);
}