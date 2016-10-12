#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class max_heap
{
private:
    vector<int> heap;
    void balanceUp(int n)
    {
        if(heap[n] > heap[getParent(n)])
        {
            swap(heap[n], heap[getParent(n)]);
            balanceUp(getParent(n));
        }
        return;
    }
    void balanceDown(int n)
    {
        if(getChildLeft(n) < 0)
            return;
        if(heap[n] < heap[getChildLeft(n)])
        {
            swap(heap[n], heap[getChildLeft(n)]);
            balanceDown(getChildLeft(n));
        }
        if(getChildRight(n) < 0)
            return;
        if(heap[n] < heap[getChildRight(n)])
        {
            swap(heap[n], heap[getChildRight(n)]);
            balanceDown(getChildRight(n));
        }
    }
    int getParent(int i)
    {
        if(!i)
            return 0;
        return (i-1)/2;
    }
    int getChildLeft(int i)
    {
        int child = 2*i+1;
        if(child >= heap.size())
            return -1;
        else
            return child;
    }
    int getChildRight(int i)
    {
        int child = 2*i+2;
        if(child >= heap.size())
            return -1;
        else
            return child;
    }
public:
    void insert(int n)
    {
        heap.push_back(n);
        balanceUp(heap.size()-1);
    }
    int extract()
    {
        int ret = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        balanceDown(0);
        return ret;
    }
    void remove()
    {
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        balanceDown(0);
    }
    int elements()
    {
        return heap.size();
    }
};
