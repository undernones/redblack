#ifndef TREE_H
#define TREE_H

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
        if (mRoot) print(mRoot);
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
        Node(const T& v) : value(v)
        { }

        ~Node()
        {
            delete left;
            delete right;
        }

        Node* parent;
        Node* left;
        Node* right;
        T value;
    };
    Node* mRoot;
    size_t mSize;

    // TODO: remove
    void print(const Node* node) const
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
    : mRoot(NULL)
    , mSize(0)
{
}

template <class T>
Tree<T>::~Tree()
{
    delete mRoot;
}

template <class T>
bool
Tree<T>::add(const T& value)
{
    if (!mRoot) {
        mRoot = new Node(value);
        mSize++;
        return true;
    }

    Node* current = mRoot;
    while (true) {
        if (value == current->value) {
            // Already in the tree.
            return false;
        }

        if (value < current->value) {
            if (!current->left) {
                current->left = new Node(value);
                current->left->parent = current;
                mSize++;
                return true;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = new Node(value);
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
