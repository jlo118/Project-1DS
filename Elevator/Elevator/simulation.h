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
	for (int k = 0; k < ppl_count; k++) {
		request* newrequest = new request();
		newrequest->floor = rand() % max_floor;

		//Handles edge cases for direction
		if (newrequest->floor == 0) {
			newrequest->direction = 1;
		}
		else if (newrequest->floor == max_floor) {
			newrequest->direction = -1;
		}
		else {
			temp = rand() & 1;
			if (temp == 1) {
				newrequest->direction = 1;
			}
			else if (temp == 0) {
				newrequest->direction = -1;
			}
		}
		//cout << newrequest->floor << " " << newrequest->begin << endl;
		wait.push_back(*newrequest);
	}
	while (!wait.empty()) {
		for (unsigned i = 0; i < elevators_v.size(); i++) {
			elevators_v[i].pickfloors(wait);
			cout << wait.size() << endl;
		}
	}
	cout << "DONE";
	elevators_v[0].avg_wait_time(avgwait);
}

//simulation timer