#include "sfwdraw.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

/*
+-------------+
| Player Info |
+-------------+
*/
struct Player
{
	int x, y;
	int score;
	bool hasCollided;
	int radius;
};


/*
+---------------+
| Asteroid Info |
+---------------+
*/
struct Asteroid
{
	bool isDead = false;
	float x, y, vX, vY = 0;
	int radius = 15; // 3, 2, 1
};

int nAsteroids = 0;
Asteroid aArray[256];

/*
+-----------+
| Functions |
+-----------+
*/
#pragma region Functions
void spawnSquare(int x, int y)
{
	sfw::drawLine(x, y, x, y + 30);
	sfw::drawLine(x, y, x + 30, y);
	sfw::drawLine(x + 30, y + 30, x, y + 30);
	sfw::drawLine(x + 30, y + 30, x + 30, y);
}

float addVelocity(float vectorX, float vectorY)
{
	float vX = rand() % (-1) + 1;
	float vY = rand() % (-1) + 1;
	vectorX = vX;
	vectorY = vY;
	return vectorX, vectorY;
}

bool isColliding(float aX, float aY, float bX, float bY, float r1, float r2)
{
	/*
	Code editted from code sample at http://cgp.wikidot.com/circle-to-circle-collision-detection 
	*/
	if (sqrt((bX - aX) * (bX - aX) + (bY - aY) * (bY - aY)) < (r1 + r2))
	{
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion

/*
+---------------------+
| MAIN FUNCTION START |
+---------------------+
*/
int main()
{
	srand(time(NULL));

	const int windowSizeX = 800;
	const int windowSizeY = 600;
	int counter = 0;
	bool isVulnerable = false;

	//player initialization
	Player pStats;
	pStats.x = windowSizeX / 2;
	pStats.y = windowSizeY / 2;
	pStats.radius = 10;
	pStats.score = 0;

	//asteroid initialization
	const int N_ROIDS = 8;
	Asteroid roids[N_ROIDS];
	
	//Spawning and giving initial values to asteroids
	for (int i = 0; i < N_ROIDS; ++i)
	{
		roids[i].x = rand() % 500 + 2;
		roids[i].y = rand() % 500 + 2;
		roids[i].vX = rand() % 1 + 2;
		roids[i].vY = rand() % 1 + 2;
		std::cout << "tempX = " << roids[i].x << "\ntempY =" << roids[i].y;
		nAsteroids++;
	}

	sfw::initContext(windowSizeX, windowSizeY, "Asteroid Weaver");
		while (sfw::stepContext())
		{
			sfw::drawCircle(pStats.x, pStats.y, 10);

			counter++;

			//asteroid update
			for (int i = 0; i <= N_ROIDS; ++i)
			{
				spawnSquare(roids[i].x, roids[i].y);
				addVelocity(roids[i].vX, roids[i].vY);

				roids[i].x += roids[i].vX;
				roids[i].y += roids[i].vY;

				//Asteroid acceleration
				if (counter % 120 == 0)
				{
					roids[i].vX += .2;
					roids[i].vY += .2;
				}

				//Asteroid Bounderies
				#pragma region Asteroid Bounderies
				if (roids[i].x + 30 >= windowSizeX)
				{
					roids[i].x = windowSizeX - 30;
					roids[i].x *= -1;
				}

				if (roids[i].x < 0)
				{
					roids[i].x = 0;
					roids[i].x *= -1;
				}

				if (roids[i].y + 30 >= windowSizeY)
				{
					roids[i].y = windowSizeY - 30;
					roids[i].y *= -1;
				}

				if (roids[i].y < 0)
				{
					roids[i].y = 0;
					roids[i].y *= -1;
				}
				#pragma endregion
			}

			//Scorekeeper
			pStats.score = counter / 60;
			if (counter % 60 == 0)
			{
				std::cout << pStats.score << "\n";
			}

			//Player Movement
			#pragma region pMovement
			if (sfw::getKey('w'))
			{
				pStats.y -= 4;
			}
			if (sfw::getKey('s'))
			{
				pStats.y += 4;
			}
			if (sfw::getKey('a'))
			{
				pStats.x -= 4;
			}
			if (sfw::getKey('d'))
			{
				pStats.x += 4;
			}
			#pragma endregion

			//Starting vulnerabilty
			if (counter == 30)
			{
				isVulnerable = true;
			}

			//Player/Asteroid Collision
			if (isVulnerable == true)
			{
				for (int i = 0; i <= N_ROIDS; ++i)
				{
					if (isColliding(pStats.x, pStats.y, roids[i].x, roids[i].y, pStats.radius, roids[i].radius) == true)
					{
						system("pause");
						return 0;
					}
				}
			}
		}
	sfw::termContext();
}