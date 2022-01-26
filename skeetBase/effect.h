/***********************************************************************
 * Header File:
 *    Fragment : Pieces that fly off a dead bird
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Pieces that fly off a dead bird
 ************************************************************************/

#pragma once
#include "point.h"

/**********************
 * Effect: stuff that is not interactive
 **********************/
class Effect
{
protected:
    Point pt;      // location of the effect
    double age;    // 1.0 = new, 0.0 = dead
public:
    // create a fragment based on the velocity and position of the bullet
    Effect(const Point & pt) : pt(pt), age(0.5) {}
    
    // draw it
    virtual void render() const = 0;
    
    // move it forward with regards to inertia. Let it age
    virtual void fly() = 0;
    
    // it is dead when age goes to 0.0
    bool isDead() const { return age <= 0.0; }
};

/**********************
 * FRAGMENT
 * Pieces that fly off a dead bird
 **********************/
class Fragment : public Effect
{
private:
   Velocity v;    // direction the fragment is flying
   double size;   // size of the fragment
public:
    // create a fragment based on the velocity and position of the bullet
    Fragment(const Point & pt, const Velocity & v);
    
    // draw it
    void render() const;
    
    // move it forward with regards to inertia. Let it age
    void fly();
};

/**********************
 * STREEK
 * Stuff that trails off the back of shrapnel
 **********************/
class Streek : public Effect
{
private:
   Point ptEnd;
public:
    // create a fragment based on the velocity and position of the bullet
    Streek(const Point & pt, Velocity v);
    
    // draw it
    void render() const;
    
    // move it forward with regards to inertia. Let it age
    void fly();
};

/**********************
 * EXHAUST
 * Stuff that comes out the back of a missile when in flight
 **********************/
class Exhaust : public Effect
{
private:
   Point ptEnd;
public:
    // create a fragment based on the velocity and position of the bullet
    Exhaust(const Point & pt, Velocity v);
    
    // draw it
    void render() const;
    
    // move it forward with regards to inertia. Let it age
    void fly();
};
