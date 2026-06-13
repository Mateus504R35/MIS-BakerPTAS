#!/bin/bash

echo "===== 1. CICLO ====="
./build/baker_ptas examples/cycle6.txt

echo
echo "===== 2. ARVORE ====="
./build/baker_ptas examples/tree5.txt

echo
echo "===== 3. GRAFO DESCONEXO ====="
./build/baker_ptas examples/disconnected6.txt

echo
echo "===== 4. CONJUNTO VALIDO ====="
./build/baker_ptas examples/cycle6.txt examples/set_valid.txt

echo
echo "===== 5. VERTICES ADJACENTES ====="
./build/baker_ptas examples/cycle6.txt examples/set_adjacent_vertices.txt

echo
echo "===== 6. VERTICE INEXISTENTE NO CONJUNTO ====="
./build/baker_ptas examples/cycle6.txt examples/set_invalid_vertex.txt

echo
echo "===== 7. LACO ====="
./build/baker_ptas examples/graph_with_loop.txt

echo
echo "===== 8. ARESTA DUPLICADA ====="
./build/baker_ptas examples/graph_with_duplicate_edge.txt

echo
echo "===== 9. VERTICE INEXISTENTE NA ARESTA ====="
./build/baker_ptas examples/graph_with_invalid_vertex.txt

echo
echo "===== 10. VERTICE REPETIDO NO CONJUNTO ====="
./build/baker_ptas examples/cycle6.txt examples/set_repeated_vertex.txt
