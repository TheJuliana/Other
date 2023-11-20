#pragma once
#include <iostream>
#include <any>

namespace math
{
    //если закоментировано cout-ы не выводятся
    // MY_DEBUG
//#define MY_DEBUG

    template<class T, int N, int M>
    struct MasWrapper
    {
        T mas[N][M];
    };

    template<class T, int N, int M>
    class Matrix {
    public:
        //конструктор
        Matrix()
        {
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = 0;
        }

        //
        Matrix(const T mas[N][M])
        {
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mas[i][j];
        }

        //
        Matrix(const MasWrapper<T, N, M>& mas)
        {
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mas.mas[i][j];
        }

        // конструктор копирования
        Matrix(const Matrix<T, N, M>& mat)
        {
#ifdef MY_DEBUG
            std::cout << "Copy constructor" << std::endl;
#endif

            m_n = mat.m_n;
            m_m = mat.m_m;

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mat.m_mat[i][j];
        }

        int getN() const { return m_n; }
        int getM() const { return m_m; }
        T get(int i, int j) const { return m_mat[i][j]; }
        void set(int i, int j, T data) { m_mat[i][j] = data; }

        T getDet() const {
            if (m_n == m_m && m_n == 2) {
                return (m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0]);
            }
            else if (m_n == m_m && m_n == 3) {
                return (m_mat[0][0] * m_mat[1][1] * m_mat[2][2]
                    + m_mat[0][2] * m_mat[1][0] * m_mat[2][1]
                    + m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
                    - m_mat[0][2] * m_mat[1][1] * m_mat[2][0]
                    - m_mat[0][1] * m_mat[1][0] * m_mat[2][2]
                    - m_mat[0][0] * m_mat[1][2] * m_mat[2][1]);
            }
            else {
                std::cout << "Operation not supported" << std::endl;
                return 0;
            }
        }

        //транспонированная матрциа
        Matrix<T, N, M> transpose() {
            Matrix<T, M, N> tmp;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    tmp.set(i, j, m_mat[j][i]);
                }
            }

            return tmp;
        }

        //Обратная матрица
        template <typename U>
        Matrix<U, N, M> getInverseMatrix() {
            T det = getDet();
            Matrix<U, N, M> tmp;
            if (det == 0) {
                throw std::logic_error("Inverse Matrix doesn't exist");
            }
            else if (N == M && N == 2) {
                tmp.set(0, 0, m_mat[1][1]);
                tmp.set(1, 0, -1 * m_mat[1][0]);
                tmp.set(0, 1, -1 * m_mat[0][1]);
                tmp.set(1, 1, m_mat[0][0]);
                tmp = (tmp) * (1.0 / det);
                return tmp;
            }
            else if (N == M && N == 3) {
                tmp.set(0, 0, m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]);
                tmp.set(1, 0, -1 * m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0]);
                tmp.set(0, 1, -1 * m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]);
                tmp.set(1, 1, m_mat[0][0] * m_mat[2][2] - m_mat[0][2] * m_mat[2][0]);
                tmp.set(2, 0, m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0]);
                tmp.set(0, 2, m_mat[0][1] * m_mat[1][2] - m_mat[0][2] * m_mat[1][1]);
                tmp.set(2, 1, -1 * m_mat[0][0] * m_mat[2][1] - m_mat[0][1] * m_mat[2][0]);
                tmp.set(1, 2, -1 * m_mat[0][0] * m_mat[1][2] - m_mat[0][2] * m_mat[1][0]);
                tmp.set(2, 2, m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0]);
                tmp = (tmp) * (1.0 / det);
                return tmp;
            }
        }

        //оператор присваивания
        template<typename U, int L, int K>
        Matrix<U, L, K>& operator=(const Matrix<U, L, K>& mat) {
#ifdef MY_DEBUG
            std::cout << "Operator =" << std::endl;
#endif

            m_n = mat.getN();
            m_m = mat.getM();

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mat.get(i, j);

            return *this;
        }

        //оператор сложения
        template<typename U, int L, int K>
        Matrix<U, L, K> operator+(const Matrix<U, L, K>& mat)
        {
#ifdef MY_DEBUG
            std::cout << "operator+" << std::endl;
#endif
            Matrix<U, L, K> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
            return tmp;
        }

        //оператор вычитания
        template<typename U, int L, int K>
        Matrix<U, L, K> operator-(const Matrix<U, L, K>& mat)
        {
#ifdef MY_DEBUG
            std::cout << "operator-" << std::endl;
#endif
            Matrix<U, L, K> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
            return tmp;
        }

        //оператор умножения
        template<typename U, int L, int K>
        Matrix<U, L, K> operator*(const Matrix<U, L, K>& mat)
        {
#ifdef MY_DEBUG
            std::cout << "operator*" << std::endl;
#endif
            Matrix<U, L, K> tmp;

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < mat.getM(); j++)
                {
                    U sum = 0;
                    for (int k = 0; k < m_m; k++)
                        sum += m_mat[i][k] * mat.get(k, j);
                    tmp.set(i, j, sum);
                }

            return tmp;
        }

        Matrix<T, N, M> operator*(const T k)
        {
#ifdef MY_DEBUG
            std::cout << "operator*" << std::endl;
#endif
            Matrix<T, N, M> tmp;

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                {
                    tmp.set(i, j, m_mat[i][j] * k);
                }

            return tmp;
        }

        //деструктор
        ~Matrix()
        {
#ifdef MY_DEBUG
            std::cout << "Destructor" << std::endl;
#endif
        }

        // friend - позволяет функциии иметь доступ к private полям/методам класса
        template<typename U, int L, int K>
        friend std::istream& operator>>(std::istream& os, Matrix<U, L, K>& mat);

        template<typename U, int L, int K>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<U, L, K>& mat);

    private:
        int m_n, m_m;
        T m_mat[N][M];
    };

    //перегрузка оператора ввода
    template<typename T, int N, int M>
    std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
    {
        for (int i = 0; i < mat.m_n; i++)
            for (int j = 0; j < mat.m_m; j++)
                in >> mat.m_mat[i][j];
        return in;
    }

    //перегрузка оператора вывода
    template<typename T, int N, int M>
    std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
    {
        out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
        for (int i = 0; i < mat.m_n; i++) {
            for (int j = 0; j < mat.m_m; j++)
                out << mat.m_mat[i][j] << " ";
            out << std::endl;
        }
        return out;
    }

    using Vec2i = Matrix<int, 2, 1>;	//соращенное удобное название
    using Vec2d = Matrix<double, 2, 1>;
    using Mat22i = Matrix<int, 2, 2>;
    using Mat22d = Matrix<double, 2, 2>;
    using Mat33i = Matrix<int, 3, 3>;
    using Mat33d = Matrix<double, 3, 3>;
    using Vec4d = Matrix<double, 4, 1>;
    using Mat44d = Matrix<double, 4, 4>;
}
