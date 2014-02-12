#ifndef TREE_H
#define TREE_H

// TODO:
// * templatize
// * iterators

typedef int T;

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
};

#endif // TREE_H
