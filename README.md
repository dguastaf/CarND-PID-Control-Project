# Self Driving Car PID Controller
Self-Driving Car Engineer Nanodegree Program

---

This is a very simple PID controller that controls a self dirving car's steering angle. 

## Writeup
The hyperparameters were tuned manually using multiple trial runs.  

The P parameter controls recovering once the car goes off center. If the P value is low, it drifts easily and doesn't go back to center quickly. However if it's high, it tends to overcompensate and has a hard time getting back to center once it drifts.  
The I parameter adds extra bias for if the car has been off center for a while. So when the cumulative error is high for a sustained period, this part of the controller will bring the car back to center.  
The D parameter dictates how sensitive the steeering is if the car is off center. If it's high, it's super sensitive and jitters a lot. However if it's too low it doesn't recover fast enough and the car will drive off the road.

## Future Work
The code has some logic to use the Twiddle algorithm to tune the hyperparameters. However, it's not working in its current state. In the future I'd like to use to make sure the hyperparameters are as finely tuned as possible.

