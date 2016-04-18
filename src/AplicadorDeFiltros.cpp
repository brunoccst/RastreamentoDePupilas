#include <cstdlib>
#include <iostream>

using namespace std;

#include "..\AVIClass.h"
#include "AplicadorDeFiltros.h"


AplicadorDeFiltros::AplicadorDeFiltros()
{

}


AplicadorDeFiltros::AplicadorDeFiltros(AVIClass video)
{
    Video = video;
}


void AplicadorDeFiltros::TonsDeCinza()
{
    int x, y;
    int i, j;

    for( x=0; x < Video.SizeX(); x++ )
    {
        for( y=0; y < Video.SizeY(); y++ )
        {
            i = Video.GetPointIntensity(x,y);
            Video.DrawPixel(x, y, i, i, i);
        }
    }
}


void AplicadorDeFiltros::OrdenaVetor(unsigned char window[])
{
    int temp, i , j;
    for(i = 0; i < 9; i++)
    {
        temp = window[i];
        for(j = i-1; j >= 0 && temp < window[j]; j--)
        {
            window[j+1] = window[j];
        }
        window[j+1] = temp;
    }
}


void AplicadorDeFiltros::Mediana()
{
    int cont;
    unsigned char r[9], g[9], b[9];

    for(int y = 0; y < Video.SizeY(); y++){
        for(int x = 0; x < Video.SizeX(); x++){

            cont = 0;

            for(int i = 0; i<3; i++){
                for(int j = 0; j<3; j++){
                    Video.ReadPixel(x+j, y+i, r[cont], g[cont], b[cont]);
                    cont++;
                }
            }

            OrdenaVetor(r);
            OrdenaVetor(g);
            OrdenaVetor(b);

            Video.DrawPixel(x, y, r[4], g[4], b[4]);
        }
    }
}

void AplicadorDeFiltros::Limiarizacao(int intensidade)
{
    for(int y = 0; y < Video.SizeY(); y++){
        for(int x = 0; x < Video.SizeX(); x++){

            int i = Video.GetPointIntensity(x, y);

            //Pinta o ponto de vermelho.
            if (i < intensidade)
            {
                Video.DrawPixel(x, y, 255, 0, 0);
            }else{
                Video.DrawPixel(x,y,200,200,200);
            }
        }
    }
}

// Pinta conjunto de pontos dados por vetores de tamanhos iguais
void AplicadorDeFiltros::PintaConjuntoDePontos(int x[], int y[], unsigned char r, unsigned char g, unsigned char b)
{
    for (int i = 0; i < sizeof(x); i++)
        Video.DrawPixel(x[i], y[i], r, g, b);
}


void AplicadorDeFiltros::PintaCirculos(int tamanhoDaMatriz)
{
    unsigned char r, g, b;
    int vetorDeX[tamanhoDaMatriz];
    int vetorDeY[tamanhoDaMatriz];

    for(int y = 0; y < Video.SizeY(); y++)
    {
        for(int x = 0; x < Video.SizeX(); x++)
        {
           Video.ReadPixel(x, y, r, g, b);
           bool ehVermelho = false;

           //Se o ponto for vermelho, pesquisa os vizinhos
            if (r == 255)
            {
                int posicao = 0;

                for (int j = 0; j < tamanhoDaMatriz; j++)
                {
                    if (!ehVermelho) break;
                    for (int k = 0; k < tamanhoDaMatriz; k++)
                    {
                        int xVizinho = x + j;
                        int yVizinho = y + k;
                        Video.ReadPixel(xVizinho, yVizinho, r, g, b);

                        if (r == 255)
                        {
                            vetorDeX[posicao] = xVizinho;
                            vetorDeY[posicao] = yVizinho;
                            posicao++;
                        }
                        else
                        {
                            ehVermelho = false;
                            break;
                        }
                    }
                }
            }

            //Se o ponto processado era vermelho em volta, pinta a area de azul
            if (ehVermelho) PintaConjuntoDePontos(vetorDeX, vetorDeY, 0, 0, 255);
        }
    }
}


void AplicadorDeFiltros::ProcuraOlhos()
{
    unsigned char r, g, b;
    int cont;
    int metadeY = (Video.SizeY())/2;
    for(int y = metadeY; y < Video.SizeY() - 150; y++ )
    {
        for(int x = 0; x < Video.SizeX(); x++ )
        {
            Pintando(x, y);
        }
    }
}

void AplicadorDeFiltros::Pintando(int x,int y){

    unsigned char r,g,b;
    Video.ReadPixel(x,y,r,g,b);
    if(r == 255){
        Video.DrawPixel(x,y,0,255,0);
        Pintando(x+1,y);
        Pintando(x-1,y);
        Pintando(x,y+1);
        Pintando(x,y-1);
    }else{
        return;
    }
}

void AplicadorDeFiltros::ProcuraBranco(){
    for(int y = 0; y < Video.SizeY(); y++ )
    {
        for(int x = 0; x < Video.SizeX(); x++ )
        {
            if(Video.GetPointIntensity(x,y) > 40 && Video.GetPointIntensity(x,y) < 120){
                Video.DrawPixel(x,y,0,0,255);
            }
        }
    }
}

void AplicadorDeFiltros::Realce(int limiar){
    unsigned char r,g,b;

    for(int y = 0; y < Video.SizeY(); y++ )
    {
        for(int x = 0; x < Video.SizeX(); x++ )
        {
            Video.ReadPixel(x,y,r,g,b);
            if(r > 150){
                Video.DrawPixel(x,y,r+limiar,b+limiar,g+limiar);
            }else{
                Video.DrawPixel(x,y,r-limiar,b-limiar,g-limiar);
            }
        }
    }
}
