#ifndef brick_h
#define brick_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Brick: public Object {
    public:
        vector<vector<vector<int>>> space;

        Brick(Vetor3D initialPos = Vetor3D(0, 0, 0), Vetor3D initialRotation = Vetor3D(0, 0, 0), Vetor3D initialScale = Vetor3D(1, 1, 1));
        
        void draw(bool isShadow = false) override;
        void draw(vector<vector<vector<int>>> &space);
};

#endif