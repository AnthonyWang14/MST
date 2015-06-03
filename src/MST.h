#ifndef __MST__H__
#define __MST__H__

class MST {
public:
    typedef std::vector<int> Connection;
    struct Vertex;
    struct Edge;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    std::vector<Edge> tree_edges;
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
    //添加结点
    int add_vertex(int x, int y) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i].x == x && vertices[i].y == y)
                return i;
        }
        vertices.push_back(Vertex(x, y));
        return int(vertices.size()-1);
    }
    //添加边
    void add_edge(int hi, int ti) {
        int h = (hi < ti) ? hi : ti;
        int t = (hi < ti) ? ti : hi;
        edges.push_back(Edge(h, t, vertices));
    }
    //根据树边绘制最小生成树
    void paint() {
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
    
    static bool cmp(const Edge& e1, const Edge& e2) {
        return e1.length2 < e2.length2;
    }
    
    void Kruscal() {
        //初始化连通支编号
        std::vector<Connection> c;
        for (int i = 0; i < vertices.size(); i++) {
            Connection temp;
            temp.push_back(i);
            vertices[i].connect = i;
            c.push_back(temp);
        }
        //对边长度进行排序
        std::sort(edges.begin(), edges.end(), cmp);
        
        for (int i = 0; i < edges.size(); i++) {
            //判断边的两端点是否在同一个连通分量中，若是则不成环，不加入该边
            int tail_connect = vertices[edges[i].tail_index].connect;
            int head_connect = vertices[edges[i].head_index].connect;
            if (tail_connect == head_connect)
                continue;
            else {
                for (int j = 0; j < c[tail_connect].size(); j++) {
                    vertices[c[tail_connect][j]].connect = head_connect;
                    c[head_connect].push_back(c[tail_connect][j]);
                }
                tree_edges.push_back(edges[i]);
            }
            //边数满足树的要求，则退出
            if (tree_edges.size() == vertices.size()-1)
                break;
        }
    }
};

#endif
