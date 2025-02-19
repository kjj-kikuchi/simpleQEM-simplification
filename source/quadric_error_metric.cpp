//
//  quadric_error_metric.cpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/09.
//

#include "quadric_error_metric.hpp"

Eigen::Vector3d QEM::minimizer()
{
    return A.inverse() * b;
}

double QEM::min_value()
{
    Eigen::Vector3d q = minimizer();
    return (q.transpose() * A * q)(0, 0) - 2 * (b.transpose() * q)(0, 0) + c;
}


QEM compute_face_qem(Mesh const& m, Eigen::Vector3i f)
{
    QEM Qf;
    Eigen::Vector3d normal = ((m.V[f(1)] - m.V[f(0)]).cross(m.V[f(2)] - m.V[f(0)])).normalized();
    Eigen::Vector3d p = m.V[f(0)];
    Qf.A = normal * normal.transpose();
    Qf.b = Qf.A * p;
    Qf.c = p.transpose() * Qf.A * p;
    return Qf;
}

QEM operator+(QEM q1, QEM q2)
{
    QEM result;
    result.A = q1.A + q2.A;
    result.b = q1.b + q2.b;
    result.c = q1.c + q2.c;
    return result;
}

//QEM operator+=(QEM q1, QEM q2)
//{
//    q1.A += q2.A;
//    q1.b += q2.b;
//    q1.c += q2.c;
//    return q1;
//}

//QEM operator/(QEM q1, double val)
//{
//    QEM result;
//    result.A = q1.A / val;
//    result.b = q1.b / val;
//    result.c = q1.c / val;
//    return result;
//}
