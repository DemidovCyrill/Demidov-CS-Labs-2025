#ifndef MyStack_h
#define MyStack_h

template<class INF, class FRIEND>
class ListNode
{
private:
    INF d;
    ListNode *next;

    ListNode(void) { next = nullptr; }

    ListNode(const INF& data) : d(data), next(nullptr) {}

    ListNode(const ListNode& other) : d(other.d), next(nullptr) {}


    ListNode& operator=(const ListNode& other) {
        if (this != &other) {
            d = other.d;
            next = nullptr;
        }
        return *this;
    }


    friend FRIEND;
};


template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node *top;
public:
    MyStack(void);

    MyStack(const MyStack& other);

    MyStack& operator=(const MyStack& other);


    ~MyStack(void);

    bool any(void);

    bool append(INF n);

    bool pop(void);

    INF get(void);
};

#include "MyStack.cpp"
#endif
