/*
 * main.cpp
 *
 *  Created on: Sep 2, 2015
 *      Author: aniruddha
 */

#include <iostream>
#include <fstream>
#include "LL.h"
#define MAX_BAG_SIZE 50

using namespace std;

/*
 * This is the main file which implements the main program and top level functionalities of 'all
 * possible topological sorting problem'.

This Program Generates all possible topological sorting arrangements. The principle idea is taken from
"A structured program to generate all topological sorting arrangements" by Donald E. Knuth and
 Jayme L. Szwarcfiter.

 This program implements the recursive version outlined in the paper. Alternatively a non recursive version can
 be implemented using the same data structures as outlined in the original article.

 Data structures:
 ----------------------------------

The linear List D (the 'BAG') described in the paper is implemented as a linked list where insertion is possible
both in head and in tail. This mechanism is equivalent to taking an element from right and putting it to
left of the list until base case is found (please refer to the original paper).

The successor list is implemented as an array of linked lists.

The predecessor count is a simple array.
----------------------------------------

Apart from the needed functionalities of each data structures, several redundant functions is also
implemented and provided in the program which can be used for debugging purposes.


Author: Aniruddha Maiti
Date: 6th September, 2015

*/

// define Global variable to count the number of output
int numPerm=0;
LL *successorArrayPt=NULL;
int *count = NULL;
int * printbuffer;
int NumNodes;
int k=0;
int *bag;
int output_index = 0;
int items_added_to_bag;
int items_in_bag = 0;
int bag_index = 0;
int order_Conflict_Flag;


// This Function Initializes array containing predecessor counts
void predinitialization(int n, int **count1){
     int i;
     *count1=new int[n];
     for (i=0; i<n; i++){
         (*count1)[i]=0;
     }
}

// This Function Initializes array of linked list containing successors
void succinitialization(int n, LL **successorNode){
     (*successorNode)=new LL[n];
}
// This wrapper function increase the Count array which stores the number of predecessors
void increase(int succN,int *count){
     count[succN]=count[succN]+1;
}

// This wrapper function inserts a successor in the successor List
void insert(int predN, int succN, LL *successorNode){

     successorNode[predN].AddNode(succN);
}

// This Function initializes the bag
void baginitialization(int n, int * count){
	bag=new int[MAX_BAG_SIZE];

	int i;
    // Look for zero counts in the predecessor array : count
    for (i=0; i < n ; i++){
   	     //If pred count is zero then put the node in the bag
         if (count[i]==0){
       	                        if(items_in_bag>n)
				{
					cout << "Bag is Full" << endl;
				}
				else
				{
					bag[items_in_bag] = i;
					items_in_bag++;
				}
         }
    }
}



/* This function implements update rule
 * for each successor of the output object, decrease its predecessor count by l;
 * if the predecessor count becomes zero, add the successor to the bag.
 */

void update(LL *successor,int obj, int *count){
	int x;
	successor[obj].setCurrentToHead();
	x=successor[obj].peek();
	while (!(x==-100)){

		count[x]=count[x]-1;
		if (count[x]==0){
			bag[items_in_bag] =x;
            items_in_bag++;
		}
		x=successor[obj].peek();
	}

	successor[obj].setCurrentToHead();
	

}

// This function restores the original condition
void restore(LL *successor,int obj,  int *count){
	        int x;
		successor[obj].setCurrentToHead();
		x=successor[obj].peek();	

		while (!(x==-100)){
			count[x]=count[x]+1;

			x=successor[obj].peek();
		}

		successor[obj].setCurrentToHead();
	
}

// This is the recursive function that will be called from main to generate outcomes
void topsorts(){

     int k;
     int temp;
     int bag_item;
    

     /* While the bag is not empty  Do the following Two Steps :
      * a. remove an object from the bag and output it in the output ranking;
      * b. for each successor of the output object, decrease its predecessor count by l;
      *    if the predecessor count becomes zero, add the successor to the bag. */

     if(order_Conflict_Flag == 1)
		return;
     
       if(bag_index!=items_in_bag)
	{
		for(k=bag_index; k < items_in_bag; k++)
			{
                           bag_item = bag[k];
		                   bag[k]=bag[bag_index];
                           printbuffer[output_index++] = bag_item;


                           temp = items_in_bag;
                           bag_index++;

                           update(successorArrayPt, bag_item, count);
                           topsorts();
                         
                           restore(successorArrayPt, bag_item, count);

                           bag_index--;
			   items_in_bag = temp;
			   output_index--;
			   bag[k] = bag_item;
                 	}
	}
	else if(output_index == NumNodes)
		{
			if (numPerm < 26){
			for(int i = 0 ;i< NumNodes;i++)
				{
					cout << " " << printbuffer[i]+1 << " ";
						
				}
				cout << endl ;
				
			}
                        numPerm=numPerm+1;
			
	       }
		else
			{
				printf("\n No topological Sort could be generated : Input pairs are not Partial Order\n");
				order_Conflict_Flag = 1;
				
			}
			
}



// Here is the main program
int main(int argc, char* argv[]){

    if (argc < 2){
       cout << "Input file name should be given as command line argument..\n";
    }
    else
    {
       // open input file
       ifstream inputFile;
       inputFile.open(argv[1]);

       //--------------------------------------------------------------
       if (!inputFile.is_open()) {
          cout << "The input file could not be opened.. \n";
       }
       else{
          // Process the input file
          int successor, predecessor;

          // store the number of nodes
          inputFile >> NumNodes;

          /*Initialize array containing predecessor counts */

          predinitialization(NumNodes, &count);

         /* Initialize array of linked list containing successors*/

          succinitialization(NumNodes, &successorArrayPt);

          order_Conflict_Flag = 0;


          // Read Pairs One by one until 0 0 is found
          inputFile >> predecessor;
          inputFile >> successor;
          // The following two steps are required to have zero based calculations in array
          predecessor=predecessor-1;
          successor=successor-1;

          //PHASE I of the algorithm
          while(!((predecessor == -1) && (successor == -1))){



               // If Not The End of the input
               if (!((predecessor == -1) && (successor== -1))){
                    increase( successor,count);
                    insert (predecessor,successor,successorArrayPt);
               }
               inputFile >> predecessor;
               inputFile >> successor;
               predecessor=predecessor-1;
               successor=successor-1;
          }


        // Initialize Bag

         baginitialization(NumNodes, count);


         // PHASE-II of the algorithm

         // check is the bag is empty
         if (items_in_bag==0){
            	cout << "******** The data contains Loop ***********\n";
             	cout <<"Exiting Program .......\n";
             	return 0;
         } else{
             // prepare output buffer
             printbuffer=new int[NumNodes];

             //call recursive topsorts() to get the all possible results
        	 topsorts();

         }

         // Output total number of outcomes
         if ((numPerm >0)&&(order_Conflict_Flag == 0)){
        	 cout << "Total Number of outcome is : " << numPerm << endl;
         } else{
        	 cout << " There is loop in the input data " << endl;
         }


       }
      //--------------------------------------------------------------
    }


    cout << "\n...The program ends..." << endl;
    return 0;
}




