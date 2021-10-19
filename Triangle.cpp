//
// Created by Ethan on 4/28/2021.
//
#include "Triangle.h"
#include "graphics.h"
#include <iostream>
using namespace std;

/**
 * Triangle Class to be used to draw the FlappyBird's wing
 * Draw function creates a wing shaped triangle using GL_TRIANGLES
 */

//Constructors
Triangle::Triangle() : Shape(), size({0, 0}) {
}

Triangle::Triangle(color fill, double x, double y, dimensions size) : Shape(fill, x, y) {
    setSize(size);
}

//Getters

double Triangle::getLeftX() const {
    return leftX;
}

double Triangle::getRightX() const {
    return rightX;
}

double Triangle::getTopY() const {
    return topY;
}

double Triangle::getBottomY() const {
    return bottomY;
}

//Setters

void Triangle::setLeftX(double leftX) {
    this->leftX=leftX;
}
void Triangle::setRightX(double rightX) {
    this->rightX=rightX;
}
void Triangle::setTopY(double topY) {
    this->topY=topY;
}
void Triangle::setBottomY(double bottomY) {
    this->bottomY=bottomY;
}
void Triangle::setSize(dimensions s){
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}
void Triangle::setWidth(double width){
    setSize({width, size.height});
}

void Triangle::setHeight(double height) {
    setSize({size.width, height});
}

//regular draw function for all triangles
void Triangle::draw() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((getLeftX() - ((getRightX()-getLeftX())/2)-2), getBottomY()+1);
    glVertex2f( this->getRightX(), this->getTopY());
    glEnd();
}

//5 draw functions for the 5 different possitions of the wing
//special draw method for drawing outline of wing in up position
void Triangle::drawUp2Outline() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((getLeftX() - ((getRightX()-getLeftX())/2)-5), getBottomY()-33);
    glVertex2f( this->getRightX(), this->getTopY());
    glEnd();
}
//draw wing pointing up
void Triangle::drawUp2Wing() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((getLeftX() - ((getRightX()-getLeftX())/2)-12), getBottomY()-29);
    glVertex2f( this->getRightX(), this->getTopY());
    glEnd();
}
//Draw wing between up and middle
void Triangle::drawUp1() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((getLeftX() - ((getRightX()-getLeftX())/2)-6), getBottomY()-9);
    glVertex2f( this->getRightX(), this->getTopY());
    glEnd();
}

//Draws wing in middle of flapping animation
void Triangle::drawMiddle() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((getLeftX() - ((getRightX()-getLeftX())/2)-4), getBottomY()-3);
    glVertex2f( this->getRightX(), this->getTopY());
    glEnd();
}

//Draws wing shape in between middle and all the way down
void Triangle::drawDown1() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((getLeftX() - ((getRightX()-getLeftX())/2)+3), getBottomY()+5);
    glVertex2f( this->getRightX(), this->getTopY());
    glEnd();
}

//Draws wing shape in downward pointing position
void Triangle::drawDown2() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((getLeftX() - ((getRightX()-getLeftX())/2)+12), getBottomY()+7);
    glVertex2f( this->getRightX(), this->getTopY());
    glEnd();
}

//Draw function for the beak. Draws beak shaped triangle
void Triangle::drawBeak() const{
    glBegin(GL_TRIANGLES);
    glColor3f(fill.red, fill.green, fill.blue);
    glVertex2f( this->getLeftX(), this->getTopY());
    glVertex2f((this->getRightX()), (getBottomY()- ((getBottomY()-getTopY())/2)));
    glVertex2f( this->getLeftX(), this->getBottomY());
    glEnd();
}