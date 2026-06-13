/*
    Leitura dos arquivos
*/

#pragma once

#include "graph.hpp"

#include <string>
#include <vector>

Graph read_graph_from_file(const std::string& path);
std::vector<VertexId> read_vertex_set_from_file(const std::string& path);