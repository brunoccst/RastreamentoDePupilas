#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#include "..\AVIClass.h"
#include "AplicadorDeFiltros.h"

int posicaoDoVetor = 0;
vector<int> vetor1X;
vector<int> vetor1Y;
vector<int> vetor2X;
vector<int> vetor2Y;
int posicao;

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

void AplicadorDeFiltros::Mediana(int minX, int maxX, int minY, int maxY)
{
    int cont;
    unsigned char r[9], g[9], b[9];

    for(int y = minY; y < maxY; y++){
        for(int x = minX; x < maxX; x++){

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
                int posicaoDoVetor = 0;

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
                            vetorDeX[posicaoDoVetor] = xVizinho;
                            vetorDeY[posicaoDoVetor] = yVizinho;
                            posicaoDoVetor++;
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
    int posicoes[4];
    int *dupla[2];
    unsigned char r, g, b;
    int cont;
    int metadeY = (Video.SizeY())/2;

    bool jaPintouOlho1 = false;
    bool jaPintouOlho2 = false;

    for(int y = metadeY; y < Video.SizeY() - 150; y++ )
    {
        if (jaPintouOlho1 && jaPintouOlho2) break;

        for(int x = 0; x < Video.SizeX(); x++ )
        {
            if (jaPintouOlho1 && jaPintouOlho2) break;

            Video.ReadPixel(x,y,r,g,b);
            if (r == 255)
            {
                Pintando(x, y, jaPintouOlho1);
                if (jaPintouOlho1) jaPintouOlho2 = true;
                jaPintouOlho1 = true;
            }
        }
    }

    Media(vetor1X, vetor1Y, 1);
    Media(vetor2X, vetor2Y, 2);
}

void AplicadorDeFiltros::Pintando(int x,int y, bool jaPintouOlho1){

    unsigned char r,g,b;
    Video.ReadPixel(x,y,r,g,b);
    if(r == 255){

        Video.DrawPixel(x,y,200,200,200);

        if (!jaPintouOlho1)
        {
            vetor1X.push_back(x);
            vetor1Y.push_back(y);
        }
        else
        {
            vetor2X.push_back(x);
            vetor2Y.push_back(y);
        }

        posicaoDoVetor++;


        Pintando(x+1,y, jaPintouOlho1);
        Pintando(x-1,y, jaPintouOlho1);
        Pintando(x,y+1, jaPintouOlho1);
        Pintando(x,y-1, jaPintouOlho1);
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

void AplicadorDeFiltros::AplicaRetangulo(int minX, int maxX, int minY, int maxY){

    for(int y = 0; y < Video.SizeY(); y++ )
    {
        for(int x = 0; x < Video.SizeX(); x++ )
        {
            if (!(x > minX && x < maxX) || !(y > minY && y < maxY))
            {
                Video.DrawPixel(x, y, 255, 255, 255);
            }
        }
    }
}

void AplicadorDeFiltros::CriaCruz(int x, int y){
    Video.DrawPixel(x,y,0,255,0);

    for(int i=-5;i<5;i++){
        Video.DrawPixel(x+i,y,0,255,0);
    }

    for(int j=-5;j<5;j++){
        Video.DrawPixel(x,y+j,0,255,0);
    }

    Video.DrawPixel(x,y,0,255,0);
}

void AplicadorDeFiltros::Media(vector<int> vetorx, vector<int> vetory, int vetor){
    int dupla[2];
    int x,y;
    int soma = 0;
    for(int i =0; i< vetorx.size();i++){
        soma += vetorx[i];
    }
    x = soma / vetorx.size();
    soma = 0;
    for(int j =0; j< vetory.size();j++){
        soma += vetory[j];
    }
    y = soma / vetory.size();
    if(vetor == 1){
        pos1X = x;
        pos1Y = y;
    }else{
        pos2X = x;
        pos2Y = y;
    }
}


void AplicadorDeFiltros::Zera(){
    vetor1X.clear();
    vetor1Y.clear();
    vetor2X.clear();
    vetor2Y.clear();
}
