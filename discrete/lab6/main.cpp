#include <iostream>
#include <vector>
#include <fstream>

void PrintMatrix(std::vector<std::vector<int>> &Matrix) {
    for (auto i : Matrix) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

struct Edge{
    int a, b, cost;
};

int main() {
    int rows = 15; //количество ребер
    int cols = 8; //количество вершин в графе (0-7)
    //двумерный массив под матрицу инцидентности, заполненный нулями
    std::vector<std::vector<int>> incidenceMatrixB(rows, std::vector<int> (cols, 0));

    std::ifstream in1("../input.txt");
    std::ifstream in2("../input2.txt");

    if (in1.is_open()){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                in1 >> incidenceMatrixB[i][j]; //сin если с консоли
            }
        }
        std::cout << "Матрица инцидентности:" << std::endl;
        PrintMatrix(incidenceMatrixB);

        //двумерный пустой массив под матрицу смежности
        std::vector<std::vector<int>> adjacencyMatrixA(cols, std::vector<int> (cols, 0));

        //алгоритм перевода матрицы инцидентности в матрицу смежности
        for (int i = 0; i < rows; i++) {
            int iA = -1;//номер строки в матрице смежности, куда будем ставить 1
            int jA = -1;//номер столбца
            for (int j = 0; j < cols; j++) {
                if(incidenceMatrixB[i][j] == 1) {
                    iA = j; //находим начало ребра (это номер строки)
                }
                if(incidenceMatrixB[i][j] == -1) {
                    jA = j; //находим конец (номер столбца)
                }
            }
            if (iA != -1 && jA !=-1) {
                adjacencyMatrixA[iA][jA] = 1;
            }
        }
        std::cout << "Матрица смежности:" << std::endl;
        PrintMatrix(adjacencyMatrixA);

    } else {
       std::cout << "Error of opening file in1"<< std::endl;
    }

    if (in2.is_open()) {
        //Используем алгоритм Форда-Беллмана для поиска кратчайших путей
        std::vector<Edge> e(rows);
        const int INF = 1000000000;
        std::vector<int> d(cols, INF);
        for (int i = 0; i < rows - 1; i++) {
            in2 >> e[i].a >> e[i].b >> e[i].cost;  //сin если с консоли
        }
        int v; //номер стартовой вершины (от 0 до 7)
        std::cout << "Введите номер стартовой вершины, для которой выведутся кратчайшие расстояния(0-7): " << std::endl;
        std::cin >> v;
        if (v > cols-1) {std::cout << "Нет такой вершины" << std::endl;} else {
            d[v] = 0;
            for (int i = 0; i < cols - 1; ++i) {
                for (int j = 0; j < rows; ++j) {
                    if (d[e[j].a] < INF) {
                        d[e[j].b] = std::min(d[e[j].b], d[e[j].a] + e[j].cost);
                    }
                }
            }

            std::cout << "Массив кратчайших расстояний для вершины " << v << ":" << std::endl;
            for (auto &i: d) {
                std::cout << i << " ";
            }
        }
    } else {
        std::cout << "Error of opening file in2"<< std::endl;
    }
    return 0;
}
