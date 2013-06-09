#ifndef _RNG_H_
#define _RNG_H_

#include <random>

class RandomNumberGenerator
{
public:
    void Initialise(int s, int min, int max);
	int Random();

    static RandomNumberGenerator * Instance()
	{
	  return &m_Generator;
	}

private:

	static RandomNumberGenerator m_Generator;
	
	// Types for Random number generation
	typedef std::minstd_rand                             Engine;
	typedef std::uniform_int_distribution<int>           Distribution;
	typedef std::variate_generator<Engine, Distribution> Generator;
 
	Generator * gen;  
};

#endif