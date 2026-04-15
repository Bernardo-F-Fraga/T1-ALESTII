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

using namespace std;

struct Ordem
{
    int quant;
    int preço;
};

// Heap de compr: max-heap -> quem paga mais fica no topo
struct Compra
{

};

// Heap de vendas: min-heap → quem aceita menos fica no topo
struct Venda
{

};

int main()
{
    ifstream lista("lista.txt");
    
    //Pegar primeira linha (num total)
    int total = 0;
    lista >> total;

    // 
    



}