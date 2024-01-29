#ifndef tree_h
#define tree_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Tree: public Object {
    public:
        Tree(Vetor3D initialPos = Vetor3D(0, 0, 0), Vetor3D initialRotation = Vetor3D(0, 0, 0), Vetor3D initialScale = Vetor3D(1, 1, 1));

        void draw(vector<vector<vector<int>>> &terrain) override;
        vector<vector<vector<int>>> leaves;
};

#endif