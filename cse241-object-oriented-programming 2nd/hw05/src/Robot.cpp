#include "Robot.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Robot::Robot()
{
    strength = 0;
    hitpoints = 0;
    name = "";
}

Robot::Robot(int newStrength, int newHit, std::string newName)
{
    strength = newStrength;
    hitpoints = newHit;
    name = newName;
}

int Robot::getStrength() const
{
    return strength;
}

int Robot::getHitpoints() const
{
    return hitpoints;
}

std::string Robot::getName() const
{
    return name;
}

void Robot::setStrength(int newStrength)
{
    strength = newStrength;
}

void Robot::setHitpoints(int newHit)
{
    hitpoints = newHit;
}

std::string Robot::getType() const
{
    return "Robot";
}

int Robot::getDamage() const
{
    int damage = (rand() % strength) + 1;
    std::cout << getName() << " attacks for " << damage << " points!" << std::endl;
    return damage;
}

Robot::~Robot()
{
}

Humanic::Humanic(int newStrength, int newHit, std::string newName)
: Robot(newStrength, newHit, newName)
{
}

std::string Humanic::getType() const
{
    return "Humanic";
}

int Humanic::getDamage() const
{
    int damage = Robot::getDamage();
    if (rand() % 10 == 0)
    {
    std::cout << getName() << " inflicts a tactical nuke attack!" << std::endl;
    damage += 50;
    }
    return damage;
}

OptimusPrime::OptimusPrime(int newStrength, int newHit, std::string newName)
: Humanic(newStrength, newHit, newName)
{
}

int OptimusPrime::getDamage() const
{
    int damage = Humanic::getDamage();
    if (rand() % 100 < 15)
    {
        std::cout << getName()<< " inflicts a strong attack!" << std::endl;
        damage *= 2;
    }
    return damage;
}

RoboCop::RoboCop(int newStrength, int newHit, std::string newName)
: Humanic(newStrength, newHit, newName)
{
}

int RoboCop::getDamage() const
{
return Humanic::getDamage();
}

Roomba::Roomba(int newStrength, int newHit, std::string newName)
: Robot(newStrength, newHit, newName)
{
}

std::string Roomba::getType() const
{
return "Roomba";
}

int Roomba::getDamage() const
{
    int damage = Robot::getDamage();
    std::cout << "Roomba is attacking again!" << std::endl;
    damage += Robot::getDamage();
    return damage;
}

Bulldozer::Bulldozer(int newStrength, int newHit, std::string newName)
: Robot(newStrength, newHit, newName)
{
}

std::string Bulldozer::getType() const
{
return "Bulldozer";
}