#ifndef APLICADORDEFILTROS_H
#define APLICADORDEFILTROS_H
#include <vector>

class AplicadorDeFiltros
{
    public:
        AplicadorDeFiltros();
        AplicadorDeFiltros(AVIClass video);
        void TonsDeCinza();
        void Mediana(int minX, int maxX, int minY, int maxY);
        void Limiarizacao(int intensidade);
        void PintaCirculos(int tamanhoDaMatriz);
        void ProcuraOlhos();
        void Pintando(int x, int y, bool jaPintouOlho1);
        void ProcuraBranco();
        void Realce(int limiar);
        void AplicaRetangulo(int minX, int maxX, int minY, int maxY);
        void CriaCruz(int x, int y);
        void Media(vector<int> vetorx, vector<int> vetory);
        void Zera();
    protected:

    private:
        int olho1X[200];
        int olho1Y[200];
        int olho2X[200];
        int olho2Y[200];
        AVIClass Video;
        void OrdenaVetor(unsigned char window[]);
        void PintaConjuntoDePontos(int x[], int y[], unsigned char r, unsigned char g, unsigned char b);
};

#endif // APLICADORDEFILTROS_H
