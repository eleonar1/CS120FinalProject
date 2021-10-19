//
// Created by Ethan on 4/28/2021.
//


#ifndef GRAPHICS1_TRIANGLE_H
#define GRAPHICS1_TRIANGLE_H
#include "shape.h"
#include "rect.h"
#include <iostream>


class Triangle : public Shape {
private:
    dimensions size;
    double leftX;
    double rightX;
    double topY;
    double bottomY;
    double middleX;
public:
    Triangle();
    Triangle(color fill, double x, double y, dimensions size);

    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    void setHeight(double h);
    void setWidth(double w);
    void setSize(dimensions s);
    void setLeftX(double leftX);
    void setRightX(double rightX);
    void setTopY(double topY);
    void setBottomY(double bottomY);

    /* Draw */
    void draw() const override;
    void drawUp2Wing() const;
    void drawUp2Outline() const;
    void drawUp1() const;
    void drawMiddle() const;
    void drawDown1() const;
    void drawDown2() const;
    void drawBeak() const;
};
#endif //GRAPHICS1_TRIANGLE_H
