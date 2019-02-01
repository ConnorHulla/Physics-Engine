#ifndef NODE_H
#define NODE_H
#include <fstream>

class Node
{
    private:
        int power; //exponent
        double coeff; //coefficient
        Node *next = nullptr; //next node
        //double x_val;
        //Equation *head;

    public:

        //constructors
        Node(); //default constructor
        Node(double, int);//overloaded constructor

        //Mutator functions
        void setPow(int pr) { power = pr; } //gets the exponent value, stores it into pow
        void setCoeff(double cof) { coeff = cof; } //gets the coefficient, stores it into coeff
        void setNode(Node *&, double, int);

        //void setX(double val) { x_val = val; }

        //Accessor functions
        int getPow() const { return power; }
        double getCoeff() const { return coeff; }
        Node *movenext() { return next; }

        //Other functions
        void display(Node *, std::ofstream&, double);
        void combine(Node *&);
        double Calculate(Node *, double);
        void Sort(Node *&);
};

#endif // Node_H
