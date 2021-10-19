#include "graphics.h"
#include "rect.h"
#include <iostream>
#include "math.h"
using namespace std;

/********************* Dimensions Struct ********************/

dimensions::dimensions() : width(0), height(0) {}

dimensions::dimensions(double w, double h) : width(w), height(h) {}

ostream& operator << (ostream& outs, const dimensions &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}


Rect::Rect() : Shape(), size({0, 0}) {
}

Rect::Rect(dimensions size) : Shape() {
    setSize(size);
}

Rect::Rect(color fill) : Shape(fill), size({0, 0}) {
}

Rect::Rect(point2D center) : Shape(center), size({0, 0}) {
}

Rect::Rect(color fill, point2D center) : Shape(fill, center), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha) : Shape(red, green, blue, alpha), size({0, 0}) {
}

Rect::Rect(double x, double y) : Shape(x, y), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y) : Shape(red, green, blue, alpha, x, y), size({0, 0}) {
}

Rect::Rect(color fill, double x, double y) : Shape(fill, x, y), size({0, 0}) {
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center) : Shape(red, green, blue, alpha, center), size({0, 0}) {
}

Rect::Rect(color fill, dimensions size) : Shape(fill) {
    setSize(size);
}

Rect::Rect(point2D center, dimensions size) : Shape(center) {
    setSize(size);
}

Rect::Rect(color fill, point2D center, dimensions size) : Shape(fill, center) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, dimensions size) : Shape(red, green, blue, alpha) {
    setSize(size);
}

Rect::Rect(double x, double y, dimensions size) : Shape(x, y) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, double x, double y, dimensions size) : Shape(red, green, blue, alpha, x, y) {
    setSize(size);
}

Rect::Rect(color fill, double x, double y, dimensions size) : Shape(fill, x, y) {
    setSize(size);
}

Rect::Rect(double red, double green, double blue, double alpha, point2D center, dimensions size) : Shape(red, green, blue, alpha, center) {
    setSize(size);
}

dimensions Rect::getSize() const {
    return size;
}

double Rect::getWidth() const {
    return size.width;
}

double Rect::getHeight() const {
    return size.height;
}

double Rect::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Rect::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Rect::getTopY() const {
    return center.y - (size.height / 2.0);
}

double Rect::getBottomY() const {
    return center.y + (size.height / 2.0);
}

void Rect::setSize(dimensions size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Rect::setSize(double width, double height) {
    setSize({width, height});
}

void Rect::setWidth(double width) {
    setSize({width, size.height});
}

void Rect::setHeight(double height) {
    setSize({size.width, height});
}

void Rect::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Rect::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Rect::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}


bool Rect::isOverlapping(const Rect &r) const {
    if((r.getLeftX() > this->getLeftX() && r.getLeftX() < this->getRightX()) || (r.getRightX() < this->getRightX() && r.getRightX() > this->getLeftX())) {
        if((r.getTopY() > this->getTopY() && r.getTopY() < this->getBottomY()) || (r.getBottomY() < this->getBottomY() && r.getBottomY() > this->getTopY())){
            return true;
        }
    }
    return false; // placeholder value for compilation
}

bool Rect::isOverlapping(const Circle &c) const {
    //Circle center point is above and to the left of the rectangle
    if(c.getCenterX() < getLeftX() && c.getCenterY() < getTopY()){
        if(sqrt(pow(c.getCenterX()-getLeftX(),2) + pow(c.getCenterY()-getTopY(),2)) <= c.getRadius()){
            return true;
        }
    }
    //Circle center point is above the rectangle, but between its left and right sides
    else if(c.getCenterX() > getLeftX() && c.getCenterX() < getRightX() && c.getCenterY() < getTopY()){
        if(c.getCenterY() + c.getRadius() >= getTopY()){
            return true;
        }
    }
    //Circle center point is above and to the right of the rectangle
    else if(c.getCenterX() > getRightX() && c.getCenterY() < getTopY() ){
        if(sqrt((pow(c.getCenterX()-getRightX(),2)) + (pow(c.getCenterY()-getTopY(),2))) <= c.getRadius()){
            return true;
        }
    }
    //Circle center point is below the top of the rectangle, and to the left of the rectangle
    else if(c.getCenterX() < getLeftX() && c.getCenterY() >= getTopY() && c.getCenterY() < getBottomY()){
        if(c.getCenterX() + c.getRadius() >= getLeftX()){
            return true;
        }
    }
    //Circle center point is below and to the left of the rectangle
    else if(c.getCenterX() < getLeftX() && c.getCenterY() > getBottomY()){
        if(sqrt(pow(c.getCenterX()-getLeftX(),2) + pow(c.getCenterY()-getBottomY(),2)) <= c.getRadius()){
            return true;
        }
    }
    //Circle center point is below the rectangle but between its left and right sides
    else if(c.getCenterX() > getLeftX() && c.getCenterX() < getRightX() && c.getCenterY() > getBottomY()){
        if(c.getCenterY() - c.getRadius() <= getBottomY()){
            return true;
        }
    }
    //Circle center point is below and to the right of the rectangle
    else if(c.getCenterX() > getRightX() && c.getCenterY() > getBottomY()){
        if(sqrt((pow(c.getCenterX()-getRightX(),2)) + (pow(c.getCenterY()-getBottomY(),2))) <= c.getRadius()){
            return true;
        }
    }
    return false;
}

// Implement this method
void Rect::draw() const {
    // Don't forget to set the color to the fill field
    // Set the color to draw
// Note: you can change this at any time during the drawing process
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
// glVertex2i takes a 2-D (x, y) coordinate
    glVertex2i(this->getLeftX(), this->getTopY());
    glVertex2i(this->getLeftX(), this->getBottomY());
    glVertex2i(this->getRightX(), this->getBottomY());
    glVertex2i(this->getRightX(), this->getTopY());
    glEnd();
}