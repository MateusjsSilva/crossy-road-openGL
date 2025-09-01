/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#include "player.h"

Player::Player() : level(1), posX(0.0f), posY(1.0f), posZ(-10.0f), speed(5.0f), playerDirection(1), canJump(true), playerGridX(8), playerGridZ(2) {}

void Player::moveUp(const std::vector<std::vector<char>>& levelData)
{
    if (canJump)
    {
        if (levelData[playerGridZ + 1][playerGridX] != '1')
        {
            isJumping = true;
            posZ -= speed;
            playerDirection = 1;
            jumpStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
            playerGridZ += 1;
            checkCollision(levelData);
        }
    }
}

void Player::moveDown(const std::vector<std::vector<char>>& levelData)
{
    if (canJump)
    {
        if (levelData[playerGridZ - 1][playerGridX] != '1')
        {
            isJumping = true;
            posZ += speed;
            playerDirection = 3;
            playerGridZ -= 1;
            jumpStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
            checkCollision(levelData);
        }
    }
}

void Player::moveLeft(const std::vector<std::vector<char>>& levelData)
{
    if (canJump)
    {
        if (levelData[playerGridZ][playerGridX - 1] != '1')
        {
            isJumping = true;
            posX -= speed;
            playerDirection = 2;
            playerGridX -= 1;
            jumpStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
            checkCollision(levelData);
        }
    }
}

void Player::moveRight(const std::vector<std::vector<char>>& levelData)
{
    if (canJump)
    {
        if (levelData[playerGridZ][playerGridX + 1] != '1')
        {
            isJumping = true;
            posX += speed;
            playerDirection = 0;
            playerGridX += 1;
            jumpStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
            checkCollision(levelData);
        }
    }
}

void Player::setPosition(float x, float y, float z)
{
    posX = x;
    posY = y;
    posZ = z;
}

void Player::drawOrientationLines(float length)
{
    glBegin(GL_LINES);
        // X axis
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(posX, posY, posZ);
        glVertex3f(posX + length, posY, posZ);
        // Y axis
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(posX, posY, posZ);
        glVertex3f(posX, posY + length, posZ);
        // Z axis
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(posX, posY, posZ);
        glVertex3f(posX, posY, posZ + length);
    glEnd();
}

void Player::checkCollision(const std::vector<std::vector<char>>& levelData)
{
    switch (levelData[playerGridZ][playerGridX])
    {
        case '3':
            death();
            break;
        case '5':
            hasWon = true;
            victory();
            break;
        default:
            break;
    }
}

void Player::death() 
{
    posX = 0;
    posY = 1;
    posZ = -10;

    playerGridX = 8;
    playerGridZ = 2;
    playerDirection = 1;
    canJump = true;
    isDead = false;
    level = 1;

    timerD = 0;

    cout << "You died!" << endl; 
}

void Player::victory() 
{
    posX = 0;
    posY = 1;
    posZ = -10;

    playerGridX = 8;
    playerGridZ = 2;
    playerDirection = 1;
    canJump = true;
    isDead = false;

    timerW = 0;
    timerD = 0;
    level++;

    cout << "You won!" << endl;
}