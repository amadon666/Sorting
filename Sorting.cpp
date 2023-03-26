#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
// Пузырьковая сортировка
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                //меняем элементы местами
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Сортировка вставками
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Гномья сортировка
void gnomeSort(int arr[], int n) {
    int i = 0;
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) {
            i++;
        }
        else {
            //меняем элементы местами
            int temp = arr[i];
            arr[i] = arr[i - 1];
            arr[i - 1] = temp;
            i--;
        }
    }
}

// Сортировка выбором
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        std::swap(arr[i], arr[min_index]);
    }
}

// Сортировка Шелла
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Быстрая сортировка
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Функция для обмена значениями элементов
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Выполнение сортировки кучей
void heapify(int arr[], int n, int i)
{
    int largest = i; // Инициализация наибольшего элемента как корневого узла
    int l = 2 * i + 1; // Левый потомок текущего узла
    int r = 2 * i + 2; // Правый потомок текущего узла

    // Если левый потомок больше корня
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Если правый потомок больше, чем наибольший элемент на данный момент
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Если наибольший элемент не корень
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);

        // Рекурсивная обработка поддерева
        heapify(arr, n, largest);
    }
}

// Функция сортировки кучей
void heapSort(int arr[], int n)
{
    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(&arr[0], &arr[i]);

        // вызываем процедуру уменьшения кучи на измененной куче
        heapify(arr, i, 0);
    }
}

// Сортировка слиянием
void merge(int arr[], int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int* L = new int[n1];
    int* R = new int[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

// Сортировка деревом
struct Node
{
    int value;
    Node* left;
    Node* right;
};

void insert(Node*& root, int value)
{
    if (!root)
    {
        root = new Node;
        root->value = value;
        root->left = root->right = NULL;
    }
    else if (value < root->value) insert(root->left, value);
    else if (value > root->value) insert(root->right, value);
}

void inorderTraversal(Node* root)
{
    if (!root) return;
    inorderTraversal(root->left);
    std::cout << root->value << " ";
    inorderTraversal(root->right);
}

void treeSort(int arr[], int size) {
    Node* root = NULL;
    for (int i = 0; i < size; i++)
        insert(root, arr[i]);
    inorderTraversal(root);
}

//===
void gravitationalSort(int* arr, int n) {
    int* temp = new int[n];
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] < arr[i])
                count++;
        }
        temp[count] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
    delete[] temp;
}

void bucketSort(std::vector<float>& arr) {
    int n = arr.size();

    if (n == 0) return;

    // Создаем n пустых ведер
    std::vector<float>* buckets = new std::vector<float>[n];

    // Распределение элементов по ведрам
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i];
        if (bucketIndex >= n) {
            bucketIndex = n - 1;
        }
        buckets[bucketIndex].push_back(arr[i]);
    }

    // Сортировка каждого ведра
    for (int i = 0; i < n; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // Объединение элементов из ведер
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (auto& item : buckets[i]) {
            arr[index++] = item;
        }
    }
    delete[] buckets;
}

void countingSort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    std::vector<int> count(10, 0);

    // подсчет частот
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // суммирование частот
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // построение выходного массива
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // копирование выходного массива в исходный
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Поразрядная сортировка
void radixSort(std::vector<int>& arr) {
    // поиск максимального элемента
    int max_element = arr[0];
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_element) {
            max_element = arr[i];
        }
    }

    // сортировка по разрядам
    for (int exp = 1; max_element / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

void insertionSort_forTimsort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void merge_forTimsort(std::vector<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    std::vector<int> left(len1), right(len2);
    for (int i = 0; i < len1; i++) {
        left[i] = arr[l + i];
    }
    for (int i = 0; i < len2; i++) {
        right[i] = arr[m + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}

void timSort(std::vector<int>& arr, int n) {
    const int RUN = 32;

    for (int i = 0; i < n; i += RUN) {
        insertionSort_forTimsort(arr, i, std::min((i + RUN - 1), (n - 1)));
    }

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));
            merge_forTimsort(arr, left, mid, right);
        }
    }
}


// ======== ТЕСТЫ ===========
void bubblesort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    bubbleSort(arr, arr_length);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения bubblesort: " << duration.count() << " ms" << std::endl;
}

void insertionsort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    insertionSort(arr, arr_length);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения insertionsort: " << duration.count() << " ms" << std::endl;
}

void gnomesort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    gnomeSort(arr, arr_length);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения gnomeSort: " << duration.count() << " ms" << std::endl;
}

void selectionsort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    selectionSort(arr, arr_length);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения selectionsort: " << duration.count() << " ms" << std::endl;
}

void shellsort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    shellSort(arr, arr_length);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения shellsort: " << duration.count() << " ms" << std::endl;
}

void quicksort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr_length-1);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения quickSort: " << duration.count() << " ms" << std::endl;
}

void heapsort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    heapSort(arr, arr_length - 1);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения heapSort: " << duration.count() << " ms" << std::endl;
}

void mergesort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);

    auto start_time = std::chrono::high_resolution_clock::now();
    mergeSort(arr, 0, arr_length - 1);
    auto end_time = std::chrono::high_resolution_clock::now();
    printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения mergeSort: " << duration.count() << " ms" << std::endl;
}

void treeSort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);
    std::cout << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    treeSort(arr, arr_length - 1);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << std::endl;
    //printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения treeSort: " << duration.count() << " ms" << std::endl;
}

void gravitationalSort_test() {
    const int count = 70;
    int* arr = new int[count];
    srand(time(NULL));

    for (int i = 0; i < count; ++i) {
        arr[i] = (rand() % count);
    }
    int arr_length = count;
    printArray(arr, arr_length);
    std::cout << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    gravitationalSort(arr, arr_length - 1);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << std::endl;
    //printArray(arr, arr_length);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения gravitationalSort: " << duration.count() << " ms" << std::endl;
}

template<typename T>
void printVector(std::vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
}

void bucketSort_test() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 10);

    std::vector<int> vec_int(70);
    for (int i = 0; i < vec_int.size(); ++i) {
        vec_int[i] = distr(gen);
    }

    std::vector<float> vec_float(vec_int.size());

    // Используем алгоритм std::transform с лямбда-функцией в качестве аргумента
    std::transform(vec_int.begin(), vec_int.end(), vec_float.begin(),
        [](const int& intValue) {return static_cast<float>(intValue); });

    printVector(vec_float);

    auto start_time = std::chrono::high_resolution_clock::now();
    bucketSort(vec_float);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl;
    printVector(vec_float);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения bucketSort: " << duration.count() << " ms" << std::endl;
}

void radixSort_test() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 10);

    std::vector<int> vec_int(70);
    for (int i = 0; i < vec_int.size(); ++i) {
        vec_int[i] = distr(gen);
    }

    printVector(vec_int);

    auto start_time = std::chrono::high_resolution_clock::now();
    radixSort(vec_int);
    auto end_time = std::chrono::high_resolution_clock::now();
    
    std::cout << std::endl << std::endl;
    printVector(vec_int);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения radixSort: " << duration.count() << " ms" << std::endl;
}

void timSort_test() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 10);

    std::vector<int> vec_int(60);
    for (int i = 0; i < vec_int.size(); ++i) {
        vec_int[i] = distr(gen);
    }

    printVector(vec_int);

    auto start_time = std::chrono::high_resolution_clock::now();
    timSort(vec_int, vec_int.size());
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    printVector(vec_int);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Время выполнения timSort: " << duration.count() << " ms" << std::endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");
   /* bubblesort_test();
    insertionsort_test();
    gnomesort_test();
    selectionsort_test();
    shellsort_test();
    quicksort_test();
    mergesort_test();
    heapsort_test();*/
    //treeSort_test();
    //gravitationalSort_test();
    //bucketSort_test();
    //radixSort_test();
    //timSort_test();
    
    return 0;
}

