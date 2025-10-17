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
ll mulmod(ll a, ll b, ll mod); 
int is_prime(ll n);
char num_to_char_simples(ll n);
void limpar_buffer();
void run_etapa1_test(ll *p_out, ll *q_out);
void run_etapa2(ll p, ll q);
void run_etapa3(ll n, ll e, ll d, ll p, ll q);

// =========================================================================
// FUNÇÕES DE UTILIDADE E ARITMÉTICA MODULAR
// =========================================================================

ll mulmod(ll a, ll b, ll mod) {
    a %= mod; if (a < 0) a += mod;
    b %= mod; if (b < 0) b += mod;
    ll res = 0;
    while (b > 0) {
        if (b & 1LL) {
            res += a;
            if (res >= mod) res -= mod;
        }
        b >>= 1LL;
        if (a >= mod) a %= mod;
        if (b) {
            a <<= 1LL;
            if (a >= mod) a %= mod;
        }
    }
    return res % mod;
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int is_prime(ll n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (ll i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    return 1;
}

char num_to_char_simples(ll n) {
    if (n >= 11 && n <= 36) {
        return (char)('A' + n - 11);
    } else if (n == 0) {
        return ' ';
    }
    return 'N'; // Indica que é um Número Cifrado ou Inaplicável (não mapeado A-Z)
}

ll mdc(ll a, ll b) {
    ll resto;
    printf("\n--- Inicio do Algoritmo de Euclides (mdc(%lld, %lld)) ---\n", a, b);
    if (llabs(b) > llabs(a)) { ll temp = a; a = b; b = temp; }
    while (b != 0) { 
        resto = a % b;
        printf("Passo: %lld = %lld * %lld + %lld\n", a, a / b, b, resto); 
        a = b;
        b = resto;
    }
    printf("--- Fim do Algoritmo de Euclides (MDC = %lld) ---\n", llabs(a));
    return llabs(a);
}

ll mdc_sem_print(ll a, ll b) {
    ll resto;
    if (llabs(b) > llabs(a)) { ll temp = a; a = b; b = temp; }
    while (b != 0) { 
        resto = a % b;
        a = b;
        b = resto;
    }
    return llabs(a);
}


ll estendido_euclides(ll a, ll b, ll *x, ll *y) {
    ll mdc_val; ll x1 = 0, y1 = 1; ll xx = 1, yy = 0; 
    printf("\n--- EUCLIDES ESTENDIDO (D*E mod z) ---\n");
    printf("Valores iniciais: E=%lld, z=%lld\n", a, b);
    if (b == 0) { *x = 1; *y = 0; return a; }
    ll q, t, temp_x, temp_y;
    while (b != 0) { 
        q = a / b;
        temp_x = xx - q * x1; 
        temp_y = yy - q * y1;
        xx = x1; x1 = temp_x;
        yy = y1; y1 = temp_y;
        t = b; b = a % b; a = t;
        printf("ITER: q=%lld | Coefs (x, y) = (%lld, %lld)\n", q, xx, yy);
    }
    mdc_val = a;
    *x = xx; *y = yy; 
    printf("--- MDC ENCONTRADO: %lld ---\n", mdc_val);
    return mdc_val;
}

ll estendido_euclides_sem_print(ll a, ll b, ll *x, ll *y) {
    ll x1 = 0, y1 = 1; ll xx = 1, yy = 0; ll q, t, temp_x, temp_y;
    if (b == 0) { *x = 1; *y = 0; return a; }
    while (b != 0) { 
        q = a / b;
        temp_x = xx - q * x1; temp_y = yy - q * y1; 
        xx = x1; x1 = temp_x; yy = y1; y1 = temp_y;
        t = b; b = a % b; a = t;
    }
    *x = xx; *y = yy; 
    return a;
}

ll inverso_modular(ll a, ll m) {
    ll x, y; ll m0 = m; 
    ll mdc_val = estendido_euclides(a, m, &x, &y); 
    if (mdc_val != 1) {
        printf("\nERRO: O inverso modular de %lld mod %lld nao existe.\n", a, m);
        return -1; 
    }
    ll inv = x;
    if (inv < 0) { 
        inv += m0;
        printf("\n[AJUSTE INVERSO] Negativo (%lld) -> Positivo: %lld\n", x, inv);
    }
    printf("-> EXPOENTE PRIVADO D: %lld\n", inv);
    return inv;
}

ll inverso_modular_sem_print(ll a, ll m) {
    ll x, y; ll m0 = m;
    ll mdc_val = estendido_euclides_sem_print(a, m, &x, &y);
    if (mdc_val != 1) { return -1; }
    ll inv = x;
    if (inv < 0) { inv += m0; }
    return inv;
}


// =========================================================================
// ETAPA 1: FATORAÇÃO RHO DE POLLARD
// =========================================================================

ll pollard_rho(ll n) {
    ll x = 2, y = 2; ll d = 1; ll i = 0;
    printf("\n--- METODO RHO DE POLLARD (N=%lld) ---\n", n);
    if (n % 2 == 0) return 2; 

    while (d == 1) { 
        x = (mulmod(x, x, n) + 1) % n; 
        y = (mulmod(y, y, n) + 1) % n; 
        y = (mulmod(y, y, n) + 1) % n; 

        d = mdc(llabs(x - y), n); 
        i++;

        printf("\nITERACAO RHO %lld:\n", i);
        printf("  [VALORES] x_i = %lld, x_2i = %lld\n", x, y);
        printf("  [TESTE MDC] d = %lld\n", d);

        if (d != 1 && d != n) {
            printf("--- FATOR ENCONTRADO: %lld ---\n", d);
            return d;
        }

        if (d == n || i > 5000) { 
            printf("--- FALHA NA FATORACAO ---\n");
            return -1; 
        }
    }
    return d;
}

void run_etapa1_test(ll *p_out, ll *q_out) {
    ll n1, n2; ll p = 0, q = 0;
    printf("\n=========================================================\n");
    printf("                ETAPA 1: FATORACAO RHO                  \n");
    printf("=========================================================\n");

    do {
        printf("Insira o primeiro numero composto N1 (3 ou 4 digitos, entre 100 e 9999): ");
        if (scanf("%lld", &n1) != 1) { limpar_buffer(); n1 = 0; }
        printf("Insira o segundo numero composto N2 (3 ou 4 digitos, distintos de N1): ");
        if (scanf("%lld", &n2) != 1) { limpar_buffer(); n2 = 0; }
        limpar_buffer(); 

        if (n1 < 100 || n1 > 9999 || n2 < 100 || n2 > 9999 || n1 == n2) {
            printf("[ERRO] Restricao violada. Tente novamente.\n"); continue;
        }
        if (is_prime(n1) || is_prime(n2)) { 
            printf("[AVISO] Pelo menos um dos numeros parece ser primo. O enunciado requer compostos.\n");
        }
        printf("\n--- Aviso: O metodo Rho e mais eficiente se Ni for produto de primos distintos ---\n");
        
        p = pollard_rho(n1);
        q = pollard_rho(n2);

        // Lógica de correção de fator composto e seleção final
        if (p > 0 && p != -1 && p != n1) {
            ll p_other = n1 / p;
            if (!is_prime(p) && is_prime(p_other)) p = p_other;
        } else { p = 0; } 

        if (q > 0 && q != -1 && q != n2) {
            ll q_other = n2 / q;
            if (!is_prime(q) && is_prime(q_other)) q = q_other;
        } else { q = 0; }
        
        // Validação de requisitos de saída: p e q devem ser primos, distintos e maiores que 1
        if (p <= 1 || q <= 1 || p == q || !is_prime(p) || !is_prime(q)) {
            printf("\n[REQUISITO VIOLADO] Fatores P=%lld e Q=%lld sao invalidos, nao primos ou iguais.\n", p, q);
            printf("Por favor, insira novos N1 e N2 que sejam produtos de primos distintos.\n");
            continue;
        }
        
        break;
    } while (1);

    printf("\n===> PRIMOS RSA SELECIONADOS: P = %lld, Q = %lld <===\n", p, q);
    *p_out = p; *q_out = q;
}

// =========================================================================
// ETAPA 2: GERAÇÃO DE CHAVES RSA
// =========================================================================

void run_etapa2(ll p, ll q) {
    ll n, z, e, d;
    
    printf("\n==================== ETAPA 2: GERACAO DE CHAVES RSA ====================\n");
    printf("Primos Recebidos: P=%lld, Q=%lld\n", p, q);

    n = p * q; z = (p - 1) * (q - 1);                     

    printf("\n[1. CALCULOS MODULARES]\n");
    printf("Modulo n = %lld\n", n);
    printf("Totiente de Euler z(n) = %lld\n", z);

    // 2. Escolha do Expoente Público E
    e = 2; 
    printf("\n[2. ESCOLHA DO EXPOENTE PUBLICO E]\n");
    
    while (e < z) { 
        if (mdc(e, z) == 1) { 
            printf("=> E ESCOLHIDO: %lld\n", e);
            break;
        }
        e++; 
    }
    
    if (e >= z) { e = 5; }

    // 3. Cálculo do Expoente Privado D
    printf("\n[3. CALCULO DO EXPOENTE PRIVADO D]\n");
    printf("Buscando D tal que D * %lld = 1 mod %lld\n", e, z);
    d = inverso_modular(e, z); 
    
    // 4. Impressão das Chaves
    printf("\n==================== CHAVES FINAIS ====================\n");
    printf("CHAVE PUBLICA: (n=%lld, E=%lld)\n", n, e);
    printf("CHAVE PRIVADA: (n=%lld, D=%lld)\n", n, d);
    printf("=========================================================\n");
}

// =========================================================================
// ETAPA 3: CRIPTOGRAFIA/DECRIPTOGRAFIA
// =========================================================================

ll powMod(ll base, ll exp, ll mod) {
    ll res = 1; ll b = base % mod; ll exp_original = exp;
    printf("\n--- EXPONENCIACAO MODULAR: %lld^%lld mod %lld ---\n", base, exp_original, mod);
    printf("INICIO: res = 1, base_mod = %lld, exp = %lld\n", b, exp);

    while (exp > 0) {
        if (exp & 1) { 
            ll tmp = mulmod(res, b, mod);
            printf("  BIT [1]: res = (%lld * %lld) mod %lld = %lld\n", res, b, mod, tmp);
            res = tmp;
        } else {
             printf("  BIT [0]: res permanece %lld\n", res);
        }
        ll sq = mulmod(b, b, mod);
        printf("  QUADRADO: base_mod = (%lld * %lld) mod %lld = %lld\n", b, b, mod, sq);
        b = sq;
        exp >>= 1; 
        printf("  NOVO EXP: %lld\n", exp);
    }
    printf("--- RESULTADO EXP: %lld ---\n", res);
    return res;
}

ll aplicar_teorema_modular(ll base, ll exp, ll mod, ll p, ll q) {
    ll new_exp = exp; int teorema_aplicado = 0; ll z_n = (p - 1) * (q - 1); 
    char base_char = num_to_char_simples(base);

    // 1. Verificar Pequeno Teorema de Fermat (PTF) - Se n for primo
    if (is_prime(mod)) {
        printf("\n[APLICANDO TEOREMA MODULAR: Pequeno Teorema de Fermat] (Base=%lld%c)\n", base, base_char);
        new_exp = exp % (mod - 1); teorema_aplicado = 1;
    } 
    
    // 2. Teorema de Euler: Se mdc(M, n) = 1, reduz o expoente mod z(n).
    if (!teorema_aplicado) {
        if (mdc(base, mod) == 1) { 
            printf("\n[APLICANDO TEOREMA MODULAR: Teorema de Euler] (Base=%lld%c)\n", base, base_char);
            printf("  Reduzindo o expoente E ou D mod z(n)=%lld.\n", z_n);
            new_exp = exp % z_n; teorema_aplicado = 1;
        }
    }

    // 3. Teorema da Divisão Euclidiana (Método Padrão)
    if (!teorema_aplicado) {
        printf("\n[APLICANDO TEOREMA MODULAR: Divisao Euclidiana (Metodo Padrao)] (Base=%lld%c)\n", base, base_char);
        new_exp = exp;
    }

    ll resultado = powMod(base, new_exp, mod);
    return resultado;
}


void run_etapa3(ll n, ll e, ll d, ll p, ll q) {
    printf("\n==================== ETAPA 3: CRIPTO/DECRIPTO RSA ====================\n");

    char mensagem_input[100]; char mensagem_original[100] = ""; 
    
    printf("Insira a mensagem (letras MAIUSCULAS e espacos): ");
    
    if (scanf(" %99[^\n]", mensagem_input) != 1) { 
        printf("\n[AVISO] Nenhuma mensagem valida lida.\n");
        return;
    }
    
    int len_input = strlen(mensagem_input); int k = 0;
    for (int i = 0; i < len_input; i++) {
        char c = mensagem_input[i];
        if (c >= 'A' && c <= 'Z') { mensagem_original[k++] = c; } 
        else if (c == ' ') { mensagem_original[k++] = c; }
        else { mensagem_original[k++] = toupper((unsigned char)c); }
    }
    mensagem_original[k] = '\0'; 
    int len = k; 
    
    if (len == 0) { printf("\n[AVISO] mensagem vazia.\n"); return; }
    
    ll *m_blocos = (ll *)malloc(len * sizeof(ll));
    ll *c_blocos = (ll *)malloc(len * sizeof(ll));

    // 1. PRÉ-CODIFICACAO
    printf("\n[1. PRE-CODIFICACAO] Mensagem: %s\n", mensagem_original);
    printf("Codigos M (blocos de 2 digitos): ");
    
    for (int i = 0; i < len; i++) {
        char c = mensagem_original[i];
        if (c == ' ') m_blocos[i] = 0; 
        else m_blocos[i] = c - 'A' + 11; 
        printf("%02lld ", m_blocos[i]); 
    }
    printf("\n");

    // 2. CRIPTOGRAFIA
    printf("\n[2. CRIPTOGRAFIA] C = M^E mod n (E=%lld, n=%lld)\n", e, n);
    for (int i = 0; i < len; i++) {
        printf("\n--- Criptografando Bloco %d (M=%lld) ---\n", i + 1, m_blocos[i]);
        c_blocos[i] = aplicar_teorema_modular(m_blocos[i], e, n, p, q); 
    }
    printf("\n===> MENSAGEM CIFRADA: ");
    for (int i = 0; i < len; i++) {
        printf("%lld ", c_blocos[i]);
    }
    printf(" <===\n");

    // 3. DECRIPTOGRAFIA
    printf("\n[3. DECRIPTOGRAFIA] M = C^D mod n (D=%lld, n=%lld)\n", d, n);
    ll *m_decifrados = (ll *)malloc(len * sizeof(ll));
    
    for (int i = 0; i < len; i++) {
        printf("\n--- Decriptografando Bloco %d (C=%lld) ---\n", i + 1, c_blocos[i]);
        m_decifrados[i] = aplicar_teorema_modular(c_blocos[i], d, n, p, q); 
    }
    
    // 4. RECONVERSÃO E VALIDAÇÃO
    printf("\n[4. RESULTADO FINAL]\n");
    printf("Mensagem Decifrada: ");
    int sucesso = 1;
    for (int i = 0; i < len; i++) {
        char c;
        if (m_decifrados[i] == 0) c = ' ';
        else if (m_decifrados[i] >= 11 && m_decifrados[i] <= 36) c = (char)('A' + m_decifrados[i] - 11);
        else { c = '?'; sucesso = 0; }
        printf("%c", c);
        if (m_decifrados[i] != m_blocos[i]) sucesso = 0;
    }
    printf("\n");
    
    printf(sucesso ? "CONFIRMACAO: SUCESSO! Mensagem decifrada e identica a original.\n" : "CONFIRMACAO: FALHA! Divergencia.\n");

    free(m_blocos); free(c_blocos); free(m_decifrados);
}


// =========================================================================
// FUNÇÃO PRINCIPAL
// =========================================================================

int main(void) {
    ll p_rsa, q_rsa;
    ll n_rsa, z_rsa, e_rsa, d_rsa;
    
    // 1. Executa a Etapa 1 (Fatoração)
    run_etapa1_test(&p_rsa, &q_rsa);
    
    // 2. Executa a Etapa 2 (Geração de Chaves)
    run_etapa2(p_rsa, q_rsa);
    
    // Recalcula chaves n, z, E, D (USANDO VERSÕES SEM PRINT para a Etapa 3)
    n_rsa = p_rsa * q_rsa;
    z_rsa = (p_rsa - 1) * (q_rsa - 1);
    
    e_rsa = 2; 
    while (e_rsa < z_rsa && mdc_sem_print(e_rsa, z_rsa) != 1) { e_rsa++; }
    if (e_rsa >= z_rsa) { e_rsa = 5; }
    
    d_rsa = inverso_modular_sem_print(e_rsa, z_rsa); 
    
    
    // 3. Executa a Etapa 3 (Criptografia e Decriptografia)
    if (d_rsa != -1) {
        run_etapa3(n_rsa, e_rsa, d_rsa, p_rsa, q_rsa);
    } else {
        printf("\nERRO FATAL: Impossivel prosseguir para a Etapa 3 pois o expoente privado D e invalido.\n");
    }

    printf("\n--- FIM COMPLETO DA ATIVIDADE (Questao 01) ---\n");
    return 0;
}