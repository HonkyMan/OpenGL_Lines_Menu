#include "GL/glut.h" 
#include <vector>

using namespace std; 

void createMenu(void);
void menu(int value);

GLint	Width = 512, 
		Height = 512;

GLubyte ColorR = 170, 
		ColorG = 170, 
		ColorB = 170; 

struct type_point 
{ 
	GLint x, y;
	type_point(GLint _x, GLint _y) 
	{ 
		x = _x; 
		y = _y;
	} 
}; 

struct lines
{
	GLubyte Red, Green, Blue;
	vector <type_point> Points;

	lines(GLubyte r = ColorR, GLubyte g = ColorG, GLubyte b = ColorB)
	{
		Red = r;
		Green = g;
		Blue = b;
	}
};


//vector <vector <type_point>> Points(5);
vector <lines> Lines;
int pointCounter = Lines.size();

/* Функция вывода на экран */ 
void Display(void) 
{ 
	glClearColor(0.3, 0.3, 0.3, 1); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glEnable(GL_LINE_SMOOTH);
	//glPointSize(1050);

	for (int i = 0; i < Lines.size(); i++)
	{
		if ( (i + 1) == Lines.size())
		{
			glLineWidth(10);
			glColor3ub(GLubyte(255), GLubyte(255), GLubyte(255));
		}
		else
		{
			glLineWidth(5);
			glColor3ub(Lines[i].Red, Lines[i].Green, Lines[i].Blue);
		}

		glBegin(GL_LINE_LOOP);

		for (int j = 0; j < Lines[i].Points.size(); j++)
		{
			glVertex2i(Lines[i].Points[j].x, Lines[i].Points[j].y);
		}

		glEnd();
	}

	glFinish(); 
} 

/* Функция изменения размеров окна */ 
void Reshape(GLint w, GLint h) 
{ 
	Width = w;    
	Height = h; 
	glViewport(0, 0, w, h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0, w, 0, h); 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
}

/* Функцияобработкисообщенийотклавиатуры */ 
void Keyboard(unsigned char key, int x, int y) 
{ 
	int i, n = Lines[pointCounter].Points.size(); //Points[pointCounter].size();  /* Изменение RGB-компонент цвета точек */
	if (key == 'r') 
		ColorR += 5;  

	if (key == 'g') 
		ColorG += 5;  

	if (key == 'b') 
		ColorB += 5;  

	if (key == ' ')
	{
		lines buf(ColorR, ColorG, ColorB);
		Lines.push_back(buf);
		++pointCounter;
	}

	if (key == '') // onpress DELETE button on keyboard
		Lines[pointCounter].Points.pop_back(); //Points[pointCounter].pop_back();


	/* Изменение XY-кординатточек */  
	if (key == 'w')
		for (i = 0; i < n; i++)
			Lines[pointCounter].Points[i].y += 9; //Points[pointCounter][i].y += 9;
	
	if (key == 's') 
		for (i = 0; i < n; i++) 
			Lines[pointCounter].Points[i].y -= 9;
			//Points[pointCounter][i].y -= 9;
	
	if (key == 'a') 
		for (i = 0; i < n; i++) 
			Lines[pointCounter].Points[i].x -= 9;
			//Points[pointCounter][i].x -= 9;
	
	if (key == 'd') 
		for (i = 0; i < n; i++)
			Lines[pointCounter].Points[i].x += 9;
			//Points[pointCounter][i].x += 9;
		
	glutPostRedisplay(); 
} 

/* Функцияобработкисообщенияотмыши */ 
void Mouse(int button, int state, int x, int y) 
{  /* клавишабыланажата, нонеотпущена */  
	if (state != GLUT_DOWN) 
		return;  /* новаяточкаполевомуклику */  
	
	if (button == GLUT_LEFT_BUTTON) 
	{ 
		type_point p(x, Height - y);

		Lines[pointCounter].Points.push_back(p);
	}
	
	glutPostRedisplay(); 
}

/* Головнаяпрограмма */ 
void main(int argc, char* argv[]) 
{ 
	glutInit(&argc, argv);
	lines buf(ColorR, ColorG, ColorB);
	Lines.push_back(buf);
	glutInitDisplayMode(GLUT_RGB); 
	glutInitWindowSize(Width, Height); 
	glutCreateWindow("Рисуем линии"); 
	createMenu();
	glutDisplayFunc(Display); 
	glutReshapeFunc(Reshape); 
	glutKeyboardFunc(Keyboard); 
	glutMouseFunc(Mouse); 
	glutMainLoop(); 
}

// Menu items
enum MENU_TYPE
{
	DELETE_POINT,
	CHANGE_COLOR_WHITE,
	CHANGE_COLOR_RED,
	CHANGE_COLOR_GREEN,
	CHANGE_COLOR_BLUE,
	CHANGE_POSITION_UP,
	CHANGE_POSITION_DOWN,
	CHANGE_POSITION_LEFT,
	CHANGE_POSITION_RIGHT,
};

// Menu handling function declaration
void menu(int);

void createMenu(void)
{
	// create sub menu
	int colorMenu = glutCreateMenu(menu);
	glutAddMenuEntry("White Color", CHANGE_COLOR_WHITE);
	glutAddMenuEntry("Red Color", CHANGE_COLOR_RED);
	glutAddMenuEntry("Green Color", CHANGE_COLOR_GREEN);
	glutAddMenuEntry("Blue Color", CHANGE_COLOR_BLUE);


	int positionMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Move up", CHANGE_POSITION_UP);
	glutAddMenuEntry("Move down", CHANGE_POSITION_DOWN);
	glutAddMenuEntry("Move left", CHANGE_POSITION_LEFT);
	glutAddMenuEntry("Move right", CHANGE_POSITION_RIGHT);

	// Create a menu
	glutCreateMenu(menu);

	// Add menu items
	glutAddMenuEntry("Delete last point", DELETE_POINT);
	glutAddSubMenu("Change color", colorMenu);
	glutAddSubMenu("Change position", positionMenu);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

// Menu handling function definition
void menu(int item)
{
	switch (item)
	{
		case DELETE_POINT:
		{
			Lines[pointCounter].Points.pop_back();
		}
		break;

		case CHANGE_COLOR_WHITE:
		{
			Lines[pointCounter].Blue = 255;
			Lines[pointCounter].Green = 255;
			Lines[pointCounter].Red = 255;
		}
		break;
		case CHANGE_COLOR_RED:
		{
			Lines[pointCounter].Blue = 70;
			Lines[pointCounter].Green = 70;
			Lines[pointCounter].Red = 255;
		}
		break;
		case CHANGE_COLOR_GREEN:
		{
			Lines[pointCounter].Blue = 70;
			Lines[pointCounter].Green = 255;
			Lines[pointCounter].Red = 70;
		}
		break;
		case CHANGE_COLOR_BLUE:
		{
			Lines[pointCounter].Blue = 255;
			Lines[pointCounter].Green = 70;
			Lines[pointCounter].Red = 70;
		}
		break;

		case CHANGE_POSITION_UP:
		{
			int n = Lines[pointCounter].Points.size();
			for (int i = 0; i < n; i++)
				Lines[pointCounter].Points[i].y += 9;
		}
		break;
		case CHANGE_POSITION_DOWN:
		{
			int n = Lines[pointCounter].Points.size();
			for (int i = 0; i < n; i++)
				Lines[pointCounter].Points[i].y -= 9;
		}
		break;
		case CHANGE_POSITION_LEFT:
		{
			int n = Lines[pointCounter].Points.size();
			for (int i = 0; i < n; i++)
				Lines[pointCounter].Points[i].x -= 9;
		}
		break;
		case CHANGE_POSITION_RIGHT:
		{
			int n = Lines[pointCounter].Points.size();
			for (int i = 0; i < n; i++)
				Lines[pointCounter].Points[i].x += 9;
		}
		break;

		default:
		{       /* Nothing */       }
		break;
	}

	glutPostRedisplay();

	return;
}