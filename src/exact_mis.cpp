#include "exact_mis.hpp"

#include <boost/graph/graph_traits.hpp>

#include <bit>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace {
using Mask = std::uint64_t;

std::vector<Mask> build_adjacency_masks(const Graph& graph) {
    std::vector<Mask> adjacency_masks(graph.vertex_count(),0);

    const auto& data = graph.data();
    const auto [begin,end] = boost::edges(data);

    for (auto iterator = begin;iterator != end;++iterator) {
        const VertexId u = boost::source(*iterator,data);
        const VertexId v = boost::target(*iterator,data);

        adjacency_masks[u] |= Mask{1} << v;
        adjacency_masks[v] |= Mask{1} << u;
    }

    return adjacency_masks;
}

bool is_independent_mask(
    Mask subset,
    const std::vector<Mask>& adjacency_masks
) {
    for (VertexId vertex = 0;vertex < adjacency_masks.size();vertex++) {
        const Mask vertex_bit = Mask{1} << vertex;

        if ((subset & vertex_bit) == 0) {
            continue;
        }

        if ((adjacency_masks[vertex] & subset) != 0) {
            return false;
        }
    }

    return true;
}

std::vector<VertexId> mask_to_vertices(Mask subset,std::size_t vertex_count) {
    std::vector<VertexId> vertices;

    for (VertexId vertex = 0;vertex < vertex_count;vertex++) {
        const Mask vertex_bit = Mask{1} << vertex;

        if ((subset & vertex_bit) != 0) {
            vertices.push_back(vertex);
        }
    }

    return vertices;
}
}

ExactMISResult solve_exact_mis_bruteforce(const Graph& graph) {
    const std::size_t vertex_count = graph.vertex_count();

    if (vertex_count > 63) {
        throw std::invalid_argument(
            "O solucionador exato por forca bruta aceita no maximo 63 vertices."
        );
    }

    const auto adjacency_masks = build_adjacency_masks(graph);

    const Mask total_subsets = Mask{1} << vertex_count;

    Mask best_subset = 0;
    int best_size = 0;

    for (Mask subset = 0;subset < total_subsets;subset++) {
        const int current_size = std::popcount(subset);

        if (current_size <= best_size) {
            continue;
        }

        if (!is_independent_mask(subset,adjacency_masks)) {
            continue;
        }

        best_subset = subset;
        best_size = current_size;
    }

    return {
        mask_to_vertices(best_subset,vertex_count)
    };
}