#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

class PerlinNoise {
public:
    PerlinNoise();
    PerlinNoise(unsigned int seed);

    double noise(double x, double y, double z) const;

private:
    double fade(double t) const;
    double lerp(double t, double a, double b) const;
    double grad(int hash, double x, double y, double z) const;

    int p[512];
};

#endif // PERLIN_NOISE_H
