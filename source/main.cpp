//
//  main.cpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/07.
//

#include <iostream>
#include <chrono>

#include "mesh.hpp"
#include "simplification.hpp"
#include "readmesh.hpp"


int main(int argc, const char * argv[])
{
    // Enter target vertex number............................
    double target_v_num;
    std::cout << "Enter target vertex number : ";
    std::cin >> target_v_num;


    // Read mesh file........................................
    auto start_readmesh = std::chrono::system_clock::now();

    std::string filename;
    if (argc != 2)
    {
        std::cout << "wrong command line argument" << std::endl;
        std::exit(1);
    }
    filename = std::string(argv[1]);

    Mesh mesh;
    ReadMesh::read_obj(filename, mesh);
    mesh.make_edge_map();
    std::cout << "e.num : " << mesh.E.size() << std::endl;

    auto end_readmesh = std::chrono::system_clock::now();


    // Simplification........................................
    auto start_s = std::chrono::system_clock::now();

    Simplification simp;
    simp.compute(mesh, target_v_num);

    auto end_s = std::chrono::system_clock::now();


    // Export................................................
    ReadMesh::export_obj(filename, simp.coarseV, simp.coarseF);

    using namespace std::chrono_literals;
    std::cerr << "Read mesh : " << (end_readmesh - start_readmesh) / 1.0s << " sec\n";
    std::cout << "Simplification : " << (end_s - start_s) / 1.0s << " sec\n";

    return 0;
}
