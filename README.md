# Trabalho Grafos

Trabalho para a disciplina de Teoria dos Grafos (DCC059) 2024.1 da UFJF.
<br>

Para rodar o código coloque isso no terminal:
g++ -o graph_program Graph.cpp Node.cpp Edge.cpp main.cpp

Trabalho 1 - DCC059 - Teoria dos Grafos
Este documento traz a especificação do Trabalho 1, uma atividade avaliativa do tipo “Trabalho Prático”, e serve de base para todas as atividades de implementação cobradas ao longo do curso da disciplina DCC059 - Teoria dos Grafos no semestre letivo 2024-1.

Especificação
Desenvolver um Tipo Abstrato de Dados (TAD) ou uma Classe que represente grafos simples, que podem ser:

Orientados ou não orientados
Ponderados ou não ponderados (nos vértices e/ou nas arestas)
Implemente o conjunto de funcionalidades a seguir, detalhadas em sala de aula. O desenvolvimento dos algoritmos contribui como base para a resolução das questões das avaliações teóricas.

Orientações
Representação do Grafo: Seu TAD ou Classe deve ser capaz de representar grafos utilizando LISTA DE ADJACÊNCIA.

Linguagem: O código deve ser desenvolvido em C ou C++. Não deve usar funções que não sejam nativas da linguagem, pois isso pode levar à impossibilidade de compilar seu código no ambiente que será usado para testes.

Clareza e Organização: Além do atendimento às funcionalidades, alguns dos elementos avaliados são a clareza e a organização do código (nomes de funções e variáveis, comentários que indiquem o propósito das principais funções e procedimentos, inclusive explicando o que são os parâmetros e o retorno, em caso de função).

Leitura de Arquivo: O programa principal que usará o TAD ou a Classe Grafo deve ler os dados do grafo de entrada (direcionados ou não direcionados, ponderados ou não ponderados) a partir de um arquivo texto. O formato do arquivo dependerá da origem dos dados de entrada. Certifique-se de ler o arquivo README que explica a semântica do arquivo de entrada ou, caso não haja este arquivo, leia o detalhamento do mesmo na fonte de dados, implementando conforme o caso.

Formato do Arquivo:

O arquivo pode ser apresentado com o número de vértices na primeira linha e as arestas nas linhas seguintes.
A informação sobre o tipo de grafo (direcionado ou não direcionado), arestas ponderadas ou não, e pesos nos vértices deve ser passada ao programa por parâmetros via linha de comando.
Parâmetros via Linha de Comando:

Tipo de Grafo: 0 (não direcionado) ou 1 (direcionado).
Arestas Ponderadas: 0 (não ponderado) ou 1 (ponderado).
Pesos nos Vértices: 0 (não ponderado) ou 1 (ponderado).
Nome do Arquivo: O nome do arquivo a ser lido deve ser informado ao programa via teclado para a função main (utilizar int main (int argc, char **argv) para passar todas as informações necessárias ao funcionamento do programa).

Entrega: Cada grupo enviará um único arquivo compactado com o nome Trabalho_GrupoX.zip. No arquivo zip, devem estar incluídos apenas os arquivos com extensão .c, .cc, .cpp ou .h, e os arquivos das instâncias usadas no experimento.

Funcionalidades
O programa deve apresentar em tela a saída para as seguintes funcionalidades:

a) Fecho Transitivo Direto:

Parâmetro: Um ID de um vértice de um grafo direcionado.
Saída: O fecho transitivo direto deste vértice.
b) Fecho Transitivo Indireto:

Parâmetro: Um ID de um vértice de um grafo direcionado.
Saída: O fecho transitivo indireto deste vértice.
c) Caminho Mínimo (Dijkstra):

Parâmetro: Dois IDs de vértices do grafo.
Saída: O caminho mínimo entre estes dois vértices usando o algoritmo de Dijkstra.
d) Caminho Mínimo (Floyd-Warshall):

Parâmetro: Dois IDs de vértices do grafo.
Saída: O caminho mínimo entre estes dois vértices usando o algoritmo de Floyd-Warshall.
e) Árvore Geradora Mínima (Prim):

Parâmetro: Um subconjunto X de vértices do grafo.
Saída: Uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Prim.
f) Árvore Geradora Mínima (Kruskal):

Parâmetro: Um subconjunto X de vértices do grafo.
Saída: Uma Árvore Geradora Mínima sobre o subgrafo vértice-induzido por X usando o algoritmo de Kruskal.
g) Caminhamento em Profundidade:

Parâmetro: Um ID de vértice.
Saída: A árvore dada pela ordem de caminhamento em profundidade a partir do nó dado como parâmetro, destacando as arestas de retorno.
h) Métricas do Grafo:

Parâmetro: O grafo (direcionado ou não direcionado) ponderado nas arestas.
Saída: O raio, o diâmetro, o centro e a periferia do grafo.
i) Pontos de Articulação:

Parâmetro: O grafo não direcionado.
Saída: O conjunto de vértices de articulação.
Cada uma das saídas das funcionalidades deve ser apresentada na tela. Após a execução, o programa deve perguntar ao usuário se deseja salvar a saída em um arquivo.

Menu de Opções
O programa deve apresentar as funcionalidades em forma de um menu de opções que se repete até que o usuário escolha sair do programa.
