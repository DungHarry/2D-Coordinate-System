/*
	Author: Dung Harry
	Date created: 4th, October 2013
	Operating System: Ubuntu Desktop 13.04
	Compiler: GNU compiler 4.7.3

	Description: this is the C++ program to simulate the 2D coordinate system
*/

#include<iostream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

#define unitsPerX 4
#define unitsPerY 2

typedef struct point point;

struct point {
	int x;
	int y;
};

class coordinate {
	private:
		point *lpPoints;
		int iMaxX, iMaxY, iMinX, iMinY, iNumPoint;

		vector<string> stringSplit(const string &str, char splitChar);
	public:
		~coordinate();
		void vEnterPoints();
		void vConvertXY();
		void vSetMaxXY();
		void vSetMinXY();
		void vPaint();
};

coordinate::~coordinate() {
	delete lpPoints;
}

vector<string> coordinate::stringSplit(const string &str, char splitChar) {
	vector<string> objectReturn;
	stringstream strStream(str);
	string eachPart;

	while(getline(strStream, eachPart, splitChar)) {
		objectReturn.push_back(eachPart);
	}

	return objectReturn;
}

void coordinate::vEnterPoints() {
	vector<string> strX, strY;
	string bufferX, bufferY;

	cout<<"Enter coordinate X: ";
	getline(cin, bufferX);

	cout<<"Enter coordinate Y: ";
	getline(cin, bufferY);

	strX = stringSplit(bufferX, ' ');
	strY = stringSplit(bufferY, ' ');

	iNumPoint = strX.size() > strY.size() ? strY.size() : strX.size();

	lpPoints = new point[iNumPoint];

	for(int i = 0; i < iNumPoint; i ++) {
		stringstream(strX[i])>>(lpPoints + i)->x;
		stringstream(strY[i])>>(lpPoints + i)->y;
	}
}

void coordinate::vConvertXY() {
	for(int i = 0; i < iNumPoint; i ++) {
		(lpPoints + i)->x *= unitsPerX;
		(lpPoints + i)->y *= unitsPerY;
	}
}

void coordinate::vSetMaxXY() {
	iMaxX = iMaxY = 0;

	for(int i = 0; i < iNumPoint; i ++) {
		iMaxX = (lpPoints + i)->x > iMaxX ? (lpPoints + i)->x : iMaxX;
		iMaxY = (lpPoints + i)->y > iMaxY ? (lpPoints + i)->y : iMaxY;
	}
}

void coordinate::vSetMinXY() {
	iMinX = iMinY = 0;

	for(int i = 0; i < iNumPoint; i ++) {
		iMinX = (lpPoints + i)->x > iMinX ? iMinX : (lpPoints + i)->x;
		iMinY = (lpPoints + i)->y > iMinY ? iMinY : (lpPoints + i)->y;
	}
}

void coordinate::vPaint() {
	char mesh[iMaxY - iMinY + 2 * unitsPerY][iMaxX - iMinX + 2 * unitsPerX];
	int i, j;

	for(j = 0; j < iMaxY - iMinY + 2 * unitsPerY; j ++) {
		for(i = 0; i < iMaxX - iMinX + 2 * unitsPerX; i ++) {
			mesh[j][i] = ' ';
		}
	}

	if((unitsPerX - iMinX) >= 0) {
		for(j = 0; j < iMaxY - iMinY + 2 * unitsPerY; j ++) {
			mesh[j][unitsPerX - iMinX] = '|';
		}
	}

	if((unitsPerY + iMaxY) <= (iMaxY - iMinY + 2 * unitsPerY)) {
		for(i = 0; i < iMaxX - iMinX + 2 * unitsPerX; i ++) {
			mesh[unitsPerY + iMaxY][i] = '-';
		}
	}

	for(i = 0; i < iNumPoint; i ++) {
		mesh[unitsPerY + iMaxY - (lpPoints + i)->y][(lpPoints + i)->x + unitsPerX - iMinX] = '*';
	}

	for(j = 0; j < iMaxY - iMinY + 2 * unitsPerY; j ++) {
		for(i = 0; i < iMaxX - iMinX + 2 * unitsPerX; i ++) {
			if((i == 0) && ((unitsPerY + iMaxY - j) % unitsPerY == 0)) {
				((int) ((unitsPerY + iMaxY - j) / unitsPerY)) >= 0 ? cout<<"+"<<((int) ((unitsPerY + iMaxY - j) / unitsPerY))<<" " : cout<<((int) ((unitsPerY + iMaxY - j) / unitsPerY))<<" ";

				cout<<mesh[j][i];
			} else if(i == 0) {
				cout<<"    ";
			} else {
				cout<<mesh[j][i];
			}
		}

		cout<<endl;
	}

	for(i = 0; i < iMaxX - iMinX + 2 * unitsPerX; i ++) {
		if((i + iMinX - unitsPerX) % unitsPerX == 0) {
			((int) ((i + iMinX - unitsPerX) / unitsPerX)) >= 0 ? cout<<"+"<<((int) ((i + iMinX - unitsPerX) / unitsPerX)) : cout<<((int) ((i + iMinX - unitsPerX) / unitsPerX));
		} else {
			cout<<" ";
		}
	}

	cout<<endl;
}

int main(int argc, char *argv[]) {
	cout<<"Author: Dung Harry\nDate Created: 4th, October 2013"<<endl;

	coordinate object;

	object.vEnterPoints();
	object.vConvertXY();
	object.vSetMaxXY();
	object.vSetMinXY();
	object.vPaint();
}
