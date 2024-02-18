#ifndef character_h
#define character_h

#include <gui.h>
#include "object.h"
#include <vector>

using namespace std;

class Character: public Object {
    public:
        int memberAngle = 0;
        int maxMemberAngle = 25;
        int subTrator = 2;
        Character(Vetor3D initialPos = Vetor3D(0, 0, 0), Vetor3D initialRotation = Vetor3D(0, 0, 0), Vetor3D initialScale = Vetor3D(1, 1, 1));

        void draw() override;
};

#endif