#include <headers/tree.h>
#include <vector>
#include <cmath>
#include <typeinfo>

#include <utils/utils.h>

using namespace std;

vector<vector<vector<int>>> createLeaves() {
    int leavesByLayer[3] = {6, 6, 6};
    vector<vector<vector<int>>> leaves(leavesByLayer[1], vector<vector<int>>(leavesByLayer[0], vector<int>(leavesByLayer[2], 0)));

    for(int i = 0; i < leavesByLayer[0]; i++) {
        for(int j = 0; j < leavesByLayer[1]; j++) {
            for(int k = 0; k < leavesByLayer[2]; k++) {
                if(i <= 0 + 2 || i >= leavesByLayer[0] - 2 || j <= -leavesByLayer[1] + 2 || j >= leavesByLayer[1] - 2 || k <= 0 + 2 || k >= leavesByLayer[2] - 2) {
                    if(rand() % 100 > 50) continue;
                }

                if((i >= abs(leavesByLayer[0] - 2) && j >= abs(leavesByLayer[1] - 2) && k >= abs(leavesByLayer[2] - 2))) {
                    if(rand() % 100 > 10) continue;
                }

                leaves[j][i][k] = 1;
            }
        }
    }

    return leaves;
}

Tree::Tree(Vetor3D initialPos, Vetor3D initialRotation, Vetor3D initialScale) {
    this->setTranslation(initialPos);
    this->setRotation(initialRotation);
    this->setScaling(initialScale);
    this->leaves = createLeaves();
};

Utils utilsT = Utils();

void Tree::draw(vector<vector<vector<int>>> &terrain) {
    Object::draw(terrain);

    float r = 0.0;
    float g = 1.0;
    float b = 0.0;

    if(this->getSelected()) {
        r = 1.0;
        g = 0.0;
    }

    float colorsL[6][3] = {
        {r, g, b}, // back
        {r, g, b}, // front
        {r, g, b}, // left
        {r, g, b}, // right
        {r, g, b}, // bottom
        {r, g, b}  // top
    };

    Vetor3D tra = this->getTranslation();
    Vetor3D rot = this->getRotation();
    Vetor3D scl = this->getScaling();

    glPushMatrix();
        glTranslatef(tra.x, tra.y, tra.z);
        glRotatef(rot.x, 1, 0, 0);
        glRotatef(rot.y, 0, 1, 0);
        glRotatef(rot.z, 0, 0, 1);

        this->drawOrigin(3.0);
        
        glScalef(scl.x, scl.y, scl.z);


        glPushMatrix();
            glScalef(0.3, 1, 0.3);

            if(this->getSelected()) {
                GUI::setColor(1.0, 0.0, 0.0); 
            } else {
                GUI::setColor(0.6, 0.2, 0.2); 
            }

            glPushMatrix();
                glRotatef(180, 0, 0, 1);
                glBegin(GL_QUAD_STRIP);
                    for(int j = 0; j <= 360; j+= 5) {
                        glNormal3f(cos(j), 0, sin(j));
                        glVertex3f(cos(j) * 2, 0, sin(j) * 2);
                        glVertex3f(cos(j), -1, sin(j));
                    }
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glBegin(GL_QUAD_STRIP);
                    for(int j = 0; j <= 360; j+= 5) {
                        glNormal3f(cos(j), 0, sin(j));
                        glVertex3f(cos(j), 3, sin(j));
                        glVertex3f(cos(j), 1, sin(j));
                    }
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glBegin(GL_QUAD_STRIP);
                    for(int j = 0; j <= 360; j+= 5) {
                        glNormal3f(cos(j), 0, sin(j));
                        glVertex3f(cos(j) * 2, 4, sin(j) * 2);
                        glVertex3f(cos(j), 3, sin(j));
                    }
                glEnd();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.7, 4, -2.2);
            for (size_t i = 0; i < this->leaves.size(); ++i) {
                for (size_t j = 0; j < this->leaves[i].size(); ++j) {
                    for (size_t k = 0; k < this->leaves[i][j].size(); ++k) {
                        if(this->leaves[i][j][k] != 1) continue;
                        utilsT.DrawCube(this->leaves, Vetor3D(j, i, k), Vetor3D(0, 0, 0), Vetor3D(1, 1, 1), colorsL);
                    }
                }
            }
        glPopMatrix();
    glPopMatrix();
}