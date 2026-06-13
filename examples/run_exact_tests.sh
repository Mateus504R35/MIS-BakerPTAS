#!/bin/bash

echo "===== CICLO COM 6 VERTICES ====="
./build/baker_ptas examples/cycle6.txt --exact

echo
echo "===== ARVORE COM 5 VERTICES ====="
./build/baker_ptas examples/tree5.txt --exact

echo
echo "===== GRAFO DESCONEXO ====="
./build/baker_ptas examples/disconnected6.txt --exact

echo
echo "===== TRIANGULO ====="
./build/baker_ptas examples/triangle3.txt --exact

echo
echo "===== ESTRELA ====="
./build/baker_ptas examples/star5.txt --exact

echo
echo "===== K4 ====="
./build/baker_ptas examples/k4.txt --exact