#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Definição para usar long long para cálculos maiores
typedef long long ll;

// Protótipos das funções
ll mdc(ll a, ll b);
ll mdc_sem_print(ll a, ll b); 
ll pollard_rho(ll n);
ll estendido_euclides(ll a, ll b, ll *x, ll *y);
ll estendido_euclides_sem_print(ll a, ll b, ll *x, ll *y); 
ll inverso_modular(ll a, ll m);
ll inverso_modular_sem_print(ll a, ll m); 
ll powMod(ll base, ll exp, ll mod);
ll aplicar_teorema_modular(ll base, ll exp, ll mod, ll p, ll q);
int is_prime(ll n);
void limpar_buffer();
void run_etapa1_test(ll *p_out, ll *q_out);
void run_etapa2(ll p, ll q);
void run_etapa3(ll n, ll e, ll d, ll p, ll q);

// FUNÇÕES DE UTILIDADE E ARITMÉTICA MODULAR

/**
 * @brief Limpa o buffer de entrada.
 */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * @brief Checa se n é primo (simplificado).
 */
int is_prime(ll n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (ll i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    return 1;
}

/**
 * @brief Implementação do Algoritmo de Euclides para calcular o MDC de a e b.
 * Exibe o passo a passo (Requisito 2).
 */
ll mdc(ll a, ll b) {
    ll resto;
    printf("\n--- Inicio do Algoritmo de Euclides (mdc(%lld, %lld)) ---\n", a, b);
    
    if (llabs(b) > llabs(a)) {
        ll temp = a; a = b; b = temp;
    }

    while (b != 0) { 
        resto = a % b;
        printf("Passo: %lld = %lld * %lld + %lld\n", a, a / b, b, resto); 
        a = b;
        b = resto;
    }
    printf("--- Fim do Algoritmo de Euclides (MDC = %lld) ---\n", llabs(a));
    return llabs(a);
}

/**
 * @brief Versão do MDC sem prints, usada apenas internamente no main.
 */
ll mdc_sem_print(ll a, ll b) {
    ll resto;
    if (llabs(b) > llabs(a)) {
        ll temp = a; a = b; b = temp;
    }
    while (b != 0) { 
        resto = a % b;
        a = b;
        b = resto;
    }
    return llabs(a);
}


/**
 * @brief Implementação do Algoritmo Estendido de Euclides.
 * Exibe o passo a passo (Requisito 3).
 */
ll estendido_euclides(ll a, ll b, ll *x, ll *y) {
    ll mdc_val;
    ll a0 = a, m0 = b; 
    ll x1 = 0, y1 = 1; 
    ll xx = 1, yy = 0; 

    printf("\n--- Inicio do Algoritmo Estendido de Euclides (Inverso Modular) ---\n");
    printf("Valores iniciais: E=%lld, z=%lld\n", a, b);
    if (b == 0) { *x = 1; *y = 0; return a; }
    
    ll q, t, temp_x, temp_y;
    
    while (b != 0) { 
        q = a / b;
        
        temp_x = xx - q * x1; 
        temp_y = yy - q * y1;

        xx = x1; x1 = temp_x;
        yy = y1; y1 = temp_y;

        t = b;
        b = a % b;
        a = t;

        printf("Iteracao (a=%lld, b=%lld): Quociente q=%lld, Coeficientes (x, y) = (%lld, %lld)\n", a, b, q, xx, yy);
    }
    
    mdc_val = a;
    *x = xx; *y = yy; 
    printf("MDC encontrado: %lld. Coeficiente x (Inverso) = %lld, Coeficiente y = %lld\n", mdc_val, *x, *y);
    printf("--- Fim do Algoritmo Estendido de Euclides ---\n");
    return mdc_val;
}

/**
 * @brief Versão do Algoritmo Estendido de Euclides sem prints.
 */
ll estendido_euclides_sem_print(ll a, ll b, ll *x, ll *y) {
    ll x1 = 0, y1 = 1, xx = 1, yy = 0, q, t, temp_x;
    if (b == 0) { *x = 1; *y = 0; return a; }
    while (b != 0) { 
        q = a / b;
        temp_x = xx - q * x1; 
        xx = x1; x1 = temp_x;
        t = b;
        b = a % b;
        a = t;
    }
    *x = xx; *y = yy; 
    return a;
}

/**
 * @brief Calcula o inverso modular D = E^(-1) mod z(n).
 */
ll inverso_modular(ll a, ll m) {
    ll x, y;
    ll m0 = m; 
    ll mdc_val = estendido_euclides(a, m, &x, &y); 

    if (mdc_val != 1) {
        printf("\nERRO: O inverso modular de %lld mod %lld nao existe pois mdc(E, z(n)) = %lld != 1.\n", a, m, mdc_val);
        return -1; 
    }
    
    ll inv = x;
    if (inv < 0) { 
        inv += m0;
        printf("\n[AJUSTE] Inverso negativo (%lld) ajustado: %lld + %lld = %lld\n", x, x, m0, inv);
    }
    
    printf("\n[RESULTADO DO INVERSO]: O inverso de %lld modulo %lld e %lld (D).\n", a, m0, inv);
    return inv;
}

/**
 * @brief Calcula o inverso modular D = E^(-1) mod z(n) SEM PRINTS.
 */
ll inverso_modular_sem_print(ll a, ll m) {
    ll x, y;
    ll m0 = m;
    ll mdc_val = estendido_euclides_sem_print(a, m, &x, &y);

    if (mdc_val != 1) { return -1; }
    
    ll inv = x;
    if (inv < 0) { inv += m0; }
    return inv;
}

// ETAPA 1: FATORAÇÃO RHO DE POLLARD

/**
 * @brief Implementa o Método Rho de Pollard.
 * Exibe o passo a passo (Requisito 1).
 */
ll pollard_rho(ll n) {
    ll x = 2, y = 2; // Semente x0 = 2
    ll d = 1;
    ll i = 0;

    printf("\n--- Inicio do Metodo Rho de Pollard (N=%lld) ---\n", n);
    printf("Funcao de iteracao: g(x) = (x^2 + 1) mod N. Teste: mdc(|x_2i - x_i|, N).\n");

    if (n % 2 == 0) return 2; 

    while (d == 1 || d == n) {
        x = (x * x + 1) % n;
        y = (y * y + 1) % n;
        y = (y * y + 1) % n;

        // Note que o mdc é chamado aqui e gera seu próprio passo a passo.
        d = mdc(llabs(x - y), n); 
        i++;

        printf("\nIteracao %lld:\n", i);
        printf("  x_i = %lld, x_2i = %lld\n", x, y);
        printf("  Diferenca para MDC = %lld\n", llabs(x - y));
        printf("  MDC encontrado (d) = %lld\n", d);

        if (d != 1 && d != n) {
            printf("\n[SUCESSO] Fator nao trivial encontrado: %lld.\n", d);
            return d;
        }

        if (i > 5000) { 
            printf("\n[FALHA] Maximo de iteracoes atingido ou fator muito grande.\n");
            return -1; 
        }
    }
    return d;
}

/**
 * @brief Executa a Etapa 1 completa: Leitura, validação e fatoração.
 */
void run_etapa1_test(ll *p_out, ll *q_out) {
    ll n1, n2;
    ll p = 0, q = 0;

    printf("\n=========================================================\n");
    printf("                ETAPA 1: FATORACAO RHO                  \n");
    printf("=========================================================\n");

    // Lógica de Entrada de Dados e Restrições
    do {
        printf("Insira o primeiro numero composto N1 (3 ou 4 digitos, entre 100 e 9999): ");
        if (scanf("%lld", &n1) != 1) { limpar_buffer(); n1 = 0; }
        printf("Insira o segundo numero composto N2 (3 ou 4 digitos, distintos de N1): ");
        if (scanf("%lld", &n2) != 1) { limpar_buffer(); n2 = 0; }
        limpar_buffer(); 

        // Verificação de faixas e distinção (Requisito 1)
        if (n1 < 100 || n1 > 9999 || n2 < 100 || n2 > 9999) {
            printf("[ERRO] Restricao: Ambos os numeros devem ser entre 100 e 9999. Tente novamente.\n");
            continue;
        }
        if (n1 == n2) {
             printf("[ERRO] Restricao: N1 e N2 devem ser distintos. Tente novamente.\n");
             continue;
        }
        // Aviso se não for composto
        if (is_prime(n1) || is_prime(n2)) { 
            printf("[AVISO] Pelo menos um dos numeros (N1/N2) parece ser primo. Recomenda-se numeros COMPOSTOS para o Rho.\n");
        }
        printf("\n--- Aviso: O metodo Rho e mais eficiente se Ni for produto de primos distintos ---\n");
        break;
    } while (1);

    // 1. Fatoração de N1 (para encontrar P)
    ll fator_p_raw = pollard_rho(n1);
    ll fator_p_other = (fator_p_raw > 0 && fator_p_raw != n1) ? n1 / fator_p_raw : 0;

    if (fator_p_raw > 0 && fator_p_raw != n1) {
        ll fator_selecionado = 0;
        
        // Prioriza o fator primo.
        if (is_prime(fator_p_raw)) {
            fator_selecionado = fator_p_raw;
        } else if (is_prime(fator_p_other)) {
            fator_selecionado = fator_p_other;
        } else {
            // Caso de falha: usar o outro fator (fallback)
            printf("\n[FALHA DE SELECAO N1] O fator encontrado (%lld) e seu par (%lld) nao sao primos.\n", fator_p_raw, fator_p_other);
            fator_selecionado = fator_p_other; 
        }
        
        p = fator_selecionado; 
        
        // Ajusta a impressão para mostrar o fator correto e seu par
        ll p_par = n1 / p;
        printf("\n-> Fator P (de N1=%lld) selecionado: %lld. O outro fator e: %lld\n", n1, p, p_par);
    } else {
        printf("\nFALHA NA FATORACAO N1. Usando P=17 (arbitrario) como fallback.\n");
        p = 17; 
    }

    // 2. Fatoração de N2 (para encontrar Q)
    ll fator_q_raw = pollard_rho(n2);
    ll fator_q_other = (fator_q_raw > 0 && fator_q_raw != n2) ? n2 / fator_q_raw : 0;

    if (fator_q_raw > 0 && fator_q_raw != n2) {
        ll fator_selecionado = 0;

        // Prioriza o fator primo.
        if (is_prime(fator_q_raw)) {
            fator_selecionado = fator_q_raw;
        } else if (is_prime(fator_q_other)) {
            fator_selecionado = fator_q_other;
        } else {
            printf("\n[FALHA DE SELECAO N2] O fator encontrado (%lld) e seu par (%lld) nao sao primos.\n", fator_q_raw, fator_q_other);
            fator_selecionado = fator_q_other; 
        }

        q = fator_selecionado; 
        
        // Ajusta a impressão para mostrar o fator correto e seu par
        ll q_par = n2 / q;
        printf("\n-> Fator Q (de N2=%lld) selecionado: %lld. O outro fator e: %lld\n", n2, q, q_par);
    } else {
        printf("\nFALHA NA FATORACAO N2. Usando Q=19 (arbitrario) como fallback.\n");
        q = 19; 
    }

    // Saída final dos Primos RSA (Requisito 1)
    printf("\n[PRIMOS RSA SELECIONADOS PARA ETAPA 2]\n");
    printf("P = %lld\n", p);
    printf("Q = %lld\n", q);
    
    // Validação de segurança e Fallback para Etapa 2
    if (p <= 1 || q <= 1 || p == q || p < 10 || q < 10) {
        printf("\n[AVISO CRITICO DE RSA] P ou Q e invalido, igual, ou muito pequeno. Forcando P=17, Q=19 para prosseguir a Etapa 2.\n");
        p = 17; q = 19;
    }
    
    *p_out = p;
    *q_out = q;
}

// ETAPA 2: GERAÇÃO DE CHAVES RSA

/**
 * @brief Executa a Etapa 2: Geração das chaves n, z, E, D.
 */
void run_etapa2(ll p, ll q) {
    ll n, z, e, d;
    
    printf("\n\n=========================================================\n");
    printf("                 ETAPA 2: GERACAO DE CHAVES RSA          \n");
    printf("  Primos Recebidos: P=%lld, Q=%lld\n", p, q);
    printf("=========================================================\n");

    // 1. Cálculo de n e z(n)
    n = p * q;                                 
    z = (p - 1) * (q - 1);                     

    printf("[1. CALCULOS MODULARES]\n");
    printf("Modulo n = p * q = %lld * %lld = %lld\n", p, q, n);
    printf("Totiente de Euler z(n) = (p-1) * (q-1) = %lld * %lld = %lld\n", p - 1, q - 1, z);

    // 2. Escolha do Expoente Público E
    e = 3; 
    printf("\n[2. ESCOLHA DO EXPOENTE PUBLICO E]\n");
    
    // O mdc é chamado aqui, o que exibe o passo a passo da escolha (Requisito 2).
    while (e < z) { 
        if (mdc(e, z) == 1) { 
            printf("\n[SUCESSO] E = %lld, pois e o menor E > 1 tal que mdc(E, z(n)=%lld) = 1\n", e, z);
            break;
        }
        e += 2; 
    }
    
    if (e >= z) {
        printf("\nERRO: Nao foi possivel encontrar um E adequado no intervalo. Usando E=5.\n");
        e = 5; 
    }

    // 3. Cálculo do Expoente Privado D
    printf("\n[3. CALCULO DO EXPOENTE PRIVADO D]\n");
    printf("Objetivo: Encontrar D tal que D * %lld = 1 mod %lld\n", e, z);
    d = inverso_modular(e, z); // Usa Algoritmo Estendido de Euclides
    
    // 4. Impressão das Chaves (Requisito 2)
    printf("\n[CHAVES RSA GERADAS]\n");
    printf("Chave Publica: (n=%lld, E=%lld)\n", n, e);
    printf("Chave Privada: (n=%lld, D=%lld)\n", n, d);
}

// ETAPA 3: CRIPTOGRAFIA/DECRIPTOGRAFIA

/**
 * @brief Potenciação Modular Otimizada (Exponenciação por Quadrados / binário).
 * Exibe o passo a passo (Requisito 4).
 */
ll powMod(ll base, ll exp, ll mod) {
    ll res = 1;
    ll b = base % mod;
    ll exp_original = exp;

    printf("\n[INICIO DA EXPONENCIACAO MODULAR: %lld^%lld mod %lld]\n", base, exp_original, mod);
    printf("Inicial: res = 1, base_mod = %lld, exp = %lld\n", b, exp);

    while (exp > 0) {
        if (exp & 1) { // Verifica o bit menos significativo do expoente
            printf("  Bit 1 (exp impar): res = (res * base_mod) mod %lld = (%lld * %lld) mod %lld = %lld\n", 
                   mod, res, b, mod, (res * b) % mod);
            res = (res * b) % mod;
        } 
        
        printf("  Quadrado (base^2): base_mod = (base_mod * base_mod) mod %lld = (%lld * %lld) mod %lld = %lld\n", 
               mod, b, b, mod, (b * b) % mod);
        b = (b * b) % mod;
        
        exp >>= 1; // Desloca o expoente para a direita (exp = exp / 2)
        printf("  Novo exp (>>= 1): %lld\n", exp);
    }
    printf("[FIM DA EXPONENCIACAO MODULAR: Resultado = %lld]\n", res);
    return res;
}

/**
 * @brief Aplica Exponenciação Modular Otimizada, indicando o teorema aplicado.
 * Seleciona PTF, Teorema de Euler ou Divisão Euclidiana (Requisito 4).
 */
ll aplicar_teorema_modular(ll base, ll exp, ll mod, ll p, ll q) {
    ll new_exp = exp;
    int teorema_aplicado = 0;
    ll z_n = (p - 1) * (q - 1); 

    // 1. Verificar Pequeno Teorema de Fermat (PTF) - Se n for primo
    if (is_prime(mod)) {
        printf("\n[APLICANDO TEOREMA MODULAR: Pequeno Teorema de Fermat (n primo)]\n");
        printf("  Modulo n=%lld eh primo. Reduzindo o expoente E ou D mod (n-1).\n", mod);
        new_exp = exp % (mod - 1);
        teorema_aplicado = 1;
    } 
    
    // 2. Teorema de Euler: Se mdc(M, n) = 1, reduz o expoente mod z(n).
    if (!teorema_aplicado) {
        // O mdc é chamado aqui para ter o passo a passo da checagem.
        if (mdc(base, mod) == 1) { 
            printf("\n[APLICANDO TEOREMA MODULAR: Teorema de Euler]\n");
            printf("  mdc(Base=%lld, Modulo=%lld) = 1. Reduzindo o expoente E ou D mod z(n)=%lld.\n", base, mod, z_n);
            new_exp = exp % z_n;
            teorema_aplicado = 1;
        }
    }

    // 3. Teorema da Divisão Euclidiana (Método Padrão)
    if (!teorema_aplicado) {
        printf("\n[APLICANDO TEOREMA MODULAR: Divisao Euclidiana (Metodo Padrao)]\n");
        printf("  Nenhuma otimizacao por PTF/Euler. Utilizando o expoente %lld no algoritmo de Exponenciacao por Quadrados.\n", exp);
        new_exp = exp;
    }

    ll resultado = powMod(base, new_exp, mod);
    return resultado;
}


/**
 * @brief Implementa a Etapa 3 completa: Codificação e Decodificação.
 */
void run_etapa3(ll n, ll e, ll d, ll p, ll q) {
    printf("\n\n=========================================================\n");
    printf("               ETAPA 3: CRIPTO/DECRIPTO RSA             \n");
    printf("=========================================================\n");

    char mensagem_input[100]; // Armazena a leitura bruta
    char mensagem_original[100] = ""; // Armazena a mensagem limpa e processada
    
    printf("Insira a mensagem (apenas letras MAIUSCULAS e espacos): ");
    
    // Usa scanf para uma leitura mais robusta após o print dos passos
    // Limpa o newline do buffer deixado pelo último printf da main
    if (scanf(" %99[^\n]", mensagem_input) != 1) { 
        printf("\n[AVISO] Nenhuma mensagem valida lida.\n");
        return;
    }
    
    // 1. PRÉ-CODIFICAÇÃO E LIMPEZA
    int len_input = strlen(mensagem_input);
    int k = 0;
    for (int i = 0; i < len_input; i++) {
        char c = mensagem_input[i];
        if (c >= 'A' && c <= 'Z') {
            mensagem_original[k++] = c;
        } else if (c == ' ') {
            mensagem_original[k++] = c;
        }
    }
    mensagem_original[k] = '\0'; 
    int len = k; // Novo comprimento da mensagem válida
    
    if (len == 0) {
        printf("\n[AVISO] A mensagem digitada resultou em uma string vazia apos a limpeza.\n");
        printf("\n[CONFIRMACAO DE RESULTADO]\nSUCESSO! (String Original vazia e String Decifrada vazia).\n");
        return;
    }
    
    ll *m_blocos = (ll *)malloc(len * sizeof(ll));
    ll *c_blocos = (ll *)malloc(len * sizeof(ll));


    printf("\n[1. PRE-CODIFICACAO] A=11, B=12... Z=36, Espaco=00\n");
    printf("Mensagem Original: %s\n", mensagem_original);
    printf("Codigos M (blocos de 2 digitos): ");
    
    for (int i = 0; i < len; i++) {
        char c = mensagem_original[i];
        if (c >= 'A' && c <= 'Z') {
            m_blocos[i] = c - 'A' + 11; // A=11, B=12, ..., Z=36
        } else if (c == ' ') {
            m_blocos[i] = 0; // Espaço=00
        }
        printf("%02lld ", m_blocos[i]); 
    }
    printf("\n");

    // 2. CRIPTOGRAFIA (Codificação): C = M^E mod n
    printf("\n[2. CRIPTOGRAFIA] C = M^E mod n. (E=%lld, n=%lld)\n", e, n);
    for (int i = 0; i < len; i++) {
        printf("\n--- Criptografando Bloco %d (M=%lld) ---\n", i + 1, m_blocos[i]);
        c_blocos[i] = aplicar_teorema_modular(m_blocos[i], e, n, p, q); 
    }
    printf("\nMensagem Cifrada Final (blocos C): ");
    for (int i = 0; i < len; i++) {
        printf("%lld ", c_blocos[i]);
    }
    printf("\n");

    // 3. DECRIPTOGRAFIA (Decodificação): M = C^D mod n
    printf("\n[3. DECRIPTOGRAFIA] M = C^D mod n. (D=%lld, n=%lld)\n", d, n);
    ll *m_decifrados = (ll *)malloc(len * sizeof(ll));
    
    for (int i = 0; i < len; i++) {
        printf("\n--- Decriptografando Bloco %d (C=%lld) ---\n", i + 1, c_blocos[i]);
        m_decifrados[i] = aplicar_teorema_modular(c_blocos[i], d, n, p, q); 
    }
    
    // 4. RECONVERSÃO E VALIDAÇÃO
    printf("\n[4. RECONVERSAO NUMERICA EM TEXTO]\n");
    printf("Mensagem Decifrada em Numeros (blocos M'): ");
     for (int i = 0; i < len; i++) {
        printf("%02lld ", m_decifrados[i]);
    }
    printf("\n");

    printf("Mensagem Decifrada: ");
    int sucesso = 1;
    for (int i = 0; i < len; i++) {
        char c;
        if (m_decifrados[i] >= 11 && m_decifrados[i] <= 36) {
            c = (char)('A' + m_decifrados[i] - 11);
        } else if (m_decifrados[i] == 0) {
             c = ' ';
        } else {
            c = '?'; 
            sucesso = 0;
        }
        printf("%c", c);
        
        if (m_decifrados[i] != m_blocos[i]) {
            sucesso = 0;
        }
    }
    printf("\n");
    
    printf("\n[CONFIRMACAO DE RESULTADO]\n");
    if (sucesso) {
        printf("SUCESSO! A mensagem decifrada e identica a mensagem original.\n");
    } else {
        printf("FALHA! A mensagem decifrada NAO e identica a mensagem original.\n");
    }

    free(m_blocos);
    free(c_blocos);
    free(m_decifrados);
}

// FUNÇÃO PRINCIPAL

int main() {
    ll p_rsa, q_rsa;
    ll n_rsa, z_rsa, e_rsa, d_rsa;
    
    // 1. Executa a Etapa 1 (Fatoração)
    run_etapa1_test(&p_rsa, &q_rsa);
    
    // 2. Executa a Etapa 2 (Geração de Chaves)
    run_etapa2(p_rsa, q_rsa);
    
    // Recalcula chaves n, z, E, D com base nos P e Q finais para a Etapa 3.
    n_rsa = p_rsa * q_rsa;
    z_rsa = (p_rsa - 1) * (q_rsa - 1);
    
    // Re-encontrar E (USANDO VERSÃO SEM PRINT PARA NÃO POLUIR O BUFFER)
    e_rsa = 3; 
    while (e_rsa < z_rsa && mdc_sem_print(e_rsa, z_rsa) != 1) { 
        e_rsa += 2; 
    }
    if (e_rsa >= z_rsa) { e_rsa = 5; }
    
    // Re-encontrar D (USANDO VERSÃO SEM PRINT para evitar poluição do buffer)
    d_rsa = inverso_modular_sem_print(e_rsa, z_rsa); 
    
    
    // 3. Executa a Etapa 3 (Criptografia e Decriptografia)
    if (d_rsa != -1) {
        run_etapa3(n_rsa, e_rsa, d_rsa, p_rsa, q_rsa);
    } else {
        printf("\nERRO FATAL: Impossivel prosseguir para a Etapa 3 pois o expoente privado D e invalido.\n");
    }

    printf("\n--- FIM COMPLETO DA ATIVIDADE ---\n");
    return 0;
}