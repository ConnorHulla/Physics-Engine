#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "node.h"
#include <fstream>
class LinkedList
{
    private:
        Node *solution;
        LinkedList *next = nullptr;
        double solveX;
    public:
        LinkedList(); //default constructor
        LinkedList(Node *); //overloaded constructor
        ~LinkedList(); //destructor
        //mutator
        void moveNext(LinkedList *&m) { m = m->next; }  //moves the linked list to the next node

        void insertList(LinkedList *&, Node*, int, double); //inserts a node into the list
        void out(LinkedList*, std::ofstream&);

        void recursiveDelete(LinkedList *);

        //accessors
        double getSolved(Node *sol) {return sol->Calculate(sol, solveX); }
        double getX() {return solveX;}
        Node *getNode() {return solution; }
};

#endif // LINKEDLIST_H
