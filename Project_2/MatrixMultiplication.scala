import scala.concurrent._
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._
import scala.util.Random

object MatrixMultiplication extends App {
  val N = 2000  // Размерность матриц
  val numTasks = 4  // Количество параллельных задач

  // Инициализация матриц A, B и C случайными значениями
  val A = Array.fill(N, N)(Random.nextDouble() * 100)
  val B = Array.fill(N, N)(Random.nextDouble() * 100)
  val C = Array.ofDim[Double](N, N)

  // Функция для параллельного перемножения строк матриц A и B
  def multiplyRows(startRow: Int, endRow: Int): Unit = {
    for (i <- startRow until endRow) {
      for (j <- 0 until N) {
        C(i)(j) = (0 until N).map(k => A(i)(k) * B(k)(j)).sum
      }
    }
  }

  // Замер времени выполнения
  val startTime = System.nanoTime()

  // Разделение задачи на несколько параллельных Future
  val rowsPerTask = N / numTasks
  val tasks = (0 until numTasks).map { t =>
    val startRow = t * rowsPerTask
    val endRow = if (t == numTasks - 1) N else (t + 1) * rowsPerTask
    Future { multiplyRows(startRow, endRow) }
  }

  // Ожидание завершения всех задач
  Await.result(Future.sequence(tasks), Duration.Inf)

  // Вывод времени выполнения
  val endTime = System.nanoTime()
  println(s"Время выполнения: ${(endTime - startTime) / 1e9} секунд")
}

