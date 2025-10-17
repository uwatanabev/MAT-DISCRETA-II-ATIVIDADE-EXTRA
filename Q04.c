#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

// Protótipos das funções auxiliares necessárias (simulando a estrutura da questao)
ll mdcComPassos(ll a, ll b);
ll estendido_euclides_passos(ll a, ll b, ll *x, ll *y);
ll inversoModular(ll a, ll m);
ll powMod(ll base, ll exp, ll mod); 

// =========================================================================
// FUNÇÕES BASE (Preenchidas com as linhas faltantes)
// =========================================================================

/**
 * @brief Função para calcular o máximo divisor comum (MDC) com exibição dos passos.
 */
ll mdcComPassos (ll a, ll b) {
    ll resto;
    printf("\n--- ALGORITMO DE EUCLIDES ---\n");
    while (b != 0) { // Linha 9: while (b != 0)
        resto = a % b;
        printf("Algoritmo de Euclides: %lld mod %lld = %lld\n", a, b, resto);
        a = b; // Linha 11 (Implícita): a = b
        b = resto; // [1] Linha 14: b = resto
    }
    return a;
}

/**
 * @brief Algoritmo Estendido de Euclides com passos.
 */
ll estendido_euclides_passos(ll a, ll b, ll *x, ll *y) {
    ll x1 = 0, y1 = 1; ll xx = 1, yy = 0; 
    if (b == 0) { *x = 1; *y = 0; return a; }
    ll q, t;
    while (b != 0) { 
        q = a / b;
        t = x1; x1 = xx - q * x1; xx = t; 
        t = y1; y1 = yy - q * y1; yy = t; 
        t = b; b = a % b; a = t;
    }
    *x = xx; *y = yy; return a;
}


/**
 * @brief Calcula o inverso modular usando o Algoritmo Estendido de Euclides.
 */
ll inversoModular(ll a, ll m) {
    ll m0 = m; 
    ll x1, y1;
    ll g;

    // [2] Linha 23: Chamada para verificar MDC
    g = mdcComPassos(a, m); 

    if (g != 1) return -1;
    
    // Assumindo que a implementação real chamaria extended_gcd para obter x1 e y1
    estendido_euclides_passos(a, m, &x1, &y1); 

    
    if (x1 < 0) { // [3] Linha 36: if (x1 < 0)
        x1 += m0; // Linha 38 (Implícita): x1 += m0;
    }

    printf("\nSubstituindo, temos que o inverso de %lld em %lld e %lld.\n\n", a, m0, x1);
    return x1;
}

/**
 * @brief Calcula a potência modular (a^x mod n) usando Exponenciacao por Quadrados.
 */
ll powMod(ll base, ll exp, ll mod) {
    ll res = 1;
    ll b = base % mod;
    while (exp > 0) {
        if (exp & 1) { // [4] Linha 45: if (exp & 1)
            res = (res * b) % mod;
        } 
        b = (b * b) % mod;
        exp >>= 1;
    }
    return res;
}

// =========================================================================
// FUNÇÃO MAIN (Simulando o teste de mesa da questão)
// =========================================================================

int main() {
    ll H = 7, G = 3, Zn = 11, x = 10, n1 = 13;
    
    printf("--- TESTE QUESTAO 04 ---\n");
    printf("Dados: H=%lld, G=%lld, Zn=%lld, x=%lld, n1=%lld\n\n", H, G, Zn, x, n1);

    // Linhas 71-78 da Questão:
    
    // [5] Linha 72: Calculo do Inverso
    ll inverso = inversoModular(G, Zn); // int inverso = inversoModular(G, Zn);
    
    if (inverso == -1) {
        printf("A divisao modular nao existe.\n");
        return 1;
    }

    // Calculo de a = (H/G) mod Zn
    ll a = (H * inverso) % Zn;

    printf("Fazendo a multiplicacao modular: %lld * %lld mod %lld = %lld\n", H, inverso, Zn, a);
    
    // [6] Linha 78: Calculo da Congruencia Final
    ll resultado = powMod(a, x, n1); // int resultado = powMod(a, x, n1); 

    printf("\nValor final da congruencia: %lld\n", resultado);
    
    printf("\n----------------------------------------------------\n");
    printf("RESPOSTAS (V/F) DA QUESTAO 4\n");
    printf("----------------------------------------------------\n");
    
    printf("(V) O algoritmo de Euclides estendido e utilizado para calcular o inverso modular de um numero.\n");
    printf("(F) Se mdc(G, Zn) nao e 1, o programa ainda consegue encontrar o inverso de G em Zn.\n");
    printf("(V) A operacao (H * inverso) mod Zn representa a divisao modular de H por G.\n");
    printf("(V) Se n1 for primo, o codigo aplica o Pequeno Teorema de Fermat para simplificar o calculo de a^x mod n1.\n");
    printf("(F) A funcao powMod implementa o calculo de potencia modular utilizando multiplicacoes diretas sem otimizacao.\n");
    printf("(V) Quando o resultado do inverso e negativo, o codigo ajusta o valor somando o modulo m0.\n");
    printf("(F) O calculo de phi(n1) (funcao totiente de Euler) e utilizado apenas quando n1 nao e primo.\n");
    printf("----------------------------------------------------\n");


    return 0;
}