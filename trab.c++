/*
 Primeira linha: total de vendas/compras
 Demais linhas:

 <tipo> <quant> <preço>
  char     int     int

Da para usar 
Max-heap -> venda


*/


#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

//Min-heap
void Venda();

//Max-heap
void Compra();

struct Ordem
{   
    char tipo;
    int quant;
    int preço;
};

//Fila de entrada das ordens
queue <Ordem> entrada;

// Heap de compr: max-heap -> quem paga mais fica no topo
priority_queue <Ordem> Compra;

// Heap de vendas: min-heap → quem aceita menos fica no topo
priority_queue<Ordem> Venda;

int main(void)
{
    ifstream lista("lista.txt");

    //Pegar primeira linha (num total)
    int total = 0;
    lista >> total;

    // 
    



}