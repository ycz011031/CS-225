/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if(curDim < 0 || curDim >= Dim){
      return false;
    }
    if(first[curDim]==second[curDim]){
      return first<second;
    }
    return (first[curDim] < second[curDim]);
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double cur_dist = 0;
    double pot_dist = 0;
    for (int i=0; i<Dim;i++){
      cur_dist += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
      pot_dist += ((target[i]-potential[i])*(target[i]-potential[i]));
    }
    if(cur_dist<pot_dist){
      return false;
    }
    else if(pot_dist<cur_dist){
      return true;
    }
    else{
      return potential < currentBest;
    }
}


template <int Dim>
typename KDTree<Dim> :: KDTreeNode * KDTree<Dim>::nodeconnector( vector<Point<Dim>>& newPoints, int curDim){
  if (newPoints.empty()){
    return NULL;
  }
  int mid;
  int dim = curDim;
  KDTreeNode* NODE =  new KDTreeNode();  
  mid = ((int)newPoints.size()/2)+(int)(newPoints.size()%2)-1;
  auto smallerDim = [dim] (Point<Dim> a, Point<Dim> b) {return smallerDimVal(a,b,dim);};
  select(std::begin(newPoints),std::end(newPoints),std::begin(newPoints)+mid,smallerDim);
  NODE->point = newPoints[mid];
  newPoints.erase(newPoints.begin()+mid);

  if (newPoints.size()<3){
    if(newPoints.size()==1){
      NODE -> right = NULL;
      KDTreeNode* NODEL =  new KDTreeNode();
      NODEL -> point = newPoints[0];
      NODE -> right =NODEL;
      return NODE;
    }
    if(newPoints.size()==2){
      if (smallerDimVal(newPoints[0],newPoints[1],dim=(dim+1)%Dim)){
        KDTreeNode* NODEL =  new KDTreeNode();
        KDTreeNode* NODER =  new KDTreeNode();
        NODER ->point = newPoints[1];
        NODEL ->point = newPoints[0];
        NODE ->right = NODER;
        NODE ->left = NODEL;
        return NODE;
      }
      else{
        KDTreeNode* NODEL =  new KDTreeNode();
        KDTreeNode* NODER =  new KDTreeNode();
        NODER ->point = newPoints[1];
        NODEL ->point = newPoints[0];
        NODE ->right = NODER;
        NODE ->left = NODEL;
        return NODE;
      }
    }
    NODE -> left = NULL;
    NODE -> right = NULL;
    return NODE;
  }
  vector<Point<Dim>> front_half(newPoints.begin(),newPoints.begin()+mid);
  vector<Point<Dim>> rare_half(newPoints.begin()+mid,newPoints.end());
  dim=(dim+1)%Dim;
  NODE -> left = KDTree<Dim>::nodeconnector(front_half,dim);
  NODE -> right = KDTree<Dim>::nodeconnector(rare_half,dim);
  return NODE;


}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = newPoints.size();
    vector<Point<Dim>> points_;
    points_.assign(newPoints.begin(),newPoints.end());
    if (newPoints.empty()){
      root = NULL;
      return;
    }
    root = nodeconnector(points_, 0);

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
void KDTree<Dim>::_delete(KDTree<Dim>::KDTreeNode* node){
  if (node==NULL){
    return;
  }
  _delete(node->left);
  _delete(node->right);
  delete node;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _delete(root);
}

template <int Dim>
typename KDTree<Dim> :: KDTreeNode *  KDTree<Dim>::findNearestNeighbor(KDTreeNode* node, const Point<Dim>& query, int dimension) const {
  if (node == NULL){
    return NULL;
  }
  KDTreeNode* next;
  KDTreeNode* other;
  if (smallerDimVal(query,node->point,dimension)){
    next = node->left;
    other = node->right;
  }
  else{
    next = node->right;
    other = node->left;
  }
  if(next == NULL){
    //cout << node->point <<endl;
    return node;
  }
  //cout << next->point <<endl;
  //cout << "hello" << endl;
  KDTreeNode *temp,*current_best;
  //cout << next->point << query << (dimension+1)%Dim <<endl;
  temp = findNearestNeighbor(next,query,(dimension+1)%Dim);
  if (shouldReplace(query,node->point,temp->point)){
    current_best = temp;
    //cout << "again" << endl;
  }
  else{
    current_best = node;
  }
  int r2=0;
  for (int i=0; i<Dim; i++){
    r2+= (query[i]-current_best->point[i])*(query[i]-current_best->point[i]);
  }
  int rc = (query[dimension]-node->point[dimension])*(query[dimension]-node->point[dimension]);
  if (r2 >= rc){
    if (other == NULL){
      return current_best;
    }

    temp = findNearestNeighbor(other,query,(dimension+1)%Dim);
    if (shouldReplace(query,current_best->point,temp->point)){
      current_best = temp;
    }
  }
  //cout << current_best->point<<endl;
  return current_best;

}




template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    


    return findNearestNeighbor(root,query,0)->point;
}

// //helper partition function --------------------------------------------------------
// template <typename RandIter, typename Comparator>
// void partition(RandIter begin, RandIter end, RandIter k, Comparator cmp){
//   auto point =k--;
//   auto pivot = *(point);
//   auto leftmark = begin++;
//   auto rightmark = end;

//   while (true){
//     while ( leftmark!=end && cmp(*(leftmark),pivot)){
//       leftmark++;
//     }
//     while (begin!=rightmark && cmp(pivot,*(rightmark))){
//       rightmark--;
//     }
//     if (leftmark<rightmark){
//       break;
//     }
//     else {
//       auto temp = *(leftmark);
//       *(leftmark) = *(rightmark);
//       *(rightmark) = temp;
//       pivot = *(point);
//     }
//   }


// }


template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp)
{
    /**
     * @todo Implement this function!
     */    
    if (start == end){
      return;
    }

    auto pivot = *(k);
    auto leftmark = start;
    auto rightmark = end -1 ;
    //cout << pivot << endl;




    while (true){

      if (leftmark>=rightmark){
        break;
      }
      while ( leftmark<k && cmp(*(leftmark),pivot)){
        leftmark++;
      }
      while (k<rightmark && cmp(pivot,*(rightmark))){
        rightmark--;
      }
      if (leftmark==rightmark){
        break;
      }
      else {
        auto temp = *(leftmark);
        *(leftmark) = *(rightmark);
        *(rightmark) = temp;
        // std::swap(v[leftmark],v[rightmark])
        pivot = *(k);
        leftmark = start;
        rightmark = end-1;
        //cout << pivot << endl;
      }
    }



    
}

