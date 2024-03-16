#ifndef object_h
#define object_h

#include <gui.h>
#include <vector>

using namespace std;

class Object {
    private:
        Vetor3D translation = Vetor3D(0, 0, 0);
        Vetor3D rotation = Vetor3D(0, 0, 0);
        Vetor3D scaling = Vetor3D(1, 1, 1);

        bool isSelected = false;
        bool canDrawOrigin = false;
        bool drawShadow = false;
        string type = "object";

    public:
        // Only for the player --------------
        string playerName = "No Player";
        float playerYVel = 0;
        float gravity = 0.1;
        float jumpForce = 1.5;
        bool isMoving = false;
        // End of only for the player -------
        
        Object();

        virtual void draw(bool isShadow = false);
        void drawOrigin(float size = 1.0);

        void setType(string type);
        string getType();

        void setIsSelected(bool select);
        bool getIsSelected();

        void setCanDrawOrigin(bool canDraw);
        bool getCanDrawOrigin();

        void setDrawShadow(bool drawShadow);
        bool getDrawShadow();

        void setTranslation(Vetor3D vector);
        Vetor3D getTranslation();

        void setRotation(Vetor3D vector);
        Vetor3D getRotation();

        void setScaling(Vetor3D vector);
        Vetor3D getScaling();
};

#endif