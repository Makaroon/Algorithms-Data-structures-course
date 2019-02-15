#include "ReadWriter.h"
//iostream, fstream, Student_and_Ski.h включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных методов для решения задачи.
//Рекомендуется использовать имеющиеся классы Student и Ski для решения задачи.
void algorithm(Ski* skies, Student* studs, int l, int r)
{
    int i = l, j = r;
    int i1 = l, j1 = r;
    Ski pivot = skies[(l + r) / 2];
    int curPos=0;
    while (i <= j && i1 <= j1)
    {
        while (compare(studs[j], pivot) >= 0)
        {
            if (compare(studs[j], pivot) == 0)
                curPos = j;
            else j--;
        }
        while (compare(studs[i], pivot) < 0)
            i++;

        while (compare(studs[curPos], skies[j1]) >= 0)
            j1--;

        while (compare(studs[curPos], skies[i1]) < 0)
            i1++;

        if (i <= j)
        {
            Student s = studs[i];
            studs[i] = studs[j];
            studs[j] = s;
            j--;
            i++;
        }

        if (i1 <= j1)
        {
            Ski s1 = skies[i1];
            skies[i1] = skies[j1];
            skies[j1] = s1;
            j1--;
            i1++;
        }
    }

    if (l < j )
        algorithm(skies, studs, l, j);
    if (i < r)
        algorithm(skies, studs, i, r);

}

//Задача - реализовать этот метод.
//Ответ должен быть упорядочен по возрастанию номеров студентов(!), то есть их id.
//Ответы должны быть в этих же массивах.
void findPairs(Student* students, Ski* skis, int n)
{
    algorithm(skis, students, 0, n - 1);
}

int main()
{
    ReadWriter rw;

    Student* students = nullptr;
    Ski* skis = nullptr;
    int n;

    //Read n from file
    n = rw.readInt();

    //Create arrays
    students = new Student[n];
    skis = new Ski[n];

    //read Students and Skis from file
    rw.readStudents(students, n);
    rw.readSkis(skis, n);

    //Find pairs
    findPairs(students, skis, n);

    //Write answer to file
    rw.writeStudentsAndSkis(students, skis, n);

    delete[] students;
    delete[] skis;
    return 0;
}
