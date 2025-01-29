# Архитектура библиотеки и экспериментальной среды

## Введение

Данная библиотека предназначена для реализации различных алгоритмов поиска кратчайшего пути с учетом стоимости, таких как алгоритмы Форда-Беллмана, Дейкстры и другие. Экспериментальная среда будет позволять тестировать и сравнивать производительность этих алгоритмов на различных данных.

## Структура библиотеки

### 1. Основные компоненты

- GeneralGraph: Класс для представления графа.
  - GeneralNode: Класс для представления вершин.
  - GeneralEdge: Класс для представления ребер.
- algorithms: namespace с функциями различных алгоритмов
  - FordBellman: Реализация алгоритма Форда-Беллмана.
  
### 2. Классы, их поля и формат заголовков алгоритмов

#### 2.1 GeneralGraph
```
template<typename T, typename K>
class GeneralGraph {
private:
    std::vector <std::unique_ptr<GeneralEdge<T>>>
            edges; // All edges of the graph
    std::vector <std::unique_ptr<GeneralNode<K>>>
            nodes; // All nodes of the graph

```
##### 2.1.1 GeneralNode
```
template<typename T>
class GeneralNode {
private:
    std::vector <std::pair<GeneralNode<T> *, size_t>>
            neighbors; // Node neighbors vector
    T value; // Value of the node
    size_t index; // Index of the node
    size_t capacity; //
```
##### 2.1.2 GeneralEdge
```
template<typename T>
class GeneralEdge {
private:
    size_t start, end; // Edge's ends
    T weight;          // Edge's weight

```

#### 2.2 
```
namespace algorithms {
/// @brief Ford Bellman algorithm for SSSP
/// @tparam T type for graph's weights and distances
/// @param startIndex start index for the SSSP
/// @param g graph itself
/// @param distances vector of distances from start point to all others
template <typename T>
void FordBellman(size_t startIndex, GeneralGraph<T, size_t> *g,
                 std::vector<T> &distances);
}
```


## Экспериментальная среда

### 1. Цели экспериментальной среды

- Сравнение производительности различных алгоритмов.
- Анализ сложности в зависимости от структуры графа.

### 2. Структура экспериментальной среды
- Task: Виртуальный класс задачи
  - SSSP: Наследник Task. Окружение тестирования задачи SSSP на разных алгоритмах
  - APSP: Наследник Task. Окружение тестирования задачи APSP

#### 2.1 class Task
```
class Task {
  public:
    /// @brief Run task method
    virtual void run(int logLevel) = 0;

    /// @brief Class destructor
    virtual ~Task() = default;
}; // End of class 'Task'
```

##### 2.1.1 class SSSP
```
template <typename T, typename K> class SSSP : public Task {
public:
    SSSP(const std::vector<GeneralGraph<T, K> *> &graphs_, const std::vector<size_t> &startNodeIndexes_,
         const std::function<void(size_t, GeneralGraph<T, K> *, std::vector<T> &)> &algorithm_);
         
    void run(int logLevel = 1) override;     
}
```

##### 2.1.2 class APSP
```
template <typename T, typename K> class APSP : public Task {
public:
    APSP(const std::vector<GeneralGraph<T, K> *> &graphs_,
         std::function<void(const GeneralGraph<T, K> *, std::vector<std::vector<T>> &)> algorithm_) {
         
    void run(int logLevel = 1) override;     
}
```

#### 2.2 Параметры эксперимента

- Тип графа (смешанный, ориентированный, взвешенный).
- Размер графа.
- Параметры алгоритмов (например, использование приоритетной очереди).

