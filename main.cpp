//Project by Connor Hulla
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "node.h"
#include "linkedlist.h"
using namespace std;

double parse(string, Node *&);
void display(Node *);
int main()
{
    int i = 0;
    double xval;
    fstream input;
    ofstream out;
    out.open("answers.txt");
    LinkedList *head = nullptr;
    input.open("poly.txt", ios :: in);
    string line;
    if(input) //if the file opened correctly
    {
        while(!(input.eof())) //while the isn't at the end
              {
                  //get the line and parse it
                  getline(input, line);
                  Node *equation;
                  xval = parse(line, equation);

                  //equation->Display(equation, xval);
                  head->insertList(head, equation, i, xval);
                  i++;
               }
        //display the list
        head->out(head, out);
        input.close();
        out.close();
        //close the files
    }
    else
        cout << "File failed to open\n";
    head->recursiveDelete(head); //deletes itself

    return 0;
}

double parse(string fx, Node *&head)
{
    Node *ptr = new Node;
    head = nullptr;
    unsigned int i = 0;
    double coefficient = 1, xVal; //xVal will hold our x value
    int exponent = 1;
    string line = fx;
    string num;
    i = line.find('f'); //set the position to where ever f is
    int f = i + 2; //set f to that position

    //Extract the x value out of the ()
    while(line.at(f) != ')') //while line at position doesn't = ')'
    {
        num = num + line.at(f); //concat line at position f to num
        f++; //move position forward by one
    }

    xVal = stod(num); //convert our num to decimal, set it to x val

    i = line.find('='); //find the = sign
    i += 2; //move i by twice (where the first term should be
    fx = line.substr(i); //cut off line from the 0th position to the ith position

    ptr = head; //point to head so we can maintain its value
    i = 0; //set i = to 0
    while(!(fx.find('-') == -1 && fx.find('+') == -1 && fx.find('x') == -1)) //while we can't find a - or a + sign
    {
        i = 0; //set i = to 0
        exponent = 1; //set exponent to 1
        num = ""; //make num empty
        if (fx.at(i) == '-') //if thers a minus sign, make the coefficient negative
        {
            if(fx.at(i + 1) == ' ')
            {
                //if theres a space ahead
                coefficient = -1;
                i += 2; //move i 2 places forward

            }
            else //if we have a negative term in the first part of our equation
                i++; //move i forward by one
        }
        else if (fx.at(i) == '+') //make the coefficient positive if we find a + sign
        {
            coefficient = 1; //set coefficient equal to 1
            i += 2; //move i forward to places
        }

        if (fx.at(i) == 'x') //if theres a positive sign or no sign, make it positive
            coefficient = 1; //set coefficent to 1 because theres no term infront of the x in this situation

        else
        {
            //coefficient = stod(fx.at(i)); //coefficient = number at i
            if (fx.find(' ', i) < fx.find('x', i) || fx.find('x', i) == -1) //if theres a space before an x or if there isn't an x
            {
                exponent = 0; //exponent = 0
                fx = fx.substr(i); // cut off the line from every point before the position
                i = 0; //set the position back to 0
                while(i < fx.length() && i < fx.find(' ')) //while i is less than the length of the line and if i is less than the position of the next space
                {
                    num = num + fx.at(i); //concatinate num with the char at the ith position
                    i++;//i++
                }
                i++; //move i forward one
                if (i < fx.length()) //if i is less than the length of fx
                    fx = fx.substr(i); //cut it
                else //otherwise,
                    fx = ""; //get rid of fx

                coefficient *=  stod(num); //coefficient * the number we got for coefficient
                ptr->setNode(head, coefficient, exponent); //set our node
                continue; //continue
            }
            else
            {
                i = fx.find('x'); //find x
                int j = i;

                //find all the numbers before x
                while(j != 0 && fx.at(j - 1) != ' ')
                    j--;


                num = fx.substr(j, i - j);
                //num = fx.substr(0, i);
                coefficient *= stod(num); //coefficient *= our number
            }
        }
        //move I over
        i++;


        //check for exponents
        if(i < fx.length() && fx.at(i) == '^')
        {
            i++;
            if(fx.at(i) == '-')
            {
                i++;
                exponent *= -1; //if theres a negative sign, make the exponent negative
            }
            num = fx.at(i);
            while(i + 1 < fx.length() && fx.at(i + 1) != ' ') //if I is less than length and if there isn't a space
            {
                //get our exponents
                i++; //mvoe
                num = num + fx.at(i); //concat
            }
            exponent *= stoi(num); //exponent = the num we got
            i++; //move position by one
        }
        else if(exponent != 0) //otherwise if exponent isn't 0
            exponent = 1; //exponent = 1

        i++; //move i forward by one

        ptr->setNode(head, coefficient, exponent); //set the node with these values
        if (i < fx.length()) //if is less than the length of the string
            fx = fx.substr(i); //crop off
        else
            fx = ""; //fx is empty
    }
    return xVal; //return the x val
}
