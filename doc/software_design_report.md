# ***On Constructing Minimum Spanning Tree***

###Name:Wang Hao
###Class:CST32   
###Stu.No:2012010981

##Abstract
Use the *CGAL* Library for constructing the Voronoi diagram and Delaunay triangulation.

Apply *Kruscal algorithm* on the Delaunay graph and the primial graph to verify the results.

Use *openGL* Library to plot the MST of graph to verify the result.

##Details
###main data structures and variables
Point: this type is only used in Delaunay type

Delaunay: save vertices and maintain a Delaunay triangulation for the vertices. Use the face iterator to get the edges of Delaunay triangulation.

MST: namespace MST have the vertices of the graph and the edges of Delaunay triangulation. Tree edges save the edges of MST after Kruscal algorithm.

###main.cpp
List some details of important functions

####main
openGL will create a window and wait for operation. 

The second command argument should be number between '1' ~ '5' to choose 'testcase1' ~ 'testcase5'.(default:1)

If have the third argument, program will draw Voronoi diagram when you use Delaunay triangulation to get the MST.

####keyboard
The program will correspond to keyboard event when you press 'esc', 'a', 's', 'd'.

'esc':exit the program (close the window).

'a': read from files and draw the nodes (in white)

's': draw MST by using Delaunay triangulation (in blue)

'd': draw MST of the primial graph (in red)

####mouse
The program will correspond to mouse event.

'left button': will add a point to the graph and draw it on the window

'right button': will clear the graph data when it has done the MST or it will do the Delaunay triangulation and draw the MST.

###drawPoint
It will draw the Point saved in the vertex<>
###addPoint
###clear 
###reshape, display
Some required but not important openGL setting functions for display openGL window

###MST.h

###init_random.py



