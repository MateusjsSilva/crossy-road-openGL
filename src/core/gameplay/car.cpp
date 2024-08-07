/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#include "car.h"
#include <stdio.h>
#include <iostream>

Car::Car(float startX, float startY, float startZ, float spd, int dir, int rd)
    : x(startX), y(startY), z(startZ), speed(spd), direction(dir), road(rd), type((rand() % 3)) {}

bool Car::update(int w1, int w2, float playerX, float playerZ, int playerGridX, int playerGridZ)
{
    // Atualizar posição do carro com base na direção
    if (direction == 0) {
        x += speed;
        if (x > w2) {
            x = w1;
        }
    }
    else {
        x -= speed;
        if (x < w1) {
            x = w2;
        }
    }

    if (playerGridZ == road) {
        // Calcula a distância euclidiana entre o centro do carro e o centro do jogador
        float dx = x - playerX;
        float dz = z - playerZ;
        float distance = sqrt(dx * dx + dz * dz);

        const float playerRadius = 1.0;
        const float carRadius = 1.5;

        if (distance < (playerRadius + carRadius)) {
            return true;
        }
    }
    return false;
}

void Car::draw()
{
    int type =0;
    int facing = (direction == 0) ? 1 : -1;
    float gameZ = -123;

    switch (type) 
    {
        case 0:
            // Corpo
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(25.0 / 255.0, 222.0 / 255.0, 254.0 / 255.0);
                glTranslatef(x, y - 1.25, z + 120 + gameZ);
                glScaled(1.2, .5, .8);
                glutSolidCube(3);
            glPopMatrix(); 
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            // Corpo superior
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(1, 1, 1);
                glTranslatef(x, y + .25, z + 120 + gameZ);
                glScaled(.7, .4, .5);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            // Janela lateral
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(0, 0, 0);
                glTranslatef(x, y - .15, z + 120 + gameZ);
                glScaled(.5, .25, .51);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            // Janela frente/traseira
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(0, 0, 0);
                glTranslatef(x , y - .15, z + 120 + gameZ);
                glScaled(.71, .25, .4);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            // Espelhos laterais
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(4.0 / 255.0, 187.0 / 255.0, 253.0 / 255.0);
                glTranslatef(x + (.25 * facing), y - .30, z + 120 + gameZ);
                glScaled(.3, .15, 1);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            // Rodas dianteiras
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(0, 0, 0);
                glTranslatef(x  + (1 * facing), y - .80, z + 120 + gameZ);
                glScaled(.3, .3, .815);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(1, 1, 1);
                glTranslatef(x  + (1 * facing), y - .80, z + 120 + gameZ);
                glScaled(.125, .125, .816);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            // Rodas traseiras
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(0, 0, 0);
                glTranslatef(x  - (1 * facing), y - .80, z + 120 + gameZ);
                glScaled(.3, .3, .815);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);

            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glColor3f(1, 1, 1);
                glTranslatef(x  - (1 * facing), y - .80, z + 120 + gameZ);
                glScaled(.125, .125, .816);
                glutSolidCube(3);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);
            break;
    }
}