#include <iostream>
#include <stdlib.h>
#include <time.h>  
#include <memory>

using namespace std;

#include <gui.h>
#include <vector>

#include <headers/object.h>
#include <headers/brick.h>
#include <headers/tree.h>
#include <headers/model.h>
#include <utils/perlinNoise.h>


int height = 32; // y
int width = 32;  // x
int depth = 32;  // z
float scaleFactor = 0.6;

vector<vector<vector<int>>> terrain(height, vector<vector<int>>(width, vector<int>(depth, 0)));

int selectedObj = -1;
vector<Brick> brickArr;
Brick* nBrick;

vector<Object*> objects;
Tree* nTree;

void createTerrain() {
    PerlinNoise perlin;

    double scaleX = 0.1;
    double scaleZ = 0.1;
    double scaleY = 0.7; 

    for (int z = 0; z < depth; ++z) {
        for (int x = 0; x < width; ++x) {
            double nx = static_cast<double>(x) * scaleX;
            double nz = static_cast<double>(z) * scaleZ;
            double ny = perlin.noise(nx, 0.0, nz) * scaleY;

            int yHeight = static_cast<int>((ny + 1.0) * 10.0);

            for(int k = 0; k < height; k++) {
                if(k < yHeight) {
                    Vetor3D initialPos = Vetor3D(x, k, z);
                    terrain[k][x][z] = 1;
                    brickArr.push_back(Brick(initialPos));

                }
            }
        }
    }
}

void drawFloor() {
    for(auto b: brickArr) {
        Vetor3D v = b.getTranslation();

        int x = v.x;
        int y = v.y;
        int z = v.z;

        if(terrain[y][x][z] == 1) {
            glPushMatrix(); 
                b.draw(terrain);
            glPopMatrix();
        }
    }
}

int calculateOffsetY(int x, int z) {
    int lastOne = 0;

    for(int i = 0; i < height; i++) {
        if(terrain[i][x][z] != 1) break;
        lastOne = i;
    }

    return lastOne;
}

void createTrees(int numT) {
    for(int i = 0; i < numT; i++) {
        int x = rand() % width;
        int z = rand() % depth;

        int y = calculateOffsetY(x, z);

        nTree = new Tree(Vetor3D(x, y + scaleFactor / 2, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nTree);
    }
}

Model fruit = Model(Vetor3D(10, 0, 10), Vetor3D(1, 1, 1), "./3ds/fruit.3DS");
Model bridge1 = Model(Vetor3D(47, 0, 40), Vetor3D(2.3, 2.3, 2.3), "./3ds/bridge.3DS");
Model bridge2 = Model(Vetor3D(37, 0, 12), Vetor3D(2.3, 2.3, 2.3), "./3ds/bridge.3DS");

void toggleSelectObj(bool select = true) {
    if (selectedObj != -1) {
        Object* objPtr = objects[selectedObj];
        objPtr->setSelected(select);

        if(!select) objPtr->setCanDrawOrigin(false);
    }
}

float offsetX = width / 2.0;
float offsetZ = depth / 2.0;
float offsetY = 15.0;

void draw()
{
    GUI::displayInit();

    GUI::setLight(1, 0, 24, 24, true, false);
    glDisable(GL_CULL_FACE);
    
    // Custom
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    GUI::drawOrigin(3.0);
    glTranslatef(-offsetX, 0, -offsetZ);

    drawFloor();

    for (const auto& objPtr : objects) {
        objPtr->draw(terrain);
    }

    toggleSelectObj(true);

    if (selectedObj != -1) {
        Object* objPtr = objects[selectedObj];

        Vetor3D tra = objPtr->getTranslation();
        Vetor3D rot = objPtr->getRotation();
        Vetor3D scl = objPtr->getScaling();

        objPtr->setTranslation(Vetor3D(tra.x + glutGUI::dtx * 10.0, tra.y + glutGUI::dty * 10.0, tra.z + glutGUI::dtz * 10.0));
        objPtr->setRotation(Vetor3D(rot.x + glutGUI::dax * 10.0, rot.y + glutGUI::day * 10.0, rot.z + glutGUI::daz * 10.0));
        objPtr->setScaling(Vetor3D(scl.x + glutGUI::dsx, scl.y + glutGUI::dsy, scl.z + glutGUI::dsz));

        glutGUI::trans_obj = true;
        glutGUI::trans_luz = false;
    } else {
        glutGUI::trans_obj = false;
    }

    // fruit.draw(terrain);
    
    // glPushMatrix();
    //     glTranslatef(0, 3, 0);

    //     bridge1.draw(terrain);
    //     bridge2.draw(terrain);
    // glPopMatrix();

    // Custom

    GUI::displayEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    GUI::keyInit(key, x, y);

    switch (key)
    {
    case 'l':
        toggleSelectObj(false);
        selectedObj = -1;

        if(glutGUI::trans_luz) {
            glutGUI::trans_luz = false;
            glutGUI::trans_obj = false;
        } else {
            glutGUI::trans_luz = true;
        }

        glutGUI::sclMode = false;

        break;
    case '0':
        toggleSelectObj(false);
        selectedObj = -1;

        glutGUI::trans_obj = false;
        glutGUI::trans_luz = false;
        glutGUI::sclMode = false;

        break;
    case 'g':
        toggleSelectObj(false);
        if(selectedObj > 0) selectedObj--;
        else selectedObj = static_cast<int>(objects.size()) - 1;
        glutGUI::sclMode = false;

        break;
    case 'h':
        toggleSelectObj(false);
        selectedObj++;
        selectedObj = selectedObj % static_cast<int>(objects.size());
        glutGUI::sclMode = false;

        break;
    case '-':
        glutGUI::sclMode = !glutGUI::sclMode;

        break;
    case '=':
        if (selectedObj != -1) {
            Object* objPtr = objects[selectedObj];
            objPtr->setCanDrawOrigin(!objPtr->getCanDrawOrigin());
        }

        break;
    case '2': 
        glutGUI::sclMode = false;
        toggleSelectObj(false);

        nTree = new Tree(Vetor3D(offsetX, offsetY, offsetZ), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nTree);
        selectedObj = static_cast<int>(objects.size()) - 1;

        break;
    case '[': 
        if(selectedObj != -1) {
            objects.erase(objects.begin() + selectedObj);
            selectedObj--;

            if(selectedObj < 0 && static_cast<int>(objects.size()) > 0) {
                selectedObj = static_cast<int>(objects.size()) - 1;
            }
        }

        break;
    case ']': 
        if(static_cast<int>(objects.size()) > 0) {
            objects.pop_back();
        }

        break;
    default:
        break;
    }
}

int main()
{
    cout << "Running..." << endl;
    createTerrain();
    createTrees(5);
    GUI gui = GUI(800, 600, draw, keyboard);
}