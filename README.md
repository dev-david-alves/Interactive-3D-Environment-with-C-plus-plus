# Interactive 3D Environment with C++

## About the projetct
In this project you will find an interactive 3D environment, similar to Minecraft, developed by me to obtain grades in the computer graphics discipline at the Federal University of Ceará.
 
## Technologies used in this project 

* C++
* Some C++ libs (with some code snippets customized by the teacher of this subject)

## How to run the project (a Linux distribution is recommended)

- Clone this repository
- Install C++ and all the required libs <br />
  QT: 
    - sudo apt-get install qtcreator (ignore this line if you like using another IDE)
    - sudo apt-get update
    - sudo apt-get install qt5-default
    - sudo apt-get install build-essential
 
  GLUT:
    - sudo apt-get install freeglut3-dev
    - sudo apt-get install libgl1-mesa-dev
    
  3D MESHS:
    - sudo apt-get install lib3ds-dev
    
  TEXTURES/IMAGES:
    - sudo apt-get install libdevil-dev
    
  SDL:
    - sudo apt-get install libsdl1.2-dev
    - sudo apt-get install libsdl-image1.2-dev

- Open the task02 folder (it's a full version, including task01)
- Run the following command if you are running through cmd like me: qmake main.pro && make && ./run/main
- Or run in the QtCreator otherwise

## Images of the project

### A square world where you can create, edit and delete objects (player, some mobs, and tree)
<img src="https://github.com/dev-david-alves/computer-graphics/blob/main/Images/img1.png?raw=true" />

### You can select and drag a object around
<img src="https://github.com/dev-david-alves/computer-graphics/blob/main/Images/img2.png?raw=true" />

### You can rotate, translate and apply scaling to a object
<img src="https://github.com/dev-david-alves/computer-graphics/blob/main/Images/img3.png?raw=true" />

### You can move the player character (at index 0) with [A,W,S,D] to see his vision
<img src="https://github.com/dev-david-alves/computer-graphics/blob/main/Images/img4.png?raw=true" />

### And much more, like shadows and other stuff!!! Try it out

##

## About me
  * **My name is David Alves Soares and I'm a Computer Science student at the Federal University of Ceará - UFC.** 
  * **Linkedin:** https://www.linkedin.com/in/dev-david-alves/


