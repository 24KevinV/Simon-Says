#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include <vector>
#include "windows.h"
#include "time.h"
using namespace std;

GLdouble width, height;
int wd;
const color offBlue(0/255.0, 102/255.0, 204/255.0);
const color onBlue(102/255.0, 179/255.0, 255/255.0);
const color offGreen(0/255.0, 153/255.0, 0/255.0);
const color onGreen(102/255.0, 255/255.0, 153/255.0);
const color offRed(140/255.0, 0/255.0, 0/255.0);
const color onRed(255/255.0, 102/255.0, 102/255.0);
const color offYellow(255/255.0, 204/255.0, 0/255.0);
const color onYellow(255/255.0, 224/255.0, 102/255.0);
const color white(255/255.0, 255/255.0, 255/255.0);

vector<Rect> tiles;
dimensions tileSize(180, 180);
vector<int> tileOrder;
vector<int> clickedTiles;

string label, label2;

int litTile;
int score;
int waitTime ; // milliseconds
bool tileIsOn = false;

enum states {welcome, play, over};
enum tileStatus{ready, flashing};

states gameState;
tileStatus tileState;

void tileOn(int tileNum) {
    switch (tileNum) {
        case 0:
            tiles[tileNum].setColor(onGreen);
            break;
        case 1:
            tiles[tileNum].setColor(onRed);
            break;
        case 2:
            tiles[tileNum].setColor(onYellow);
            break;
        case 3:
            tiles[tileNum].setColor(onBlue);
            break;
    }
}

void tileOff(int tileNum) {
    switch (tileNum) {
        case 0:
            tiles[tileNum].setColor(offGreen);
            break;
        case 1:
            tiles[tileNum].setColor(offRed);
            break;
        case 2:
            tiles[tileNum].setColor(offYellow);
            break;
        case 3:
            tiles[tileNum].setColor(offBlue);
            break;
    }
}

void initTiles() {
    tiles.push_back(Rect(offGreen, width / 4 + (width / 2 - tileSize.width) / 3, height / 4 + (height / 2 - tileSize.height) / 3, tileSize));
    tiles.push_back(Rect(offRed, 3 * width / 4 - (width / 2 - tileSize.width) / 3, height / 4 + (height / 2 - tileSize.height) / 3, tileSize));
    tiles.push_back(Rect(offYellow, width / 4 + (width / 2 - tileSize.width) / 3, 3 * height / 4 - (height / 2 - tileSize.height) / 3, tileSize));
    tiles.push_back(Rect(offBlue, 3 * width / 4 - (width / 2 - tileSize.width) / 3, 3 * height / 4 - (height / 2 - tileSize.height) / 3, tileSize));
    tileOrder.push_back(rand() % 4);
    litTile = 0;
    score = 0;
}

void init() {
    width = 500;
    height = 500;
    waitTime = 400;
    srand(time(0));
    initTiles();
    gameState = welcome;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // background color
    glClearColor(0.05, 0.05, 0.05, 1.0f);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE
    
    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    
    /*
     * Draw here
     */
    // Set labels based on game state
    switch (gameState) {
        case welcome: {
            label = "Press 's' to start";
            label2 = "Simon Says";
            break;
        }
        case play: {
            label = "Score: ";
            label.append(to_string(score));
            label2 = "Simon Says";
            break;
        }
        case over: {
            label = "Score: ";
            label.append(to_string(score));
            label2 = "Game Over, press 's' to play again";
            break;
        }
    }

    for(Rect &t: tiles) {
        t.draw();
    }
    // Add the labels on screen
    glColor3f(white.red, white.green, white.blue);
    glRasterPos2i(width / 2 - (4 * label.length()), height + 8 - (height - 2 * tileSize.height) / 4);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
    glRasterPos2i(width / 2 - (4 * label2.length()), (height - 2 * tileSize.height) / 4);
    for (const char &letter : label2) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 's') {
        if (gameState != play) {
            // Reset the game for playing if not already in a game
            tileOrder.clear();
            clickedTiles.clear();
            tileOrder.push_back(rand() % 4);
            score = 0;
            Sleep(500);
            tileState = flashing;
        }
        gameState = play;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            
            break;
        case GLUT_KEY_LEFT:
            
            break;
        case GLUT_KEY_RIGHT:
            
            break;
        case GLUT_KEY_UP:
            
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (tileState == ready) {
        if (gameState == play) {
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
                // Add the clicked tile to the list of clicked tiles
                for (int i = 0; i < tiles.size(); i++) {
                    if (tiles[i].isOverlapping(x, y)) {
                        clickedTiles.push_back(i);
                        // Change tile to the clicked color
                        tileOn(i);
                        // Check to make sure the most recently added tile is correct
                        if (clickedTiles[clickedTiles.size() - 1] != tileOrder[clickedTiles.size() - 1]) {
                            // A tile was clicked out of order, end the game
                            gameState = over;
                        }
                        if (clickedTiles.size() == tileOrder.size() && gameState != over) {
                            // All tiles were clicked correctly for that round increase score and reset for a new round
                            clickedTiles.clear();
                            score++;
                            // Add a new tile for the next round
                            tileOrder.push_back(rand() % 4);
                            // Flash all the tiles again and don't let the user click them while they're flashing
                            Sleep(waitTime);
                            tileState = flashing;
                        }
                    }
                }
            }
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        // Reset all the colors
        tiles[0].setColor(offGreen);
        tiles[1].setColor(offRed);
        tiles[2].setColor(offYellow);
        tiles[3].setColor(offBlue);
    }

    glutPostRedisplay();
}

void timer(int dummy) {
    // Flash the tiles once
    if (tileState == flashing) {
        if (!tileIsOn) {
            tileOn(tileOrder[litTile]);
            tileIsOn = true;
        } else {
            tileOff(tileOrder[litTile]);
            tileIsOn = false;
            litTile++;
            if (litTile == tileOrder.size()) {
                tileState = ready;
                litTile = 0;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(500, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Simon Says" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
