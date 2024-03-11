#include <headers/brick.h>
#include <vector>
#include <cmath>
#include <typeinfo>

#include <utils/utils.h>

using namespace std;

Brick::Brick(Vetor3D initialPos, Vetor3D initialRotation, Vetor3D initialScale) {
    this->setTranslation(initialPos);
    this->setRotation(initialRotation);
    this->setScaling(initialScale);
    this->setType("brick");
};

Utils utils = Utils();

void Brick::draw(bool isShadow) {
    float colors[6][3] = {
        {0.6, 0.2, 0.2}, // back
        {0.6, 0.2, 0.2}, // front
        {0.6, 0.2, 0.2}, // left
        {0.6, 0.2, 0.2}, // right
        {0.6, 0.2, 0.2}, // bottom
        {0.57, 0.75, 0.015}  // top
    };

    if(this->getIsSelected()) {
        for(int i = 0; i < 6; i++) {
            colors[i][0] = 1.0;
            colors[i][1] = 0.0;
            colors[i][2] = 0.0;
        }
    }

    if(isShadow) {
        for(int i = 0; i < 6; i++) {
            colors[i][0] = 0.0;
            colors[i][1] = 0.0;
            colors[i][2] = 0.0;
        }
    }

    Vetor3D tra = this->getTranslation();
    Vetor3D rot = this->getRotation();
    Vetor3D scl = this->getScaling();

    glPushMatrix();
        glTranslatef(tra.x, tra.y, tra.z);
        glRotatef(rot.x, 1, 0, 0);
        glRotatef(rot.y, 0, 1, 0);
        glRotatef(rot.z, 0, 0, 1);
        glScalef(scl.x, scl.y, scl.z);

        this->drawOrigin(2.0);
        
        glTranslatef(-0.5, 0, 0.5);

        utils.DrawCube(colors);
    glPopMatrix();
}


void Brick::draw(vector<vector<vector<int>>> &space) {
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
    
    utils.DrawCube(space, tra, rot, scl, colors);
    this->drawOrigin();
}