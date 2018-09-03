#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>

void OnStartEngine()
{
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_COLOR_MATERIAL );
  glCullFace( GL_BACK );

  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

  GLfloat light_position[] = { 1.0, 3.0, -10.0, 0.0 },
          light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
  glLightfv( GL_LIGHT0, GL_POSITION, light_position );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );

  glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

}

void OnRenderEvent()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );




  glutSwapBuffers();

}

void OnReshapeEvent (GLint uiWidth, GLint uiHeight)
{

}

void OnKeyboardEvent (unsigned char ucKey, int iMouseX, int iMouseY)
{

}

void OnSpecialKeyboardEvent ( int iKey, int iMouseX, int iMouseY)
{

}

void OnMouseButtonEvent (int iButton, int iState, int iMouseX, int iMouseY)
{

}

void OnMouseMotionEvent (int iMouseX, int iMouseY)
{

}

void OnIdleEvent ()
{

}



int main ( int argc, char** argv)
{

  glutInit(&argc, argv);
  glutInitWindowSize( 500, 600);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutCreateWindow(" AniEngine 2017 ");

  OnStartEngine();

  // define as funcoes callback do sistema
	glutDisplayFunc( OnRenderEvent );
	glutReshapeFunc( OnReshapeEvent );
	glutKeyboardFunc( OnKeyboardEvent );
	glutSpecialFunc( OnSpecialKeyboardEvent );
	glutMouseFunc( OnMouseButtonEvent );
	glutMotionFunc( OnMouseMotionEvent );
	glutIdleFunc( OnIdleEvent );

  glutMainLoop();

  return 0;
}
