/*
 * LL.h
 *
 *  Created on: Sep 2, 2015
 *      Author: aniruddha
 */

#ifndef LL_H_
#define LL_H_

class LL{
  private :
      struct node{
          int data;
          node* next;
      };

      typedef struct node * nodePtr;
      nodePtr head;
      nodePtr curr;
      nodePtr temp;

  public :
      LL();
      void AddNode(int addData);
      void DeleteNode(int DelData);
      void PrintList();
      bool isEmpty();
      int getFromHead();
      int peek();
      void setCurrentToHead();
      nodePtr currentData;

};




#endif /* LL_H_ */
