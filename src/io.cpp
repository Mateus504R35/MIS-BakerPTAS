/*
    Leitura dos arquivos
*/

#include "io.hpp"

#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
VertexId convert_vertex_id(long long value,const std::string& context) {
    if (value < 0) {
        throw std::runtime_error(
            context + ": identificador de vertice negativo."
        );
    }

    if (
        static_cast<unsigned long long>(value) >
        std::numeric_limits<VertexId>::max()
    ) {
        throw std::runtime_error(
            context + ": identificador de vertice muito grande."
        );
    }

    return static_cast<VertexId>(value);
}
}

Graph read_graph_from_file(const std::string& path) {
    std::ifstream input(path);

    if (!input) {
        throw std::runtime_error(
            "Nao foi possivel abrir o arquivo do grafo: " + path
        );
    }

    long long vertex_count_raw;
    long long edge_count_raw;

    if (!(input >> vertex_count_raw >> edge_count_raw)) {
        throw std::runtime_error(
            "Cabecalho invalido. Use: numero_de_vertices numero_de_arestas."
        );
    }

    if (vertex_count_raw < 0 || edge_count_raw < 0) {
        throw std::runtime_error(
            "O numero de vertices e o numero de arestas devem ser nao negativos."
        );
    }

    const auto vertex_count =
        static_cast<std::size_t>(vertex_count_raw);

    const auto edge_count =
        static_cast<std::size_t>(edge_count_raw);

    Graph graph(vertex_count);

    for (std::size_t index = 0;index < edge_count;index++) {
        long long u_raw;
        long long v_raw;

        if (!(input >> u_raw >> v_raw)) {
            throw std::runtime_error(
                "Arquivo terminou antes da leitura de todas as arestas."
            );
        }

        const VertexId u = convert_vertex_id(
            u_raw,
            "Aresta " + std::to_string(index)
        );

        const VertexId v = convert_vertex_id(
            v_raw,
            "Aresta " + std::to_string(index)
        );

        graph.add_edge(u,v);
    }

    std::string extra;

    if (input >> extra) {
        throw std::runtime_error(
            "O arquivo possui conteudo extra depois da ultima aresta."
        );
    }

    return graph;
}

std::vector<VertexId> read_vertex_set_from_file(const std::string& path) {
    std::ifstream input(path);

    if (!input) {
        throw std::runtime_error(
            "Nao foi possivel abrir o arquivo do conjunto: " + path
        );
    }

    long long set_size_raw;

    if (!(input >> set_size_raw) || set_size_raw < 0) {
        throw std::runtime_error(
            "Cabecalho invalido no arquivo do conjunto."
        );
    }

    const auto set_size =
        static_cast<std::size_t>(set_size_raw);

    std::vector<VertexId> vertices;
    vertices.reserve(set_size);

    for (std::size_t index = 0;index < set_size;index++) {
        long long vertex_raw;

        if (!(input >> vertex_raw)) {
            throw std::runtime_error(
                "Arquivo terminou antes da leitura de todos os vertices do conjunto."
            );
        }

        vertices.push_back(
            convert_vertex_id(
                vertex_raw,
                "Posicao " + std::to_string(index)
            )
        );
    }

    std::string extra;

    if (input >> extra) {
        throw std::runtime_error(
            "O arquivo do conjunto possui conteudo extra."
        );
    }

    return vertices;
}