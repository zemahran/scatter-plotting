#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <fstream>
using namespace std;

void scatterplot(int arr[100][6]);

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	// Reading the file
	ifstream inFile;

	inFile.open("mypoints.txt");

	// Filling a 1D string array with points in the file
	string str = "";
	string arr[100];
	int n = 0;
	if (inFile.is_open())
	{
		while (getline(inFile, str))
		{
			arr[n] = str;
			n++;
		}
		inFile.close();
	}

	// Making it a 2D string array with every point having 6 attributes
	string mypts[100][6];
	for (int i = 0; i < 100; i++) {
		for (int j = 0, k = 0; j < 6, k < 11; j++, k += 2) {
			mypts[i][j] = arr[i][k];
		}
	}

	// Converting strings to integers inside a new 2D int array
	int pts[100][6];
	string rdm;
	int c;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 6; j++) {
			rdm = mypts[i][j];
			stringstream oss(rdm);
			c = 0;
			oss >> c;
			pts[i][j] = c;
		}
	}
	/*now we have a 2D array (pts) that holds 100*6 indices,
	the first dimesnion is the point & the second one is the
	6 attributes of the point. EVERYTHING INTEGER.*/

	scatterplot(pts);	
	glFlush();
}

void scatterplot(int arr[100][6]) {

	// Scatterplot grid
	for (double i = 0; i < 600; i += 100) {
		for (double j = 0; j < 600; j += 100) {
			glColor3f(0.41, 0.41, 0.41);
			glBegin(GL_POLYGON);
			glVertex3f(i, j, 0.0);
			glVertex3f(i + 100, j, 0.0);
			glVertex3f(i + 100, j + 100, 0.0);
			glVertex3f(i, j + 100, 0.0);
			glEnd();
			glPointSize(1);
			glBegin(GL_POINTS);
			glColor3f(0.75, 0.75, 0.75);
			for (int x = i + 10; x < i + 100; x += 10) {
				for (int y = j + 10; y < j + 100; y += 10) {
					glVertex2i(x, y);
				}
			}
			glEnd();
		}
	}

	// Scatterplot fill
	int draw[6];
	for (int i = 0; i < 100; i++) {
		for (int j = 0, b = 0; j < 6; j++) {
			draw[j] = (arr[i][j] * 10) + b;
			glPointSize(5);
			glColor3f(1, 0, 0);
			for (int x = 0; x < 6; x++) {
				for (int y = 0; y < 6; y++) {
					glBegin(GL_POINTS);
					glVertex2i(draw[x], draw[y]);
				}
			}
			glEnd();
			b += 100;
		}
	}
	return;
}

void main(int argc, char** argr) {
		
	glutInit(&argc, argr);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(170, 70);

	glutCreateWindow("OpenGL - 2D Template");
	glutDisplayFunc(Display);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0, 900, 0, 900);

	glutMainLoop();

	_getch();
	return;
}
