#include "exact_mis.hpp"
#include "independent_set.hpp"
#include "io.hpp"
#include "planarity.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
void print_vertex_set(const std::vector<VertexId>& vertices) {
    std::cout << '{';

    for (std::size_t index = 0;index < vertices.size();index++) {
        std::cout << vertices[index];

        if (index + 1 < vertices.size()) {
            std::cout << ',';
        }
    }

    std::cout << '}';
}

void print_embedding(
    const Graph& graph,
    const PlanarEmbedding& embedding
) {
    std::cout << "Imersao planar:\n";

    for (
        VertexId vertex = 0;
        vertex < graph.vertex_count();
        vertex++
    ) {
        const auto neighbors =
            cyclic_neighbors(graph,embedding,vertex);

        std::cout << "Vertice " << vertex << ": ";

        if (neighbors.empty()) {
            std::cout << "(sem vizinhos)";
        } else {
            for (
                std::size_t index = 0;
                index < neighbors.size();
                index++
            ) {
                std::cout << neighbors[index];

                if (index + 1 < neighbors.size()) {
                    std::cout << " -> ";
                }
            }
        }

        std::cout << '\n';
    }
}
}

int main(int argc,char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr
            << "Uso:\n"
            << "  "
            << argv[0]
            << " <arquivo_do_grafo>\n"
            << "  "
            << argv[0]
            << " <arquivo_do_grafo> <arquivo_do_conjunto>\n"
            << "  "
            << argv[0]
            << " <arquivo_do_grafo> --exact\n"
            << "  "
            << argv[0]
            << " <arquivo_do_grafo> --planarity\n"
            << "  "
            << argv[0]
            << " <arquivo_do_grafo> --embedding\n";

        return 1;
    }

    try {
        const Graph graph =
            read_graph_from_file(argv[1]);

        std::cout << "Grafo carregado com sucesso.\n";
        std::cout
            << "Vertices: "
            << graph.vertex_count()
            << '\n';

        std::cout
            << "Arestas: "
            << graph.edge_count()
            << '\n';

        if (argc == 2) {
            return 0;
        }

        const std::string argument = argv[2];

        if (argument == "--exact") {
            const auto result =
                solve_exact_mis_bruteforce(graph);

            const auto validation =
                validate_independent_set(
                    graph,
                    result.vertices
                );

            if (!validation.is_independent) {
                throw std::logic_error(
                    "Erro interno: o solucionador retornou um conjunto invalido."
                );
            }

            std::cout << "MIS exato: ";
            print_vertex_set(result.vertices);
            std::cout << '\n';

            std::cout
                << "Tamanho do MIS: "
                << result.vertices.size()
                << '\n';

            return 0;
        }

        if (
            argument == "--planarity" ||
            argument == "--embedding"
        ) {
            const auto result =
                compute_planar_embedding(graph);

            if (!result.is_planar) {
                std::cout
                    << "O grafo nao e planar.\n";

                return 2;
            }

            std::cout
                << "O grafo e planar.\n";

            if (argument == "--embedding") {
                print_embedding(
                    graph,
                    result.embedding
                );
            }

            return 0;
        }

        const auto vertices =
            read_vertex_set_from_file(argument);

        const auto validation =
            validate_independent_set(
                graph,
                vertices
            );

        std::cout
            << validation.message
            << '\n';

        return validation.is_independent ? 0 : 2;
    } catch (const std::exception& error) {
        std::cerr
            << "Erro: "
            << error.what()
            << '\n';

        return 1;
    }
}