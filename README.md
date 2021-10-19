# Graphics1-eleonar1-jeconkli

This project is a game, similar to the popular mobile app, Flappy Bird.
The character is a bird, which the user must navigate up and down to avoid obstacles.
When the user passes through a set of objects, and those objects leave the left side of
the screen, a point is added to the user's score. All of the graphics in the project were
drawn using the OpenGL/GLUT framework.

To create the obstacles, two vectors of rectangles were created. The goal of these obstacles
was to create pairs of obstacles, one coming up from the bottom, while the other comes down from the top.
Then, the user would have to fly in between the sets of obstacles. To do this, the height of one
of the obstacles was randomly generated, and then the other obstacles height was created by subtracting
the screen height from the height of the first object.

To create the wings and beak, the Triangle class had to be created. Since the wings were going to be
in different shapes from the flying animation, 6 different draw functions were implemented. The first
5 draw the wings in different shapes throughout the flying animation, while the last one 
draws a beak shape.

To keep track of the high scores, a struct was used. Each highscore has an int and string, containing the score
and the username of the highscore. At the beginning of the file running, the scores are read out
of a file and into a vector. When a game ends, the score is tested against the scores in the vector.
If the score is high enough, the game brings the user to a high score screen, where the user is prompted
to enter a username. When the user enters their name and it is valid, they press enter and their
score is added to the leaderboard.

Since this project was a game, it felt redundant to include a testing program. The methods that were implemented
we're either entirely visual, such as the draw methods, or testable easily in the game, like the isOverlapping
methods in Rect. Everytime the game ends is clear evidence of the isOverlapping method properly functioning
because for the game to end, the bird must overlap with an obstacle.

The end product is a fully functioning, self contained game. All of the user inputs function in real
time to create a very user-friendly game that needs little explanation. To easily test the highscore
screen function, you can go into Highscores.txt and set one of the scores to 0. Our current high score
is 95, achieved by Ethan. See if you can beat it!