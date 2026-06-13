#include "planarity.hpp"

#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/property_map/property_map.hpp>

#include <stdexcept>
#include <utility>
#include <vector>

PlanarityResult compute_planar_embedding(const Graph& graph) {
    const auto& data = graph.data();

    PlanarEmbedding embedding(graph.vertex_count());

    const auto vertex_index =
        boost::get(boost::vertex_index,data);

    auto embedding_map =
        boost::make_iterator_property_map(
            embedding.begin(),
            vertex_index
        );

    const bool is_planar =
        boost::boyer_myrvold_planarity_test(
            boost::boyer_myrvold_params::graph = data,
            boost::boyer_myrvold_params::embedding = embedding_map
        );

    if (!is_planar) {
        embedding.clear();
    }

    return {
        is_planar,
        std::move(embedding)
    };
}

std::vector<VertexId> cyclic_neighbors(
    const Graph& graph,
    const PlanarEmbedding& embedding,
    VertexId vertex
) {
    if (vertex >= graph.vertex_count()) {
        throw std::invalid_argument(
            "O vertice nao pertence ao grafo."
        );
    }

    if (embedding.size() != graph.vertex_count()) {
        throw std::invalid_argument(
            "A imersao planar nao corresponde ao grafo."
        );
    }

    const auto& data = graph.data();

    std::vector<VertexId> neighbors;
    neighbors.reserve(embedding[vertex].size());

    for (const auto& edge : embedding[vertex]) {
        const VertexId u = boost::source(edge,data);
        const VertexId v = boost::target(edge,data);

        if (u == vertex) {
            neighbors.push_back(v);
        } else if (v == vertex) {
            neighbors.push_back(u);
        } else {
            throw std::logic_error(
                "A imersao contem uma aresta nao incidente ao vertice."
            );
        }
    }

    return neighbors;
}