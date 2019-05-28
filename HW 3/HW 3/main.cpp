//Tanya Sharma
//
//main.cpp
//
//
//COSC 2430 HW3

#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

class Sort
{
private:
    typedef struct node
    {
        int info;
        node *link;
        
        
    } *nodePtr;
    
    nodePtr head;
    nodePtr tail;
    nodePtr curr;
    nodePtr temp;
    nodePtr prev;
    
    int size = 0;
    
public:
    Sort()
    {
        head = NULL;
        tail = NULL;
    }
    void insert(int data);
    void divideList(node* first1, node* &first2);
    node* mergeList(node* first1, node* first2, string sor);
    void recMergeSort(node* &head, string sort);
    void mergeSort(string sortMethod);
    int partition(int list[], int first, int last, string so);
    void swap(int list[], int first, int second);
    void recQuickSort(int* arr, int first, int last, string sort);
    void quickSort(int first, int length, string sortMethod, int * arr);
    void shellSort(int arr[], int length, string sortMethod);
    void intervalIS(int arr[], int start, int inc, int length, string line);
    int printIndex(int index);
    
    
    
    
    
};

//Merge sort
void Sort::divideList(node *first1, node* &first2)
{
    
    node *mid, *curr;
    
    if (first1 == NULL) //   empty list
        first2 = NULL;
    else if (first1->link == NULL)   //  list has only 1 node
        first2 = NULL;
    else {
        mid = first1;
        curr = first1->link;
        
        if (curr != NULL)    // list has more than 2 nodes
            curr = curr->link;
        while (curr != NULL)
        {
            mid = mid->link;
            curr = curr->link;
            if (curr != NULL)
                curr = curr->link;
        }
        first2 = mid->link; //  first2 points to the first node of the second sublist
        
        mid->link = NULL;   // set the link of the last node of the first sublist to NULL
    }
}

Sort::node* Sort::mergeList(node* first1, node* first2, string sortMethod)
{
    node *lastSmall;    // pointer to the last node of the merged list
    node *newHead;  // pointer to the merged list
    
    if (first1 == NULL)  // the first sublist is empty
        return first2;
    else if (first2 == NULL) // second sublist is empty
        return first1;
    else {
        if (sortMethod == "ascending")
        {
            if (first1->info < first2->info) // compare the first nodes
            {
                newHead = first1;
                first1 = first1->link;
                lastSmall = newHead;
            }
            else {
                newHead = first2;
                first2 = first2->link;
                lastSmall = newHead;
            }
            
            while (first1 != NULL && first2 != NULL)
            {
                if (first1->info < first2->info)
                {
                    lastSmall->link = first1;
                    lastSmall = lastSmall->link;
                    first1 = first1->link;
                }
                else {
                    lastSmall->link = first2;
                    lastSmall = lastSmall->link;
                    first2 = first2->link;
                }
            }
            
            if (first1 == NULL) // first sublist is exhausted first
                lastSmall->link = first2;
            else
                lastSmall->link = first1;
            
            return newHead;
        }
        else
        {
            if (first1->info > first2->info) // compare the first nodes
            {
                newHead = first1;
                first1 = first1->link;
                lastSmall = newHead;
            }
            else {
                newHead = first2;
                first2 = first2->link;
                lastSmall = newHead;
            }
            
            while (first1 != NULL && first2 != NULL)
            {
                if (first1->info > first2->info)
                {
                    lastSmall->link = first1;
                    lastSmall = lastSmall->link;
                    first1 = first1->link;
                }
                else {
                    lastSmall->link = first2;
                    lastSmall = lastSmall->link;
                    first2 = first2->link;
                }
            }
            
            if (first1 == NULL) // first sublist is exhausted first
                lastSmall->link = first2;
            else
                lastSmall->link = first1;
            
            return newHead;
            
        }
    }
}


void Sort::recMergeSort(node* &head, string sortMethod)
{
    node *otherHead;
    
    if (head != NULL)
    {
        if (head->link != NULL)
        {
            divideList(head, otherHead);
            recMergeSort(head, sortMethod);
            recMergeSort(otherHead, sortMethod);
            head = mergeList(head, otherHead, sortMethod);
        }
    }
}

void Sort::mergeSort(string sortMethod)
{
    recMergeSort(head, sortMethod);
    
    if (head == NULL)
        tail = NULL;
    else
    {
        tail = head;
        while (tail->link != NULL)
            tail = tail->link;
    }
}

void Sort::insert(int data)
{
    node* last = new node;
    last->info = data;
    last->link = NULL;
    
    if (head == NULL)
    {
        head = last;
        tail = head;
    }
    else
    {
        tail->link = last;
        tail = last;
    }
    
}


//Quicksort
int Sort::partition(int list[], int first, int last, string so)
{
    int pivot;
    int index, smallIndex;
    swap(list, first, (first + last) / 2);
    pivot = list[first];
    smallIndex = first;
    if (so == "ascending")
    {
        for (index = first + 1; index <= last; index++)
            if (list[index] < pivot)
            {
                smallIndex++;
                swap(list, smallIndex, index);
            }
    }
    else
    {
        for (index = first + 1; index <= last; index++)
            if (list[index] > pivot)
            {
                smallIndex++;
                swap(list, smallIndex, index);
            }
        
    }
    swap(list, first, smallIndex);
    return smallIndex;
}

void Sort::swap(int list[], int first, int second)
{
    int temp;
    temp = list[first];
    list[first] = list[second];
    list[second] = temp;
}

void Sort::recQuickSort(int *arr, int first, int last, string sort)
{
    int pivotLocation;
    if (first < last)
    {
        pivotLocation = partition(arr, first, last, sort);
        recQuickSort(arr, first, pivotLocation - 1, sort);
        recQuickSort(arr, pivotLocation + 1, last, sort);
    }
}

void Sort::quickSort(int first, int length, string sortMethod, int* arr)
{
    recQuickSort(arr, 0, length, sortMethod);
}

//Shell sort
void Sort::intervalIS(int arr[], int start, int inc, int length, string line)
{
    if (line == "ascending")
    {
        int firstOutOfOrder, location;
        int temp;
        
        for (firstOutOfOrder = start + inc; firstOutOfOrder < length;
             firstOutOfOrder += inc)
            if (arr[firstOutOfOrder] < arr[firstOutOfOrder - inc])
            {
                temp = arr[firstOutOfOrder];
                location = firstOutOfOrder;
                do
                {
                    arr[location] = arr[location - inc];
                    location -= inc;
                } while (location > start && arr[location - inc] > temp);
                
                arr[location] = temp;
            }
    }
    else if (line == "descending")
    {
        int firstOutOfOrder = start, location = inc;
        int temp;
        
        for (firstOutOfOrder = start + inc; firstOutOfOrder < length;
             firstOutOfOrder+=inc)
            if (arr[firstOutOfOrder] > arr[firstOutOfOrder - inc])
            {
                temp = arr[firstOutOfOrder];
                location = firstOutOfOrder;
                do
                {
                    arr[location] = arr[location - inc];
                    location -= inc;
                } while (location > start && arr[location - inc] < temp);
                arr[location] = temp;
            }
    }
}

void Sort::shellSort(int list[], int length, string sortMethod)
{
    int inc;
    for (inc = 1; inc < (length - 1) / 9; inc = 3 * inc + 1);
    
    do
    {
        for (int start = 0; start < inc; start++)
            intervalIS(list, start, inc, length, sortMethod);
        inc = inc / 3;
    } while (inc > 0);
    
}

int Sort::printIndex(int index)
{
    curr = head;
    int count = 1;
    if (index == 0)
        return curr->info;
    else
    {
        curr = curr->link;
        while (curr != NULL && count != index)
        {
            curr = curr->link;
            count++;
        }
        if (curr != NULL)
            return curr->info;
    }
    return 0;
}



int main(int argc, char* argv[])
{
    
    ArgumentManager am(argc, argv);
    string inputName = am.get("input");
    string outputName = am.get("output");
    string commandName = am.get("command");
    
    ifstream inputFile(inputName);
    
    ofstream outputFile(outputName);
    
    ifstream commandFile(commandName);
    
    
    if (inputFile.is_open())
        cout << "FILE OPEN" << endl;
    if (commandFile.is_open())
        cout << "COMMAND FILE OPEN" << endl;
    
    if (inputFile.peek() == ifstream::traits_type::eof())
        cout << "FILE EMPTY";
    else if (commandFile.peek() == ifstream::traits_type::eof())
        cout << "COMMAND FILE EMPTY";
    
    if (inputFile.fail() || commandFile.fail())
    {
        cout << "FILE NOT OPEN" << endl;
    }
    
    Sort listSort;
    
    string commandLine;
    string commandType;
    string sortType;
    string line;
    string sortMethod;
    string indicies;
    int number;
    int arrSize = 0;
    int x;
    int size = 100000;
    int wordIndex;
    int *arr = new int[size];
    while (getline(commandFile, commandLine))
    {
        if (commandLine.find("ascending") != -1)
        {
            wordIndex = commandLine.find("ascending");
            indicies = commandLine.substr(wordIndex + 10);
        }
        else if (commandLine.find("descending") != -1)
        {
            wordIndex = commandLine.find("descending");
            indicies = commandLine.substr(wordIndex + 11);
            
        }
        else if (commandLine.find("sort") != -1)
        {
            
            wordIndex = commandLine.find("sort");
            indicies = commandLine.substr(wordIndex + 5);
            
        }
        
        if (commandLine.find("quick sort") != -1)
        {
            while (inputFile.good())
            {
                inputFile >> line;
                number = stoi(line);
                arr[arrSize] = number;
                arrSize++;
            }
            if (commandLine.find("ascending") != -1)
            {
                sortMethod = "ascending";
                listSort.quickSort(0, arrSize - 1, sortMethod, arr);
            }
            else if (commandLine.find("descending") != -1)
            {
                
                sortMethod = "descending";
                listSort.quickSort(0, arrSize - 1, sortMethod, arr);
                
            }
            else
            {
                sortMethod = "ascending";
                listSort.quickSort(0, arrSize - 1, sortMethod, arr);
            }
            
        }
        else if (commandLine.find("shell sort") != -1)
        {
            while (inputFile.good())
            {
                inputFile >> line;
                number = stoi(line);
                arr[arrSize] = number;
                arrSize++;
            }
            if (commandLine.find("ascending") != -1)
            {
                sortMethod = "ascending";
                listSort.shellSort(arr, arrSize, sortMethod);
            }
            else if (commandLine.find("descending") != -1)
            {
                sortMethod = "descending";
                listSort.shellSort(arr, arrSize, sortMethod);
                
            }
            else
            {
                sortMethod = "ascending";
                listSort.shellSort(arr, arrSize, sortMethod);
            }
            
        }
        else if (commandLine.find("merge sort") != -1)
        {
            while (inputFile.good())
            {
                inputFile >> line;
                number = stoi(line);
                listSort.insert(number);
                arrSize++;
                
            }
            if (commandLine.find("ascending") != -1)
            {
                sortMethod = "ascending";
                listSort.mergeSort(sortMethod);
            }
            else if (commandLine.find("descending") != -1)
            {
                sortMethod = "descending";
                listSort.mergeSort(sortMethod);
            }
            else
            {
                sortMethod = "ascending";
                listSort.mergeSort(sortMethod);
            }
            
            stringstream ss;
            
            
            ss << indicies;
           
            
            while (ss >> x)
            {
                if (x >= 0 && x < arrSize)
                {
                    
                    
                    outputFile << listSort.printIndex(x) << " ";
                    
                }
            }
        }
        if (commandLine.find("quick sort") != -1 || commandLine.find("shell sort") != -1)
        {
            stringstream ss;
            
            ss << indicies;
           
            
            while (ss >> x)
            {
                if (x >= 0 && x < arrSize)
                {
                    
                    
                    outputFile << arr[x] << " ";
                }
            }
        }
        
        
    }
    
    inputFile.close();
    commandFile.close();
    outputFile.close();
    return 0;
}
