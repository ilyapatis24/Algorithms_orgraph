#include <fstream>
#include <iostream>

struct DirectedGraph // Структура ориентированный граф
{
private:
    bool** adjacencyMatrix; // Матрица смежности
    int vertices; // Количество вершин

public:
    DirectedGraph(int vertices) // Конструктор
    {
        this->vertices = vertices;
        adjacencyMatrix = new bool* [vertices]();
        for (int i = 0; i < vertices; ++i)
        {
            adjacencyMatrix[i] = new bool[vertices]();
        }
    }
    void clear() // Очищение памяти.
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
        adjacencyMatrix = nullptr;
    }

    // Сеттер
    void setVertex(int vertexA, int vertexB, bool edge) // Задание значения элемента матрицы смежности
    {
        adjacencyMatrix[vertexA][vertexB] = edge;
    }

    // Геттеры
    bool getEdge(int vertexA, int vertexB) // Получение элемента матрицы смежности
    {
        return adjacencyMatrix[vertexA][vertexB];
    }

    int getVertices() // Получение количества вершин
    {
        return vertices;
    }
};

void fillGraph(DirectedGraph& graph, int vertices, std::string file) // Заполнение графа из файла
{
    std::ifstream fin(file);

    int n = 0; // Переменная для считывания информации из файла

    //Пропускаю первое значение (размерность)
    fin >> n;

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            fin >> n;
            graph.setVertex(i, j, static_cast<bool>(n)); //Заполняю матрицу смежности
        }
    }

    fin.close();
}

void printDirectedGraph(DirectedGraph& graph) //Вывод оргграфа
{
    int* arcs = new int[graph.getVertices()](); //Временный массив для хранения дуг текущей вершины
    std::cout << "Текстовый вид орграфа: " << std::endl;
    for (int i = 0; i < graph.getVertices(); ++i) //Пробегаюсь по строчкам матрицы смежностей (вершинам)
    {
        int countArc = 0; //Переменная для подсчета дуг

        for (int j = 0; j < graph.getVertices(); ++j)//Пробегаюсь по связям с вершинами из текущей вершины
        {
            if (graph.getEdge(i, j)) //Если связь есть, то добавляю вершину во временный массив
            {
                arcs[countArc++] = j + 1;
            }
        }

        if (countArc != 0) //Если смежные вершины нашлись, то печатаю их
        {
            std::cout << i + 1 << ": ";
            for (int k = 0; k < countArc; ++k)
            {
                std::cout << arcs[k] << " ";
            }
        }
        else //Иначе нет
        {
            std::cout << i + 1 << ": нет";
        }
        std::cout << std::endl;
    }

    delete[] arcs;
    arcs = nullptr;
}

int main(int argc, char** argv)
{
    system("chcp 1251");
    std::string file = "input.txt";
    std::ifstream fin(file);

    if (fin.is_open())
    {
        int vertices = 0;// Количество вершин

        //Считываю количество вершин из файла
        fin >> vertices;
        fin.close();

        DirectedGraph graph(vertices); // Создаю граф

        fillGraph(graph, vertices, file); //Заполоняю его из файла

        printDirectedGraph(graph); //Вывожу оргграф

        graph.clear(); // Очищаю память
    }
    else
    {
        std::cout << "Не получилось открыть файл!" << std::endl;
    }

    return 0;
}