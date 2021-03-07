#include <iostream>
#include <cstdlib>
#include <ctime>

class Matrix
{
public:
	~Matrix();
	Matrix();
	Matrix(int Size_x, int Size_y);
	void resize(int New_size_x, int New_size_y);
	int getSize_x();
	int getSize_y();
	int** matrix;

private:
	int size_x;
	int size_y;
};

Matrix::Matrix()
{
	size_x = 0;
	size_y = 0;
}

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

void Matrix::resize(int New_size_x, int New_size_y)
{
	size_x = New_size_x;
	size_y = New_size_y;
	matrix = new int* [size_x];
	for (int i = 0; i < size_x; i++)
	{
		matrix[i] = new int[size_y];
	}
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
	int sizeX1, sizeY1, sizeX2, sizeY2, choice, l = 2;
	system("chcp 1251");
	std::cout << "Вас приветствует программа" << std::endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	/*Ввод размеров матрицы пользователем*/
	getValMatrixSize(sizeX1, sizeY1, "Введите размеры первой матрицы");
	getValMatrixSize(sizeX2, sizeY2, "Введите размеры второй матрицы");

	Matrix M1 = Matrix(sizeX1, sizeY1);
	Matrix M2 = Matrix(sizeX2, sizeY2);

	/*Выбор способа заполнения и заполнение матриц*/
	do
	{
		std::cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		std::cin >> choice;
	} while (choice < 1 || choice > 2);
	switch (choice)
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
	while (l < sizeX1 || l < sizeX2 || l < sizeY1 || l < sizeY2)
		l *= 2;
	Matrix M3 = Matrix(l, l);
	Matrix M4 = Matrix(l, l);
	fillMatrixZero(M3);
	fillMatrixZero(M4);
	partiallyCopyMatrix(M3, M1, true);
	partiallyCopyMatrix(M4, M2, true);
	std::cout << "Приведенные матрицы\n";
	showMatrix(M3, "Матрица 1");
	showMatrix(M4, "Матрица 2");

	/*Разбиение матриц на подматрицы и их заполнение*/
	Matrix mat[8];
	for (int i = 0; i < 8; i++)
	{
		mat[i].resize(l / 2, l / 2);
	}

	createPathMatrix(mat[0], M3, l, 0, 0);
	createPathMatrix(mat[1], M3, l, 0, l / 2);
	createPathMatrix(mat[2], M3, l, l / 2, 0);
	createPathMatrix(mat[3], M3, l, l / 2, l / 2);
	createPathMatrix(mat[4], M4, l, 0, 0);
	createPathMatrix(mat[5], M4, l, 0, l / 2);
	createPathMatrix(mat[6], M4, l, l / 2, 0);
	createPathMatrix(mat[7], M4, l, l / 2, l / 2);

	/*Создание промежуточных матриц*/
	Matrix p [7];
	for (int i = 0; i < 7; i++)
	{
		p[i].resize(l / 2, l / 2);
	}

	/*Вычисление значений промежуточных матриц*/
	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			for (int k = 0; k < 7; k++)
			{
				p[k].matrix[i][j] = 0;
			}

			for (int z = 0; z < l / 2; z++)
			{
				p[0].matrix[i][j] += (mat[0].matrix[i][z] + mat[3].matrix[i][z]) * (mat[4].matrix[z][j] + mat[7].matrix[z][j]);
				p[1].matrix[i][j] += (mat[2].matrix[i][z] + mat[3].matrix[i][z]) * mat[4].matrix[z][j];
				p[2].matrix[i][j] += mat[0].matrix[i][z] * (mat[5].matrix[z][j] - mat[7].matrix[z][j]);
				p[3].matrix[i][j] += mat[3].matrix[i][z] * (mat[6].matrix[z][j] - mat[4].matrix[z][j]);
				p[4].matrix[i][j] += (mat[0].matrix[i][z] + mat[1].matrix[i][z]) * mat[7].matrix[z][j];
				p[5].matrix[i][j] += (mat[2].matrix[i][z] - mat[0].matrix[i][z]) * (mat[4].matrix[z][j] + mat[5].matrix[z][j]);
				p[6].matrix[i][j] += (mat[1].matrix[i][z] - mat[3].matrix[i][z]) * (mat[6].matrix[z][j] + mat[7].matrix[z][j]);
			}
		}
	}

	/*Создание вспомогательных матриц*/
	Matrix mat1[4];
	for (int i = 0; i < 4; i++)
	{
		mat1[i].resize(l / 2, l / 2);
	}
	/*Подсчет значений вспомогательных матриц из промежуточных*/
	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			mat1[0].matrix[i][j] = p[0].matrix[i][j] + p[3].matrix[i][j] - p[4].matrix[i][j] + p[6].matrix[i][j];
			mat1[1].matrix[i][j] = p[2].matrix[i][j] + p[4].matrix[i][j];
			mat1[2].matrix[i][j] = p[1].matrix[i][j] + p[3].matrix[i][j];
			mat1[3].matrix[i][j] = p[0].matrix[i][j] - p[1].matrix[i][j] + p[2].matrix[i][j] + p[5].matrix[i][j];
		}
	}

	/*Создание результирующей матрицы*/
	Matrix M5 = Matrix(l, l);

	/*Занесение информации из вспомогательных матриц в результирующую*/
	for (int i = 0; i < l / 2; i++)
	{
		for (int j = 0; j < l / 2; j++)
		{
			M5.matrix[i][j] = mat1[0].matrix[i][j];
			M5.matrix[i][j + l / 2] = mat1[1].matrix[i][j];
			M5.matrix[i + l / 2][j] = mat1[2].matrix[i][j];
			M5.matrix[i + l / 2][j + l / 2] = mat1[3].matrix[i][j];
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