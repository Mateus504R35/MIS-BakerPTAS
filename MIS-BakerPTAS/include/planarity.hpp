#pragma once

#include "graph.hpp"

#include <boost/graph/graph_traits.hpp>

#include <vector>

using EdgeDescriptor =
    boost::graph_traits<BoostGraph>::edge_descriptor;

using PlanarEmbedding =
    std::vector<std::vector<EdgeDescriptor>>;

struct PlanarityResult {
    bool is_planar;
    PlanarEmbedding embedding;
};

PlanarityResult compute_planar_embedding(const Graph& graph);

std::vector<VertexId> cyclic_neighbors(
    const Graph& graph,
    const PlanarEmbedding& embedding,
    VertexId vertex
);