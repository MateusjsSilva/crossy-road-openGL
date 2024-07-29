/*
 * -----------------------------------------
 * Computer Graphics
 * Code: frogger + crossy road
 * Authors: Mateus Silva, Jailson Palhares
 * -----------------------------------------
 */

#pragma once

#ifndef map_hpp
	#define map_hpp

    #include "../gameplay/objects/car.hpp"
    
    
    #include <iostream>
    #include <fstream>
    #include <string>

    float gameZ = -120;
    float gameX = 4;

    float playerX = 0;
    float playerY = -5;
    float playerZ = 4;

    int playerRelativeToGridX = 7;
    int playerRelativeToGridZ = 31;

    int playerDirection = 1;

    bool canJump = true;
    int jumpTimer = 0;
    bool isCollisionUp = false, isCollisionDown = false, isCollisionLeft = false, isCollisionRight = false;

    float finalX, finalZ;

    bool playerIsDead = false;
    bool playerHasWon = false;
    float deathTimer = 0;
    float winTimer = 0;

    int score = 0;

    GLuint textureGrass;

    // Fog declarations
    static GLint fogMode;
    bool showFog = true;

    // Declaração antecipada da classe gameMap
    class gameMap;

    // Ponteiro global para a instância de gameMap
    gameMap* currentGameMap = nullptr;

    const int MAP_WIDTH = 10;

    std::vector<vector<char>> listOfRows;
    std::vector<car> vectorOfCars;

    #include "../gameplay/objects/player.hpp"

	class gameMap
	{
		public:
            gameMap() { init(); }

            void init() 
            { 
                currentGameMap = this;
                glutDisplayFunc(drawWrapper);
                glutIdleFunc(drawWrapper);

                initializeMap(25);
            }

		private:
            static void drawWrapper() 
            { 
                currentGameMap -> draw(); 
            }
            
            void draw();
            void renderPlayer();
            void updateMap(int playerPositionZ);
            std::vector<char> generateRow();
            void initializeMap(int initialRows);
			void renderGrass(float x, float z);
			void renderLargeTree(float x, float z);
			void renderRoad(float x, float z);
			void renderWater(float x, float z);
			void renderFlag(float x, float z);
            void ludersCube(float size, float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, GLuint texture);
	};

    void gameMap::draw() 
    {
        updateMap(static_cast<int>(gameZ));

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 50, 40, 0, 0, 0, 0, 1, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (size_t i = 0; i < listOfRows.size(); i++)
        {
            for (size_t j = 0; j < listOfRows[1].size(); j++)
            {
                float x = (static_cast<int>(j) * 4) - 32 + gameX;
                float z = (static_cast<int>(i) * 4) + gameZ;

                switch (listOfRows[i][j])
                {
                    case '0': renderGrass(x, z); break;
                    case '1': renderLargeTree(x, z); break;
                    case '2': renderRoad(x, z); break;
                    case '3': renderWater(x, z); break;
                    case '5': renderFlag(x, z); break;
                }
            }
        }

        renderPlayer(); // rendering the player

        glFlush();
        glutSwapBuffers();
    }


    void gameMap::updateMap(int playerPositionZ) {
        // Número de linhas que queremos manter à frente do jogador
        const int bufferLines = 5;

        // Verifique se precisamos adicionar novas linhas
        while (playerPositionZ + bufferLines >= listOfRows.size()) {
            listOfRows.push_back(generateRow());
        }

        // Opcional: Remova linhas que estão muito atrás do jogador
        if (playerPositionZ > bufferLines) {
            listOfRows.erase(listOfRows.begin());
        }
    }


    // Função para gerar uma linha do mapa
    std::vector<char> gameMap::generateRow() {
        std::vector<char> row(MAP_WIDTH, 0);

        // Vamos garantir que haja pelo menos um caminho claro (célula vazia) em cada linha
        int clearPathIndex = rand() % MAP_WIDTH;
        row[clearPathIndex] = 1;

        // Opcional: Adicione mais lógica para variar a dificuldade
        for (int i = 0; i < MAP_WIDTH; ++i) {
            if (i != clearPathIndex && rand() % 2 == 0) {
                row[i] = 1; // 1 representa uma célula vazia
            }
        }
        return row;
    }

    // Inicialize o mapa com algumas linhas
    void gameMap::initializeMap(int initialRows) {
        for (int i = 0; i < initialRows; ++i) {
            listOfRows.push_back(generateRow());
        }
    }

    void gameMap::renderPlayer()
    {
        int directionSwitcher = 1;

        if (playerDirection == 0 || playerDirection == 3) {

            directionSwitcher = 1;
        }
        else {
            directionSwitcher = -1;
        }

        // Draw player
        glPushMatrix();
        ludersCube(4.0f, 0 - gameX, 0.0f, 0 - gameZ, 2.0f, 2.0f, 2.0f, textureGrass);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0 - gameX + 10, 0, 0 - gameZ);
        glutSolidCube(4);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0 - gameX - 10, 0, 0 - gameZ);

        glBegin(GL_QUADS);

        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float scaleZ = 1.0f;

        //glColor3f(0.0f,1.0f,0.0f);    // Color Blue
        glVertex3f(scaleX, scaleY, -scaleZ);    // Top Right Of The Quad (Top)
        glVertex3f(-scaleX, scaleY, -scaleZ);    // Top Left Of The Quad (Top)
        glVertex3f(-scaleX, scaleY, scaleZ);    // Bottom Left Of The Quad (Top)
        glVertex3f(scaleX, scaleY, scaleZ);    // Bottom Right Of The Quad (Top)

        //glColor3f(scaleX,0.5f,0.0f);    // Color Orange
        glVertex3f(scaleX, -1.0f, scaleZ);    // Top Right Of The Quad (Bottom)
        glVertex3f(-scaleX, -1.0f, scaleZ);    // Top Left Of The Quad (Bottom)
        glVertex3f(-scaleX, -1.0f, -scaleZ);    // Bottom Left Of The Quad (Bottom)
        glVertex3f(scaleX, -1.0f, -scaleZ);    // Bottom Right Of The Quad (Bottom)

        //glColor3f(scaleX,0.0f,0.0f);    // Color Red
        glVertex3f(scaleX, scaleY, scaleZ);    // Top Right Of The Quad (Front)
        glVertex3f(-scaleX, scaleY, scaleZ);    // Top Left Of The Quad (Front)
        glVertex3f(-scaleX, -1.0f, scaleZ);    // Bottom Left Of The Quad (Front)
        glVertex3f(scaleX, -1.0f, scaleZ);    // Bottom Right Of The Quad (Front)

        //glColor3f(scaleX,1.0f,0.0f);    // Color Yellow
        glVertex3f(scaleX, scaleY, -scaleZ);    // Top Right Of The Quad (Back)
        glVertex3f(-scaleX, scaleY, -scaleZ);    // Top Left Of The Quad (Back)
        glVertex3f(-scaleX, -1.0f, -scaleZ);    // Bottom Left Of The Quad (Back)
        glVertex3f(scaleX, -1.0f, -scaleZ);    // Bottom Right Of The Quad (Back)

        //glColor3f(0.0f,0.0f,1.0f);    // Color Blue
        glVertex3f(-scaleX, scaleY, scaleZ);    // Top Right Of The Quad (Left)
        glVertex3f(-scaleX, scaleY, -scaleZ);    // Top Left Of The Quad (Left)
        glVertex3f(-scaleX, -1.0f, -scaleZ);    // Bottom Left Of The Quad (Left)
        glVertex3f(-scaleX, -1.0f, scaleZ);    // Bottom Right Of The Quad (Left)

         glColor3f(1.0f,0.0f,1.0f);    // Color Violet
        glVertex3f(scaleX, scaleY, -scaleZ);    // Top Right Of The Quad (Right)
        glVertex3f(scaleX, scaleY, scaleZ);    // Top Left Of The Quad (Right)
        glVertex3f(scaleX, -1.0f, scaleZ);    // Bottom Left Of The Quad (Right)
        glVertex3f(scaleX, -1.0f, -scaleZ);    // Bottom Right Of The Quad (Right)

        glEnd();
        glPopMatrix();

        // Body lower
        glPushMatrix();
        glColor3f(256.0 / 256.0, 256.0 / 256.0, 256.0 / 256.0);
        glTranslatef(playerX, playerY, playerZ);
        glRotated(90 * playerDirection, 0, 1, 0);
        glScaled(1.5, 1, 1);
        glutSolidCube(1.5);
        glPopMatrix();


        // Neck
        glPushMatrix();
        glColor3f(256.0 / 256.0, 256.0 / 256.0, 256.0 / 256.0);

        if (playerDirection == 0 || playerDirection == 2)
            glTranslatef(playerX + .3 * directionSwitcher, playerY + 2, playerZ);
        else
            glTranslatef(playerX, playerY + 2, playerZ + .3 * directionSwitcher);
        glRotated(90, 0, 1, 0);
        glScaled(1, 2, 1);
        glutSolidCube(1.5);
        glPopMatrix();

        glPushMatrix();
        glColor3f(256.0 / 256.0, 256.0 / 256.0, 256.0 / 256.0);

        if (playerDirection == 0 || playerDirection == 2) {
            glTranslatef(playerX - .1 * directionSwitcher, playerY, playerZ);
            glRotated(90, 0, 1, 0);
        }
        else {
            glTranslatef(playerX, playerY, playerZ - .1 * directionSwitcher);
            glRotated(180, 0, 1, 0);
        }
        glScaled(1.5, .75, .75);
        glutSolidCube(1.5);
        glPopMatrix();



        glPushMatrix();
        glColor3f(255.0 / 256.0, 128.0 / 256.0, 103.0 / 256.0);

        if (playerDirection == 0 || playerDirection == 2) {
            glTranslatef(playerX + 1.25 * directionSwitcher, playerY + 3, playerZ);
            glRotated(90, 0, 1, 0);
        }
        else {
            glTranslatef(playerX, playerY + 3, playerZ + 1.25 * directionSwitcher);
            glRotated(180, 0, 1, 0);
        }

        glRotated(90, 0, 1, 0);
        glScaled(.25, .5, .25);
        glutSolidCube(1.5);
        glPopMatrix();




        glPushMatrix();
        glColor3f(255.0 / 256.0, 110.0 / 256.0, 165.0 / 256.0);
        if (playerDirection == 0 || playerDirection == 2) {
            glTranslatef(playerX + 1.25 * directionSwitcher, playerY + 2.5, playerZ);
            glRotated(90, 0, 1, 0);
        }
        else {
            glTranslatef(playerX, playerY + 2.5, playerZ + 1.25 * directionSwitcher);
            glRotated(180, 0, 1, 0);
        }

        glRotated(90, 0, 1, 0);
        glScaled(.25, .5, .25);
        glutSolidCube(1.5);
        glPopMatrix();



        glPushMatrix();
        glColor3f(0.0 / 256.0, 0.0 / 256.0, 0.0 / 256.0);

        if (playerDirection == 0 || playerDirection == 2) {
            glTranslatef(playerX + .5 * directionSwitcher, playerY + 3, playerZ);
            glRotated(180, 0, 1, 0);
        }
        else {
            glTranslatef(playerX, playerY + 3, playerZ + .5 * directionSwitcher);
            glRotated(90, 0, 1, 0);
        }

        glRotated(90, 0, 1, 0);
        glScaled(1, .3, .2);
        glutSolidCube(1.5);
        glPopMatrix();

        glPushMatrix();
        glColor3f(255.0 / 256.0, 110.0 / 256.0, 165.0 / 256.0);

        if (playerDirection == 0 || playerDirection == 2) {
            glTranslatef(playerX + .25 * directionSwitcher, playerY + 4, playerZ);
            glRotated(180, 0, 1, 0);
        }
        else {
            glTranslatef(playerX, playerY + 4, playerZ + .25 * directionSwitcher);
            glRotated(90, 0, 1, 0);
        }

        glRotated(90, 0, 1, 0);
        glScaled(.25, .5, .5);
        glutSolidCube(1.5);
        glPopMatrix();

        // Draw player End -------------------------------------------------------------
    }

    void gameMap::renderGrass(float x, float z) 
    {
        glPushMatrix();
            glColor3f(190.0 / 255.0, 245.0 / 255.0, 102.0 / 255.0);
            glTranslatef(x, -6.8, z);
            glScalef(1, .15, 1);
            glRotated(90, 1, 0, 0);
            glBegin(GL_QUADS);
                glTexCoord2i(0, 0); glVertex2i(-2, -2);
                glTexCoord2i(0, 1); glVertex2i(-2, 2);
                glTexCoord2i(1, 1); glVertex2i(2, 2);
                glTexCoord2i(1, 0); glVertex2i(2, -2);
            glEnd();
        glPopMatrix();
    }

    void gameMap::renderLargeTree(float x, float z) 
    {
        glPushMatrix();
        glColor3f(190.0 / 255.0, 245.0 / 255.0, 102.0 / 255.0);
        glTranslatef(x, -6.8, z);
        glScalef(1, .15, 1);
        glRotated(90, 1, 0, 0);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(-2, -2);
        glTexCoord2i(0, 1); glVertex2i(-2, 2);
        glTexCoord2i(1, 1); glVertex2i(2, 2);
        glTexCoord2i(1, 0); glVertex2i(2, -2);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3f(142.0 / 255.0, 84.0 / 255.0, 80.0 / 255.0);
        glTranslatef(x, -5, z);
        glScalef(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();

        glPushMatrix();
        glColor4f(183.0 / 255.0, 214.0 / 255.0, 33.0 / 255.0, 1.0f);
        glTranslatef(x, -1.8, z);
        glScalef(.7, 1.25, .7);
        glutSolidCube(4);
        glPopMatrix();
    }

    void gameMap::renderRoad(float x, float z) 
    {
        glPushMatrix();
        glColor3f(82.0 / 255.0, 88.0 / 255.0, 102.0 / 255.0);
        glTranslatef(x, -7, z);
        glScalef(1, 0, 1);
        glutSolidCube(4);
        glPopMatrix();

        glPushMatrix();
        glColor3f(82.0 / 255.0, 88.0 / 255.0, 102.0 / 255.0);
        glTranslatef(x, -7, z);
        glScalef(.5, .1, .08);
        glutSolidCube(4);
        glPopMatrix();
    }

    void gameMap::renderWater(float x, float z) 
    {
        glPushMatrix();
        glColor3f(128.0 / 255.0, 245.0 / 255.0, 255.0 / 255.0);
        glTranslatef(x, -7, z);
        glScalef(1, 0, 1);
        glutSolidCube(4);
        glPopMatrix();
    }

    void gameMap::renderFlag(float x, float z) 
    {
        glPushMatrix();
        glColor3f(190.0 / 255.0, 245.0 / 255.0, 102.0 / 255.0);
        glTranslatef(x, -6.8, z);
        glScalef(1, .15, 1);
        glutSolidCube(4);
        glPopMatrix();

        glPushMatrix();
        glColor3f(100.0 / 255.0, 100.0 / 255.0, 100.0 / 255.0);
        glTranslatef(x, -2, z);
        glScalef(.18, 4, .18);
        glutSolidCube(2);
        glPopMatrix();

        glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslatef(x - 2, -2, z);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(0, 0);
        glTexCoord2i(0, 1); glVertex2i(2, 0);
        glTexCoord2i(1, 1); glVertex2i(2, 4);
        glTexCoord2i(1, 0); glVertex2i(4, 0);
        glEnd();
        glPopMatrix();
    }

    void gameMap::ludersCube(float size, float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, GLuint texture) {

        //glTranslatef(posX, (-7.0f+((size*scaleY)/2.0f)), posZ);
        glTranslatef(posX, posY, posZ);
        /*glScalef(scaleX, scaleY, scaleZ);
         glutSolidCube(size);*/

        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        //glColor3f(0.0f,1.0f,0.0f);    // Color Blue
        glVertex3f(scaleX, scaleY, -scaleZ);    // Top Right Of The Quad (Top)
        glVertex3f(-scaleX, scaleY, -scaleZ);    // Top Left Of The Quad (Top)
        glVertex3f(-scaleX, scaleY, scaleZ);    // Bottom Left Of The Quad (Top)
        glVertex3f(scaleX, scaleY, scaleZ);    // Bottom Right Of The Quad (Top)

        //glColor3f(scaleX,0.5f,0.0f);    // Color Orange
        glVertex3f(scaleX, -1.0f, scaleZ);    // Top Right Of The Quad (Bottom)
        glVertex3f(-scaleX, -1.0f, scaleZ);    // Top Left Of The Quad (Bottom)
        glVertex3f(-scaleX, -1.0f, -scaleZ);    // Bottom Left Of The Quad (Bottom)
        glVertex3f(scaleX, -1.0f, -scaleZ);    // Bottom Right Of The Quad (Bottom)

        //glColor3f(scaleX,0.0f,0.0f);    // Color Red
        glVertex3f(scaleX, scaleY, scaleZ);    // Top Right Of The Quad (Front)
        glVertex3f(-scaleX, scaleY, scaleZ);    // Top Left Of The Quad (Front)
        glVertex3f(-scaleX, -1.0f, scaleZ);    // Bottom Left Of The Quad (Front)
        glVertex3f(scaleX, -1.0f, scaleZ);    // Bottom Right Of The Quad (Front)

        //glColor3f(scaleX,1.0f,0.0f);    // Color Yellow
        glVertex3f(scaleX, scaleY, -scaleZ);    // Top Right Of The Quad (Back)
        glVertex3f(-scaleX, scaleY, -scaleZ);    // Top Left Of The Quad (Back)
        glVertex3f(-scaleX, -1.0f, -scaleZ);    // Bottom Left Of The Quad (Back)
        glVertex3f(scaleX, -1.0f, -scaleZ);    // Bottom Right Of The Quad (Back)

        //glColor3f(0.0f,0.0f,1.0f);    // Color Blue
        glVertex3f(-scaleX, scaleY, scaleZ);    // Top Right Of The Quad (Left)
        glVertex3f(-scaleX, scaleY, -scaleZ);    // Top Left Of The Quad (Left)
        glVertex3f(-scaleX, -1.0f, -scaleZ);    // Bottom Left Of The Quad (Left)
        glVertex3f(-scaleX, -1.0f, scaleZ);    // Bottom Right Of The Quad (Left)

         glColor3f(1.0f,0.0f,1.0f);    // Color Violet
        glVertex3f(scaleX, scaleY, -scaleZ);    // Top Right Of The Quad (Right)
        glVertex3f(scaleX, scaleY, scaleZ);    // Top Left Of The Quad (Right)
        glVertex3f(scaleX, -1.0f, scaleZ);    // Bottom Left Of The Quad (Right)
        glVertex3f(scaleX, -1.0f, -scaleZ);    // Bottom Right Of The Quad (Right)

        glEnd();
    }

#endif /* map_hpp */