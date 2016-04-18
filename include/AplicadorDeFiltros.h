#ifndef APLICADORDEFILTROS_H
#define APLICADORDEFILTROS_H


class AplicadorDeFiltros
{
    public:
        AplicadorDeFiltros();
        AplicadorDeFiltros(AVIClass video);
        void TonsDeCinza();
        void Mediana();
        void Limiarizacao(int intensidade);
        void PintaCirculos(int tamanhoDaMatriz);
        void ProcuraOlhos();
        void Pintando(int x, int y);
        void ProcuraBranco();
        void Realce(int limiar);
    protected:

    private:
        AVIClass Video;
        void OrdenaVetor(unsigned char window[]);
        void PintaConjuntoDePontos(int x[], int y[], unsigned char r, unsigned char g, unsigned char b);
};

#endif // APLICADORDEFILTROS_H
