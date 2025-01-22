### Описание алгоритмов и их особенности:

**Задача SSSP** (single-source shortest path problem): Найти расстояния от выделенной вершины s до всех вершин

**Задача APSP** (all pairs shortest path problem): Найти расстояния между всеми парами вершин, матрицу расстояний (SSSP ⊂ APSP)

Работаем с ориентированными графами. Любое решение также будет работать и в неориентированном графе.

|Задача|Название алгоритма|Асимптотика|
| :-: | :-: | :-: |
|SSSP + ацикличность|DFS|O(V + E)|
|SSSP + w<sub>e</sub> =k ∊ N|BFS + queue|O(k(V + E))|
|SSSP + w<sub>e</sub> =k ∊ N<sub>0</sub>|BFS + deque|O(V + E)|
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

# Архитектура библиотеки и экспериментальной среды 

## Введение

Данная библиотека предназначена для реализации различных алгоритмов поиска кратчайшего пути с учетом стоимости, таких как алгоритмы Дейкстры, A и другие. Экспериментальная среда будет позволять тестировать и сравнивать производительность этих алгоритмов на различных данных.

## Структура библиотеки

### 1. Основные компоненты

- Graph: Класс для представления графа.
- GraphAlgorithm: Абстрактный базовый класс для алгоритмов поиска кратчайшего пути.
- DijkstraAlgorithm: Реализация алгоритма Дейкстры.
- AStarAlgorithm: Реализация алгоритма A.
- Аналогично с другими алгоритмами
- Utility: Вспомогательные функции, такие как считывание графа из файла.

### 2. Классы и их ответственность

#### 2.1 Graph
```
class Graph {
public:
    void addEdge(int source, int destination, T weight);
    std::vector<int> getNeighbors(int vertex);
    T getWeight(int source, int destination);
    // Другие необходимые методы
};
```

#### 2.2 GraphAlgorithm
```
class GraphAlgorithm {
public:
    virtual std::vector<int> findShortestPath(Graph& graph, int start, int end) = 0;
};
```

#### 2.3 DijkstraAlgorithm
```
class DijkstraAlgorithm : public GraphAlgorithm {
public:
    std::vector<int> findShortestPath(Graph& graph, int start, int end) override;
};
```

#### 2.4 AStarAlgorithm
```
class AStarAlgorithm : public GraphAlgorithm {
public:
    std::vector<int> findShortestPath(Graph& graph, int start, int end) override;
};
```

#### 2.5 Utility
```
namespace Utility {
    Graph FromFile(const std::string& filename);
    void printPath(const std::vector<int>& path);
    // Другие вспомогательные функции
}
```

## Экспериментальная среда

### 1. Цели экспериментальной среды

- Сравнение производительности различных алгоритмов.
- Анализ сложности в зависимости от структуры графа.
- Визуализация результатов.

### 2. Структура экспериментальной среды

#### 2.1 Main Class
```
class Experiment {
public:
    void runExperiment(Graph& graph);
    void compareAlgorithms(Graph& graph);
    void visualizeResults();
    // Другие методы для проведения экспериментов
};
```

#### 2.2 Параметры эксперимента

- Тип графа (смешанный, ориентированный, взвешенный).
- Размер графа.
- Параметры алгоритмов (например, использование приоритетной очереди).


