//
// Created by Ricky Saputra on 02/23/2020
//

#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

//Display the output for the Skiplist
ostream &operator<<(ostream &out, const SkipList &skipList) {
    for (int i = skipList.depth - 1; i >= 0; i--) {
        out << "Level: " << i << " -- ";

        SkipList::SNode *curr = skipList.frontGuards[i];
        while (curr != nullptr) {
            out << curr->data << ", ";
            curr = curr->next;
        }
        out << "\n";

    }
    return out;
}

//Constructor for SNode
SkipList::SNode::SNode(int data) {
    this->data = data;
    next = nullptr;
    prev = nullptr;
    upLevel = nullptr;
    downLevel = nullptr;
}

//Constructor for Skiplist
SkipList::SkipList(int depth) {
    this->depth = depth;
    frontGuards = new SNode *[depth];
    rearGuards = new SNode *[depth];
    for (int i = 0; i < depth; i++) {
        frontGuards[i] = new SNode(INT_MIN);
        rearGuards[i] = new SNode(INT_MAX);

        //Set pointer Next
        frontGuards[i]->next = rearGuards[i];
        rearGuards[i]->next = nullptr;

        //Set pointer Prev
        frontGuards[i]->prev = nullptr;
        rearGuards[i]->prev = frontGuards[i];

        //Set pointer upLevel
        if (i != depth - 1) {
            frontGuards[i]->upLevel = frontGuards[i + 1];
            rearGuards[i]->upLevel = rearGuards[i + 1];
        }

        //Set pointer downLevel
        if (i != 0) {
            frontGuards[i]->downLevel = frontGuards[i - 1];
            rearGuards[i]->downLevel = rearGuards[i - 1];
        }
    }
}

//Returns true if (rand() % 2) == 1 else return false
bool SkipList::alsoHigher() const {
    return (rand() % 2) == 1 ? true : false;
}

//This fuction adds node to the skiplist
bool SkipList::add(int data) {
    int temp = 1;
    SNode *NextNode = frontGuards[0];
    SNode *NewNode = new SNode(data);

    while (NextNode != nullptr && NextNode->data <= data) {
        //insert if no elements exist
        if (NextNode == rearGuards[0]) {
//            NewNode = new SNode(Data);
            addBefore(NewNode, NextNode);
            while (alsoHigher() && temp <= depth - 1) {
                SNode *NewUpper = new SNode(data);
//                SNode *NextUpper = FrontGuards[temp]->Next;
                NewNode->upLevel = NewUpper;
                NewUpper->downLevel = NewNode;
                addBefore(NewUpper, rearGuards[temp]);
                NewNode = NewUpper;
                temp++;
            }
            return true;
        }
        //If it has the same data, return false, no duplicates allowed
        if (NextNode->data == data) {
            cout << "No Duplicates Allowed: " << data << endl;
            delete NewNode;
            return false;
        }
        NextNode = NextNode->next;
    }

//    auto *NewNode = new SNode(Data);
    addBefore(NewNode, NextNode);
    temp = 1;
    while (alsoHigher() && temp <= depth - 1) {
        SNode *NewUpper = new SNode(data);
        NewNode->upLevel = NewUpper;
        NewUpper->downLevel = NewNode;
        SNode *NextUpper = frontGuards[temp]->next;
        while (NextUpper != nullptr && NextUpper->data < data) {
            NextUpper = NextUpper->next;
        }
        addBefore(NewUpper, NextUpper);
        NewNode = NewUpper;
        temp++;
    }
    return true;
}

//This function is to add node before the next node
void SkipList::addBefore(SNode *newNode, SNode *nextNode) {
    nextNode->prev->next = newNode;
    newNode->next = nextNode;
    newNode->prev = nextNode->prev;
    nextNode->prev = newNode;
}

//Destructor for Skiplist
SkipList::~SkipList() {
    // need to delete individual nodes
    SNode *Curr;
    SNode *Temp;
    for (int I = 0; I < depth; I++) {
        Curr = frontGuards[I];
        while (Curr != nullptr) {
            Temp = Curr;
            Curr = Curr->next;
            delete Temp;
        }
    }
    delete[] frontGuards;
    delete[] rearGuards;
}

//This function removes node from Skiplist
bool SkipList::remove(int data) {
    if (!contains(data)) {
        return false;
    }

    SNode *Temporary;
    SNode *Curr = frontGuards[depth - 1];
    while (Curr != nullptr) {
        if (Curr->next->data == data) {
            SNode *RemoveNext = Curr->next;
            Temporary = RemoveNext;
            RemoveNext = RemoveNext->next;
            RemoveNext->prev = Curr;
            Curr->next = RemoveNext;
            delete Temporary;

        } else if (Curr->next->data < data) {
            Curr = Curr->next;
        } else if (!contains(data)) {
            return true;
        } else {
            Curr = Curr->downLevel;
        }
    }
    return false;
}

//Returns true when Skiplist contains the data
bool SkipList::contains(int data) {
    SNode *curr = frontGuards[depth - 1];
    while (curr != nullptr) {
        if (curr->next->data < data) {
            curr = curr->next;
        }
        if (curr->next->data == data) {
            return true;
        } else {
            curr = curr->downLevel;
        }
    }
    return false;
}

