#ifndef model_h
#define model_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Model: public Object {
    public:
        Model3DS model;
        Model(Vetor3D initialPos, Vetor3D initialScale, const char* src);
        
        void draw(vector<vector<vector<int>>> &terrain);
};

#endif