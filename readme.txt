## Group 20 ##

1/ Grammar expansion
LindenmayerSystemDeterministic::expandSymbol
Given a character input, we can search whether this input is presented in the rules by callig "this->rules" and using "find" method according to the hint. If it is, we can simply replace this character by its rule. Otherwise we just leave the character unchanged and return it.

LindenmayerSystem::expandOnce
This method expands once the whole sequence. So we did a for loop. We go through all characters of the sequence and apply each character to the expandSymbol method. Finally we output the new sequence.

LindenmayerSystem::expand
We have to expand the input sequence several time which is determined by num_iters. As usual, we created a for loop on num_iters. And thanks to expandOnce method, we can update sequence each time. Finally we output the new sequence, after num_iters iterations.


2/ Drawing
For this function, we simply take care of the cases when the character is + or - by updating an "angle" value, and the cases where we need to advance our pencil by 1 using a segment (a,b) where a is the previous pencil position and b is the current pencil positions,
then we compute the next pencil position "n" by translating (cos(angle), sin(angle)) by b (in other words we take one step of length 1 in the direction of "angle" starting from b). We then only need to replace our segment (a,b) by (b, n).
As for brackets, we trivialy stack our segment variable along with the current angle when the bracket is openning, and pop and assign the segment and angle variables at the top of the stack to our inner varaibles, and keep going from there.
Stacking angles is possible to avoid by recomputing the angle of the segment poped from the stack but we preferred trading memory to avoid making additional calls to acos and asin functions wich are costly.



3/ Understanding the expansion rules
Found the rules and create the Json file necessary to the creation of the exemple.
To solve the formulas, we used the seed and seed generator way of thinking.

4/ Stochastic systems
We firstly created an instance of Dice in order to use "roll" method. The number returned by "roll" is uniformly distributed from 0 and 1. So the probabilty that this number is greater or smaller than 0.5 is half half. Using this property, we say that is this number is greater than (or equal) 0.5, the rule become F+F, otherwise the rule is F-F.



Fraction of the total workload for each project member :
Mohamed: 33%
Paul: 33%
Xiaoyan: 33%


