//
//  simplification.cpp
//  simpleQEM-simplification
//
//  Created by 菊池祐作 on 2024/11/09.
//

#include <iostream>
#include "simplification.hpp"

void Simplification::compute(Mesh const& m, int const target_v_num)
{
    // 1. 初期化
    Qv.resize(m.V.size(), {});
    for (auto& f : m.F)
    {
        QEM Qf = compute_face_qem(m, f);
        for (int j = 0; j < 3; j++)
        {
            //Qv[f(j)] += (Qf / 3.0);
            Qv[f(j)].A += Qf.A / 3.0;
            Qv[f(j)].b += Qf.b / 3.0;
            Qv[f(j)].c += Qf.c / 3.0;
        }
    }

    UnionFind uf((int)m.V.size());  // singleton clusters

    int t = 0;   // タイムスタンプの初期化

    // 全ての辺をヒープに入れる
    using CostEdgeTime = std::tuple<double, std::pair<int, int>, int>;
    std::priority_queue<CostEdgeTime, std::vector<CostEdgeTime>,std::greater<CostEdgeTime>> pq;
    for (auto& [e, idx] : m.E)
    {
        pq.push( {(Qv[e.first] + Qv[e.second]).min_value(), e, t} );
    }

    // 2. 簡略化ループ
    int v_num = (int)m.V.size();
    while (v_num > target_v_num)
    {
        auto [cost, e_min, time_stamp] = pq.top();
        pq.pop();

        int r0 = uf.find(e_min.first);
        int r1 = uf.find(e_min.second);

        if (r0 == r1) continue; // 辺は縮約済み

        if (time_stamp != t)    // コストが古いので更新
        {
            pq.push( {(Qv[r0] + Qv[r1]).min_value(), e_min, t});
        }
        else                    // 辺を縮約する（クラスタ対をマージする）
        {
            uf.unite(r0, r1);
            Qv[ uf.find(r0) ] = Qv[r0] + Qv[r1];
            t ++;
            v_num --;
        }
    }

    // 3. 簡略化メッシュの抽出
    std::vector<int> coarse_v_idx(m.V.size(), -1);
    int new_v_idx = 0;

    for (int i = 0; i < m.V.size(); i++)
    {
        if (uf.find(i) == i)
        {
            coarse_v_idx[i] = new_v_idx;
            new_v_idx ++;
        }
    }

    for (int i = 0; i < m.V.size(); i++)
    {
        if (uf.find(i) == i)
        {
            coarseV.push_back(Qv[i].minimizer());
        }
    }

    for (auto& f : m.F)
    {
        int v0 = coarse_v_idx[uf.find(f(0))];
        int v1 = coarse_v_idx[uf.find(f(1))];
        int v2 = coarse_v_idx[uf.find(f(2))];

        if (v0 != v1 && v1 != v2 && v2 != v0)
        {
            coarseF.push_back({v0, v1, v2});
        }
    }
}
