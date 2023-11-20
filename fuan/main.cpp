#include <iostream>
#include <vector>
#include <math.h>
#include "matrix.h"

const double E = 0.01; //точность

double Ro2(math::Vec4d& x1, math::Vec4d& x2) {
	double result = 0;
	for (int i = 0; i < 4; i++) {
		int j = 0;
		result += pow((x1.get(i, j) - x2.get(i, j)), 2);
	}
	result = sqrt(result);
	return result;
}

double Napr(double E, double a, double Ro2) {
	double Napr = ((log((E * (1 - a)) / Ro2) / log(a)) + 1);
	return Napr;
}

void lab3() {
	double e = 0.0001;
	double a = (static_cast<double>(4) / 30);
	double ro = static_cast<double>(43) / 15;
	double napr = Napr(e, a, ro);
	std::cout << "NAPR = " << napr << std::endl;;
}



void lab1() {
	math::Mat44d C(
		{ {
							{0.58251, -0.41117, 0.21507, -0.06326},
							{-0.41117, 0.56353, 0.15814, -0.12651},
							{0.21507, 0.15814, 0.48130, -0.36689},
							{-0.06326, -0.12651, -0.36689, 0.55721}
				} }
	);

	math::Vec4d d({ {
	{1.68895},
	{2.08114},
	{2.03053},
	{3.15017}
} });

	math::Vec4d answer({ { //ответ, полученный методом Гаусса
	{6},
	{1},
	{6},
	{1}
} });

	double lambdaC = 0.98885; //наибольшее собственное значение матрицы C = alpha

	std::vector<math::Vec4d> X; //массив векторов X
	double k = (lambdaC / (1 - lambdaC));
	std::cout << "k = " << k << std::endl;


	math::Vec4d x1({ {{0.5},{0.5},{0.5},{0.5}} }); //возьмем произвольным образом начальное приближение
	math::Vec4d x2({ {{0},{0},{0},{0}} });
	x2 = C * x1 + d;
	std::cout << "X2 = " << x2 << std::endl;
	double ro = Ro2(x2, x1);

	double x = Napr(E, lambdaC, ro);
	std::cout << "Ro2 = " << ro << "     Napr = " << x << std::endl;

	bool end = true;
	while (end) {

		if (X.size() == 0) {
			X.emplace_back(x1);
		}
		else if (X.size() == 1) {
			X.emplace_back(x2);
		}
		else {

			if ((k * Ro2(X.back(), X.at(X.size() - 2))) > E) {
				math::Vec4d x3({ {{0},{0},{0},{0}} });
				x3 = C * X.back() + d;
				X.emplace_back(x3);
			}
			else {
				end = false;
			};
		}
	}

	for (auto& i : X) {
		std::cout << i << std::endl;
	}
	std::cout << "//////////////////////////////" << std::endl;
	std::cout << "RESULT: \n" << X.back() << std::endl;

	std::cout << "Napr = " << x << ", RESULT AT NUMBER = " << X.size() << std::endl; //итоговое количество итераций

	std::cout << "\nE:\n" << answer - X.back() << std::endl; //оценка точности
}

void lab2() {
	std::vector<int> T;
	for (int i = -1; i <= 15; i++) {
		T.emplace_back(i);
	}
	std::cout << "///////////////////////" << std::endl;
	std::cout << "VECTOR T" << std::endl;
	for (auto i : T) {
		std::cout << i << " ";
	}
	std::vector<std::vector<double>> X;
	std::vector<double> x1;
	for (int i = 0; i < T.size(); i++) {
		x1.emplace_back(sqrt(T[i] + 1));
	}
	X.emplace_back(x1);
	int c = X.size();
	//std::vector<double> x2;
	//for (int i = 0; i < T.size(); i++) {
	//	x2.emplace_back(sqrt(T[i] + 1) - 3 * (std::pow((1 + abs(X[c - 1][i])), (1 / 4))));
	//}
	//X.emplace_back(x2);

	//c = X.size();
	//std::vector<double> x3;
	//for (int i = 0; i < T.size(); i++) {
	//	x3.emplace_back(sqrt(T[i] + 1) - 3 * (std::pow((1 + abs(X[c - 1][i])), (1 / 4))));
	//}
	//X.emplace_back(x3);

	
	std::cout << "\nX size = " << X.size() << "X[0] size = " << X[0].size() << std::endl;
	
	for (int j = 1; j <= 27; j++) {
		//std::cout << "C = " << c << std::endl;
		std::vector<double> x;
		//std::cout << "size x = " << x.size() << std::endl;
		for (int i = 0; i < T.size(); i++) {
			//x.emplace_back(sqrt(T[i] + 1) - 3);
			//std::cout << "ADDEED: " << (sqrt(T[i] + 1) - 3 * (std::pow((1 + sqrt(X[c - 1][i] + 1)), (1 / 4)))) << std::endl;
			//std::cout << "C_1= " << c-1 << "   x[c-1] = " << abs(X[c - 1][i]) << std::endl;
			x.emplace_back(sqrt(T[i] + 1) - 3 * (std::pow((1 + abs(X[c - 1][i])), (1 / 4))));
			//X[j].emplace_back(sqrt(T[i] + 1) - 3 * (std::pow((1 + X[j-1][i]), (1 / 4))));
			
		}
		X.emplace_back(x);
		c++;
	}
	//std::cout << "X SIZE = " << X.size() << std::endl;
	std::cout << std::endl;
	std::cout << "\n///////////RESULT////////////" << std::endl;
	int i = X.size()-1;
	std::cout << "!" << X[i].size() << "   ";
	for (int j = 0; j < X[i].size(); j++) {
		std::cout << X[i][j] << std::endl;
	}
	std::cout << std::endl;
	
}
int main() {
	lab2();

	
	return 0;
}