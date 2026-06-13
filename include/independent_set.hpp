/*
    Verificação do conjunto independente
*/

#pragma once

#include "graph.hpp"

#include <optional>
#include <string>
#include <utility>
#include <vector>

struct IndependentSetValidation {
    bool is_independent;
    std::string message;
    std::optional<std::pair<VertexId,VertexId>> conflicting_edge;
};

IndependentSetValidation validate_independent_set(
    const Graph& graph,
    const std::vector<VertexId>& vertices
);