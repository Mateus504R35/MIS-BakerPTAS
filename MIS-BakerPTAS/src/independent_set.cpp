/*
    Verificação do conjunto independente
*/

#include "independent_set.hpp"

#include <boost/graph/graph_traits.hpp>

#include <string>
#include <vector>

IndependentSetValidation validate_independent_set(
    const Graph& graph,
    const std::vector<VertexId>& vertices
) {
    std::vector<bool> selected(graph.vertex_count(),false);

    for (const VertexId vertex : vertices) {
        if (vertex >= graph.vertex_count()) {
            return {
                false,
                "O vertice " + std::to_string(vertex) +
                " nao pertence ao grafo.",
                std::nullopt
            };
        }

        if (selected[vertex]) {
            return {
                false,
                "O vertice " + std::to_string(vertex) +
                " aparece mais de uma vez no conjunto.",
                std::nullopt
            };
        }

        selected[vertex] = true;
    }

    const auto& data = graph.data();
    const auto [begin,end] = boost::edges(data);

    for (auto iterator = begin;iterator != end;++iterator) {
        const VertexId u = boost::source(*iterator,data);
        const VertexId v = boost::target(*iterator,data);

        if (selected[u] && selected[v]) {
            return {
                false,
                "Os vertices " + std::to_string(u) +
                " e " + std::to_string(v) +
                " sao adjacentes.",
                std::pair<VertexId,VertexId>{u,v}
            };
        }
    }

    return {
        true,
        "O conjunto informado e independente.",
        std::nullopt
    };
}