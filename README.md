![Alt text](Graph.png?raw=true "Test Graph")

Um QuasiClique (ou γ-Clique) de um grafo G é um subconjunto de V(G) cujo subgrafo induzido é conexo e tem densidade maior ou igual a γ.

O projeto, no momento, é capaz de encontrar, dados um grafo G uma densidade γ ∈ [0,1], um γ-Clique maximal em G.

A inclusão do uso de memória secundária ainda não foi realizada pelo fato de que ainda há otimizações a serem feitas e sua implementação é razoavelmente complicada.

A imagem acima é uma instância de um grafo qualquer, dentro do qual serão encontrados QuasiCliques. Sua descrição está no arquivo adj_list.txt, que é um conjunto de listas de adjacências. O grafo é não-direcionado.

Para executar o projeto, basta ter os arquivos QuasiClique.cpp e adj_list.txt na mesma pasta e executar o .cpp.
