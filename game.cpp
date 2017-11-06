#include <GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>

#define FROM_RIGHT      1 
#define FROM_LEFT       2 
#define FROM_TOP        3 
#define FROM_BOTTOM     4 
 
static int WINDOW_WIDTH ,WINDOW_HEIGHT;
struct Object {
	int x; int y;
	int width; int height;

	// Dictate the movement direction of the object
	int dx; int dy;
} mouse_x;

int playerResult=0;
static float Xspeed=1,Yspeed=1; 
static float delta=1; 

char string [100];
int pcResult =0;



struct RECTA
{ 
        float left,top,right,bottom; 
};

RECTA ball={100,100,120,120};
RECTA wall ;
RECTA player_1 ={0,490,40,500}; 

void DrawRectangle(RECTA  rect) 
{ 
        glBegin(GL_QUADS); 
        glVertex2f(rect.left,rect.bottom);      //Left - Bottom 
        glVertex2f(rect.right,rect.bottom); 
        glVertex2f(rect.right,rect.top); 
        glVertex2f(rect.left,rect.top); 
        glEnd(); 
}

void Timer(int v) 
{ 
 
        ball.left+=Xspeed; 
        ball.right+=Xspeed; 
        ball.top+=Yspeed; 
        ball.bottom+=Yspeed; 
 
        glutTimerFunc(1,Timer,1); 
}
void drawText(char*string,int x,int y)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y,0);
	  glScalef(0.1,-0.1,1);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();

}
 
int Test_Ball_Wall(RECTA  ball , RECTA wall) 
{ 
        if(ball.right >=wall.right) 
        return FROM_RIGHT;  
        if(ball.left <=wall.left) 
        return FROM_LEFT;  
        if(ball.top <=wall.top) 
        return FROM_TOP;  
        if(ball.bottom >=wall.bottom) 
        return FROM_BOTTOM;  
 
        else return 0 ; 
}

bool Test_Ball_Player(RECTA ball,RECTA player) 
{ 
         

        if(ball.bottom >= player.top && ball.left>= player.left && ball.right <=player.right ) 
        {
            playerResult++;
            return true;  
        }
 
            return false;  
}
 
 /*result(pcResult, playerResult ){
     if(pcResult==10 || playerResult==10){
         if(pcResult==10){
             sprintf(string,"PC WON "); 
             drawText(string,100,80); 
            }
          else{
            sprintf(string,"YOU WON "); 
             drawText(string,100,80);
            }  
             
    }
} */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT );
    //glLoadIdentity();
    
    glBegin(GL_QUADS);			//SKY
	//glColor3f(0,0,1);
	//glColor3f(0,0,0.7);
	glColor3f(1,1,1);
    glVertex2f(795,500);
    glVertex2i(795,0);
	//glColor3f(1, 1, 1);
	glVertex2i(0,0);
    glVertex2f(0,500);
	
    glEnd();
    
    
    
    glColor3f(0,0,0);
	sprintf(string,"PC : %d ",pcResult); 
	drawText(string,10,80); 
	sprintf(string,"YOU : %d ",playerResult);
	drawText(string,10,120);

  
    
	wall.left=wall.top=0;
	wall.right=WINDOW_WIDTH;
	wall.bottom=WINDOW_HEIGHT;
    glColor3f(1,0,0);
	DrawRectangle(ball);

	if(Test_Ball_Wall(ball,wall)== FROM_RIGHT) 
    Xspeed=-delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_LEFT) 
    Xspeed=delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_TOP) 
    Yspeed=delta; 

    if(Test_Ball_Wall(ball,wall)== FROM_BOTTOM) 
	{
		Yspeed=-delta; 
		pcResult +=1;
	}
    glColor3f(0,0,0);
	DrawRectangle(player_1); 
    player_1.left=mouse_x.x-20; 
    player_1.right=mouse_x.x+40; 


    if(Test_Ball_Player(ball,player_1)==true) {
            Yspeed=-delta;
            delta++;
            }
    
    if(pcResult==10 || playerResult==10){
         if(pcResult==10){
             glColor3f(1,0,0);
             sprintf(string,"GAME OVER!! ");
             drawText(string,360,170);
             sprintf(string,"PC WON "); 
             drawText(string,360,200);
             glColor3f(0,0,0);
             sprintf(string,"Press ESC to exit! "); 
             drawText(string,360,250 );
             usleep(2000000);
             //exit(0);
            }
          else{
            glColor3f(1,0,0);
            sprintf(string,"GAME OVER!! ");  
            drawText(string,360,170);
            sprintf(string,"YOU WON "); 
             drawText(string,360,200);
             glColor3f(0,0,0);
             sprintf(string,"Press ESC to exit! "); 
             drawText(string,360,250);
             usleep(2000000);
             //exit(0);
            }  
             
    }
        if(pcResult==11 || playerResult==11){
                exit(0);
        }
	glutSwapBuffers();
}

 
 
// Key Board Messages 
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      case 'd': mouse_x.x += 30;
        break;
      case 'a': mouse_x.x -= 30;
   }
}

void MouseMotion(int x,int y)
{
 
	mouse_x.x=x;
}

 
void reshape (int w, int h)
{
	WINDOW_WIDTH =w ;
	WINDOW_HEIGHT =h ;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   
   gluOrtho2D (0, w, h, 0);


   glMatrixMode (GL_MODELVIEW);
   

}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (795, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow (" Game");


    
    glClearColor (0.0, 0.0, 0.0, 0.0);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   
    glutDisplayFunc(display); 
   glutIdleFunc(display);
    	

   glutTimerFunc(1,Timer,1);

   glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

  

   glutPassiveMotionFunc(MouseMotion);


   glutMainLoop();
   return 0;
}
