
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <iostream>


using namespace std;

class Collision
{
public:
	inline bool check_collision(float posX, float posZ, vector<vector<int>> map);
	inline bool check_ladder(float posX, float posZ, vector<vector<float>> ladder);
	inline bool check_collision_up(float posX, float posZ, vector<vector<int>> map);
	inline bool check_ballingoal(float posX, float posZ);
};

