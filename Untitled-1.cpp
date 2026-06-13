/*
Fluxo geral do projeto:

1. Ler o grafo G.
2. Verificar se G é planar e obter uma imersão planar.
3. Calcular o nível de cada vértice na imersão.
4. Para cada deslocamento r em {0,1,...,k}:
      4.1. Remover os vértices cujo nível é congruente a r módulo (k + 1).
      4.2. Separar o grafo restante em componentes conexos.
      4.3. Resolver MIS exatamente em cada componente k-outerplanar.
      4.4. Unir as soluções dos componentes.
5. Retornar a maior solução encontrada entre os k + 1 deslocamentos.

*/