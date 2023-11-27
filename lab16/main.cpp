template <typename ValueType>
class RedBlackTree
{
protected:
    enum State
    {
        Red,
        Black
    };
    struct RedBlackNode
    {
        T data;
        State state;
        RedBlackNode *left, *right;
        size_t height() const;
        size_t size() const;
    };

public: // constructors, destructors
    RedBlackTree();
    RedBlackTree(const RedBlackTree &srcTree);
    ~RedBlackTree();

public: // methods
    void insert(const ValueType &val);
    void remove(const ValueType &val);
    bool exists(const ValueType &val) const;
    size_t height() const;
    size_t size() const;
    std::vector<ValueType> inOrder() const;
    std::vector<ValueType> levelOrder() const;

protected:
    RedBlackNode *root;
};

template <typename T>
void sortByBST(vector<T> &arr)
{
    RedBlackTree<T> tree;
    for (auto data : arr)
        tree.insert(data);
    arr = tree.inOrder();
};

int main()
{
    return 0;
}
