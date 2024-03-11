#include <headers/chicken.h>
#include <vector>
#include <cmath>
#include <typeinfo>

using namespace std;

Chicken::Chicken(Vetor3D initialPos, Vetor3D initialRotation, Vetor3D initialScale) {
    this->setTranslation(initialPos);
    this->setRotation(initialRotation);
    this->setScaling(initialScale);
    this->setType("chicken");
};

void Chicken::draw(bool isShadow) {
    float Sr = 1.0;
    float Sg = 1.0;
    float Sb = 1.0;

    float Ydr = 0.8;
    float Ydg = 0.8;
    float Ydb = 0.0;

    float Yr = 1.0;
    float Yg = 1.0;
    float Yb = 0.0;

    float Rr = 0.9;
    float Rg = 0.0;
    float Rb = 0.0;

    if(this->getIsSelected()) {
        Sr = 1.0;
        Sg = 0.0;
        Sb = 0.0;

        Ydr = 1.0;
        Ydg = 0.0;
        Ydb = 0.0;

        Yr = 1.0;
        Yg = 0.0;
        Yb = 0.0;

        Rr = 1.0;
        Rg = 0.0;
        Rb = 0.0;
    }

    if(isShadow) {
        Sr = 0.0;
        Sg = 0.0;
        Sb = 0.0;

        Ydr = 0.0;
        Ydg = 0.0;
        Ydb = 0.0;

        Yr = 0.0;
        Yg = 0.0;
        Yb = 0.0;

        Rr = 0.0;
        Rg = 0.0;
        Rb = 0.0;
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

        glTranslatef(-0.9, 0.7, -1.2);

        // Right leg
        glPushMatrix();
            GUI::setColor(Yr, Yg, Yb);
            glPushMatrix();
                glTranslatef(0.3, -1, 1.4);
                glScalef(0.7, 1, 0.7);
                GUI::drawQuadBox(0, 0, 0, 0.3, 1, 0.3);
                glTranslatef(0, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 0.3, 0.3, 0.7);
            glPopMatrix();
        glPopMatrix();

        // Left leg
        glPushMatrix();
            glPushMatrix();
                glTranslatef(1.2, -1, 1.4);
                glScalef(0.7, 1, 0.7);
                GUI::drawQuadBox(0, 0, 0, 0.3, 1, 0.3);
                GUI::drawQuadBox(0, 0, 0, 0.3, 0.3, 0.7);
            glPopMatrix();
        glPopMatrix();

        GUI::setColor(Sr, Sg, Sb);
        // Right arm
        glPushMatrix();
            glPushMatrix();
                glTranslatef(-0.3, 0.2, 0.2);
                GUI::drawQuadBox(0, 0, 0, 0.3, 1.2, 2);
            glPopMatrix();
        glPopMatrix();

        // left arm
        glPushMatrix();
            glPushMatrix();
                glTranslatef(1.7, 0.2, 0.2);
                GUI::drawQuadBox(0, 0, 0, 0.3, 1.2, 2);
            glPopMatrix();
        glPopMatrix();
        

        // Upper body
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 1.7, 1.7, 2.5);
            glPopMatrix();
        glPopMatrix();

        // Head
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0.25, 1.5, 2.2);
                GUI::drawQuadBox(0, 0, 0, 1.2, 1.5, 0.8);
            glPopMatrix();

            GUI::setColor(Ydr, Ydg, Ydb);
            glPushMatrix();
                glTranslatef(0.25, 1.9, 3);
                GUI::drawQuadBox(0, 0, 0, 1.2, 0.5, 0.7);
            glPopMatrix();

            GUI::setColor(Rr, Rg, Rb);
            glPushMatrix();
                glTranslatef(0.6, 1.5, 3);
                GUI::drawQuadBox(0, 0, 0, 0.5, 0.5, 0.3);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}