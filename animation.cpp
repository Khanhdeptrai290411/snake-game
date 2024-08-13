#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>  
float sunX = -0.8;  
float sunY = -0.8;
float t = 0.0;  
const float PI = 3.14159;
bool isSunSet = false;  
bool startGame = false; 
int playX, playY;
typedef struct {
    float x, y, width, height;
} Button;

Button playButton = {-0.1f, -0.5f, 0.2f, 0.1f};

void drawSun() {
    glColor3f(1.0, 1.0, 0.0);  
    float radius = 0.1;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);  

    for (int angle = 0; angle <= 360; angle += 10) {
        float rad = angle * PI / 180.0;
        glVertex2f(radius * cos(rad), radius * sin(rad));
    }
    
    glEnd();
}




void drawMidpointLine(float x1, float y1, float x2, float y2) {
    int Dx = abs(int(x2 - x1));
    int Dy = abs(int(y2 - y1));
    int x = int(x1);
    int y = int(y1);
    int x_unit = (x1 < x2) ? 1 : -1;
    int y_unit = (y1 < y2) ? 1 : -1;
    
    // Tính toán giá tr? d
    int d;
    int x_end, y_end;
    if (Dx > Dy) {
        d = 2 * Dy - Dx;
        x_end = int(x2);
        y_end = int(y1);
        while (x != x_end) {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            
            x += x_unit;
            if (d > 0) {
                y += y_unit;
                d += 2 * (Dy - Dx);
            } else {
                d += 2 * Dy;
            }
        }
    } else {
        d = 2 * Dx - Dy;
        x_end = int(x1);
        y_end = int(y2);
        while (y != y_end) {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            
            y += y_unit;
            if (d > 0) {
                x += x_unit;
                d += 2 * (Dx - Dy);
            } else {
                d += 2 * Dx;
            }
        }
    }

    glBegin(GL_POINTS);
    glVertex2i(x_end, y_end);
    glEnd();
}


void drawThickLine(float x1, float y1, float x2, float y2, float thickness) {
    float angle = atan2(y2 - y1, x2 - x1);
    float xOffset = sin(angle) * thickness / 2;
    float yOffset = cos(angle) * thickness / 2;

    glBegin(GL_QUADS);
    glVertex2f(x1 - xOffset, y1 + yOffset);
    glVertex2f(x2 - xOffset, y2 + yOffset);
    glVertex2f(x2 + xOffset, y2 - yOffset);
    glVertex2f(x1 + xOffset, y1 - yOffset);
    glEnd();
}

void drawHouse() {

    glColor3f(0.8, 0.5, 0.2);  


    glBegin(GL_QUADS);
    glVertex2f(-0.2, -0.3);
    glVertex2f(0.2, -0.3);
    glVertex2f(0.2, 0.2);
    glVertex2f(-0.2, 0.2);
    glEnd();

 
    glColor3f(0.0, 0.0, 0.0);  
    drawMidpointLine(-0.2, -0.3, 0.2, -0.3);  
    drawMidpointLine(0.2, -0.3, 0.2, 0.2);  
    drawMidpointLine(0.2, 0.2, -0.2, 0.2);  
    drawMidpointLine(-0.2, 0.2, -0.2, -0.3);


    glColor3f(0.7, 0.3, 0.1);  
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25, 0.2);
    glVertex2f(0.25, 0.2);
    glVertex2f(0.0, 0.5);
    glEnd();


    glColor3f(0.5, 0.3, 0.1);  
    glBegin(GL_QUADS);
    glVertex2f(-0.05, -0.3);
    glVertex2f(0.05, -0.3);
    glVertex2f(0.05, -0.1);
    glVertex2f(-0.05, -0.1);
    glEnd();

   
    glColor3f(1.0, 1.0, 1.0);  
    glBegin(GL_QUADS);
    glVertex2f(-0.12, -0.12); 
    glVertex2f(-0.02, -0.12);
    glVertex2f(-0.02, -0.02);
    glVertex2f(-0.12, -0.02);
    glEnd();

  
    glColor3f(0.0, 0.0, 0.0);  
    drawMidpointLine(-0.15, -0.15, -0.05, -0.15);  
    drawMidpointLine(-0.05, -0.15, -0.05, -0.05); 
    drawMidpointLine(-0.05, -0.05, -0.15, -0.05); 
    drawMidpointLine(-0.15, -0.05, -0.15, -0.15); 
}





void drawTree(float x, float y) {
  
    glColor3f(0.55, 0.27, 0.07); 
    drawThickLine(x - 0.05, y, x + 0.05, y, 0.01);
    drawThickLine(x + 0.05, y, x + 0.05, y + 0.2, 0.01);
    drawThickLine(x + 0.05, y + 0.2, x - 0.05, y + 0.2, 0.01);
    drawThickLine(x - 0.05, y + 0.2, x - 0.05, y, 0.01);


    glColor3f(0.0, 0.8, 0.0);  
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y + 0.2);  
    for (int angle = 0; angle <= 360; angle += 10) {
        float rad = angle * PI / 180.0;
        glVertex2f(x + 0.1 * cos(rad), y + 0.2 + 0.1 * sin(rad));
    }
    glEnd();
}

void drawSymmetricTree(float x, float y) {
    drawTree(x, y);
    drawTree(-x, y);
}

void update(int value) {
    t += 0.005;  
    if (t > 1.0) {
        t = 0.0;  
    }

  
    sunX = -0.8 + (1.6 * t);  
    sunY = -0.8 + 1.6 * (1.0 - pow(t - 0.5, 2));  


    if (sunX < 0.0) {
        glClearColor(0.53, 0.81, 0.92, 1.0);  
    } else if (sunX > 0.66 && !isSunSet) {
        glClearColor(0.0, 0.0, 0.0, 1.0);  
        isSunSet = true;
    } else if (sunX <= 0.66) {
        isSunSet = false;  
    }

    glutPostRedisplay(); 
    glutTimerFunc(30, update, 0);  
}


void drawButton(Button button) {
  
    glColor3f(1.0, 1.0, 1.0); 
    glBegin(GL_QUADS);
    glVertex2f(button.x, button.y);
    glVertex2f(button.x + button.width, button.y);
    glVertex2f(button.x + button.width, button.y + button.height);
    glVertex2f(button.x, button.y + button.height);
    glEnd();


    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(button.x + button.width / 3, button.y + button.height / 4);              
    glVertex2f(button.x + button.width / 3, button.y + 3 * button.height / 4);        
    glVertex2f(button.x + 2 * button.width / 3, button.y + button.height / 2);     
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float translationMatrix[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        sunX, sunY, 0.0, 1.0
    };

   
    glPushMatrix();  
    glMultMatrixf(translationMatrix);  
    drawSun();  
    glPopMatrix();  

    drawHouse();
    drawSymmetricTree(0.4, -0.3);
    drawSymmetricTree(0.6, -0.3);
        drawButton(playButton);
    glFlush();
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
     
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float mouseX = (2.0f * x / glutGet(GLUT_WINDOW_WIDTH)) - 1.0f;
        float mouseY = 1.0f - (2.0f * y / windowHeight);


        if (mouseX >= playButton.x && mouseX <= (playButton.x + playButton.width) &&
            mouseY >= playButton.y && mouseY <= (playButton.y + playButton.height)) {
            startGame = true;
            system("start /B D:\\snakegame-main\\snake.exe");
            exit(0); 
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'p') {
        startGame = true;

        system("start /B D:\\snakegame-main\\snake.exe");
        exit(0);
    }
}

void initAnimation() {
    glClearColor(0.53, 0.81, 0.92, 1.0);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}



int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sun, House, and Trees Animation");
    initAnimation();
      glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse); 
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);  
    glutMainLoop();
    return 0;
}


