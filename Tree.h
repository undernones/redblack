#ifndef TREE_H
#define TREE_H

#include <boost/iterator/iterator_facade.hpp>

template <class T>
class Tree
{

private:
    struct Node;

public:
    Tree();
    ~Tree();

    void clear();
    bool isEmpty() const { return mSize == 0; }

    bool add(const T& value);
    bool remove(const T& value);
    bool contains(const T& value) const;

    size_t size() const { return mSize; }

    // Refer to:
    // http://www.boost.org/doc/libs/1_55_0/libs/iterator/doc/iterator_facade.html
    class iterator : public boost::iterator_facade<
         iterator, T, boost::forward_traversal_tag>
    {
    public:
        iterator() : iterator(nullptr) {}
        explicit iterator(Node* n) : mNode(n) {}

    private:
        friend class boost::iterator_core_access;

        void increment();
        bool equal(iterator const& other) const;
        T& dereference() const;

        Node* mNode;
    };

    iterator begin();
    iterator end();

private:
    Tree(const Tree& t) = default;
    Tree& operator=(const Tree& t) = default;

    struct Node
    {
        Node(const T& v);
        ~Node();

        // Returns the left-most node of the tree rooted at this node.
        Node* leftMostNode();

        // Returns the left-most ancestor of this node. It is possible that this
        // node is its own left-most ancestor.
        Node* leftMostAncestor();

        Node* parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        T value;
    };

    // This is a fake root node that is always present, the value of which is
    // not considered to be in the set. All values in the set are contained
    // within the fake root's left sub-tree.
    Node mRoot;
    size_t mSize;
};


// --------------------------------------------------------------------------
// Tree implementation
// --------------------------------------------------------------------------
template <class T>
Tree<T>::Tree()
    : mRoot(T())
    , mSize(0)
{
}

template <class T>
Tree<T>::~Tree()
{
}

template <class T>
void
Tree<T>::clear()
{
    mRoot.left.reset();
    mSize = 0;
}

template <class T>
bool
Tree<T>::add(const T& value)
{
    if (!mRoot.left) {
        mRoot.left.reset(new Node(value));
        mSize++;
        return true;
    }

    Node* current = mRoot.left.get();
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

template <class T>
bool
Tree<T>::remove(const T& value)
{
    // Refer to:
    // http://webdocs.cs.ualberta.ca/~holte/T26/del-from-bst.html

    Node* current = mRoot.left.get();
    while (current) {
        if (value == current->value) {
            // Found it! Proceed to remove.
            if (!current->left && !current->right) {
                // No sub-tree. Set parent's left or right child to null.
                if (current == current->parent->left.get()) {
                    current->parent->left.reset();
                } else {
                    current->parent->right.reset();
                }
            } else if (!current->left && current->right) {
                // Only right sub-tree present.
                if (current == current->parent->left.get()) {
                    current->parent->left = current->right;
                } else {
                    current->parent->right = current->right;
                }
            } else if (current->left && !current->right) {
                // Only left sub-tree present.
                if (current == current->parent->left.get()) {
                    current->parent->left = current->left;
                } else {
                    current->parent->right = current->left;
                }
            } else {
                // Both sub-trees present. Replace the current node's value with
                // the smallest value in the right sub-tree, then delete that
                // node containing the smallest value.
                Node* smallest = current->right->leftMostNode();
                current->value = smallest->value;
                smallest->parent->left = smallest->right;
            }

            mSize--;
            return true;
        }
    }
    return false;
}

template <class T>
bool
Tree<T>::contains(const T& value) const
{
    Node* current = mRoot.left.get();
    while (current) {
        if (value == current->value) {
            return true;
        }

        if (value < current->value) {
            current = current->left.get();
        } else {
            current = current->right.get();
        }
    }
    return false;
}

template <class T>
typename Tree<T>::iterator
Tree<T>::begin()
{
    Node* n = mRoot.leftMostNode();
    return iterator(n);
}

template <class T>
typename Tree<T>::iterator
Tree<T>::end()
{
    return iterator();
}


// --------------------------------------------------------------------------
// Node implementation
// --------------------------------------------------------------------------
template <class T>
Tree<T>::Node::Node(const T& v)
    : value(v)
{
}

template <class T>
Tree<T>::Node::~Node()
{
}

template <class T>
typename Tree<T>::Node*
Tree<T>::Node::leftMostNode()
{
    Node* current = this;
    while (current->left) {
        current = current->left.get();
    }
    return current;
}

template <class T>
typename Tree<T>::Node*
Tree<T>::Node::leftMostAncestor()
{
    Node* current = this;
    while (current->parent && current->parent->right.get() == current) {
        current = current->parent;
    }
    return current;
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
        mNode = mNode->right->leftMostNode();
        return;
    }

    if (mNode->parent && mNode->parent->left.get() == mNode) {
        // The current node is the left child of its parent.
        mNode = mNode->parent;
        return;
    }

    mNode = mNode->leftMostAncestor()->parent;
}

template <class T>
bool
Tree<T>::iterator::equal(iterator const& other) const
{
    if (mNode && other.mNode) {
        return mNode->value == other.mNode->value;
    }
    return mNode == other.mNode;
}

template <class T>
T&
Tree<T>::iterator::dereference() const
{
    return mNode->value;
}

#endif // TREE_H
