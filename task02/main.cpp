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
#include <headers/chicken.h>

// Declarations

int cameraID = 5;
int numCams = 7;
int viewportID = -1;
int numViewports = 3;
int projectionType = 4;
int projectionVariant = -1;
float customFov = 30.;
bool canPick = true;
float orthof = 0.03;

int height = 24; // y
int width = 38;  // x
int depth = 38;  // z
float scaleFactor = 0.6;

float offsetX = width / 2.0;
float offsetZ = depth / 2.0;
float offsetY = 15.0;

vector<vector<vector<int>>> terrain(height, vector<vector<int>>(width, vector<int>(depth, 0)));

int selectedObj = -1;
vector<Brick*> brickArr;
Brick* nBrick;

vector<Object*> objects;
Tree* nTree;
Sheep* nSheep;
Spider* nSpider;
Chicken* nChicken;
Character* nCharacter;

string defultFilePath = "./csv/objects.csv";

// -----------

// Helper functions

void updateCamera() {
    cameraID = (cameraID + 1) % numCams;

    switch (cameraID) {
        case 0:
            glutGUI::cam = new CameraDistante(36.1593, 52.0569, 33.8342, -0.374595, 3.00397, 0.195141, -0.516964, 0.711456, -0.476002);
            break;
        case 1:
            glutGUI::cam = new CameraDistante(35.1502, 50.7328, -36.3078, -0.374595, 3.00397, 0.195141, -0.476882, 0.729706, 0.490012);
            break;
        case 2:
            glutGUI::cam = new CameraDistante(-25.7932, 51.7887, -42.7752, -0.374595, 3.00397, 0.195141, 0.355825, 0.715231, 0.601526);
            break;
        case 3:
            glutGUI::cam = new CameraDistante(-33.2456, 54.5045, 34.0059, -1.75942, 3.00397, -1.04871, 0.493013, 0.675026, -0.548888);
            break;
        case 4:
            glutGUI::cam = new CameraDistante(-45.1375, 45.7314, -2.4365, -1.75942, 3.00397, -1.04871, 0.701202, 0.712609, 0.0224334);
            break;
        case 5:
            glutGUI::cam = new CameraDistante(-1.45606, 41.2756, -48.4239, -1.75942, 3.00397, -1.04871, -0.00402372, 0.777891, 0.628386);
            break;
        default:
            glutGUI::cam = new CameraDistante(0, 72, 48, 0, 1, 0, 0, 1, 0);
            break;
    }
}

void updateProjectionVariant() {
    if(projectionType == 0) {
        cout << "Perspective with 120 fov\n";
        projectionVariant = (projectionVariant + 1) % 3;
        glutGUI::perspective = true;
        customFov = 120.;

        switch (projectionVariant) {
            case 0:
                glutGUI::cam = new CameraDistante(-0.649749, 16.3132, 17.8613, -0.684494, 7.14594, -4.10465,  0., 1., 0.);
                break;
            case 1:
                glutGUI::cam = new CameraDistante(15.6342, 14.6921, 13.3225, -0.121987, 10.2937, -4.17344,  0., 1., 0.);
                break;
            case 2:
                glutGUI::cam = new CameraDistante(-5.33653, 9.8339, 14.7601, -15.1616, 12.8533, 1.97791,  0., 1., 0.);
                break;
            default:
                glutGUI::cam = new CameraDistante(-0.649749, 16.3132, 17.8613, -0.684494, 7.14594, -4.10465,  0., 1., 0.);
                break;
        }
    } else if(projectionType == 1) {
        cout << "Orthographic view\n";

        projectionVariant = (projectionVariant + 1) % 3;
        glutGUI::perspective = false;

        switch (projectionVariant) {
            case 0:
                glutGUI::cam = new CameraDistante(27.9903, 24.6903, 51.7745, 27.9903, 24.6903, 0, 0, 1, 0);
                break;
            case 1:
                glutGUI::cam = new CameraDistante(74, 24.7816, -28.4708, 37.5, 24.7816, -28.4708, 0, 1, 0);
                break;
            case 2:
                glutGUI::cam = new CameraDistante(0.04, 92.7794, -29.7485, 0, -1.57253, -29.7485, 0, 1, 0);
                break;
            default:
                glutGUI::cam = new CameraDistante(27.9903, 24.6903, 51.7745, 27.9903, 24.6903, 0, 0, 1, 0);
                break;
        }
    } else if(projectionType == 2) {
        cout << "Orthographic axonometric view\n";

        projectionVariant = (projectionVariant + 1) % 3;
        glutGUI::perspective = false;

        switch (projectionVariant) {
            case 0:
                glutGUI::cam = new CameraDistante(51.1404, 54.7472, 4.53408, 30.8242, 25.2462, -12.1734, -0.576491, 0.665503, -0.474092);
                break;
            case 1:
                glutGUI::cam = new CameraDistante(60.2538, 34.1738, 14.4989, 32.4709, 19.9109, -9.72665, -0.271986, 0.932619, -0.237161);
                break;
            case 2:
                glutGUI::cam = new CameraDistante(63.1569, 41.9716, 1.43672, 32.3913, 23.4102, -15.03, -0.414041, 0.88287, -0.221608);
                break;
            default:
                glutGUI::cam = new CameraDistante(51.1404, 54.7472, 4.53408, 30.8242, 25.2462, -12.1734, -0.576491, 0.665503, -0.474092);
                break;
        }
    } else if(projectionType == 3) {
        cout << "Oblique view\n";
        glutGUI::perspective = false;

        glutGUI::cam = new CameraDistante(35.3964, 25.1987, 37.6592, 29.0114, 15.7886, -1.18523, -0.0377098, 0.972598, -0.229413);
    } else {
        cout << "(Default) Perspective with 30 fov\n";
        glutGUI::perspective = true;
        customFov = 30.;
        cameraID = 5;
        updateCamera();
    }
}

void createTerrainByVector() {
    for (int x = 0; x < width; x++) {
        for (int k = 0; k < height; k++) {
            for(int z = 0; z < depth; z++) {
                if(terrain[k][x][z] == 1) {
                    Vetor3D initialPos = Vetor3D(x, k, z);
                    nBrick = new Brick(initialPos);
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

void createTerrainCSV(vector<Brick*> b, const string& filename = "./csv/terrain.csv") {
    ofstream file(filename);

    if (file.is_open()) {
        for(auto el: b) {
            Vetor3D tra = el->getTranslation();
            string phrase = v3dToString(tra) + "\n";
            file << phrase;
        }

        file.close();

        cout << "CSV file created successfully.\n";
    } else {
        cerr << "Error creating CSV file.\n";
    }

}

void readCSV(const string& filename = defultFilePath, bool isTerrain = false) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;

        if(isTerrain) {
            while (getline(file, line)) {
                stringstream ss(line);
                string Tx, Ty, Tz;

                // Translation
                getline(ss, Tx, ',');
                getline(ss, Ty, ',');
                getline(ss, Tz, ',');

                int x = stoi(Tx);
                int y = stoi(Ty);
                int z = stoi(Tz);

                terrain[y][x][z] = 1;
            }

            createTerrainByVector();
        } else {
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
                    nBrick = new Brick(stringToV3d(Tx, Ty, Tz), stringToV3d(Rx, Ry, Rz), stringToV3d(Sx, Sy, Sz));
                    nBrick->setIsSelected(stoi(isSelected));
                    nBrick->setCanDrawOrigin(stoi(canDrawOrigin));

                    if(nBrick->getIsSelected()) selectedObj = stoi(selectedIndex);

                    objects.push_back(nBrick);
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
                } else if(type == "sheep") {
                    nSheep = new Sheep(stringToV3d(Tx, Ty, Tz), stringToV3d(Rx, Ry, Rz), stringToV3d(Sx, Sy, Sz));
                    nSheep->setIsSelected(stoi(isSelected));
                    nSheep->setCanDrawOrigin(stoi(canDrawOrigin));

                    if(nSheep->getIsSelected()) selectedObj = stoi(selectedIndex);

                    objects.push_back(nSheep);
                } else if(type == "spider") {
                    nSpider = new Spider(stringToV3d(Tx, Ty, Tz), stringToV3d(Rx, Ry, Rz), stringToV3d(Sx, Sy, Sz));
                    nSpider->setIsSelected(stoi(isSelected));
                    nSpider->setCanDrawOrigin(stoi(canDrawOrigin));

                    if(nSpider->getIsSelected()) selectedObj = stoi(selectedIndex);

                    objects.push_back(nSpider);
                } else if(type == "chicken") {
                    nChicken = new Chicken(stringToV3d(Tx, Ty, Tz), stringToV3d(Rx, Ry, Rz), stringToV3d(Sx, Sy, Sz));
                    nChicken->setIsSelected(stoi(isSelected));
                    nChicken->setCanDrawOrigin(stoi(canDrawOrigin));

                    if(nChicken->getIsSelected()) selectedObj = stoi(selectedIndex);

                    objects.push_back(nChicken);
                }
            }
        }

        file.close();
    } else {
        cerr << "Error opening CSV file.\n";
    }
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
                b->draw(terrain);
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

        nCharacter = new Character(Vetor3D(x, y + scaleFactor, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nCharacter);
    }
}

void createSheep(int numT) {
    for(int i = 0; i < numT; i++) {
        int x = rand() % width;
        int z = rand() % depth;

        int y = calculateOffsetY(x, z);

        nSheep = new Sheep(Vetor3D(x, y + 0.5, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nSheep);
    }
}

void createSpider(int numT) {
    for(int i = 0; i < numT; i++) {
        int x = rand() % width;
        int z = rand() % depth;

        int y = calculateOffsetY(x, z);

        nSpider = new Spider(Vetor3D(x, y + scaleFactor, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
        objects.push_back(nSpider);
    }
}

void createChicken(int numT) {
    for(int i = 0; i < numT; i++) {
        int x = rand() % width;
        int z = rand() % depth;

        int y = calculateOffsetY(x, z);

        nChicken = new Chicken(Vetor3D(x, y + scaleFactor, z), Vetor3D(0, 0, 0), Vetor3D(scaleFactor  / 2, scaleFactor  / 2, scaleFactor  / 2));
        objects.push_back(nChicken);
    }
}

void toggleSelectObj(bool select = true) {
    if (selectedObj != -1) {
        Object* objPtr = objects[selectedObj];
        objPtr->setIsSelected(select);

        if(!select) objPtr->setCanDrawOrigin(false);
    }
}

void drawScenario() {
    GUI::drawOrigin(3.0);
    GUI::setLight(1, 20, 38, 10, true, false);
    glTranslatef(-offsetX, 0, -offsetZ);

    // Draw floor
    drawFloor();

    // Draw objects
    int indexName = 1;

    for (const auto& objPtr : objects) {
        glPushName(indexName);
            objPtr->draw();
            indexName++;
        glPopName();
    }

    glTranslatef(offsetX, 0, offsetZ);
}

void updateViewports() {
    viewportID = (viewportID + 1) % (numViewports + 1);
}

void drawViewports() {
    float width = glutGUI::width;
    float height = glutGUI::height;
    const float ar = height>0 ? (float) width / (float) height : 1.0;

    glMatrixMode(GL_PROJECTION);
    if(!glutGUI::picking) {
        glLoadIdentity();
    }

    if(glutGUI::perspective) {
        gluPerspective(customFov, ar, 0.1, 1000.);
    } else {
        glOrtho(-orthof * width, orthof,-orthof * height,orthof * height, 0.0, 100.);
    }

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
    glLoadIdentity();
    gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
    drawScenario();

    // Player viewport
    if(selectedObj != -1) {
        Object* objPtr = objects[selectedObj];
        if(objPtr->getType() == "character" && objPtr->playerName == "Player") {
            viewportID = numViewports + 1;
            Vetor3D tra = objPtr->getTranslation();
            Vetor3D rot = objPtr->getRotation();
            
            objPtr->playerYVel -= objPtr->gravity;
            if(tra.y + objPtr->playerYVel < calculateOffsetY(tra.x, tra.z) + 1) {
                objPtr->playerYVel = 0;
                objPtr->setTranslation(Vetor3D(tra.x, calculateOffsetY(tra.x, tra.z) + 0.6, tra.z));
            } else {
                objPtr->setTranslation(Vetor3D(tra.x, tra.y + objPtr->playerYVel, tra.z));
            }

            float x = tra.x + sin(rot.y * M_PI / 180) - offsetX;
            float z = tra.z + cos(rot.y * M_PI / 180) - offsetZ;

            // Put light on that viewport
            GUI::glScissoredViewport(0, 3 * height / 4, width / 4, height / 4);
            glLoadIdentity();
            gluLookAt(tra.x - offsetX, tra.y + 3, tra.z - offsetZ, x, tra.y + 2.7, z, 0, 1, 0);
            drawScenario();
        }
    }

    // Other viewports
    switch (viewportID) {
        case 0:
            GUI::glScissoredViewport(0, 3 * height / 4, width / 4, height / 4);
            glLoadIdentity();
            gluLookAt(37.5597, 24.1961, 27.6964, -4.08124, 3.22017, 9.91225, -0.386562, 0.907366, -0.165094);
            drawScenario();
            break;
        case 1:
            GUI::glScissoredViewport(0, 3 * height / 4, width / 4, height / 4);
            glLoadIdentity();
            gluLookAt(-24.6673, 25.0923, -45.725, -0.279888, -0.0280033, 4.59568, 0.178714, 0.912185, 0.368755);
            drawScenario();
            break;
        case 2:
            GUI::glScissoredViewport(0, 3 * height / 4, width / 4, height / 4);
            glLoadIdentity();
            gluLookAt(0.13474, 29.7279, -25.9732, 0.0197747, 8.41875, 5.61293, -0.00203556, 0.828989, 0.559261);
            drawScenario();
            break;
        default:
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    // GUI::keyUpInit(key, x, y);

    if (selectedObj != -1) {
        Object* objPtr = objects[selectedObj];
        if(objPtr->getType() == "character" && objPtr->playerName == "Player") {
            if(key == 'w') {
                objPtr->isMoving = false;
            }
        }
    }
}

void draw(){
    glutKeyboardUpFunc(keyboardUp);
    canPick = !(!glutGUI::perspective || (glutGUI::perspective && customFov != 30.));

    // Init
    GUI::displayInit();

    drawViewports();

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

//-------------------picking start ------------------

int picking(GLint cursorX, GLint cursorY, int w, int h) {
    if(!canPick) return 0;

    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX, cursorY, w, h, selectBuf, BUFSIZE);

    GUI::displayInit();
    drawScenario();
    GUI::displayEnd();

    return GUI::pickingClosestName(selectBuf, BUFSIZE);
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking(x, y, 5, 5);
            if (pick != 0 && pick != selectedObj + 1) {
                toggleSelectObj(false);
                selectedObj = pick - 1;
                toggleSelectObj(true);
                glutGUI::lbpressed = false;
            }
        }
    }
}

//-------------------picking end --------------------

void keyboard(unsigned char key, int x, int y)
{
    GUI::keyInit(key, x, y);

    switch (key) {
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
        case '-':
            toggleSelectObj(false);
            if(selectedObj > 0) selectedObj--;
            else selectedObj = static_cast<int>(objects.size()) - 1;
            glutGUI::sclMode = false;

            break;
        case '+':
            toggleSelectObj(false);
            selectedObj++;
            selectedObj = selectedObj % static_cast<int>(objects.size());
            glutGUI::sclMode = false;

            break;
        case ',':
            glutGUI::sclMode = !glutGUI::sclMode;

            break;
        case '.':
            if (selectedObj != -1) {
                Object* objPtr = objects[selectedObj];
                objPtr->setCanDrawOrigin(!objPtr->getCanDrawOrigin());
            }

            break;
        case '1': 
            glutGUI::sclMode = false;
            toggleSelectObj(false);

            nTree = new Tree(Vetor3D(offsetX, offsetY, offsetZ), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
            objects.push_back(nTree);
            selectedObj = static_cast<int>(objects.size()) - 1;

            break;
        case '2': 
            glutGUI::sclMode = false;
            toggleSelectObj(false);

            nCharacter = new Character(Vetor3D(offsetX, offsetY, offsetZ), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
            objects.push_back(nCharacter);
            selectedObj = static_cast<int>(objects.size()) - 1;

            break;
        case '3': 
            glutGUI::sclMode = false;
            toggleSelectObj(false);

            nSheep = new Sheep(Vetor3D(offsetX, offsetY, offsetZ), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
            objects.push_back(nSheep);
            selectedObj = static_cast<int>(objects.size()) - 1;

            break;
        case '4': 
            glutGUI::sclMode = false;
            toggleSelectObj(false);

            nSpider = new Spider(Vetor3D(offsetX, offsetY, offsetZ), Vetor3D(0, 0, 0), Vetor3D(scaleFactor, scaleFactor, scaleFactor));
            objects.push_back(nSpider);
            selectedObj = static_cast<int>(objects.size()) - 1;

            break;
        case '5': 
            glutGUI::sclMode = false;
            toggleSelectObj(false);

            nChicken = new Chicken(Vetor3D(offsetX, offsetY, offsetZ), Vetor3D(0, 0, 0), Vetor3D(scaleFactor / 2, scaleFactor / 2, scaleFactor / 2));
            objects.push_back(nChicken);
            selectedObj = static_cast<int>(objects.size()) - 1;

            break;
        case '6': 
            glutGUI::sclMode = false;
            toggleSelectObj(false);

            nBrick = new Brick(Vetor3D(offsetX, offsetY, offsetZ));
            objects.push_back(nBrick);
            selectedObj = static_cast<int>(objects.size()) - 1;

            break;
        case '7':
            updateCamera();

            break;
        case '8':
            updateViewports();

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
            createTerrainCSV(brickArr);
            createCSV(objects);

            break;
        case ':':
            cout << "Camera pos: " << glutGUI::cam->e.x << ", " << glutGUI::cam->e.y << ", " << glutGUI::cam->e.z << ", " 
            << glutGUI::cam->c.x << ", " << glutGUI::cam->c.y << ", " << glutGUI::cam->c.z << ", "
            << glutGUI::cam->u.x << ", " << glutGUI::cam->u.y << ", " << glutGUI::cam->u.z << endl;
            
            break;
        case 'a':
            if(selectedObj != -1) {
                Object* objPtr = objects[selectedObj];
                if(objPtr->getType() == "character" && objPtr->playerName == "Player") {
                    objPtr->setRotation(Vetor3D(0, objPtr->getRotation().y - 8, 0));
                }
            }
            break;
        case 'd':
            if(selectedObj != -1) {
                Object* objPtr = objects[selectedObj];
                if(objPtr->getType() == "character" && objPtr->playerName == "Player") {
                    objPtr->setRotation(Vetor3D(0, objPtr->getRotation().y + 8, 0));
                }
            }
            break;
        case 'w':
            if(selectedObj != -1) {
                Object* objPtr = objects[selectedObj];
                if(objPtr->getType() == "character" && objPtr->playerName == "Player") {
                    float x = sin(objPtr->getRotation().y * M_PI / 180);
                    float z = cos(objPtr->getRotation().y * M_PI / 180);
                    float newX = objPtr->getTranslation().x + x / 3;
                    float newZ = objPtr->getTranslation().z + z / 3;

                    if(newX >= 0 && newX < width && newZ >= 0 && newZ < depth) {
                        objPtr->isMoving = true;
                        objPtr->setTranslation(Vetor3D(newX, objPtr->getTranslation().y, newZ));
                    }
                }
            }
            break;
        case '~':
            projectionType = (projectionType + 1) % 5;
            projectionVariant = -1;
            updateProjectionVariant();

            break;
        case 'p':
            updateProjectionVariant();

            break;
        case ';':
            if(projectionType != 4) return;
            
            customFov = ((int) customFov + 10) % 120;
            if(customFov < 30) customFov = 30;
            
            break;
        default:
            break;
    }
}


int main()
{
    cout << "Running..." << endl;
    
    // Terrain
    if(isFileEmpty("./csv/terrain.csv")) {
        createTerrain();
    } else {
        readCSV("./csv/terrain.csv", true);
    }

    // Objects
    if(isFileEmpty()) {
        createCharacter(2);
        createTrees(3);
        // createSheep(3);
        // createSpider(3);
        // createChicken(3);
    } else {
        readCSV();
    }

    objects[0]->playerName = "Player";
    objects[0]->setRotation(Vetor3D(0, 180, 0));
    
    updateCamera();
    GUI gui = GUI(800, 600, draw, keyboard, mouse);
}
