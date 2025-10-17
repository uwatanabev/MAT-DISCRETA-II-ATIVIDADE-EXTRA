#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Definição de tipo para consistência
typedef long long ll;

// Protótipos das funções da Questão 02
ll mdc_sem_print(ll a, ll b);
ll mmc(ll a, ll b);
void limpar_buffer();
void run_questao02();

// =========================================================================
// FUNÇÕES DE ARITMÉTICA MODULAR (Reutilizadas da Questão 01)
// =========================================================================

/**
 * @brief Versão do MDC sem prints. Essencial para o cálculo do MMC.
 */
ll mdc_sem_print(ll a, ll b) {
    ll resto;
    // Garante que ambos sejam positivos
    a = llabs(a);
    b = llabs(b);
    
    if (b > a) { ll temp = a; a = b; b = temp; }
    while (b != 0) { 
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

/**
 * @brief Calcula o Mínimo Múltiplo Comum (MMC) de dois números.
 * Fórmula: MMC(a, b) = (|a * b|) / MDC(a, b).
 */
ll mmc(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    // O cálculo é feito com divisão primeiro para evitar overflow no a * b
    return llabs(a / mdc_sem_print(a, b) * b);
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


// =========================================================================
// QUESTÃO 02: CHAVES PERIÓDICAS (Execução Principal)
// =========================================================================

/**
 * @brief Resolve a Questão 02: Encontra o primeiro ano de sincronização (MMC).
 * Requisitos: 1 <= N <= 10, 2 <= C_i <= 20, X <= 50.
 */
void run_questao02() {
    int N;
    const int LIMITE_MAXIMO = 50;
    
    printf("\n=========================================================\n");
    printf("                QUESTAO 02: CHAVES PERIODICAS            \n");
    printf("=========================================================\n");
    printf("Objetivo: Encontrar o MMC dos ciclos C (max 50 anos).\n");

    // 1. Leitura de N (Número de Chaves)
    do {
        printf("Insira o numero de chaves N (1 <= N <= 10): ");
        if (scanf("%d", &N) != 1 || N < 1 || N > 10) {
            printf("[ERRO] N deve ser entre 1 e 10. Tente novamente.\n");
            limpar_buffer();
        } else {
            break;
        }
    } while (1);

    ll ciclos[10];
    printf("Insira os %d ciclos C (2 <= C <= 20), separados por espaco: ", N);
    limpar_buffer(); 

    // 2. Leitura dos Ciclos C_i com validação
    int valido = 1;
    for (int i = 0; i < N; i++) {
        if (scanf("%lld", &ciclos[i]) != 1 || ciclos[i] < 2 || ciclos[i] > 20) {
            printf("\n[ERRO] Ciclo C[%d] invalido. Deve ser entre 2 e 20.\n", i + 1);
            valido = 0;
            break;
        }
    }
    limpar_buffer(); 
    
    if (!valido) {
        printf("\n[SAIDA]\nImpossibilidade: Dados de entrada invalidos.\n");
        return;
    }

    // 3. Cálculo do MMC sequencial (Primeiro Ano de Sincronização)
    ll primeiro_ano_sincronizado = 1; // Começa com 1 para garantir o MMC inicial
    
    // Calcula o MMC do primeiro ciclo com 1.
    if (N > 0) {
         primeiro_ano_sincronizado = ciclos[0];
    }
    
    printf("\n[PASSO A PASSO DO MMC]\n");
    printf("MMC Inicial: %lld\n", primeiro_ano_sincronizado);

    for (int i = 1; i < N; i++) {
        ll mmc_anterior = primeiro_ano_sincronizado;
        
        // Calculamos o MMC acumulado
        primeiro_ano_sincronizado = mmc(primeiro_ano_sincronizado, ciclos[i]);

        printf("Passo %d: MMC(%lld, %lld) = %lld\n", 
               i, mmc_anterior, ciclos[i], primeiro_ano_sincronizado);
        
        // Otimização: se o MMC ultrapassou o limite, não precisamos calcular mais.
        if (primeiro_ano_sincronizado > LIMITE_MAXIMO) {
            break; 
        }
    }

    // 4. Verificação do Limite de Ano (X <= 50) e Saída
    if (primeiro_ano_sincronizado > 0 && primeiro_ano_sincronizado <= LIMITE_MAXIMO) {
        printf("\n[SAIDA]\n");
        printf("O primeiro ano sincronizado (X > 0) dentro do limite de %d anos e: %lld\n", 
               LIMITE_MAXIMO, primeiro_ano_sincronizado);
    } else {
        printf("\n[SAIDA]\n");
        printf("Impossibilidade: Nao existe ano sincronizado (X) entre 1 e %d. O MMC encontrado e %lld.\n", 
               LIMITE_MAXIMO, primeiro_ano_sincronizado);
    }
}

int main() {
    run_questao02();
    printf("\n--- FIM COMPLETO DA ATIVIDADE (Questao 02) ---\n");
    return 0;
}