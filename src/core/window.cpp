/*
 * -----------------------------------------
 * Computer Graphics
 * Code: crossy road
 * Author: Mateus Silva
 * -----------------------------------------
 */

#include "window.h"

GLuint width = 800, height = 600;

int fps_desejado = FPS / 2;

GLManimation* animation = NULL;
map <int, GLManimation*> animations; //Mapeamento dos identificadores com as animacoes
int keyframe = 0; // numero do modelo 3D (keyframe) da animacao que sera desenhado no momento

// Definicao dos parametros do modelo de iluminacao
GLfloat light_position[] = { 0.0, 70.0, 0.0, 1.0 };
GLfloat light_ambient[] = { 0.6, 0.6, 6.0, 1.0 };

// player
enum PlayerID { idle };

bool lookAt = true;
bool grid;
std::vector<std::vector<char>> levelData;
std::vector<Car> listCars;

GLManimation* animationCar = NULL;

int animation_id = idle;

Sound sound;
Player player;

// 
float borderXMin = 0.0f;
float borderXMax = 0.0f;
float borderZMin = 0.0f;
float borderZMax = 0.0f;

void initGlut(const char* title, int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  // Inicia o display usando RGB, double-buffering e Z-buffering
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(title);

    // funcoes de callback
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard_special);
    glutTimerFunc(1000 / fps_desejado, timer, 0);

    // Ativacao dos parametros do modelo de iluminacao para a Luz 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING); // Ativa o modelo de iluminacao
    glEnable(GL_LIGHT0); // OpenGL suporta pelo menos 8 pontos de luz.

    //Define como a textura sera aplicada ao objeto
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    //Ativa a visualizacao de texturas 2D (Texturizacao 2D)
    glEnable(GL_TEXTURE_2D);

    // Ativa o modelo de sombreamento de "Gouraud" (Smooth
    glShadeModel(GL_SMOOTH);

    // Ativa o Back-face Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Ativa o z-buffering, de modo a remover as superficies escondidas
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

    loadLevel();
    loadPlayerAnimations();
    generateCars();

    sound.play("core/resources/sounds/track1.wav");
    sound.setVolume(60);

    glutMainLoop();

    sound.stop();
    SDL_QUIT;
}

void loadPlayerAnimations() 
{
    animation = glmLoadAnimation("core/resources/assets/chicken/chicken.obj", idle, 1);
    animation->name = "idle";
    animations[idle] = animation;
}

void reshape(int width, int height)
{
    // Prevent a divide by zero
    if (height == 0)
        height = 1;
    float ratio = 1.0 * width / height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(30, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Apaga o video e o depth buffer, e reinicia a matriz
    glLoadIdentity();

    float cameraX, cameraY, cameraZ;
    float lookAtX, lookAtY, lookAtZ;

    if (lookAt)
    {
        cameraX = player.posX;
        cameraY = player.posY + 70.0f;
        cameraZ = player.posZ + 80.0f;

        lookAtX = player.posX;
        lookAtY = player.posY;
        lookAtZ = player.posZ;
    }
    else
    {
        cameraX = player.posX;
        cameraY = player.posY + 70.0f;
        cameraZ = player.posZ + 15.0f;

        lookAtX = player.posX;
        lookAtY = player.posY;
        lookAtZ = player.posZ;
    }

    // Configura a câmera para olhar o jogador
    gluLookAt(cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, 0, 1, 0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    GLuint mode = (GLM_SMOOTH | GLM_TEXTURE); // Define sombreamento Gouraud

    renderGrass();

    if (levelData.empty()) return;

    for (size_t i = 0; i < levelData.size(); i++)
    {
        const std::vector<char>& row = levelData[i];
        for (size_t j = 0; j < row.size(); j++)
        {
            float x = borderXMin + (static_cast<int>(j) * 5);
            float z = borderZMax - (static_cast<int>(i) * 5);

            switch (row[j])
            {
                case '0': break;
                case '1': renderTree(x, z); break;
                case '2': renderRoad(x, z); break;
                case '3': renderWater(x, z); break;
                case '4': renderLilypad(x, z); break;
                case '5': renderFinishLine(x, z); break;
            }
        }
    }

    renderPlayer(player.posX, player.posZ, mode, player.playerDirection, player.isJumping, player.jumpStartTime, player.jumpDuration);

    for (Car& car : listCars) {
        if (car.update(borderXMin, borderXMax, player.posX, player.posZ, player.playerGridX, player.playerGridZ))
            player.death();
        car.draw();
    }

    if (grid) renderGrid();

    if (player.hasWon)
        loadLevel();

    glFlush();
    glutSwapBuffers();  // Troca os buffers
}

void drawAnimation(int id, GLuint mode) 
{
    glmDrawAnimation(animations[id], keyframe, mode);
}

void renderGrass()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(0.74, 0.96, 0.4);
        glBegin(GL_QUADS);
            glVertex3f(borderXMin, 0.0f, borderZMin);
            glVertex3f(borderXMin, 0.0f, borderZMax);
            glVertex3f(borderXMax, 0.0f, borderZMax);
            glVertex3f(borderXMax, 0.0f, borderZMin);
        glEnd();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void renderRoad(float x, float z)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(82.0 / 255.0, 88.0 / 255.0, 102.0 / 255.0);
        glBegin(GL_QUADS);
            glVertex3f(x, 0.1f, z - 5);
            glVertex3f(x, 0.1f, z);
            glVertex3f(x + 5, 0.1f, z);
            glVertex3f(x + 5, 0.1f, z - 5);
        glEnd();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(x + 2.5, 0.1, z - 2.5);
        glScalef(.5, 0.1f, .08);
        glutSolidCube(4);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void renderWater(float x, float z)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(128.0 / 255.0, 245.0 / 255.0, 255.0 / 255.0);
        glBegin(GL_QUADS);
            glVertex3f(x, 0.1f, z - 5);
            glVertex3f(x, 0.1f, z);
            glVertex3f(x + 5, 0.1f, z);
            glVertex3f(x + 5, 0.1f, z - 5);
        glEnd();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void renderTree(float x, float z)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    // stem
    glPushMatrix();
        glColor3f(142.0 / 255.0, 84.0 / 255.0, 80.0 / 255.0);
        glTranslatef(x + 2.5, 1.5f, z - 2.5);
        glScalef(0.5, 1, 0.5);
        glutSolidCube(2);
    glPopMatrix();

    // tree top
    glPushMatrix();
        glColor3f(0.514, 0.604, 0.125);
        glTranslatef(x + 2.5, 5.0f, z - 2.5);
        glScalef(0.8f, 1.25f, 0.8f);
        glutSolidCube(4);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void renderLilypad(float x, float z)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(0.0 / 255.0, 100.0 / 255.0, 0.0 / 255.0);
        glBegin(GL_QUADS);
            glVertex3f(x, 0.1f, z - 5);
            glVertex3f(x, 0.1f, z);
            glVertex3f(x + 5, 0.1f, z);
            glVertex3f(x + 5, 0.1f, z - 5);
        glEnd();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);
        glTranslatef(x + 2.5, 0.1f, z - 2.5);
        glRotated(45, 0, 1, 0);
        glScalef(.5, .2, .8);
        glutSolidCube(2);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f);
        glTranslatef(x + 2.5, 0.1f, z - 2.5);
        glRotated(-45, 0, 1, 0);
        glScalef(.5, .2, .8);
        glutSolidCube(2);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void renderFinishLine(float x, float z)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
            glVertex3f(x + 5.0f, 0.1f, z);
            glVertex3f(x + 5.0f, 0.1f, z);
            glVertex3f(x + 5.0f, 0.1f, z - 5.0f);
            glVertex3f(x + 5.0f, 0.1f, z - 5.0f);
        glEnd();
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void generateCars()
{
    for (size_t i = 0; i < levelData.size(); i++)
    {
        if (levelData[i][0] == '2')
        {
            float speed = 0.25f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.6f - 0.25f)));
            float distance1 = 15.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (40.0f - 15.0f)));

            int a = i * -1 * 5;
            listCars.push_back(Car(borderXMin + distance1, 1.0f, a, speed, 0, i));
        }
    }
}

void renderGrid()
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    for (float x = borderXMin; x < borderXMax; x += 5.0f) {
        for (float z = borderZMin; z < borderZMax; z += 5.0f) {
            glBegin(GL_LINE_LOOP);
                glVertex3f(x, 0.15f, z);
                glVertex3f(x + 5.0f, 0.15f, z);
                glVertex3f(x + 5.0f, 0.15f, z + 5.0f);
                glVertex3f(x, 0.15f, z + 5.0f);
            glEnd();
        }
    }
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void renderPlayer(float x, float z, GLuint mode, int playerDirection, bool isJumping, float jumpStartTime, float jumpDuration)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
        // Calcular o deslocamento Y baseado na animação de pulo
        float yOffset = 0.0f;
        if (isJumping) {
            float elapsedTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - jumpStartTime;
            if (elapsedTime < jumpDuration) {
                float jumpProgress = elapsedTime / jumpDuration;
                yOffset = sin(jumpProgress * M_PI) * 2.0f; 
            }
            else {
                isJumping = false; // Pulo completado
            }
        }

        glTranslated(x + 2.5, 1.0f + yOffset, z - 2);
        glScaled(0.7f, 0.7f, 0.7f);
        switch (playerDirection) 
        {
            case 0: // Right
                glRotated(90, 0.0f, 1.0f, 0.0f);
                break;
            case 1: // Up
                glRotated(180, 0.0f, 1.0f, 0.0f);
                break;
            case 2: // Left
                glRotated(-90, 0.0f, 1.0f, 0.0f);
                break;
            case 3: // Down
                glRotated(0, 0.0f, 1.0f, 0.0f);
                break;
        }
        drawAnimation(animation_id, mode);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void timer(int value) 
{
   glutTimerFunc(1000 / (fps_desejado), timer, 0);
   glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) 
{
    switch (key) 
    {
        case 'w': case 'W': player.moveUp(levelData); break;
        case 'a': case 'A': player.moveLeft(levelData); break;
        case 's': case 'S': player.moveDown(levelData); break;
        case 'd': case 'D': player.moveRight(levelData); break;
        case 'l': case 'L': lookAt = !lookAt; break;
        case 'g': case 'G': grid = !grid; break;
        case 27: exit(EXIT_SUCCESS); break;
    }
    glutPostRedisplay();
}

void keyboard_special(int key, int x, int y)
{
    switch (key) 
    {
        case GLUT_KEY_UP: player.moveUp(levelData); break;
        case GLUT_KEY_LEFT: player.moveLeft(levelData); break;
        case GLUT_KEY_RIGHT: player.moveRight(levelData); break;
        case GLUT_KEY_DOWN: player.moveDown(levelData); break;
    }
    glutPostRedisplay();
}

bool loadLevel()
{

    std::ostringstream filePathStream;
    filePathStream << "core/gameplay/levels/lv" << player.level << ".txt";
    std::string filename = filePathStream.str();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open level file: " << filename << std::endl;
        return false;
    }

    levelData.clear();
    std::string line;

    // read the level data
    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        levelData.push_back(row);
    }

    // update mapWidth and mapHeight based on actual data
    int mapWidth = levelData.empty() ? 0 : levelData[0].size();  // guard against empty levelData
    int mapHeight = levelData.size();

    borderXMin = -((mapWidth * 5) / 2);
    borderXMax = ((mapWidth * 5) / 2);
    borderZMin = -(mapHeight * 5);
    borderZMax = 0.0f;

    file.close();
    return true;
}