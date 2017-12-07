// constructor
template<typename _object_>
stack<_object_>::stack() {
    // root is null
    _root = 0;
}

// desctructor
template<typename _object_>
stack<_object_>::~stack() {
    // the current node
    node* __current = _root;

    // if there is at least one node
    while (__current) {
        // tmp node
        node* __tmp = __current;

        // update current
        __current = __current->_next;

        // erasing the node
        __tmp->_next = 0;
        delete __tmp;
    }
}

// push new element
template<typename _object_>
void stack<_object_>::push(_object_ __data) {
    // new node
    node* __new = new node;
    __new->_data = __data;
    __new->_next = 0;

    // if the stack is empty
    if (_root == 0)
        _root = _last = __new;
    else {
        __new->_next = _root;
        _root = __new;
    }
}

// pop element
template<typename _object_>
void stack<_object_>::pop(_object_& __data) {
    // if empty, return
    if (!_root)
        return;

    // getting the data
    __data = _root->_data;

    // the temp node
    node* __tmp = _root;

    // updating the root
    _root = _root->_next;

    // deleting the temp
    delete __tmp;
}

// top element
template<typename _object_>
void stack<_object_>::top(_object_& __data) {
    // if empty, return
    if (!_root)
        return;

    // getting the data
    __data = _root->_data;
}

// empty?
template<typename _object_>
bool stack<_object_>::empty() {
    return _root == 0;
}
