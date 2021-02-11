#include <iostream>
#include <cstdlib>
#include <ctime>

class Matrix
{
public:
	~Matrix();
	Matrix(int Size_x, int Size_y);
	int getSize_x();
	int getSize_y();
	int** matrix;

private:
	int size_x;
	int size_y;
};

Matrix::Matrix(int Size_x, int Size_y)
{
	size_x = Size_x;
	size_y = Size_y;
	matrix = new int* [size_x];
	for (int i = 0; i < size_x; i++)
	{
		matrix[i] = new int[size_y];
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < this->size_x;i++)
		delete [] matrix[i];
	delete [] matrix;
}

int Matrix::getSize_x()
{
	return size_x;
}

int Matrix::getSize_y()
{
	return size_y;
}

void fillMatrixByKeyboard(Matrix& M)
{
	for (int i = 0; i < M.getSize_x(); i++)
		for (int j = 0; j < M.getSize_y(); j++)
			std::cin >> M.matrix[i][j];
}

void fillMatrixRandom(Matrix& M)
{
	for (int i = 0; i < M.getSize_x(); i++)
		for (int j = 0; j < M.getSize_y(); j++)
			M.matrix[i][j] = rand() % 10;
}

void fillMatrixZero(Matrix& M)
{
	for (int i = 0; i < M.getSize_x(); i++)
		for (int j = 0; j < M.getSize_y(); j++)
			M.matrix[i][j] = 0;
}

void mallocMatrix(int size_x, int size_y)
{
	int** matrix = new int* [size_x];
	for (int i = 0; i < size_x; i++)
	{
		matrix[i] = new int[size_y];
	}
}

void getValMatrixSize(int& x, int& y, std::string text)
{
	do
	{
		std::cout << text << "\n";
		std::cin >> x >> y;
	} while (x <= 0 || y <= 0);
}

void showMatrix(Matrix& M, std::string text)
{
	std::cout << "\n" << text << "\n\n";
	for (int i = 0; i < M.getSize_x(); i++)
	{
		for (int j = 0; j < M.getSize_y(); j++)
			std::cout << M.matrix[i][j] << " ";
		std::cout << std::endl;
	}
}

void partiallyCopyMatrix(Matrix& copyTo, Matrix& copyFrom, bool isFirstBigger)
{
	int sizeX;
	int sizeY;

	if (isFirstBigger)
	{
		sizeX = copyFrom.getSize_x();
		sizeY = copyFrom.getSize_y();
	}
	else
	{
		sizeX = copyTo.getSize_x();
		sizeY = copyTo.getSize_y();
	}

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
			copyTo.matrix[i][j] = copyFrom.matrix[i][j];
		std::cout << std::endl;
	}
}

void createPathMatrix(Matrix& path, Matrix& mainMatrix, int l, int offset_x, int offset_y)
{
	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
			path.matrix[i][j] = mainMatrix.matrix[i + offset_x][j + offset_y];
	}
}

int main()
{
	srand(time(NULL));
	int n1, m1, n2, m2, k, l = 2;
	system("chcp 1251");
	std::cout << "Вас приветствует программа" << std::endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	/*Ввод размеров матрицы пользователем*/
	getValMatrixSize(n1, m1, "Введите размеры первой матрицы");
	getValMatrixSize(n2, m2, "Введите размеры второй матрицы");

	Matrix M1 = Matrix(n1, m1);
	Matrix M2 = Matrix(n2, m2);

	/*Выбор способа заполнения и заполнение матриц*/
	do
	{
		std::cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		std::cin >> k;
	} while (k < 1 || k > 2);
	switch (k)
	{
	case 1:
		fillMatrixByKeyboard(M1);
		fillMatrixByKeyboard(M2);
		showMatrix(M1, "Матрица 1");
		showMatrix(M2, "Матрица 2");
		break;
	case 2:
		fillMatrixRandom(M1);
		fillMatrixRandom(M2);
		showMatrix(M1, "Матрица 1");
		showMatrix(M2, "Матрица 2");
		break;
	}

	/*Приведение матриц к требуемому размеру*/
	while (l < n1 || l < n2 || l < m1 || l < m2)
		l *= 2;
	Matrix M3 = Matrix(l,l);
	Matrix M4 = Matrix(l,l);
	fillMatrixZero(M3);
	fillMatrixZero(M4);
	partiallyCopyMatrix(M3, M1, true);
	partiallyCopyMatrix(M4, M2, true);
	std::cout << "Приведенные матрицы\n";
	showMatrix(M3, "Матрица 1");
	showMatrix(M4, "Матрица 2");

	/*Разбиение матриц на подматрицы и их заполнение*/
	Matrix mat1 = Matrix(l / 2, l / 2);
	Matrix mat2 = Matrix(l / 2, l / 2);
	Matrix mat3 = Matrix(l / 2, l / 2);
	Matrix mat4 = Matrix(l / 2, l / 2);
	Matrix mat5 = Matrix(l / 2, l / 2);
	Matrix mat6 = Matrix(l / 2, l / 2);
	Matrix mat7 = Matrix(l / 2, l / 2);
	Matrix mat8 = Matrix(l / 2, l / 2);

	createPathMatrix(mat1, M3, l, 0, 0);
	createPathMatrix(mat2, M3, l, 0, l / 2);
	createPathMatrix(mat3, M3, l, l / 2, 0);
	createPathMatrix(mat4, M3, l, l / 2, l / 2);
	createPathMatrix(mat5, M4, l, 0, 0);
	createPathMatrix(mat6, M4, l, 0, l / 2);
	createPathMatrix(mat7, M4, l, l / 2, 0);
	createPathMatrix(mat8, M4, l, l / 2, l / 2);

	/*Создание промежуточных матриц*/
	Matrix p1 = Matrix(l / 2, l / 2);
	Matrix p2 = Matrix(l / 2, l / 2);
	Matrix p3 = Matrix(l / 2, l / 2);
	Matrix p4 = Matrix(l / 2, l / 2);
	Matrix p5 = Matrix(l / 2, l / 2);
	Matrix p6 = Matrix(l / 2, l / 2);
	Matrix p7 = Matrix(l / 2, l / 2);

	/*Вычисление значений промежуточных матриц*/
	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			p1.matrix[i][j] = 0;
			p2.matrix[i][j] = 0;
			p3.matrix[i][j] = 0;
			p4.matrix[i][j] = 0;
			p5.matrix[i][j] = 0;
			p6.matrix[i][j] = 0;
			p7.matrix[i][j] = 0;

			for (int z = 0; z < l / 2; z++)
			{
				p1.matrix[i][j] += (mat1.matrix[i][z] + mat4.matrix[i][z]) * (mat5.matrix[z][j] + mat8.matrix[z][j]);
				p2.matrix[i][j] += (mat3.matrix[i][z] + mat4.matrix[i][z]) * mat5.matrix[z][j];
				p3.matrix[i][j] += mat1.matrix[i][z] * (mat6.matrix[z][j] - mat8.matrix[z][j]);
				p4.matrix[i][j] += mat4.matrix[i][z] * (mat7.matrix[z][j] - mat5.matrix[z][j]);
				p5.matrix[i][j] += (mat1.matrix[i][z] + mat2.matrix[i][z]) * mat8.matrix[z][j];
				p6.matrix[i][j] += (mat3.matrix[i][z] - mat1.matrix[i][z]) * (mat5.matrix[z][j] + mat6.matrix[z][j]);
				p7.matrix[i][j] += (mat2.matrix[i][z] - mat4.matrix[i][z]) * (mat7.matrix[z][j] + mat8.matrix[z][j]);
			}
		}
	}

	/*Создание вспомогательных матриц*/
	Matrix mat9 = Matrix(l / 2, l / 2);
	Matrix mat10 = Matrix(l / 2, l / 2);
	Matrix mat11 = Matrix(l / 2, l / 2);
	Matrix mat12 = Matrix(l / 2, l / 2);

	/*Подсчет значений вспомогательных матриц из промежуточных*/
	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			mat9.matrix[i][j] = p1.matrix[i][j] + p4.matrix[i][j] - p5.matrix[i][j] + p7.matrix[i][j];
			mat10.matrix[i][j] = p3.matrix[i][j] + p5.matrix[i][j];
			mat11.matrix[i][j] = p2.matrix[i][j] + p4.matrix[i][j];
			mat12.matrix[i][j] = p1.matrix[i][j] - p2.matrix[i][j] + p3.matrix[i][j] + p6.matrix[i][j];
		}
	}

	/*Создание результирующей матрицы*/
	Matrix M5 = Matrix(l, l);

	/*Занесение информации из вспомогательных матриц в результирующую*/
	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			M5.matrix[i][j] = mat9.matrix[i][j];
			M5.matrix[i][j + l / 2] = mat10.matrix[i][j];
			M5.matrix[i + l / 2][j] = mat11.matrix[i][j];
			M5.matrix[i + l / 2][j + l / 2] = mat12.matrix[i][j];
		}
	}

	/*Выравнивание границ результирующей матрицы*/
	int x = 0, f = 100, s = 100;
	for (int i = 0; i < l; i++)
	{
		x = 0;
		for (int j = 0; j < l; j++)
		{
			if (M5.matrix[i][j] != 0)
			{
				x++;
				f = 100;
				s = 100;
			}
		}
		if (x == 0) 
		{
			if (i < f)
			{
				f = i;
			}
			if (i < s)
			{
				s = i;
			}
		}
	}

	Matrix M6 = Matrix(f, s);
	partiallyCopyMatrix(M6, M5, false);

	/*Вывод результирующей матрицы*/
	showMatrix(M6, "Результирующая матрица");

	system("pause");
	return 0;
}