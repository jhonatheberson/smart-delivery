#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <iostream> // Saída padrão
#include <fstream> // Manipulação de arquivos
#include <cstdlib> // Funções padrão
#include <string> // Manipulação de strings
#include <limits> // Para Ajudar na leiura e escrita de arquivos
#include <ctime> // Para gerar grafos aleatórios
#include "Vertice.h" // Inclusão do tipo Aresta

using namespace std;

#define MAX_V 718 // Quantidade maxima de vértices

int contt(0);

 // Escreve um grafo grid aleatório com n*n vertices no arquivo "Grid.txt"
void gerarGrafoGrid(int n){

    cout << "Imprimindo grafo grid aleatorio com " << n*n << " vertices no arquivo Grid.txt..." << endl << endl;

    srand(time(NULL));
    int vg = n*n;
    ofstream Arquivo;
    Arquivo.open("Grid.txt");
    if (Arquivo.is_open())
    {
        Arquivo << vg <<"\nVertices:\n";
        for(int k = 0; k < vg; k++)
            Arquivo << k+1 <<" "<< (rand()%3)+1 <<"\n";
        Arquivo <<"Arestas:\n";
        for(int k = 0; k < vg; k++)
                {
                    if(k%n < n-1) Arquivo << k+1 <<" "<< k+2 << " " << (rand()%99)+1 << "\n";
                    if(k+n < vg) Arquivo << k+1 <<" "<< k+n+1 << " " << (rand()%99)+1 << "\n";
                }

        cout << "Grafo grid com " << vg << " vertices impresso com sucesso no arquivo Grid.txt..." << endl << endl << endl;
    }
    else
    {
        cout << "Arquivo Grid.txt nao encontrado..." << endl << endl << endl;
    }
    Arquivo.close();

}

// Escreve um grafo completo aleatório com n vertices no arquivo "Completo.txt".
void gerarGrafoCompleto(int n){
    cout << "Imprimindo grafo completo aleatorio com " << n << " vertices no arquivo Completo.txt..." << endl << endl;

    srand(time(NULL));
    ofstream Arquivo;
    Arquivo.open("Completo.txt");
    if (Arquivo.is_open())
    {
        Arquivo << n <<"\nVertices:\n";
        for(int k = 0; k < n; k++)
            Arquivo << k+1 <<" "<< (rand()%3)+1 <<"\n";
        Arquivo <<"Arestas:\n";
        for(int k = 0; k < n; k++)
            for(int l=0; l < k; l++)
                    Arquivo << k+1 <<" "<< l+1 << " " << (rand()%99)+1 << "\n";

        cout << "Grafo completo com " << n << " vertices impresso com sucesso no arquivo Completo.txt..." << endl << endl << endl;
    }
    else
    {
        cout << "Arquivo Completo.txt nao encontrado..." << endl << endl << endl;
    }
    Arquivo.close();

}

//Pilha Simples
struct Pilha{
private:
    Pilha *anterior;
    unsigned long long tamanho;
    int topo;
public:

    inline Pilha()
    {
        tamanho = 0;
        topo = 0;
        anterior = NULL;
    }

    bool vazio()
    {
        if (tamanho == 0) return true;
        else return false;
    }

    int top()
    {
        if(tamanho > 0) return topo;
        else return 0;
    }

    int tam()
    {
        return tamanho;
    }

    void push(int V)
    {
        if(tamanho > 0)
        {
            Pilha* pilha = new Pilha;
            pilha->topo = topo;
            pilha->tamanho = tamanho;
            pilha->anterior = anterior;
            anterior = pilha;
        }
        topo = V;
        tamanho++;
    }

    void pop()
    {
        if(tamanho > 1)
            topo = anterior->topo;

        if(tamanho == 2)
            if(anterior != NULL) delete anterior;

        if(tamanho > 2)
        {
            Pilha* lixo = anterior;
            anterior = anterior->anterior;
            if(lixo != NULL) delete lixo;
        }
        if(tamanho > 0) tamanho--;
    }

    void esvaziar() {while(!vazio()) pop();}
};

//Pilha para armazenar os vertices a seres visitados e pilha para armazena a rota.
Pilha pa;

class Grafo
{
public:

    int v; // Quantidade de vértices
    Vertice vertice[MAX_V]; // Vetor de vertices
    int matrizPesos[MAX_V][MAX_V]; // Matriz de Pesos das Arestas
    int melhorRota[MAX_V]; // Armazena os vertices com a melhor rota;

    inline Grafo() {v = 0;} //Construtor Default.
    void invalidarMatriz(); // Inicia todos os valores da matriz de Pesos com -1. O(v²)
    void desmarcarVertices(); // Desmarca Todos os Vertices. O(v)
    void criarAresta(int i, int j, int p); // Cria uma aresta (atualizando a matriz de pesos) entre os vertices de id i/j com peso p. O(1)
    void carregar_grafo(char *arquivo); // Lê o Grafo de um arquivo. O(v²)
    void imprimir(); // Imprime o grafo em um arquivo de nome "Resultado.txt". O(v²)
    void Ordenar_vertice(int, int); //Ordena o vetor de vertices do grafo, em ordem decrescente, de acordo com os graus, utilizando o MergeSort O(vlogv)
    Vertice Get_restaurante(); // retona o ID do vertice que é o restaurante O(v);
    void Set_restaurante(int); // Indica qual vertice será o restaurante (desativa o antigo caso haja) O(v);
    void melhoresRotas(); // Escreve em um arquivo chamado "melhoresRotas.txt" as rotas usadas para percorrer o grafo.
    int Dijkstra(int i, int pesoDesejado, int aux[]); // Encontra o menor caminho entre um vertice e outro vertice de 'pesoDesejado', e retorda o id do vertice encontrado.

};


void Grafo::criarAresta(int i, int j, int p){

    if(i <= 0 || i > v || j <= 0 || j > v) return;
    i--;
    j--;
    matrizPesos[i][j] = p;
    matrizPesos[j][i] = p;

}

void Grafo::invalidarMatriz(){
    for(int i=0; i<v; i++)
        for(int j=0; j<v; j++) matrizPesos[i][j] = -1;

}

void Grafo::desmarcarVertices(){
    for(int i=0; i<v; i++) vertice[i].status = false;
}

void Grafo::Set_restaurante(int r){

    int restaurante;

    if(r>=1 && r <= v)
    {
        //DESATIVA O ANTIGO RESTAURANTE E ATUALIZA O NOVO.
        for(int i=0; i<v; i++)
        {
            if(vertice[i].tipo == true) vertice[i].tipo = false;
            if(vertice[i].id == r) restaurante = i;
        }
    }
    vertice[restaurante].tipo = true;

}

Vertice Grafo::Get_restaurante(){
    for(int i = 0; i<v; i++)
    {
        if(vertice[i].tipo)
        {
            return vertice[i];
        }
    }
    return vertice[0];
};

void Grafo::melhoresRotas(){

    cout << endl << "Tentando gerar as melhores rotas e escreve-las no arquivo melhoresRotas.txt... " << endl << endl;

    int origem(0), pOrigem, cont(0);

    //desmarca os vertices e recebe o id do vertice restaurante.
    desmarcarVertices();
    origem = Get_restaurante().id;
    Ordenar_vertice(0, v-1);
    //imprimir();
    ofstream Arquivo;
    Arquivo.open("melhoresRotas.txt");
    if (Arquivo.is_open())
    {
        //percorre o vetor de vertices para criar as rotas para o vetor de vertices mais proximo, de maior grau.
        for(int i=0; i<v; i++)
            if(!vertice[i].status)
            {
                Arquivo << "rota " << cont << ":  ";
                cont++;
                pOrigem = Dijkstra(origem, vertice[i].grau, melhorRota);
                origem = pOrigem;
                Arquivo << melhorRota[0];
                for(int j=0 ; melhorRota[j+1] >= 0 && j+1 < v; j++ )
                    Arquivo << " (" << matrizPesos[melhorRota[j]-1][melhorRota[j+1]-1] << ") " << melhorRota[j+1];
                Arquivo << "\n\n";
            }

        cout << "As melhores rotas foram geradase escritas no arquivo melhoresRotas.txt com sucesso... " << endl << endl << endl;
    }
    else
    {
        cout << "Nao foi possivel abrir o arquivo para escrever as rotas..." << endl << endl << endl;
    }
    Arquivo.close();
}

void Grafo::carregar_grafo(char *arquivo){

    cout << "Tentando carregar Grafo do arquivo " << arquivo << "... " << endl << endl;

    int i=0, j=0, p=0;

    ifstream fin; // Objeto de fluxo de entrada de arquivo
    fin.open(arquivo, ios::in); // Abrindo fluxo de leitura com o arquivo
    // Verificando se o arquivo foi aberto corretamente
    if (fin.is_open())
    {
        fin >> v; // Lendo quantidade de vértices que deve estar presenta na primeira linha do arquivo

        if(v > MAX_V)
        {
            cout << "ERRO!!! v = " << v << " e MAX_V = " << MAX_V << ";  Aumente MAX_V no programa ou diminua v no arquivo." << endl << endl;
            exit(0);
        }

        invalidarMatriz(); // inicia todos os valores da matriz de peso com -1, como se não huvesse nenhuma aresta.
        fin.ignore(numeric_limits<streamsize>::max(), ':');
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        //Lê o id e o grau dos vertices no arquivo, respectivamente.
        for(int x=0; x<v; x++)
            fin >> vertice[x].id >> vertice[x].grau;
        fin.ignore(numeric_limits<streamsize>::max(), ':');
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (!fin.eof())
        {
            fin >> i;
            fin.ignore(numeric_limits<streamsize>::max(), ' ');
            fin >> j;
            fin.ignore(numeric_limits<streamsize>::max(), ' ');
            fin >> p;
            fin.ignore(numeric_limits<streamsize>::max(), '\n');
            criarAresta(i, j, p);
        }
        fin.close();// Fechando fluxo de leitura de arquivo
        cout << "Grafo do arquivo " << arquivo << " carregado com sucesso! " << endl << endl << endl;
    }
    else
    {
        cout << "Arquivo nao encontrado..." << endl;
    }


}

void Grafo::Ordenar_vertice(int l, int r){
    if (l < r)
    {
        int m = l + (r - l) / 2;
        Ordenar_vertice(l, m);
        Ordenar_vertice(m + 1, r);

        ///MERGE
        int i, j, k, n1, n2;

        n1 = m - l + 1;
        n2 = r - m;

        Vertice L[n1], R[n2];

        for (i = 0; i < n1; i++)
            L[i] = vertice[l + i];
        for (j = 0; j < n2; j++)
            R[j] = vertice[m + 1 + j];

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2)
        {
            if (L[i].grau >= R[j].grau)
            {
                vertice[k] = L[i];
                i++;
            }
            else
            {
                vertice[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            vertice[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            vertice[k] = R[j];
            j++;
            k++;
        }
        ///FIM MERGE
    }
}

void Grafo::imprimir(){

    cout << "Tentando imprimir o grafo no arquivo Resultado.txt... " << endl << endl;

    ofstream Arquivo;
    Arquivo.open("Resultado.txt");

    if (Arquivo.is_open())
    {
        Arquivo << v <<"\nVertices:\n";
        for(int k = 0; k < v; k++)
            Arquivo << vertice[k].id <<" "<<vertice[k].grau<<"\n";
        Arquivo <<"Arestas:\n";
        for(int k = 0; k < v; k++)
            for(int l = 0; l < k; l++)
                if(matrizPesos[k][l] > 0)
                    Arquivo << k+1 << " " << l+1 << " " << matrizPesos[k][l] <<"\n";

        cout << "Grafo impresso com sucesso no arquivo Resultado.txt... " << endl << endl << endl;
    }
    else
    {
        cout << "Arquivo nao encontrado..." << endl;
    }
    Arquivo.close();
};

int Grafo::Dijkstra(int i, int grauDesejado, int aux[]){

    //Verifica se as entradas i e j são validas
    if(i <= 0 || grauDesejado <= 0 || i > v || grauDesejado > 3)
    {
        cout << "Dijsktra: ENTRADAS INVALIDAS! " << contt << endl;
        cout << "i = " << i << endl;
        cout << "grauDesejado = " << grauDesejado << endl << endl;
        system("pause");
        return 0;
    }

    //Corrige o valor de entrada para utilizar nos vetores.
    i--;

    //Variaveis para auxiliar no algorítmo
    int pesoC, p, proxVertice, verticeAtual, pivoPeso, pPeso2;
    int c, j, melhorVertice;
    int pCaminhoMelhor;
    int VerticesNMarcados[v] = {};

    //Variaves de armazenar as rotas e a soma dos pesos.
    int d[v];
    int rot[v];

    //Variavel usada como marcador dos vertices para o algoritmo do dijkstra.
    bool vm[v] = {};

    //Coloca o vertice inicial na fila.
    verticeAtual = i;
    vm[verticeAtual] = true;

    //inicia as rotas com -1 e as distancias com infinito. antes de executar o algoritmo.
    for(int k = 0; k < v; k++)
    {
        if(vertice[k].id == i+1)vertice[k].marcar();// marca no vetor de vertices o vertice atual.
        rot[k] = -1;
        d[k] = INT_MAX;
        VerticesNMarcados[k] = -1;
    }
    d[verticeAtual] = 0;

    //Enquanto houverem vértices a serem percorridos.
    for(int k = 0; k < v; k++)
    {
        //cout << endl;
        pivoPeso = INT_MAX;
        proxVertice = -1;
        for(int l = 0; l < v; l++)
        {
            c = -1;
            if (matrizPesos[verticeAtual][l] > 0)
            {
                c = l;
                p = matrizPesos[verticeAtual][l];
                if(!vm[l])
                {
                    if(p < pivoPeso)
                    {
                        pivoPeso = p;
                        proxVertice = l;
                    }
                    VerticesNMarcados[l] = p;
                }
            }
            if (c >= 0)
            {
                pesoC = d[verticeAtual] + p;
                if( d[c] > pesoC )
                {
                    d[c] = pesoC;
                    rot[c] = verticeAtual;
                }
            }
        }
        if(proxVertice < 0 && k < v-1)
        {
            pPeso2 = INT_MAX;
            for(int m = 0; m < v; m++)
                if(VerticesNMarcados[m] > 0 && VerticesNMarcados[m] < pPeso2)
                {
                    proxVertice = m;
                    pPeso2 = VerticesNMarcados[m];
                }
        }
        vm[verticeAtual] = true;
        VerticesNMarcados[verticeAtual] = -1;
        verticeAtual = proxVertice;
    }

    //Calcula o peso total das rotas e atualiza no vetor auxiliar;
    j = -1;
    pCaminhoMelhor = INT_MAX;

    for(int k=0; k<v; k++)
        if(vertice[k].grau == grauDesejado && !vertice[k].status && d[vertice[k].id-1] < pCaminhoMelhor)
        {
            pCaminhoMelhor = d[vertice[k].id-1];
            j = vertice[k].id-1;
        }

    if(j < 0)
    {
        cout << "BUGOU O DIJKSTRA NO J (PODE TER SIDO CHAMADO SEM NENHUM VERTICE COM grau " << grauDesejado << " restante) " << contt << endl;
        return 0;
    }

    melhorVertice = j+1;

    pa.push(j+1);

    do
    {
        j = rot[j];
        for(int k = 0; k < v; k++)
            if(vertice[k].id == j+1)
                vertice[k].marcar();
        pa.push(j+1);
    }
    while(j != i);

    for(int k = 0; k < v; k++)
        if(!pa.vazio())
        {
            aux[k] = pa.top();
            pa.pop();
        }
        else aux[k] = -1;

    while(!pa.vazio())
        pa.pop();

    return melhorVertice;
}

#endif
