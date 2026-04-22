/*
PRINTS PARA VER TUDO ACONTECENDO



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
    void exibirHeaps();

private:
    void exibirHeapCompras();
    void exibirHeapVendas();
};

void OrderBook::inserir(Ordem o)
{
    cout << "\n========================================" << endl;
    cout << "NOVA ORDEM RECEBIDA!" << endl;
    cout << "Tipo: " << (o.tipo == 'C' ? "COMPRA" : "VENDA") << endl;
    cout << "Quantidade: " << o.quant << endl;
    cout << "Preço: R$" << o.preco << endl;
    cout << "========================================" << endl;

    // Se uma Compra foi inserida
    if (o.tipo == 'C')
    {
        cout << "\n[COMPRA] Procurando vendas compatíveis..." << endl;

        int negociacoes = 0;
        // Enquanto
        // 1. Houver vendas
        // 2. A venda mais alta for menor ou igual ao preço da compra
        // 3. A compra ainda tiver quantidade a negociar
        while (vendas.empty() == false && vendas.top().preco <= o.preco && o.quant > 0)
        {
            // Pega a venda mais barata do heap
            Ordem venda = vendas.top();
            vendas.pop();

            negociacoes++;
            cout << "  → Venda encontrada! Preço: R$" << venda.preco << " | Quantidade: " << venda.quant << endl;

            // Negocia a menor quantidade entre compra e venda
            int negociado;

            // Se a quantidade que a compra atual quer é menor que a quantidade disponível na venda, negocia o que a compra quer.
            // Se não, negocia o que a venda tem disponível.
            if (o.quant < venda.quant) {
                negociado = o.quant;
            } else {
                negociado = venda.quant;
            }

            int lucro_operacao = (o.preco - venda.preco) * negociado;

            cout << "    ✓ NEGOCIAÇÃO FECHADA!" << endl;
            cout << "      Quantidade: " << negociado << " ações" << endl;
            cout << "      Diferença de preço: R$" << (o.preco - venda.preco) << " por ação" << endl;
            cout << "      Lucro desta negociação: R$" << lucro_operacao << endl;

            // Registra lucro da fintech -> diferença entre preço de compra e venda multiplicada pela quantidade negociada
            lucro      += lucro_operacao;

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

        if (negociacoes == 0) {
            cout << "  ✗ Nenhuma venda compatível encontrada." << endl;
        }

        // Se sobrou quantidade na compra, guarda no heap
        if (o.quant > 0)
        {
            cout << "\n[COMPRA] Quantidade restante (" << o.quant << ") armazenada no heap de compras." << endl;
            compras.push(o);
        } else {
            cout << "\n[COMPRA] Ordem completamente negociada!" << endl;
        }
    }
    // Se uma Venda foi inserida
    else {
        cout << "\n[VENDA] Procurando compras compatíveis..." << endl;

        int negociacoes = 0;
        // Enquanto
        // 1. Houver compras
        // 2. A compra mais alta for maior ou igual ao preço da venda
        // 3. A venda ainda tiver quantidade a negociar
        while (compras.empty() == false && compras.top().preco >= o.preco && o.quant > 0)
        {
            // Pega a compra mais cara do heap
            Ordem compra = compras.top();
            compras.pop();

            negociacoes++;
            cout << "  → Compra encontrada! Preço: R$" << compra.preco << " | Quantidade: " << compra.quant << endl;

            // Negocia a menor quantidade entre compra e venda
            int negociado;

            // Se a quantidade que a venda atual quer é menor que a quantidade disponível na compra, negocia o que a venda quer.
            // Se não, negocia o que a compra tem disponível.
            if (o.quant < compra.quant) {
                negociado = o.quant;
            } else {
                negociado = compra.quant;
            }

            int lucro_operacao = (compra.preco - o.preco) * negociado;

            cout << "    ✓ NEGOCIAÇÃO FECHADA!" << endl;
            cout << "      Quantidade: " << negociado << " ações" << endl;
            cout << "      Diferença de preço: R$" << (compra.preco - o.preco) << " por ação" << endl;
            cout << "      Lucro desta negociação: R$" << lucro_operacao << endl;

            // Registra lucro da fintech -> diferença entre preço de compra e venda multiplicada pela quantidade negociada
            lucro        += lucro_operacao;

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

        if (negociacoes == 0) {
            cout << "  ✗ Nenhuma compra compatível encontrada." << endl;
        }

        // Se sobrou quantidade na venda, guarda no heap
        if (o.quant > 0)
        {
            cout << "\n[VENDA] Quantidade restante (" << o.quant << ") armazenada no heap de vendas." << endl;
            vendas.push(o);
        } else {
            cout << "\n[VENDA] Ordem completamente negociada!" << endl;
        }
    }

    cout << "\n>>> Estado atual do Order Book:" << endl;
    cout << "    Lucro acumulado: R$" << lucro << endl;
    cout << "    Ações negociadas: " << negociadas << endl;
    cout << "    Compras pendentes: " << compras.size() << endl;
    cout << "    Vendas pendentes: " << vendas.size() << endl;

    cout << "\n--- HEAPS APÓS PROCESSAMENTO ---" << endl;
    cout << "\n[COMPRAS - Max-Heap (maior preço no topo)]:" << endl;
    exibirHeapCompras();

    cout << "\n[VENDAS - Min-Heap (menor preço no topo)]:" << endl;
    exibirHeapVendas();
}

void OrderBook::imprimir() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║     RESUMO FINAL DO PROCESSAMENTO     ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "Lucro: R$" << lucro << endl;
    cout << "Acoes negociadas: " << negociadas << endl;
    cout << "Compras pendentes: " << compras.size() << endl;
    cout << "Vendas pendentes: " << vendas.size() << endl;
}

void OrderBook::exibirHeapCompras() {
    priority_queue<Ordem, vector<Ordem>, CompararCompra> temp = compras;

    if (temp.empty()) {
        cout << "  (nenhuma compra pendente)" << endl;
        return;
    }

    cout << "  Preço    | Quantidade" << endl;
    cout << "  ---------|-----------" << endl;

    while (!temp.empty()) {
        Ordem o = temp.top();
        temp.pop();
        printf("  R$%-6d | %d\n", o.preco, o.quant);
    }
}

void OrderBook::exibirHeapVendas() {
    priority_queue<Ordem, vector<Ordem>, CompararVenda> temp = vendas;

    if (temp.empty()) {
        cout << "  (nenhuma venda pendente)" << endl;
        return;
    }

    cout << "  Preço    | Quantidade" << endl;
    cout << "  ---------|-----------" << endl;

    while (!temp.empty()) {
        Ordem o = temp.top();
        temp.pop();
        printf("  R$%-6d | %d\n", o.preco, o.quant);
    }
}

void OrderBook::exibirHeaps() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║         ESTADO DOS HEAPS/FILAS        ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

    cout << "\n[COMPRAS PENDENTES - Max-Heap (maior preço no topo)]" << endl;
    exibirHeapCompras();

    cout << "\n[VENDAS PENDENTES - Min-Heap (menor preço no topo)]" << endl;
    exibirHeapVendas();
}

int main() {
    ifstream lista("lista.txt");

    int total = 0;
    lista >> total;

    OrderBook book;

    cout << "\n╔═════════════════════════════════════════╗" << endl;
    cout << "║  SIMULADOR DE BOLSA - FINTECH ORDER BOOK║" << endl;
    cout << "╚═════════════════════════════════════════╝" << endl;
    cout << "\nTotal de ordens a processar: " << total << endl;
    cout << "Iniciando processamento...\n" << endl;

    for (int i = 0; i < total; i++) {
        Ordem o;
        lista >> o.tipo >> o.quant >> o.preco;
        book.inserir(o);
    }

    book.imprimir();
    book.exibirHeaps();
    cout << "\n✓ Processamento concluído com sucesso!\n" << endl;

    return 0;
}
