# Архитектура библиотеки и экспериментальной среды

## Введение

Данная библиотека предназначена для реализации различных алгоритмов поиска кратчайшего пути с учетом стоимости, таких как алгоритмы Форда-Беллмана, Дейкстры и другие. Экспериментальная среда будет позволять тестировать и сравнивать производительность этих алгоритмов на различных данных.

## Структура библиотеки

### 1. Основные компоненты
- Task - представляет собой граф в виде списка ребер, а также множество вершин, от которых предстоит найти расстояние до других вершин.
- Algorithm - базовый класс для алгоритмов. Потомки должны реализовывать две функции fit (подстраивание алгоритма для работы с графом) и computeDistances (поиск расстояний от выделенной вершины)
- EdgesListGraph и AdjacencyListGraph - представляют собой графы, заданные с помощью списка ребер и списка связности соответственно.

  
### 2. Классы, их поля и формат заголовков алгоритмов

#### 2.0 WeightType
Параметр типа весов ребер в графе. Должен быть одним из: `int`, `long`, `long long`, `float`,  `double`, `long double`


#### 2.1 Algorithm
```c++
template<typename WeightType> 
struct Algorithm {
    virtual void fit(const EdgesListGraph<WeightType> &graph) = 0;
    virtual std::vector<WeightType> computeDistances(size_t startIndex) = 0;
};
```
##### 2.2 AdjacencyListGraph
```c++
template<typename WeightType>
struct AdjacencyListGraph {
    std::vector<std::vector<Edge>> neighbors;

    AdjacencyListGraph(const std::vector<Edge> &edges);
};
```


##### 2.3 EdgesListGraph
```c++
template<typename WeightType>
struct EdgesListGraph {
    std::vector<Edge<WeightType>> edges;

    EdgesListGraph(const std::vector<Edge<WeightType>> &edges) : edges(edges);


    void serialize(std::ostream &stream);

    void deserialize(std::istream &stream);
};

```


## Экспериментальная среда

### 1. Цели экспериментальной среды

- Сравнение производительности различных алгоритмов.
- Анализ сложности в зависимости от структуры графа.

### 2. Структура экспериментальной среды
- Task - представляет собой граф в виде списка ребер, а также множество вершин, от которых предстоит найти расстояние до других вершин. Позволяет запускать вычисления алгоритма с помощью команды run, а также запускать вычисления алгоритма со сбором статистики (используемой памяти и времени работы).

#### 2.1 class Task
```c++
struct Task{

    struct Statistics {
        size_t initializationMemoryUsage;
        std::vector<size_t> computationMemoryUsage;
        uint64_t initializationTime;
        std::vector<uint64_t> computationTime;
    };

    Task(const std::string &filePath);

    Task(const std::vector<size_t> &startIndexes_, const EdgesListGraph<WeightType> &graph_); 


    void toFile(std::string &filePath);

    void fromFile(const std::string &filePath);

    std::vector<std::vector<WeightType>> run(Algorithm<WeightType> &algorithm);

    Statistics estimate(Algorithm<WeightType> &algorithm);

}; 
```


#### 2.2 Параметры эксперимента

- Тип графа (смешанный, ориентированный, взвешенный).
- Размер графа.
- Параметры алгоритмов (например, использование приоритетной очереди).


