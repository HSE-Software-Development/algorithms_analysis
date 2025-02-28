# algo_analysis
![Build Status](https://github.com/HSE-Software-Development/algorithms_analysis/actions/workflows/ci.yml/badge.svg)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

Данная библиотека предназначена для реализации различных алгоритмов поиска кратчайшего пути с учетом стоимости, таких как алгоритмы Форда-Беллмана, Дейкстры и другие. Экспериментальная среда будет позволять тестировать и сравнивать производительность этих алгоритмов на различных данных.

## Алгоритмы

**Задача SSSP** (single-source shortest path problem): Найти расстояния от выделенной вершины s до всех вершин

**Задача APSP** (all pairs shortest path problem): Найти расстояния между всеми парами вершин, матрицу расстояний (SSSP ⊂ APSP)

1. DFS (SSSP)
2. BFS + queue (SSSP)
3. BFS + deque (SSSP)
4. Dijkstra (SSSP)
5. Dijkstra + fib-heap (SSSP)
6. A\* (SSSP)
7. Ford-Bellman (SSSP)
8. Floid (APSP)

Подробнее в [документации по алгоритмам](docs/algorithms.md)

## Build

### For Unix(Linux/MacOs)

1. **Build the project with tests and micro benchmarking:**
```sh
    git clone git@github.com:HSE-Software-Development/algorithms_analysis.git
    cd algorithms_analysis
    sh scripts/build_algo_analysis.sh
```
Если вы не хотите запускать тесты автоматически после сборки библиотеки то:
```sh
    sh scripts/build_algo_analysis.sh 0
```

2. **Run the tests:**
```sh
    cd cpp/build
    ./tests/algo_analysis_tests
```


### For Windows (MSVC)

До слез

## Installation and contributing
[Примеры использования тут](examples/README.md)


Также у вас есть возможность дополнять нашу библиотеку алгоритмов путем реализации наследников класса `Algorithm` ([см. архитектурную документацию](docs/architecture.md)).

## Using the test environment

Тестовая среда позволяет замерять время и память при инициализации и работе алгоритма. Для этого `Task` предоставляет метод `estimate` ([см. примеры](examples/README.md)). 

Запуск бенчмарков.
```sh
    cd cpp/build/micro_benchmarks
    ./DFSBenchmark # or another algorithm
```


## License

This project is licensed under the [MIT license](LICENSE)