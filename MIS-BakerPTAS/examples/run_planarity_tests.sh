#!/bin/bash

echo "===== CICLO COM 6 VERTICES ====="
./build/baker_ptas examples/cycle6.txt --planarity

echo
echo "===== ARVORE ====="
./build/baker_ptas examples/tree5.txt --planarity

echo
echo "===== GRAFO DESCONEXO ====="
./build/baker_ptas examples/disconnected6.txt --planarity

echo
echo "===== K4 ====="
./build/baker_ptas examples/k4.txt --planarity

echo
echo "===== K5 ====="
./build/baker_ptas examples/k5.txt --planarity

echo
echo "===== K3,3 ====="
./build/baker_ptas examples/k33.txt --planarity

echo
echo "===== IMERSAO DO CICLO ====="
./build/baker_ptas examples/cycle6.txt --embedding