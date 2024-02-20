/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  ListNode* curr = head_;
  while (curr!=NULL){
    ListNode* curr_next = curr->next;
    delete curr;
    curr = curr_next;
  }
  curr = NULL;
  head_=NULL;
  tail_=NULL;  
}



/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if (length_ == 0){
    head_ = newNode;
    tail_ = newNode;
    length_ = 1;
  }
  else {
    head_ ->prev = newNode;
    newNode->next = head_;
    newNode->prev = NULL;
    head_ = newNode;
    length_ ++;
  }
  // newNode -> next = head_;
  // newNode -> prev = NULL;
  
  // if (head_ != NULL) {
  //   head_ -> prev = newNode;
  // }
  // if (tail_ == NULL) {
  //   tail_ = newNode;
  // }
  

  // length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if (length_ == 0){
    head_ = newNode;
    tail_ = newNode;
    length_ = 1;
  }
  else {
    tail_ ->next = newNode;
    newNode->prev = tail_;
    newNode->next = NULL;
    tail_ = newNode;
    length_ ++;
  }
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL && curr->prev != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;

  
}



  // ListNode * curr = start;

  // for (int i = 0; i < splitPoint || curr != NULL; i++) {
  //   curr = curr->next;
  // }

  // if (curr != NULL) {
  //     curr->prev->next = NULL;
  //     curr->prev = NULL;
  // }

  

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  ListNode* temp;
  ListNode* curr =head_; //s->next;
  if (curr == NULL){
    return;
  }
  while (curr != NULL && curr->next != tail_){
    temp = curr->next->next;
    temp->prev = curr;
    curr->next->next = nullptr;
    curr->next->prev = tail_;
    tail_ -> next = curr->next;
    tail_ = curr -> next;
    curr->next=temp;
    curr = curr->next;

  }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  if (startPoint == NULL || endPoint == NULL||startPoint == endPoint){
    return;
  }
  

  ListNode* start = startPoint->prev;
  ListNode* end = endPoint->next;
  ListNode* tempcurr = startPoint -> next;
  

  while (tempcurr != endPoint){
    ListNode* temp = tempcurr->next;
     tempcurr -> next = tempcurr ->prev;
     tempcurr -> prev = temp;
     tempcurr = temp; 
  }
   startPoint -> prev = startPoint -> next;
   startPoint -> next = end;
   
   endPoint -> next = endPoint -> prev;
   endPoint -> prev = start;
  if (head_ == startPoint) {head_ = endPoint;}
  if (tail_ == endPoint) {tail_ = startPoint;}
  if (head_ != startPoint && start!=NULL){start->next=endPoint;}
  if (tail_ != endPoint && end!=NULL) {end -> prev = startPoint;}

}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  ListNode* start = head_;
  ListNode* end = head_;
  while (start != NULL){
    for (int i=0;i<n-1;i++){
      if (end->next != NULL){
        end = end->next;
      }
      else{
        break;
      }
    }
    reverse(start,end);
    start = start->next;
    end = start;
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  ListNode* start;
  if ((second ->data) < (first ->data)){
    start = second;
    second = second->next;
  }
  else {
    start = first;
    first = first ->next;
  }
  ListNode* curr = start;
  while (first != NULL && second != NULL){
    if ((second ->data) < (first ->data)){
      curr -> next = second;
      second -> prev = curr;
      curr = curr ->next;
      second =second->next;
    }
    else {
      curr ->next = first;
      first->prev = curr;
      curr = curr->next;
      first = first->next;
    }
  }
  if (first ==NULL &&second != NULL){
    curr ->next = second;
    second ->prev = curr;
  }
  else{
    curr ->next = first;
    first -> prev = curr;
  }
  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if (start->next == NULL){
    return start;
  }
  ListNode* second = split(start,chainLength/2);
  ListNode* retur = merge(mergesort(start,chainLength/2),mergesort(second,(chainLength%2)+(chainLength/2)));
  return retur;
}
