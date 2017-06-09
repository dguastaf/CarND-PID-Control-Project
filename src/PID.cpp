#include "PID.h"
#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::~PID() {}

void PID::Init(double kp, double ki, double kd) {

    coef[0] = kp;
    coef[1] = ki;
    coef[2] = kd;

    prev_cte = 0;
    total_cte = 0;
    previous_time = clock();

    twiddleUp = true;
    twiddlePos = 0;
    firstTwiddle = true;
    totalSteps = 0;
}

double PID::Run(double cte) {
    totalSteps++;

    double current_time = clock();
    double dt = (current_time - previous_time)/CLOCKS_PER_SEC;
    cout << "DT " << dt << endl;
    previous_time = current_time;

    // cout << "CTE " << cte << endl;
    cout << "Prev cte " << prev_cte << endl;
    double diff_cte = cte - prev_cte;
    total_cte += cte;
    
    cout << "Diff " << diff_cte << endl;
    cout << "Total " << total_cte << endl;
    
    prev_cte = cte;

    double p = coef[0] * cte;
    double i = coef[1] * total_cte;
    double d = coef[2] * diff_cte / dt;

    return -p - i - d;
}

double PID::AvgError() {
    return std::abs(total_cte / totalSteps);
}

void PID::Twiddle() {
    if (firstTwiddle) {
        bestErr = AvgError();
        firstTwiddle = false;
        coef[twiddlePos] += dp[twiddlePos];

        cout << "First twiddle" << endl;
        return;
    }

    double err = AvgError();
    
    //We decreased the error! Increase probing range
    if (err < bestErr) {
        bestErr = err;
        dp[twiddlePos] *= 1.1;
        twiddlePos++;
        twiddleUp = true;
        coef[twiddlePos] += dp[twiddlePos];
        cout << "Error decreased" << endl;
    } 
    // Error increased, try decreasing the hyperparam
    else if (twiddleUp) {
        coef[twiddlePos] -= 2 * dp[twiddlePos];
        twiddleUp = false;
        cout << "Error increased, trying to decrease hyperparam" << endl;
    } 
    // We already tried decreasing the hyperparam, but still didn't decrease 
    // the error. Decrease the probing range and move on to the next param
    else {
        coef[twiddlePos] += dp[twiddlePos];
        dp[twiddlePos] *= 0.9;
        twiddlePos++;
        twiddleUp = true;
        coef[twiddlePos] += dp[twiddlePos];
        cout << "Error increased again. moving hyperparam back and decreasing range" << endl;
    }

    cout << "dp ";
    for (int i = 0; i < dp.size(); i++) {
        cout << dp[i] << " ";
    }
    cout << endl;
    
    cout << "coef ";
    for (int i = 0; i < coef.size(); i++) {
        cout << coef[i] << " ";
    }
    cout << endl;

    cout << "err " << err << endl;
    cout << "pos " << twiddlePos << endl;
    cout << "twiddleUp " << twiddleUp << endl;
    cout << endl; 
}

void PID::ResetTwiddle() {
    prev_cte = 0;
    total_cte = 0;
    totalSteps = 0;
}

int PID::StepCount() {
    return totalSteps;
}

