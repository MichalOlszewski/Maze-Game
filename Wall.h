#pragma once

#include <iostream>
#include <vector>

using namespace std;

//myCubeVertices - homogeniczne współrzędne wierzchołków w przestrzeni modelu
//myCubeNormals - homogeniczne wektory normalne ścian (per wierzchołek) w przestrzeni modelu
//myCubeVertexNormals - homogeniczne wektory normalne wierzchołków w przestrzeni modelu
//myCubeTexCoords - współrzędne teksturowania
//myCubeColors - kolory wierzchołków
//myCubeC1 - kolumna macierzy TBN^-1
//myCubeC2 - kolumna macierzy TBN^-1
//myCubeC3 - kolumna macierzy TBN^-1

int WallCount = 36;

float wallVertices[] = {
	//Ściana 1
	3.0f, 0.0f,0.0f,1.0f,
	0.0f, 2.0f,0.0f,1.0f,
	0.0f,0.0f, 0.0f,1.0f,

	3.0f, 0.0f, 0.0f,1.0f,
	3.0f, 2.0f,0.0f,1.0f,
	0.0f, 2.0f,0.0f,1.0f,

	//Ściana 2
	0.0f,0.0f, 1.0f,1.0f,
	3.0f, 2.0f,1.0f,1.0f,
	3.0f, 0.0f,1.0f,1.0f,

	0.0f,0.0f, 1.0f,1.0f,
	0.0f, 2.0f,1.0f,1.0f,
	3.0f, 2.0f,1.0f,1.0f,


	//Ściana 3
	0.0f,0.0f,0.0f,1.0f,
	3.0f,0.0f, 1.0f,1.0f,
	3.0f,0.0f,0.0f,1.0f,

	0.0f,0.0f,0.0f,1.0f,
	0.0f,0.0f, 1.0f,1.0f,
	3.0f,0.0f, 1.0f,1.0f,

	//Ściana 4
	0.0f, 2.0f, 1.0f,1.0f,
	3.0f, 2.0f, 0.0f,1.0f,
	3.0f, 2.0f, 1.0f,1.0f,

	0.0f, 2.0f, 1.0f,1.0f,
	0.0f, 2.0f,0.0f,1.0f,
	3.0f, 2.0f,0.0f,1.0f,

	//Ściana 5
	0.0f,0.0f,0.0f,1.0f,
	0.0f, 2.0f, 1.0f,1.0f,
	0.0f, 0.0f, 1.0f,1.0f,

	0.0f, 0.0f, 0.0f,1.0f,
	0.0f, 2.0f, 0.0f,1.0f,
	0.0f, 2.0f, 1.0f,1.0f,

	//Ściana 6
	3.0f, 0.0f, 1.0f,1.0f,
	3.0f, 2.0f, 0.0f,1.0f,
	3.0f, 0.0f, 0.0f,1.0f,

	3.0f, 0.0f, 1.0f,1.0f,
	3.0f, 2.0f, 1.0f,1.0f,
	3.0f, 2.0f, 0.0f,1.0f,




};

//float wallVertices[] = {
//	//Ściana 1
//	1.0f,-1.0f,-1.0f,1.0f,
//	-1.0f, 1.0f,-1.0f,1.0f,
//	-1.0f,-1.0f,-1.0f,1.0f,
//
//	1.0f,-1.0f,-1.0f,1.0f,
//	1.0f, 1.0f,-1.0f,1.0f,
//	-1.0f, 1.0f,-1.0f,1.0f,
//
//	//Ściana 2
//	-1.0f,-1.0f, 1.0f,1.0f,
//	1.0f, 1.0f, 1.0f,1.0f,
//	1.0f,-1.0f, 1.0f,1.0f,
//
//	-1.0f,-1.0f, 1.0f,1.0f,
//	-1.0f, 1.0f, 1.0f,1.0f,
//	1.0f, 1.0f, 1.0f,1.0f,
//
//
//	//Ściana 3
//	-1.0f,-1.0f,-1.0f,1.0f,
//	1.0f,-1.0f, 1.0f,1.0f,
//	1.0f,-1.0f,-1.0f,1.0f,
//
//	-1.0f,-1.0f,-1.0f,1.0f,
//	-1.0f,-1.0f, 1.0f,1.0f,
//	1.0f,-1.0f, 1.0f,1.0f,
//
//	//Ściana 4
//	-1.0f, 1.0f, 1.0f,1.0f,
//	1.0f, 1.0f,-1.0f,1.0f,
//	1.0f, 1.0f, 1.0f,1.0f,
//
//	-1.0f, 1.0f, 1.0f,1.0f,
//	-1.0f, 1.0f,-1.0f,1.0f,
//	1.0f, 1.0f,-1.0f,1.0f,
//
//	//Ściana 5
//	-1.0f,-1.0f,-1.0f,1.0f,
//	-1.0f, 1.0f, 1.0f,1.0f,
//	-1.0f,-1.0f, 1.0f,1.0f,
//
//	-1.0f,-1.0f,-1.0f,1.0f,
//	-1.0f, 1.0f,-1.0f,1.0f,
//	-1.0f, 1.0f, 1.0f,1.0f,
//
//	//Ściana 6
//	1.0f,-1.0f, 1.0f,1.0f,
//	1.0f, 1.0f,-1.0f,1.0f,
//	1.0f,-1.0f,-1.0f,1.0f,
//
//	1.0f,-1.0f, 1.0f,1.0f,
//	1.0f, 1.0f, 1.0f,1.0f,
//	1.0f, 1.0f,-1.0f,1.0f,
//
//
//
//
//};



float wallNormals[] = {
	//Ściana 1
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,

	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,
	0.0f, 0.0f,-1.0f,0.0f,

	//Ściana 2
	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,

	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,
	0.0f, 0.0f, 1.0f,0.0f,

	//Ściana 3
	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,

	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,
	0.0f,-1.0f, 0.0f,0.0f,

	//Ściana 4
	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,

	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,
	0.0f, 1.0f, 0.0f,0.0f,

	//Ściana 5
	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,

	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,
	-1.0f, 0.0f, 0.0f,0.0f,

	//Ściana 6
	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,

	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,
	1.0f, 0.0f, 0.0f,0.0f,


};

float wallVertexNormals[] = {
	//Ściana 1
	1.0f,-1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
	-1.0f,-1.0f,-1.0f,0.0f,

	1.0f,-1.0f,-1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,

	//Ściana 2
	-1.0f,-1.0f, 1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,
	1.0f,-1.0f, 1.0f,0.0f,

	-1.0f,-1.0f, 1.0f,0.0f,
	-1.0f, 1.0f, 1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,


	//Ściana 3
	-1.0f,-1.0f,-1.0f,0.0f,
	1.0f,-1.0f, 1.0f,0.0f,
	1.0f,-1.0f,-1.0f,0.0f,

	-1.0f,-1.0f,-1.0f,0.0f,
	-1.0f,-1.0f, 1.0f,0.0f,
	1.0f,-1.0f, 1.0f,0.0f,

	//Ściana 4
	-1.0f, 1.0f, 1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,

	-1.0f, 1.0f, 1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,

	//Ściana 5
	-1.0f,-1.0f,-1.0f,0.0f,
	-1.0f, 1.0f, 1.0f,0.0f,
	-1.0f,-1.0f, 1.0f,0.0f,

	-1.0f,-1.0f,-1.0f,0.0f,
	-1.0f, 1.0f,-1.0f,0.0f,
	-1.0f, 1.0f, 1.0f,0.0f,

	//Ściana 6
	1.0f,-1.0f, 1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
	1.0f,-1.0f,-1.0f,0.0f,

	1.0f,-1.0f, 1.0f,0.0f,
	1.0f, 1.0f, 1.0f,0.0f,
	1.0f, 1.0f,-1.0f,0.0f,
};

float wallTexCoords[] = {
	//Ściana 1
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Ściana 2
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Ściana 3
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Ściana 4
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Ściana 5
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

	//Ściana 6
	1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
	1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
};

//### ### ### <- klocki ustawione w ten sposob
//jeden blok muru ma wymiary 3x1x1 dlatego rysujemy co 3 jednostki, aby otrzymac mur bez przerwy
//wspolrzedne X; kazdy wiersz tworzy całosc z odpowiednimi indeksami z placeWallXY
//placeWallXY[0] - wspólrzedna Z na mapie
//placeWallXX[0] - wspolrzedne X na mapie
//Łącznie otrzymujemy z powyzszego polaczenia 11 wierzcholkow
vector<vector<float> > placeWallXX{
{0.0f,3.0f,6.0f,9.0f,12.0f,15.0f,18.0f,21.0f,24.0f,27.0f,30.0f},
{9.0f,12.0f,15.0f,18.0f,23.0f,26.0f},
{1.0f,4.0f,7.0f,28.0f},
{18.0f,21.0f},
{1.0f,7.0f,10.0f},
{21.0f,24.0f},
{5.0f},
{18.0f,21.0f},
{1.0f,4.0f,7.0f},
{22.0f,28.0f},
{5.0f,10.0f,14.0f},
{26.0f},
{22.0f},
{8.0f},
{8.0f,28.0f},
{8.0f,19.0f,22.0f},
{15.0f},
{4.0f,23.0f,26.0f},
{0.0f,3.0f,6.0f,9.0f,12.0f,15.0f,23.0f,26.0f,29.0f}
};

vector<float> placeWallXY{ 0.0f, 3.0f,6.0f,7.0f,9.0f,11.0f,13.0f,14.0f,16.0f,17.0f,19.0f,21.0f,22.0f,23.0f,24.0f,25.0f,27.0f,28.0f,31.0f };

//#
//#
//# <- klocki ustawione w ten sposob
//Tak samo jak dla placeWallXX, z tą różnicą, że 
//placeWallYY to współrzędne Z
//placeWallYX to wspolrzedna X
vector<vector<float>> placeWallYY{
	{1.0f,4.0f,7.0f,10.0f,13.0f,16.0f,19.0f,22.0f,25.0f,28.0f},
	{19.0f,22.0f,25.0f},
	{1.0f},
	{10.0f,23.0f,28.0f},
	{20.0f,26.0f},
	{4.0f,7.0f,10.0f,13.0f,18.0f,25.0f,28.0f},
	{20.0f,25.0f},
	{7.0f,10.0f,13.0f,16.0f,19.0f},
	{25.0f,31.0f},
	{17.0f,22.0f},
	{28.0f,31.0f},
	{4.0f},
	{14.0f},
	{20.0f},
	{6.0f,11.0f,14.0f},
	{1.0f,4.0f,7.0f,10.0f,13.0f,16.0f,19.0f,22.0f,25.0f,28.0f }
};

vector<float> placeWallYX {0.0f,4.0f,5.0f,7.0f,10.0f,13.0f,14.0f,17.0f,18.0f,21.0f,22.0f,23.0f,24.0f,25.0f,27.0f,31.0f };

//rozstawienie muru na mapie
//tam gdzie 1 tam mur
//X = <0;31>
//Z = <0;33>
//row = X
//col = Z
vector<vector<int>> wallinmap{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1},
	{1,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0}
};

//to samo co wyżej, z tą roznicą, że brzegi muru zostały zamienione na 0, zeby nie mozna sie bylo po nich poruszac, gdy jestesmy u gory
vector<vector<int>> wall_ladderinmap{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,0},
	{0,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


vector<vector<float>> pos_ladder{
	{8.0f, 6.0f},
	{18.0f, 7.0f},
	{9.0f, 23.0f}
};