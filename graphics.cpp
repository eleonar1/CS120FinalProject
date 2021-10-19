#include "circle.h"
#include "graphics.h"
#include "rect.h"
#include <iostream>
#include <memory>
#include <vector>
#include <time.h>
#include "Triangle.h"
#include <fstream>
#include <algorithm>

using namespace std;

GLdouble width, height;
int wd;
const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color white(1, 1, 1);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color orange(1, 163/255.0, 22/255.0);
const color cyan (0, 1, 1);
const color yellow(1,1,0);
const color gray(0.5,0.5,0.5);
const color red(1,0,0);
const color pipeGreen((26/255.0), (200/255.0), (56/255.0));

//Vectors containing all of the obstacles
vector<Rect> obstacleBottom;
vector<Rect> obstacleTop;
vector<Rect> bottomOutline;
vector<Rect> topOutline;

//Vector holding the clouds
vector<unique_ptr<Shape>> clouds;

//Rectangle for the grass
Rect grass;
Rect grassOutline;

//Circle for the sun
Circle sun;
Circle sunOutline;

//Circle for the flappyBird
Circle flappyBird;
Circle birdOutline;
Triangle birdBeak;
Triangle beakOutline;
Circle flappyBirdEyeOutline;
Circle flappyBirdEyeWhite;
Circle flappyBirdEyeBlack;
Triangle flappyBirdWing;
Triangle wingOutline;

//Rectangles for score box
Rect scoreBox;
Rect scoreBoxOutline;

//Shapes for testing
Triangle testWing1;
Triangle testWing2;
Triangle testWing3;
Triangle testWing4;
Triangle testWing5;

Rect testObstacle;


//File object to store highscores
fstream f;

ofstream overwrite;

//boolean to store whether username is valid
bool validName;

//Struct to hold the data read from the highscore file
struct highScore {
    int score;
    string username;

    /* Constructors */
    highScore(){
        this->score = 0;
        this->username = "Placeholder";
    }
    highScore(int score, string username){
        this->score = score;
        this->username = username;
    }



    //Getters
    int getScore(){
        return score;
    }
    string getUsername(){
        return username;
    }

    //Overloading operators
    friend bool operator < (highScore &lhs, highScore &rhs){
        return lhs.getScore() < rhs.getScore();
    }
    friend bool operator > (highScore &lhs, highScore &rhs){
        return lhs.getScore() > rhs.getScore();
    }
    friend ostream& operator << (ostream& outs, highScore &h) {
        outs << "Score: " << h.score << " " << "Achieved by: " <<  h.username;
        return outs;
    }
};

//Strings for storage of username
string inputUsername;
string tempUsername;

//Vector of highScores
vector<highScore> highscores;

//Enum of the windows
enum screens{startScreen, gameScreen, endScreen, endScreenHighScore, testScreen};

//Current screen number
int screenNum = startScreen;

int score = 0;

int numLoops = 0;

//void initTesting() {
//    testObstacle.setHeight(150);
//    testObstacle.setColor(1,1,1,1);
//    testObstacle.setWidth(50);
//
//    testWing1
//    testWing2
//    testWing3.setCenter()
//    testWing4.setCenter()
//    testWing5.setCenter()
//}

void initClouds() {
    // Note: the Rect objects that make up the flat bottom of the clouds
    // won't appear until you implement the Rect::draw method.
    clouds.clear();
    dimensions cloudBottom(30, 30);
    // First cloud
    clouds.push_back(make_unique<Circle>(white, 300, 100, 20));
    clouds.push_back(make_unique<Circle>(white, 330, 100, 20));
    clouds.push_back(make_unique<Circle>(white, 320, 90, 20));
    clouds.push_back(make_unique<Rect>(white, 315, 105, cloudBottom));
    // Second cloud
    clouds.push_back(make_unique<Circle>(white, 100, 80, 20));
    clouds.push_back(make_unique<Circle>(white, 130, 80, 20));
    clouds.push_back(make_unique<Circle>(white, 120, 70, 20));
    clouds.push_back(make_unique<Rect>(white, 115, 85, cloudBottom));
    // Third cloud
    clouds.push_back(make_unique<Circle>(white, 450, 50, 20));
    clouds.push_back(make_unique<Circle>(white, 480, 50, 20));
    clouds.push_back(make_unique<Circle>(white, 470, 40, 20));
    clouds.push_back(make_unique<Rect>(white, 465, 55, cloudBottom));

}

void initGrass() {
    grass.setCenter(250, 475);
    grass.setSize(width, height/10);
    grass.setColor(grassGreen);
    grassOutline.setCenter(250, 475);
    grassOutline.setSize(width, height/10+1);
    grassOutline.setColor(black);
}
void initSun(){
    sun.setCenter(25, 25);
    sun.setRadius(50);
    sun.setColor(yellow);
    sunOutline.setCenter(25, 25);
    sunOutline.setRadius(51);
    sunOutline.setColor(black);
}

void initObstacles() {
    // Create a vector that holds the obstacles
    int totalObstacleWidth = 0;
    dimensions obstacleBottomSize;
    dimensions obstacleTopSize;
    dimensions topOutlineSize;
    dimensions bottomOutlineSize;
    int numObstacles = 0;
    while (numObstacles < 100) {
        // Randomly define the heights of the obstacles
        obstacleBottomSize.height = rand() % 301 + 50;
        obstacleTopSize.height = 350 - obstacleBottomSize.height;
        topOutlineSize.height = obstacleTopSize.height + 5;
        bottomOutlineSize.height = obstacleBottomSize.height + 5;

        // Set the obstacle width to 30, we want same widths for all
        obstacleBottomSize.width = 75;
        obstacleTopSize.width = 75;
        topOutlineSize.width = 83;
        bottomOutlineSize.width = 83;

        obstacleBottom.push_back(Rect(darkBlue,width * 1.5 + totalObstacleWidth,
                                      height-((obstacleBottomSize.height/2)+50), obstacleBottomSize));

        obstacleTop.push_back(Rect(darkBlue,width * 1.5 + totalObstacleWidth,
                                      ((obstacleTopSize.height/2)), obstacleTopSize));

        bottomOutline.push_back(Rect(black,width * 1.5 + totalObstacleWidth,
                                      height-((bottomOutlineSize.height/2)+50), bottomOutlineSize));

        topOutline.push_back(Rect(black,width * 1.5 + totalObstacleWidth,
                                  ((topOutlineSize.height/2)), topOutlineSize));

        totalObstacleWidth += obstacleBottomSize.width + 150;
        numObstacles++;
    }
}

void initScoreBox(){
    scoreBox.setCenter(60, (height/16) * 15 + 8);
    scoreBox.setWidth(110);
    scoreBox.setHeight(40);
    scoreBox.setColor(white);
    scoreBoxOutline.setCenter(60, (height/16) * 15 + 8);
    scoreBoxOutline.setWidth(112);
    scoreBoxOutline.setHeight(42);
    scoreBoxOutline.setColor(black);
}

void initFlappyBird() {
    //init "bird"
    flappyBird.setCenter(width/3, height/2);
    flappyBird.setRadius(14);
    flappyBird.setColor(gray);

    //init bird outline
    birdOutline.setCenter(width/3, height/2);
    birdOutline.setRadius(15);
    birdOutline.setColor(black);

    //init bird beak
    birdBeak.setLeftX((width/3+13));
    birdBeak.setRightX((width/3)+20);
    birdBeak.setTopY((height/2)+2);
    birdBeak.setBottomY(height/2+5);
    birdBeak.setColor(orange);

    //init beak outline
    beakOutline.setLeftX((width/3)+11);
    beakOutline.setRightX((width/3)+22);
    beakOutline.setTopY((height/2));
    beakOutline.setBottomY(height/2+7);
    beakOutline.setColor(black);

    //init bird eye outline
    flappyBirdEyeOutline.setCenter((width/3)+11, (height/2)-11.5);
    flappyBirdEyeOutline.setRadius(5);
    flappyBirdEyeOutline.setColor(black);

    //init white of bird eye
    flappyBirdEyeWhite.setCenter((width/3)+11, (height/2)-11.5);
    flappyBirdEyeWhite.setRadius(4);
    flappyBirdEyeWhite.setColor(white);

    //init pupil
    flappyBirdEyeBlack.setCenter((width/3)+12.5, (height/2)-11.5);
    flappyBirdEyeBlack.setRadius(2.5);
    flappyBirdEyeBlack.setColor(black);

    //init bird wing
    flappyBirdWing.setLeftX((width/3)-12);
    flappyBirdWing.setRightX((width/3)+2);
    flappyBirdWing.setTopY((height/2)-7);
    flappyBirdWing.setBottomY(height/2+8);
    flappyBirdWing.setColor(gray);

    //init wing outline
    wingOutline.setLeftX((width/3)-13);
    wingOutline.setRightX((width/3)+3.5);
    wingOutline.setTopY((height/2)-7);
    wingOutline.setBottomY(height/2+11);
    wingOutline.setColor(black);
}

void init() {
    //init all objects
    width = 500;
    height = 500;
    srand(time(NULL));
    initSun();
    initClouds();
    initGrass();
    initObstacles();
    initFlappyBird();
    initScoreBox();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);
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
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS


    //Screen messages
    //and other declarations for the highscore end screen and regular end screen
    string welcomeMessage = "Welcome to Definitely Not Flappybird, press 's' to play!";
    string rulesMessage1 = "Rules:";
    string rulesMessage2 = "1. Don't hit the obstacles!";
    string rulesMessage3 = "2. You score every time an obstacle leaves the screen";
    string rulesMessage4 = "3. Press and hold the up or down keys to fly the bird";
    string endMessage = "Thanks for playing! Score: " + to_string(score) + " Press 's' to play again!";
    string gameScore = "Score: " + to_string(score);
    string newScoreMessage = "NEW HIGH SCORE! Enter a valid username below.";
    int obstacleNum = 0;
    string tempHighScore;
    int messageHeight;
    highScore minScore;
    bool newHighscore;
    int hS;
    string enterUsername = "Username: ";
    //Switch case for which screen to display
    switch(screenNum) {
        case startScreen:
            glClearColor(0, 0, 0, 1);
            glRasterPos2i(25, height / 2);

            for (const char &letter : welcomeMessage) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            glRasterPos2i(40, height / 2 + 35);
            for (const char &letter : rulesMessage1) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            glRasterPos2i(40, height / 2 + 50);
            for (const char &letter : rulesMessage2) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glRasterPos2i(40, height / 2 + 65);
            for (const char &letter : rulesMessage3) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glRasterPos2i(40, height / 2 + 80);
            for (const char &letter : rulesMessage4) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            break;
        case gameScreen:
            glClearColor(skyBlue.red, skyBlue.green, skyBlue.blue, 1.0f);

            numLoops += 1;
            //Draw the sun
            sunOutline.draw();
            sun.draw();

            //draw clouds
            for (unique_ptr<Shape> &s : clouds) {
                // #polymorphism
                s->draw();
            }

            for (Rect &outline : bottomOutline) {
                if (outline.isOverlapping(birdOutline)) {
                    outline.setColor(red);
                    //Clear
                    highscores.clear();
                    //Get the highscores
                    f.open("../Highscores.txt");
                    while (f && f.peek() != EOF) {
                        getline(f, tempHighScore, ',');
                        getline(f, tempUsername);
                        highscores.push_back(highScore(stoi(tempHighScore), tempUsername));
                    }
                    f.close();
                    //Check if the score is higher than any of the other highscores
                    for (int i = 0; i < highscores.size(); i++) {
                        if (highscores[i].getScore() < score) {
                            newHighscore = true;
                        }
                    }
                    if (newHighscore) {
                        screenNum = endScreenHighScore;
                    }
                    else {
                        screenNum = endScreen;
                    }
                } else {
                    outline.setColor(black);
                }
                outline.draw();
            }
            //draw bottom obstacles
            obstacleNum = 0;
            for (Rect &obstacle : obstacleBottom) {
                if (obstacleNum % 3 == 0) {
                    obstacle.setColor(red);
                    obstacle.draw();
                } else if (obstacleNum % 3 == 1) {
                    obstacle.setColor(darkBlue);
                    obstacle.draw();
                } else {
                    obstacle.setColor(pipeGreen);
                    obstacle.draw();
                }
                obstacleNum++;
            }

            //draw top obstacles
            for (Rect &outline : topOutline) {
                if (outline.isOverlapping(birdOutline)) {
                    outline.setColor(red);
                    //Clear
                    highscores.clear();
                    //Get the highscores
                    f.open("../Highscores.txt");
                    while (f && f.peek() != EOF) {
                        getline(f, tempHighScore, ',');
                        getline(f, tempUsername);
                        highscores.push_back(highScore(stoi(tempHighScore), tempUsername));
                    }
                    f.close();

                    sort(highscores.begin(), highscores.begin()+5);
                    //Check if the score is higher than any of the other highscores
                    if (highscores[0].getScore() < score) {
                            newHighscore = true;
                        }
                    if (newHighscore) {
                        validName = false;
                        screenNum = endScreenHighScore;
                    }
                    else {
                        screenNum = endScreen;
                    }

                } else {
                    outline.setColor(black);
                }
                outline.draw();
            }

            //draw top obstacles
            obstacleNum = 0;
            for (Rect &obstacle : obstacleTop) {
                if (obstacleNum % 3 == 0) {
                    obstacle.setColor(red);
                    obstacle.draw();
                } else if (obstacleNum % 3 == 1) {
                    obstacle.setColor(darkBlue);
                    obstacle.draw();
                } else {
                    obstacle.setColor(pipeGreen);
                    obstacle.draw();
                }
                obstacleNum++;
            }
            //draw grass
            grassOutline.draw();
            grass.draw();

            //Draw the flappy bird
            //Body
            birdOutline.draw();
            flappyBird.draw();

            //beak
            beakOutline.drawBeak();
            birdBeak.drawBeak();

            //Wing
            if (numLoops % 40 >= 0 && numLoops % 40 <= 10) {
                wingOutline.setLeftX(wingOutline.getLeftX() - 2);
                flappyBirdWing.setLeftX(flappyBirdWing.getLeftX() + 1);
                //flappyBirdWing.setBottomY(flappyBirdWing.getBottomY()-1);
                wingOutline.setRightX(wingOutline.getRightX() + 3);
                wingOutline.drawUp2Outline();
                flappyBirdWing.drawUp2Wing();
                wingOutline.setRightX(wingOutline.getRightX() - 3);
                flappyBirdWing.setLeftX(flappyBirdWing.getLeftX() - 1);
                //flappyBirdWing.setBottomY(flappyBirdWing.getBottomY()+1);
                wingOutline.setLeftX(wingOutline.getLeftX() + 2);
            } else if (numLoops % 40 >= 11 && numLoops % 40 <= 15) {
                //draw wing between middle position and all the way up
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() + 1);
                wingOutline.drawUp1();
                flappyBirdWing.drawUp1();
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() - 1);
            } else if (numLoops % 40 >= 16 && numLoops % 40 <= 21) {
                //draw wing in middle position
                wingOutline.drawMiddle();
                flappyBirdWing.drawMiddle();
            } else if (numLoops % 40 >= 22 && numLoops % 40 <= 29) {
                //draw wing between middle position and all the way down
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() - .5);
                wingOutline.drawDown1();
                flappyBirdWing.drawDown1();
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() + .5);
            } else {
                //to ensure that wing outline stays outlining the wing
                //and to mitigate some of the pixelated look
                //the outline and wing bottomY coordinates need to be slightly adjusted
                wingOutline.setBottomY(wingOutline.getBottomY() - 1);
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() - 3);

                //draw wing all the way down
                wingOutline.drawDown2();
                flappyBirdWing.drawDown2();

                //revert adjustments to coordinates so that wing and outline don't
                //grow repeatedly for every flap of the wing
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() + 3);
                wingOutline.setBottomY(wingOutline.getBottomY() + 1);
            }
            //Eye
            flappyBirdEyeOutline.draw();
            flappyBirdEyeWhite.draw();
            flappyBirdEyeBlack.draw();

            //Score box
            scoreBoxOutline.draw();
            scoreBox.draw();


            //Print the score in the game as it is being played
            glColor3f(0, 0, 0);
            glRasterPos2i(12, (height / 16)* 15 + 18 );
            for (const char &letter : gameScore) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }

            break;
        case endScreen:
            //Clear the vector
            highscores.clear();
            //Get the highscores
            f.open("../Highscores.txt");
            while (f && f.peek() != EOF) {
                getline(f, tempHighScore, ',');
                getline(f, tempUsername, '\n');
                highscores.push_back(highScore(stoi(tempHighScore), tempUsername));
            }
            f.close();
            sort(highscores.begin(), highscores.begin()+5);

            //Set the background color to black
            glClearColor(0, 0, 0, 1);
            //Height of the message
            messageHeight = height / 2 - 100;
            glRasterPos2i(200, 100);
            for (const char &letter : "High Scores") {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }
            //Set the message position
            glRasterPos2i(30, messageHeight);

            //Print leaderboard
            glColor3f(1, 1, 1);
            for (int i = highscores.size()-1; i >= 0; i--) {
                glRasterPos2i(30, messageHeight);
                for (const char &letter : highscores[i].getUsername()) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
                glRasterPos2i(160, messageHeight);
                for (const char &letter : "  .............................    " + to_string(highscores[i].getScore())) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
                messageHeight += 30;
            }
            //Tell user their score and how to play again
            glRasterPos2i(30, 325);
            for (const char &letter : endMessage) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            break;

        case endScreenHighScore:
            //Clear the vector
            highscores.clear();
            //Get the highscores
            f.open("../Highscores.txt");
            while (f && f.peek() != EOF) {
                getline(f, tempHighScore, ',');
                getline(f, tempUsername);
                highscores.push_back(highScore(stoi(tempHighScore), tempUsername));
            }
            f.close();
            //sort the vector using score
            sort(highscores.begin(), highscores.begin()+5);

            //Set the background color to black
            glClearColor(0, 0, 0, 1);
            //Height of the message
            messageHeight = height / 2 - 100;
            glRasterPos2i(200, 100);
            for (const char &letter : "High Scores") {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }
            //Set the message position
            glRasterPos2i(30, messageHeight);

            //print leaderboard user highscores vector
            glColor3f(1, 1, 1);
            for (int i = highscores.size()-1; i >= 0; i--) {
                glRasterPos2i(30, messageHeight);
                for (const char &letter : highscores[i].getUsername()) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
                glRasterPos2i(160, messageHeight);
                for (const char &letter : "  .............................    " + to_string(highscores[i].getScore())) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
                messageHeight += 30;
            }

            //Tell user there is a highscore
            glColor3f(1, 1, 1);
            glRasterPos2i(50, 300);
            for (const char &letter : newScoreMessage) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            //Show user where to type username
            glColor3f(1, 1, 1);
            glRasterPos2i(170, 325);
            for (const char &letter : enterUsername) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            //Print the user name that is being typed
            glColor3f(1, 1, 1);
            glRasterPos2i(245, 325);
            for (const char &letter : inputUsername) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            //Tell user their score and how to restart game
            glRasterPos2i(30, 350);
            for (const char &letter : endMessage) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }


            break;
        case(testScreen):
            //Set the background color to black
            glClearColor(0, 0, 0, 1);



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

    //Switch from the start screen to game screen
    //if key is s and screen is start screen, end screen or high score end screen
    //a user must have submitted a valid username for s to restart the game in endScreenHighScore
    if(key == 's' && (screenNum == startScreen || screenNum == endScreen || (screenNum == endScreenHighScore && validName == true))){
        //Clear the previous vectors holding the obstacle info
        obstacleTop.clear();
        obstacleBottom.clear();
        bottomOutline.clear();
        topOutline.clear();

        //Reinitialize the obstacles
        initObstacles();
        initFlappyBird();
        score = 0;
        validName = false;
        screenNum = gameScreen;
    }
    //if key is backspace, remove character at end of username
    if(key == 8 && screenNum == endScreenHighScore){
        inputUsername.erase(inputUsername.size()-1);
    }

    //Note: in the following section, a boolean variable called validName is used
    //It's usage seems as though it is flipped, where if statements depend on validName being false
    //However validName simply keeps track of whether or not the name has been accepted into the vector of high scores
    //This can be seen on line 687 where validName is set to true after a new highscore has been written to the file
    //if key is enter, and username is appropriate length, add score and username to vector of highscores, write vector to file
    if(key == 13 && screenNum == endScreenHighScore && validName == false){
        //Get the min score
        sort(highscores.begin(), highscores.begin() + 5);
        //Remove the min score
        highscores.erase(highscores.begin());
        highscores.push_back(highScore(score,inputUsername));

        overwrite.open("../Highscores.txt");
        overwrite.clear();
        for(int i = 4; i >= 0; i--){
            tempUsername = highscores[i].getUsername();
            if(tempUsername.size() == 0) {
                overwrite << highscores[i].getScore() << "," << "Placeholder" << endl;
            }
            else{
                overwrite << highscores[i].getScore() << "," << tempUsername << endl;
            }
        }
        overwrite.close();
        validName = true;
    }
    //A
    //add character A to end of username string
    if(key == 'A' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("A");
    }
    //add character a to end of username string
    if(key == 'a' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("a");
    }
    
    //B
    //add character B to end of username string
    if(key == 'B' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("B");
    }
    //add character a to end of username string
    if(key == 'b' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("b");
    }
    
    //C
    //add character C to end of username string
    if(key == 'C' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("C");
    }
    //add character c to end of username string
    if(key == 'c' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("c");
    }
    
    //D
    //add character D to end of username string
    if(key == 'D' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("D");
    }
    //add character d to end of username string
    if(key == 'd' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("d");
    }

    //E
    //add character E to end of username string
    if(key == 'E' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("E");
    }
    //add character e to end of username string
    if(key == 'e' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("e");
    }
    
    //F
    //add character F to end of username string
    if(key == 'F' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("F");
    }
    //add character f to end of username string
    if(key == 'f' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("f");
    }

    //G
    //add character G to end of username string
    if(key == 'G' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("G");
    }
    //add character g to end of username string
    if(key == 'g' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("g");
    }
    
    //H
    //add character H to end of username string
    if(key == 'H' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("H");
    }
    //add character h to end of username string
    if(key == 'h' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("h");
    }

    //I
    //add character i to end of username string
    if(key == 'I' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("I");
    }
    //add character i to end of username string
    if(key == 'i' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("i");
    }

    //J
    //add character J to end of username string
    if(key == 'J' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("J");
    }
    //add character j to end of username string
    if(key == 'j' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("j");
    }

    //K
    //add character K to end of username string
    if(key == 'K' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("K");
    }
    //add character k to end of username string
    if(key == 'k' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("k");
    }


    //L
    //add character L to end of username string
    if(key == 'L' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("L");
    }
    //add character l to end of username string
    if(key == 'l' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("l");
    }

    //M
    //add character M to end of username string
    if(key == 'M' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("M");
    }
    //add character m to end of username string
    if(key == 'm' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("m");
    }

    //N
    //add character N to end of username string
    if(key == 'N' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("N");
    }
    //add character n to end of username string
    if(key == 'n' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("n");
    }

    //O
    //add character O to end of username string
    if(key == 'O' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("O");
    }
    //add character o to end of username string
    if(key == 'o' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("o");
    }

    //P
    //add character P to end of username string
    if(key == 'P' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("P");
    }
    //add character p to end of username string
    if(key == 'p' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("p");
    }

    //Q
    //add character Q to end of username string
    if(key == 'Q' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("Q");
    }
    //add character q to end of username string
    if(key == 'q' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("q");
    }
    
    //R
    //add character R to end of username string
    if(key == 'R' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("R");
    }
    //add character r to end of username string
    if(key == 'r' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("r");
    }

    //S
    //add character S to end of username string
    if(key == 'S' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("S");
    }
    //add character s to end of username string
    if(key == 's' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("s");
    }

    //T
    //add character T to end of username string
    if(key == 'T' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("T");
    }
    //add character t to end of username string
    if(key == 't' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("t");
    }

    //U
    //add character U to end of username string
    if(key == 'U' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("U");
    }
    //add character u to end of username string
    if(key == 'u' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("u");
    }

    //V
    //add character V to end of username string
    if(key == 'V' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("V");
    }
    //add character v to end of username string
    if(key == 'v' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("v");
    }
    
    //W
    //add character W to end of username string
    if(key == 'W' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("W");
    }
    //add character w to end of username string
    if(key == 'w' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("w");
    }

    //X
    //add character X to end of username string
    if(key == 'X' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("X");
    }
    //add character x to end of username string
    if(key == 'x' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("x");
    }

    //Y
    //add character Y to end of username string
    if(key == 'Y' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("Y");
    }
    //add character y to end of username string
    if(key == 'y' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("y");
    }
    
    //Z
    //add character Z to end of username string
    if(key == 'Z' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("Z");
    }
    //add character z to end of username string
    if(key == 'z' && screenNum == endScreenHighScore && inputUsername.size() < 15 && validName == false){
        inputUsername.append("z");
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            if(birdOutline.getBottomY()<448) {
                flappyBird.move(0, 9);
                birdOutline.move(0, 9);
                beakOutline.setTopY(beakOutline.getTopY() + 9);
                beakOutline.setBottomY(beakOutline.getBottomY() + 9);
                birdBeak.setTopY(birdBeak.getTopY() + 9);
                birdBeak.setBottomY(birdBeak.getBottomY() + 9);
                flappyBirdEyeOutline.move(0, 9);
                flappyBirdEyeBlack.move(0, 9);
                flappyBirdEyeWhite.move(0, 9);
                flappyBirdWing.setTopY(flappyBirdWing.getTopY() + 9);
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() + 9);
                wingOutline.setTopY(wingOutline.getTopY() + 9);
                wingOutline.setBottomY(wingOutline.getBottomY() + 9);
            }
            break;

        case GLUT_KEY_UP:
            if(birdOutline.getTopY()>0) {
                flappyBird.move(0, -9);
                birdOutline.move(0, -9);
                beakOutline.setTopY(beakOutline.getTopY() - 9);
                beakOutline.setBottomY(beakOutline.getBottomY() - 9);
                birdBeak.setTopY(birdBeak.getTopY() - 9);
                birdBeak.setBottomY(birdBeak.getBottomY() - 9);
                flappyBirdEyeOutline.move(0, -9);
                flappyBirdEyeBlack.move(0, -9);
                flappyBirdEyeWhite.move(0, -9);
                flappyBirdWing.setTopY(flappyBirdWing.getTopY() - 9);
                flappyBirdWing.setBottomY(flappyBirdWing.getBottomY() - 9);
                wingOutline.setTopY(wingOutline.getTopY() - 9);
                wingOutline.setBottomY(wingOutline.getBottomY() - 9);
            }
            break;

        case GLUT_KEY_RIGHT:
            
            break;
        case GLUT_KEY_LEFT:
            
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    // passed in as parameters to this function. This will make
    // the user block move with the mouse.
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    glutPostRedisplay();
}

void cloudTimer(int dummy) {
    for (unique_ptr<Shape> &s : clouds) {
        // Move all the clouds to the left
        s->moveX(-1);
        // If a shape has moved off the screen
        if (s->getCenterX() < -20) {
            // Set it to the right of the screen so that it passes through again
            s->setCenterX(520);
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(50, cloudTimer, dummy);
}

void obstacleTimer(int dummy) {
    //Make the obstacles move
    for (int i = 0; i < obstacleBottom.size(); ++i) {
        // Move all the red buildings to the left
        obstacleBottom[i].moveX(-3);
        // If a shape has moved off the screen
        if (obstacleBottom[i].getCenterX() < -(obstacleBottom[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? obstacleBottom.size()-1 : i - 1;
            obstacleBottom[i].setCenterX(obstacleBottom[buildingOnLeft].getCenterX() + obstacleBottom[buildingOnLeft].getWidth()/2 + obstacleBottom[i].getWidth()/2 + 150);
            //Add to the score each time an obstacle leaves the screen
            if(screenNum == gameScreen){
                score++;
            }
        }
    }
    for (int i = 0; i < obstacleTop.size(); ++i) {
        // Move all the red buildings to the left
        obstacleTop[i].moveX(-3);
        // If a shape has moved off the screen
        if (obstacleTop[i].getCenterX() < -(obstacleTop[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? obstacleTop.size()-1 : i - 1;
            obstacleTop[i].setCenterX(obstacleTop[buildingOnLeft].getCenterX() + obstacleTop[buildingOnLeft].getWidth()/2 + obstacleTop[i].getWidth()/2 + 150);
        }
    }

    //Make the outlines move
    for (int i = 0; i < bottomOutline.size(); ++i) {
        // Move all the red buildings to the left
        bottomOutline[i].moveX(-3);
        // If a shape has moved off the screen
        if (bottomOutline[i].getCenterX() < -(bottomOutline[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? obstacleBottom.size()-1 : i - 1;
            bottomOutline[i].setCenterX(obstacleBottom[buildingOnLeft].getCenterX() + obstacleBottom[buildingOnLeft].getWidth()/2 + obstacleBottom[i].getWidth()/2 + 150);
        }
    }
    for (int i = 0; i < topOutline.size(); ++i) {
        // Move all the red buildings to the left
        topOutline[i].moveX(-3);
        // If a shape has moved off the screen
        if (topOutline[i].getCenterX() < -(topOutline[i].getWidth()/2)) {
            // Set it to the right of the screen so that it passes through again
            int buildingOnLeft = (i == 0) ? obstacleTop.size()-1 : i - 1;
            topOutline[i].setCenterX(obstacleTop[buildingOnLeft].getCenterX() + obstacleTop[buildingOnLeft].getWidth()/2 + obstacleTop[i].getWidth()/2 + 150);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, obstacleTimer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    //Run all of the init functions
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("DefinitelyNotFlappyBird" /* title */ );
    
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
    glutTimerFunc(0, cloudTimer, 0);
    glutTimerFunc(0, obstacleTimer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
