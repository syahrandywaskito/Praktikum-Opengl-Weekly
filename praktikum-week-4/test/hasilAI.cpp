#include <GL/glut.h>
#include <math.h>
#include <iostream>

const float PI = 3.14159265f;

// Fungsi untuk menggambar lingkaran/elips
void drawEllipse(float centerX, float centerY, float radiusX, float radiusY, int segments = 50) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Pusat lingkaran
    
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = centerX + radiusX * cos(angle);
        float y = centerY + radiusY * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Fungsi untuk menggambar outline lingkaran/elips
void drawEllipseOutline(float centerX, float centerY, float radiusX, float radiusY, int segments = 50) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = centerX + radiusX * cos(angle);
        float y = centerY + radiusY * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Fungsi untuk menggambar persegi panjang (untuk jendela)
void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Fungsi untuk menggambar jendela berbentuk lengkungan
void drawArchWindow(float centerX, float centerY, float width, float height) {
    glColor3f(0.15f, 0.1f, 0.05f); // Warna gelap untuk jendela
    
    // Bagian persegi panjang jendela
    drawRectangle(centerX - width/2, centerY - height/2, 
                 centerX + width/2, centerY + height/4);
    
    // Bagian lengkungan atas jendela
    drawEllipse(centerX, centerY + height/4, width/2, height/4, 20);
}

// Fungsi untuk menggambar jendela-jendela di sekitar tingkat menara
void drawWindows(float centerX, float centerY, float radiusX, float radiusY, int numWindows, float windowWidth = 0.02f, float windowHeight = 0.04f) {
    for (int i = 0; i < numWindows; i++) {
        float angle = 2.0f * PI * i / numWindows;
        float x = centerX + (radiusX - 0.025f) * cos(angle);
        float y = centerY + (radiusY - 0.015f) * sin(angle);
        
        drawArchWindow(x, y, windowWidth, windowHeight);
    }
}

// Fungsi untuk menggambar satu tingkat menara
void drawLevel(float centerX, float centerY, float radiusX, float radiusY, int windows, 
               float r, float g, float b, float shadowR, float shadowG, float shadowB) {
    
    // Gambar bayangan (sedikit offset ke kanan bawah)
    glColor3f(shadowR, shadowG, shadowB);
    drawEllipse(centerX + 0.01f, centerY - 0.01f, radiusX, radiusY);
    
    // Gambar tingkat utama
    glColor3f(r, g, b);
    drawEllipse(centerX, centerY, radiusX, radiusY);
    
    // Gambar outline
    glColor3f(0.4f, 0.3f, 0.2f);
    glLineWidth(2.0f);
    drawEllipseOutline(centerX, centerY, radiusX, radiusY);
    
    // Gambar jendela-jendela
    if (windows > 0) {
        drawWindows(centerX, centerY, radiusX, radiusY, windows);
    }
}

// Fungsi untuk menggambar pegunungan berlapis
void drawMountains() {
    // Pegunungan belakang (paling jauh) - warna lebih pucat
    glColor3f(0.6f, 0.7f, 0.8f);
    drawEllipse(-0.8f, -0.1f, 0.4f, 0.2f);
    drawEllipse(-0.3f, -0.05f, 0.35f, 0.18f);
    drawEllipse(0.3f, -0.08f, 0.3f, 0.15f);
    drawEllipse(0.7f, -0.12f, 0.25f, 0.12f);
    
    // Pegunungan tengah
    glColor3f(0.5f, 0.65f, 0.7f);
    drawEllipse(-0.9f, -0.15f, 0.3f, 0.15f);
    drawEllipse(-0.4f, -0.12f, 0.28f, 0.13f);
    drawEllipse(0.1f, -0.14f, 0.25f, 0.12f);
    drawEllipse(0.6f, -0.16f, 0.2f, 0.1f);
    
    // Pegunungan depan (lebih gelap)
    glColor3f(0.4f, 0.6f, 0.65f);
    drawEllipse(-0.7f, -0.2f, 0.25f, 0.12f);
    drawEllipse(0.8f, -0.22f, 0.18f, 0.1f);
}

// Fungsi untuk menggambar awan-awan
void drawClouds() {
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Awan kiri atas
    drawEllipse(-0.7f, 0.7f, 0.08f, 0.04f);
    drawEllipse(-0.65f, 0.72f, 0.06f, 0.03f);
    drawEllipse(-0.62f, 0.69f, 0.05f, 0.025f);
    
    // Awan tengah
    drawEllipse(0.2f, 0.8f, 0.1f, 0.05f);
    drawEllipse(0.25f, 0.82f, 0.08f, 0.04f);
    drawEllipse(0.28f, 0.79f, 0.06f, 0.03f);
    
    // Awan kanan
    drawEllipse(0.75f, 0.65f, 0.07f, 0.035f);
    drawEllipse(0.78f, 0.67f, 0.05f, 0.025f);
    
    // Awan kecil tersebar
    drawEllipse(-0.3f, 0.85f, 0.04f, 0.02f);
    drawEllipse(0.5f, 0.9f, 0.03f, 0.015f);
}

// Fungsi untuk menggambar pohon-pohon
void drawTrees() {
    // Pohon kiri
    glColor3f(0.4f, 0.2f, 0.1f); // Batang coklat
    drawRectangle(-0.85f, -0.3f, -0.82f, -0.2f);
    glColor3f(0.2f, 0.6f, 0.1f); // Daun hijau
    drawEllipse(-0.835f, -0.18f, 0.04f, 0.06f);
    
    // Pohon tengah kiri
    glColor3f(0.4f, 0.2f, 0.1f);
    drawRectangle(-0.4f, -0.3f, -0.37f, -0.22f);
    glColor3f(0.25f, 0.65f, 0.15f);
    drawEllipse(-0.385f, -0.2f, 0.05f, 0.07f);
    
    // Pohon kanan
    glColor3f(0.4f, 0.2f, 0.1f);
    drawRectangle(0.82f, -0.3f, 0.85f, -0.22f);
    glColor3f(0.2f, 0.6f, 0.1f);
    drawEllipse(0.835f, -0.2f, 0.045f, 0.065f);
    
    // Pohon kecil di kejauhan
    glColor3f(0.35f, 0.55f, 0.6f); // Warna lebih pucat untuk jarak
    drawEllipse(-0.2f, -0.12f, 0.02f, 0.03f);
    drawEllipse(0.4f, -0.1f, 0.015f, 0.025f);
}

// Fungsi untuk menggambar sungai yang berkelok
void drawRiver() {
    glColor3f(0.3f, 0.6f, 0.9f);
    
    // Sungai berkelok dari kanan bawah ke tengah
    drawEllipse(0.85f, -0.4f, 0.12f, 0.08f);
    drawEllipse(0.75f, -0.35f, 0.1f, 0.06f);
    drawEllipse(0.65f, -0.32f, 0.08f, 0.05f);
    drawEllipse(0.58f, -0.3f, 0.06f, 0.04f);
    
    // Refleksi cahaya di air
    glColor3f(0.7f, 0.85f, 1.0f);
    drawEllipse(0.82f, -0.38f, 0.03f, 0.02f);
    drawEllipse(0.72f, -0.33f, 0.025f, 0.015f);
    drawEllipse(0.62f, -0.31f, 0.02f, 0.01f);
}

// Fungsi untuk menggambar rumput dan detail tanah
void drawGrassDetails() {
    // Tanah dasar dengan gradasi
    for (int i = 0; i < 10; i++) {
        float y1 = -1.0f + (0.7f * i / 10);
        float y2 = -1.0f + (0.7f * (i + 1) / 10);
        float green = 0.5f + (0.25f * i / 10);
        glColor3f(0.2f, green, 0.15f);
        drawRectangle(-1.0f, y1, 1.0f, y2);
    }
    
    // Rumput-rumput kecil
    glColor3f(0.25f, 0.7f, 0.2f);
    for (int i = 0; i < 20; i++) {
        float x = -0.9f + (1.8f * i / 20);
        if (x < -0.2f || x > 0.2f) { // Hindari area menara
            drawRectangle(x - 0.005f, -0.32f, x + 0.005f, -0.28f);
        }
    }
    
    // Bunga-bunga kecil
    glColor3f(0.9f, 0.7f, 0.3f); // Kuning
    drawEllipse(-0.6f, -0.28f, 0.008f, 0.008f);
    drawEllipse(0.7f, -0.29f, 0.006f, 0.006f);
    
    glColor3f(0.9f, 0.4f, 0.5f); // Pink
    drawEllipse(-0.3f, -0.29f, 0.007f, 0.007f);
    drawEllipse(0.5f, -0.28f, 0.006f, 0.006f);
}

// Fungsi untuk menggambar langit dengan gradasi yang lebih halus
void drawSky() {
    // Gradasi langit dari biru muda di bawah ke biru tua di atas
    for (int i = 0; i < 50; i++) {
        float y1 = -0.25f + (1.25f * i / 50);
        float y2 = -0.25f + (1.25f * (i + 1) / 50);
        
        // Gradasi warna dari biru muda ke biru langit
        float ratio = (float)i / 50;
        float r = 0.7f - (0.2f * ratio);
        float g = 0.9f - (0.1f * ratio);
        float b = 1.0f;
        
        glColor3f(r, g, b);
        drawRectangle(-1.0f, y1, 1.0f, y2);
    }
}

// Fungsi untuk menggambar bagian atas yang rusak
void drawRuinedTop(float centerX, float centerY, float radiusX, float radiusY) {
    // Bagian utama yang tersisa
    glColor3f(0.75f, 0.6f, 0.4f);
    drawEllipse(centerX, centerY, radiusX, radiusY);
    
    // Outline
    glColor3f(0.4f, 0.3f, 0.2f);
    glLineWidth(2.0f);
    drawEllipseOutline(centerX, centerY, radiusX, radiusY);
    
    // Puing-puing yang hancur
    glColor3f(0.6f, 0.45f, 0.3f);
    // Puing kiri
    drawEllipse(centerX - radiusX/2, centerY + radiusY/2, 0.015f, 0.02f);
    drawEllipse(centerX - radiusX/3, centerY + radiusY/3, 0.01f, 0.015f);
    
    // Puing kanan
    drawEllipse(centerX + radiusX/2, centerY + radiusY/2, 0.012f, 0.018f);
    drawEllipse(centerX + radiusX/4, centerY + radiusY/2, 0.008f, 0.012f);
    
    // Puing tengah
    drawEllipse(centerX, centerY + radiusY/2, 0.01f, 0.014f);
}

// Fungsi untuk menggambar Menara Babel
void drawTowerOfBabel() {
    // Data untuk setiap tingkat: centerY, radiusX, radiusY, numWindows, r, g, b
    // Menara yang lebih tinggi dan ramping
    float levels[][7] = {
        // Base level (terbesar) - lebih tinggi
        {-0.22f, 0.32f, 0.06f, 20, 0.78f, 0.63f, 0.42f},
        {-0.14f, 0.29f, 0.055f, 18, 0.79f, 0.64f, 0.43f},
        {-0.07f, 0.26f, 0.05f, 16, 0.80f, 0.65f, 0.44f},
        {0.0f, 0.23f, 0.045f, 14, 0.81f, 0.66f, 0.45f},
        {0.065f, 0.20f, 0.04f, 13, 0.82f, 0.67f, 0.46f},
        {0.125f, 0.17f, 0.035f, 12, 0.83f, 0.68f, 0.47f},
        {0.18f, 0.14f, 0.03f, 11, 0.84f, 0.69f, 0.48f},
        {0.23f, 0.11f, 0.025f, 10, 0.85f, 0.70f, 0.49f},
        {0.275f, 0.08f, 0.02f, 8, 0.86f, 0.71f, 0.50f},
        {0.315f, 0.05f, 0.015f, 6, 0.87f, 0.72f, 0.51f}
    };
    
    int numLevels = sizeof(levels) / sizeof(levels[0]);
    float centerX = 0.0f;
    
    // Gambar setiap tingkat dari bawah ke atas (kecuali yang teratas)
    for (int i = 0; i < numLevels - 2; i++) {
        float centerY = levels[i][0];
        float radiusX = levels[i][1];
        float radiusY = levels[i][2];
        int windows = (int)levels[i][3];
        float r = levels[i][4];
        float g = levels[i][5];
        float b = levels[i][6];
        
        // Warna bayangan (lebih gelap)
        float shadowR = r * 0.6f;
        float shadowG = g * 0.6f;
        float shadowB = b * 0.6f;
        
        drawLevel(centerX, centerY, radiusX, radiusY, windows, r, g, b, shadowR, shadowG, shadowB);
    }
    
    // Gambar bagian atas yang rusak
    drawRuinedTop(centerX, levels[numLevels-2][0], levels[numLevels-2][1], levels[numLevels-2][2]);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Gambar background dari belakang ke depan
    drawSky();
    drawClouds();
    drawMountains();
    drawGrassDetails();
    drawRiver();
    drawTrees();
    
    // Gambar Menara Babel
    drawTowerOfBabel();
    
    glFlush();
}

void init() {
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f); // Warna langit biru muda
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (width <= height) {
        gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)width, 
                   1.0 * (GLfloat)height / (GLfloat)width);
    } else {
        gluOrtho2D(-1.0 * (GLfloat)width / (GLfloat)height, 
                   1.0 * (GLfloat)width / (GLfloat)height, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Menara Babel 2D - OpenGL");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    std::cout << "Menara Babel 2D telah dibuat!" << std::endl;
    std::cout << "Tekan ESC atau tutup jendela untuk keluar." << std::endl;
    
    glutMainLoop();
    return 0;
}

// Compile dengan: g++ -o tower tower_of_babel.cpp -lGL -lGLU -lglut