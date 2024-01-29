#include <headers/object.h>
#include <vector>

using namespace std;

Object::Object() {};

void Object::draw(vector<vector<vector<int>>> &terrain) {
    Vetor3D tra = this->getTranslation();
    Vetor3D rot = this->getRotation();
    Vetor3D scl = this->getScaling();

    glPushMatrix();
        glTranslatef(tra.x, tra.y, tra.z);
        glRotatef(rot.x, 1, 0, 0);
        glRotatef(rot.y, 0, 1, 0);
        glRotatef(rot.z, 0, 0, 1);
        glScalef(scl.x, scl.y, scl.z);
    glPopMatrix();
}

void Object::drawOrigin(float size) {
    glPushMatrix();
        if(this->getCanDrawOrigin()) {
            // Vetor3D tra = this->getTranslation();
            // Vetor3D rot = this->getRotation();
            // Vetor3D scl = this->getScaling();

            // int x = tra.x;
            // int y = tra.y;
            // int z = tra.z;

            // glRotatef(rot.x, 1, 0, 0);
            // glRotatef(rot.y, 0, 1, 0);
            // glRotatef(rot.z, 0, 0, 1);
            // glTranslatef(x, y, z);
            GUI::drawOrigin(size);
        }
    glPopMatrix();
}

// State

void Object::setSelected(bool select) {
    this->selected = select;
}

bool Object::getSelected() {
    return this->selected;
}

void Object::setCanDrawOrigin(bool canDraw) {
    this->canDrawOrigin = canDraw;
}

bool Object::getCanDrawOrigin() {
    return this->canDrawOrigin;
}

// Setters

void Object::setTranslation(Vetor3D v) {
    this->translation = v;
}

void Object::setRotation(Vetor3D v) {
    this->rotation = v;
}
void Object::setScaling(Vetor3D v) {
    this->scaling = v;
}

// Getters

Vetor3D Object::getTranslation() {
    return this->translation;
}

Vetor3D Object::getRotation() {
    return this->rotation;
}

Vetor3D Object::getScaling() {
    return this->scaling;
}