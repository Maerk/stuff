#include <utility>
using namespace std;
class node
{
friend class bst;
private:
    int key;
    node* left;
    node* right;
    node(int val)
    {
        key = val;
        left = nullptr;
        right = nullptr;
    }
    ~node()
    {
        left = nullptr;
        right = nullptr;
    }
};

class bst
{
private:
    node* root;
    pair<node*,node*> searchNode(int key)
    {
        pair<node*, node*> a;
        a.first = root;
        a.second = nullptr;
        while(true)
        {
            if(a.first == nullptr || a.first->key == key)
                return a;
            else
            {
                a.second = a.first;
                if(a.first->key > key)
                    a.first = a.first->left;
                else
                    a.first = a.first->right;
            }
        }
    }
    void deleteNode(pair<node*,node*> a) //delete first, second is parent
    {
        if(a.first->left == nullptr && a.first->right == nullptr)
        {
            if(a.first != root)
            {
                if(a.second->left == a.first)
                    a.second->left = nullptr;
                else
                    a.second->right = nullptr;
            }
            else
                root = nullptr;
            return;
        }
        if(a.first->left == nullptr)
        {
            node* tmp = a.first;
            a.second = a.first; //parent
            a.first = a.first->right; //down of one right
            while(true)//down left
            {
                if(a.first->left == nullptr)
                {
                    tmp->key = a.first->key;
                    deleteNode(a);
                    break;
                }
                else
                {
                    a.second = a.first;
                    a.first = a.first->left;
                }
            }
        }
        else
        {
            node* tmp = a.first;
            a.second = a.first; //parent
            a.first = a.first->left; //down of one left
            while(true)//down right
            {
                if(a.first->right == nullptr)
                {
                    tmp->key = a.first->key;
                    deleteNode(a);
                    break;
                }
                else
                {
                    a.second = a.first;
                    a.first = a.first->right;
                }
            }
        }
        return;
    }
    void deleteFrom(pair<node*, node*> r)
    {
        if(!(r.first->left == nullptr && r.first->right == nullptr))
        {
            r.second = r.first;
            if(r.first->left != nullptr)
            {
                r.first = r.first->left;
                deleteFrom(r);
            }
            if(r.first->right != nullptr)
            {
                r.first = r.first->right;
                deleteFrom(r);
            }
        }
        if(r.first != root)
        {
            if(r.second->left == r.first)
                r.second->left = nullptr;
            else
                r.second->right = nullptr;
        }
        else
            root = nullptr;
        return;
    }
public:
    bst()
    {
        root = nullptr;
    }
    ~bst()
    {
        pair<node*, node*> r;
        r.first = root;
        r.second = nullptr;
        deleteFrom(r);
    }
    bool insert(int key)
    {
        node* in = new node(key);
        if(root == nullptr)
        {
            root = in;
            return true;
        }
        node* x = root;
        while(true)
        {
            if(key == x->key)
                return false;
            if(key < x->key)
            {
                if(x->left == nullptr)
                {
                    x->left = in;
                    break;
                }
                x = x->left;
            }
            else
            {
                if(x->right == nullptr)
                {
                    x->right = in;
                    break;
                }
                x = x->right;
            }
        }
        return true;
    }
    bool erase(int key)
    {
        pair<node*,node*> a = searchNode(key);
        if(a.first != nullptr)
        {
            deleteNode(a);
            return true;
        }
        else
            return false;
    }
    bool search(int key)
    {
        return (searchNode(key).first != nullptr) ? true : false;
    }
};
