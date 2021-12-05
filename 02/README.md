# Task 2

Напишите функцию, удаляющую последовательно дублирующиеся символы в строке:

`void RemoveDups(char* str);`

```
// пример использования
char data[] = “AAA BBB AAA”;
RemoveDups(data);
printf(“%s\n”, data); // “A B A”
```
---

# Usage
## Launch all tests
```
cmake . -B build
cmake --build build
cd build
ctest
```

# Notes
