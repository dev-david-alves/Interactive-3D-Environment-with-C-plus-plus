#include <headers/brick.h>
#include <vector>
#include <cmath>
#include <typeinfo>

#include <utils/utils.h>

using namespace std;

Brick::Brick(Vetor3D initialPos) {
    this->setTranslation(initialPos);
    this->setType("brick");
};

Utils utils = Utils();

void Brick::draw(vector<vector<vector<int>>> &terrain) {
    Object::draw(terrain);

    float colors[6][3] = {
        {0.6, 0.2, 0.2}, // back
        {0.6, 0.2, 0.2}, // front
        {0.6, 0.2, 0.2}, // left
        {0.6, 0.2, 0.2}, // right
        {0.6, 0.2, 0.2}, // bottom
        {0.57, 0.75, 0.015}  // top
    };

    Vetor3D tra = this->getTranslation();
    Vetor3D rot = this->getRotation();
    Vetor3D scl = this->getScaling();
    
    utils.DrawCube(terrain, tra, rot, scl, colors);
    this->drawOrigin();
}