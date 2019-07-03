#pragma once
#include <ctime>
#include <iostream>
#include "elevator.h"
#include "request.h"
#include <iterator>
//Record
using namespace std;
vector <elevator> elevators_v;//all the elevators

void sim(int elev_count, int ppl_count, int max_floor) {
	int temp; //temp random value for direction bool
	//Make and push elevators into vector
	for (int i = 0; i < elev_count; i++) {
		elevators_v.push_back(elevator());
	}
	//Set random values for request structure
	for (int k = 0; k < ppl_count; k++) {
		request* newrequest = new request();
		//Set random start floor
		newrequest->floor = rand() % max_floor;

		//Handles edge cases for direction
		if (newrequest->floor == 0) {
			//If floor is 0 passenger has to go up
			newrequest->direction = 1;
			while (newrequest->whereto == 0) {
				newrequest->whereto = rand() % max_floor;
			}
		}
		else if (newrequest->floor == max_floor) {
			//If floor is max floor passenger has to go down
			newrequest->direction = -1;
			newrequest->whereto = rand() % (max_floor - 1);
		}

		else {
			//Set random direction for travel
			temp = rand() & 1;
			if (temp == 1) {
				//Going Up
				newrequest->direction = 1;
				//Set random desired floor to travel to
				newrequest->whereto = (rand() % (max_floor - newrequest->floor)) + newrequest->floor;
			}
			else if (temp == 0) {
				newrequest->direction = -1;
				newrequest->whereto = (rand() % (max_floor - newrequest->floor)) - newrequest->floor;
			}
		}
		//Add to waiting list
		wait.push_back(*newrequest);
	}
	while (!wait.empty()) {
		for (unsigned i = 0; i < elevators_v.size(); i++) {
			elevators_v[i].pickfloors(wait);
		}
	}
	cout << "DONE";
	elevators_v[0].avg_wait_time(avgwait);
}

//simulation timer