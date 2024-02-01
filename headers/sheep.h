#ifndef sheep_h
#define sheep_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Sheep: public Object {
    public:
        Sheep(Vetor3D initialPos = Vetor3D(0, 0, 0), Vetor3D initialRotation = Vetor3D(0, 0, 0), Vetor3D initialScale = Vetor3D(1, 1, 1));

        void draw() override;
};

#endif