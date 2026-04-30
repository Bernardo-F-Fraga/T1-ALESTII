# Perguntas de Apresentação — Simulador de Bolsa (Fintech Order Book)

---

**1.** Por que o heap de compras é um max-heap e o heap de vendas é um min-heap? O que aconteceria com o lucro da fintech se fosse o contrário?

---

**2.** Ao chegar a ordem `C 5 100`, o min-heap de vendas tem no topo `V 3 80`. Descreva passo a passo o que o código faz: quantas ações são negociadas, qual o lucro gerado, e o que acontece com o restante de cada ordem.

---

**3.** Por que a fintech realiza **todos** os negócios possíveis a cada nova ordem que chega, em vez de esperar acumular ordens e processar em lote?

---

**4.** Qual é a complexidade de tempo para inserir e casar uma única ordem? E para processar todas as N ordens no pior caso? Justifique com base na estrutura usada.

---

**5.** O que os comparadores `CompararCompra` e `CompararVenda` fazem e por que eles são necessários como `struct` com `operator()` em vez de uma função comum?

---
---

# Gabarito

**1.** O max-heap de compras mantém o comprador disposto a pagar **mais** no topo, e o min-heap de vendas mantém o vendedor disposto a aceitar **menos** no topo. Assim, ao casar ordens, a diferença entre preço de compra e preço de venda é sempre a máxima possível — que é exatamente o lucro da fintech. Se os heaps fossem invertidos, o algoritmo casaria os piores preços primeiro, minimizando o lucro (ou deixando de casar ordens que poderiam ser casadas).

**2.** A quantidade negociada é `min(5, 3) = 3` ações. O lucro gerado é `(100 - 80) × 3 = 60`. A ordem de venda é totalmente consumida e removida do heap. A ordem de compra ainda tem `5 - 3 = 2` ações restantes; o `while` continua tentando casar com a próxima venda disponível. Se não houver mais vendas compatíveis, as 2 ações restantes da compra são empurradas para o heap de compras.

**3.** O enunciado especifica que a cada nova operação todos os negócios possíveis devem ser realizados imediatamente. Isso reflete o funcionamento real de um order book: a janela de oportunidade é instântanea — uma ordem que chega e pode ser casada agora pode não ser casável depois, pois novas ordens (com preços diferentes) chegam continuamente.

**4.** Cada inserção ou remoção num heap custa `O(log n)`, onde n é o número de ordens pendentes. No pior caso, uma única ordem nova casa com todas as n ordens do heap oposto, resultando em `O(n log n)` para aquela ordem. Para N ordens no total, o pior caso geral é `O(N log N)`, pois cada ordem entra e sai do heap no máximo uma vez, e cada operação de heap custa `O(log N)`.

**5.** `CompararCompra` retorna `true` quando `a.preco < b.preco`, fazendo com que o elemento de **maior** preço fique no topo (max-heap). `CompararVenda` retorna `true` quando `a.preco > b.preco`, fazendo com que o elemento de **menor** preço fique no topo (min-heap). O `std::priority_queue` exige um **tipo** como terceiro parâmetro de template (não uma função), por isso o comparador precisa ser uma `struct` com `operator()` — essa é a forma idiomática em C++ para passar comportamento como parâmetro de template.
