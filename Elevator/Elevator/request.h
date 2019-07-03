#pragma once

#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

vector <int> avgwait;

struct request {
	int floor =0; //Floor that its requested froom
	int direction = 0; //True means UP false means DOWN
	int floorstraveled = 0; //Wait Time
};

list <request> wait; // wait list of request