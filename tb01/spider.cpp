#include <headers/spider.h>
#include <vector>
#include <cmath>
#include <typeinfo>

using namespace std;

Spider::Spider(Vetor3D initialPos, Vetor3D initialRotation, Vetor3D initialScale) {
    this->setTranslation(initialPos);
    this->setRotation(initialRotation);
    this->setScaling(initialScale);
    this->setType("spider");
};

void Spider::drawPart() {
    glPushMatrix();        
        // Front
        glPushMatrix();
            glTranslatef(-0.2, 0, 1.3);
            glRotatef(3.9, 1, 0, 0);
            glBegin(GL_POLYGON);
                glNormal3f(0, 0, 1);
                glVertex3f(0.2, 0, 0);
                glVertex3f(1.3, 0, 0);
                glVertex3f(1.5, 3, 0);
                glVertex3f(0, 3, 0);
            glEnd();
        glPopMatrix();

        // Back
        glPushMatrix();
            glTranslatef(1.3, 0, 0.2);
            glRotatef(180, 0, 1, 0);
            glRotatef(3.9, 1, 0, 0);
            glBegin(GL_POLYGON);
                glNormal3f(0, 0, 1);
                glVertex3f(0.2, 0, 0);
                glVertex3f(1.3, 0, 0);
                glVertex3f(1.5, 3, 0);
                glVertex3f(0, 3, 0);
            glEnd();
        glPopMatrix();

        // Left
        glPushMatrix();
            glTranslatef(1.1, 0, 1.5);
            glRotatef(90, 0, 1, 0);
            glRotatef(3.9, 1, 0, 0);
            glBegin(GL_POLYGON);
                glNormal3f(0, 0, 1);
                glVertex3f(0.2, 0, 0);
                glVertex3f(1.3, 0, 0);
                glVertex3f(1.5, 3, 0);
                glVertex3f(0, 3, 0);
            glEnd();
        glPopMatrix();

        // Right
        glPushMatrix();
            glRotatef(-90, 0, 1, 0);
            glRotatef(3.9, 1, 0, 0);
            glBegin(GL_POLYGON);
                glNormal3f(0, 0, 1);
                glVertex3f(0.2, 0, 0);
                glVertex3f(1.3, 0, 0);
                glVertex3f(1.5, 3, 0);
                glVertex3f(0, 3, 0);
            glEnd();
        glPopMatrix();

        // Bottom
        glPushMatrix();
            glTranslatef(0, 0, 0.2);
            glRotatef(90, 1, 0, 0);
            glBegin(GL_POLYGON);
                glNormal3f(0, 0, 1);
                glVertex3f(0, 0, 0);
                glVertex3f(1.1, 0, 0);
                glVertex3f(1.1, 1.1, 0);
                glVertex3f(0, 1.1, 0);
            glEnd();
        glPopMatrix();

        // Top
        glPushMatrix();
            glTranslatef(-0.2, 3, 1.5);
            glRotatef(-90, 1, 0, 0);
            glBegin(GL_POLYGON);
                glNormal3f(0, 0, 1);
                glVertex3f(0, 0, 0);
                glVertex3f(1.5, 0, 0);
                glVertex3f(1.5, 1.5, 0);
                glVertex3f(0, 1.5, 0);
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void Spider::draw() {
    float Sr = 0.5;
    float Sg = 0.0;
    float Sb = 0.0;

    if(this->getIsSelected()) {
        Sr = 1.0;
        Sg = 0.0;
        Sb = 0.0;
    }

    Vetor3D tra = this->getTranslation();
    Vetor3D rot = this->getRotation();
    Vetor3D scl = this->getScaling();

    glPushMatrix();
        glTranslatef(tra.x - 0.5, tra.y - 0.5, tra.z - 1);
        glRotatef(rot.x, 1, 0, 0);
        glRotatef(rot.y, 0, 1, 0);
        glRotatef(rot.z, 0, 0, 1);

        glPushMatrix();
            glTranslatef(0.5, 0.5, 1);
            this->drawOrigin(3.0);
        glPopMatrix();
        
        glScalef(scl.x, scl.y, scl.z);

        GUI::setColor(Sr, Sg, Sb);

        // Right legs
        glPushMatrix();
            glPushMatrix();
                glTranslatef(1.7, 1.2, 3.5);
                glRotatef(-130, 0, 0, 1);
                glRotatef(40, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(1.7, 1.2, 3.3);
                glRotatef(-130, 0, 0, 1);
                glRotatef(10, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(1.7, 1.2, 3.1);
                glRotatef(-130, 0, 0, 1);
                glRotatef(-10, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(1.7, 1.2, 2.9);
                glRotatef(-130, 0, 0, 1);
                glRotatef(-40, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();
        glPopMatrix();

        // Left legs
        glPushMatrix();
            glTranslatef(2.3, 0, 7);
            glRotatef(180, 0, 1, 0);
            glPushMatrix();
                glTranslatef(2, 1.2, 3.5);
                glRotatef(-130, 0, 0, 1);
                glRotatef(40, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(2, 1.2, 3.3);
                glRotatef(-130, 0, 0, 1);
                glRotatef(10, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(2, 1.2, 3.1);
                glRotatef(-130, 0, 0, 1);
                glRotatef(-10, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(2, 1.2, 2.9);
                glRotatef(-130, 0, 0, 1);
                glRotatef(-40, 1, 0, 0);
                glScalef(0.3, 0.8, 0.3);

                drawPart();
            glPopMatrix();
        glPopMatrix();

        // Upper body
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0, 0, 0);
                GUI::drawQuadBox(0, 0, 0, 2, 2, 3);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.3, 0.3, 3);
                GUI::drawQuadBox(0, 0, 0, 1.3, 1.3, 1.3);
            glPopMatrix();
        glPopMatrix();

        // Head
        glPushMatrix();
            glTranslatef(0.1, 0.2, 4);
            GUI::drawQuadBox(0, 0, 0, 1.8, 1.8, 1.8);
        glPopMatrix();
    glPopMatrix();
}