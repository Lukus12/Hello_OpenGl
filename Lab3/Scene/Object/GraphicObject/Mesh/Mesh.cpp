#include "..\Mesh\Mesh.h"


using namespace std;
using namespace glm;

void Mesh::load(string filename)
{
	// вектор для хранения геометрических координат
	vector<vec3> vec;
	// вектор для хранения нормалей
	vector<vec3> normal;
	// вектор для хранения текстурных координат
	vector<vec2> textura;
	// вектор для хранения индексов атрибутов, для построения вершин
	vector<ivec3> fPoints;
	// отображение вершины (по используемым ею атрибутам) на индекс в массиве вершин
	map<string, int> vertexToIndexTable;

	int index = 0;

	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Failed!\n";
	}
	else {
		string str;
		vec3 cord{};
		vec2 cord2{};
		while (getline(fin, str)) {

			if (str[0] != '#' and str[0] != '\n' and str[0] != 'f' and str[0] != 'g') {
				istringstream strNew(str);
				string view;

				strNew >> view;
				if (view == "v") {
					strNew >> cord[0] >> cord[1] >> cord[2];
					//cout << cord[0] << " " << cord[1] << " " << cord[2] << endl;
					vec.push_back(cord);
				}
				if (view == "vn") {
					strNew >> cord[0] >> cord[1] >> cord[2];
					normal.push_back(cord);
				}
				if (view == "vt") {
					strNew >> cord2[0] >> cord2[1];
					textura.push_back(cord2);
				}
			}
			if (str[0] == 'f') {
				ivec3 fCord{};
				string simbol = "";
				int k = 0;
				/*for (int i = 2; i < str.length() + 1; i++) {
					if (str[i] == '/') {
						if (k == 0) {
							simbol.append(str.substr(i - 1, 1));
							fCord[0] = stod(simbol);
							simbol = "";

							simbol.append(str.substr(i + 1, 1));
							fCord[1] = stod(simbol);
							simbol = "";

							k++;
						}
						else {
							k = 0;
							simbol.append(str.substr(i + 1, 1));
							fCord[2] = stod(simbol);
							simbol = "";
							fPoints.push_back(fCord);
						}
					}
				}*/
				istringstream strNew(str);
				string strSub;
				for (int i = 0; i < 3; i++) {
					strNew >> strSub;
					if(strSub[0] == 'f') strNew >> strSub;
					//cout << strSub << endl;
					auto iterator = vertexToIndexTable.find(strSub);
					if (iterator == vertexToIndexTable.end()) {
						vertexToIndexTable[strSub] = index;
						indices.push_back(index);
						
						replace(strSub.begin(), strSub.end(), '/', ' ');
						//cout << strSub << endl;
						istringstream subSubSr(strSub);
						subSubSr >> fCord[0] >> fCord[1] >> fCord[2];
						//cout << endl;
						//cout << fCord[0] << " " << fCord[1] << " " << fCord[2] << endl;
						fPoints.push_back(fCord);
						
						
						index++;
					}
					else {
						int pastIndex = (*iterator).second;
						indices.push_back(pastIndex);
					}
				}
				//cout << endl;
				
			}
		}
		fin.close();
	}

	/*cout << fPoints[0][0] << " " << fPoints[0][1] << " " << fPoints[0][2] << " | ";
	cout << fPoints[1][0] << " " << fPoints[1][1] << " " << fPoints[1][2] << " | ";
	cout << fPoints[2][0] << " " << fPoints[2][1] << " " << fPoints[2][2] << " | ";
	cout << fPoints[3][0] << " " << fPoints[3][1] << " " << fPoints[3][2] << endl;*/
	
	


	for (int i = 0; i < fPoints.size(); i++) {
		Vertex memberVertices;
		int indexVec = fPoints[i][0] - 1;
		int indexTextura = fPoints[i][1] - 1;
		int indexNormal = fPoints[i][2] - 1;
		for (int j = 0; j < 3; j++) {
			memberVertices.coord[j] = vec[indexVec][j];
			memberVertices.normal[j] = normal[indexNormal][j];
		}
		for (int j = 0; j < 2; j++) {
			memberVertices.texCoord[j] = textura[indexTextura][j];
		}
		vertices.push_back(memberVertices);
	}

	//этап загрузки буфферов
	glGenBuffers(1, &bufferIds[0]);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &bufferIds[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

struct CVertex3 {
	float x;
	float y;
	float z;
};

struct CVertex2 {
	float x;
	float y;
};

struct CFace {
	int v1, v2, v3;
};

void Mesh::draw(){

	CFace face[5000] = {};

	CVertex3 v[5000] = {};
	CVertex3 vn[5000] = {};
	CVertex2 vt[5000] = {};


	for (int i = 0; i < vertices.size(); i++) {
		v[i].x = vertices[i].coord[0];
		v[i].y = vertices[i].coord[1];
		v[i].z = vertices[i].coord[2];

		vn[i].x = vertices[i].normal[0];
		vn[i].y = vertices[i].normal[1];
		vn[i].z = vertices[i].normal[2];

		vt[i].x = vertices[i].texCoord[0];
		vt[i].y = vertices[i].texCoord[1];
	}

	for (int i = 0; i < indices.size() / 3; i++) {
			face[i].v1 = indices[i*3 + 0];
			face[i].v2 = indices[i*3 + 1];
			face[i].v3 = indices[i*3 + 2];
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(CVertex3), v);
	glNormalPointer(GL_FLOAT, sizeof(CVertex3), vn);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex2), vt);

	//glDrawArrays(GL_TRIANGLES, 0, indices.size());
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, face);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}