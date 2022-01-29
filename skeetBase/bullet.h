/***********************************************************************
 * Header File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#pragma once
#include "point.h"
#include "effect.h"
#include <list>
#include <cassert>
//#include "BulletMove.h"


/*********************************************
 * BULLET
 * Something to shoot something else
 *********************************************/
class Bullet
{
protected:
   
   class BulletMove
   {
   protected:
       Bullet & bullet;
       
   public:
       BulletMove(Bullet & b) : bullet(b) { this->bullet = b;};
       void move(std::list<Effect*> &effects);
       
   private:
       virtual void loseLife() {};
       virtual void addEffects(std::list<Effect*> &effects) {};
       void moveBullet();
   };
   
   class PelletMove : public BulletMove
   {
   public:
       PelletMove(Bullet & b) : BulletMove(b){}
   };

   class MissileMove : public BulletMove
   {
   public:
       MissileMove(Bullet & b) : BulletMove(b){}
   private:
       void addEffects(std::list<Effect*> &effects);
   };

   class BombMove : public BulletMove
   {
   public:
       BombMove(Bullet & b) : BulletMove(b){}
   private:
       void loseLife();
   };

   class ShrapnelMove : public BulletMove
   {
   public:
       ShrapnelMove(Bullet & b) : BulletMove(b){}
   private:
       void loseLife();
       void addEffects(std::list<Effect*> &effects);
   };
   
   
   static Point dimensions;   // size of the screen
   Point pt;                  // position of the bullet
   Velocity v;                // velocity of the bullet
   double radius;             // the size (radius) of the bullet
   bool dead;                 // is this bullet dead?
   int value;                 // how many points does this cost?
   BulletMove * movement;
    
public:
   Bullet(double angle = 0.0, double speed = 30.0, double radius = 5.0, int value = 1);
   
   // setters
   void kill()                   { dead = true; }

   // getters
   bool isDead()           const { return dead;   }
   Point getPosition()     const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   double getRadius()      const { return radius; }
   int getValue()          const { return value;  }

   // special functions
   virtual void death(std::list<Bullet *> & bullets) {}
   virtual void output() = 0;
   virtual void input(bool isUp, bool isDown, bool isB) {}
   void move(std::list<Effect*> &effects) { movement->move(effects); }
   void adjustPosition() { pt.add(v);}
   
   virtual void stepToDeath() {};
   
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
         pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }
   
protected:
   void drawLine(const Point& begin, const Point& end,
                 double red = 1.0, double green = 1.0, double blue = 1.0) const;

   void drawDot(const Point& point, double radius = 2.0,
                double red = 1.0, double green = 1.0, double blue = 1.0) const;
   int    random(int    min, int    max);
   double random(double min, double max);
};

/*********************
 * PELLET
 * Small little bullet
 **********************/
class Pellet : public Bullet
{
public:
   Pellet(double angle, double speed = 15.0) : Bullet(angle, speed, 1.0, 1)
   {
      movement = new PelletMove(*this);
   }
   
   void output();
};

/*********************
 * BOMB
 * Things that go "boom"
 **********************/
class Bomb : public Bullet
{
private:
   int timeToDie;
public:
   Bomb(double angle, double speed = 10.0) : Bullet(angle, speed, 4.0, 4), timeToDie(60)
   {
      movement = new BombMove(*this);
   }
   
   void output();
   void death(std::list<Bullet *> & bullets);
   void stepToDeath();
};

/*********************
 * Shrapnel
 * A piece that broke off of a bomb
 **********************/
class Shrapnel : public Bullet
{
private:
   int timeToDie;
public:
   Shrapnel(const Bomb & bomb)
   {
      movement = new BombMove(*this);
      // how long will this one live?
      timeToDie = random(5, 15);
      
      // The speed and direction is random
      v.set(random(0.0, 6.2), random(10.0, 15.0));
      pt = bomb.getPosition();
      
      radius = 3.0;
   }
   
   void output();  

   void stepToDeath();
};


/*********************
 * MISSILE
 * Guided missiles
 **********************/
class Missile : public Bullet
{
public:
   Missile(double angle, double speed = 10.0) : Bullet(angle, speed, 1.0, 3)
   {
      movement = new BombMove(*this);
   }
   
   void output();
   void input(bool isUp, bool isDown, bool isB)
   {
      if (isUp)
         v.turn(0.04);
      if (isDown)
         v.turn(-0.04);
   }

};






