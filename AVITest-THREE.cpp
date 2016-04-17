// **********************************************************************
// PUCRS/FACIN
// COMPUTAÇÃO GRÁFICA
//
// Arquivo: AVITest.cpp
//
// Programa de testes para carga de Imagens e vídeos AVI
//
//  Este programa deve ser compilador junto com a classe "ImageClass",
//  que está implementada no arquivo "ImageClass.cpp"
//
//  Para a carga das imagens este programa utiliza a biblioteca
//  IM http://www.tecgraf.puc-rio.br/im de autoria de Antonio Scuri
//
// Marcio Serolli Pinho
// 12/08/2003
//  pinho@inf.pucrs.br
// **********************************************************************

#include <cstdlib>
#include <iostream>
using namespace std;

#include "AVIClass.h"
#include "AplicadorDeFiltros.h"

int filtrosOn = false;
bool watchAll;

AplicadorDeFiltros filtros;
AVIClass Video;

// **********************************************************************
//  void init(void)
//  Inicializa os parâmetros globais de OpenGL
//
// **********************************************************************
void init(void)
{
cout << "Init..." ;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Fundo de tela preto

    imFormatRegisterAVI();
    //imFormatRegisterWMV();
    if(Video.openVideoFile("videos_professor\\1.avi") == 0)
    //if(Video.openVideoFile("Videos\\video_original.avi") == 0)
    {
       cout << "Problemas na abertura do video" << endl;
    }
    else cout << "Abertura OK ! - Nro de Frames:" << Video.getTotalFrames() << endl;
    cout << "Dimensoes do Video:" << Video.SizeX() << " x " << Video.SizeY() <<endl;

cout << "Fim." << endl;

}


// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    gluOrtho2D(0,w,0,h);

    // Set the clipping volume
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


// **********************************************************************
//  void CalculaNivelDeZoom(float &ZoomH, float &ZoomV)
//
//
// **********************************************************************
void CalculaNivelDeZoom(float &ZoomH, float &ZoomV)
{
     ZoomH = (float)glutGet(GLUT_WINDOW_WIDTH)/Video.SizeX();
     ZoomV = (float)glutGet(GLUT_WINDOW_HEIGHT)/Video.SizeY();
}
// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
int frame = 1;
void display( void )
{
    int loadFrameOK;
    float ZoomH, ZoomV;

    glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10,10,-10,10,-1,1);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

    loadFrameOK = Video.loadImageFrame(frame);

    // avança o nro do frame

    frame ++;
    cout << "Frame: " << frame << endl;
    // se atingiu o final do vídeo, então recomeça
    if (frame == Video.getTotalFrames())
    {
        cout << "Ver todo o video: " << watchAll << endl;
         frame = 0;
        // getchar();
         return;
    }
    if (loadFrameOK)
    {
       Video.SetPos(-10,-10);

       // Acerta o zoom da imagem para que ocupe toda a janela
       CalculaNivelDeZoom(ZoomH, ZoomV);
       Video.SetZoomH(ZoomH);
       Video.SetZoomV(ZoomV);

       // Executa filtros
       if (filtrosOn)
       {
          filtros.TonsDeCinza();
          filtros.Mediana();
          filtros.Limiarizacao(33);
          filtros.PintaCirculos(9);
       }

       // Apresenta o video
       Video.Display();
    }
    else cout << "Erro..." << endl;
    glutSwapBuffers();

    // Se watchAll for 'true', executa o display() até o video acabar
    if(watchAll == true){
        display();
    }

}


// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{

    switch ( key )
    {
        case 'f':   filtrosOn = !filtrosOn;
                    break;
        case 'w':   watchAll = !watchAll;
                    break;
        case ' ':
                    break;
        case 27: // Termina o programa qdo
                    Video.closeVideoFile();
                    exit ( 0 );   // a tecla ESC for pressionada
                    break;
        default:
                    break;
    }
    glutPostRedisplay();
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
    switch ( a_keys )
    {
        case GLUT_KEY_UP:       // When Up Arrow Is Pressed...
        break;
        case GLUT_KEY_DOWN:     // When Down Arrow Is Pressed...

        break;
        default:
        break;
    }
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main ( int argc, char** argv )
{
    init ();

    filtros = AplicadorDeFiltros(Video);

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (300,10);

    // Define o tamanho da janela gráfica do programa
    glutInitWindowSize  ( 640, 480);
    glutCreateWindow    ( "AVI Loader - v2.0" );

    glutDisplayFunc ( display );
    glutReshapeFunc ( reshape );
    glutKeyboardFunc ( keyboard );
    glutSpecialFunc ( arrow_keys );
    //glutIdleFunc ( display );

    MessageBox(NULL, "Pressione a barra de espaço para avancar o vídeo.", "Mensagem", MB_OK);
    cout << "Pressione a barra de espaço para avancar o vídeo." << endl;

    glutMainLoop ();
    cout <<"FIM\n";

    return 0;
}


