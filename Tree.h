#ifndef TREE_H
#define TREE_H

#include <memory>

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

    size_t size() const { return mSize; }

    // TODO: remove
    void print() const
    {
        if (mRoot) {
            print(mRoot);
        }
    }

    class iterator
    {
        // TODO: ???
    };

private:
    Tree(const Tree& t) = default;
    Tree& operator=(const Tree& t) = default;

    struct Node
    {
        Node()
        { }
        Node(const T& v) : value(v)
        { }

        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        T value;
    };
    std::shared_ptr<Node> mRoot;
    size_t mSize;

    // TODO: remove
    void print(const std::shared_ptr<Node>& node) const
    {
        if (node->left) {
            print(node->left);
        }
        std::cout << node->value << std::endl;
        if (node->right) {
            print(node->right);
        }
    }
};


template <class T>
Tree<T>::Tree()
    : mSize(0)
{
}

template <class T>
Tree<T>::~Tree()
{
}

template <class T>
bool
Tree<T>::add(const T& value)
{
    if (!mRoot) {
        mRoot.reset(new Node(value));
        mSize++;
        return true;
    }

    std::shared_ptr<Node>& current = mRoot;
    while (true) {
        if (value == current->value) {
            // Already in the tree.
            return false;
        }

        if (value < current->value) {
            if (!current->left) {
                current->left.reset(new Node(value));
                current->left->parent = current;
                mSize++;
                return true;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right.reset(new Node(value));
                current->right->parent = current;
                mSize++;
                return true;
            }
            current = current->right;
        }
    }
    return false;
}

#endif // TREE_H
