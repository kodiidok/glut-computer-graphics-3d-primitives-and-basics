
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <SOIL2.h>

int win_posx = 100, win_posy = 100;
int win_width = 720, win_height = 480;

float cam_lx = 0.0f, cam_ly = 0.0f, cam_lz = 0.0f;
float cam_posx = 0.0f, cam_posy = 0.0f, cam_posz = 0.0f;
float cam_rotx = 0.0f, cam_roty = 0.0f, cam_rotz = 0.0f;

float cube_pos[] = { 0.0f, 0.0f, 0.0f };
float cube_rot[] = { 0.0f, 0.0f, 0.0f };
float cube_scl = 1.0f;

const float pi = 3.14;

char keyPressedLabel[20] = "";

void renderBitmapString(float x, float y, void* font, const char* string) {
	glRasterPos2f(x, y);
	while (*string) {
		glutBitmapCharacter(font, *string);
		string++;
	}
}

void displayLabel() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);  // Set orthographic projection for 2D rendering

	glDisable(GL_LIGHTING);  // Disable lighting for text rendering

	glColor3f(1.0f, 1.0f, 1.0f);  // Set text color to white
	renderBitmapString(-9.0f, 9.0f, GLUT_BITMAP_HELVETICA_12, "Key Pressed:");
	renderBitmapString(-9.0f, 8.5f, GLUT_BITMAP_HELVETICA_12, keyPressedLabel);

	glEnable(GL_LIGHTING);  // Re-enable lighting after text rendering
}

void cube() {
	GLfloat cube_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat cube_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Red color for the cube
	GLfloat cube_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat cube_mat_shininess[] = { 100.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, cube_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cube_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, cube_mat_shininess);

	glutSolidCube(1.0); // Draw a solid cube
}

void axes() {
	glEnable(GL_COLOR_MATERIAL);
	// x axis
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); // red
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glEnd();

	// y axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f); // green
	glVertex3f(0.0f, -10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glEnd();

	// z axis
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
}

void spin_cube(int value) {
	cube_rot[0] += 15.0f;
	cube_rot[1] += 10.0f;
	cube_rot[2] += 5.0f;
	glutPostRedisplay();
}

void camera() {
	float ex = 2.0f, ey = 2.0f, ez = 2.0f;
	float cx = 0.0f, cy = 0.0f, cz = 0.0f;
	float upx = 0.0f, upy = 1.0f, upz = 0.0f;
	float fovy = 120.0f, z_near = 0.1f, z_far = 100.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fovy, (float)win_width / (float)win_height, z_near, z_far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(ex + cam_lx, ey + cam_ly, ez + cam_lz, cx, cy, cz, upx, upy, upz);

	glTranslatef(cam_posx, cam_posy, cam_posz);

	glRotatef(cam_rotx, 1.0f, 0.0f, 0.0f);
	glRotatef(cam_roty, 0.0f, 1.0f, 0.0f);
	glRotatef(cam_rotz, 0.0f, 0.0f, 1.0f);
}

void ambientLight() {
	glEnable(GL_LIGHT0);
	GLfloat ambient_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };  // Ambient light color
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
}

void pointLight() {
	GLfloat position[] = { 2.0f, 2.0f, 2.0f, 1.0f };  // Point light position
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Diffuse light color

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, position); // Point light position
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse); // Point light color
}

void spotLight() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);  // Spotlight

	GLfloat light_position[] = { 1.0f, 4.0f, 1.0f, 1.0f };  // Spotlight position
	GLfloat light_direction[] = { -1.0f, -2.0f, -1.0f };  // Spotlight direction
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Diffuse light color
	GLfloat light_cutoff = 30.0f;  // Spotlight cutoff angle in degrees

	glLightfv(GL_LIGHT2, GL_POSITION, light_position);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light_cutoff);
}

void lights() {
	ambientLight();
	//pointLight();
	spotLight();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera();
	lights();

	glDisable(GL_LIGHTING);

	axes();

	glEnable(GL_LIGHTING);

	glutTimerFunc(1000 / 60, spin_cube, 0);

	glPushMatrix();
	glTranslatef(cube_pos[0], cube_pos[1], cube_pos[2]);
	glRotatef(cube_rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(cube_rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(cube_rot[2], 0.0f, 0.0f, 1.0f);
	glScalef(cube_scl, cube_scl, cube_scl);
	cube();
	glPopMatrix();

	displayLabel();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(120, aspect_ratio, 0.1f, 100.0f);
}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			cam_posz += 0.5;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Shift + Up Arrow: Zoom In");
		}
		else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			cube_scl += 0.1f;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Ctrl + Up Arrow: Scale Up");
		}
		else {
			cam_posy += 0.5;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Up Arrow: Move Up");
		}
	}

	if (key == GLUT_KEY_DOWN) {
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			cam_posz -= 0.5;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Shift + Down Arrow: Zoom Out");
		}
		else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			cube_scl -= 0.1f;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Ctrl + Down Arrow: Scale Down");
		}
		else {
			cam_posy -= 0.5;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Down Arrow: Move Down");
		}
	}

	if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
		if (key == GLUT_KEY_LEFT) {
			cam_roty -= 5.0;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Alt + Left Arrow: Rotate Left");
		}

		if (key == GLUT_KEY_RIGHT) {
			cam_roty += 5.0;
			snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Alt + Right Arrow: Rotate Right");
		}

		if (key == GLUT_KEY_DOWN) {
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
				cam_rotz -= 5.0;
				snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Alt + Shift + Down Arrow: Rotate Z Axis (Clockwise)");
			}
			else {
				cam_rotx -= 5.0;
				snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Alt + Down Arrow: Rotate X Axis (Clockwise)");
			}
		}

		if (key == GLUT_KEY_UP) {
			if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
				cam_rotz += 5.0;
				snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Alt + Shift + Up Arrow: Rotate Z Axis (Counter-Clockwise)");
			}
			else {
				cam_rotx += 5.0;
				snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Alt + Up Arrow: Rotate X Axis (Counter-Clockwise)");
			}
		}
	}

	if (key == GLUT_KEY_LEFT) {
		cam_posx -= 0.5;
		snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Left Arrow: Move Left");
	}

	if (key == GLUT_KEY_RIGHT) {
		cam_posx += 0.5;
		snprintf(keyPressedLabel, sizeof(keyPressedLabel), "Right Arrow: Move Right");
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	// movement

	if (key == 'w') { // up
		cube_pos[1] += 0.5f;
		snprintf(keyPressedLabel, sizeof(keyPressedLabel), "W: Move Up");
	}
	if (key == 'a') { // left
		cube_pos[0] -= 0.5f;
		snprintf(keyPressedLabel, sizeof(keyPressedLabel), "A: Move Left");
	}
	if (key == 's') { // down
		cube_pos[1] -= 0.5f;
		snprintf(keyPressedLabel, sizeof(keyPressedLabel), "S: Move Down");
	}
	if (key == 'd') { // right
		cube_pos[0] += 0.5f;
		snprintf(keyPressedLabel, sizeof(keyPressedLabel), "D: Move Right");
	}

	glutPostRedisplay();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

	glutInitWindowPosition(win_posx, win_posy);
	glutInitWindowSize(win_width, win_height);
	glutCreateWindow("3D");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutSpecialFunc(keyboardSpecial);
	glutKeyboardFunc(keyboard);

	init();
	glutMainLoop();

	return 0;
}