## Discrete Bayes filter using Arduino and two Ultrasonic Ranging Modules

The goal of this project is use Arduino and two ranging sensors to do some simple localization in an enclosed environment. Essentially, we are trying to bring somem of the simple examples done in class to life. The localization method is the "Discrete Bayes Filter", a method of determining where an agent is on a map using Baye's rule and discrete probability.

The map we are using is essentially one dimensional. In real life, it is a box with two ends, which the ranging sensors can detect using what is essentially echolocation. We represent this mini environment as a 1D array in the programming environment.

*Note: We are not aiming to do more complicated things like particle filters simply because of time constraints.*
