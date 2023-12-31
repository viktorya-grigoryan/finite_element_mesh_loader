# finite_element_mesh_loader
Разработать конечно-элементный загрузчик сеток.

	1. Предусмотреть возможность работы с различными форматами файлов конечно-элементной (КЭ) сетки. Создать базовый класс MeshLoader. Объявить в нем чисто виртуальный метод loadMesh.
 
	2. Создать производный от MeshLoader класс AneuMeshLoader, в котором переопределить метод loadMesh. Данный класс должен обеспечивать загрузку сетки из формата .aneu.
 
	3. Предусмотреть возможность консольного запуска бинарного файла и передачи имени загружаемого файла в параметрах командной строки.
 
	4. В отдельном h-файле создать следующие вспомогательные типы данных:
	Node – тип данных «узел». Хранит ID узла (>= 1), декартовы координаты узла и флаг, определяющий, является ли данный узел вершиной КЭ или его внутренним узлом.
	FiniteElement – тип данных «конечный элемент». Хранит ID КЭ (>= 1), ID геометрической области, которой принадлежит КЭ по данным файла сетки (например, ID грани, которой принадлежит граничный КЭ (треугольник) или ID объема, которому принадлежит объемный КЭ (тетраэдр)), список ID узлов КЭ.
 
	5. Предоставить следующие методы:
	методы, позволяющие получить STL-контейнеры узлов, конечных элементов и граничных элементов ;
	метод, позволяющий найти КЭ по ID трех его вершинных узлов, для чего использовать алгоритм find_if и создать необходимый предикат. Предусмотреть возможность наличия нескольких КЭ с данными тремя узлами;
	метод, позволяющий найти КЭ по ребру, заданному с помощью ID двух узлов. Предусмотреть возможность наличия нескольких КЭ с данным ребром;
	метод, возвращающий контейнер граничных узлов по ID границы;
	метод, возвращающий контейнер КЭ с заданным ID области;
	метод, возвращающий контейнер граничных КЭ с заданным ID границы;
	метод, производящий вставку новых узлов в середины ребер существующих КЭ (включая граничные КЭ). Учесть, что обновляются как списки узлов каждого КЭ, так общий список узлов сетки;
	метод, создающий контейнер, n-ый элемент которого хранит контейнер всех «соседей» по ребрам для узла n;
	методы, реализующие отформатированный вывод Node и FiniteElement в заданный поток;
	при необходимости возможно определение других методов и типов данных.

Основные требования:

	1. Предполагается, что количество узлов и элементов в сетке очень велико. В связи с этим сложность каждого приведенного метода должна быть строго меньше O(n^2).
 
	2. Загрузчик должен быть реализован на основе использования контейнеров, итераторов и алгоритмов STL. Использование циклов должно быть сведено к минимуму.
 
	3. Ошибки и нештатные ситуации загрузки сетки обработать посредством генерации исключительных ситуаций (при необходимости разработать иерархию исключений). Примерами исключительных ситуаций может быть: не найден файл сетки, неверный формат файла сетки т.п.
 
	4. Сетки в формате .neu могут быть сгенерированы в программе NetGen (http://sourceforge.net/projects/netgen-mesher/). В формат .aneu данный файл можно преобразовать, добавив в neu-файле в строку с количеством узлов размерность пространства, в строку с количеством КЭ – число узлов в одном КЭ, в строку с количеством граничных КЭ – число узлов в одном граничном КЭ.

