#include "Robot.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    srand(time(0)); // Seed random number generator

    const int grid_size = 10;
    std::vector<std::vector<Robot*>> grid(grid_size, std::vector<Robot*>(grid_size, nullptr));

    std::vector<Robot*> robots;
    const int initial_count_of_each_robot_type = 5;

    // Create robots and add them to the vector
    for (int i = 0; i < initial_count_of_each_robot_type; i++)
    {
        robots.push_back(new OptimusPrime(100, 100, "optimusprime_" + std::to_string(i)));
        robots.push_back(new RoboCop(30, 40, "robocop_" + std::to_string(i)));
        robots.push_back(new Roomba(3, 10, "roomba_" + std::to_string(i)));
        robots.push_back(new Bulldozer(50, 200, "bulldozer_" + std::to_string(i)));
    }

    // Assign initial positions for robots in the grid
    for (Robot* robot : robots)
    {
        int i, j;
        do
        {
            i = rand() % grid_size;
            j = rand() % grid_size;
        } while (grid[i][j] != nullptr);

        grid[i][j] = robot;
    }

    // Simulation loop
    while (robots.size() > 1)
    {
        auto it = robots.begin();
        while (it != robots.end())
        {
            Robot* robot = *it;

            // Find the position of the robot in the grid
            int i, j;
            bool robotFound = false;
            for (i = 0; i < grid_size; i++)
            {
                for (j = 0; j < grid_size; j++)
                {
                    if (grid[i][j] == robot)
                    {
                        robotFound = true;
                        break;
                    }
                }
                if (robotFound)
                    break;
            }

            // Robot tries to move
            int direction = rand() % 4; // Randomly choose a direction (0: up, 1: down, 2: left, 3: right)
            int new_i = i;
            int new_j = j;

            switch (direction)
            {
                case 0: // Up
                    new_i = (new_i - 1 + grid_size) % grid_size;
                    break;
                case 1: // Down
                    new_i = (new_i + 1) % grid_size;
                    break;
                case 2: // Left
                    new_j = (new_j - 1 + grid_size) % grid_size;
                    break;
                case 3: // Right
                    new_j = (new_j + 1) % grid_size;
                    break;
            }

            // Check if the new cell is occupied by another robot
            if (grid[new_i][new_j] != nullptr)
            {
                // Robot fights with another robot in the same cell
                Robot* otherRobot = grid[new_i][new_j];
                int damage1 = robot->getDamage();
                int damage2 = otherRobot->getDamage();

                while (robot->getHitpoints() > 0 && otherRobot->getHitpoints() > 0)
                {
                    std::cout << robot->getName() << " (" << robot->getHitpoints() << ") hits "
                                << otherRobot->getName() << " (" << otherRobot->getHitpoints() << ") with "
                            << damage1 << std::endl;

                    otherRobot->setHitpoints(otherRobot->getHitpoints() - damage1);
                    if(otherRobot->getHitpoints() > 0){ // // if robot is dead there is no need to show its health
                        std::cout << "The new hitpoints of " << otherRobot->getName() << " is "
                                << otherRobot->getHitpoints() << std::endl;
                    }
                    if (otherRobot->getHitpoints() > 0)
                    {
                        std::cout << otherRobot->getName() << " (" << otherRobot->getHitpoints() << ") hits "
                                    << robot->getName() << " (" << robot->getHitpoints() << ") with "
                                    << damage2 << std::endl;

                        robot->setHitpoints(robot->getHitpoints() - damage2);
                        if(robot->getHitpoints() > 0){ // if robot is dead there is no need to show its health
                            std::cout << "The new hitpoints of " << robot->getName() << " is "
                                    << robot->getHitpoints() << std::endl;
                        }
                    }
                }

                if (otherRobot->getHitpoints() <= 0)
                {
                    std::cout << otherRobot->getName() << " is dead!\n" << std::endl;
                    grid[new_i][new_j] = nullptr;
                    robots.erase(std::remove(robots.begin(), robots.end(), otherRobot), robots.end());
                    delete otherRobot;
                    break; // Exit the loop after erasing the opponent robot(FOR AVOID SEGMENTATION FAULT)
                }

                if (robot->getHitpoints() <= 0)
                {
                        std::cout << robot->getName() << " is dead!\n" << std::endl;
                        grid[i][j] = nullptr;
                        it = robots.erase(it);
                        delete robot;
                        continue;
                }
            }

            if (grid[new_i][new_j] == nullptr)
            {
                // Update the robot's position in the grid
                grid[i][j] = nullptr;
                grid[new_i][new_j] = robot;
            }
            else if (grid[new_i][new_j] != nullptr && grid[new_i][new_j] != robot)
            {
                // Cell is occupied by another robot, try to find an available adjacent cell
                bool moved = false;

                // Check up
                int up_i = (new_i - 1 + grid_size) % grid_size;
                if (grid[up_i][new_j] == nullptr)
                {
                    grid[i][j] = nullptr;
                    grid[up_i][new_j] = robot;
                    new_i = up_i;
                    moved = true;
                }

                // Check down
                if (!moved)
                {
                    int down_i = (new_i + 1) % grid_size;
                    if (grid[down_i][new_j] == nullptr)
                    {
                        grid[i][j] = nullptr;
                        grid[down_i][new_j] = robot;
                        new_i = down_i;
                        moved = true;
                    }
                }

                // Check left
                if (!moved)
                {
                    int left_j = (new_j - 1 + grid_size) % grid_size;
                    if (grid[new_i][left_j] == nullptr)
                    {
                        grid[i][j] = nullptr;
                        grid[new_i][left_j] = robot;
                        new_j = left_j;
                        moved = true;
                    }
                }

                // Check right
                if (!moved)
                {
                    int right_j = (new_j + 1) % grid_size;
                    if (grid[new_i][right_j] == nullptr)
                    {
                        grid[i][j] = nullptr;
                        grid[new_i][right_j] = robot;
                        new_j = right_j;
                        moved = true;
                    }
                }

                if (moved)
                {
                }
                else
                {
                    // All adjacent cells are occupied, and the robot cannot move
                    std::cout << robot->getName() << " is surrounded and cannot move!" << std::endl;
                }
            }

            ++it;
        }
    }

    // Display the winner
    if (!robots.empty())
    {
        Robot* winner = robots[0];
        std::cout << "The winner is " << winner->getName() << " with " << winner->getHitpoints() << " hitpoints remaining!" << std::endl;
    }

    // Clean up the memory
    for (Robot* robot : robots)
    {
        delete robot;
    }

    return 0;
}
