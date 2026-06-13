#pragma once

#include "graph.hpp"

#include <vector>

struct ExactMISResult {
    std::vector<VertexId> vertices;
};

ExactMISResult solve_exact_mis_bruteforce(const Graph& graph);