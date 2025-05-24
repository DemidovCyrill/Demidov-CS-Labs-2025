#ifndef MAP_EXAMPLES_H
#define MAP_EXAMPLES_H

#include <map>
#include <string>

void runMapExamples();
void inventoryMapExample();
void schoolClassesMapExample();

template<typename K, typename V>
void printMap(const std::map<K, V>& m);

#endif // MAP_EXAMPLES_H
