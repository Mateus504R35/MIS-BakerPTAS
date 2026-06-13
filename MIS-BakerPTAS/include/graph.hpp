/*
    Estrutura do grafo e operações básicas
*/

#pragma once

#include <boost/graph/adjacency_list.hpp>

#include <cstddef>

using VertexId = std::size_t;
using EdgeId = std::size_t;

struct VertexData {
    VertexId id{};
};

struct EdgeData {
    EdgeId id{};
};

using BoostGraph = boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::undirectedS,
    VertexData,
    EdgeData
>;

class Graph {
public:
    explicit Graph(std::size_t vertex_count);

    [[nodiscard]] std::size_t vertex_count() const;
    [[nodiscard]] std::size_t edge_count() const;
    [[nodiscard]] bool has_edge(VertexId u,VertexId v) const;

    void add_edge(VertexId u,VertexId v);

    [[nodiscard]] const BoostGraph& data() const;
    [[nodiscard]] BoostGraph& data();

private:
    BoostGraph graph_;
    EdgeId next_edge_id_ = 0;
};