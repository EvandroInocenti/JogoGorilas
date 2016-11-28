#include <math.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

#define PI 3.141592
#define janela_altura 600
#define janela_largura 800

typedef struct {
	int x;
	int y;
	bool ativo;
} PONTO;

typedef struct {
	PONTO pontos[80][400];
	int altura;
	int lagura;
	int posIni;
	float red;
	float green;
	float blue;
} PREDIO;


//DECLARAÇÃO DE FUNCOES

PREDIO* createPredio(int posIni, int largura = 0);
PREDIO* createPredios();
PREDIO* putPredio(PREDIO* predios, PREDIO* newPredio);
void pintarPredio(PREDIO* predio);
void pintarPredios(PREDIO* predios, int qtdePredios);

bool criarPredios = true;
bool colidiuPredio = false;

int larguraIni = -400, larguraFim = -300;
int alturaIni = -400, alturaFim = -100;

int transladaBananaY = 500;
int transladaBananaX = 20;

int angRotBan;

PREDIO* predios;
int qtdePredios;


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
	
	glPushMatrix();
	glTranslatef(400, 500, 0);
	glColor3f(1.0, 0.6, 0.2);
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
	glPushMatrix();
	glTranslatef(400, 300, 0);
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
	glPopMatrix();

	//boca
	glPushMatrix();
	glTranslatef(400, 490, 0);
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

PREDIO* createPredio(int posIni, int largura) {
	PREDIO* predio = (PREDIO*) malloc(sizeof(PREDIO));
	predio->posIni = posIni;
	predio->altura = (rand() % 201) + 200;
	if (largura > 0)
		predio->lagura = largura;
	else
		predio->lagura = (rand() % 11) + 70;

	predio->red = (rand() % 100) + 1;
	predio->green = (rand() % 100) + 1;
	predio->blue = (rand() % 60) + 1;

	predio->red /= 100.0;
	predio->green /= 100.0;
	predio->blue /= 100.0;

	printf("\n red %0.2f - green %0.2f - blue %0.2f ", predio->red, predio->green, predio->blue);

	for (int x = 0; x <= predio->lagura; x++) // linha
	{
		for (int y = 0; y <= predio->altura; y++) {
			predio->pontos[x][y].ativo = true;
			predio->pontos[x][y].x = x + posIni;
			predio->pontos[x][y].y = y;
		}

	}
	return predio;
}

PREDIO* putPredio(PREDIO* predios, PREDIO* newPredio) {
	qtdePredios++;
	PREDIO* lstPredios = (PREDIO*) calloc(qtdePredios, sizeof(PREDIO));

	for (int i = 0; i < (qtdePredios-1); i++)
	{
		lstPredios[i] = predios[i];
	}
	lstPredios[qtdePredios - 1] = *newPredio;//verifcar memori leak
	return lstPredios;
}

PREDIO* createPredios() {
	int larguraTotalAtual = 0; 

	while (larguraTotalAtual < janela_largura){
		PREDIO* newPredio = createPredio(larguraTotalAtual);
		larguraTotalAtual += newPredio->lagura;
		predios = putPredio(predios, newPredio);
	}
	return predios;
}

void pintarPredios(PREDIO* predios, int qtdePredios){
	for (int i = 0; i < qtdePredios; i++)
	{
		pintarPredio(predios);
		predios++;
	}
}

void pintarPredio(PREDIO* predio) {
	glColor3f(predio->red, predio->green, predio->blue);
	for (int x = 0; x <= predio->lagura; x++){
		for (int y = 0; y <= predio->altura; y++){
			if (!predio->pontos[x][y].ativo)
				continue;
			int xPonto = predio->pontos[x][y].x;
			int yPonto = predio->pontos[x][y].y;
			glBegin(GL_QUADS);
			glVertex2i(xPonto, yPonto);
			glVertex2i(xPonto + 1, yPonto);
			glVertex2i(xPonto + 1, yPonto + 1);
			glVertex2i(xPonto, yPonto + 1);
			glEnd();
		}
	}
}

void banana(){
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(transladaBananaX, transladaBananaY, 0);
	glRotated(angRotBan, 0, 0, 1);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2i(8, 5);
	glVertex2i(0, 0);
	glVertex2i(-5, 0);
	glVertex2i(-13, 5);
	glEnd();
	glPopMatrix();

}

void colisaoPredio(){
	for (int i = 0; i < qtdePredios; i++){
		if ((transladaBananaY <= predios[i].altura)) {
			if ((transladaBananaX >= predios[i].posIni) && (transladaBananaX <= (predios[i].posIni + predios[i].lagura))){
				//teste de colisão
				
				int colideLarg = predios[i].lagura/3;

				glTranslated(colideLarg, predios[i].altura, 0);
				
				glColor3f(1.0, 0.2, 0.0);
				GLfloat circ = 100;
				GLfloat angExp, rX = 8.0f, rY = 5.0f;
				GLfloat ang = 2 * PI;
				glBegin(GL_POLYGON);
				for (int i = 0; i < circ; i++){
					angExp = (ang*i) / circ;
					glVertex2f(cos(angExp)*rX, sin(angExp)*rY);
					
					//predio->pontos[x][y].ativo = false;		

				}
				glEnd();

				colidiuPredio = true;

				printf("colidiu na altura %d: \n", predios[i].altura);
				printf("colidiu na largura %d: \n", predios[i].pontos);
				transladaBananaY = 500;
				transladaBananaX = 20;
			}
		}
	}
}

void animacao(int valor){

	if (transladaBananaY < 1200){
		transladaBananaY -= 10;
		angRotBan -= 45;
	}

	glutPostRedisplay();
	glutTimerFunc(150, animacao, 1);
}


void desenha() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 1.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	sol();
	banana();
	//predio1();
	pintarPredios(predios, qtdePredios);
	colisaoPredio();


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
	if (criarPredios) {
		predios = createPredios();
		criarPredios = false;
	}
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