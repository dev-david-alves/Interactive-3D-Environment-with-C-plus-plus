#include <iostream>
#include <stdlib.h>
#include <time.h>  
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


#include <gui.h>
#include <headers/object.h>
#include <utils/perlinNoise.h>

#include <headers/brick.h>
#include <headers/tree.h>
#include <headers/character.h>
#include <headers/sheep.h>
#include <headers/spider.h>

// Declarations

int height = 16; // y
int width = 16;  // x
int depth = 16;  // z
float scaleFactor = 0.6;

float offsetX = width / 2.0;
float offsetZ = depth / 2.0;
float offsetY = 15.0;

vector<vector<vector<int>>> terrain(height, vector<vector<int>>(width, vector<int>(depth, 0)));

int selectedObj = -1;
vector<Object*> brickArr;
Brick* nBrick;

vector<Object*> objects;
Tree* nTree;
Sheep* nSheep;
Spider* nSpider;
Character* nCharacter;

string defultFilePath = "./csv/objects.csv";

// -----------

// Helper functions

void createTerrainByVector() {
    for (int x = 0; x < width; x++) {
        for (int k = 0; k < height; k++) {
            for(int z = 0; z < depth; z++) {
                if(terrain[k][x][z] == 1) {
                    Vetor3D initialPos = Vetor3D(x, k, z);
                    nBrick = new Brick(initialPos, terrain);
                    brickArr.push_back(nBrick);
                }
            }
        }
    }
}

string v3dToString(Vetor3D v3d) {
    return to_string(v3d.x) + "," + to_string(v3d.y) + "," + to_string(v3d.z);
}

Vetor3D stringToV3d(string Sx, string Sy, string Sz) {
    return Vetor3D(stof(Sx), stof(Sy), stof(Sz));
}

void createCSV(vector<Object*> v, const string& filename = defultFilePath) {
    ofstream file(filename);

    if (file.is_open()) {
        for(auto el: v) {
            Vetor3D tra = el->getTranslation();
            Vetor3D rot = el->getRotation();
            Vetor3D scl = el->getScaling();
            int isSelected = el->getIsSelected();
            int canDrawOrigin = el->getCanDrawOrigin();

            int selectedIndex = selectedObj;

            if(!isSelected) selectedIndex = -1;

            string phrase = v3dToString(tra) + "," + v3dToString(rot) + "," + v3dToString(scl) + "," + to_string(isSelected) + "," + to_string(selectedIndex) + "," + to_string(canDrawOrigin) + "," + el->getType() + "\n";
            file << phrase;
        }

        file.close();

        cout << "CSV file created successfully.\n";
    } else {
        cerr << "Error creating CSV file.\n";
    }
}

void readCSV(const string& filename= defultFilePath) {
    bool isBrick = false;

    ifstream file(filename);

    if (file.is_open()) {
        string line;

        // Read and display data
        while (getline(file, line)) {
            stringstream ss(line);
            string Tx, Ty, Tz, Rx, Ry, Rz, Sx, Sy, Sz, isSelected, selectedIndex, canDrawOrigin, type;

            // Translation
            getline(ss, Tx, ',');
            getline(ss, Ty, ',');
            getline(ss, Tz, ',');
            
            // Rotation
            getline(ss, Rx, ',');
            getline(ss, Ry, ',');
            getline(ss, Rz, ',');

            // Scaling
            getline(ss, Sx, ',');
            getline(ss, Sy, ',');
            getline(ss, Sz, ',');

            // State
            getline(ss, isSelected, ',');
            getline(ss, selectedIndex, ',');
            getline(ss, canDrawOrigin, ',');

            // Type
            getline(ss, type, ',');

            if(type == "brick") {
                isBrick = true;
                
                int x = stoi(Tx);
                int y = stoi(Ty);
                int z = stoi(Tz);

                terrain[y][x][z] = 1;
            } else if(type == "tree") {
                nTree = new Tree(stringToV3d(Tx, Ty, Tz), stringToV3d(Rx, Ry, Rz), stringToV3d(Sx, Sy, Sz));
                nTree->setIsSelected(stoi(isSelected));
                nTree->setCanDrawOrigin(stoi(canDrawOrigin));

                if(nTree->getIsSelected()) selectedObj = stoi(selectedIndex);

                objects.push_back(nTree);
            } else if(type == "character") {
                nCharacter = new Character(stringToV3d(Tx, Ty, Tz), stringToV3d(Rx, Ry, Rz), stringToV3d(Sx, Sy, Sz));
                nCharacter->setIsSelected(stoi(isSelected));
                nCharacter->setCanDrawOrigin(stoi(canDrawOrigin));

                if(nCharacter->getIsSelected()) selectedObj = stoi(selectedIndex);

                objects.push_back(nCharacter);
            }
        }

        file.close();
    } else {
        cerr << "Error opening CSV file.\n";
    }

    if(isBrick) createTerrainByVector();
}

bool isFileEmpty(const string& filename= defultFilePath) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "File: " << filename << " does not exist!\n";
        return true;
    }

    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.close();

    if(fileSize == 0) cout << "File: " << filename << " is empty!\n";
    else if(fileSize == 0) cout << "File: " << filename << " is not empty!\n";

    return fileSize == 0;
}

// ----------------------------

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
                    terrain[k][x][z] = 1;
                }
            }
        }
    }

    createTerrainByVector();
}

void drawFloor() {
    for(auto b: brickArr) {
        Vetor3D v = b->getTranslation();

        int x = v.x;
        int y = v.y;
        int z = v.z;

        if(terrain[y][x][z] == 1) {
            glPushMatrix(); 
                b->draw();
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

void createCharacter(int numT) {
    for(int i = 0; i < numT; i++) {
        int x = rand() % width;
        int z = rand() % depth;

        int y = calculateOffsetY(x, z);

        nCharacter = new Character(Vetor3D(x, y + scaleFactor / 2, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nCharacter);
    }
}

void createSheep(int numT) {
    for(int i = 0; i < numT; i++) {
        int x = rand() % width;
        int z = rand() % depth;

        int y = calculateOffsetY(x, z);

        nSheep = new Sheep(Vetor3D(x, y + scaleFactor * 3, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nSheep);
    }
}

void createSpider(int numT) {
    for(int i = 0; i < numT; i++) {
        int x = rand() % width;
        int z = rand() % depth;

        int y = calculateOffsetY(x, z);

        nSpider = new Spider(Vetor3D(x, y + scaleFactor * 2, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nSpider);
    }
}

void toggleSelectObj(bool select = true) {
    if (selectedObj != -1) {
        Object* objPtr = objects[selectedObj];
        objPtr->setIsSelected(select);

        if(!select) objPtr->setCanDrawOrigin(false);
    }
}

void draw()
{
    GUI::displayInit();

    GUI::setLight(1, 0, 24, 24, true, false);
    // glDisable(GL_CULL_FACE);
    
    // Custom
    // glScalef(scaleFactor, scaleFactor, scaleFactor);
    GUI::drawOrigin(3.0);
    // glTranslatef(-offsetX, 0, -offsetZ);

    drawFloor();

    for (const auto& objPtr : objects) {
        objPtr->draw();
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
    case '3': 
        glutGUI::sclMode = false;
        toggleSelectObj(false);

        nCharacter = new Character(Vetor3D(offsetX, offsetY, offsetZ), Vetor3D(0, 0, 0), Vetor3D(1, 1, 1));
        objects.push_back(nCharacter);
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
    case 'S': 
        createCSV(brickArr, "./csv/floor.csv");
        createCSV(objects);

        break;
    default:
        break;
    }
}

int main()
{
    cout << "Running..." << endl;
    
    if(isFileEmpty("./csv/floor.csv")) {
        createTerrain();
    } else {
        readCSV("./csv/floor.csv");
    }

    if(isFileEmpty()) {
        // createTrees(3);
        // createSheep(3);
        // createCharacter(2);
        createSpider(1);
    } else {
        readCSV();
    }

    GUI gui = GUI(800, 600, draw, keyboard);

}