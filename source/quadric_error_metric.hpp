//
//  quadric_error_metric.hpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/09.
//

#ifndef quadric_error_metric_hpp
#define quadric_error_metric_hpp

#include <Eigen/Geometry>
#include <Eigen/LU>
#include "mesh.hpp"

struct QEM
{
    Eigen::Matrix3d A;
    Eigen::Vector3d b;
    double c;

    Eigen::Vector3d minimizer();

    double min_value();
};

QEM compute_face_qem(Mesh const& m, Eigen::Vector3i f);

QEM operator+(QEM q1, QEM q2);

QEM operator+=(QEM q1, QEM q2);

QEM operator/(QEM q1, double val);

#endif /* quadric_error_metric_hpp */
