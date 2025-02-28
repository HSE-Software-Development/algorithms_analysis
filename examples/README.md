## Примеры использования

Каждая отдельная директория является самодостаточным примером имплементирования и использования нашей библиотеки algo_analysis \
Назнание директории с примером является достаточным чтобы понять что он делает ))

### Build

1. **Build examles:**
```sh
    git clone git@github.com:HSE-Software-Development/algorithms_analysis.git
    cd algorithms_analysis
    sh scripts/build_examples.sh
```

2. **Run the examples:**
```sh
    pwd | rev | cut -d '/' -f 1 | rev # must be only "algorithms_analysis" in output
    cd examples/build
    ./*_example
```

### **Warning:**
Так как примеры внутри себя работают со сторонними файлами (файлы с данными графов) то запуск исполняемого файла не из указанного места (как раз проверка путем pwd) приведет к тому что никакой граф не загрузится и они все будут пустыми
