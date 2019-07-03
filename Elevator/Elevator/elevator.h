#pragma once
#include <queue>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include "request.h"
#include <algorithm>
using namespace std;

class elevator {
private:
	int current_floor = 0;
	int direction = 0; //1 means Up, -1 means down, 0 means idle
	queue<int> up; //sort ascending order
	queue<int> down; //sort descending order
	list<request> passengers; //updates wait time by floor until people are picked up and adds values to vector
	list<request>::iterator ptr;
	list<request>::iterator temp;
public:
	//Scans wait list for floor waiting to be picked up
	void pickfloors(list<request>& wait); //First- Handles the operation of everything // Picks Floors, Sorts Queue
	//Go to floor
	void gotofloor(queue<int> &up_down); //Third
	//Sort up and down queues
	void sortqueue(queue <int> &up_down); //Second
	void avg_wait_time(vector<int> avgwait); //Outputs the average wait for each rider
	bool getdirection() {return direction;} //returns diretion
	int getfloor() {return current_floor;} //returns current_floor
	void goelevgo(queue<int>& up_down, list<request>::iterator &ptr, bool &change); //Handles taking floors from wait list
	void update_passenger_wait_time();
};

void elevator::update_passenger_wait_time() {
	for (list<request>::iterator itr = passengers.begin(); itr != passengers.end();) {
		if (current_floor != itr->floor) {
			itr->floorstraveled += 1;
			itr++;
		}
		else if ((current_floor == itr->floor) && (direction == itr->direction)) {
			avgwait.push_back(itr->floorstraveled);
			temp = itr;
			itr++;
			passengers.erase(temp);
		}
	}
}

void elevator::goelevgo(queue<int>& up_down, list<request>::iterator &ptr, bool &change) {
	//If requested floor is higher than current floor
	//Add requested floor to queue
	up_down.push(ptr->floor);
	//Add destination to queue
	up_down.push(ptr->whereto);
	change = true; //Run sort
	//Remove requested floor from wait list
	passengers.push_back(*ptr);
	temp = ptr;
	ptr++;
	wait.erase(temp);
}

void elevator::pickfloors(list<request>& wait) {
	bool change = false; // Determines if sort function is called
	if (!wait.empty()) {
		for (ptr = wait.begin(); ptr != wait.end();) {
			//If elevator going up and floor and request going up
			if ((direction == 1) && ptr->direction == 1 && current_floor <= ptr->floor) {
				goelevgo(up,ptr, change);
				direction = 1; //going up
			}

			//If elevator going down
			else if ((direction == -1) && ptr->direction == -1 && current_floor >= ptr->floor) {
				goelevgo(down, ptr, change);
				direction = -1; //going down
			}
			//Handles when the elevator is idle
			else if (direction == 0) {
				if (ptr->direction == 1) {
					direction = 1; //going up
					goelevgo(up, ptr, change);
				}
				else if (ptr->direction == -1) {
					direction = -1; //going down
					goelevgo(down, ptr, change);
				}
			}
			else {
				ptr++;
			}
		}
		//Sort queues after picking wait list
		if (change == true) {
			if (direction == 1) {
				sortqueue(up);
			}
			else if (direction == -1) {
				sortqueue(down);
			}
		}
		//Tells elevator to move floors up or down and counts floors_traveled_wait_timeupdates passenger request
		if (direction == 1) {
			update_passenger_wait_time(); //Update the wait time of each passenger and when they board elevator push into a vector to average
			gotofloor(up);
		}
		else if (direction == -1) {
			update_passenger_wait_time();
			gotofloor(down);
		}
	}

}

void elevator::gotofloor(queue<int> &up_down) {
	if (!up_down.empty()) {
		//Go to next floor
		current_floor = up_down.front();
		up_down.pop();
	}
	else if (up_down.empty() == true) {
		direction = 0; //elevator is idle
	}
}

void elevator::sortqueue(queue<int> &up_down) {
	vector<int> temp;
	if (direction == 1) {
		while (!up.empty()) {
			temp.push_back(up.front());
			up.pop();
		}
		sort(temp.begin(), temp.end());

		for (size_t i = 0; i < temp.size(); i++) {
			up.push(temp[i]);
		}
	}
	else if(direction == -1){
		while (!down.empty()) {
			temp.push_back(down.front());
			down.pop();
		}
		sort(temp.begin(), temp.end(), greater<int>());
		for (size_t i = 0; i < temp.size(); i++) {
			down.push(temp[i]);
		}
	}
	temp.clear();
}

void elevator::avg_wait_time(vector<int> avgwait) {
	int avgwaitsum = 0;
	for (unsigned i = 0; i < avgwait.size(); i++) {
		avgwaitsum += avgwait[i];
	}
	avgwaitsum = avgwaitsum / avgwait.size();
	cout << " The average wait for each person was " << avgwaitsum << " floors" << endl;
}