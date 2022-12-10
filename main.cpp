// C program to demonstrate
// drawing a circle using
// OpenGL
#include<stdio.h>
#include<bits/stdc++.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#define cl_black glColor3ub(0,0,0);

using namespace std;

class Quad {
public:
    float vertices[8] = {0,0,0,0,0,0,0,0};
    float centerX;
    float centerY;
    float X;
    float Y;
public:
    Quad(float cx, float cy, float x, float y)
    {
        X = x;
        Y = y;
        vertices[0] = x/2.0;
        vertices[1] = -y/2.0;

        vertices[2] = x/2.0;
        vertices[3] = y/2.0;

        vertices[4] = -x/2.0;
        vertices[5] = y/2.0;

        vertices[6] = -x/2.0;
        vertices[7] = -y/2.0;

        centerX = cx;
        centerY = cy;
    }

    public: void draw()
    {
        glBegin(GL_QUADS);

          glVertex2f(vertices[0]+centerX,vertices[1]+centerY);    // x, y
          glVertex2f(vertices[2]+centerX,vertices[3]+centerY);    // x, y
          glVertex2f(vertices[4]+centerX,vertices[5]+centerY);    // x, y
          glVertex2f(vertices[6]+centerX,vertices[7]+centerY);    // x, y

        glEnd();
    }
    public: void translate(float x, float y)
    {
        centerX+=x;
        centerY+=y;
    }
    public: void transf(float x, float y)
    {
        X+=x;
        Y+=y;

        vertices[0] = X/2.0;
        vertices[1] = -Y/2.0;

        vertices[2] = X/2.0;
        vertices[3] = Y/2.0;

        vertices[4] = -X/2.0;
        vertices[5] = Y/2.0;

        vertices[6] = -X/2.0;
        vertices[7] = -Y/2.0;
    }
};



class Triad {
public:
    float vertices[6] = {0,0,0,0,0,0};
    float centerX;
    float centerY;
public:
    Triad(float cx, float cy, float a, float b, float c, float d, float e, float f)
    {

        vertices[0] = a;
        vertices[1] = b;

        vertices[2] = c;
        vertices[3] = d;

        vertices[4] = e;
        vertices[5] = f;

        centerX = cx;
        centerY = cy;
    }

    public: void draw()
    {
        glBegin(GL_TRIANGLES);

          glVertex2f(vertices[0]+centerX,vertices[1]+centerY);    // x, y
          glVertex2f(vertices[2]+centerX,vertices[3]+centerY);    // x, y
          glVertex2f(vertices[4]+centerX,vertices[5]+centerY);    // x, y

        glEnd();
    }
    public: void translate(float x, float y)
    {
        centerX+=x;
        centerY+=y;
    }
    public: void transf(int v, float x, float y)
    {
        vertices[v*2] += x;
        vertices[v*2+1] += y;
    }
};


class Circle {
public:
    float radius;
    float centerX;
    float centerY;
public:
    Circle(float cx, float cy, float r)
    {
        radius = r;
        centerX = cx;
        centerY = cy;
    }

    public: void draw()
    {
        glBegin(GL_TRIANGLE_FAN);
        float x,y,i;
        for ( i = 0; i < (2 * pi); i += 0.001)
        {
            x = radius * cos(i);
            y = radius * sin(i);

            glVertex2i(x+centerX, y+centerY);
        }
        glEnd();
    }
    public: void translate(float x, float y)
    {
        centerX+=x;
        centerY+=y;
    }
    public: void transf(float a)
    {
        radius += a;
    }
};



void reshape(int,int);
void timer(int);
void draw_trees();
void draw_sunlight();







void myInit (void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 1.0, 0.0);

	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-600, 600, -460, 460);
}


/*
float x_position = 0;
int state = 1;
*/

float deltaTime=10.0;

Quad bgt(-300,78.5,600,763);
Quad bgb(-300,-381.5,600,157);
Quad grnd(-300,-360,550,3);


Circle wb1(-520,-336,25);
Circle w1(-520,-336,22);
Circle wf1(-520,-336,12);
Circle wb2(-520.0+83,-336,25);
Circle w2(-520.0+83,-336,22);
Circle wf2(-520.0+83,-336,12);
Circle wb3(-520.0+83*2,-336,25);
Circle w3(-520.0+83*2,-336,22);
Circle wf3(-520.0+83*2,-336,12);
Circle wb4(-520.0+20+83*3,-336,25);
Circle w4(-520.0+20+83*3,-336,22);
Circle wf4(-520.0+20+83*3,-336,12);
Circle wb5(-520.0+20+83*4,-336,25);
Circle w5(-520.0+20+83*4,-336,22);
Circle wf5(-520.0+20+83*4,-336,12);
Circle wb6(-520.0+20+83*5,-336,25);
Circle w6(-520.0+20+83*5,-336,22);
Circle wf6(-520.0+20+83*5,-336,12);
/*
Quad bogb(-440,-235,250,160);
Quad bogt(-440,-140,270,30);
Quad bogw1(-440,-235,50,80);
Quad bogw2(-520,-235,50,80);
Quad bogw3(-360,-235,50,80);

Quad erb(-207,-230,150,170);
Quad ert(-207,-130,170,34);
Quad erd(-225,-250,65,130);
Quad erdw(-225,-220,50,50);

Quad erc(-245,-88,40,50);
Quad erct(-245,-62,50,15);
Quad e(-77,-265,110,100);
*/
Quad ebc(-299,-280,33,20);



//tree1
Triad tt1(-500,70,45,-30,0,30,-45,-30);
Triad tm1(-500,15,45,-30,0,30,-45,-30);
Quad tb1(-500,-25,20,20);

//tree2
Triad tt2(-250,130,45,-30,0,30,-45,-30);
Triad tm2(-250,75,45,-30,0,30,-45,-30);
Quad tb2(-250,35,20,20);

//tree3
Triad tt3(-150,160,45,-30,0,30,-45,-30);
Triad tm3(-150,105,45,-30,0,30,-45,-30);
Quad tb3(-150,65,20,20);

//bigTree
Triad tt4(-380,65,60,-40,0,40,-60,-40);
Quad tb4(-380,12.5,25,25);

/*
//sun
Circle sun(-430,242,75);
*/

//sun light
Triad sl1(-230,242,70,10,30,55,-100,-10);
Triad sl2(-300,342,50,-10,40,65,-50,-50);
Triad sl3(-430,375,10,-50,15,80,-25,65);
Triad sl4(-520,350,30,-40,20,40,-40,25);
Triad sl5(-550,250,20,0,-20,30,-20,-10);
Triad sl6(-550,150,50,30,-20,18,15,-55);
Triad sl7(-430,110,18,-25,0,50,-15,-30);
Triad sl8(-330,120,20,-5,-35,40,-15,-20);


//screen right
Quad wbg(300,0,600,921);

//circles
Circle sun(100,345,50);
Circle pre_sun(100,345,50);
Circle wc1(250,345,50);
Circle wc2(400,345,50);

//sun light
Triad ytr(80,115,60,-40,0,40,-60,-40);


//tree top
Triad g10tr(200,115,60,-40,0,40,-60,-40);
//big tree top
Triad g5tr(320,115,60,-40,0,40,-60,-40);
//light tree top
Triad g2tr(440,115,60,-40,0,40,-60,-40);

//6 quad colors to display
Quad quad_c(100,-115,80,80);
Quad erdw(100,-115,80,80);

Quad quad_r(200,-115,80,80);
Quad bogb(200,-115,80,80);
Quad ert(200,-115,80,80);

Quad quad_n(300,-115,80,80);
Quad bogw1(300,-115,80,80);
Quad bogw2(300,-115,80,80);
Quad bogw3(300,-115,80,80);

Quad quad_g10(100,-230,80,80);
Quad erb(100,-230,80,80);
Quad erct(100,-230,80,80);

Quad quad_g5(200,-230,80,80);
Quad e(200,-230,80,80);
Quad erc(200,-230,80,80);
Quad bogt(200,-230,80,80);

Quad quad_g2(300,-230,80,80);
Quad erd(300,-230,80,80);

void translator();

void display (void)
{
	glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(246,198,132);
    bgb.draw();
    glColor3ub(97,196,219);
    bgt.draw();
    glColor3ub(0,0,0);
    grnd.draw();


    cl_black;
    wb1.draw();
    glColor3ub(147,120,99);
    w1.draw();
    glColor3ub(199,178,159);
    wf1.draw();

    cl_black;
    wb2.draw();
    glColor3ub(147,120,99);
    w2.draw();
    glColor3ub(199,178,159);
    wf2.draw();

    cl_black;
    wb3.draw();
    glColor3ub(147,120,99);
    w3.draw();
    glColor3ub(199,178,159);
    wf3.draw();

    cl_black;
    wb4.draw();
    glColor3ub(147,120,99);
    w4.draw();
    glColor3ub(199,178,159);
    wf4.draw();

    cl_black;
    wb5.draw();
    glColor3ub(147,120,99);
    w5.draw();
    glColor3ub(199,178,159);
    wf5.draw();
    cl_black;
    wb6.draw();
    glColor3ub(147,120,99);
    w6.draw();
    glColor3ub(199,178,159);
    wf6.draw();

    /*
    //boggi
    glColor3ub(234,28,37);
    bogb.draw();

    glColor3ub(0,128,63);
    erb.draw();

    glColor3ub(143,184,52);
    bogt.draw();

    glColor3ub(234,225,156);
    bogw1.draw();
    bogw2.draw();
    bogw3.draw();

    glColor3ub(234,28,37);
    ert.draw();
    glColor3ub(191,208,52);
    erd.draw();

    glColor3ub(172,201,231);
    erdw.draw();

    glColor3ub(143,184,52);
    erc.draw();
    e.draw();

    glColor3ub(0,128,63);
    erct.draw();

    glColor3ub(166,75,45);
    ebc.draw();




    //sun
    glColor3ub(255,207,0);
    sun.draw();

    //sun light


*/

    //screen write
    glColor3ub(255,255,255);
    wbg.draw();

    //sun
    glColor3ub(255,207,0);
    sun.draw();
    pre_sun.draw();
    glColor3ub(147,120,99);
    wc1.draw();
    glColor3ub(199,178,159);
    wc2.draw();

    //sun light
    glColor3ub(255,255,0);
    ytr.draw();

    //tree top
    glColor3ub(0,128,63);
    g10tr.draw();
    glColor3ub(143,184,52);
    g5tr.draw();
    glColor3ub(191,208,52);
    g2tr.draw();


    //quad to show color

    glColor3ub(143,184,52);
    quad_g5.draw();
    e.draw();
    erc.draw();
    bogt.draw();

    glColor3ub(0,128,63);
    quad_g10.draw();
    erb.draw();
    erct.draw();

    glColor3ub(191,208,52);
    quad_g2.draw();
    erd.draw();



    glColor3ub(172,201,231);
    quad_c.draw();
    erdw.draw();

    glColor3ub(234,28,37);
    quad_r.draw();
    bogb.draw();
    ert.draw();

    glColor3ub(234,225,156);
    quad_n.draw();
    bogw1.draw();
    bogw2.draw();
    bogw3.draw();

    translator();

	glFlush();
}

int main (int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// giving window size in X- and Y- direction
	glutInitWindowSize(1201, 921);
	glutInitWindowPosition(0, 0);

	// Giving name to window
	glutCreateWindow("Lab PROJECT");
	myInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutTimerFunc(1000,timer,0);

	glutMainLoop();
}




void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-600, 600, -460, 460);
    glMatrixMode(GL_MODELVIEW);

}
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    deltaTime+= 1.0/60.0;

}


void translator()
{
    if(deltaTime>=5)
    {

    }
    if(deltaTime>=10.0)
    {


    }
    if(deltaTime>=15.0)
    {

    }
    if(deltaTime>=20.0)
    {
        if(sun.centerX>-430) sun.translate(-2,0);
        if(sun.centerY>242) sun.translate(0,-1);


        if(erb.centerX>-207) erb.translate(-1,0);
        //if(erb.centerY>-207) erb.translate(-1,0);


        if(erct.centerX>-245) erct.translate(-1,0);
        if(erct.centerY<-65) erct.translate(0,1);


        if(e.centerX>-77) e.translate(-1,0);
        if(e.centerY>-265) e.translate(0,-1);


        if(erc.centerX>-245) erc.translate(-1,0);
        if(erc.centerY<-88) erc.translate(0,1);


        if(bogt.centerX>-440) bogt.translate(-1.5,0);
        if(bogt.centerY<-140) bogt.translate(0,1);


        if(ert.centerX>-207) ert.translate(-2,0);
        if(ert.centerY>-130) ert.translate(0,-1);


        if(bogb.centerX>-440) bogb.translate(-2,0);
        if(bogb.centerY>-235) bogb.translate(0,-1);


        if(erd.centerX>-225) erd.translate(-2,0);
        if(erd.centerY>-250) erd.translate(0,-1);


        if(erdw.centerX>-225) erdw.translate(-2,0);
        if(erdw.centerY>-220) erdw.translate(0,-1);



        if(bogw1.centerX>-440) bogw1.translate(-2,0);
        if(bogw2.centerX>-520) bogw2.translate(-2,0);
        if(bogw3.centerX>-360) bogw3.translate(-2,0);
        if(bogw3.centerY>-235){
                bogw3.translate(0,-1);
                bogw2.translate(0,-1);
                bogw1.translate(0,-1);
        }




    }
    if(deltaTime>=25)
    {
        if(sun.radius<75)sun.transf(1);

        if(bogw1.X>50){
            bogw1.transf(-1,0);
            bogw2.transf(-1,0);
            bogw3.transf(-1,0);
        }

        if(erb.X<150)erb.transf(1,0);
        if(erb.Y<170)erb.transf(0,1);

        if(erct.X>50)erct.transf(-1,0);
        if(erct.Y>15)erct.transf(0,-1);

        if(e.X<110)e.transf(1,0);
        if(e.Y<100)e.transf(0,1);

        if(erc.X>40)erc.transf(-1,0);
        if(erc.Y>50)erc.transf(0,-1);

        if(bogt.X<270)bogt.transf(1,0);
        if(bogt.Y>30)bogt.transf(0,-1);

        if(ert.X<170)ert.transf(1,0);
        if(ert.Y>34)ert.transf(0,-1);

        if(bogb.X<250)bogb.transf(1,0);
        if(bogb.Y<160)bogb.transf(0,1);

        if(erd.X>65)erd.transf(-1,0);
        if(erd.Y<130)erd.transf(0,1);

        if(erdw.X>50)erdw.transf(-1,0);
        if(erdw.Y>50)erdw.transf(0,-1);
        glColor3ub(166,75,45);
        ebc.draw();

    }
    if(deltaTime>=30)
    {
        draw_sunlight();
    }
    if(deltaTime>=32)
    {
        draw_trees();
    }

}

void draw_trees()
{
    cl_black;
    glBegin(GL_LINES);
        glVertex2f(-550,-80);
        glVertex2f(-100,55);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(-100,55);
        glVertex2f(-20,-20);
    glEnd();

    //Tree1
    glColor3ub(0,128,63);
    tt1.draw();
    tm1.draw();
    glColor3ub(166,75,45);
    tb1.draw();

    //Tree2
    glColor3ub(191,208,52);
    tt2.draw();
    tm2.draw();
    glColor3ub(166,75,45);
    tb2.draw();

    //Tree3
    glColor3ub(143,184,52);
    tt3.draw();
    tm3.draw();
    glColor3ub(166,75,45);
    tb3.draw();

    //bigTree
    glColor3ub(143,184,52);
    tt4.draw();
    glColor3ub(166,75,45);
    tb4.draw();
}

void draw_sunlight()
{
    glColor3ub(255,255,0);
    sl1.draw();
    sl2.draw();
    sl3.draw();
    sl4.draw();
    sl5.draw();
    sl6.draw();
    sl7.draw();
    sl8.draw();
}
