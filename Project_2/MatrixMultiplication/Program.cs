
using System;
using System.Linq;
using System.Threading.Tasks;

class MatrixMultiplication
{
    static void Main()
    {
        const int N = 2000; // Размерность матриц

        // Создание матриц A, B и C
        double[,] A = new double[N, N];
        double[,] B = new double[N, N];
        double[,] C = new double[N, N];

        // Инициализация матриц случайными числами
        Random rand = new Random();
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                A[i, j] = rand.NextDouble() * 100; // Случайные числа от 0 до 100
                B[i, j] = rand.NextDouble() * 100;
            }
        }

        // Замер времени начала
        var startTime = DateTime.Now;

        // Параллельное перемножение матриц с использованием Task
        int numTasks = 4; // Количество параллельных задач
        Task[] tasks = new Task[numTasks];
        int rowsPerTask = N / numTasks;

        for (int t = 0; t < numTasks; t++)
        {
            int startRow = t * rowsPerTask;
            int endRow = (t == numTasks - 1) ? N : (t + 1) * rowsPerTask;

            tasks[t] = Task.Run(() => MultiplyRows(startRow, endRow, A, B, C));
        }

        // Ожидание завершения всех задач
        Task.WhenAll(tasks).Wait();

        // Замер времени окончания
        var endTime = DateTime.Now;
        Console.WriteLine($"Время выполнения: {(endTime - startTime).TotalSeconds} секунд");
    }

    // Функция для перемножения строк матриц A и B
    static void MultiplyRows(int startRow, int endRow, double[,] A, double[,] B, double[,] C)
    {
        for (int i = startRow; i < endRow; i++)
        {
            for (int j = 0; j < A.GetLength(1); j++)
            {
                for (int k = 0; k < A.GetLength(1); k++)
                {
                    C[i, j] += A[i, k] * B[k, j];
                }
            }
        }
    }
}

