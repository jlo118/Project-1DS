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
	void pickfloors(list<request>& wait); ///First
	//Go to floor
	void gotofloor(queue<int> &up_down); ///Third
	void whereto(queue<int> &up_down); //optional
	//Sort up and down queues
	void sortqueue(queue <int> &up_down); ///Second
	void avg_wait_time(vector<int> avgwait); ///Outputs the average wait for each rider
	bool getdirection() {
		return direction;
	}
	int getfloor() {
		return current_floor;
	}
};

void elevator::whereto(queue<int> &up_down) {
	//Takes floor request after people boarded
	int destination;
	cin >> destination;
	up_down.push(destination);
}


void elevator::pickfloors(list<request>& wait) {
	bool change = false; // Determines if sort function is called
	if (!wait.empty()) {
		for (ptr = wait.begin(); ptr != wait.end();) {
			//If elevator going up and floor and request going up
			if ((direction == 1) && ptr->direction == 1 && current_floor <= ptr->floor) {
				//If requested floor is higher than current floor
				//Add requested floor to queue
				up.push(ptr->floor);
				//whereto(up);

				//Remove requested floor from wait list
				direction = 1; //going up
				change = true;
				passengers.push_back(*ptr);
				temp = ptr;
				ptr++;
				wait.erase(temp);
			}

			//If elevator going down
			else if ((direction == -1) && ptr->direction == -1 && current_floor >= ptr->floor) {
				down.push(ptr->floor);
				//whereto(down);

				change = true;
				direction = -1; //going down
				temp = ptr;
				passengers.push_back(*ptr);
				ptr++;
				wait.erase(temp);
			}
			//Handles when the elevator is idle
			else if (direction == 0) {
				if (ptr->direction == 1) {
					up.push(ptr->floor);
					//whereto(up);

					//Remove requested floor from wait list
					direction = 1; //going up
					change = true;
					temp = ptr;
					passengers.push_back(*ptr);
					ptr++;
					wait.erase(temp);
				}
				else if (ptr->direction == -1) {
					down.push(ptr->floor);
					//whereto(down);

					change = true;
					direction = -1; //going down
					temp = ptr;
					passengers.push_back(*ptr);
					ptr++;
					wait.erase(temp);
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
		//Tells elevator to move floors up or down and counts floors traveled
		if (direction == 1) {
			for (list<request>::iterator itr = passengers.begin(); itr != passengers.end();) {
				if (current_floor != itr->floor) {
					itr->floorstraveled += 1;
					itr++;
				}
				else if (current_floor == itr->floor) {
					avgwait.push_back(itr->floorstraveled);
					temp = itr;
					itr++;
					passengers.erase(temp);
				}
			}
			gotofloor(up);
		}
		else if (direction == -1) {
			for (list<request>::iterator itr = passengers.begin(); itr != passengers.end();) {
				if (current_floor != itr->floor) {
					itr->floorstraveled += 1;
					itr++;
				}
				else if (current_floor == itr->floor) {
					avgwait.push_back(itr->floorstraveled);
					temp = itr;
					itr++;
					passengers.erase(temp);
				}
			}
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