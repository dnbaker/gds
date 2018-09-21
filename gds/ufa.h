#ifndef _UNION_FIND_ADAPTER__
#define _UNION_FIND_ADAPTER__

#include <cstdint>
#include <memory>
#include <iostream>
#include "valptr/valptr.h"

namespace ufa {
/*
 Union-Find Adapter
*/

// Converts any primitive into a struct with the same performance/attributes.
// Also requests uninitialized storage.
template<typename J>
struct Classified {
    J i;
    operator       J&()       {return i;}
    operator const J&() const {return i;}

    Classified<J>() {
        static_assert(std::is_standard_layout<Classified<J>>::value && sizeof(J) == sizeof(Classified<J>), "J does not have standard layout");
#if !NDEBUG
        std::cerr << "Creating with default constructor. Value: " << i << '\n';
#endif
    }
    template<typename T> Classified<J>(T j): i(j) {
#if !NDEBUG
        std::cerr << "Creating with templated constructor. Value: " << i << '\n';
#endif
    }
};

using Double   = Classified<double>;
using Float    = Classified<float>;
using Char     = Classified<char>;
using Short    = Classified<short>;
using Int      = Classified<int>;
using Uint8_t  = Classified<std::uint8_t>;
using Uint16_t = Classified<std::uint16_t>;
using Uint32_t = Classified<std::uint32_t>;
using Uint64_t = Classified<std::uint64_t>;
using Int8_t   = Classified<std::int8_t>;
using Int16_t  = Classified<std::int16_t>;
using Int32_t  = Classified<std::int32_t>;
using Int64_t  = Classified<std::int64_t>;
using Uint64_t = Classified<std::uint64_t>;
using Size_t   = Classified<std::size_t>;
using Voidptr  = Classified<void*>;

// For composition
template<typename Class, typename size_type=std::uint8_t>
struct uf_adapter: public Class {
    vpr::valptr<uf_adapter, std::uint32_t, vpr::DoNothingFunctor<Class>> p_;
    uf_adapter *p() {return p_.get();}
    size_type rank() const {return p_.val();}
    auto setp(uf_adapter *p) {return p_.setp(p);}
    auto setr(size_type r) {return p_.setval(r);}

    template<typename... Args>
    uf_adapter(Args&&... args):
        Class(std::forward<Args>(args)...), p_{0, this} {}
    uf_adapter(const uf_adapter &) = delete;
    uf_adapter &operator=(const uf_adapter &) = delete;
    uf_adapter(uf_adapter &&o) {
        std::memcpy(this, &o, sizeof(*this));
        if(p() == &o)
            setp(this); // Set itself to be its parent
        std::memset(&o, 0, sizeof(o));
    }
    Class &ref()       {return *reinterpret_cast<Class *>(this);}
    const Class &ref() const {return *reinterpret_cast<const Class *>(this);}
};

template<typename T>
T *find(T *node) {
    for(T *next;node->p() != node; next = node->p(), node->setp(next->p()), node = next);
    return node;
}

template<typename T> T *find(T &node) {return find(std::addressof(node));}
template<typename T> const T *find(const T &node) {return find(std::addressof(node));}

template<typename T>
void perform_union(T *a, T *b) {
    if((a = find(a)) == (b = find(b))) return;
    if     (a->rank() < b->rank()) b->setp(a);
    else if(b->rank() < b->rank()) a->setp(b);
    else   b->setp(a), a->setr(a->rank() + 1);
}

template<typename T>
void perform_union(T &a, T &b) {perform_union(std::addressof(a), std::addressof(b));}

} // namespace ufa

#endif // _UNION_FIND_ADAPTER__
