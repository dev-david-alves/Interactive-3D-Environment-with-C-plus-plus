#include <headers/object.h>
#include <vector>

using namespace std;

Object::Object() {};

void Object::draw() {
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
    if(this->getCanDrawOrigin()) {
        GUI::drawOrigin(size);
    }
}

// State

void Object::setType(string type) {
    this->type = type;
}

string Object::getType() {
    return this->type;
}

void Object::setIsSelected(bool select) {
    this->isSelected = select;
}

bool Object::getIsSelected() {
    return this->isSelected;
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