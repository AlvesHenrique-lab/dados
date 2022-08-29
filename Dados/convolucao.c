/*=============================================================
 * Unifal - Universidade Federal de alfenas 
 * Bacharelado em Ciencia da Computação
 * Trabalho......: Imagem de dados
 * Disciplina....: Processamento de Imagens
 * Professor.....: Luiz Eduardo da Silva
 * Aluno.........: Henrique Alves do Nascimento
 * Data..........: 08/07/2022
 * ==========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagelib.h"

#define TAM 250

int intervalo(int valor)
{
    if (0 <= valor && valor <= 36)
    {
        return 0;
    }
    else if (37 <= valor && valor <= 72)
    {
        return 1;
    }
    else if (73 <= valor && valor <= 108)
    {
        return 2;
    }
    else if (109 <= valor && valor <= 144)
    {
        return 3;
    }
    else if (145 <= valor && valor <= 180)
    {
        return 4;
    }
    else if (181 <= valor && valor <= 216)
    {
        return 5;
    }
    else if (217 <= valor && valor <= 255)
    {
        return 6;
    }
}

void normalizarImagem(image In, int nl, int nc, int mn)
{
    for (int i = 0; i < nl; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            In[i * nc + j] = intervalo(In[i * nc + j]);
        }
    }
}

void minimizaImagem(image In, image Out, int nl, int nc, int mn)
{
    float porc = (float)TAM / nc;
    int nlIcon = nl * porc;

    for (int i = 0; i < nlIcon; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            Out[i * TAM + j] = In[(i * nl / nlIcon) * nc + (j * nc / TAM)];
        }
    }
}

void convertePixelDados(image In, int nl, int nc, int mn, image Out)
{
    int temp = 0;
    
    image dados[7] = {
        img_get("./imagens-dados/preto-0.pgm", &temp, &temp, &temp, GRAY),
        img_get("./imagens-dados/preto-1.pgm", &temp, &temp, &temp, GRAY),
        img_get("./imagens-dados/preto-2.pgm", &temp, &temp, &temp, GRAY),
        img_get("./imagens-dados/preto-3.pgm", &temp, &temp, &temp, GRAY),
        img_get("./imagens-dados/preto-4.pgm", &temp, &temp, &temp, GRAY),
        img_get("./imagens-dados/preto-5.pgm", &temp, &temp, &temp, GRAY),
        img_get("./imagens-dados/preto-6.pgm", &temp, &temp, &temp, GRAY)};
    system("clear");

    int ncFinal = nc * 40;
    for (int i = 0; i < nl; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            image dado = dados[In[i * nc + j]];
            for (int x = 0; x < 40; x++)
            {
                for (int y = 0; y < 40; y++)
                {
                    Out[(i * 40 + x) * ncFinal + j * 40 + y] = dado[x * 40 + y];
                }
            }
        }
    }
}

image dados(image In, image Out, int nl, int nc, int mn)
{
    float porc = (float)TAM / nc;
    int nlIcon = nl * porc;
    image auxOut = (image)malloc(nlIcon * 40 * TAM * 40 * sizeof(int));
    normalizarImagem(In, nl, nc, mn);
    minimizaImagem(In, Out, nl, nc, mn);
    convertePixelDados(Out, nlIcon, TAM, mn, auxOut);
    free(Out);
    return auxOut;
}

void msg(char *s)
{
    printf("\nDados");
    printf("\n-------------------------------");
    printf("\nUso:  %s  nome-imagem[.pgm] \n\n", s);
    printf("    nome-imagem[.pgm] é o nome do arquivo da imagem \n");
    exit(1);
}

/*-------------------------------------------------------------------------
 * main function
 *-------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int nc, nr, ml, tp;
    char *p, nameIn[TAM], nameOut[TAM], cmd[110];
    image In, Out;
    if (argc < 2)
        msg(argv[0]);
    img_name(argv[1], nameIn, nameOut, GRAY);
    //-- read image
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);
    float porc = (float)TAM / nc;
    int nlIcon = nr * porc;
    Out = img_alloc(nlIcon * 40, TAM * 40);
    //-- transformation
    Out = dados(In, Out, nr, nc, ml);
    //-- save image
    img_put(Out, nameOut, nlIcon * 40, TAM * 40, ml, GRAY);
    printf(cmd, "%s &", VIEW, nameOut);
    system(cmd);
    img_free(In);
    img_free(Out);
    return 0;
}