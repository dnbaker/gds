## Union-Find

Implementations:
  1. dsv.h: Disjoint-Set Vector.
    * Vector-based index implementation. This manages storage for objects and uses less memory but is less flexible.
  2. ufa.h: Union-Find Adapter.
     * Inheritance and free functions. This is more flexible, but requires manual resource management and requires more memory because it works with pointers (8-bytes) instead of integers of a user-specified size.
     * Note: the ufa.h approach can be packed to save space, but this requires the ENABLE_PACKED flag to be passed at compilation.
