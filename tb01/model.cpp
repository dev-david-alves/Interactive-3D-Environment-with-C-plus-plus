#include <headers/model.h>
#include <vector>
#include <cmath>
#include <typeinfo>

using namespace std;

Model::Model(Vetor3D initialPos, Vetor3D initialScale, const char* src) {
    this->setTranslation(initialPos);
    this->setScaling(initialScale);
    this->model.LoadModel(src);
};

void Model::draw(vector<vector<vector<int>>> &terrain) {
    Object::draw(terrain);

    int lastOne = 0;
    int height = static_cast<int>(terrain.size());   

    for(int i = 0; i < height; i++) {
        if(terrain[i][this->getTranslation().x][this->getTranslation().z] != 1) break;

        lastOne = i;
    }

    float x = this->getTranslation().x;
    float z = this->getTranslation().z;

    this->setTranslation(Vetor3D(x, lastOne, z));

    Vetor3D scale = this->getScaling();
    
    glPushMatrix();
        GUI::draw3ds(this->model, x - scale.x / 2, lastOne + scale.y / 2, z - scale.z / 2, 0, 0, 0, scale.x, scale.y, scale.z);
    glPopMatrix();
}