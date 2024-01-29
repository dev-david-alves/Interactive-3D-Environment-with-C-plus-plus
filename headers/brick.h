#ifndef brick_h
#define brick_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Brick: public Object {
    public:
        Brick(Vetor3D initialPos);
        
        void draw(vector<vector<vector<int>>> &terrain) override;
};

#endif