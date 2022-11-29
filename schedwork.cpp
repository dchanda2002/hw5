

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t row, size_t column);

bool isValid(
    const DailySchedule& sched,
    const size_t maxShifts,
    const Worker_T worker);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    std::vector<Worker_T> firstRow;
    sched.push_back(firstRow);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);

}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, 
    size_t row, size_t column)
{

		// if exceeding the size of the schedule, return true. Successfully
		// populated the whole schedule.
    if(row + 1 > avail.size()){
        sched.pop_back();
        return true;
    }

		// if incrementing past the column edge, increment to next row.
    if(column + 1 > dailyNeed){
        std::vector<Worker_T> nextRow;
				
				// push back a new row to the schedule before recursing (and undo
				// if the resulting schedule was unsuccessful)
        sched.push_back(nextRow);
        bool result = scheduleHelper(avail, dailyNeed, maxShifts, sched, row + 1, 0);
        if(!result){
            sched.pop_back();
        } else {
            return result;
        }
    }

    // for each worker
    for(unsigned int i = 0; i < avail[row].size(); i++){
        if(avail[row][i]){ 
            bool notAlreadyWorked = (std::find(sched[row].begin(), sched[row].end(), i) == sched[row].end());
            if(isValid(sched, maxShifts, i) && notAlreadyWorked){ 
								// push back a new value to the schedule before recursing (and undo
								// if the resulting schedule was unsuccessful)
								sched[row].push_back(i);
                bool result = scheduleHelper(avail, dailyNeed, maxShifts, sched, row, column + 1);
                if(!result){
                    sched[row].pop_back();
                } else {
                    return result;
                }
            }
        }
    }

    return false;

}

// checks if the worker is below their maximum shifts or not
bool isValid(
    const DailySchedule& sched,
    const size_t maxShifts,
    const Worker_T worker)
{
    unsigned int countShifts = 0;
    for(unsigned int i = 0; i < sched.size(); i++){
        for(unsigned int j = 0; j < sched[i].size(); j++){
            if(sched[i][j] == worker){
                countShifts++;
            }
        }
    }

    return countShifts < maxShifts;
}


