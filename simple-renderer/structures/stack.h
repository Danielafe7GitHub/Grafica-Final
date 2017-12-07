#ifndef _STACK_H_
#define _STACK_H_

//! the stack
template<typename _object_>
class stack {
protected:
    //! the node
    struct node {
        //! the data
        _object_ _data;

        //! the next pointer
        node* _next;
    };

    //! the stack
    node *_root;

    //! the last node
    node *_last;

public:
    //! constructor
    stack();

    //! desctructor
    ~stack();

    //! push new element
    void push(_object_ __data);

    //! pop element
    void pop(_object_& __data);

    //! top
    void top(_object_& __data);

    //! empty?
    bool empty();
};

//! the implementation
#include "stack.hxx"

#endif
