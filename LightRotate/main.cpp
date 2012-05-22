#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static GLint spin = 0.0;

void init(void) {

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	GLfloat blue_light[] = { 0.0, 0.0, 1.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	


	GLfloat mat_shininess[] = { 50.0 };

	GLfloat light_position[] = { -9.0, 8.0, 10.0, 0.0 };

	GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, white_light);

	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_light);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);

}
void spinDisplay() {
	spin = spin + 2.0;
		if (spin > 360.0) {
			spin = spin - 360;
		}
	spin = (spin + 10) % 360;

	glutPostRedisplay();
}
void display(void) {
     
     glClearColor(0.2, 0.4, 1.6, 1);
     glColor3f(0.0, 0.8, 0.2);
     GLfloat light_position[] = { 0.0, 0.0, 0.8, 1.0};
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glPushMatrix();
	 gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	 
     glPushMatrix();
     glRotated(spin, 1.0, 0.0, 0.0);
     glLightfv(GL_LIGHT0, GL_POSITION, light_position);
     glPopMatrix();

	 //glutSolidSphere(1.0, 20.0, 20.0);
   

	 glutSolidTorus(0.5,1.0,6.0,6.0);
	 
	 glPopMatrix();

	 glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w, 1.5 * (GLfloat) h
				/ (GLfloat) w, -10.0, 10.0);
	} else {
		glOrtho(-1.5 * (GLfloat) w / (GLfloat) h, 1.5 * (GLfloat) w
				/ (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			spinDisplay();
		glutPostRedisplay();
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("lighting");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
