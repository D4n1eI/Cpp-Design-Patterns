#include <iostream>
#include <string>
#include <coroutine>

template <typename T>
struct BinaryTree;

template <typename T>
struct Node
{
    T value;
    Node<T> *left{nullptr};
    Node<T> *right{nullptr};
    Node<T> *parent{nullptr};
    BinaryTree<T> *tree{nullptr};

    explicit Node(const T &value)
        : value(value)
    {
    }

    Node(const T &value, Node<T> *left, Node<T> *right)
        : value(value), left(left), right(right)
    {
        if (this->left)
            this->left->parent = this;

        if (this->right)
            this->right->parent = this;
    }

    void set_tree(BinaryTree<T> *t)
    {
        tree = t;

        if (left)
            left->set_tree(t);

        if (right)
            right->set_tree(t);
    }

    ~Node()
    {
        delete left;
        delete right;
    }
};

template <typename T>
struct BinaryTree
{
    Node<T> *root{nullptr};

    explicit BinaryTree(Node<T> *root)
        : root(root)
    {
        if (this->root)
            this->root->set_tree(this);
    }

    ~BinaryTree()
    {
        delete root;
    }

    template <typename U>
    struct PreOrderIterator
    {
        Node<U> *current;

        explicit PreOrderIterator(Node<U> *current)
            : current(current)
        {
        }

        bool operator!=(const PreOrderIterator<U> &other) const
        {
            return current != other.current;
        }

        PreOrderIterator<U> &operator++()
        {
            if (!current)
                return *this;

            if (current->right)
            {
                current = current->right;

                while (current->left)
                    current = current->left;
            }
            else
            {
                Node<U> *p = current->parent;

                while (p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }

                current = p;
            }

            return *this;
        }

        Node<U> &operator*() const
        {
            return *current;
        }

        Node<U> *operator->() const
        {
            return current;
        }
    };

    using iterator = PreOrderIterator<T>;

    iterator begin()
    {
        Node<T> *n = root;

        if (n)
        {
            while (n->left)
                n = n->left;
        }

        return iterator(n);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

   
};

int main()
{
    BinaryTree<std::string> family(
        new Node<std::string>(
            "me",
            new Node<std::string>(
                "mother",
                new Node<std::string>("mother's mother"),
                new Node<std::string>("mother's father")),
            new Node<std::string>("father")));

    for (auto it = family.begin(); it != family.end(); ++it)
    {
        std::cout << (*it).value << '\n';
    }

    return 0;
}