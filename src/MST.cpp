#include "MST.h"
#include <algorithm>

//添加结点
int MST::add_vertex(int x, int y) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].x == x && vertices[i].y == y)
            return i;
    }
    vertices.push_back(Vertex(x, y));
    return int(vertices.size()-1);
}

//添加边
void MST::add_edge(int hi, int ti) {
    int h = (hi < ti) ? hi : ti;
    int t = (hi < ti) ? ti : hi;
    edges.push_back(Edge(h, t, vertices));
}

//根据树边绘制最小生成树
void MST::paint() {
    glBegin(GL_LINES);
    for (int i = 0; i < tree_edges.size(); i++) {
        glVertex2i(vertices[tree_edges[i].head_index].x, vertices[tree_edges[i].head_index].y);
        glVertex2i(vertices[tree_edges[i].tail_index].x, vertices[tree_edges[i].tail_index].y);
    }
    glEnd();
    glBegin(GL_POINTS);
    for (int i = 0; i < vertices.size(); i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
}

//递归查找所属连通分量，并进行路径压缩
int MST::find_connect(int x) {
	if (vertices[x].connect != x)
		vertices[x].connect = find_connect(vertices[x].connect);
	return vertices[x].connect;
}

void MST::Kruscal() {
	//使用并查集来进行连通分量的查找
    for (int i = 0; i < vertices.size(); i++)
        vertices[i].connect = i;
    //对边长度进行排序
    std::sort(edges.begin(), edges.end(), cmp);
    for (int i = 0; i < edges.size(); i++) {
    	int x = find_connect(edges[i].head_index);
    	int	y = find_connect(edges[i].tail_index);
    	//如果这添加该边之后会形成环，则跳过
    	if (x == y)
    		continue;
    	//不成环则加边并合并两点的连通分量
    	else {
    		vertices[y].connect = x;
    		tree_edges.push_back(edges[i]);
    	}
    	if (tree_edges.size() == vertices.size() - 1)
    		break;
    }
}