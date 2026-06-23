#include <stdio.h>
#include <stdlib.h>

#define TAMANHO  10
#define HAB       5
#define NAVIO     3
#define AFETADO   1
#define AGUA      0

int main() {

    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Navio 1 - horizontal: linha 1, colunas 0 a 2
    int n1_linha = 1, n1_coluna = 0, n1_tam = 3;

    // Navio 2 - vertical: coluna 4, linhas 2 a 4
    int n2_linha = 2, n2_coluna = 4, n2_tam = 3;

    for (int i = 0; i < n1_tam; i++)
        tabuleiro[n1_linha][n1_coluna + i] = NAVIO;

    for (int i = 0; i < n2_tam; i++)
        tabuleiro[n2_linha + i][n2_coluna] = NAVIO;

    printf("=== Nivel Novato ===\n\n");

    printf("[Navio 1 - horizontal]\n");
    for (int i = 0; i < n1_tam; i++)
        printf("(%d, %d)\n", n1_linha, n1_coluna + i);

    printf("\n[Navio 2 - vertical]\n");
    for (int i = 0; i < n2_tam; i++)
        printf("(%d, %d)\n", n2_linha + i, n2_coluna);

    // Navio 3 - diagonal ↘: início (3, 3)
    int n3_linha = 3, n3_coluna = 3, n3_tam = 3;

    // Navio 4 - diagonal ↗: início (9, 0)
    int n4_linha = 9, n4_coluna = 0, n4_tam = 3;

    for (int i = 0; i < n3_tam; i++)
        tabuleiro[n3_linha + i][n3_coluna + i] = NAVIO;

    for (int i = 0; i < n4_tam; i++)
        tabuleiro[n4_linha - i][n4_coluna + i] = NAVIO;

    printf("\n=== Nivel Aventureiro ===\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }

    int cone[HAB][HAB]     = {0};
    int cruz[HAB][HAB]     = {0};
    int octaedro[HAB][HAB] = {0};

    // Cone: expande a partir do topo
    for (int i = 0; i < HAB; i++)
        for (int j = 0; j < HAB; j++)
            if (j >= HAB/2 - i && j <= HAB/2 + i)
                cone[i][j] = AFETADO;

    // Cruz: linha e coluna centrais
    for (int i = 0; i < HAB; i++) {
        cruz[HAB/2][i] = AFETADO;
        cruz[i][HAB/2] = AFETADO;
    }

    // Octaedro: distância de Manhattan <= HAB/2
    for (int i = 0; i < HAB; i++)
        for (int j = 0; j < HAB; j++)
            if (abs(i - HAB/2) + abs(j - HAB/2) <= HAB/2)
                octaedro[i][j] = AFETADO;

    printf("\n=== Nivel Mestre ===\n");

    printf("\n[Cone]\n");
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++)
            printf("%d ", cone[i][j]);
        printf("\n");
    }

    printf("\n[Cruz]\n");
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++)
            printf("%d ", cruz[i][j]);
        printf("\n");
    }

    printf("\n[Octaedro]\n");
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++)
            printf("%d ", octaedro[i][j]);
        printf("\n");
    }

    // Aplica habilidades no tabuleiro
    int origem_cone_l     = 0, origem_cone_c     = 3;
    int origem_cruz_l     = 4, origem_cruz_c     = 5;
    int origem_octaedro_l = 7, origem_octaedro_c = 2;

    for (int i = 0; i < HAB; i++)
        for (int j = 0; j < HAB; j++) {
            int tl, tc;

            tl = origem_cone_l + i;
            tc = origem_cone_c + j - HAB/2;
            if (cone[i][j] && tl >= 0 && tl < TAMANHO && tc >= 0 && tc < TAMANHO)
                if (tabuleiro[tl][tc] == AGUA) tabuleiro[tl][tc] = AFETADO;

            tl = origem_cruz_l + i - HAB/2;
            tc = origem_cruz_c + j - HAB/2;
            if (cruz[i][j] && tl >= 0 && tl < TAMANHO && tc >= 0 && tc < TAMANHO)
                if (tabuleiro[tl][tc] == AGUA) tabuleiro[tl][tc] = AFETADO;

            tl = origem_octaedro_l + i - HAB/2;
            tc = origem_octaedro_c + j - HAB/2;
            if (octaedro[i][j] && tl >= 0 && tl < TAMANHO && tc >= 0 && tc < TAMANHO)
                if (tabuleiro[tl][tc] == AGUA) tabuleiro[tl][tc] = AFETADO;
        }

    printf("\n[Tabuleiro Final - 0=agua | 1=afetado | 3=navio]\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }

    return 0;
}
