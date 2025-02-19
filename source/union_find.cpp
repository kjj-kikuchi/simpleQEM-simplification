//
//  union_find.cpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/09.
//

#include "union_find.hpp"

UnionFind::UnionFind(int n) : parents(n, -1) {}

//UnionFind::UnionFind(int n) : parents(n)
//{
//    for (int i = 0; i < n; i++)
//    {
//        parents[i] = i;
//    }
//}

int UnionFind::find(int idx)
{
    int rank = 0;
    while (parents[idx] >= 0)
    {
        idx = parents[idx];
        rank ++;
    }
    parents[idx] = -(rank + 1);

    return idx;

//    while (parents[idx] != idx)
//    {
//        idx = parents[idx];
//    }
//    return idx;
}

void UnionFind::unite(int idx0, int idx1)
{
    int root0 = find(idx0);
    int root1 = find(idx1);

    if (root0 > root1) parents[root0] = root1;
    else if (root0 < root1) parents[root1] = root0;

//    if (root0 != root1)
//    {
//        parents[root0] = root1;
//    }
}
