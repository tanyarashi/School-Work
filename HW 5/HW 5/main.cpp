//
//  main.cpp
//  HW 5
//
//  Created by Tanya Sharma on 3/19/19.
//  Copyright © 2019 Tanya Sharma. All rights reserved.
//


#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;
struct Node
{
    char info;
    int nums;
    struct Node* next;
};

class Stack {
private:
    Node* top;
public:
    Stack();
    void push(char x);
    void pushInt(int y);
    void pop();
    void Display();
    bool BalancedParanthesis(string value);
    int prec(char c);
    string inToPost(string s);
    int evaluatePostfix(string exp);
    bool isEmpty();
};

Stack::Stack()
{
    top = NULL;
}
void Stack::push(char x)
{
    Node* temp = new Node;
    {
        temp->info = x;
        temp->next = top;
        top = temp;
    }
    
}
void Stack::pushInt(int y)
{
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    if (temp == NULL)
        cout << "stack is full" << endl;
    else
    {
        temp->nums = y;
        temp->next = top;
        top = temp;
    }
    
}
void Stack::pop()
{
    Node* temp = new Node;
    if (top == NULL)
    {
        return;
    }
    else
    {
        temp = top;
        top = top->next;
        temp->next = NULL;
        free(temp);
    }
    
}
void Stack::Display()
{
    struct Node* temp;
    if (top == NULL)
    {
        cout << "stack is empty" << endl;
    }
    else
    {
        temp = top;
        while (temp != NULL)
        {
            cout << temp->info << endl;
            temp = temp->next;
        }
    }
}
bool Stack::BalancedParanthesis(string value)
{
    int i = 0;
    while (value[i])
    {
        if (value[i] == '(')
        {
            push(value[i]);
        }
        else if (value[i] == '[')
        {
            push(value[i]);
        }
        else if (value[i] == '{')
        {
            push(value[i]);
        }
        else if (value[i] == ')')
        {
            if (top == NULL || top->info != '(')
                return false;
            pop();
        }
        else if (value[i] == ']')
        {
            if (top == NULL || top->info != '[')
                return false;
            pop();
        }
        else if (value[i] == '}')
        {
            if (top == NULL || top->info != '{')
                return false;
            pop();
        }
        i++;
    }
    if (top == NULL)
        return true;
    else
        return false;
}
bool Stack::isEmpty()
{
    if (top == NULL)
        return true;
    return false;
}

int Stack::prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string Stack::inToPost(string s)
{
    push('N');
    int l;
    l = s.length();
    string ns;
    for (int i = 0; i < l; i++)
    {
        
        if (isalpha(s[i]) || isdigit(s[i]))
            ns += s[i];
        
        else if (s[i] == '(')
            push('(');
        else if (s[i] == '[')
            push('[');
        else if (s[i] == '{')
            push('{');
        else if (s[i] == ')')
        {
            while (top->info != 'N' && top->info != '(')
            {
                char c = top->info;
                pop();
                ns += c;
            }
            if (top->info == '(')
            {
                char c = top->info;
                pop();
            }
        }
        else if (s[i] == ']')
        {
            while (top->info != 'N' && top->info != '[')
            {
                char c = top->info;
                pop();
                ns += c;
            }
            if (top->info == '[')
            {
                char c = top->info;
                pop();
            }
        }
        else if (s[i] == '}')
        {
            while (top->info != 'N' && top->info != '{')
            {
                char c = top->info;
                pop();
                ns += c;
            }
            if (top->info == '{')
            {
                char c = top->info;
                pop();
            }
        }
        else {
            while (top->info != 'N' && prec(s[i]) <= prec(top->info))
            {
                char c = top->info;
                pop();
                ns += c;
            }
            push(s[i]);
        }
        
    }
    while (top->info != 'N')
    {
        char c = top->info;
        pop();
        ns += c;
    }
    pop();
    return ns;
    
}

int Stack::evaluatePostfix(string exp)
{
    int temp, i;
    
    for (i = 0; exp[i]; ++i)
    {
        cout << "entered for loop for eval postfix" << endl;
        
        if (exp[i] == ' ')
        {
            cout << "a blank space so skip it" << endl;
            continue;
        }
        
        else if (isdigit(exp[i]))
        {
            cout << "found a digit" << endl;
            int num;
            num = 0;
            
            while (isdigit(exp[i]))
            {
                num = num * 10 + (int)(exp[i] - '0');
                i++;
            }
            i--;
            pushInt(num);
            cout << "push it" << endl;
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
        {
            cout << "it is scanned now" << endl;
            int val1 = top->nums;
            cout << "val 1 is " << val1 << endl;
            pop();
            cout << "pop val 1 " << endl;
            int val2 = top->nums;
            cout << "val 2 is " << val2 << endl;
            pop();
            cout << "pop val 2 " << endl;
            
            switch (exp[i])
            {
                case '+': pushInt(val2 + val1); break;
                case '-': pushInt(val2 - val1); break;
                case '*': pushInt(val2 * val1); break;
                case '/': pushInt(val2 / val1); break;
                    
            }
            
        }
    }
    cout << "reached end" << endl;
    temp = top->nums;
    pop();
    return temp;
    
}

int main(int argc, char*argv[]) {
   /*
    if (argc < 2) {
        cout << "Usage: evalexpr input=input1.txt output=output1.txt" << std::endl;
        return -1;
    }
    */
    ArgumentManager am(argc, argv);
    const string input = am.get("input");
    const string output = am.get("output");
    
    ifstream infile(input);
    string line = "";
    ofstream outfile(output);
    
    if (infile.is_open())
        cout << "FILE OPEN" << endl;
    if (infile.fail())
    {
        cout << "FILE NOT OPEN" << endl;
    }
    
    Stack Num;
    /*Stack Num2;*/
    bool balanced = true;
    int count;
    count = 1;
    string* lines = new string[1000];
    
    while (getline(infile, line))
    {
        if (!line.empty())
        {
            /*Num2.push2(line);*/
            lines[count - 1] = line;
            if (Num.BalancedParanthesis(line) == false)
            {
                cout << "Error at: " << count << endl;
                outfile << "Error at: " << count << endl;
                balanced = false;
            }
            count++;
            
            while (!Num.isEmpty())
            {
                Num.pop();
            }
        }
    }
    
    
    if (balanced == true)
    {
        
        for (int i = 0; i < count - 1; i++)
        {
            int j;
            j = 0;
            string value = lines[i];
            if (isdigit(lines[i][0]) || isalpha(lines[i][0]) || lines[i][0] == '+' || lines[i][0] == '-' || lines[i][0] == '(' || lines[i][0] == '[' || lines[i][0] == '{')
            {
                while (j < value.length())
                {
                    if (value[j] == '-')
                    {
                        if (j == 0 || value[j - 1] == '(' || value[j - 1] == '[' || value[j - 1] == '{' || value[j - 1] == '+' || value[j - 1] == '-' || value[j - 1] == '*' || value[j - 1] == '/' || value[j - 1] == '^')
                        {
                            value.replace(j, 1, "0-");
                        }
                    }
                    else if (value[j] == '+')
                    {
                        if (j == 0 || value[j - 1] == '(' || value[j - 1] == '[' || value[j - 1] == '{' || value[j - 1] == '+' || value[j - 1] == '-' || value[j - 1] == '*' || value[j - 1] == '/' || value[j - 1] == '^')
                        {
                            value.replace(j, 1, "0+");
                        }
                    }
                    lines[i] = value;
                    j++;
                }
                cout << "test " << lines[i] << endl;
                cout << "test " << Num.inToPost(lines[i]) << endl;
                
                string post = Num.inToPost(lines[i]);
                for (int i = 1; i < post.length(); i += 2)
                {
                    post.insert(i, " ", 1);
                }
                cout << post << endl;
                
                for (int i = 0; i < post.length(); i++)
                {
                    cout << "about to change to nums here" << endl;
                    if (isalpha(post[i]))
                    {
                        if (post[i] == 'a')
                            post.replace(i, 1, "9");
                        else if (post[i] == 'b')
                            post.replace(i, 1, "25");
                        else if (post[i] == 'c')
                            post.replace(i, 1, "49");
                        else if (post[i] == 'd')
                            post.replace(i, 1, "121");
                        else if (post[i] == 'e')
                            post.replace(i, 1, "169");
                        else if (post[i] == 'f')
                            post.replace(i, 1, "289");
                        else if (post[i] == 'g')
                            post.replace(i, 1, "361");
                        else if (post[i] == 'h')
                            post.replace(i, 1, "529");
                        else if (post[i] == 'i')
                            post.replace(i, 1, "841");
                        else if (post[i] == 'j')
                            post.replace(i, 1, "961");
                        else if (post[i] == 'k')
                            post.replace(i, 1, "1369");
                        else if (post[i] == 'l')
                            post.replace(i, 1, "1681");
                        else if (post[i] == 'm')
                            post.replace(i, 1, "1849");
                        else if (post[i] == 'n')
                            post.replace(i, 1, "2209");
                        else if (post[i] == 'o')
                            post.replace(i, 1, "2809");
                        else if (post[i] == 'p')
                            post.replace(i, 1, "3481");
                        else if (post[i] == 'q')
                            post.replace(i, 1, "3721");
                        else if (post[i] == 'r')
                            post.replace(i, 1, "4489");
                        else if (post[i] == 's')
                            post.replace(i, 1, "5041");
                        else if (post[i] == 't')
                            post.replace(i, 1, "5329");
                        else if (post[i] == 'u')
                            post.replace(i, 1, "6241");
                        else if (post[i] == 'v')
                            post.replace(i, 1, "6889");
                        else if (post[i] == 'w')
                            post.replace(i, 1, "7921");
                        else if (post[i] == 'x')
                            post.replace(i, 1, "9409");
                        else if (post[i] == 'y')
                            post.replace(i, 1, "10201");
                        else if (post[i] == 'z')
                            post.replace(i, 1, "10609");
                        else if (post[i] == 'A')
                            post.replace(i, 1, "11449");
                        else if (post[i] == 'B')
                            post.replace(i, 1, "11881");
                        else if (post[i] == 'C')
                            post.replace(i, 1, "12769");
                        else if (post[i] == 'D')
                            post.replace(i, 1, "16129");
                        else if (post[i] == 'E')
                            post.replace(i, 1, "17161");
                        else if (post[i] == 'F')
                            post.replace(i, 1, "18769");
                        else if (post[i] == 'G')
                            post.replace(i, 1, "19321");
                        else if (post[i] == 'H')
                            post.replace(i, 1, "22201");
                        else if (post[i] == 'I')
                            post.replace(i, 1, "22801");
                        else if (post[i] == 'J')
                            post.replace(i, 1, "24649");
                        else if (post[i] == 'K')
                            post.replace(i, 1, "26569");
                        else if (post[i] == 'L')
                            post.replace(i, 1, "27889");
                        else if (post[i] == 'M')
                            post.replace(i, 1, "29929");
                        else if (post[i] == 'N')
                            post.replace(i, 1, "32041");
                        else if (post[i] == 'O')
                            post.replace(i, 1, "32761");
                        else if (post[i] == 'P')
                            post.replace(i, 1, "36481");
                        else if (post[i] == 'Q')
                            post.replace(i, 1, "37249");
                        else if (post[i] == 'R')
                            post.replace(i, 1, "38809");
                        else if (post[i] == 'S')
                            post.replace(i, 1, "39601");
                        else if (post[i] == 'T')
                            post.replace(i, 1, "44521");
                        else if (post[i] == 'U')
                            post.replace(i, 1, "49729");
                        else if (post[i] == 'V')
                            post.replace(i, 1, "51529");
                        else if (post[i] == 'W')
                            post.replace(i, 1, "52441");
                        else if (post[i] == 'X')
                            post.replace(i, 1, "54289");
                        else if (post[i] == 'Y')
                            post.replace(i, 1, "57121");
                        else if (post[i] == 'Z')
                            post.replace(i, 1, "58081");
                    }
                }
                cout << "does it reach here" << endl;
                lines[i] = post;
                cout << lines[i] << endl;
                cout << " or does it reach here" << endl;
                cout << Num.evaluatePostfix(post) << endl;
            }
        }
        bool isEqual = true;
        for (int i = 0; i < count - 2; i++)
        {
            if ((isdigit(lines[i][0]) && isdigit(lines[i + 1][0])) || (isalpha(lines[i][0]) && isalpha(lines[i + 1][0])) || (lines[i][0] == '+' && lines[i + 1][0] == '+') || (lines[i][0] == '-') && (lines[i + 1][0] == '-'))
            {
                if (Num.evaluatePostfix(lines[i]) != Num.evaluatePostfix(lines[i + 1]))
                    isEqual = false;
            }
            else
                isEqual = false;
        }
        if (isEqual == true)
        {
            cout << "Yes" << endl;
            outfile << "Yes" << endl;
        }
        else if (isEqual == false)
        {
            cout << "No" << endl;
           outfile << "No" << endl;
        }
    }
    
    system("pause");
    return 0;
    
}
