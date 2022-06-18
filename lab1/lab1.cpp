#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>

// структура с полями о городе
struct city {
    char cityName[16];
    float coordX;
    float coordY;
    unsigned int numberPeople;
};

// структура для подсчета расстояния
struct algorithmData {
    int* curSubsequence; // последовательность городов на текущем обходе
    int* minSubsequence; // последовательность с минимальным расстоянием на текущем обходе
    int* lookedCity; // маркерованные или пройденные города на текущем обходе
    float minlength; // минимальное расстояние на текущем обходе
};


bool isNumber(char x) {

    if ((x >= '0' && x <= '9') || x == ',' || x == '.')
        return true;
    return false;
}

bool isSymbol(char x) {

    if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
        return true;
    if ((x > 'А' && x < 'Я') || (x > 'а' && x < 'я'))
        return true;
    return false;
}
int inputFileCount(city* mas) {
    printf("\nПрежде чем начинать чтение из файла убедитесь, что файл 'cityData.txt' находится в папке с проектом и нажмите enter:");
    char wait[2];
    getchar();
    getchar();
    FILE* fp;
    char name[] = "cityData.txt";
    int inpt = 1;
    while (fopen_s(&fp, name, "r") != 0) {
        printf("\nНе удалось открыть файл.Введите \n0 - Выход\n1 - Повторная попытка \nВвод команды: ");
        if (inpt == 0)
            break;
        int chekInput = scanf_s("%d", &inpt);
        while (chekInput < 0 || (inpt < 0 && inpt > 1)) {
            printf("\nОшибка ввода. Попробуйте снова.\nВвод команды: ");
            chekInput = scanf_s("%d", &inpt);
        }
            if (inpt == 0) {
                return -1;
            }
            if (inpt == 1) {
                inputFileCount(mas);
            }
        
    }
    int cityCount;
    fscanf_s(fp, "%d", &cityCount);
    int k = fgetc(fp);
    return cityCount;

}
void inputFile(city* mas) {
    FILE* fp;
    char name[] = "cityData.txt";
    int inpt = 1;
    fopen_s(&fp, name, "r");
    int cityCount;
    fscanf_s(fp, "%d", &cityCount);
    int k = fgetc(fp);


    for (int i = 0; i < cityCount; i++) {
        char str[100] = { ' ' };
        fgets(str, 100, fp);
        int j;
        // поиск имени в считанной строке

        for (j = 0; str[j] != ' '; j++) {}
        strncpy_s(mas[i].cityName, str, j);

        int indS = -1;
        int indE = -1;
        // поиск координаты х
        for (j = 0; j < strlen(str); j++) {
            if (isNumber(str[j]) && indS == -1) {
                indS = j;
                indE = j;
            }
            if (isNumber(str[j]) && indS != -1 && (str[j + 1] == ' ' || j == strlen(str) - 1)) {
                indE = j;
                break;
            }
        }

        char numb[20] = {};
        int nmb = 0;
        for (int q = indS; q < indE + 1; q++, nmb++) {
            if (str[q] == '.')
                numb[nmb] = ',';
            else
                numb[nmb] = str[q];
        }
        mas[i].coordX = atof(numb);


        // поиск координаты Y
        indS = indE + 2;
        for (j = indS; j < strlen(str); j++) {
            if (isNumber(str[j]) && (str[j + 1] == ' ' || j == strlen(str) - 1)) {
                indE = j;
                break;
            }
        }
        nmb = 0;
        nmb = '\0';
        for (int q = indS; q < indE + 1; q++, nmb++) {
            if (str[q] == '.')
                numb[nmb] = ',';
            else
                numb[nmb] = str[q];
        }
        mas[i].coordY = atof(numb);

        //поиск кол-ва жителей
        indS = indE + 2;
        for (j = indS; j < strlen(str); j++) {
            if (isNumber(str[j]) && (str[j + 1] == ' ' || str[j + 1] == '\n')) {
                indE = j;
                break;
            }
        }
        nmb = 0;
        nmb = '\0';
        for (int q = indS; q < indE + 1; q++, nmb++) {
            numb[nmb] = str[q];
        }
        mas[i].numberPeople = atoi(numb);

    }

    fclose(fp);
}

int saveFile(city* mas, algorithmData* data, int cityCount) {
    printf("\nПрежде чем начинать сохранять в файл убедитесь, что файл 'cityResult.txt' находится в папке с проектом и нажмите enter:");
    char wait[2];
    getchar();
    getchar();
    FILE* fp;
    char name[] = "cityResult.txt";
    int inpt = 1;
    while (fopen_s(&fp, name, "w") != 0) {
        printf("\nНе удалось открыть файл.Введите \n0 - Выход\n1 - Повторная попытка \nВвод команды: ");
        if (inpt == 0)
            break;
        int chekInput = scanf_s("%d", &inpt);
        while (chekInput < 0 || (inpt < 0 && inpt > 1)) {
            printf("\nОшибка ввода. Попробуйте снова.\nВвод команды: ");
            int chekInput = scanf_s("%d", &inpt);
            if (inpt == 0) {
                return -1;
            }
            if (inpt == 1) {
                printf("Поместите файл для сохранения и нажмите enter:");
                getchar();
                getchar();
            }
        }
    }

    fprintf(fp, "Информация о городах:\n");
    for (int i = 0; i < cityCount; i++) {
        fprintf(fp, "\nГород №%d", i + 1);
        fprintf(fp, "\n Город: %s", mas[i].cityName);
        fprintf(fp, "\n Координата по Х: %f", mas[i].coordX);
        fprintf(fp, "\n Координата по У: %f", mas[i].coordY);
        fprintf(fp, "\n Количество жителей: %d", mas[i].numberPeople);
    }

    fprintf(fp, "\n\n\nИнформация о последнем пройденном пути коммивояжёра\n");
    fprintf(fp, "\nКратчайший путь: %f\n", data->minlength);
    fprintf(fp, "\nПуть коммивояжёра:\n");
    for (int j = 0; j < cityCount; j++) {
        fprintf(fp, "%d)Город #%d ", j + 1, &data->minSubsequence[j] + 1);
        fprintf(fp, "%s \n", &mas[data->minSubsequence[j]].cityName);
    }


    fclose(fp);
}

void inputConsole(city* mas, int cityCount) {


    for (int i = 0; i < cityCount; i++) {

        printf("\nГород №%d", i + 1);

        printf("\n Введите название города: ");
        scanf_s("%s", mas[i].cityName, 10);

        int checkInput = -1;
        printf("\n Введите координату города по Х: ");
        while (checkInput <= 0) {
            checkInput = scanf_s("%f", &mas[i].coordX);
            if (checkInput > 0)
                break;
            else {
                printf("\n Некорректный ввод, попробуйте снова: ");
                getchar();
                getchar();

            }

        }

        checkInput = -1;
        printf("\n Введите координату города по У: ");
        while (checkInput <= 0) {
            checkInput = scanf_s("%f", &mas[i].coordY);
            if (checkInput > 0)
                break;
            else {
                printf("\n Некорректный ввод, попробуйте снова: ");
                getchar();
                getchar();
            }
        }

        printf("\n Введите количество жителей: ");
        checkInput = -1;
        while (checkInput < 0) {
            scanf_s("%d", &checkInput);
            if (checkInput >= 0)
                mas[i].numberPeople = checkInput;
            else
                printf("\nНекорректный ввод, попробуйте снова: ");
        }


    }
}

void output(city* mas, int cityCount) {
    for (int i = 0; i < cityCount; i++) {
        printf("\n\nГород №%d", i + 1);
        printf("\n Город: %s", mas[i].cityName);
        printf("\n Координата по Х: %f", mas[i].coordX);
        printf("\n Координата по У: %f", mas[i].coordY);
        printf("\n Количество жителей: %d", mas[i].numberPeople);
    }
}

// подсчет расстояния от indexCurrent до indexTo
float dimLength(city* mas, int indexCurrent, int indexTo) {
    if (indexCurrent == indexTo)
        return 0;

    float length;

    float X1 = (mas + indexCurrent)->coordX;
    float Y1 = (mas + indexCurrent)->coordY;

    float X2 = (mas + indexTo)->coordX;
    float Y2 = (mas + indexTo)->coordY;

    length = sqrt(pow(X2 - X1, 2) + pow(Y2 - Y1, 2));
    return length;
}

// функция подсчета кратчайшего пути по всем городам
void shortestWay(city* mas, algorithmData* data, int step, int cityN, float length, int cityCount) {
    // step - шаг обхода
    // cityN - текущий просматриваемый город
    // length = текущий путь
    if (data->minlength < length && data->minlength != -1) // Оптимизация
        return;

    if (step == cityCount) {
        if (data->minlength == -1 || length < data->minlength) {// Обход закончен - фиксировать минимум
            data->minlength = length;// Запомнить длину и последовательность
            for (int i = 0; i < cityCount; i++)// Заполняем массив минимального прохода элементами текущего(нового минимумуа) прохода
                data->minSubsequence[i] = data->curSubsequence[i];
        }
        return;
    }

    if (data->lookedCity[cityN] == 1)// Повторное прохождение
        return;


    data->curSubsequence[step] = cityN;// В последовательность обхода на текущем ШАГЕ добавлен просматриваемый ГОРОДН
    data->lookedCity[cityN] = 1;// Отметить прохождение
    for (int i = 0; i < cityCount; i++) {// Просмотр соседей
        if (cityN == i)
            continue;// Если проверяем путь от города до самого себя - пропускаем
        if ((step + 1) != cityCount)
            shortestWay(mas, data, step + 1, i, length + dimLength(mas, cityN, i), cityCount);// Рекурсивный вызов для соседнего
        else
            shortestWay(mas, data, step + 1, i, length, cityCount);  // Рекурсивный вызов для соседнего
    }                                                                               // "города" с учетом расстояния до него
    data->lookedCity[cityN] = 0;// Зануляем посещение 
}

int max(int x1, int x2) {
    if (x1 >= x2)
        return x1;
    else
        return x2;
}

// перестановка городов с индексами ind и ind + 1 
void swapCity(city* mas, int indexCurreht, int indexTo) {
    city temp = *(mas + indexCurreht);
    *(mas + indexCurreht) = *(mas + indexTo);
    *(mas + indexTo) = temp;

}

// функция сравнения слов посимвольно
bool wordsCompare(char* str1, char* str2) {
    if (strlen(str1) > strlen(str2))
        return false;
    if (strlen(str1) < strlen(str2))
        return true;

    char* p1 = str1;
    char* p2 = str2;

    while (*str1 == *str2) {
        p1 = str1;
        p2 = str2;
        str1++;
        str2++;
        if (*str1 == '\n' || *str1 == '\0')
            return false;
    }
    if (*p1 < *p2)
        return true;
    else
        return false;
}

// функция проверки слов на равенство
bool wordsEqual(char* str1, char* str2) {
    if (strlen(str1) != strlen(str2)) // если длина одной строки меньше другой, то очевидно что длинная больше
        return false;

    char* p1 = str1;
    char* p2 = str2;

    while (*str1 == *str2) {
        p1 = str1;
        p2 = str2;
        str1++;
        str2++;
        if (*str1 == '\n' || *str1 == '\0')
            break;
    }

    if (*p1 == *p2)
        return true;
    else
        return false;
}

// функция сортировки массива структур по имени города
void sortByName(city* mas, int cityCount) {
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount - 1; j++) {
            if (wordsCompare((mas + j)->cityName, (mas + j + 1)->cityName))
                swapCity(mas, j, j + 1);
        }
    }
}

// бинарный поиск города по имени
int binSearch(city* mas, int left, int right, char* search) {
    int mid = (left + right) / 2;

    if (wordsEqual((mas + mid)->cityName, search))
        return mid + 1;

    if (left >= right)
        return -1;
    else {
        if (!wordsCompare((mas + mid)->cityName, search))
            binSearch(mas, mid + 1, right, search);
        else
            binSearch(mas, left, mid - 1, search);
    }

}

// функция выделения памяти и выставления изначальных параметров
void defaultData(algorithmData* data, int cityCount) {
    data->curSubsequence = (int*)calloc(cityCount, sizeof(int));
    data->minSubsequence = (int*)calloc(cityCount, sizeof(int));
    data->lookedCity = (int*)calloc(cityCount, sizeof(int));
    data->minlength = -1;

}

// функция освобождения памяти
void freeData(algorithmData* data, city* mas) {

    free(data->curSubsequence);
    free(data->minSubsequence);
    free(data);

    free(mas);
}

using namespace std;
int main() {
    setlocale(LC_ALL, "Rus");
    printf("Задача Коммивояжёра - пройти n городов без повторений за минимальный путь.");
    printf("\nДля того чтобы программа работала необходимо заполнить данные о городах и их количестве.");


    int inpt;
    int cityCount = -1;
    city* mas = NULL;
    algorithmData* data = (algorithmData*)calloc(1, sizeof(algorithmData));
    //Ввод данных
    while (1) {
        printf("\nВведите \n0 - Ввод данных с консоли \n1 - Ввод данных из файла\n2 - Выход\n\nВвод команды: ");

        scanf_s("%d", &inpt);
        // Ввод с консоли
        if (inpt == 0) {
            printf("\nВведите информацию о городах.");
            printf("\nВведите кол-во городов: ");
            while (cityCount < 0) {
                inpt = scanf_s("%d", &cityCount);
                if (inpt > 0 && cityCount > 0)
                    break;
                else {
                    printf("\n Некорректный ввод, попробуйте снова: ");
                    getchar();
                    getchar();
                }
            }
            mas = (city*)calloc(cityCount, sizeof(city));
            inputConsole(mas, cityCount);
            cityCount;
            break;
        }
        // Ввод с файла
        if (inpt == 1) {
            cityCount = inputFileCount(mas);
            if (cityCount == -1) {
                continue;
            }
            mas = (city*)calloc(cityCount, sizeof(city));
            inputFile(mas);
            break;
        }
        if (inpt == 2) {
            free(mas);
            free(data->curSubsequence);
            free(data->minSubsequence);
            free(data);
            printf("\nВсего доброго, спасибо за использование программы!");
            return 0;
        }

        printf("\nПопробуйте ввести \n0 - Ввод данных с консоли \n1 - Ввод данных из файла\n2 - Выход\nВвод комманды: ");
    }

    //Работа с остальным функционалом программы
    while (inpt != 0) {


        while (1) {
            printf("\n\nМеню программы:\n0 - Выход\n1 - Найти путь коммивояжера из заданного города\n2 - Вывод данных о городах\n3 - Отсортировать массив");
            printf("\n4 - Бинарный поиск\n5 - Сохранение данных в файл\n\nВвод команды: ");
            scanf_s("%d", &inpt);
            if (inpt == 0) {
                free(mas);
                free(data->curSubsequence);
                free(data->minSubsequence);
                free(data);
                printf("\nВсего доброго, спасибо за использование программы!");
                return 0;
            }
            // Поиск пути комм-ора
            if (inpt == 1) {
                printf("\nВведите \n1 - ввод номерa города для поиска\n2 - ввод названия города для поиска\n");
                printf("\nВвод команды: ");
                scanf_s("%d", &inpt);
                if (inpt == 1) {
                    algorithmData* data = (algorithmData*)calloc(1, sizeof(algorithmData));
                    defaultData(data, cityCount);
                    inpt = -1;
                    int start;
                    printf("\nВведите номер города, с которго начинаем: ");
                    while (inpt < 0) {
                        inpt = scanf_s("%d", &start);
                        if (inpt < 0) {
                            printf("\nОшибка ввода, попробуйте снова: ");
                            if (start < 1 || start > cityCount) {
                                inpt = -1;
                                printf("\nВведенный номер не соответствует списку, попробуйте снова:");
                            }

                        }
                    }
                    shortestWay(mas, data, 0, start - 1, 0, cityCount);
                    printf("\n\nКратчайший путь: %f\n", data->minlength);
                    printf("\nПуть коммивояжёра:\n");
                    for (int j = 0; j < cityCount; j++) {
                        printf("%d)Город #%d ", j + 1, &data->minSubsequence[j] + 1);
                        printf("%s \n", &mas[data->minSubsequence[j]].cityName);
                    }
                }
                if (inpt == 2) {
                    defaultData(data, cityCount);
                    inpt = -1;
                    int start = -1;
                    char startC[16];
                    startC[0] = '\0';
                    printf("\nВведите название города, с которого будем начинать: ");
                    scanf_s("%s", startC, 10);
                    for (int j = 0; j < cityCount; j++) {
                        if (wordsEqual(mas[j].cityName, startC)) {
                            start = j;
                            break;
                        }
                    }
                    if (start >= 0) {
                        shortestWay(mas, data, 0, start, 0, cityCount);

                        printf("\n\nКратчайший путь: %f\n", data->minlength);
                        printf("\nПуть коммивояжёра:\n");
                        for (int j = 0; j < cityCount; j++) {
                            printf("%d)Город  %s\n", j + 1, &mas[data->minSubsequence[j]].cityName);
                        }

                    }
                    else {
                        printf("\nГорода с таким именем нет.");
                    }
                    inpt = 1;
                }
            }

            // Вывод данных
            if (inpt == 2) {
                printf("\nДанные о городах:\n");
                output(mas, cityCount);
            }

            // Сортировка массива
            if (inpt == 3) {
                printf("\nМассив сортируется...\n");
                sortByName(mas, cityCount);
                printf("\nГотово!Теперь массив отсортирован:\n");
                output(mas, cityCount);
                printf("\n");
            }

            // Бин. поиск
            if (inpt == 4) {
                printf("\nДля бинарного поиска массив будет отсортирован! Теперь он имеет вид:\n");
                sortByName(mas, cityCount);
                output(mas, cityCount);
                char startC[16];
                startC[0] = '\0';

                int search = -1;
                printf("\nВведите название города, который будем искать: ");
                scanf_s("%s", startC, 10);



                search = binSearch(mas, 0, cityCount - 1, startC) - 1;
                if (search >= 0) {
                    printf("Индекс города %s - %d", startC, search + 1);
                    break;
                }
                else {
                    printf("\nТакого города нет в списке.\n");
                }
                break;
            }

            // Сохранение в файл
            if (inpt == 5) {
                saveFile(mas, data, cityCount);
                break;
            }

            if (inpt < 0 || inpt > 5) {
                printf("\nНеизвестная команда, попробуйте ввести 0 - Ввод с консоли, 1 - Ввод данных с файла.\nВвод: ");
            }
        }
    }
}
