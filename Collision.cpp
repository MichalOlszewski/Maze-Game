#include "Collision.h"


using namespace std;

//sprawdzamy kolizje z murem
/* Tam gdzie na wektorze 2D jest 1, oznacza ¿e jest mur
   Przyk³adowo jezeli w map[0][0] = 1, to oznacza to, ze w przedziale x = <0;1> i z = <0;1> stoi mur
   Dlatego z aktualnej pozycji kamery bierzemy zaokr¹glenie w dó³, gdy¿ jezeli bêdzie w tym przedziale
   to zwróci nam map[0][0] = 1, i bedzie oznacza³o to kolizje*/
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
	//count - która drabina
	for (int count = 0; count < ladder.size(); count++) {
		printf("%d", count);
		if ((posX <= (ladder[count][0] + 0.25f) && (posX >= ladder[count][0] - 0.25f)) && (posZ >= (ladder[count][1] - 0.25f) && posZ < (ladder[count][1] + 0.1f)))
		{
			return true;
		}
	}
	return false;
}

//sprawdzamy, czy poruszamy siê po murze
/* Zasady dzia³ania tej kolizji takie same, jak w przypadku kolziji poruszania siê na ziemi
   Ró¿nica jest taka, ze kolizja wystêpuje wtedy gdy map[x][z] = 0, czyli wtedy, gdy jestemy poza murem*/
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