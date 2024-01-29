#include "utils.h"

Utils::Utils() {}

void Utils::DrawQuadPolygon(float r, float g, float b, float a) {
    glPushMatrix();
        GUI::setColor(r, g, b, a);

        glBegin(GL_POLYGON);
            glNormal3f(0, 0, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);
            glVertex3f(1, 1, 0);
            glVertex3f(0, 1, 0);
        glEnd();
    glPopMatrix();
}

void Utils::DrawCube(Vetor3D tra, Vetor3D rot, Vetor3D scl, float colors[6][3]) {
    int x = tra.x;
    int y = tra.y;
    int z = tra.z;

    glPushMatrix();
        glTranslatef(x - scl.x / 2, y - scl.y / 2, z + scl.z / 2);
        glRotatef(rot.x, 1, 0, 0);
        glRotatef(rot.y, 0, 1, 0);
        glRotatef(rot.z, 0, 0, 1);
        glScalef(scl.x, scl.y, scl.z);

        // Front face
        glPushMatrix();
            this->DrawQuadPolygon(colors[1][0], colors[1][1], colors[1][2], 1.0);
        glPopMatrix();

        // // Back face  
        glPushMatrix();
            glTranslatef(1, 0, -1);
            glRotatef(180, 0, 1, 0);
            this->DrawQuadPolygon(colors[1][0], colors[1][1], colors[1][2], 1.0);
        glPopMatrix();

        // Right face
        glPushMatrix();
            glTranslatef(1, 0, 0);
            glRotatef(90, 0, 1, 0);
            this->DrawQuadPolygon(colors[3][0], colors[3][1], colors[3][2], 1.0);
        glPopMatrix();

        // Left face
        glPushMatrix();
            glTranslatef(0, 0, -1);
            glRotatef(-90, 0, 1, 0);
            this->DrawQuadPolygon(colors[2][0], colors[2][1], colors[2][2], 1.0);
        glPopMatrix();

        // Bottom face
            glPushMatrix();
                glTranslatef(0, 0, -1);
                glRotatef(90, 1, 0, 0);
                this->DrawQuadPolygon(colors[4][0], colors[4][1], colors[4][2], 1.0);
            glPopMatrix();

        // Top face
        glPushMatrix();
            glTranslatef(0, 1, 0);
            glRotatef(-90, 1, 0, 0);
            this->DrawQuadPolygon(colors[5][0], colors[5][1], colors[5][2], 1.0);
        glPopMatrix();
    glPopMatrix();
}

void Utils::DrawCube(vector<vector<vector<int>>> &space, Vetor3D tra, Vetor3D rot, Vetor3D scl, float colors[6][3]) {
    int x = tra.x;
    int y = tra.y;
    int z = tra.z;

    int height = static_cast<int>(space.size());           
    int width = static_cast<int>(space[0].size());   
    int depth = static_cast<int>(space[0][0].size());

    glPushMatrix();
        glTranslatef(x - scl.x / 2, y - scl.y / 2, z + scl.z / 2);
        glRotatef(rot.x, 1, 0, 0);
        glRotatef(rot.y, 0, 1, 0);
        glRotatef(rot.z, 0, 0, 1);
        glScalef(scl.x, scl.y, scl.z);

        // Front face
        if (!(z < depth - 1 && space[y][x][z + 1] != 0)) {
            glPushMatrix();
                this->DrawQuadPolygon(colors[1][0], colors[1][1], colors[1][2], 1.0);
            glPopMatrix();
        }

        // // Back face
        if (!(z > 0 && space[y][x][z - 1] != 0)) {     
            glPushMatrix();
                glTranslatef(1, 0, -1);
                glRotatef(180, 0, 1, 0);
                this->DrawQuadPolygon(colors[1][0], colors[1][1], colors[1][2], 1.0);
            glPopMatrix();
        }

        // Right face
        if (!(x < width - 1 && space[y][x + 1][z] != 0)) {
            glPushMatrix();
                glTranslatef(1, 0, 0);
                glRotatef(90, 0, 1, 0);
                this->DrawQuadPolygon(colors[3][0], colors[3][1], colors[3][2], 1.0);
            glPopMatrix();
        }

        // Left face
        if (!(x > 0 && space[y][x - 1][z] != 0)) {
            glPushMatrix();
                glTranslatef(0, 0, -1);
                glRotatef(-90, 0, 1, 0);
                this->DrawQuadPolygon(colors[2][0], colors[2][1], colors[2][2], 1.0);
            glPopMatrix();
        }

        // Bottom face
        if (!(y > 0 && space[y - 1][x][z] != 0)) {
            glPushMatrix();
                glTranslatef(0, 0, -1);
                glRotatef(90, 1, 0, 0);
                this->DrawQuadPolygon(colors[4][0], colors[4][1], colors[4][2], 1.0);
            glPopMatrix();
        }

        // Top face
        if (!(y < height - 1 && space[y + 1][x][z] != 0)) {
            glPushMatrix();
                glTranslatef(0, 1, 0);
                glRotatef(-90, 1, 0, 0);
                this->DrawQuadPolygon(colors[5][0], colors[5][1], colors[5][2], 1.0);
            glPopMatrix();
        }
    glPopMatrix();
}