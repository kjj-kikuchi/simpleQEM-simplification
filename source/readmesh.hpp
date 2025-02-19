//
//  readmesh.hpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/07.
//

#ifndef readmesh_hpp
#define readmesh_hpp

#include <iostream>
#include <fstream>
#include "mesh.hpp"

namespace ReadMesh
{
void read_obj(std::string const& filename, Mesh& mesh);
void export_obj(std::string name, std::vector<Eigen::Vector3d> const& vert, std::vector<Eigen::Vector3i> const& face);
}

#endif /* readmesh_hpp */
