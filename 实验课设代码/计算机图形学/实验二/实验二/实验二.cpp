// 实验二.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include"common.h"
#include<windows.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include<gl/glui.h>
#include<gl/glut.h>
#include<vector>

int g_xform_mode = TRANSFORM_NONE;
int g_form_mode = TRANSFORM_NONE;
int g_view_type = VIEW_YES;
int g_control_type = CRTL_LOAD;
int g_dense = 0;
int  g_main_window;
int g_index;
double g_windows_width, g_windows_height;

static int  g_press_x; //鼠标按下时的x坐标
static int  g_press_y; //鼠标按下时的y坐标

//the lighting
static GLfloat g_light0_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };//环境光
static GLfloat g_light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };//散射光
static GLfloat g_light0_specular[] = { 1.0f,1.0f,1.0f,1.0f }; //镜面光
static GLfloat g_light0_position[] = { 0.0f, 0.0f, 100.0f, 0.0f };//光源的位置。第4个参数为1，表示点光源；第4个参数量为0，表示平行光束{0.0f, 0.0f, 10.0f, 0.0f}

static GLfloat g_material[] = { 0.96f, 0.8f, 0.69f, 1.0f };//材质

struct Point {
	double x, y;
};

std::vector<Point> points; // 用于记录每个控制点的坐标
std::vector<float> vecs;
static int controlNum = 0; // 控制点的数量
static int pointNum = 0; //节点数
static int degree = 0; //B样条曲线的次数
static std::vector<int> Fact;      //Fact = new int[…];
std::vector<Point> opts;

unsigned int fact(unsigned int n)
{
	static unsigned int num = 0;
	unsigned int res;
	if (n <= num)   
		return Fact[n - 1];
	else {
		if (n == 1 || n == 0)      
			res = 1;
		else               
			res = n * fact(n - 1);

		num = n;
		Fact.push_back(res);
	}
	return res;
}

void createKnots() {
	vecs.clear();
	int nKnots = controlNum + degree;
	for (int i = 0; i < nKnots; i++) {
		if (i < degree) {
			vecs.push_back(0);
		}
		else if (i < nKnots - degree + 1) {
			vecs.push_back(vecs[i - 1] + 1);
		}
		else {
			vecs.push_back(vecs[i - 1]);
		}
	}
}

int find_point(int x, int y) {
	for (int i = 0; i < points.size();i++) {
		float x_diff = x - points[i].x;
		float y_diff = y - points[i].y;
		if (x_diff*x_diff + y_diff * y_diff <= 25) {
			return i;
		}
	}
	return -1;
}

void add_point(float x, float y) {
	Point point;
	point.x = x;
	point.y = y;
	points.push_back(point);
	//degree++;
	controlNum++;
}

int whichInterval(float t) {
	for (int i = 1; i < vecs.size() - 1; i++)
	{
		if (t < vecs[i])
			return (i - 1);
		else if (t == vecs[vecs.size() - 1])
			return (vecs.size() - 1);
	}
	return -1;
}

Point Deboor(int j, int i, float t) {
	if (j == 0) {
		return points[i];
	}
	else{
		float param = (t - vecs[i]) / (vecs[i + degree + 1 - j] - vecs[i]);
		Point x = Deboor(j - 1, i - 1, t);
		Point y = Deboor(j - 1, i, t);
		Point ans;
		ans.x = (1 - param)*x.x + param * y.x;
		ans.y = (1 - param)*x.y + param * y.y;
		return ans;
	}
}

void bspToPoint() {
	opts.clear();
	float tJump = (vecs[controlNum] - vecs[degree]) / (g_dense);
	for (int i = 0; i < g_dense; i++) {
		float t = vecs[degree] + i * tJump;
		int tInt = whichInterval(t);
		if (tInt >= controlNum)
			continue;
		Point point = Deboor(degree, tInt, t);
		opts.push_back(point);
	}
}

bool load_Point(const char* pcszFileName)
{
	FILE* fpFile = fopen(pcszFileName, "r"); //以只读方式打开文件
	if (fpFile == NULL)
	{
		return false;
	}

	points.clear();
	opts.clear(); 
	vecs.clear();

	char strLine[1024];
	Point point;
	float vec;

	fgets(strLine, 1024, fpFile);
	std::istringstream sin(strLine);
	sin >> degree;

	fgets(strLine, 1024, fpFile);
	std::istringstream sin1(strLine);
	sin1 >> controlNum;

	fgets(strLine, 1024, fpFile);
	std::istringstream sin2(strLine);
	while (sin2 >> vec)
	{
		vecs.push_back(vec);
	}

	while (!feof(fpFile))
	{
		fgets(strLine, 1024, fpFile);
	
		std::istringstream sin3(strLine);
		sin3 >> point.x >> point.y;
		points.push_back(point);
	}
	points.pop_back();
	fclose(fpFile);

	fact(degree);
	g_dense = controlNum + degree;
	bspToPoint();
	return true;
}

void displayImage()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glColor3f(1.0, 0.0, 0.0);
	//glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);

	if (g_view_type == VIEW_YES) {
		glBegin(GL_LINE_STRIP);
		//glNormal3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < controlNum; i++) {
			glVertex2f(points[i].x, points[i].y);
		}
		glEnd();
	}

	//glDisable(GL_LINE_STIPPLE);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < opts.size(); i++) {
		glVertex2f(opts[i].x, opts[i].y);
	}
	glEnd();

	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < controlNum; i++) {
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
	glFlush();
}

void myGlutDisplay() //绘图函数， 操作系统在必要时刻就会对窗体进行重新绘制操作
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓冲以及深度缓冲
	//glEnable(GL_NORMALIZE); //打开法线向量归一化，确保了法线的长度为1

	//glMatrixMode(GL_MODELVIEW);//模型视图矩阵
	//glPushMatrix(); //压入当前矩阵堆栈

	displayImage();
	
	//glPopMatrix();
	glutSwapBuffers(); //双缓冲
}

void myGlutReshape(int x, int y) //当改变窗口大小时的回调函数
{
	if (y == 0)
	{
		y = 1;
	}

	g_windows_width = x;
	g_windows_height = y;
	double xy_aspect = (float)x / (float)y;
	GLUI_Master.auto_set_viewport(); //自动设置视口大小

	glMatrixMode(GL_PROJECTION);//当前矩阵为投影矩阵
	glLoadIdentity();
	gluPerspective(60.0, xy_aspect, 0.01, 1000.0);//视景体

	glutPostRedisplay(); //标记当前窗口需要重新绘制
}

void mouse(int button, int state, int x, int y) 
{
	g_press_x = x;
	g_press_y = y;
	if (button == GLUT_LEFT_BUTTON) {
		if (g_xform_mode + 1 == CRTL_ADD) {
			add_point(x, 600 - y);
			createKnots();
			glutPostRedisplay();
		}
		else if (g_xform_mode + 1 == CRTL_DRAG) {
			g_index = find_point(g_press_x, 600 - g_press_y);
			g_form_mode = TRANSFORM_DRAG;
		}
	}
	else {
		g_form_mode = TRANSFORM_NONE;
	}
	
}

void init()
{
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//用白色清屏

	//glLightfv(GL_LIGHT0, GL_AMBIENT, g_light0_ambient);//设置场景的环境光
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, g_light0_diffuse);//设置场景的散射光
	//glLightfv(GL_LIGHT0, GL_POSITION, g_light0_position);//设置场景的位置

	//glMaterialfv(GL_FRONT, GL_DIFFUSE, g_material);//指定用于光照计算的当前材质属性
	//glEnable(GL_LIGHTING);//开启灯光
	//glEnable(GL_LIGHT0);//开启光照0

	//glShadeModel(GL_SMOOTH); //设置着色模式为光滑着色
	//glEnable(GL_DEPTH_TEST);//启用深度测试
	
	glMatrixMode(GL_MODELVIEW); //指定当前矩阵为模型视景矩阵
	glLoadIdentity(); //将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
	gluOrtho2D(0.0, 800, 0.0, 600);
	//gluLookAt(0.0, 0.0, 100.0, 0, 0, 0, 0, 1.0, 0.0);//该函数定义一个视图矩阵，并与当前矩阵相乘.
}

void myGlutMotion(int x, int y) //处理当鼠标键摁下时,鼠标拖动的事件
{
	if (g_form_mode == TRANSFORM_DRAG) //拖拽点
	{
		
		float x_offset = (x - g_press_x);
		float y_offset = (y - g_press_y);
		if (g_index != -1) {
			points[g_index].x += x_offset;
			points[g_index].y -= y_offset;
		}
		g_press_x = x;
		g_press_y = y;
	}
	bspToPoint();
	// force the redraw function
	glutPostRedisplay();
}

void myGlutIdle(void) //空闲回调函数
{
	if (glutGetWindow() != g_main_window)
		glutSetWindow(g_main_window);

	glutPostRedisplay();
}

void loadFile(void)
{//加载模型

	//调用系统对话框
	OPENFILENAME  fname;
	ZeroMemory(&fname, sizeof(fname));
	char strfile[200] = "*.txt";
	char szFilter[] = TEXT("TXT Files(*.TXT)\0");
	fname.lStructSize = sizeof(OPENFILENAME);
	fname.hwndOwner = NULL;
	fname.hInstance = NULL;
	fname.lpstrFilter = szFilter;
	fname.lpstrCustomFilter = NULL;
	fname.nFilterIndex = 0;
	fname.nMaxCustFilter = 0;
	fname.lpstrFile = strfile;
	fname.nMaxFile = 200;
	fname.lpstrFileTitle = NULL;
	fname.nMaxFileTitle = 0;
	fname.lpstrTitle = NULL;
	fname.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
	fname.nFileOffset = 0;
	fname.nFileExtension = 0;
	fname.lpstrDefExt = 0;
	fname.lCustData = NULL;
	fname.lpfnHook = NULL;
	fname.lpTemplateName = NULL;
	fname.lpstrInitialDir = NULL;
	HDC hDC = wglGetCurrentDC();
	HGLRC hRC = wglGetCurrentContext();
	GetOpenFileName(&fname);
	wglMakeCurrent(hDC, hRC);
	//printf("读取文件\n");
	load_Point(fname.lpstrFile); //读入模型文件
}

void glui_control(int control) //处理控件的返回值
{
	switch (control)
	{
	case CRTL_LOAD://选择“open”控件
		loadFile();
		break;
	case CRTL_DENSE:
		bspToPoint();
		break;
	default:
		break;
	}
}

void myGlutKeyboard(unsigned char Key, int x, int y)
{//键盘时间回调函数
	if (Key = GLUT_KEY_DOWN) {
		g_view_type = !g_view_type;
	}
}

void myGlui()
{
	GLUI_Master.set_glutDisplayFunc(myGlutDisplay); //注册渲染事件回调函数， 系统在需要对窗体进行重新绘制操作时调用
	//GLUI_Master.set_glutReshapeFunc(myGlutReshape);  //注册窗口大小改变事件回调函数
	glutMotionFunc(myGlutMotion);//注册鼠标移动事件回调函数
	GLUI_Master.set_glutMouseFunc(mouse);//注册鼠标点击事件回调函数
	GLUI_Master.set_glutKeyboardFunc(myGlutKeyboard);//注册键盘输入事件回调函数
	GLUI_Master.set_glutIdleFunc(myGlutIdle); //为GLUI注册一个标准的GLUT空闲回调函数，当系统处于空闲时,就会调用该注册的函数

	//GLUI
	GLUI *glui = GLUI_Master.create_glui_subwindow(g_main_window, GLUI_SUBWINDOW_RIGHT); //新建子窗体，位于主窗体的右部 
	new GLUI_StaticText(glui, "GLUI"); //在GLUI下新建一个静态文本框，输出内容为“GLUI”
	new GLUI_Separator(glui); //新建分隔符
	new GLUI_Button(glui, "Open", CRTL_LOAD, glui_control); //新建按钮控件，参数分别为：所属窗体、名字、ID、回调函数，当按钮被触发时,它会被调用.
	new GLUI_Button(glui, "Quit", 0, (GLUI_Update_CB)exit);//新建退出按钮，当按钮被触发时,退出程序

	GLUI_Panel *type_panel = glui->add_panel("Type");
	GLUI_RadioGroup *radio = glui->add_radiogroup_to_panel(type_panel, &g_xform_mode, CRTL_ADD, glui_control);
	glui->add_radiobutton_to_group(radio, "add");
	glui->add_radiobutton_to_group(radio, "drag");
	//glui->add_radiobutton_to_group(radio, "wire");
	//glui->add_radiobutton_to_group(radio, "flat");

	GLUI_Spinner *spinner = glui->add_spinner("spinner", 2, &g_dense, CRTL_DENSE, glui_control);
	spinner->set_int_limits(3, 1000, 1);
	

	glui->set_main_gfx_window(g_main_window); //将子窗体glui与主窗体main_window绑定，当窗体glui中的控件的值发生过改变，则该glui窗口被重绘
	GLUI_Master.set_glutIdleFunc(myGlutIdle);
}


int main(int argc, char** argv)
{
	freopen("log.txt", "w", stdout);//重定位，将输出放入log.txt文件中
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(200, 200); //初始化窗口位置
	glutInitWindowSize(800, 600); //初始化窗口大小
	g_main_window = glutCreateWindow("吕明伟");

	myGlui();
	init();

	glutMainLoop();
	return 0;
}

