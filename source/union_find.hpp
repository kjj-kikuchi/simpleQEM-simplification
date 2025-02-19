//
//  union_find.hpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/09.
//

#ifndef union_find_hpp
#define union_find_hpp

#include <vector>

struct UnionFind
{
    std::vector<int> parents;

    UnionFind(int n);
    int find(int x);
    void unite(int x, int y);
};

#endif /* union_find_hpp */
