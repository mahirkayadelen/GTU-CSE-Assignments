#ifndef ROBOT_H
#define ROBOT_H

#include <string>

class Robot
{
public:
    Robot();
    Robot(int newStrength, int newHit, std::string name);
    int getStrength() const;
    int getHitpoints() const;
    std::string getName() const;
    void setStrength(int newStrength);
    void setHitpoints(int newHit);
    virtual std::string getType() const;
    virtual int getDamage() const;

    virtual ~Robot();
protected:
    int strength;
    int hitpoints;
    std::string name;
};

class Humanic : public Robot
{
public:
    Humanic(int newStrength, int newHit, std::string name);
    std::string getType() const override;
    int getDamage() const override;
};

class OptimusPrime : public Humanic
{
public:
    OptimusPrime(int newStrength, int newHit, std::string name);
    int getDamage() const override;
};

class RoboCop : public Humanic
{
public:
    RoboCop(int newStrength, int newHit, std::string name);
    int getDamage() const override;
};

class Roomba : public Robot
{
public:
    Roomba(int newStrength, int newHit, std::string name);
    std::string getType() const override;
    int getDamage() const override;
};

class Bulldozer : public Robot
{
public:
    Bulldozer(int newStrength, int newHit, std::string name);
    std::string getType() const override;
};

#endif