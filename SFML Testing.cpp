#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

//The height and length of the grid
int heightCount = 20; // vertical count
int widthCount = 20; //horizontal count

int pixelSize = 16; //size of a pixel
int height = pixelSize * heightCount; //making background pixels
int width = pixelSize * widthCount; // making background pixels

int random; //random number to simulate encounters

bool upFlag; //if player is moving up
bool downFlag; // if player is moving down
bool leftFlag; // if player is moving left
bool rightFlag; // if player is moving right
bool encounter = false; //flag is for random encounter
bool isMoving; //flag for when player is moving
bool collision = false; //flag for when collision occurs
bool walls[20][20] = {false}; // wall flag for each tile all are false

//Player action flags
bool playerTurn; //turn of player
bool playerSword = false; //if sword is used
bool playerPunch = false; //if punch is used
bool playerDefend = false; //if defend is used

bool skeleton = false; //there is a skeleton
bool orc = false; //there is a orc
bool alive = true; //flag for if player is alive
bool enemyDefeated = false;// flag for when enemy dies
							 
bool threeWayWall = true; //flag to display the correct corrdior image
bool corridor = false;
bool twoEndWalls = false;
bool leftCorners = false;
bool rightCorners = false;
// set border in the grid
void setBorder(){
	for (int i = 0; i < widthCount; i++) 
	{
		walls[0][i] = true;
		walls[i][0] = true;
		walls[widthCount - 1][i] = true;
		walls[i][widthCount - 1] = true;
	}
}
//struct for human 
struct Player
{
	int x; //x cordinate of player
	int y; //y cordinate of player
	int health = 100; //health of player
	int swordDamage = 30;
	int punchDamage = 15;
}player[1]; //the human only takes one pixel cordinate

struct Orc 
{
	int health = 100; //health of orc
	int damage = 20;
}enemyOrc[1];
struct Skeleton
{
	int health = 25;
	int damage = 5;
}enemySkeleton[1];

//checks if player is at a wall
void checkCollision() {
	if (walls[player[0].x][player[0].y] == true)
	{
		std::cout << "There is a wall";
		collision = true;
	}
	else
	{
		std::cout << "there is no wall";
		collision = false;
	}
}
// resets all of the movements
void resetMovementFlag() 
{
	upFlag = false; //once moved resets direction value
		//Ensures no other movement is taken
	downFlag = false;
	leftFlag = false;
	rightFlag = false;
}
//what enemy type starts the encounter
void battle() {
	int damage;
	while (encounter == true)
	{
		playerTurn == true;

		if (playerTurn == true && enemyDefeated == false)
		{
			if (playerSword == true)
			{
				damage = player[0].swordDamage;
				enemyOrc[0].health = enemyOrc[0].health - damage;
				if (enemyOrc[0].health < 0)
				{
					enemyDefeated = true;
					encounter = false;
				}
			}
			else if (playerPunch == true)
			{
				damage = player[0].punchDamage;
				enemyOrc[0].health = enemyOrc[0].health - damage;
				if (enemyOrc[0].health < 0)
				{
					enemyDefeated = true;
					encounter = false;
				}
			}
		}
		else
		{
			damage = enemyOrc[0].damage;
			player[0].health = player[0].health - damage;
			if (player[0].health < 0) {
				alive = false;
			}
		}
	}
}
void encounterType() 
{
	int type = (rand() % 100) + 1;
	if (type < 50) 
	{
		skeleton = true;
		battle();
	}
	else 
	{
		orc = true;
		battle();
	}
}
//generates a random encounter
void generateEncounter() 
{
	random = (rand() % 100) + 1; //gets random number between 1-100
	if (random < 50) // sets rate to occur at 50%
	{
		encounter = true;
		encounterType(); //when a encounter happens what kind.
	}
}
//checks if walls already exists
int checkWall(int wallCount) 
{
	//if the wall above is true
	if (walls[player[0].x][player[0].y - 1] == true)
	{
		wallCount++;
	}
	//check below player for wall
	if (walls[player[0].x][player[0].y + 1] == true)
	{
		wallCount++;
	}
	//checks to the right of the player
	if (walls[player[0].x + 1][player[0].y] == true)
	{
		wallCount++;
	}
	//checks to the left of the player
	if (walls[player[0].x - 1][player[0].y] == true)
	{
		wallCount++;
	}
	return wallCount;
}

void upFlagCorridor() 
{
	//if block ahead is a wall and the two sides are not it is for twoEndWall
	if (walls[player[0].x][player[0].y - 1] == true && walls[player[0].x - 1][player[0].y] == false && walls[player[0].x + 1][player[0].y] == false) 
	{
		twoEndWalls = true;
	}
	else if (walls[player[0].x][player[0].y - 1] == false && walls[player[0].x - 1][player[0].y] == true && walls[player[0].x + 1][player[0].y] == true)
	{
		corridor = true;
	}
	else if (walls[player[0].x][player[0].y - 1] == true && walls[player[0].x + 1][player[0].y] == true && walls[player[0].x - 1][player[0].y] == false)
	{
		leftCorners = true;
	}
	else if (walls[player[0].x][player[0].y - 1] == true && walls[player[0].x - 1][player[0].y] == true && walls[player[0].x + 1][player[0].y] == true)
	{
		rightCorners = true;
	}
	else 
	{
		threeWayWall = true;
	}

}
void downFlagCorridor() 
{
	//if block ahead is a wall and the two sides are not it is for twoEndWall
	if (walls[player[0].x][player[0].y + 1] == true && walls[player[0].x - 1][player[0].y] == false && walls[player[0].x + 1][player[0].y] == false)
	{
		twoEndWalls = true;
	}
	//if there is no wall ahead but walls surrounding it is a corridor
	else if (walls[player[0].x][player[0].y + 1] == false && walls[player[0].x - 1][player[0].y] == true && walls[player[0].x + 1][player[0].y] == true)
	{
		corridor = true;
	}
	else if (walls[player[0].x][player[0].y + 1] == true && walls[player[0].x + 1][player[0].y] == true && walls[player[0].x - 1][player[0].y] == false)
	{
		rightCorners = true;
	}
	else if (walls[player[0].x][player[0].y + 1] == true && walls[player[0].x - 1][player[0].y] == true)
	{
		leftCorners = true;
	}
	else
	{
		threeWayWall = true;
	}

}
void rightFlagCorridor() 
{
	//if block ahead is a wall and the two sides are not it is for twoEndWall
	if (walls[player[0].x + 1][player[0].y] == true && walls[player[0].x][player[0].y + 1] == false && walls[player[0].x][player[0].y - 1] == false)
	{
		twoEndWalls = true;
	}
	else if (walls[player[0].x + 1][player[0].y] == false && walls[player[0].x][player[0].y + 1] == true && walls[player[0].x][player[0].y - 1] == true)
	{
		corridor = true;
	}
	else if (walls[player[0].x + 1][player[0].y] == true && walls[player[0].x][player[0].y + 1] == true && walls[player[0].x][player[0].y - 1] == false)
	{
		leftCorners = true;
	}
	else if (walls[player[0].x + 1][player[0].y] == true && walls[player[0].x][player[0].y - 1] == true && walls[player[0].x][player[0].y + 1] == false)
	{
		rightCorners = true;
	}
	else
	{
		threeWayWall = true;
	}
}
//left flag display
void leftFlagCorridor() 
{
	//if block ahead is a wall and the two sides are not it is for twoEndWall
	if (walls[player[0].x - 1][player[0].y] == true && walls[player[0].x][player[0].y - 1] == false && walls[player[0].x][player[0].y + 1] == false)
	{
		twoEndWalls = true;
	}
	else if (walls[player[0].x - 1][player[0].y] == false && walls[player[0].x][player[0].y - 1] == true && walls[player[0].x][player[0].y + 1] == true)
	{
		corridor = true;
	}
	else if (walls[player[0].x - 1][player[0].y] == true && walls[player[0].x][player[0].y - 1] == true && walls[player[0].x][player[0].y + 1] == false)
	{
		leftCorners = true;
	}
	else if (walls[player[0].x - 1][player[0].y] == true && walls[player[0].x][player[0].y + 1] == true && walls[player[0].x][player[0].y - 1] == false)
	{
		rightCorners = true;
	}
	else
	{
		threeWayWall = true;
	}
}
//makes walls as we move 
void generateWall() 
{
	int wallCount = 0; //counts how many walls already exists checks to avoid trapping player
	int wallChance; //chance for a wall to appear
	//until there are two walls
	while (wallCount < 2) {
		//check above player for wall
		wallCount = checkWall(wallCount); //goes to check if all wall count is good
		//cannot add wall below
		if (upFlag == true)
		{
			//if there is no wall and the count is still less than 3
			if (walls[player[0].x][player[0].y - 1] == false && wallCount < 2) 
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{

					walls[player[0].x][player[0].y - 1] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x + 1][player[0].y] == false && wallCount < 2) 
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x + 1][player[0].y] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x - 1][player[0].y] == false && wallCount < 2) 
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x - 1][player[0].y] = true;
					wallCount++;
				}
			}
		}
		//no wall above
		if (downFlag == true)
		{
			//if there is no wall and the count is still less than 3
			if (walls[player[0].x][player[0].y + 1] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x][player[0].y + 1] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x + 1][player[0].y] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x + 1][player[0].y] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x - 1][player[0].y] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x - 1][player[0].y] = true;
					wallCount++;
				}
			}
		}
		//no wall to the left
		if (rightFlag == true)
		{
			//if there is no wall and the count is still less than 3
			if (walls[player[0].x][player[0].y + 1] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x][player[0].y + 1] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x][player[0].y - 1] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x][player[0].y -1] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x + 1][player[0].y] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x + 1][player[0].y] = true;
					wallCount++;
				}
			}
		}
		//no wall to the right
		if (leftFlag == true)
		{
			//if there is no wall and the count is still less than 3
			if (walls[player[0].x][player[0].y - 1] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x][player[0].y - 1] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x][player[0].y + 1] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x][player[0].y + 1] = true;
					wallCount++;
				}
			}
			if (walls[player[0].x - 1][player[0].y] == false && wallCount < 2)
			{
				wallChance = (rand() % 100) + 1; //gets random number between 1-100
				if (wallChance < 20) // sets rate to occur at 50%
				{
					walls[player[0].x - 1][player[0].y] = true;
					wallCount++;
				}
			}
		}
	}
}
//move for the human to move to different spaces
void move()
{
	//there is no encounter until after movement
	encounter = false; 
	//resetCorridorFlag(); //resets the corridor image
	threeWayWall = false; //flag to display the correct corrdior image
	corridor = false;
	twoEndWalls = false;
	leftCorners = false;
	rightCorners = false;
	if (upFlag) 
	{	
		upFlagCorridor();
		player[0].y = player[0].y - 1; //up movement
		//upFlagCorridor();
		checkCollision();
		if (collision == true) //undoes the action
		{
			player[0].y = player[0].y + 1;
		}
		generateWall();
		resetMovementFlag();
		generateEncounter();
	}
	//if user presses down
	else if (downFlag) 
	{
		downFlagCorridor();
		player[0].y = player[0].y + 1; //down movement
		//downFlagCorridor();
		checkCollision();
		if (collision == true) //undoes the action
		{

			player[0].y = player[0].y - 1;
		}
		generateWall();
		resetMovementFlag();
		generateEncounter();
	}
	//if user presses left
	else if (leftFlag)
	{
		//leftFlagCorridor();
		player[0].x = player[0].x - 1; //left movement
		leftFlagCorridor();
		checkCollision();
		if (collision == true) //undoes the action
		{
			player[0].x = player[0].x + 1;
		}
		generateWall();
		resetMovementFlag();
		generateEncounter();
	}
	//if user presses right
	else if (rightFlag)
	{
		//rightFlagCorridor();
		player[0].x = player[0].x + 1;  //right movement
		rightFlagCorridor();
		checkCollision();
		if (collision == true) //undoes the action
		{
			player[0].x = player[0].x - 1;
		}
		generateWall();
		resetMovementFlag();
		generateEncounter();
	}
}

//launches the move function by checking if player is moving
void moving()
{
	//player is moving
	if (isMoving)
	{
		//resets movement state
		isMoving = false;
		move();
	}
}
// has to check the collison if the space is a wall before moving

int main()
{
	setBorder(); //sets the border for the wall
	//Window to play the game in set to be as large as the pixels displaying name.
	sf::RenderWindow background(sf::VideoMode(940, 540, 32), "World View");
	sf::RenderWindow window(sf::VideoMode(width, height,16), "Map");
	sf::Texture human, map, wall; //for player, grid, and walls
	sf::Texture threeCorridor,Corridor,twoEndWall,leftCorner,rightCorner; //3d pics of halls
	sf::Texture battleSkeleton, battleOrc;
	sf::Texture deathOrc, deathSkeleton;
	sf::Texture punchOrc, punchSkeleton;
	sf::Texture swordOrc, swordSkeleton;
	
	battleSkeleton.loadFromFile("images/PlayerSkeletonIdle.png");
	battleOrc.loadFromFile("images/PlayerOrcIdle.png");

	deathOrc.loadFromFile("images/PlayerLossScreenOrc.png");
	deathSkeleton.loadFromFile("images/PlayerLossScreenSkeleton.png");

	punchOrc.loadFromFile("images/PlayerPunchingOrc.png");
	punchSkeleton.loadFromFile("images/PlayerPunchingSkeleton.png");

	swordOrc.loadFromFile("images/PlayerSwordOrc.png");
	swordSkeleton.loadFromFile("images/PlayerSwordSkeleton.png");
	//start in x and y then width and height
	threeCorridor.loadFromFile("images/3wayWall.png");
	Corridor.loadFromFile("images/Corridor.png");
	twoEndWall.loadFromFile("images/twoEndWall.png");
	leftCorner.loadFromFile("images/leftCorner.png");
	rightCorner.loadFromFile("images/rightCorner.png");
	

	map.loadFromFile("images/white.png"); //loads white for map tiles
	human.loadFromFile("images/red.png"); //loads red for human
	wall.loadFromFile("images/green.png"); //use green for walls
	//add wall pixels to with collsion

	//takes the loaded image and makes sprites
	sf::Sprite mapSprite(map); //grid tiles
	sf::Sprite humanSprite(human); //human spot
	//sprites for the hallways
	sf::Sprite threeCorridorSprite(threeCorridor);
	sf::Sprite CorridorSprite(Corridor);
	sf::Sprite twoEndWallSprite(twoEndWall);
	sf::Sprite leftCornerSprite(leftCorner);
	sf::Sprite rightCornerSprite(rightCorner);

	sf::Sprite orcSprite(battleOrc);
	sf::Sprite skeletonSprite(battleSkeleton);

	sf::Sprite punchOrcSprite(punchOrc);
	sf::Sprite punchSkeletonSprite(punchSkeleton);

	sf::Sprite swordOrcSprite(swordOrc);
	sf::Sprite swordSkeletonSprite(swordSkeleton);

	sf::Sprite deathToOrcSprite(deathOrc);
	sf::Sprite deathToSkeletonSprite(deathSkeleton);
	sf::Sprite wallSprite(wall); //wall spot
	threeCorridorSprite.setPosition(0, 0);
	
	//Place human into inital spot
	player[0].x = 5;
	player[0].y = 5;

	//adds a clock
	sf::Clock clock;
	float timer = 0.0f;
	float delay = 0.4f;

	while (window.isOpen())
	{
		//check how this works
		float time = clock.getElapsedTime().asSeconds();
		clock.restart(); //resets the time after getting time 
		timer = timer + time; //updating the timer with time as passed
		//names the event userInput
		sf::Event exit;
		while (window.pollEvent(exit))
		{
			//if user closes the window
			if (exit.type == sf::Event::Closed)
				window.close();
			//Event for pressed key
			//when user input is not inputed anymore
		}
		while (background.pollEvent(exit)) 
		{
			if (exit.type == sf::Event::Closed)
				background.close();
		}
		//controls for player
		//Sets a flag to move
		//set key will not repeat
		//window.setKeyRepeatEnabled(false);
		//if a key is pressed
		if (exit.type == sf::Event::KeyPressed) {
			if (exit.key.code == sf::Keyboard::A) 
			{
				playerSword == true;
			}
			else if(exit.key.code == sf::Keyboard::S) 
			{
				playerPunch == true;
			}
			else if (exit.key.code == sf::Keyboard::D) 
			{
				playerDefend == true;
			}
		}
		if(exit.type == sf::Event::KeyPressed)
		{
			if (exit.key.code == sf::Keyboard::Up)
			{
				isMoving = true;
				upFlag = true;
			}
			else if (exit.key.code == sf::Keyboard::Down)
			{
				isMoving = true;
				downFlag = true;
			}
			else if (exit.key.code == sf::Keyboard::Left)
			{
				isMoving = true;
				leftFlag = true;
			}
			else if (exit.key.code == sf::Keyboard::Right)
			{
				isMoving = true;
				rightFlag = true;
			}
		}
		
		if (timer > delay) //every delay or frame
		{
			timer = 0; //resets timer
			moving(); //calls move functions
		}
		//draws the state 
		background.clear();
		if (threeWayWall == true) {
			background.clear();
			background.draw(threeCorridorSprite);
		}
		if (corridor == true) {
			background.clear();
			background.draw(CorridorSprite);
		}
		if (twoEndWalls == true) {
			background.clear();
			background.draw(twoEndWallSprite);
		}
		if (leftCorners == true) {
			background.clear();
			background.draw(leftCornerSprite);
		}
		if (rightCorners == true) {
			background.clear();
			background.draw(rightCornerSprite);
		}
		if (orc == true) 
		{
			background.clear();
			background.draw(orcSprite);
			if (alive == false) 
			{
				background.clear();
				background.draw(deathToOrcSprite);
			}
		}
		if (skeleton == true) 
		{
			background.clear();
			background.draw(skeletonSprite);
			if (alive == false) 
			{
				background.clear();
				background.draw(deathToSkeletonSprite);
			}
		}
		background.display();
		window.clear(); // clears window of previous pictures
		//window.draw(shape); // draws shape
		//draw the pixels for grid background
		
		for (int i = 0; i < widthCount; i++)
		{
			for (int j = 0; j < heightCount; j++) 
			{
				//sets the position of each sprite pixel by pixel
				mapSprite.setPosition(i*pixelSize, j*pixelSize);
				window.draw(mapSprite);
			}
		}

		//draw the human onto the map
		humanSprite.setPosition(player[0].x*pixelSize, player[0].y*pixelSize);
		//sets the wall 
		for (int i = 0; i < widthCount; i++) 
		{	
			for (int j = 0; j < heightCount; j++) 
			{
				if (walls[i][j] == true) 
				{
					wallSprite.setPosition(i*pixelSize, j*pixelSize);
					window.draw(wallSprite);
				}
			}
		}
		window.draw(humanSprite);
		window.display(); //displays all images
	}
	return 0;
}