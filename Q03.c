#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição de tipo para consistência
typedef long long ll;

// Protótipos
long long power(int base, int exp);
void run_questao03();

// =========================================================================
// FUNÇÕES AUXILIARES (FÓRMULA FECHADA, com retorno LL para precisão)
// =========================================================================

/**
 * @brief Função para calcular a potência, necessária para sigma(N).
 * Usamos long long para evitar overflow com números maiores.
 */
long long power(int base, int exp) {
  long long res = 1;
  for (int i = 0; i < exp; ++i) {
    res *= base;
  }
  return res;
}

// =========================================================================
// QUESTÃO 03: RAZÃO DE EFICIÊNCIA (Execução Principal)
// =========================================================================

/**
 * @brief Resolve a Questão 03: Calcula Tau(N), Sigma(N) e a Razão de Eficiência.
 */
void run_questao03() {
    int n;
    printf("\n=========================================================\n");
    printf("            QUESTAO 03: RAZAO DE EFICIENCIA              \n");
    printf("=========================================================\n");
    printf("Objetivo: Calcular Sigma(N) / Tau(N).\n");

    printf("Digite um inteiro N (1 <= N <= 100000): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100000) {
        printf("Entrada inválida. N deve estar entre 1 e 100000.\n");
        return;
    }

    if (n == 1) {
        printf("\n--- PASSO A PASSO DA FATORACAO ---\n");
        printf("N = 1\n");
        printf("Fatoracao Prima: N=1 (caso base)\n");
        printf("\n--- CALCULOS INTERMEDIARIOS ---\n");
        printf("Tau(N) (Numero de divisores): 1\n");
        printf("Sigma(N) (Soma dos divisores): 1\n");
        printf("\n--- RESULTADO FINAL ---\n");
        printf("Razao de Eficiencia (Sigma/Tau): 1.00\n");
        return;
    }

    // Variáveis de Fatoração e Cálculo
    int temp_n = n;
    ll tau_n = 1;
    ll sigma_n = 1;

    printf("\n--- PASSO A PASSO DA FATORACAO ---\n");
    printf("N = %d\n", n);

    // Fatoração usando Trial Division
    for (int i = 2; i * i <= temp_n; ++i) {
        if (temp_n % i == 0) {
            int count = 0;
            int p = i;
            while (temp_n % i == 0) {
                temp_n /= i;
                count++;
            }
            
            // Exibe o fator (Formato Antigo)
            printf("Fator Primo: %d (Expoente: %d)\n", p, count);

            // Cálculo de Tau(N)
            tau_n *= (count + 1);
            
            // Cálculo de Sigma(N) - Usando a FÓRMULA FECHADA (Assumindo que LL aguenta)
            // Lógica: sigma_n *= ((p^(a+1) - 1) / (p - 1))
            ll termo = (power(p, count + 1) - 1) / (p - 1);
            sigma_n *= termo;
        }
    }
    
    // Trata o último fator primo
    if (temp_n > 1) {
        int p = temp_n;
        int count = 1;
        printf("Fator Primo: %d (Expoente: %d)\n", p, count);
        tau_n *= (count + 1);
        ll termo = (power(p, count + 1) - 1) / (p - 1);
        sigma_n *= termo;
    }

    // --- Cálculo da Razão de Eficiência ---
    printf("\n--- CALCULOS INTERMEDIARIOS ---\n");
    printf("Tau(N) (Numero de divisores): %lld\n", tau_n);
    printf("Sigma(N) (Soma dos divisores): %lld\n", sigma_n);

    printf("\n--- RESULTADO FINAL ---\n");
    
    double razao = 0.0;
    if (tau_n != 0) {
        razao = (double)sigma_n / tau_n;
    }
    
    // Usamos fabs (de math.h) e %f
    printf("Razao de Eficiencia (Sigma/Tau): %.2f\n", fabs(razao)); 
}

int main() {
    run_questao03();
    printf("\n--- FIM COMPLETO DA ATIVIDADE (Questao 03) ---\n");
    return 0;
}