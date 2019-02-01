#include "node.h"
#include <iostream>
#include <iomanip>
#include <cmath>

Node::Node() //constructor
{
    //set default values
    power = 1;
    coeff = 1;
}

Node::Node(double co, int p) //overloaded constructor
{
    power = p;
    coeff = co;
    next = nullptr;
}

void Node::setNode(Node *&head, double co, int p)
{
    Node *ptr = new Node; //create a node to hold the values
    ptr->coeff = co;
    ptr->power = p;
    Node *tail;
    tail = head; //point taile to head
    if(!head) //if head is empty
    {
        head = ptr; //set head to ptr
    }
    else
    {
        while(tail->next != nullptr) //while tail isn't at the end
        {
            tail = tail->next; //set tail to next
        }
        tail->next = ptr; //add ptr to the end
        ptr->next = nullptr; //make ptr point to null to indicate the end of our list

    }

}
//Note to future self: Replace this with merge/quick sort when you learn about it
void Node::Sort(Node*& head)
{
    Node *comp, *second;
    int length = 0;
    Node *findl;
    findl = head;
    //get the length of the list
    while(findl) //while length isn't empty
    {
        findl = findl->next; //move length
        length++; //add to the length
    }

    comp = head; //comp starts at the head
    second = comp;//second is always one away from comp, except for in the first instance of the loop
    for (int i = length - 1; i > 0; i--)
    {
        //comp is the first box, second is the second box, second->next is the 3rd box
        for(int j = 0; j < i; j++)
        {
            if(second == head) //if we are at the head
            {
                second = comp->next; //move second one sapce over
                if (comp->getPow() < second->getPow()) //if we need to swap the head
                {
                    comp->next = second->next; //connect the first node to the 3rd node
                    second->next = comp; //connect the second node to the first
                    comp = second; //set comp = to second which has the correct order
                    head = second; //set sort = to second to update the list
                    second = second->next; //move second
                }
                continue; //continue
            }
            else if (second->getPow() < second->next->getPow()) //if the current pow is less than the next power
            {
                comp->next = second->next; //connect the first comp into the second
                second->next = second->next->next;//connect the second node to the fourth
                comp->next->next = second; //connect the 3rd node to the second
                comp = comp->next; //move comp over once
                //the second and third nodes have been switched (second->arabic and second->next->arabic have been switched
                continue; //continue
            }
            //if none of the above conditions were true
            comp = second; //move comp over by one
            second = second->next; //move second over by one
        }
        comp = head; //set comp and second back to the start
        second = comp;
    }
    return;
}

double Node::Calculate(Node *head, double x_val)
{
    Node *calc = new Node;
    calc = head;
    double sum = 0;
    while(calc)
    {
        sum += pow(x_val, calc->getPow()) * calc->getCoeff(); //x to the power of n * the coefficient
        calc = calc->next; //move calc
    }
    return sum;
}

void Node::display(Node *h, std::ofstream& output, double x_val)
{
    Node *start;
    start = h;
    int first = 0;
    double answer = Calculate(h, x_val); //call calculate function
    output << "f(" << x_val << ") = "; //output f(x)
    while(start)
    {
        if(start->coeff == 0) //if the coefficient is 0, skip
        {
            start = start->next; //move start to the next
            continue;
        }
        else if(start->coeff < 0 && first > 0) //if we are not on the first run of the loop and if the coefficient is less than 0
        {
            start->coeff *= -1; //make the coefficent negative
            output << "- "; //output the minus sign
        }
        else if(start->coeff > 0 && first > 0) //if coefficient is greater than 0 and if first is greater than 0
        {
            output << "+ "; //output the + sign
        }
        if (start->coeff != 1 || (start->coeff == 1 && start->power == 0)) //if coefficient is 1 or if coefficient is 1 and the exponent is 0
        {
            output << start->coeff; //output the coefficient
        }
        if (start->power != 0) //if the exponent isn't 0
        {
            output << "x"; //output x
            if(start->power != 1) //if the exponent isn't 1
            {
                output << "^" << start->power; //output ^ and the exponent
            }
        }
        output << " "; //output a space
        first++; //add one to first to indicate that we have completed the first run of the loop
        start = start->next;// move start
    }
    output << " = " << std::setprecision(3) << std::fixed << answer  << std::defaultfloat << std::endl; //output the answer like this: = answer
}
