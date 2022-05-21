#include <GL/glut.h>
#include <cstdlib>
#include <cmath>
 
class Particle {
    private:
        float x;
        float y;
        float vx;
        float vy;
        float color[3];
        float r;
    public:
        Particle();
        void moveParticle();
        void holdInLimits();
        void moveToCursor(int, int);
        void moveFromCursor(int, int);
        void drawParticle();
};
 
int MOUSEX;
int MOUSEY;
int PRESSED_LEFT = 0;
int PRESSED_RIGHT = 0;
Particle *array, *i;
 
#define N 100
 
void mouse(int, int, int, int);
void mouseMotion(int, int);
void display();
void timer(int = 0);
 
Particle::Particle()
{
    x = rand() % 500;
    y = rand() % 500; 
    vx = rand() % 500 / 100.0 - 2.5;
    vy = rand() % 500 / 100.0 - 2.5;
    color[0] = rand() % 200 / 200.0;
    color[1] = rand() % 200 / 200.0;
    color[2] = rand() % 200 / 200.0;
    r = rand() % 5 + 1;
}
 
void Particle::moveParticle()
{
    x += vx;
    y += vy;
}
 
void Particle::holdInLimits()
{
        if(x > 495 || x < 5)
            vx *= -1;
        if(y > 495 || y < 5)
            vy *= -1;
}
 
void Particle::moveToCursor(int mx, int my)
{
    float d = sqrt((mx - x)*(mx - x) + (my - y)*(my - y));      
    x += 5 * (mx - x) / d; 
    y += 5 * (my - y) / d;
}
 
void Particle::moveFromCursor(int mx, int my)
{
    float d = sqrt((mx - x)*(mx - x) + (my - y)*(my - y));      
    x -= 5 * (mx - x) / d; 
    y -= 5 * (my - y) / d;
}
 
void Particle::drawParticle()
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POLYGON);
    for(float angle = 0; angle < 2*M_PI; angle += 0.1)
        glVertex2f(r*cos(angle)+x, r*sin(angle)+y);
    glEnd();
}
 
int main(int argc, char **argv)
{

    array = new Particle[N];
 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Move Particles");
 
    //glClearColor(0.9, 0.9, 0.9, 0.9);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 500.0, 0.0, 0.0, 1.0);
 
    glutDisplayFunc(display);
    timer();
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
 
    glutMainLoop();
 
    delete [] array;
}
 
void timer(int)
{
    display();
 
    for(i = array; i < array+N; i++)
    {

        i->holdInLimits();
 

        i->moveParticle();
 

        if(PRESSED_LEFT)
            i->moveToCursor(MOUSEX, MOUSEY);
    
    

        else if(PRESSED_RIGHT)
            i->moveFromCursor(MOUSEX, MOUSEY);
    }
 

    glutTimerFunc(10, timer, 0);
}
 
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
 
    for(i = array; i < array+N; i++)
        i->drawParticle();
    
 
    glFlush();
    glutSwapBuffers();
}
 
void mouse(int button, int state, int x, int y)
{
    //we take the mouse coordinate in global variable
    MOUSEX = x;
    MOUSEY = y;
 
    //check which button is pressed
    if(button == GLUT_LEFT_BUTTON)
        PRESSED_LEFT = state == GLUT_DOWN;
    else if(button == GLUT_RIGHT_BUTTON)
        PRESSED_RIGHT = state == GLUT_DOWN;
}
 
//moving the mouse with a push of a button
void mouseMotion(int x, int y)
{
    MOUSEX = x;
    MOUSEY = y;
}