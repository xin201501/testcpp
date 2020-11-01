#pragma once
#include<memory>
template<typename>
struct Node;
template<typename>
class MyList;
template<typename T>
struct Node {
    using value_type = T;
    T data;
    Node* previous;
    Node* next;
};
template<typename T>
class MyList {
    using value_type = T;
private:
    std::unique_ptr<Node<T>> head;
    std::unique_ptr<Node<T>> end;
public:
    MyList() :head(new Node<T>{ .previous = nullptr ,.next = nullptr }), end(head->next) {}
    MyList(const MyList& anotherList) :MyList() {
        auto cur = anotherList.head();
        while (cur) {
            end.reset(new Node<T>{ cur->data })
        }
    }
};