#ifndef chicken_h
#define chicken_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Chicken: public Object {
    public:
        Chicken(Vetor3D initialPos = Vetor3D(0, 0, 0), Vetor3D initialRotation = Vetor3D(0, 0, 0), Vetor3D initialScale = Vetor3D(1, 1, 1));

        void draw(bool isShadow = false) override;
};

#endif