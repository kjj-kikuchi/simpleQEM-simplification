# QEMと辺縮約によるメッシュ簡略化

### OS・コンパイラ

- macOS Sequoia 15.1
- g++-13 (Homebrew GCC 13.2.0) 13.2.0

<img src = "snapshot01.png" width = 50%><img src = "snapshot00.png" width = 50%>


### 概略

貪欲な辺縮約メッシュ簡略化法 (**The Simplest QEM Simplification**) の実装．

1. 目標頂点数を入力．
1. メッシュを読み込み，`Mesh::make_edge_map()`で辺リスト`std::map<int, int> E`を作る．
1. `Simpification::compute()`で**SimpleQEM**の計算を行う．

- ヒープは`std::priority_queue`を使用．
- Union FindはUnion by Rankのみを実施．

### 実行結果

- 入力 : `lucy.obj`  
- 出力 : `lucy1000_simplified.obj`
- 簡略化にかかった時間 : 90.2857秒
 ```
Enter target vertex number : 1000       // 入力

Read mesh : 41.6675 sec
Simplification : 90.2857 sec
```
