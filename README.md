# Документация по библиотеке графовых алгоритмов

1. [Класс GeneralGraph](#класс-generalgraph)
2. [Формат графа](#формат-графа)
3. [Алгоритмы](#алгоритмы)
   - [FordBellman](#fordbellman)
   - [DFS](#dfs)
   - [BSF](#bfs)
   - [Dijkstra](#dijkstra)

## Архитектура

### Пространство имен algorithms
В пространстве имен algorithms находятся шаблонные методы для выполнения графовых алгоритмов. Каждый алгоритм принимает на вход объект класса GeneralGraph, и опциональные переменные.

### Класс GeneralGraph
Класс GeneralGraph является шаблонным и имеет две переменные типа:
- TVertex — тип данных для вершин
- TEdge — тип данных для ребер

#### Конструкторы
Класс GeneralGraph предлагает два конструктора для инициализации графа:
1. GeneralGraph(const std::string& filePath)  
   Конструктор, принимающий путь до файла, в котором хранится граф в необходимом формате.

2. GeneralGraph(std::istream& inputStream)  
   Конструктор, принимающий поток ввода для задания графа в необходимом формате.

## Примеры использования

### Пример создания графа из файла
```
#include "GeneralGraph.h"
#include "algorithms.h"

int main() {
    GeneralGraph<int, double> graph("path/to/graph.txt");
    algorithms::someGraphAlgorithm(graph, ...);
    return 0;
}
```


## Формат графа
Для корректного создания графа, необходимо следующее оформление данных:
- В первом ряду указывается два числа: n - количество вершин в графе и число 0 или 1(При отсутствии веса в вершинах или наличии соответственно)
- В случае, если был выставлен флаг 1:
    - В каждом из следующих n строчек указывается вес внутри вершины с соответствующим номером
- В каждом следующем ряду указывается новое ребро:
  - Формат записи:
    vertex1 vertex2 weight \
  где:
    - vertex1 и vertex2 — идентификаторы вершин, соединенных ребром.
    - weight — вес ребра (должен быть типом данных TEdge).

### Пример формата графа
```
4 1
1
2
3
4
0 1 10
1 2 20
2 3 30
3 0 40
0 2 50
1 3 60
```

В данном примере указан полный граф на 4-ех вершинах с указанными весами на ребрах и в вершинах.

## Алгоритмы

### FordBellman
#### Описание
Функция реализует алгоритм Форда - Беллмана для поиска кратчайших путей от одной начальной вершины до всех остальных в графе, в том числе с учетом отрицательных весов.

#### Шаблон
```c++
template <typename T, typename K>
void FordBellman(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances);
```
#### Параметры
- startIndex — начальный индекс для алгоритма (указатель на начальную вершину для вычисления кратчайших путей).
- graph — указатель на объект GeneralGraph, который представляет граф.
- distances — ссылка на вектор, который будет заполнен наименьшими расстояниями от начальной вершины до всех остальных.

#### Пример использования
```c++
#include "GeneralGraph.h"
#include "algorithms.h"

int main() {
    GeneralGraph<int, double> graph("path/to/graph_with_negatives.txt");
    std::vector<double> distances(graph.vertexCount(), std::numeric_limits<double>::infinity());
    
    size_t startIndex = 0; // Начальная вершина
    algorithms::FordBellman(startIndex, &graph, distances);
    
    // Теперь вектор distances содержит кратчайшие расстояния, даже с учетом отрицательных весов
    return 0;
}
```

### DFS
#### Функция DFS

#### Описание
Функция выполняет поиск в глубину (DFS) в графе и может использоваться для вычисления кратчайших расстояний в графе без отрицательных весов.

#### Шаблон
```c++
template <typename T, typename K>
void DFS(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances);
```

#### Параметры
- startIndex — начальный индекс для поиска (указатель на начальную вершину).
- graph — указатель на объект GeneralGraph, содержащий граф, по которому будет выполнен поиск.
- distances — ссылка на вектор, который будет заполнен расстояниями от начальной вершины до всех остальных.

#### Пример использования
```c++
#include "GeneralGraph.h"
#include "algorithms.h"

int main() {
    GeneralGraph<int, double> graph("path/to/graph.txt");
    std::vector<double> distances(graph.vertexCount(), std::numeric_limits<double>::infinity());
    
    size_t startIndex = 0; // Начальная вершина
    algorithms::DFS(startIndex, &graph, distances);
    
    // Теперь вектор distances содержит расстояния
    return 0;
}
```
### BFS
#### Описание
Функция реализует алгоритм поиска в ширину (BFS) для нахождения кратчайших путей от одной стартовой вершины до всех остальных. Алгоритм работает для графов без отрицательных весов и подходит для неориентированных и ориентированных графов.

#### Шаблон
```c++
template <typename T, typename K>
void BFS(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances);
```

#### Параметры
- startIndex — начальный индекс для поиска, указывающий на стартовую вершину.
- graph — указатель на объект GeneralGraph, представляющий сам граф.
- distances — ссылка на вектор, который будет заполнен кратчайшими расстояниями от начальной вершины до всех остальных.

#### Пример использования
```c++
#include "GeneralGraph.h"
#include "algorithms.h"

int main() {
    GeneralGraph<int, double> graph("path/to/graph.txt");
    std::vector<double> distances(graph.vertexCount(), std::numeric_limits<double>::infinity());
    
    size_t startIndex = 0; // Начальная вершина
    algorithms::BFS(startIndex, &graph, distances);
    
    // distances теперь содержит кратчайшие расстояния от startIndex до всех других вершин
    return 0;
}
```

### Dijkstra
#### Описание
Функция реализует алгоритм Дейкстры для решения задачи нахождения кратчайшего пути от одной стартовой вершины до всех остальных вершин в графе с неотрицательными весами.

#### Шаблон
```c++
template <typename T, typename K>
void Dijkstra(size_t startIndex, GeneralGraph<T, K> *graph, std::vector<T> &distances);
```

#### Параметры
- startIndex — начальный индекс для поиска кратчайших путей, указывающий на стартовую вершину в графе.
- graph — указатель на объект GeneralGraph, представляющий граф, по которому будет выполняться поиск кратчайших путей.
- distances — ссылка на вектор, который будет заполнен расстояниями от начальной вершины до всех остальных. Вектор должен быть инициализирован (например, значением "бесконечность" для всех вершин, кроме стартовой).

#### Пример использования
```c++
#include "GeneralGraph.h"
#include "algorithms.h"
#include <limits>
#include <iostream>

int main() {
    GeneralGraph<int, double> graph("path/to/graph.txt");
    std::vector<double> distances(graph.vertexCount(), std::numeric_limits<double>::infinity());
    
    size_t startIndex = 0; // Начальная вершина
    distances[startIndex] = 0; // Расстояние до самой себя - 0
    algorithms::Dijkstra(startIndex, &graph, distances);
    
    // Вывод расстояний от стартовой вершины до всех остальных
    for (size_t i = 0; i < distances.size(); ++i) {
        if (distances[i] == std::numeric_limits<double>::infinity()) {
            std::cout << "Расстояние до вершины " << i << ": бесконечность" << std::endl;
        } else {
            std::cout << "Расстояние до вершины " << i << ": " << distances[i] << std::endl;
        }
    }
    
    return 0;
}
```