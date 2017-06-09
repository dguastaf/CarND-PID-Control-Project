#ifndef PID_H
#define PID_H

#include <vector>

class PID {
public:
  /*
  * Constructor
  */
  PID() : coef(3) {}

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double kp, double ki, double kd);

  double Run(double cte);

  double AvgError();

  void ResetTwiddle();

  int StepCount();

  void Twiddle();

private:
  double total_cte;
  double prev_cte;
  double previous_time;
  
  int totalSteps;
  bool firstTwiddle;
  bool twiddleUp;
  int twiddlePos;
  double bestErr;

  /*
  * Errors
  */
  std::vector<double> dp = {1.0, 1.0, 1.0};

  /*
  * Coefficients
  */ 
  std::vector<double> coef;

};

#endif /* PID_H */
