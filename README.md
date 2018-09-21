## GDS: Graph Data Structures

#### Union-Find
Implementations:
  1. dsv.h: Disjoint-Set Vector.
    * Vector-based index implementation. This manages storage for objects and uses less memory but is less flexible.
    * Overhead: 3 bits + `sizeof(size_type) * CHAR_BIT` per element, plus `sizeof(void *) * 2 + sizeof(std::vector::size_type)` for the vector.
  2. ufa.h: Union-Find Adapter.
     * Inheritance and free functions. This is more flexible, but requires manual resource management and requires more memory because it works with pointers (8-bytes) instead of integers of a user-specified size.
     * Overhead: `alignof(T) % sizeof(T) + sizeof(void *)` per element.


#### TODO:

1. Topological Sort
2. Kruskal's Algorithm: Topological Sort
3. Additional Graph Algorithms...
