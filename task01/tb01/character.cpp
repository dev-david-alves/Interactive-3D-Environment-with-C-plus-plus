#include <headers/character.h>
#include <vector>
#include <cmath>
#include <typeinfo>

using namespace std;

Character::Character(Vetor3D initialPos, Vetor3D initialRotation, Vetor3D initialScale) {
    this->setTranslation(initialPos);
    this->setRotation(initialRotation);
    this->setScaling(initialScale);
    this->setType("character");
};

void Character::draw() {
    float Sr = 1.0;
    float Sg = 0.75;
    float Sb = 0.50;

    float Cr = 0.0;
    float Cg = 1.0;
    float Cb = 0.0;

    float Lr = 0.0;
    float Lg = 0.0;
    float Lb = 1.0;

    if(this->getIsSelected()) {
        Sr = 1.0;
        Sg = 0.0;
        Sb = 0.0;

        Cr = 1.0;
        Cg = 0.0;
        Cb = 0.0;

        Lr = 1.0;
        Lg = 0.0;
        Lb = 0.0;
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
        
        this->drawOrigin(3.0);

        glTranslatef(0, 1.8, -0.5);

        // Left leg
        glPushMatrix();
            GUI::setColor(Lr, Lg, Lb);
            glTranslatef(0, 0, 0.25);
            glRotatef(180, 0, 0, 1);
            glRotatef(-25, 1, 0, 0);
            GUI::drawQuadBox(0, 0, 0, 0.5, 2, 0.5);
        glPopMatrix();

        // Right leg
        glPushMatrix();
            GUI::setColor(Lr, Lg, Lb);
            glTranslatef(0.5, 0, 0.25);
            glRotatef(180, 0, 0, 1);
            glRotatef(25, 1, 0, 0);
            GUI::drawQuadBox(0, 0, 0, 0.5, 2, 0.5);
        glPopMatrix();
       
        // Left arm
        glPushMatrix();
            GUI::setColor(Sr, Sg, Sb);
            glTranslatef(-0.5, 1.5, 0.25);
            glRotatef(180, 0, 0, 1);
            glRotatef(45, 1, 0, 0);
            GUI::drawQuadBox(0, 0, 0, 0.5, 2, 0.5);
        glPopMatrix();

        // Right arm
        glPushMatrix();
            GUI::setColor(Sr, Sg, Sb);
            glTranslatef(1, 1.5, 0.25);
            glRotatef(180, 0, 0, 1);
            glRotatef(60, 1, 0, 0);
            GUI::drawQuadBox(0, 0, 0, 0.5, 2, 0.5);
        glPopMatrix();

        // Upper body
        glPushMatrix();
            GUI::setColor(Cr, Cg, Cb);
            glTranslatef(-0.5, -0.2, 0.25);
            GUI::drawQuadBox(0, 0, 0, 1, 2, 0.5);
        glPopMatrix();

        // Head
        glPushMatrix();
            GUI::setColor(Sr, Sg, Sb);
            glTranslatef(-0.5, 1.8, 0);
            GUI::drawQuadBox(0, 0, 0, 1, 1, 1);
        glPopMatrix();
    glPopMatrix();
}