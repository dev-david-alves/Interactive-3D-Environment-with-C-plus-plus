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
        string type = "object";

    public:
        Object();

        virtual void draw(vector<vector<vector<int>>> &terrain);
        void drawOrigin(float size = 1.0);

        void setType(string type);
        string getType();

        void setIsSelected(bool select);
        bool getIsSelected();

        void setCanDrawOrigin(bool canDraw);
        bool getCanDrawOrigin();

        void setTranslation(Vetor3D vector);
        Vetor3D getTranslation();

        void setRotation(Vetor3D vector);
        Vetor3D getRotation();

        void setScaling(Vetor3D vector);
        Vetor3D getScaling();
};

#endif