#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

#include "..\AVIClass.h"
#include "AplicadorDeFiltros.h"

AplicadorDeFiltros::AplicadorDeFiltros()
{

}

void AplicadorDeFiltros::TonsDeCinza(AVIClass* video)
{
    TonsDeCinza(video, 0, video->SizeX(), 0, video->SizeY());
}

void AplicadorDeFiltros::TonsDeCinza(AVIClass* video, int minX, int maxX, int minY, int maxY)
{
    for(int x = minX; x < maxX; x++)
    {
        for(int y = 0; y < maxY; y++)
        {
            int intensidade = video->GetPointIntensity(x,y);
            video->DrawPixel(x, y, intensidade, intensidade, intensidade);
        }
    }
}

void AplicadorDeFiltros::Media(AVIClass* video, double* mediaX, double* mediaY)
{
    Media(video, mediaX, mediaY, 0, video->SizeX(), 0, video->SizeY());
}

void AplicadorDeFiltros::Media(AVIClass* video, double* mediaX, double* mediaY, int minX, int maxX, int minY, int maxY)
{
    double soma = 0.0;

    for(int i = minX; i < maxX; i++)
    {
        soma += i;
    }

    *mediaX = soma/(maxX - minX);

    soma = 0.0;

    for(int i = minY; i < maxY; i++)
    {
        soma += i;
    }

    *mediaY = soma/(maxY - minY);
}

void AplicadorDeFiltros::Mediana(AVIClass* video)
{
    Mediana(video, 0, video->SizeX(), 0, video->SizeY());
}

void AplicadorDeFiltros::Mediana(AVIClass* video, int minX, int maxX, int minY, int maxY)
{
    int cont;
    unsigned char r[9], g[9], b[9];

    for(int y = minY; y < maxY; y++)
    {
        for(int x = minX; x < maxX; x++)
        {
            cont = 0;
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    video->ReadPixel(x+j, y+i, r[cont], g[cont], b[cont]);
                    cont++;
                }
            }

            OrdenaVetor(r);
            OrdenaVetor(g);
            OrdenaVetor(b);

            video->DrawPixel(x, y, r[4], g[4], b[4]);
        }
    }
}

void AplicadorDeFiltros::Limiarizacao(AVIClass* video, int intensidade, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2)
{
    Limiarizacao(video, intensidade, r1, g1, b1, r2, g2, b2, 0, video->SizeX(), 0, video->SizeY());
}

void AplicadorDeFiltros::Limiarizacao(AVIClass* video, int intensidade, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2, int minX, int maxX, int minY, int maxY)
{
    for(int y = minY; y < maxY; y++){
        for(int x = minX; x < maxX; x++){

            int i = video->GetPointIntensity(x, y);

            if (i < intensidade)
            {
                video->DrawPixel(x, y, r1, g1, b1);
            }
            else
            {
                video->DrawPixel(x, y, r2, g2, b2);
            }
        }
    }
}

void AplicadorDeFiltros::BaldeDeTinta(AVIClass* video, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    unsigned char originalR, originalG, originalB;
    video->ReadPixel(x, y, originalR, originalG, originalB);
    BaldeDeTinta(video, x, y, originalR, originalG, originalB, r, g, b);
}

void AplicadorDeFiltros::BaldeDeTinta(AVIClass* video, int x, int y, unsigned char originalR, unsigned char originalG, unsigned char originalB, unsigned char r, unsigned char g, unsigned char b)
{
    unsigned char rAtual, gAtual, bAtual;
    video->ReadPixel(x, y, rAtual, gAtual, bAtual);

    if(rAtual == originalR && gAtual == originalG && bAtual == originalB)
    {
        video->DrawPixel(x, y, r, g, b);

        BaldeDeTinta(video, x+1, y, originalR, originalG, originalB, r, g, b);
        BaldeDeTinta(video, x-1, y, originalR, originalG, originalB, r, g, b);
        BaldeDeTinta(video, x, y+1, originalR, originalG, originalB, r, g, b);
        BaldeDeTinta(video, x, y-1, originalR, originalG, originalB, r, g, b);
    }
    else
    {
        return;
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
