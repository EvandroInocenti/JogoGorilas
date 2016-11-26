#include <math.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592
#define janela_altura 600
#define janela_largura 800
int larguraIni = -400, larguraFim = -300;
int alturaIni = -400, alturaFim = -100;
int transladaBananaY = 130;
int transladaBananaX = -350;

void visualizacao() {
	glMatrixMode(GL_PROJECTION);	//Matriz de projeção
	glLoadIdentity();				//Zera transformações
	//Configura perspectiva
	glMatrixMode(GL_MODELVIEW);		//Muda p/matriz de visualização
	glLoadIdentity();				//Zera transformações
}

void teclado(unsigned char key, int x, int y) {

	switch (key) {
	case 27:	//Tecla ESC
		exit(0);
		break;
	default:
		break;
	}
	visualizacao();			//Método que aplica os novos parâmetros
	glutPostRedisplay();	//Força redesenho
}

void teclasEspeciais(int tecla, int x, int y){
	switch (tecla){
	case GLUT_KEY_LEFT:
		
		break;
	case GLUT_KEY_RIGHT:
		
		break;
	default:
		break;
	}
	visualizacao();
	glutPostRedisplay();
}

void sol(){
	// glTranslated(0, -100, 0);
	glPushMatrix();
	glTranslatef(0, 200, 0);
	glColor3f(1.0, 1.0, 0.0);
	GLfloat circ_pnt = 100;
	GLfloat angCirc, raioX = 30.0f, raioY = 30.0f;
	GLfloat ang = 2 * PI;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++){
		angCirc = (ang*i) / circ_pnt;
		glVertex2f(cos(angCirc)*raioX, sin(angCirc)*raioY);
		//printf("%f   %f\n", cos(ang)*raioX, sin(ang)*raioY);
	}
	glEnd();
	glPopMatrix();

	//raios
	glBegin(GL_LINES);
	glVertex2d(30, 200);
	glVertex2d(60, 200);
	glVertex2d(20, 220);
	glVertex2d(40, 240);
	glVertex2d(0, 230);
	glVertex2d(0, 250);
	glVertex2d(-30, 200);
	glVertex2d(-60, 200);
	glVertex2d(-20, 220);
	glVertex2d(-40, 240);
	glVertex2d(-20, 180);
	glVertex2d(-40, 160);
	glVertex2d(0, 150);
	glVertex2d(0, 170);
	glVertex2d(20, 180);
	glVertex2d(40, 160);
	glEnd();

	//Olhos
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2d(-10, 210);
	glVertex2d(-10, 217);
	glVertex2d(-7, 213);
	glVertex2d(-14, 213);
	glVertex2d(10, 210);
	glVertex2d(10, 217);
	glVertex2d(6, 213);
	glVertex2d(13, 213);
	glEnd();

	//boca
	glPushMatrix();
	glTranslatef(0, 190, 0);
	GLfloat circ = 100;
	GLfloat angBoca, rX = 14.0f, rY = 2.0f;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ; i++){
		angBoca = (ang*i) / circ;
		glVertex2f(cos(angBoca)*rX, sin(angBoca)*rY);
	}
	glEnd();
	glPopMatrix();
}

void predio1(){
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int x = larguraIni; x <= larguraFim; x++){
		for (int y = alturaIni; y <= alturaFim; y++){
			glVertex2i(x, y);
		}
	}
	glEnd();
}

void predio2(){
	/*glEnable(GL_TEXTURE_CUBE_MAP_EXT);

	glTexGenfv(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);
	glTexGenfv(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);
	glTexGenfv(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	*/
}

void banana(){
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(transladaBananaX, transladaBananaY, 0);
	glBegin(GL_QUADS);
	glVertex2i(-10, -10);
	glVertex2i(-10, 10);
	glVertex2i(10, 10);
	glVertex2i(10, -10);
	glEnd();
	glPopMatrix();
}

void colisao(){
	//printf("colidiu na altura %d: \n", transladaBananaY);

	if ((transladaBananaY == alturaFim + 10)) {
		if ((transladaBananaX >= larguraIni) && (transladaBananaX <= larguraFim)){
			
			glColor3i(0.0, 0.0, 1.0);
			glPointSize(5);
		
		//teste de colisão
			glBegin(GL_POINTS);
			glVertex2i(-350, -100);
			glVertex2i(-355, -105);
			glVertex2i(-350, -105);
			glVertex2i(-355, -100);
			glEnd();

	
			printf("colidiu na altura %d: \n", transladaBananaX);
			transladaBananaY = 130;
			transladaBananaX = -350;
		}
	}

}

void animacao(int valor){

	if (transladaBananaY < 1200){
		transladaBananaY -= 10;
	}

	glutPostRedisplay();
	glutTimerFunc(150, animacao, 1);
}


void desenha() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 1.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
	glViewport(0, 0, janela_largura, janela_altura);
	sol();
	banana();
	predio1();
	colisao();
	

	glutSwapBuffers();
}

void janela(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, janela_largura, 0, janela_altura);
	glMatrixMode(GL_MODELVIEW);

}

void inicializa() {
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(200, 50); // posicao que surge a janela
	glutCreateWindow("Jogo Gorilas");//Cria janela
	glutReshapeFunc(janela);
	glutDisplayFunc(desenha);
	glutKeyboardFunc(teclado);
	glutTimerFunc(150, animacao, 1);

	glutMainLoop();
	return(0);
}