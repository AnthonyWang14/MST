# ***On Constructing Minimum Spanning Tree***

###Name:Wang Hao
###Class:CST32   
###Stu.No:2012010981

##1. Abstract
###1.1 Use the *CGAL* Library for constructing the Voronoi diagram and Delaunay triangulation.

###1.2 Apply *Kruscal algorithm* on the Delaunay graph and the primial graph to verify the results.

###1.3 Use *openGL* Library to plot the MST of graph to easily verify the result.

##2. Usage

~~~bash
make
(the compile info...)
./main <testcase> [whether show Voronoi or not]
~~~

1.After running the program, there will be a window on your screen. 

2.Click your mouse(left button) to draw a Point to the window. 

3.Press key 's' will show the MST which using Delaunay triangulation.

4.Press key 'd' will show the MST using Kruscal directly.

5.Press key 'a' will load the data in testcase and show the points on the window.

##3. Details
###3.1 file structures

src			|testcases		|doc
---			|----			|----
MST.cpp		|testcase1~5		|software\_design\_report.md
MST.h		|init_random.py	|software\_design\_report.pdf
main.cpp	|
makefile	|
###3.2 main data structures and variables
####3.2.1 Point
This type is only used in Delaunay type.

####3.2.2 Delaunay
Save vertices and maintain a Delaunay triangulation for the vertices. Use the face iterator to get the edges of Delaunay triangulation.

####3.2.3 MST class
see in MST.h and MST.cpp:

MST  | usage
-------------				|--- 
-vertices : vector<Vertex>  	|vertices in the graph 
-edges : vector<Edge>   	  	|edges in the graph
-tree_edges : vector<Edge>	|edges of MST
+cmp(Edge, Edge) : bool		|compare the length of 2 edges
+add_vertex(int, int) : int	|add vertex to the graph
+add_edge(int, int : void		|add edge to the graph
+paint() : void				|draw vertices and edges
+Kruscal() : void			|use Kruscal to get MST edges
+find_connect(int) : int		|find connections (use disjoint sets in Kruscal)
+clean() : void				|clear the vertices and edges data
+vertex_num() : int     		|return the number of vertices 

###3.3 main.cpp
List some details of important functions

####3.3.1 main
openGL will create a window and wait for operation. 

The second command argument should be the name of your testcase which is saved in ./testcases.(default:"testcase1.txt")

If have the third argument, program will draw Voronoi diagram when you use Delaunay triangulation to get the MST.

####3.3.2 keyboard
The program will correspond to keyboard event when you press 'esc', 'a', 's', 'd'.

'esc':exit the program (close the window).

'a': read from files and draw the nodes (in white)

's': draw MST by using Delaunay triangulation (in blue)

'd': draw MST of the primial graph (in red)

####3.3.3 mouse
The program will correspond to mouse event.

'left button': will add a point to the graph and draw it on the window.

'right button': will clear the graph data when it has done the MST or it will do the Delaunay triangulation and draw the MST.

####3.3.4 drawPoint
It will draw the Point saved in the vertices.

####3.3.5 addPoint
Add the Point you click in the window.

####3.3.6 clear 
clear the data and window.

####3.3.7 reshape, display
Some required but not important openGL setting functions for display openGL window.

###3.4 testcases
The format is showed in below:

~~~txt
8982			<number of the vertices>
432 475			<(x,y) of one vertex>
449 147
762 460
724 199
98 485
335 497
47 521
708 181
201 216
750 599
302 58
597 559
...
~~~

###3.5 init_random.py
you can use this python script to generate your own testcase which has randomly 5000~10000 vertices. 

~~~bash
python init_random.py <testcase name>
~~~

##4. Reference
1.使用CGAL编程实现点集的Delaunay三角剖分，Voronoi图 [http://blog.csdn.net/wsh6759/article/details/7425052](http://blog.csdn.net/wsh6759/article/details/7425052)
2.并查集算法介绍 [http://blog.csdn.net/dm_vincent/article/details/7655764](http://blog.csdn.net/dm_vincent/article/details/7655764)