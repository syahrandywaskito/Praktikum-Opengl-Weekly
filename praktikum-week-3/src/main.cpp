#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

void drawAxes() {
    // Gambar garis sumbu X (merah)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();

    // Gambar garis sumbu Y (hijau)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Kotak merah
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, 0.1f);
        glVertex2f(-0.3f, 0.1f);
        glVertex2f(-0.3f, 0.6f);
        glVertex2f(-0.8f, 0.6f);
    glEnd();

    // Kotak hijau
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.7f, -0.5f);
        glVertex2f(-0.2f, -0.5f);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.7f, 0.0f);
    glEnd();

    // Kotak gradien
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.8f, -0.6f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.5f, -0.6f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.3f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.8f, -0.3f); // kiri atas
    glEnd();

    // Segitiga biru
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.1f, -0.5f); // kiri
    glVertex2f(0.6f, -0.5f); // kanan
    glVertex2f(0.33f, -0.1f); // pusat
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f);
    for (int i = 0; i < 6; i++) {
        float angle = 2.0 * 3.1415926535 * i / 6.0;
        glVertex2f(0.4f + 0.2 * cos(angle), 0.4f + 0.2 * sin(angle));
    }
    glEnd();
    
    // Segitiga terbalik (gradien)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f); // Merah
    glVertex2f(0.3f, -0.35f);      // Kiri atas
    glColor3f(0.0f, 1.0f, 0.0f); // Hijau
    glVertex2f(0.8f, -0.35f);      // Kanan atas
    glColor3f(0.0f, 0.0f, 1.0f); // Biru
    glVertex2f(0.55f, -0.85f);    // Bawah
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Praktikum Week 3");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}