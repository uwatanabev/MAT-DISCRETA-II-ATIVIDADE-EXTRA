# MD2 - Atividade Prática: Criptografia RSA e Teoria dos Números

## Informações Gerais
* **Disciplina:** Matemática Discreta II (MD2) 
* **Curso:** Engenharia de Software 
* **Instituição:** Universidade de Brasília (UnB), Campus UnB Gama (FGA) 
* **Professor:** Cristiane Loesch de Souza Costa 
* **Turma:** T01 
* **Data da Entrega:** até 18/10/2025 (Meio-dia) 

## Aluno(s)
| Nome | Matrícula |
| :--- | :--- |
| **Bernardo Watanabe Venzi** | **232001120** |
| [NOME DO SEU PAR, SE HOUVER] | [MATRÍCULA DO SEU PAR] |

*(A atividade pode ser realizada individualmente ou em dupla. O cabeçalho do código deve conter nome e matrícula.)*

## Objetivo do Projeto

Este projeto consiste na implementação de quatro questões de desenvolvimento de código em **C ou C++**, abordando temas centrais da Aritmética Modular e Teoria dos Números, aplicados em criptografia e problemas de sincronização.

Todas as implementações foram feitas **sem o uso de bibliotecas externas de criptografia**, com as funções fundamentais programadas pelo(s) aluno(s) (como `mdc`, inverso modular e exponenciação modular).

## Estrutura das Questões

| Questão | Título | Pontuação | Descrição Principal |
| :--- | :--- | :--- | :--- |
| **Q01** | Sistema RSA com Fatoração p de Pollard e Teoremas Modulares | 1,0 ponto | Implementação completa do RSA, incluindo fatoração de Pollard ($\rho$), Algoritmo de Euclides, Euclides Estendido e aplicação seletiva dos Teoremas de Fermat, Euler ou Divisão Euclidiana na exponenciação modular. |
| **Q02** | "Chaves Periódicas" (Sincronização de Ciclos) | 0,5 ponto | Determinação do primeiro ano futuro onde um conjunto de chaves com ciclos periódicos se ativa simultaneamente (cálculo de MMC). Limite: anos de 1 a 50. |
| **Q03** | "A Razão de Eficiência de um Número" | 0,5 ponto | Cálculo da Razão de Eficiência ($\sigma(N)/\tau(N)$) a partir da fatoração prima de $N$. |
| **Q04** | Análise de Código e Divisão Modular | 0,5 ponto (bônus) | Completar trechos de código em C para funções de `mdc`, `inversoModular` e `powMod`, e realizar a análise de saída e Teoremas aplicados. |

**Total de Pontos:** até 2,0 pontos na avaliação P2.

## Instruções de Execução
*(Adapte esta seção com base em como você estruturou seus arquivos C/C++.)*

1.  **Pré-requisitos:** Compilador C/C++ (e.g., GCC, G++).
2.  **Compilação:** Navegue até o diretório do projeto e compile os arquivos:
    ```bash
    # Exemplo para um único arquivo (se for o caso)
    g++ -o rsa_project main.cpp 
    
    # Exemplo para múltiplos arquivos (se for o caso)
    g++ -o rsa_project q1_rsa.cpp q2_periodic.cpp q3_razao.cpp main.cpp
    ```
3.  **Execução:**
    ```bash
    ./rsa_project
    ```
4.  **Interação:** O programa irá solicitar as entradas necessárias para cada questão (e.g., $N_1$ e $N_2$ para RSA, ciclos para Q02, $N$ para Q03).

## Requisitos e Critérios de Avaliação (Lembretes)

Para cada questão, é crucial:
* **Passo a Passo Visível:** Imprimir os cálculos e decisões intermediárias de forma clara, incluindo iterações de algoritmos (Pollard's $\rho$, Euclides), fatores primos e a aplicação dos teoremas modulares.
* **Legibilidade:** Numerar passos e incluir legendas explicativas na saída[cite: 302, 303].
* **Justificativa no Código:** Comentar as decisões de código, especialmente a escolha de teoremas modulares ou algoritmos[cite: 77, 305].
* **Validação:** Solicitar entradas e validar restrições (ex: $N_{i}$ de 3-4 dígitos, ciclo de ano $1$ a $50$)[cite: 25, 86, 307].
* **Confirmação de Resultados:** Confirmar que a mensagem decifrada é idêntica à original na Q01[cite: 76].
