//
//  mesh.cpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/07.
//

#include "mesh.hpp"

void Mesh::make_edge_map()
{
    int edge_idx = 0;
    for (auto& f : F)
    {
        for (int j = 0; j < 3; j++)
        {
            auto edge = std::make_pair(f(j), f((j+1)%3));
            auto edge_opp = std::make_pair(f((j+1)%3), f(j));
            if (! E.contains(edge) && ! E.contains(edge_opp))
            {
                E.emplace(edge, edge_idx);
                edge_idx ++;
            }
        }
    }
}
