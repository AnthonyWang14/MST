#ifndef __MST__H__
#define __MST__H__
#include <GLUT/GLUT.h>
#include <vector>

class MST {
public:
    struct Vertex;
    struct Edge;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::vector<Edge> tree_edges;
    //点结构
    struct Vertex {
        int x, y;
        int connect;
        Vertex(int xx, int yy):x(xx),y(yy){}
    };
    //边结构，存储了节点在节点向量中的指标，且head_index要小于tail_index
    struct Edge{
        int head_index, tail_index;
        int length2;
        Edge(int hi, int ti, std::vector<Vertex>& vertices){
            head_index = (hi < ti) ? hi : ti;
            tail_index = (ti > hi) ? ti : hi;
            int dx = vertices[hi].x - vertices[ti].x;
            int dy = vertices[hi].y - vertices[ti].y;
            length2 = dx*dx + dy*dy;
        }
    };
    //边排序的比较函数
    static bool cmp(const Edge& e1, const Edge& e2) {
        return e1.length2 < e2.length2;
    }
    int add_vertex(int x, int y);
    void add_edge(int hi, int ti);
    void paint();
    void Kruscal();
    int find_connect(int x);
};

#endif
