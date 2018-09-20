#pragma once
#include <array>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <type_traits>

namespace graph {
using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::size_t;

struct Empty {};

template<typename T>
class GraphNode {
    // Let T usually be a Semiring
    T val_;
public:
    template<typename... Args>
    GraphNode(Args &&... args): val_(std::forward<Args>(args)...) {
    }
    T &val() {return val_;}
    const T &val() const {return val_;}
    // This lets me add extra features later
};

template<typename T, typename IndexType=uint32_t>
class Edge {
    // Let T usually be a Semiring
    T val_;
    std::array<IndexType, 2> nodes_;
public:
    template<typename... Args>
    Edge(Args &&... args): T(std::forward<Args>(args)...) {}
    T &val() {return val_;}
    const T &val() const {return val_;}
    // This lets me add extra features later
};


template<typename NodeT, typename EdgeT, bool is_directed_, typename IndexType=uint32_t>
class Graph {
    // Note: This is incomplete!
    std::vector<GraphNode<NodeT>> node_values_;
    std::vector<Edge<EdgeT, IndexType>> adjacency_lists_;
    IndexType nedges_;
    // Think about templating by container later.
public:
    using node_type = GraphNode<NodeT>;
    using edge_type = Edge<EdgeT, IndexType>;
    using size_type = IndexType;
    // Think about using things like memory allocation policy downstream
    static constexpr bool has_node_labels() {return std::is_empty_v<NodeT>;}
    static constexpr bool has_edge_labels() {return std::is_empty_v<EdgeT>;}
    static constexpr bool is_directed() {return is_directed_;}
    size_t node_id(const node_type *nd) {
        return nd - &node_values_[0];
    }
    size_t node_id(const node_type &nd) {return node_id(std::addressof(nd));}
    Graph(): nedges_(0) {}
};

}
