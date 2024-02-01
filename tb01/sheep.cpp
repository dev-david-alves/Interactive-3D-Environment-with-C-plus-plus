#include <headers/sheep.h>
#include <vector>
#include <cmath>
#include <typeinfo>

using namespace std;

Sheep::Sheep(Vetor3D initialPos, Vetor3D initialRotation, Vetor3D initialScale) {
    this->setTranslation(initialPos);
    this->setRotation(initialRotation);
    this->setScaling(initialScale);
    this->setType("sheep");
};

void Sheep::draw() {
    float Sr = 1.0;
    float Sg = 0.75;
    float Sb = 0.50;

    float Cr = 1.0;
    float Cg = 1.0;
    float Cb = 1.0;

    if(this->getIsSelected()) {
        Sr = 1.0;
        Sg = 0.0;
        Sb = 0.0;

        Cr = 1.0;
        Cg = 0.0;
        Cb = 0.0;
    }

    Vetor3D tra = this->getTranslation();
    Vetor3D rot = this->getRotation();
    Vetor3D scl = this->getScaling();

    glPushMatrix();
        glTranslatef(tra.x, tra.y + scl.y / 4, tra.z);
        glRotatef(rot.x, 1, 0, 0);
        glRotatef(rot.y, 0, 1, 0);
        glRotatef(rot.z, 0, 0, 1);

        this->drawOrigin(3.0);
        
        glScalef(scl.x, scl.y, scl.z);

        glTranslatef(0, 1, -1);
        glRotatef(90, 1, 0, 0);

        // Left leg
        glPushMatrix();
            glTranslatef(0.1, 0, 0);
            glPushMatrix();
                GUI::setColor(Cr, Cg, Cb);
                glTranslatef(0.2, -0.1, 1.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.7, 1.0, 0.7);
            glPopMatrix();

            glPushMatrix();
                GUI::setColor(Sr, Sg, Sb);
                glTranslatef(0.1, 0.1, 2.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.5, 0.7, 0.5);
            glPopMatrix();
        glPopMatrix();

        // Right leg
        glPushMatrix();
            glTranslatef(0.9, 0, 0);
            glPushMatrix();
                GUI::setColor(Cr, Cg, Cb);
                glTranslatef(0.2, -0.1, 1.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.7, 1.0, 0.7);
            glPopMatrix();

            glPushMatrix();
                GUI::setColor(Sr, Sg, Sb);
                glTranslatef(0.1, 0.1, 2.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.5, 0.7, 0.5);
            glPopMatrix();
        glPopMatrix();
       
        // Left arm
        glPushMatrix();
            glTranslatef(0.1, 1.5, 0);
            glPushMatrix();
                GUI::setColor(Cr, Cg, Cb);
                glTranslatef(0.2, -0.1, 1.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.7, 1.0, 0.7);
            glPopMatrix();

            glPushMatrix();
                GUI::setColor(Sr, Sg, Sb);
                glTranslatef(0.1, 0.1, 2.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.5, 0.7, 0.5);
            glPopMatrix();
        glPopMatrix();

        // Right arm
        glPushMatrix();
            glTranslatef(0.9, 1.5, 0);
            glPushMatrix();
                GUI::setColor(Cr, Cg, Cb);
                glTranslatef(0.2, -0.1, 1.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.7, 1.0, 0.7);
            glPopMatrix();

            glPushMatrix();
                GUI::setColor(Sr, Sg, Sb);
                glTranslatef(0.1, 0.1, 2.5);
                glRotatef(180, 0, 0, 1);
                glRotatef(90, 1, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.5, 0.7, 0.5);
            glPopMatrix();
        glPopMatrix();

        // Upper body
        glPushMatrix();
            GUI::setColor(Cr, Cg, Cb);
            glTranslatef(-0.5, -0.2, 0.25);
            GUI::drawQuadBox(0, 0, 0, 1.7, 2.5, 1.7);
        glPopMatrix();

        // Head
        glPushMatrix();
            GUI::setColor(Cr, Cg, Cb);
            glTranslatef(-0.3, 2.0, -0.2);
            GUI::drawQuadBox(0, 0, 0, 1.3, 1.3, 1.3);
        glPopMatrix();
    glPopMatrix();
}