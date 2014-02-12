#ifndef TREE_H
#define TREE_H

// TODO:
// * iterators

template <class T>
class Tree
{
public:
    Tree();
    ~Tree();

    void clear();
    bool isEmpty() const;

    bool add(const T& value);
    bool remove(const T& value);
    bool contains(const T& value) const;

    size_t size() const;

private:
    Tree(const Tree& t) = default;
    Tree& operator=(const Tree& t) = default;

    class Node
    {
    public:
        Node* parent;
        Node* left;
        Node* right;
        T value;
    };
};


template <class T>
Tree<T>::Tree()
{
}

template <class T>
Tree<T>::~Tree()
{
}

#endif // TREE_H
