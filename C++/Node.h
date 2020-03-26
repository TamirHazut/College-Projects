#ifndef __NODE_H_
#define __NODE_H_

#include <iostream>
using namespace std;

template<class T>
class Node
{
    public:
        T data;
        Node<T>* next;
        Node(T& data) : data(data), next(nullptr) {}
        ~Node()
        {
            if (next)
                delete next;
        }
        bool operator==(const Node<T>& node) const { return data == node.data; }

        friend ostream& operator<<(ostream& os, const Node& node)
        {
            os << node.data;
            return  os;
        }

};
#endif