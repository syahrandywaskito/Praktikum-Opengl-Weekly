#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

float trans_x = -0.7f;
float trans_y = -1.0f;
float direction_scale_x = 1.0f;

float max_tran_y = -0.5f;

GLuint mountainTextureID;
GLuint wallTextureID;
GLuint woodTextureID;
GLuint leafTextureID;

// Fungsi callback untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Translasi
        case 'a':
        case 'A':
            trans_x -= 0.05f;
            direction_scale_x = -1.0f;
            break;
        case 'd':
        case 'D':
            trans_x += 0.05f;
            direction_scale_x = 1.0f;
            break;
        case 'w':
        case 'W':
            if (max_tran_y >= trans_y)
            {
                trans_y += 0.05f;
            }
            else
            {
                trans_y = max_tran_y;
            }
            break;
        case 's':
        case 'S':
            trans_y -= 0.05f;
            break;

        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay(); // memaksa opengl untuk render ulang 
}

void loadLeafTexture()
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load("src/leaf_texture.jpeg", &width, &height, &nrChannels, 4);
    if (data)
    {
        glGenTextures(1, &leafTextureID);
        glBindTexture(GL_TEXTURE_2D, leafTextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void loadWoodTexture()
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load("src/wood_texture.jpeg", &width, &height, &nrChannels, 3);
    if (data)
    {
        glGenTextures(1, &woodTextureID);
        glBindTexture(GL_TEXTURE_2D, woodTextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void loadWallTexture()
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load("src/wall_texture.jpeg", &width, &height, &nrChannels, 4);
    if (data)
    {
        glGenTextures(1, &wallTextureID);
        glBindTexture(GL_TEXTURE_2D, wallTextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void loadMountainTexture()
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load("src/mountain_texture.jpg", &width, &height, &nrChannels, 3);
    if (data)
    {
        glGenTextures(1, &mountainTextureID);
        glBindTexture(GL_TEXTURE_2D, mountainTextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void drawAnimal()
{
    glPushMatrix();
    glTranslatef(trans_x, trans_y, 0.0f);
    glScalef(direction_scale_x * 0.5f, 0.5f, 1.0f);
    // kaki belakang
    glBegin(GL_QUADS);
        glColor3f(0.96f, 0.96f, 0.86f);
        glVertex2f(0.05, 0.2); // kanan atas
        glVertex2f(0.0, 0.2); // kiri atas
        glVertex2f(0.0, 0.1); // kiri bawah
        glVertex2f(0.05, 0.1); // kanan bawah
    glEnd();

    // kaki depan
    glBegin(GL_QUADS);
        glColor3f(0.96f, 0.96f, 0.86f);
        glVertex2f(0.15, 0.2); // kanan atas
        glVertex2f(0.1, 0.2); // kiri atas
        glVertex2f(0.1, 0.1); // kiri bawah
        glVertex2f(0.15, 0.1); // kanan bawah
    glEnd();

    // badan
    glBegin(GL_QUADS);
        glColor3f(0.96f, 0.96f, 0.86f);
        glVertex2f(0.17, 0.3); // kanan atas
        glVertex2f(-0.02, 0.3); // kiri atas
        glVertex2f(-0.02, 0.2); // kiri bawah
        glVertex2f(0.17, 0.2); // kanan bawah
    glEnd();

    // ekor
    glBegin(GL_QUADS);
        glColor3f(0.96f, 0.96f, 0.86f);
        glVertex2f(-0.02, 0.27); // kanan atas
        glVertex2f(-0.04, 0.27); // kiri atas
        glVertex2f(-0.04, 0.23); // kiri bawah
        glVertex2f(-0.02, 0.23); // kanan bawah
    glEnd();

    // leher 
    glBegin(GL_QUADS);
        glColor3f(0.96f, 0.96f, 0.86f);
        glVertex2f(0.17, 0.45); // kanan atas
        glVertex2f(0.11, 0.45); // kiri atas
        glVertex2f(0.11, 0.3); // kiri bawah
        glVertex2f(0.17, 0.3); // kanan bawah
    glEnd();

    // telinga
    glBegin(GL_QUADS);
        glColor3f(0.96f, 0.96f, 0.86f);
        glVertex2f(0.15, 0.49); // kanan atas
        glVertex2f(0.12, 0.49); // kiri atas
        glVertex2f(0.12, 0.45); // kiri bawah
        glVertex2f(0.15, 0.45); // kanan bawah
    glEnd();

    // mata
    glBegin(GL_QUADS);
        glColor3f(0.25f, 0.0f, 0.0f);
        glVertex2f(0.16, 0.43); // kanan atas
        glVertex2f(0.14, 0.43); // kiri atas
        glVertex2f(0.14, 0.41); // kiri bawah
        glVertex2f(0.16, 0.41); // kanan bawah
    glEnd();

    // kepala 
    glBegin(GL_QUADS);
        glColor3f(0.96f, 0.96f, 0.86f);
        glVertex2f(0.2, 0.43); // kanan atas
        glVertex2f(0.17, 0.43); // kiri atas
        glVertex2f(0.17, 0.39); // kiri bawah
        glVertex2f(0.2, 0.39); // kanan bawah
    glEnd();

    glPopMatrix();

}

void reshape(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, w, 0.0, h);

    glMatrixMode(GL_MODELVIEW);
}

void drawTriangleLeft()
{
    // enable texture menggunakan GL Texture 2D
    glEnable(GL_TEXTURE_2D);

    // Bind texture antara GLTEXRURE_2D dengan textureID
    glBindTexture(GL_TEXTURE_2D, mountainTextureID);

    glBegin(GL_TRIANGLES);
        glColor3f(0.45f, 0.6f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); // atur coordinate texture
        glVertex2f(-1.0f, -0.2f);//bawah kiri

        glColor3f(0.45f, 0.6f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);

        glColor3f(0.5f, 0.86f, 0.45f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(-0.5f, 0.2f);
    glEnd();

    glDisable(GL_TEXTURE_2D); // disable texture setelah digunakan
}

void drawTriangleRight()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, mountainTextureID);

    glBegin(GL_TRIANGLES);
        glColor3f(0.45f, 0.6f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(0.5f, -0.2f);//bawah kiri

        glColor3f(0.45f, 0.6f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(-0.3f, -0.2f);

        glColor3f(0.5f, 0.86f, 0.45f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(0.1f, 0.1f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void drawLayer(float panjangKiri, float panjangKanan, float sisiAtas, float sisiBawah, bool isInit = false)
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, wallTextureID);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.5f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(panjangKiri, sisiAtas);// kiri atas

        glColor3f(1.0f, 0.6f, 0.55f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(panjangKanan, (sisiAtas + 0.1));// kanan atas

        glColor3f(1.0f, 0.5f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        if (isInit)
        {
            glVertex2f(panjangKanan, sisiBawah);// kanan bawah
        }
        else
        {
            glVertex2f(panjangKanan, (sisiBawah + 0.1));// kanan bawah
        }
        glColor3f(1.0f, 0.5f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(panjangKiri, sisiBawah);// kiri bawah
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawLineLayer(float panjangKiri, float panjangKanan, float sisiAtas, float sisiBawah, bool isInit = false)
{
    glColor3f(0.1f, 0.1f, 0.0f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(panjangKiri, sisiAtas);// kiri atas
        glVertex2f(panjangKanan, (sisiAtas + 0.1));// kanan atas
        if (isInit)
        {
            glVertex2f(panjangKanan, sisiBawah);// kanan bawah
        }
        else
        {
            glVertex2f(panjangKanan, (sisiBawah + 0.1));// kanan bawah
        }
        glVertex2f(panjangKiri, sisiBawah);// kanan bawah
    glEnd();
}

void drawDoor()
{
    glColor3f(0.3f, 0.15f, 0.0f); // warna pintu

    // Parameter umum pintu
    float dx = 0.1f;   // lebar pintu
    float dy = 0.11f;  // tinggi pintu
    float gap = 0.05f; // jarak antar pintu

    // ----- Layer 1 -----
    int doors1 = 6;
    float yTop1 = -0.57f;
    float yBot1 = yTop1 - dy;
    float xStart1 = -0.4f;
    for (int i = 0; i < doors1; i++) {
        float xLeft = xStart1 + i * (dx + gap);
        float xRight = xLeft + dx;
        glBegin(GL_QUADS);
            glVertex2f(xLeft, yTop1);
            glVertex2f(xRight, yTop1);
            glVertex2f(xRight, yBot1);
            glVertex2f(xLeft, yBot1);
        glEnd();
    }

    // ----- Layer 2 -----
    int doors2 = 4;
    float yTop2 = -0.33f;
    float yBot2 = yTop2 - dy;
    float xStart2 = -0.25f;
    for (int i = 0; i < doors2; i++) {
        float xLeft = xStart2 + i * (dx + gap);
        float xRight = xLeft + dx;
        glBegin(GL_QUADS);
            glVertex2f(xLeft, yTop2);
            glVertex2f(xRight, yTop2);
            glVertex2f(xRight, yBot2);
            glVertex2f(xLeft, yBot2);
        glEnd();
    }

    // ----- Layer 3 -----
    int doors3 = 3;
    float yTop3 = -0.12f;
    float yBot3 = yTop3 - dy;
    float xStart3 = -0.15f;
    for (int i = 0; i < doors3; i++) {
        float xLeft = xStart3 + i * (dx + gap);
        float xRight = xLeft + dx;
        glBegin(GL_QUADS);
            glVertex2f(xLeft, yTop3);
            glVertex2f(xRight, yTop3);
            glVertex2f(xRight, yBot3);
            glVertex2f(xLeft, yBot3);
        glEnd();
    }

    // ----- Layer 4 -----
    int doors4 = 2;
    float yTop4 = 0.07f;
    float yBot4 = yTop4 - dy;
    float xStart4 = -0.1f;
    for (int i = 0; i < doors4; i++) {
        float xLeft = xStart4 + i * (dx + gap);
        float xRight = xLeft + dx;
        glBegin(GL_QUADS);
            glVertex2f(xLeft, yTop4);
            glVertex2f(xRight, yTop4);
            glVertex2f(xRight, yBot4);
            glVertex2f(xLeft, yBot4);
        glEnd();
    }

    // ----- Layer 5 -----
    int doors5 = 1;
    float yTop5 = 0.28f;
    float yBot5 = yTop5 - dy;
    float xStart5 = -0.05f;
    for (int i = 0; i < doors5; i++) {
        float xLeft = xStart5 + i * (dx + gap);
        float xRight = xLeft + dx;
        glBegin(GL_QUADS);
            glVertex2f(xLeft, yTop5);
            glVertex2f(xRight, yTop5);
            glVertex2f(xRight, yBot5);
            glVertex2f(xLeft, yBot5);
        glEnd();
    }
}


void drawTower()
{
    float initSisiKiri = -0.5f;
    float initSisiKanan = 0.5f;
    float initSisiAtas = -0.5f;
    float initSisiBawah = -0.7f;

    float initLineSisiKiri = -0.5f;
    float initLineSisiKanan = 0.5f;
    float initLineSisiAtas = -0.5f;
    float initLineSisiBawah = -0.7f;

    float shrinkSisiKiri = 0.1f;
    float shrinkSisiKanan = -0.1f;
    float tinggiPerLayer = 0.2f;

    drawLayer(initSisiKiri, initSisiKanan, initSisiAtas, initSisiBawah, true);
    drawLineLayer(initLineSisiKiri, initLineSisiKanan, initLineSisiAtas, initLineSisiBawah, true);

    for (int i = 0; i < 4; i++)
    {
        drawLayer((initSisiKiri += shrinkSisiKiri), (initSisiKanan += shrinkSisiKanan), (initSisiAtas += tinggiPerLayer), (initSisiBawah += tinggiPerLayer));
        drawLineLayer((initLineSisiKiri += shrinkSisiKiri), (initLineSisiKanan += shrinkSisiKanan), (initLineSisiAtas += tinggiPerLayer), (initLineSisiBawah += tinggiPerLayer));
    }

    drawDoor();
}

void drawCloud(float x, float y, float size)
{
    glColor3f(1.0f, 1.0f, 1.0f); // warna putih
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x + size * 0.8, y + size * 0.2);
        glVertex2f(x + size * 1.8, y + size * 0.2);
        glVertex2f(x + size * 1.8, y + size * 1.2);
        glVertex2f(x + size * 0.8, y + size * 1.2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(x - size * 0.8, y + size * 0.2);
        glVertex2f(x + size * 0.2, y + size * 0.2);
        glVertex2f(x + size * 0.2, y + size * 1.2);
        glVertex2f(x - size * 0.8, y + size * 1.2);
    glEnd();
}

void drawGrass(float x, float y, float size)
{
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();
}

void drawTree(float x, float y, float size)
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, woodTextureID);

    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x, y);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(x + size * 0.2f, y);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x + size * 0.2f, y + size * 0.6f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(x, y + size * 0.6f);
    glEnd();

    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, leafTextureID);

    glColor3f(0.0f, 0.6f, 0.0f); 
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(x - size * 0.4f, y + size * 0.6f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(x + size * 0.6f, y + size * 0.6f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x + size * 0.6f, y + size * 1.2f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(x - size * 0.4f, y + size * 1.2f);
    glEnd();

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(x - size * 0.3f, y + size * 1.0f);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(x + size * 0.5f, y + size * 1.0f);

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(x + size * 0.5f, y + size * 1.6f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(x - size * 0.3f, y + size * 1.6f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.6f, 0.0f);
        glVertex2f(1.0f, -0.2f);   // kanan atas
        glColor3f(0.0f, 0.25f, 0.0f);
        glVertex2f(1.0f, -1.0f);  // kanan bawah
        glColor3f(0.0f, 0.25f, 0.0f);
        glVertex2f(-1.0f, -1.0f); // kiri bawah
        glColor3f(0.0f, 0.6f, 0.0f);
        glVertex2f(-1.0f, -0.2f);  // kiri atas
    glEnd();

    drawTriangleLeft();
    drawTriangleRight();

    for (float gx = -1.0f; gx < 1.0f; gx += 0.1f)
    {
        for (float gy = -1.0f; gy < -0.2f; gy += 0.1f)
        {
            if (rand() % 3 == 0)
            {
                drawGrass(gx, gy, 0.01f);
            }
        }
    }

    drawTree(-0.9f, -0.6f, 0.2f);
    drawTree(0.7f, -0.6f, 0.25f);
    drawTree(0.0f, -0.6f, 0.15f);

    drawTower();
  
    drawCloud(-0.7f, 0.6f, 0.2f); // kiri atas
    drawCloud(0.2f, 0.7f, 0.15f); // kanan atas

    // draw walkable animal
    drawAnimal();

    glutSwapBuffers();
}

void initColor()
{
      glClearColor(0.5f, 1.0f, 1.0f, 0.0f);
      loadMountainTexture();
      loadWallTexture();
      loadWoodTexture();
      loadLeafTexture();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // di init dulu 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // pakai display apa 
    glutInitWindowSize(700, 700);// set ukuran window
    glutCreateWindow("Evaluasi 1 - Menara Babel 2D"); // beri nama window
    initColor();
    // glutReshapeFunc(reshape);
    glutDisplayFunc(display); // mendisplay bentu
    glutKeyboardFunc(keyboard); // memanggil callback keyboard
    glutMainLoop();
    return 0;
}
