#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_
#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class LinkedList
{
private:
    int listSize;
    Node<T>* head;
public:
    LinkedList() {
        head = nullptr;
        listSize = 0;
    }
    LinkedList(const LinkedList& l)
    {
        head = l.head;
        listSize = l.listSize;
    }
    ~LinkedList() { delete head; }
    class LinkedListIter
    {
        public: 
        
            LinkedListIter() : pCurrentNode (head) { } 
            LinkedListIter(const Node<T>* pNode) : pCurrentNode (pNode) { } 

            LinkedListIter& operator=(Node<T>* pNode) 
            { 
                this->pCurrentNode = pNode; 
                return *this; 
            } 
            LinkedListIter& operator++() 
            { 
                if (pCurrentNode) 
                    pCurrentNode = pCurrentNode->next; 
                return *this; 
            } 
            LinkedListIter operator++(int) 
            { 
                LinkedListIter iterator = *this; 
                ++*this; 
                return iterator; 
            } 
            bool operator!=(const LinkedListIter& iterator) {  return pCurrentNode != iterator.pCurrentNode; } 
            const T& operator*() { return pCurrentNode->data; } 
  
        private: 
            const Node<T>* pCurrentNode;  
    };

    bool add(T& data)
    {
        int current = listSize;
        if (!isDataInList(data))
            *this += *(new Node<T>(data));
        return !(current == listSize);
    }
    bool remove(T& data)
    {
        int current = listSize;
        if (isDataInList(data))
            *this -= *(new Node<T>(data));
        return !(current == listSize);
    }
    bool isEmpty() const { return listSize == 0; }
    bool isDataInList(const T& data) const 
    {
        if (!head)
            return false;
        for (LinkedListIter iterator = LinkedListIter(head); iterator != LinkedListIter(nullptr); iterator++)
        {
            if (*iterator == data)
                return  true;
        }
        return false;
    }
    Node<T>* getHead() { return head; }
    int size() const { return listSize; }

    friend ostream& operator<<(ostream& os, const LinkedList& ll)
    {
        for (LinkedListIter iterator = LinkedListIter(ll.head); iterator != LinkedListIter(nullptr); iterator++)
        {
                os << *iterator;
        }
        return os;
    }

private:
   LinkedList& operator+=(Node<T>& node) 
    {
        if (head)
        {
            Node<T>* currentNode = head;
            while (currentNode->next)
                currentNode = currentNode->next;
            currentNode->next = &node;
        } else
        {
            head = &node;
            head->next = nullptr;
        }
        listSize++;
        return *this;
    }
    LinkedList& operator-=(Node<T>& node)
    {
        if (head)
        {
            if (*head == node)
            {
                Node<T>* temp = head->next;
                head->next = nullptr;
                delete head;
                head = temp;
                listSize--;
            }
            else if (listSize > 1)
            {
                Node<T>* currentNode = head;
                Node<T>* currentPrevNode = nullptr;
                while (currentNode)
                {
                    if (*currentNode == node)
                    {
                        if (currentNode->next)
                        {
                            currentPrevNode->next = currentNode->next;
                            currentNode->next = nullptr;
                        } else
                            currentPrevNode->next = nullptr;
                        delete currentNode;
                        listSize--;
                        break;
                    }
                    currentPrevNode = currentNode;
                    currentNode = currentNode->next; 
                }
            }
        }
        return *this;
    }
};
#endif