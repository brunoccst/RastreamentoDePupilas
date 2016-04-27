#ifndef APLICADORDEFILTROS_H
#define APLICADORDEFILTROS_H
#include <vector>

class AplicadorDeFiltros
{
    public:
        AplicadorDeFiltros();
        void TonsDeCinza(AVIClass* video);
        void TonsDeCinza(AVIClass* video, int minX, int maxX, int minY, int maxY);
        void Media(AVIClass* video, double* mediaX, double* mediaY);
        void Media(AVIClass* video, double* mediaX, double* mediaY, int minX, int maxX, int minY, int maxY);
        void Mediana(AVIClass* video);
        void Mediana(AVIClass* video, int minX, int maxX, int minY, int maxY);
        void Limiarizacao(AVIClass* video, int intensidade, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2);
        void Limiarizacao(AVIClass* video, int intensidade, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2, int minX, int maxX, int minY, int maxY);
        void BaldeDeTinta(AVIClass* video, int x, int y, unsigned char r, unsigned char g, unsigned char b);
    protected:
    private:
        void OrdenaVetor(unsigned char window[]);
        void BaldeDeTinta(AVIClass* video, int x, int y, unsigned char originalR, unsigned char originalG, unsigned char originalB, unsigned char r, unsigned char g, unsigned char b);
};

#endif // APLICADORDEFILTROS_H
