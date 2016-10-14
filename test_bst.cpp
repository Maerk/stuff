#include <bits/stdc++.h>
#include "bst.hpp"

using namespace std;

template <typename T>
ostream& operator<<(ostream& o, const vector<T>& v)
{
    o << "[";
    for(size_t i = 0; i < v.size(); i++)
    {
        o << v[i];
        if(i != v.size() - 1)
            o << ", ";
    }
    o << "]";
    return o;
}

int main(int argc, char* argv[])
{
    assert(argc == 3);
    mt19937_64 r(atoi(argv[2]));
    vector<pair<int, int>> op;
    int n = atoi(argv[1]);
    for(int i = 0; i < n; i++)
    {
        op.push_back(make_pair(r() % 3, r() % (n / 4)));
    }
    set<int> s;
    vector<bool> s_s;
    bst o;
    vector<bool> s_o;
    for(int i = 0; i < n; i++)
    {
        switch(op[i].first)
        {
            case 0:
                s_s.push_back(s.insert(op[i].second).second);
                break;

            case 1:
                s_s.push_back(s.erase(op[i].second));
                break;

            case 2:
                s_s.push_back(s.count(op[i].second));
                break;
        }
    }
    for(int i = 0; i < n; i++)
    {
        switch(op[i].first)
        {
            case 0:
                cout << "Insert " << op[i].second << endl;
                s_o.push_back(o.insert(op[i].second));
                break;

            case 1:
                cout << "Erase " << op[i].second << endl;
                s_o.push_back(o.erase(op[i].second));
                break;

            case 2:
                cout << "Find " << op[i].second << endl;
                s_o.push_back(o.search(op[i].second));
                break;
        }
    }
    cout << s_s << endl << s_o << endl;
    assert(s_s == s_o);
    return 0;
}
