#ifndef spider_h
#define spider_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Spider: public Object {
    public:
        Spider(Vetor3D initialPos = Vetor3D(0, 0, 0), Vetor3D initialRotation = Vetor3D(0, 0, 0), Vetor3D initialScale = Vetor3D(1, 1, 1));

        void drawPart();
        void draw() override;
};

#endif