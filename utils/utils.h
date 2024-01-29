#ifndef UTILS_H
#define UTILS_H

#include <gui.h>
#include <vector>

class Utils {
    public:
        Utils();
        void DrawQuadPolygon(float r = 1.0, float g = 1.0, float b = 1.0, float a = 1.0);
        void DrawCube(vector<vector<vector<int>>> &space, Vetor3D tra, Vetor3D rot, Vetor3D scl, float colors[6][3]);
        void DrawCube(Vetor3D tra, Vetor3D rot, Vetor3D scl, float colors[6][3]);
};

#endif
