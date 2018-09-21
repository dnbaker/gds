#include <cstdio>
#include <cstring>
#include <iostream>
#include "gds/dsv.h"
#include "gds/ufa.h"

using namespace fds;
using namespace ufa;
using std::cerr;

struct dummy {
    int i;
    char s[7] = "hello";
    dummy(int i, const char *p): i{i} {
        if(p) std::strcpy(s, p);
        else s[0] = '\0';
    }
    dummy(): dummy(-1, nullptr) {}
};

int main() {
    DisjointSetVector<int> uf;
    uf.emplace(42);
    uf.emplace(17);
    uf.emplace(24);
    uf.perform_union(2, 1);
    for(auto i(0u); i < sizeof(uf.n_) / sizeof(uf.n_[0]); ++i)
        cerr << "index  " << i << ", value: " << uf.n_[i] << '\n';
    using ufi = uf_adapter<dummy>;
    ufi i1;
    ufi i2;
    find(i1);
    find(i2);
    std::fprintf(stderr, "Before union: rank 1: %i. Rank 2: %i\n", i1.rank(), i2.rank());
    perform_union(i1, i2);
    std::fprintf(stderr, "Rank 1: %i. Rank 2: %i\n", i1.rank(), i2.rank());
    uf_adapter<dummy> d1{-1, "hello"}, d2{1336, "world"};
    uf_adapter<Int> i01{-1}, i02{4};
    Int I1{-4}, I2{-1};
    cerr << "Int value from -1: " << (int)I2 << '\n';
    I2 += 4;
    cerr << "Int value from -1 with 4 added: " << (int)I2 << '\n';
}
