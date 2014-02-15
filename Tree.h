#ifndef TREE_H
#define TREE_H

#include <boost/iterator/iterator_facade.hpp>

template <class T>
class Tree
{
private:
    struct Node
    {
        Node(const T& v) : value(v)
        { }

        ~Node()
        { }

        Node* parent;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        T value;
    };

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
        if (mRoot) print(mRoot.get());
    }

    // Iterator
    class iterator : public boost::iterator_facade<
         iterator, T, boost::forward_traversal_tag>
    {
    public:
        iterator() : iterator(NULL) {}
        iterator(Node* n) : mNode(n) {}

    private:
        friend class boost::iterator_core_access;

        void increment();
        bool equal(iterator const& other) const;
        T& dereference() const;

        Node* mNode;
    };

private:
    Tree(const Tree& t) = default;
    Tree& operator=(const Tree& t) = default;

    std::unique_ptr<Node> mRoot;
    size_t mSize;

    // TODO: remove
    void print(const Node* node) const
    {
        if (node->left) {
            print(node->left.get());
        }
        std::cout << node->value << std::endl;
        if (node->right) {
            print(node->right.get());
        }
    }
};


// --------------------------------------------------------------------------
// Tree implementation
// --------------------------------------------------------------------------
template <class T>
Tree<T>::Tree()
    : mRoot(nullptr)
    , mSize(0)
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

    Node* current = mRoot.get();
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
            current = current->left.get();
        } else {
            if (!current->right) {
                current->right.reset(new Node(value));
                current->right->parent = current;
                mSize++;
                return true;
            }
            current = current->right.get();
        }
    }
    return false;
}


// --------------------------------------------------------------------------
// Iterator implementation
// --------------------------------------------------------------------------
template <class T>
void
Tree<T>::iterator::increment()
{
    if (!mNode) {
        // TODO: throw an exception
    }

    if (mNode->right) {
        mNode = mNode->right.get();
    }
}

template <class T>
bool
Tree<T>::iterator::equal(iterator const& other) const
{
    if (!mNode || !other.mNode) {
        return false;
    }
    return mNode->value == other.mNode->value;
}

template <class T>
T&
Tree<T>::iterator::dereference() const
{
    return mNode->value;
}

#endif // TREE_H
