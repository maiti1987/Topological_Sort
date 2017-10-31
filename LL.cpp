/*
 * LL.cpp
 *
 *  Created on: Sep 2, 2015
 *      Author: aniruddha
 */

#include <iostream>
#include "LL.h"
// This file is the standard Linked List implementation
using namespace std;
LL::LL(){
  head=NULL;
  curr=NULL;
  temp=NULL;
  currentData=NULL;

}

void LL::AddNode(int addData){

              nodePtr n = new node;
              n->next = NULL;
              n->data=addData;

              if (head !=NULL){
                  curr=head;
                  while(curr->next != NULL){
                     curr=curr->next;
                  }
                  curr->next=n;
              } else{
                  head = n;
              }

}
void LL::DeleteNode(int DelData){
           nodePtr delPtr=NULL;
           curr=head;
           temp=head;

           while((curr != NULL) && (curr->data !=DelData)){
                temp=curr;
                curr=curr->next;

           }

           if (curr == NULL){
                cout << DelData << " was not in the List \n";
                delete delPtr;
           } else{
                delPtr=curr;
                curr=curr->next;
                temp->next=curr;
                // If the data is at the front make changes to the head

                if (delPtr==head){
                   head=head->next;
                   temp=NULL;
                }

                delete delPtr;
                //cout << "The value " << DelData << " is deleted from the list" << endl;
           }
}
void LL::PrintList(){
           curr=head;
           cout << "\n--------------------------------\n";
           while(curr!=NULL){
                cout << curr->data << "-->";
                curr=curr->next;
           }
           cout << "\n--------------------------------\n";
}

bool LL::isEmpty(){
	if (head==NULL){
		return true;
	}
	else{
		return false;
	}
}

int LL::getFromHead(){

	if (head!=NULL){

           return head->data;
	}
    else{
          cout << "\nSomething went wrong : Bag is Empty:\n" ;
          return -100;
    }
}

int LL:: peek(){
	int data;
	if (currentData!=NULL){
		   data=currentData->data;
		   currentData=currentData->next;
           return data;

	}
    else{

          return -100;
    }
}

 void LL:: setCurrentToHead(){
	 currentData=head;
}
