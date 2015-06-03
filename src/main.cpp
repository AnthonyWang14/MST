#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_euclidean_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <GLUT/GLUT.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include "MST.h"

using std::string;
using std::cout;
using std::endl;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef Delaunay::Vertex_handle Vertex_handle;
typedef K::Point_2 Point;

bool paint_voi = false;
string filename = "testcase1.txt";
std::vector<Point> vertices;
int global_w, global_h;
int mst_state = 0;
MST mst;
void drawPoint()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    std::vector <Point>::iterator iter;
    glColor3f( 1.0, 1.0, 1.0 );
    glPointSize(3);
    glBegin(GL_POINTS);
    for( iter = vertices.begin(); iter != vertices.end(); iter++ ) {
        glVertex2i( iter->hx(), iter->hy() );
//        std::cout << iter->hx() << ' ' << iter->hy() << std::endl;
    }
    glEnd();
    
    glPopMatrix();
    glutSwapBuffers();
}

void addPoint( int x, int y )
{
    vertices.push_back( Point( x, global_h-y ) );
}

void clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
    mst.vertices.clear();
    mst.tree_edges.clear();
    mst.edges.clear();
    vertices.clear();
    mst_state = 0;
}

void read_file(string& filename)
{

    std::ifstream in("../testcases/" + filename, std::ios::in);
    if (!in) 
        cout << 'can not read from file' << endl;
    int a, b, num;
    in >> num;
    for (int i = 0; i < num; i++) {
        in >> a >> b;
        vertices.push_back(Point(a, b));
    }
}

void basic_mst() {
    //清空操作
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();

    drawPoint();
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < vertices.size(); i++) {
        mst.add_vertex(vertices[i].hx(), vertices[i].hy());
    }
    for (int i = 0; i < mst.vertices.size(); i++)
        for (int j = i+1; j < mst.vertices.size(); j++)
            mst.edges.push_back(MST::Edge(i, j, mst.vertices));
    mst.Kruscal();
    mst.paint();
    //将MST中数据清除
    mst.vertices.clear();
    mst.edges.clear();
    mst.tree_edges.clear();
    
    glPopMatrix();
    glutSwapBuffers();
}

void triangulation_mst() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
    
    Delaunay dt;//Delaunay数据结构，代表当前数据的一个且仅有一个的三角剖分，详情请参考CGAL_manual
    dt.insert(vertices.begin(), vertices.end());//输入数据
    drawPoint();
    glPushMatrix();
    //三角剖分的每个面
    Delaunay::Finite_faces_iterator fit;
    glColor3f( 0.0, 0.0, 1.0 );
    
    //将Delaunay中的边、点都读入MST中的结点和边向量
    for( fit = dt.finite_faces_begin(); fit != dt.finite_faces_end(); fit ++)
    {
        int x[3];
        int y[3];
        int index_of_vertex[3];
        for (int i = 0; i < 3; i++) {
            x[i] = fit->vertex(i)->point().hx();
            y[i] = fit->vertex(i)->point().hy();
            index_of_vertex[i] = mst.add_vertex(x[i], y[i]);
        }
        mst.add_edge(index_of_vertex[0], index_of_vertex[1]);
        mst.add_edge(index_of_vertex[1], index_of_vertex[2]);
        mst.add_edge(index_of_vertex[2], index_of_vertex[0]);
    }
    
    mst.Kruscal();
    mst.paint();
    //将MST中数据清除
    mst.vertices.clear();
    mst.edges.clear();
    mst.tree_edges.clear();
    if (paint_voi) {
        Delaunay::Edge_iterator eit;//遍历Delaunay的所有边，绘制Delaunay图的对偶图，即Voronoi图
        
        glEnable( GL_LINE_STIPPLE );//使用点画模式，即使用虚线来绘制Voronoi图
        glLineStipple( 1, 0x3333 );
        glColor3f( 0.0, 1.0, 0.0 );
        
        for( eit = dt.edges_begin(); eit != dt.edges_end(); eit ++)
        {
            CGAL::Object o = dt.dual(eit);//边eit在其对偶图中所对应的边
            
            if (CGAL::object_cast<K::Segment_2>(&o)) //如果这条边是线段，则绘制线段
            {
                glBegin(GL_LINES);
                glVertex2i( CGAL::object_cast<K::Segment_2>(&o)->source().hx(), CGAL::object_cast<K::Segment_2>(&o)->source().hy() );
                glVertex2i( CGAL::object_cast<K::Segment_2>(&o)->target().hx(), CGAL::object_cast<K::Segment_2>(&o)->target().hy() );
                glEnd();
            }
            else if (CGAL::object_cast<K::Ray_2>(&o))//如果这条边是射线，则绘制射线
            {
                glBegin(GL_LINES);
                glVertex2i( CGAL::object_cast<K::Ray_2>(&o)->source().hx(), CGAL::object_cast<K::Ray_2>(&o)->source().hy() );
                glVertex2i( CGAL::object_cast<K::Ray_2>(&o)->point(1).hx(), CGAL::object_cast<K::Ray_2>(&o)->point(1).hy() );
                glEnd();  
            }  
        }
        
        glDisable( GL_LINE_STIPPLE );//关闭点画模式  
    }
    glPopMatrix();
    glutSwapBuffers();
    
    mst_state = 1;//完成最小生成树，置状态为1
}

void display(void) {
}

void init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void reshape(int w, int h) {
    global_w = w;
    global_h = h;
    clear();
    
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        addPoint(x,y);
        drawPoint();
    }
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_UP ) {
        if (mst_state == 1)
            clear();
        else
            triangulation_mst();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'a':
            if (mst_state == 1)
                clear();
            else {
                read_file(filename);
                drawPoint();
            }
            break;
        case 's':
            triangulation_mst();
            break;
        case 'd':
            basic_mst();
            break;
        case 'c':
            clear();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 600); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    if (argc > 1) 
        filename = "testcase" + string(argv[1]) + ".txt";
    if (argc > 2)
        paint_voi = true;
    init();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

