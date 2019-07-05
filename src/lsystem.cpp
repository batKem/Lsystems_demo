
#include "lsystem.h"
#include <stack>
#include <memory>
#include <iostream>

/*
Provided utilities:

- Dice class (utils/misc.h)
	Produces random values uniformly distributed between 0 and 1
	Example:
		Dice d;
		double random_val = d.roll();

- write_string_to_file (utils/misc.h)
	Write string data into a text file.
	Example:
		write_string_to_file("ala ma kota!", "ala.txt");
*/

std::string LindenmayerSystemDeterministic::expandSymbol(unsigned char const& sym) {
	/*============================================================
		TODO 1.1
		For a given symbol in the sequence, what should it be replaced with after expansion?
		The rules are in this->rules, see lsystem.h for details.
	*/

	auto c = this->rules.find(sym);
    if ( c != this->rules.end()) {
		return {this->rules.at(sym)};
	} else {
		return {char(sym)};
	}
	
	/*
	You may find useful:
		map.find: Iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
		http://en.cppreference.com/w/cpp/container/unordered_map/find
	============================================================
	*/
}

std::string LindenmayerSystem::expandOnce(std::string const& symbol_sequence) {
	/*============================================================
		TODO 1.2
		Perform one iteration of grammar expansion on `symbol_sequence`.
		Use the expandSymbol method
	*/

	std::string res= "";
	for (auto& c : symbol_sequence) {
    	res = res + expandSymbol(c);
	}
	return res;

	//============================================================
}

std::string LindenmayerSystem::expand(std::string const& initial, uint32_t num_iters) {
	/*============================================================
		TODO 1.3
		Perform `num_iters` iterations of grammar expansion (use expandOnce)
	*/

	std::string res = expandOnce(initial);
	for ( int i = 0; i < num_iters; ++i ) {
    	res = expandOnce(res);
	}
	return res;

	//============================================================
}

std::vector<Segment> LindenmayerSystem::draw(std::string const& symbols) {
	/*============================================================
		TODO 2.1
		Build line segments according to the sequence of symbols
		The initial position is (0, 0) and the initial direction is "up" (0, 1)
		Segment is std::pair<vec2, vec2>
	*/

	vec2 curr_pen = vec2(0.0f, 0.0f);
	Segment seg = { (0,0), (0,0) };
	std::vector<Segment> result = { };
	std::vector<Segment> stack = { };
	std::vector<float> angle_stack = {};
	float angle = 90.0f; //initial "up" direction
	
	
	for (char c : symbols) {
		switch (c) {
		case '+': 
			angle += rotation_angle_deg;
			break;

		case '-': 
			angle -= rotation_angle_deg;
			break;

		case '[': 
			stack.push_back(seg);
			angle_stack.push_back(angle);
			break;

		case ']':
			seg = stack.back();
			stack.pop_back();
			angle = angle_stack.back();
			angle_stack.pop_back();
			break;

		default: 
			
			//'F' or any other symbol not listed above
			//compute new pen position
			float rad = angle * M_PI / 180;
			//sin and cos give relative vector coordinates of length 1 and angle "angle" on the trig. circle
			//translate unit circle point by the last pen position
			curr_pen = seg.second + vec2( cos(rad),sin(rad) );
			//build new segment
			seg.first = seg.second;
			seg.second = curr_pen;
			result.push_back(seg);
			
		
		}
	}
	return result;
	
	//============================================================
}

std::string LindenmayerSystemStochastic::expandSymbol(unsigned char const& sym) {
	/*============================================================
		TODO 4.1
		For a given symbol in the sequence, what should it be replaced with after expansion?
		(stochastic case)
		The rules are in this->rules, but now these are stochastic rules because this method belongs to the LindenmayerSystemStochastic class, see lsystem.h for details.
	*/
	
	Dice d;
	double val = d.roll();

	std::string res ="";
	res = res + char(sym);
	if( val >= 0.5){
		res = res + char('+');
	} else {
		res = res + char('-');
	}
	return res + char(sym);

	//============================================================
}

void LindenmayerSystemDeterministic::addRuleDeterministic(unsigned char sym, std::string const& expansion) {
	rules[sym] = expansion;
}

void LindenmayerSystemStochastic::addRuleStochastic(unsigned char sym, std::vector<StochasticRule> expansions_with_ps) {
	rules[sym] = expansions_with_ps;
}
