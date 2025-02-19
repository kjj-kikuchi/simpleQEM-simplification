//
//  mesh.hpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/07.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <vector>
#include <map>
#include <Eigen/Core>

struct Mesh
{
    std::vector<Eigen::Vector3d> V;
    std::vector<Eigen::Vector3i> F;
    std::map<std::pair<int, int>, int> E;

    void make_edge_map();
};

#endif /* mesh_hpp */
