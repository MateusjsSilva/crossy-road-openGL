/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef car_hpp
    #define car_hpp

    extern int playerRelativeToGridX;
    extern int playerRelativeToGridZ;
    extern bool playerIsDead;

    class car 
    {
        public:
            car(float inputX, float inputZ, float inputSpeed, int inputDirection, int inputLane);
            void update();
            float x = -60.0, y = -5.0, z;
            int type, direction, lane;

        private:
            float speed;
    };

    car::car(float inputX, float inputZ, float inputSpeed, int inputDirection, int inputLane) 
    {
        x = inputX;
        z = inputZ;
        speed = inputSpeed;
        direction = inputDirection;
        lane = inputLane;
        type = (rand() % ((3 - 0) + 3)) + 0;
    }

    void car::update() 
    {
        if (direction == 0) {
            x += speed;
            if (x > 60) {
                x = -60.0;
                type = (rand() % ((3 - 0) + 3)) + 0;
            }
        }
        else {
            x -= speed;
            if (x < -60) {
                x = 60;
                type = (rand() % ((3 - 0) + 3)) + 0;
            }
        }

        if (playerRelativeToGridX * 4 > x + 28 && playerRelativeToGridX * 4 < x + 32 && lane == playerRelativeToGridZ) {
            playerIsDead = true;
        }
    }

#endif /* car_hpp */