/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include <iostream>
#include <cmath>

class Velocity;

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   // constructors
   Point()            : x(0.0), y(0.0)  {}
   Point(double x, double y);
   Point(const Point & pt) : x(pt.x), y(pt.y) {}

   // getters
   double getX()       const { return x;              }
   double getY()       const { return y;              }
   bool operator == (const Point & rhs) const
   {
      return x == rhs.x && y == rhs.y;
   }
   bool operator != (const Point & rhs) const
   {
      return x != rhs.x || y != rhs.y;
   }

   // setters
   void setX(double x)       { this->x = x;           }
   void setY(double y)       { this->y = y;           }
   void addX(double dx)      { setX(getX() + dx);     }
   void addY(double dy)      { setY(getY() + dy);     }
   void add(const Velocity & v);
   Point & operator += (const Velocity & v);
   Point & operator = (const Point & rhs)
   {
      x = rhs.x;
      y = rhs.y;
      return *this;
   }

private:
   double x;           // horizontal position
   double y;           // vertical position
};

/*********************************************
 * VELOCITY
 * Movement
 *********************************************/
class Velocity
{
public:
   // constructors
   Velocity()            : dx(0.0), dy(0.0)  {}
   Velocity(double dx, double dy);
   Velocity(const Velocity & v) : dx(v.dx), dy(v.dy) {}

   // getters
   double getDx()       const { return dx;              }
   double getDy()       const { return dy;              }
   bool operator == (const Velocity & rhs) const
   {
      return dx == rhs.dx && dy == rhs.dy;
   }
   bool operator != (const Velocity & rhs) const
   {
      return dx != rhs.dx || dy != rhs.dy;
   }
   double getSpeed() const
   {
      return sqrt(dx * dx + dy * dy);
   }

   // setters
   void setDx(double dx)       { this->dx = dx;   }
   void setDy(double dy)       { this->dy = dy;   }
   void addDx(double dx)       { this->dx += dx;  }
   void addDy(double dy)       { this->dy += dy;  }
   Velocity & operator += (const Velocity & v)
   {
      addDx(v.getDx());
      addDy(v.getDy());
      return *this;
   }
   void add(const Velocity & v)
   {
      *this += v;
   }
   Velocity & operator = (const Velocity & rhs)
   {
      dx = rhs.dx;
      dy = rhs.dy;
      return *this;
   }
   Velocity & operator *= (double mult)
   {
      dx *= mult;
      dy *= mult;
      return *this;
   }
   Velocity operator* (double mult)
   {
      Velocity v(*this);
      v *= mult;
      return v;
   }
   void set(double angle, double speed)
   {
      dx = sin(angle) * speed;
      dy = cos(angle) * speed;
   }
   void turn(double radians = 0.04)
   {
      set(atan2(dx, dy) + radians, getSpeed());      
   }

private:
   double dx;           // horizontal velocity
   double dy;           // vertical velocity
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

inline double max(double x, double y) { return (x > y) ? x : y; }
inline double min(double x, double y) { return (x > y) ? y : x; }

double minimumDistance(const Point & pt1, const Velocity & v1,
                       const Point & pt2, const Velocity & v2);
