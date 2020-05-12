#include <iostream>
#include "Fractal.h"
#include "cmath"

/**
 * classes implemention
 */

/**
 * constractor of FRACTAL implemention
 * @param dim
 */
Fractal::Fractal(int dim) : _dim(dim)
{};

/**
     * getter dim of the object *implemention*
     * @return dim of the object
     */
int Fractal::getDim() const
{
    return _dim;
};

/**
     *  Sierpinski carpet constractor- implement
     * @param dim
     */
Carpet::Carpet(int dim) : Fractal(dim)
{
    for (int i = 0; i < pow(3, dim); i++)
    {
        std::vector<char> v;
        v.reserve(pow(3, dim));
        for (int j = 0; j < pow(3, dim); j++)
        {
            v.push_back(' ');
        }

        _matrix.push_back(v);
    }

};

/**
 *   helper drawer of  the object
 * @param i
 * @param j
 * @param dim
 */
void Carpet::_drawHelper(int i, int j, int dim)
{
    if (dim > 0)
    {
        dim -= 1;
        int X1 = i;
        int X2 = i + 1 * pow(3, dim);
        int X3 = i + 2 * pow(3, dim);
        int Y1 = j;
        int Y2 = j + 1 * pow(3, dim);
        int Y3 = j + 2 * pow(3, dim);

        _drawHelper(X1, Y1, dim);
        _drawHelper(X2, Y1, dim);
        _drawHelper(X3, Y1, dim);

        _drawHelper(X1, Y2, dim);
        _drawHelper(X3, Y2, dim);

        _drawHelper(X1, Y3, dim);
        _drawHelper(X2, Y3, dim);
        _drawHelper(X3, Y3, dim);
    }
    else
    {
        _matrix[i - 1][j - 1] = '#';
    }
}

/**
 * draw the  carpet fractal object implemention
 */
void Carpet::drawFractal()
{
    _drawHelper(1, 1, _dim);
    for (int i = 0; i < pow(3, _dim); ++i)
    {
        for (int j = 0; j < pow(3, _dim); ++j)
        {
            std::cout << _matrix[i][j];
        }
        std::cout << "\n";
    }
}

/**
 *  helper drawer of  the  Vicsek object
 * @param i
 * @param j
 * @param dim
 */
void Vicsek::_drawHelper(int i, int j, int dim)
{
    if (dim > 0)
    {
        dim -= 1;
        int X1 = i;
        int X2 = i + 1 * pow(3, dim);
        int X3 = i + 2 * pow(3, dim);
        int Y1 = j;
        int Y2 = j + 1 * pow(3, dim);
        int Y3 = j + 2 * pow(3, dim);

        _drawHelper(X1, Y1, dim);
        _drawHelper(X3, Y1, dim);
        _drawHelper(X2, Y2, dim);
        _drawHelper(X1, Y3, dim);
        _drawHelper(X3, Y3, dim);
    }
    else
    {
        _matrix[i - 1][j - 1] = '#';
    }
}

/**
 * Vicsek constractor- implemention
 * @param dim
 */
Vicsek::Vicsek(int dim) : Fractal(dim)
{
    for (int i = 0; i < pow(3, dim); i++)
    {
        std::vector<char> v;
        v.reserve(pow(3, dim));
        for (int j = 0; j < pow(3, dim); j++)
        {
            v.push_back(' ');
        }

        _matrix.push_back(v);
    }

};

/**
 * draw the  vicsek fractal object implemention
 */
void Vicsek::drawFractal()
{
    _drawHelper(1, 1, _dim);
    for (int i = 0; i < pow(3, _dim); ++i)
    {
        for (int j = 0; j < pow(3, _dim); ++j)
        {
            std::cout << _matrix[i][j];
        }
        std::cout << "\n";
    }
}

/**
 * Sierpinski Triangle constractor- implemention
 * @param dim
 */
SierpinskiTriangle::SierpinskiTriangle(int dim) : Fractal(dim)
{

    for (int i = 0; i < pow(2, dim); i++)
    {
        std::vector<char> v;
        v.reserve(pow(2, dim));
        for (int j = 0; j < pow(2, dim); j++)
        {
            v.push_back(' ');
        }

        _matrix.push_back(v);
    }

};


void SierpinskiTriangle::_drawHelper()
{
    for (int y = 0; y <= pow(2, _dim) - 1; y++)
    {
        for (int x = 0; x + y < pow(2, _dim); x++)
        {
            if (!(x & y))
            {
                _matrix[x][y] = '#';
            }
        }
    }
}

/**
 * draw the Sierpinski Triangle object -implemention
 */
void SierpinskiTriangle::drawFractal()
{
    _drawHelper();
    for (int i = 0; i < pow(2, _dim); ++i)
    {
        for (int j = 0; j < pow(2, _dim); ++j)
        {
            std::cout << _matrix[i][j];
        }
        std::cout << "\n";
    }
}
