#include "PhongMaterial.h"

using namespace std;



void PhongMaterial::setAmbient(vec4 color)
{
	this->ambient.r = color.x;
	this->ambient.g = color.y;
	this->ambient.b = color.z;
	this->ambient.a = 1;
}

void PhongMaterial::setDiffuse(vec4 color)
{
	this->diffuse.r = color.x;
	this->diffuse.g = color.y;
	this->diffuse.b = color.z;
	this->diffuse.a = 1;
}

void PhongMaterial::setSpecular(vec4 color)
{
	this->specular.r = color.x;
	this->specular.g = color.y;
	this->specular.b = color.z;
	this->specular.a = 1;
}

void PhongMaterial::setEmission(vec4 color)
{
	this->emission.r = color.x;
	this->emission.g = color.y;
	this->emission.b = color.z;
	this->emission.a = 1;
}

void PhongMaterial::setShininess(float p)
{
	this->shininess = p;
}

void PhongMaterial::load(string filename)
{
	ifstream fin;
	fin.open(filename);

	if (!fin.is_open()) {
		cout << "Failed!\n";
	}
	else {
		//cout << "Fail Open!\n";
		int j = 0;
		string str;
		vec4 color;
		string simbol = "";
		while (!fin.eof()) {
			int k = 0;
			fin >> str;
			for (int i = 0; i < str.length(); i++) {
				if (j == 0) {
					if (str[i] == '.' && (str[i - 1] == '1' || str[i - 1] == '0')) {
						simbol.append(str.substr(i - 1, 3));
						color[k] = stod(simbol);
						simbol = "";
						k++;
					}
				}
				if (j == 1) {
					if (str[i] == '.' && (str[i - 1] == '1' || str[i - 1] == '0')) {
						simbol.append(str.substr(i - 1, 3));
						color[k] = stod(simbol);
						simbol = "";
						k++;
					}
				}
				if (j == 2) {
					if (str[i] == '.' && (str[i - 1] == '1' || str[i - 1] == '0')) {
						simbol.append(str.substr(i - 1, 3));
						color[k] = stod(simbol);
						simbol = "";
						k++;
					}
				}
				if (j == 3) {
					if (str[i] == '.' && (str[i - 1] == '1' || str[i - 1] == '0')) {
						simbol.append(str.substr(i - 1, 3));
						color[k] = stod(simbol);
						simbol = "";
						k++;
					}
				}
				if (j == 4) {
					float num;
					if (str[i] == '.' and (int(str[i - 1]) >= 48 and int(str[i - 1]) <= 57)) {
						if (int(str[i - 2]) >= 48 and int(str[i - 2]) <= 57) {
							if (int(str[i - 3]) >= 48 and int(str[i - 3]) <= 57) {
								simbol.append(str.substr(i - 3, 5));
								num = stod(simbol);
							}
							else {
								simbol.append(str.substr(i - 2, 4));
								num = stod(simbol);
							}
						}
						else {
							simbol.append(str.substr(i - 1, 3));
							num = stod(simbol);
						}
						if (num >= 0 and num <= 128) {
							setShininess(num);
						}
						else {
							cout << "Error! 0 <= X <= 128";
						}

					}
				}
				if (str[i] == ';') {
					if (j == 0) setDiffuse(color);
					if (j == 1) setAmbient(color);
					if (j == 2) setSpecular(color);
					if (j == 3) setEmission(color);
					color = {};
					j++;
				}
			}
			//cout << str << endl;
		}
	}
	fin.close();
	cout << this->diffuse.r << " ";
	cout << this->diffuse.g << " ";
	cout << this->diffuse.b << " ";
	cout << this->diffuse.w << endl;
	cout << this->ambient.r << " ";
	cout << this->ambient.g << " ";
	cout << this->ambient.b << " ";
	cout << this->ambient.w << endl;
	cout << this->specular.r << " ";
	cout << this->specular.g << " ";
	cout << this->specular.b << " ";
	cout << this->specular.w << endl;
	cout << this->emission.r << " ";
	cout << this->emission.g << " ";
	cout << this->emission.b << " ";
	cout << this->emission.w << endl;
	cout << this->shininess << endl;
}

void PhongMaterial::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, value_ptr(ambient)); //Фоновая отражающая способность материала. 
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, value_ptr(diffuse)); //Диффузная отражающая способность
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, value_ptr(specular)); //Зеркальная отражающая способность
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, value_ptr(emission)); //Цвет самосвечения. 
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess); //Степень отполированности объекта

}