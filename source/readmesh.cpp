//
//  readmesh.cpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/07.
//

#include "readmesh.hpp"

void ReadMesh::read_obj(std::string const& filename, Mesh& mesh)
{
    std::ifstream ifs(filename);
    if (ifs.fail())
    {
        std::cerr << "Failed to open file." << "\n";
        std::exit(1);
    }

    std::string line;
    while (std::getline(ifs, line))
    {
        std::istringstream string_in(line);
        std::string type;
        string_in >> type;

        if (type == "v")
        {
            Eigen::Vector3d v;
            string_in >> v(0) >> v(1) >> v(2);
            mesh.V.push_back(v);
        }
        else if (type == "f")
        {
            Eigen::Vector3i f;
            string_in >> f(0) >> f(1) >> f(2);
            f -= Eigen::Vector3i{1, 1, 1};
            mesh.F.push_back(f);
        }
    }
}

void ReadMesh::export_obj(std::string name, std::vector<Eigen::Vector3d> const& vert, std::vector<Eigen::Vector3i> const& face)
{
    std::ofstream of;
    name.erase(name.length()-4);
    std::string filename = name + std::to_string(vert.size()) + "_simplified.obj";
    of.open(filename, std::ios::out);
    for(auto& v : vert)
    {
        of << "v " << v(0) << " " << v(1) << " " << v(2) << std::endl;
    }
    for(auto& f : face)
    {
        of << "f " << f(0)+1 << " " << f(1)+1 << " " << f(2)+1 << std::endl;
    }
    of.close();
}
