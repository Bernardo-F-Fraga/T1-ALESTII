/*
 Primeira linha: total de vendas/compras
 Demais linhas:

 <tipo> <quant> <preco>
  char     int     int

Max-heap -> Compra
Min-heap -> Venda

lê uma ordem
│
├── é Compra?
│     └── tem venda no topo com preço ≤ compra?
│           ├── sim → casa, registra lucro
│           └── não → empurra no heap de compras
│
└── é Venda?
      └── tem compra no topo com preço ≥ venda?
            ├── sim → casa, registra lucro
            └── não → empurra no heap de vendas

*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Ordem {
    char tipo;
    int quant;
    int preco;
};

// priority_queue exige um tipo como comparador, não uma função, por isso struct com operator() é a forma mais simples
struct CompararCompra {
    bool operator()(Ordem a, Ordem b) {
        return a.preco < b.preco; // maior preço no topo
    }
};

struct CompararVenda {
    bool operator()(Ordem a, Ordem b) {
        return a.preco > b.preco; // menor preço no topo
    }
};

class OrderBook {
    //              tipo    container      comparador
    priority_queue<Ordem, vector<Ordem>, CompararCompra> compras;
    priority_queue<Ordem, vector<Ordem>, CompararVenda>  vendas;
    int lucro = 0;
    int negociadas = 0;

public:
    void inserir(Ordem o);
    void imprimir();
};

void OrderBook::inserir(Ordem o) 
{
    // Se uma Compra foi inserida
    if (o.tipo == 'C') 
    {
        // Enquanto
        // 1. Houver vendas
        // 2. A venda mais alta for menor ou igual ao preço da compra
        // 3. A compra ainda tiver quantidade a negociar
        while (vendas.empty() == false && vendas.top().preco <= o.preco && o.quant > 0) 
        {
            // Pega a venda mais barata do heap
            Ordem venda = vendas.top();
            vendas.pop();

            // Negocia a menor quantidade entre compra e venda
            int negociado;

            // Se a quantidade que a compra atual quer é menor que a quantidade disponível na venda, negocia o que a compra quer.
            // Se não, negocia o que a venda tem disponível.
            if (o.quant < venda.quant) {
                negociado = o.quant;
            } else {
                negociado = venda.quant;
            }

            // Registra lucro da fintech -> diferença entre preço de compra e venda multiplicada pela quantidade negociada
            lucro      += (o.preco - venda.preco) * negociado;

            // Registra quantidade negociada
            negociadas += negociado;

            // Desconta a quantidade negociada de cada lado
            o.quant     -= negociado;
            venda.quant -= negociado;

            // Se sobrou quantidade na venda, devolve ao heap
            if (venda.quant > 0) {
                vendas.push(venda);
            }
        }

        // Se sobrou quantidade na compra, guarda no heap
        if (o.quant > 0)
        {
            compras.push(o);
        }
    }
    // Se uma Venda foi inserida
    else {
        // Enquanto
        // 1. Houver compras
        // 2. A compra mais alta for maior ou igual ao preço da venda
        // 3. A venda ainda tiver quantidade a negociar
        while (compras.empty() == false && compras.top().preco >= o.preco && o.quant > 0)
        {
            // Pega a compra mais cara do heap
            Ordem compra = compras.top();
            compras.pop();

            // Negocia a menor quantidade entre compra e venda
            int negociado;

            // Se a quantidade que a venda atual quer é menor que a quantidade disponível na compra, negocia o que a venda quer.
            // Se não, negocia o que a compra tem disponível.
            if (o.quant < compra.quant) {
                negociado = o.quant;
            } else {
                negociado = compra.quant;
            }

            // Registra lucro da fintech -> diferença entre preço de compra e venda multiplicada pela quantidade negociada
            lucro       += (compra.preco - o.preco) * negociado;

            // Registra quantidade negociada
            negociadas   += negociado;

            // Desconta a quantidade negociada de cada lado
            o.quant      -= negociado;
            compra.quant -= negociado;

            // Se sobrou quantidade na compra, devolve ao heap
            if (compra.quant > 0) {
                compras.push(compra);
            }
        }

        // Se sobrou quantidade na venda, guarda no heap
        if (o.quant > 0)
        {
            vendas.push(o);
        }
    }
}

void OrderBook::imprimir() {
    cout << "Lucro: " << lucro << endl;
    cout << "Acoes negociadas: " << negociadas << endl;
    cout << "Compras pendentes: " << compras.size() << endl;
    cout << "Vendas pendentes: " << vendas.size() << endl;
}

int main() {
    //ifstream lista("testes/t5.txt");
    ifstream lista("testes/t5.txt");

    int total = 0;
    lista >> total;

    OrderBook book;

    for (int i = 0; i < total; i++) {
        Ordem o;
        lista >> o.tipo >> o.quant >> o.preco;
        book.inserir(o);
    }

    book.imprimir();
}
