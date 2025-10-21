#include <GL/glut.h>
#include <iostream>

// Variabel global untuk menyimpan state transformasi
float trans_x = 0.0f;
float trans_y = 0.0f;
float rot_angle = 0.0f;
float scale_factor = 1.0f;

// Deklarasi fungsi-fungsi
void display();
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
    glutInit(&argc, argv); // di init dulu 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // pakai display apa 
    glutInitWindowSize(800, 600); // set ukuran window
    glutCreateWindow("Praktikum Week 4"); // beri nama window

    // Daftarkan fungsi callback
    glutDisplayFunc(display); // mendisplay bentuk
    glutKeyboardFunc(keyboard); // memanggil callback keyboard 

    // Looping render
    glutMainLoop();
    return 0;
}

// Fungsi untuk menggambar objek dan menerapkan transformasi
void display() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // background color
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 1. Translasi
    glTranslatef(trans_x, trans_y, 0.0f);

    // 2. Rotasi
    glRotatef(rot_angle, 0.0f, 0.0f, 1.0f);

    // 3. Scaling
    glScalef(scale_factor, scale_factor, 1.0f);

    // Gambar kotak
    glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, -0.25f);
        glVertex2f( 0.25f, -0.25f);
        glVertex2f( 0.25f,  0.25f);
        glVertex2f(-0.25f,  0.25f);
    glEnd();

    glutSwapBuffers();
}

// Fungsi callback untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Translasi
        case 'a':
        case 'A':
            trans_x -= 0.05f;
            break;
        case 'd':
        case 'D':
            trans_x += 0.05f;
            break;
        case 'w':
        case 'W':
            trans_y += 0.05f;
            break;
        case 's':
        case 'S':
            trans_y -= 0.05f;
            break;

        // Rotasi
        case 'q':
        case 'Q':
            rot_angle -= 5.0f;
            break;
        case 'e':
        case 'E':
            rot_angle += 5.0f;
            break;

        // Scaling
        case '+':
            scale_factor += 0.1f;
            break;
        case '-':
            scale_factor -= 0.1f;
            if (scale_factor < 0.1f) scale_factor = 0.1f; // jika scale ke 0.1 maka tetapkan ke 0.1 (tidak bisa lebih kecil lagi) 
            break;

        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay(); // memaksa opengl untuk render ulang 
}