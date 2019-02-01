#include "linkedlist.h"
#include "node.h"
#include <iomanip>
#include <iostream>
LinkedList::LinkedList()
{
    next = nullptr;
    solution =0;
}

LinkedList::LinkedList(Node *defaultNode)
{
    solution = defaultNode;
}

LinkedList::~LinkedList()
{
    //dtor
}


void LinkedList::recursiveDelete(LinkedList * del)
{
    //if the linked list is empty, return null
    if(!del)
    {
        return;
    }
    recursiveDelete(del->next);
    delete del;

}
void LinkedList::out(LinkedList *moves, std::ofstream& output)
{
    if(moves)
    {
        Node *display = moves->getNode(); //create a new node, get the node from the linked list class
        display->Sort(display); //display said node
        display->display(display, output, moves->solveX); //move the node forward by one
        out(moves->next, output); //call the output function
    }
}

void LinkedList::insertList(LinkedList *&head, Node *add, int n, double fx)
{
    //n will be where we want to store it;
    int i = 0;
    //create a linkedlist to traverse our list
    LinkedList *in = new LinkedList;
    LinkedList *trav;
    //set up n to be added to the list
    in->solution = add;
    in->solveX = fx;
    //link trav to head
    trav = head;
    if(!head) //if head is empty
    {
        head = in; //link head to in
    }
    else //otherwise
    {
        while(trav->next && i < n) //while trav->next and while i < n
        {
            trav = trav->next; //move to the next
            i++; //i++
        }

        if(trav->next == nullptr)
        {
            trav->next = in;
            //connect the last node to in (which has our data)
        }
        else
        {
            trav->next = in; //connect trav to in
            in->next = trav->next->next; //connect in to the node ahead of trav->next->next
        }
    }


}
