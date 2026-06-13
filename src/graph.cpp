/*
    Estrutura do grafo e operações básicas
*/

#include "graph.hpp"

#include <boost/graph/graph_traits.hpp>

#include <stdexcept>

Graph::Graph(std::size_t vertex_count) : graph_(vertex_count) {
    for (VertexId vertex = 0;vertex < vertex_count;vertex++) {
        graph_[vertex].id = vertex;
    }
}

std::size_t Graph::vertex_count() const {
    return boost::num_vertices(graph_);
}

std::size_t Graph::edge_count() const {
    return boost::num_edges(graph_);
}

bool Graph::has_edge(VertexId u,VertexId v) const {
    if (u >= vertex_count() || v >= vertex_count()) {
        return false;
    }

    return boost::edge(u,v,graph_).second;
}

void Graph::add_edge(VertexId u,VertexId v) {
    if (u >= vertex_count() || v >= vertex_count()) {
        throw std::invalid_argument(
            "Aresta possui vertice fora do intervalo permitido."
        );
    }

    if (u == v) {
        throw std::invalid_argument(
            "Lacos nao sao permitidos no grafo de entrada."
        );
    }

    if (has_edge(u,v)) {
        throw std::invalid_argument(
            "Arestas duplicadas nao sao permitidas no grafo de entrada."
        );
    }

    const auto [edge,inserted] = boost::add_edge(u,v,graph_);

    if (!inserted) {
        throw std::runtime_error(
            "Nao foi possivel inserir a aresta."
        );
    }

    graph_[edge].id = next_edge_id_++;
}

const BoostGraph& Graph::data() const {
    return graph_;
}

BoostGraph& Graph::data() {
    return graph_;
}