#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include "Application.h"

// vari�veis globais

//! gerenciador da aplicacao IDS
Application   * ptrApp   = NULL;
//! armazena a ultima contagem de ticks para o calculo do delta time entre frames
clock_t         LastTime;

/**
	\fn OnStartGL
	\brief Inicia os parametros do ambiente grafico OPENGL e as variaveis de controle da aplicacao
*/
void OnStartGL()
{
	glEnable( GL_TEXTURE_2D );  // habilita manipula�ao de mapas de textura 2D (imagens)
	glEnable( GL_DEPTH_TEST );  // desenha os poligonos na ordem inversa de profundidade: mais longe --> mais perto
	glEnable( GL_CULL_FACE ); // nao desenha poligonos cujo vetor normal nao esteja orientado para a camera
	glEnable( GL_LIGHTING ); // habilita calculo de modelo de iluminacao
	glEnable( GL_COLOR_MATERIAL );

	glEnable( GL_NORMALIZE );
	glEnable(GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	LastTime = clock();
}

/**
	\fn OnFinishGL
	\brief Finaliza o ambiente OPENGL antes de encerrar a aplicacao
*/
void OnFinishGL()
{}

/**
	\fn OnRenderEvent
	\brief Desenha um frame da animacao a cada vez que um evento de REDISPLAY ocorrer
*/
void OnRenderEvent()
{
	ptrApp->RenderFrame();
}

/**
    \fn OnReshapeEvent()
	\brief Recalcula a aparencia grafico da janela sempre que a mesma for redimensionada
	\param uiWidth  nova largura da janela
	\param uiHeight nova altura da janela
*/
void OnReshapeEvent( GLint uiWidth, GLint uiHeight )
{
	ptrApp->setWindowSize( uiWidth, uiHeight );
}

/**
	\fn OnKeyboardEvent
	\brief Processa eventos do teclado
	\param ucKey codigo da tecla sendo pressionada
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento do teclado
	\param iMouseY posicao vertical do cursor do mouse no momento do evento do teclado
*/
void OnKeyboardEvent( unsigned char ucKey, int iMouseX, int iMouseY )
{
	switch( ucKey )
	{
	// ESC
	case 27: // encerra a aplicacao
		OnFinishGL();
		exit( 0 );
		break;

	}
}

/**
	\fn OnSpecialKeyboardEvent
	\brief Processa eventos para teclas 'especiais' do teclado como setas direcionais, CTRL, ALT, SHIFT, etc.
	\param iKey codigo da tecla sendo pressionada
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento do teclado
	\param iMouseY posicao vertical do cursor do mouse no momento do evento do teclado
*/
void OnSpecialKeyboardEvent( int iKey, int iMouseX, int iMouseY )
{
	switch( iKey )
	{
	case GLUT_KEY_LEFT: break;
	}
}

/**
	\fn OnMouseButtonEvent
	\brief Processa eventos dos botoes do mouse
	\param iButton indica qual botao do mouse foi pressionado
	\param iState indica o estado corrente do referido botao do mouse
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento
	\param iMouseY posicao vertical do cursor do mouse no momento do evento
*/
void OnMouseButtonEvent( int iButton, int iState, int iMouseX, int iMouseY )
{
	switch( iButton )
	{
	case GLUT_LEFT_BUTTON:
		if( iState == GLUT_DOWN )
		{
			// DO SOMETHING HERE
		}
		break;
	}
}

/**
	\fn OnMouseMotionEvent
	\brief Processa eventos de movimentacao do cursor do mouse
	\param iMouseX posicao horizontal do cursor do mouse no momento do evento
	\param iMouseY posicao vertical do cursor do mouse no momento do evento
*/
void OnMouseMotionEvent( int iMouseX, int iMouseY )
{}

/**
	\fn OnIdleEvent
	\brief Executado a cada nova iteracao do loop OPENGL
*/
void OnIdleEvent()
{
	clock_t currTime = clock();
	double elapsedTime = (( double) ( currTime - LastTime )) / CLOCKS_PER_SEC;
	LastTime = currTime;

	ptrApp->Execute( elapsedTime );

	glutSetWindowTitle( ptrApp->getTitle().c_str() );
	glutPostRedisplay();
}

/**
   \fn main()
   \brief Funcao principal representando o ponto de inicio da execu�ao do codigo fonte
   \param argc quantidade de argumentos passados atraves de linha de comando de execucao
   \param argv lista contendo os argumentos passados por linha de comando
   \return int flag que indica sucesso ou falha na execucao da aplicacao
*/
int main( int argc, char ** argv )
{
	ptrApp = new Application();

	// inicializa�ao do ambiente da GLUT
	glutInit( &argc, argv );
	glutInitWindowSize( ptrApp->getWidth(), ptrApp->getHeight() );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutCreateWindow( ptrApp->getTitle().c_str() );

	OnStartGL();

	ptrApp->CreateScene();

	// define as funcoes callback do sistema
	glutDisplayFunc( OnRenderEvent );
	//glutReshapeFunc( OnReshapeEvent );
	glutKeyboardFunc( OnKeyboardEvent );
	glutSpecialFunc( OnSpecialKeyboardEvent );
	glutMouseFunc( OnMouseButtonEvent );
	glutMotionFunc( OnMouseMotionEvent );
	glutIdleFunc( OnIdleEvent );
	//glutFullScreen();
	glutMainLoop();

	return 1;
}
