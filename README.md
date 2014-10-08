<h1>spring-model</h1>
============
<h2>The Kamada-Kawai spring model</h2>

<p>
The desirable 'geometric' distance between two vertices is regarded as the 'graph theoretic' distance between them in the corresponding graph. A virtual dynamic system is introduced in which every two vertices are connected by a 'spring' of desirable length. The optimal layout of vertices is regarded as the state in which the total spring energy of the system is minimal.
</p>
</br>

<h3> Implementation </h3>
<p>
OpenGL with C++ has been used to implement and visualize this model. The DrawLine and DrawCircle files implement the mid-point (Bresenham's) algorithm to draw lines and circles respectively. sfm.cpp file implements the spring force model as described by the Kamada-Kawai spring model. main.cpp is the driver program. 
</p>
</br>
<p>
The points are input interactively at run-time. Each point selected is shown by a circle (of constant radius) with that point as the circle's centre. To draw a line, two of the already input points are selected. After the input of the graph, to run the program, a point on the top 100 pixels of the (glut) window is selected. 
</p>
