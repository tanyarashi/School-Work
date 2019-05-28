//
//  main.cpp
//  hw7
//
//  Created by Tanya Sharma on 3/31/19.
//  Copyright © 2019 Tanya Sharma. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;


/*
 
 Used the text to write the functions excpet for insertBTree function
 which was only psuedo code
 
 */



class bTree
{
public:
    bool search(const int& searchItem);
    void insert(const int& insertItem);
    void inOrder(string output, ofstream &outputFile);
    bTree(int order);
    void printLevel(bTree *current, int level,  string output, ofstream &outputFile);

    int order;
    int heightOfTree(bTree *node);
    void printGivenLevel(bTree *root, int level,  string output, ofstream &outputFile);
    void print(bTree *root, int level,  string output, ofstream &outputFile);
    
    void printLevelRec(int level, string output, ofstream &outputFile);
    
    void searchNode(bTree *current, const int& item, bool& found, int& location);
    void insertBTree(bTree *current, const int& insertItem, int& median,
                     bTree *&rightChild, bool& isTaller);
    void insertNode(bTree *current, const int& insertItem,
                    bTree* &rightChild, int insertPosition);
    void splitNode(bTree *current,    const int& insertItem, bTree* rightChild,    int insertPosition,
                   bTree* &rightNode,    int &median);
    void recInorder(bTree *current,  string output, ofstream &outputFile);
    
protected:
    bTree *root;
    
private:
   
    int recCount;
    int bTreeOrder;
    int *list;
    bTree **children;
    
    
};


//default constructor
bTree::bTree(int order)
{
    root = NULL;
    bTreeOrder = order;
    list = new int[order - 1];
    children = new bTree*[order];
    this->order = order;
}


//search

bool bTree::search(const int& searchItem)
{
    bool found = false;
    int loc;
    bTree *current;
    current = root;
    while (current != NULL && !found)
    {
        searchNode(current, searchItem, found, loc);
        if (!found)
            current = current->children[loc];
    }
    return found;
} //end search


//searchNode

void bTree::searchNode(bTree *current, const int& item, bool& found, int& loc)
{
    loc = 0;
    while (loc < current->recCount    && item > current->list[loc])
        loc++;
    if (loc < current->recCount && item == current->list[loc])
        found = true;
    else
        found = false;
} //end searchNode


//inOrder

void bTree::inOrder(string output, ofstream &outputFile)
{
    recInorder(root, output, outputFile);
} // end inOrder


//recInorder
void bTree::recInorder(bTree *current, string output, ofstream &outputFile)
{
    if (current != NULL)
    {
        recInorder(current->children[0],output,outputFile);
        for (int i = 0; i < current->recCount; i++)
        {
            outputFile << current->list[i] << " ";
            recInorder(current->children[i + 1], output,outputFile);
        }
    }
} //end recInorder


//insert
void bTree::insert(const int& insertItem)
{
    bool isTaller = false;
    int median;
    bTree *rightChild;
    insertBTree(root, insertItem, median, rightChild, isTaller);
    if (isTaller) //the tree is initially empty or the root
        //was split by the function insertBTree
    {
        bTree *tempRoot;
        tempRoot = new bTree(order);
        tempRoot->recCount = 1;
        tempRoot->list[0] = median;
        tempRoot->children[0] = root;
        tempRoot->children[1] = rightChild;
        root = tempRoot;
    }
    
} //end insert


//insertBTree
void bTree::insertBTree(bTree *current, const int &insertItem, int &median,    bTree *&rightChild, bool &isTaller)
{
    int pos;
    isTaller = false;
    if (current == NULL)
    {
        median = insertItem;
        rightChild = NULL;
        isTaller = true;
    }
    else
    {
        bool found;
        searchNode(current, insertItem, found, pos);
        if (found == true) {} //do nothing cause duplicate
        else
        {
            int newMedian;
            bTree *newChild;
            insertBTree(current->children[pos], insertItem, newMedian, newChild, isTaller);
            if (isTaller == true)
            {
                if (current->recCount < bTreeOrder - 1)
                {
                    isTaller = false;
                    insertNode(current, newMedian, newChild, pos);
                }
                else
                {
                    splitNode(current, newMedian, newChild, pos, rightChild, median);
                    
                }
            }
        }
    }
}//end insertBTree


//splitNode
void bTree::splitNode(bTree *current, const int& insertItem, bTree* rightChild, int insertPosition, bTree *&rightNode, int &median)
{
    rightNode = new bTree(order);
    int mid = (bTreeOrder - 1) / 2;
    if (insertPosition <= mid) //new item goes in the first half of the node
    {
        int index = 0;
        int i = mid;
        while (i < bTreeOrder - 1)
        {
            rightNode->list[index] = current->list[i];
            rightNode->children[index + 1] = current->children[i + 1];
            index++;
            i++;
        }
        current->recCount = mid;
        insertNode(current, insertItem, rightChild,    insertPosition);
        (current->recCount)--;
        median = current->list[current->recCount];
        rightNode->recCount = index;
        rightNode->children[0] = current->children[current->recCount + 1];
    }
    else //new item goes in the second half of the node
    {
        int i = mid + 1;
        int index = 0;
        while (i < bTreeOrder - 1)
        {
            rightNode->list[index] = current->list[i];
            rightNode->children[index + 1] = current->children[i + 1];
            index++;
            i++;
        }
        current->recCount = mid;
        rightNode->recCount = index;
        median = current->list[mid];
        insertNode(rightNode, insertItem, rightChild, insertPosition - mid - 1);
        rightNode->children[0] = current->children[current->recCount + 1];
    }
} //splitNode


//insertNode
void bTree::insertNode(bTree *current, const int& insertItem, bTree *&rightChild, int insertPosition)
{
    int index;
    for (index = current->recCount; index > insertPosition;  index--)
    {
        current->list[index] = current->list[index - 1];
        current->children[index + 1] = current->children[index];
    }
    current->list[index] = insertItem;
    current->children[index + 1] = rightChild;
    current->recCount++;
} //end insertNode


    

 
int bTree::heightOfTree(bTree *node)
{
    if (node == NULL) return 0;
    else
    {
        int height = heightOfTree(node->children[0]);
        return height + 1;
    }
}

void bTree::printGivenLevel(bTree *root, int level,  string output, ofstream &outputFile)
{
    if (root == NULL) return;
    if (level == 1){}
    else if (level > 1)
    {
        printGivenLevel(root->children[0], level - 1, output, outputFile);
        for (int i = 0; i < root->recCount; i++)
        {
            printGivenLevel(root->children[i+1], level - 1, output, outputFile);
        }
        
    }
}


void bTree::print(bTree *root, int level,  string output, ofstream &outputFile)
{
    if (root == NULL) return;
    if (level == 1)
    {
        for (int i = 0; i < root->recCount; i++)
        {
            outputFile << root->list[i] << " "; //output to file
        }
    }
    else if (level > 1)
    {
        print(root->children[0], level - 1, output, outputFile);
        for (int i = 0; i < root->recCount; i++)
        {
            print(root->children[i + 1], level - 1, output, outputFile);
        }
        
    }
}

void bTree::printLevel(bTree *current, int level,  string output, ofstream &outputFile)
{
    int x = 0;
    int h = heightOfTree(root);
    if(level> h){
        outputFile<< "empty";
        return;
    }
    int i;
    for (i = 1; i <= h; i++)
    {
        x++;
        if (x == level)
        {
            cout << "PRINTING LEVEL " << x << endl;
            print(root, i, output, outputFile);
        }
        printGivenLevel(root, i, output, outputFile);
    }
}



void bTree::printLevelRec(int level,  string output, ofstream &outputFile)
{
    printLevel(root, level, output, outputFile);
}

int main(int argc, char *argv[]){
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    string command = am.get("command");
    
    ifstream inFile(input);
    ofstream outputFile(output);
    ifstream commandFile(command);
    
    
    
    if (inFile.is_open())
        cout << "FILE OPEN" << endl;
    if (commandFile.is_open())
        cout << "COMMAND FILE OPEN" << endl;
    
    if (inFile.peek() == ifstream::traits_type::eof())
        cout << "FILE EMPTY";
    else if (commandFile.peek() == ifstream::traits_type::eof())
        cout << "COMMAND FILE EMPTY";
    
    if (inFile.fail() || commandFile.fail())
    {
        cout << "FILE NOT OPEN" << endl;
    }
    
    
    string inputline;
    string commandline;
    
    int inputNumber;
    int findOrder;
    int inorderTrav;
    int findLevel;
    string orderNum;
    string levNum;
    int order;
    int lev;
    
    
   
        

    
    while (getline(commandFile, commandline)){
        if(commandline.empty()){}
        else{
        findOrder = commandline.find("Degree=");
        
        if(findOrder != -1){
            orderNum = commandline.substr(findOrder +7);
            order = stoi(orderNum);
        }
    }
    }
    bTree btreeobj(order);
    
while (inFile.good()){
    
    inFile >> inputline;
    inputNumber = stoi(inputline);
    btreeobj.insert(inputNumber);
    
    
}
    commandFile.clear();
    commandFile.seekg(0, ios::beg);
    
    while (getline(commandFile, commandline)){
        
        if(commandline.empty()){}
        else{
    inorderTrav = commandline.find("Inorder Traversal");
    findLevel = commandline.find("Level");
      
        
        if (inorderTrav != -1){
            btreeobj.inOrder(output, outputFile);
            outputFile<<endl;
            
        }
        if (findLevel != -1){
            levNum = commandline.substr(findLevel + 6);
            lev = stoi(levNum);
            btreeobj.printLevelRec(lev, output, outputFile);
            outputFile<<endl;
            
            
    }
    
}
    }
    
    
    return 0;
}
