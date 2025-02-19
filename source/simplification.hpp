//
//  simplification.hpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/09.
//

#ifndef simplification_hpp
#define simplification_hpp

#include <queue>
#include "mesh.hpp"
#include "quadric_error_metric.hpp"
#include "union_find.hpp"

class Simplification
{
    std::vector<QEM> Qv;
public:
    std::vector<Eigen::Vector3d> coarseV;
    std::vector<Eigen::Vector3i> coarseF;

    void compute(Mesh const& m, int const target_v_num);
};

#endif /* simplification_hpp */
