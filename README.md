### Описание алгоритмов и их особенности:

**Задача SSSP** (single-source shortest path problem): Найти расстояния от выделенной вершины s до всех вершин

**Задача APSP** (all pairs shortest path problem): Найти расстояния между всеми парами вершин, матрицу расстояний (SSSP ⊂ APSP)

Работаем с ориентированными графами. Любое решение также будет работать и в неориентированном графе.

|Задача|Название алгоритма|Асимптотика|
| :-: | :-: | :-: |
|SSSP + ацикличность|DFS|O(V + E)|
|SSSP + w<sub>e</sub> =k ∊ N|BFS + queue|O(k(V + E))|
|SSSP + w<sub>e</sub> =k ∊ N0|BFS + deque|O(V + E)|
|SSSP + w<sub>e</sub> ≥ 0|Dijkstra|O(V<sup>2</sup> + E)|
|SSSP + w<sub>e</sub> ≥ 0|Dijkstra + fib-heap|O(VlogV + E)|
|SSSP + w<sub>e</sub> ≥ 0|A\*|O(V<sup>2</sup> + E)|
|SSSP + w<sub>e</sub> ∈ R|Ford-Bellman|O(VE)|
|APSP + w<sub>e</sub> ∈ R|Floid|O(V<sup>3</sup>)|


**1. DFS**

DFS — это алгоритм обхода или поиска в графе, который начинает с начальной вершины и идет "вглубь" по каждому направлению до тех пор, пока не достигнет вершины без непосещенных соседей, после чего он откатывается назад и пробует следующую непосещённую вершину.

**2. BFS + queue**

BFS — это алгоритм обхода графа, который начинает с начальной вершины и посещает всех её соседей, прежде чем двигаться к вершинам следующего уровня, т.е. "вширь" (соседей у каждой вершине обрабатываем в порядке очереди).

**3. BFS + deque**

Заменим очередь на дек. Разрешим вершине добавляться в дек несколько раз: добавлять будем каждый раз, когда расстояние уменьшается.

**4. Dijkstra**

Алгоритм Дейкстры находит кратчайшие пути от стартовой вершины до всех других вершин в графе с неотрицательными весами рёбер. Он работает за счёт выбора вершины с минимальным текущим расстоянием, обновления расстояний до её соседей, и повторения этого процесса пока все вершины не будут обработаны.

**5. Dijkstra + fib-heap**

Выбор вершины на каждом шаге оптимизирован с помощью фибоначчиевой кучи.

**6. A\***

Алгоритм A\* ищет кратчайший путь в графе, используя комбинацию фактической стоимости пути и эвристической оценки оставшегося расстояния до цели. Это позволяет ему эффективно находить оптимальные пути, особенно если эвристика точна и допустима.

**7. Bellman & Ford**

Алгоритм Форда-Беллмана находит кратчайшие пути в графах, допускающих отрицательные веса рёбер. Он работает итеративно, обновляя расстояния, и обнаруживает отрицательные циклы. Хотя он медленнее Дейкстры, он позволяет работать с отрицательными весами.

**8. Floid**

Алгоритм Флойда – простое решение APSP с помощью динамического программирования, позволяет решать данную задачу для графов с целыми весами на ребрах
S