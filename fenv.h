#include <iostream>
#include <fenv.h>
#include <locale>

#pragma STDC FENV_ACCESS ON
//информирует компилятор о том, что программа получит доступ или изменит среду с плавающей запятой

// интервальное представление числа 
typedef struct test {
    // typedef создает ссылку на неименованный тип struct.
    double lb;
    double ub;
} 
possibly;

//сложение интервалов
//нормальный результат равен нулю
//сумма помещается в выходной аргумент
int complex(const possibly* a, const possibly* b,
    possibly* result) 
{
    //как говорилось выше, fenv_t - представляет среду с плавающей точкой.
    fenv_t point;

    //первым делом сохраняем текущую среду ,за это отвечает функция fegetenv
    if (fegetenv(&point) != 0) {
        perror("FEGETENV");
        return (-1);
    }

    //мы уже разложили числа на верхние и нижние границы
    //нижние границы скалдываем с округлением вниз - чтобы избежать неточности.
    //за это отвечаем FE_DOWNWARD
    if (fesetround(FE_DOWNWARD) != 0) {
        perror("FESETROUND");
        return (-1);
    }
    result->lb = a->lb + b->lb;

    //верхние границы складываем с окргулением вверх
    //за это отвечаем FE_UPWARD 
    if (fesetround(FE_UPWARD) != 0) {
        perror("FESETROUND");
        return (-1);
    }
    result->ub = a->ub + b->ub;

    //затем восстанавливаем текушую среду 
    //за это отвечает функция fesetenv
    if (fesetenv(&point) != 0) {
        perror("FESETENV");
        return (-1);
    }

    return 0;
}

//расписываем минус
int minus(const possibly* a, possibly* result) {
    result->lb = -(a->ub);
    result->ub = -(a->lb);

    return 0;
}


int main() {
    setlocale(0, "");
    system("title library fenv.h");
    //устанавливаем значения pi
    possibly pi = { 3.141592, 3.141593 };
    //и значения e
    possibly e = { 2.718281, 2.718282 };
    possibly res;
    possibly tmp;

    //выводим значения
    printf("Нижние границы числа pi: (%f)\n", pi.lb);
    printf("Верхние границы числа pi: (%f)\n", pi.ub);
    std::cout << std::endl;
    printf("Нижние границы числа e: (%f)\n", e.lb);
    printf("Верхние границы числа e: (%f)\n", e.ub);
    std::cout << std::endl;

   //вычисляем сумму
    complex(&pi, &e, &res);
    printf("Сумма нижних границ pi и e: (%f)\n", res.lb);
    printf("Сумма верхних границ pi и e: (%f)\n", res.ub);
    std::cout << std::endl;
    /* Вычислим разность pi и e */
    minus(&e, &tmp);
    complex(&pi, &tmp, &res);
    printf("Разность нижних границ pi и e: (%f)\n", res.lb);
    printf("Разность верхних границ pi и e: (%f)\n", res.ub);

    std::cin.get();
    return 0;
}
