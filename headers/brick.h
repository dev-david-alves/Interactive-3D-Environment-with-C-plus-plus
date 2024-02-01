#ifndef brick_h
#define brick_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Brick: public Object {
    public:
        vector<vector<vector<int>>> space;

        Brick(Vetor3D initialPos, vector<vector<vector<int>>> &space);
        
        void draw() override;
};

#endif