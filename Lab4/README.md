# Лабораторная работа 4
## Задание
1. Разработать программу, реализующую конвейер из двух фильтров.
2. Разработать программу, организующую взаимодействие  
 двух процессов через неименованный программный канал
### Фильтры
1. Фильтр, удаляющий любую последовательность одинаковых символов в строке.
2. Фильтр, изменяющий регистр латинских букв
## Компиляция
Для компилирования `c` кода используется компилятор [clang](https://github.com/llvm-mirror/clang)  
Код предназначен для выполнения в unix системах. Работоспосоность проверена на freeBSD и OS X El Capitan
Скомпилируйте все файлы исходного кода, выполнив следующую последовательность команд:
```
clang case_swap.c -o case_swap.out  
clang substring.c -o substring.out  
clang lr4p1.c -o lr4p1.out  
clang lr4p2.c -o lr4p2.out
```
## Выполнение
Оба варианта программы выполняют одинаковые действия
Для запуска передайте в программу текстовую строку посредством  
конвейера
### Пример
```echo eeRRdsTfdg | ./lr4p1.out```