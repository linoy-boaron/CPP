//Fractal.h
//

#ifndef EX2_CPP_FRACTAL_H
#define EX2_CPP_FRACTAL_H

#include <vector>

/**
 * class Fractal declaration
 */
class Fractal
{

    /**
     * fields
     */
protected:
    int _dim;
    std::vector<std::vector<char>> _matrix;

public:
    /**
     * constractor of the class *declaration*
     * @param dim
     */
    Fractal(int dim);

    /**
     * getter dim of the object *declaration*
     * @return dim of the object
     */

    int getDim() const;

    /**
     * draw the object - will override by the types -* declaration*
     */
    virtual void drawFractal() = 0;

    /**
     * destructor of the object
     */
    ~Fractal() = default;
};

/**
 * class Sierpinski carpet (heir Fractal)
 */
class Carpet : public Fractal
{

public:
    /**
     *  Sierpinski carpet constractor- declaration
     * @param dim
     */
    Carpet(int dim);

    /**
     * draw the object - declaration
     */
    void drawFractal() override;

private:
    /**
     * draw helper - declaration
     * @param i
     * @param j
     * @param dim
     */
    void _drawHelper(int i, int j, int dim);
};

/**
 * class Sierpinski Triangle
 */
class SierpinskiTriangle : public Fractal
{

public:
    /**
     * Sierpinski Triangle constractor- declaration
     * @param dim
     */
    SierpinskiTriangle(int dim);

    /**
     * draw the object - declaration
     */
    void drawFractal() override;

private:
    /**
     * draw helper - declaration
     * @param i
     * @param j
     * @param dim
     */
    void _drawHelper();

};

/**
 * class Vicsek fractal
 */
class Vicsek : public Fractal
{

public:
    /**
     * Vicsek constractor- declaration
     * @param dim
     */
    Vicsek(int dim);

    /**
     * draw the object - declaration
     */
    void drawFractal() override;

private:
    /**
     * draw helper - declaration
     * @param i
     * @param j
     * @param dim
     */
    void _drawHelper(int i, int j, int dim);
};


#endif //EX2_CPP_FRACTAL_H
