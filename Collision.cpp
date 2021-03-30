#include "Collision.h"


using namespace std;

//sprawdzamy kolizje z murem
/* Tam gdzie na wektorze 2D jest 1, oznacza �e jest mur
   Przyk�adowo jezeli w map[0][0] = 1, to oznacza to, ze w przedziale x = <0;1> i z = <0;1> stoi mur
   Dlatego z aktualnej pozycji kamery bierzemy zaokr�glenie w d�, gdy� jezeli b�dzie w tym przedziale
   to zwr�ci nam map[0][0] = 1, i bedzie oznacza�o to kolizje*/
bool Collision::check_collision(float posX, float posZ, vector<vector<int>> map) {
	for (int row = 0; row < map.size(); row++) {
		for (int col = 0; col < map[row].size(); col++) {
			if (!(floor(posX) >= 0 and floor(posX) <= 31 and floor(posZ) >= 0 and floor(posZ) <= 33)) {
				return false;
			}
			else 
			{
				
				if ((map[floor(posZ)][floor(posX)] == 1))
				{
					cout << "true" << endl;
					return true;
				}
			}
		}
	}

	return false;
}

//sprawdzamy, czy kamera jest przy drabinie
bool Collision::check_ladder(float posX, float posZ, vector<vector<float>> ladder) {
	//count - kt�ra drabina
	for (int count = 0; count < ladder.size(); count++) {
		printf("%d", count);
		if ((posX <= (ladder[count][0] + 0.25f) && (posX >= ladder[count][0] - 0.25f)) && (posZ >= (ladder[count][1] - 0.25f) && posZ < (ladder[count][1] + 0.1f)))
		{
			return true;
		}
	}
	return false;
}

//sprawdzamy, czy poruszamy si� po murze
/* Zasady dzia�ania tej kolizji takie same, jak w przypadku kolziji poruszania si� na ziemi
   R�nica jest taka, ze kolizja wyst�puje wtedy gdy map[x][z] = 0, czyli wtedy, gdy jestemy poza murem*/
bool Collision::check_collision_up(float posX, float posZ, vector<vector<int>> map){
	for (int row = 0; row < map.size(); row++) {
		for (int col = 0; col < map[row].size(); col++) {
			if (!(floor(posX) >= 0 and floor(posX) <= 31 and floor(posZ) >= 0 and floor(posZ) <= 33)) {
				return false;
			}
			else
			{
				if ((map[floor(posZ)][floor(posX)] == 0))
				{
					cout << "true" << endl;
					return true;
				}
			}
		}
	}

	return false;

}

//sprawdzamy czy pilka jest w bramce
bool Collision::check_ballingoal(float posX, float posZ)
{
	if ((posX >= 19.75f && posX <= 21.30f) && (posZ >= 38.15f && posZ <= 38.75f)) return true;
	return false;
}