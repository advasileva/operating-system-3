# Операционные системы ИДЗ 3

0. [**Задание**](#задание)
0. [**Отчёт**](#отчёт)
    + [*4-5 баллов*](#4-5-баллов)
    + [*6-7 баллов*](#6-7-баллов)
0. [**Как запустить**](#как-запустить)

## Задание

*Сетевые взаимодействия с применением транспортного протокола TCP.*

*Вариант 20. Задача о магазине – 2 (забывчивые покупатели). В магазине работают два отдела, каждый отдел обладает уникальным ассортиментом. В каждом отделе работает один продавец. В магазин ходят исключительно забывчивые покупатели, поэтому каждый покупатель носит с собой список товаров, которые желает купить. Покупатель приобретает товары точно в том порядке, в каком они записаны в его списке. При этом товары в списке расположены в случайном порядке, что заставляет покупателя переходить от отдела к отделу, если это требуется для совершения покупок. Продавец может обслужить только одного покупателя за раз. Покупатель, вставший в очередь, засыпает пока не дойдет до продавца. Продавец засыпает, если в его отделе нет покупателей, и просыпается, если появится хотя бы один.*

*Создать приложение, моделирующее работу магазина в течение рабочего дня. Каждого продавца и покупателя представить отдельным процессом*

*Каждый продавецц — клиент. Покупатели изначально порождаются отдельным клиентом. Сервер обеспечивает взаимодействие покупателей и клиентов.*

## Отчёт

**Исполнитель: Васильева Алёна Дмитриевна БПИ218**

**Делала на оценку 6 баллов**

### 4 балла 
### Именнованные POSIX семафоры

*Разработать консольное приложение, в котором единый родительский процесс запускает требуемое число дочерних процессов.*

1. *В отчете приведены фамилия, имя, отчество исполнителя, группа.*

    Продублирую: Васильева Алёна Дмитриевна БПИ218

2. *Приведено условие задачи.*

    [Условие](#задание)

3. *Представить сценарий решаемой задачи поясняющий, каким образом исходные сущности и их поведение отображаются в процессы и их взаимодействие.*

    Задача описана достаточно подробно. У нас есть 5 сущностей -- продавец, покупатель, товар, ассортимент, список.
    
    Продавец и покупатель будут представлены процессами (два процесса для двух продавцов и `n` процессов для покупателей в зависимости от теста). Товар будет представлен числовым идентификатором типа int. Ассортимент поделен так, что в первом отделе товары с нечётными идентификаторами, во втором -- с чётными. Списки покупателей будут представлены массивами из идентификаторов (товаров). 

    Процессы продавцов и покупателей будут взаимодействовать между собой через разделяемую память посредством семафоров. Каждый продавец будет иметь ассортимент и каждый покупатель будет иметь список.

    Формат входных данных в файле, передаваемом первым аргументом командной строки: в первой строке записано число `n` -- количество покупателей. Далее описаны `n` покупателей в формате: в первой строке число `k` -- количество товаров в списке этого покупателя, в следующей строке `k` чисел -- идентификаторы товаров.

    В коде есть комментарии :)

4. *Множество процессов взаимодействуют с использованием именованных POSIX семафоров. Обмен данными ведется через разделяемую память в стандарте POSIX.*

    Разработанная программа находится в файле `4-points/main.c`

5. *Реализовать завершение программы в соответствии с условием задачи, а также предусмотреть корректное завершение по прерыванию с клавиатуры по соответствующему сигналу.*

    По умолчанию программа завершается после завершения работы покупателей. Также можно прервать программу, например, с помощью `Ctrl+C`.

6. *В программе предусмотреть удаление семафоров и разделяемой памяти по ее завершению любым из способов.*

    Завершенение работы реализовано так:
    ```c
    shm_unlink(memn);

    sem_close(sem_first);
    sem_close(sem_second);
    ```

7. *Результаты работы программы должны быть отражены в отчете.*

    Пример работы:
    ```bash
    Program for 4 points
    Test 1
    Seller 1 PID: 83142
    Seller 2 PID: 83143
    Buyer PID: 83144
    Buying stock 2 from 2
    Buying stock 3 from 1
    Selling stock 2 by 2
    Selling stock 3 by 1
    Buying stock 5 from 1
    Selling stock 5 by 1
    Buying stock 6 from 2
    Selling stock 6 by 2
    Seller 1 finished
    Seller 2 finished

    Test 2
    Seller 1 PID: 83157
    Seller 2 PID: 83158
    Buyer PID: 83159
    Buying stock 4 from 2
    Buyer PID: 83160
    Selling stock 4 by 2
    Buying stock 1 from 1
    Buying stock 2 from 2
    Selling stock 2 by 2
    Selling stock 1 by 1
    Buying stock 3 from 1
    Selling stock 3 by 1
    Buying stock 5 from 1
    Selling stock 5 by 1
    Seller 1 finished
    Seller 2 finished

    Test 3
    Seller 1 PID: 83167
    Seller 2 PID: 83168
    Buyer PID: 83169
    Buying stock 3 from 1
    Buyer PID: 83170
    Buying stock 4 from 2
    Buyer PID: 83171
    Selling stock 3 by 1
    Selling stock 4 by 2
    Buying stock 1 from 1
    Buying stock 2 from 2
    Selling stock 2 by 2
    Selling stock 1 by 1
    Buying stock 3 from 1
    Buying stock 6 from 2
    Selling stock 6 by 2
    Selling stock 3 by 1
    Buying stock 5 from 1
    Selling stock 5 by 1
    Seller 1 finished
    Seller 2 finished


    Programs finished
    ```

### 5 баллов
### Неименнованные POSIX семафоры

*В дополнение к программе на предыдущую оценку необходимо разработать программу, в которой для взаимодействия процессов используется один из двух вариантов, описанных выше, но не реализованных на предшествующую оценку.*

1. *Множество процессов взаимодействуют с использованием неименованных POSIX семафоров расположенных в разделяемой памяти. Обмен данными также ведется через разделяемую память в стандарте POSIX.*

    Разработанная программа находится в файле `5-points/main.c`

2. *Реализовать завершение программы в соответствии с условием задачи, а также предусмотреть корректное завершение по прерыванию с клавиатуры по соответствующему сигналу.*

    Аналогично предыдущему пункту.

3. *В программе предусмотреть удаление семафоров и разделяемой памяти по ее завершению любым из способов.*

    Аналогично предыдущему пункту.

4. *Результаты работы программы должны быть отражены в отчете.*

    Пример работы:
    ```bash
    Program for 5 points
    Test 1
    Seller 1 PID: 84069
    Seller 2 PID: 84070
    Buyer PID: 84071
    Buying stock 2 from 2
    Selling stock 2 by 2
    Buying stock 3 from 1
    Selling stock 3 by 1
    Buying stock 5 from 1
    Buying stock 6 from 2
    Selling stock 5 by 1
    Selling stock 6 by 2
    Seller 1 finished
    Seller 2 finished

    Test 2
    Seller 1 PID: 84081
    Seller 2 PID: 84082
    Buyer PID: 84083
    Buying stock 4 from 2
    Buyer PID: 84084
    Selling stock 4 by 2
    Buying stock 1 from 1
    Buying stock 2 from 2
    Selling stock 1 by 1
    Selling stock 2 by 2
    Buying stock 3 from 1
    Selling stock 3 by 1
    Buying stock 5 from 1
    Selling stock 5 by 1
    Seller 2 finished
    Seller 1 finished

    Test 3
    Seller 1 PID: 84097
    Seller 2 PID: 84098
    Buyer PID: 84099
    Buying stock 3 from 1
    Buyer PID: 84100
    Buying stock 4 from 2
    Buyer PID: 84101
    Selling stock 3 by 1
    Selling stock 4 by 2
    Buying stock 1 from 1
    Buying stock 2 from 2
    Selling stock 1 by 1
    Selling stock 2 by 2
    Buying stock 3 from 1
    Buying stock 6 from 2
    Selling stock 6 by 2
    Selling stock 3 by 1
    Buying stock 5 from 1
    Selling stock 5 by 1
    Seller 2 finished
    Seller 1 finished


    Programs finished
    ```

### 6 баллов 
### UNIX SYSTEM V

*В дополнение к программе на предыдущую оценку необходимо разработать программу, в которой для взаимодействия процессов используется один из двух вариантов, описанных выше, но не реализованных на предшествующую оценку.*

1. *Множество процессов взаимодействуют с использованием семафоров в стандарте UNIX SYSTEM V. Обмен данными ведется через разделяемую память в стандарте UNIX SYSTEM V.*

    Разработанная программа находится в файле `6-points/main.c`

2. *Реализовать завершение программы в соответствии с условием задачи, а также предусмотреть корректное завершение по прерыванию с клавиатуры по соответствующему сигналу.*

    Аналогично предыдущему пункту.

3. *В программе предусмотреть удаление семафоров и разделяемой памяти по ее завершению любым из способов.*

    Аналогично предыдущему пункту.

4. *Результаты работы программы должны быть отражены в отчете.*

    Пример работы:
    ```bash
    Program for 6 points
    Test 1
    Seller 1 PID: 84428
    Seller 2 PID: 84429
    Buyer PID: 84430
    Buying stock 2 from 2
    Selling stock 2 by 2
    Buying stock 3 from 1
    Selling stock 3 by 1
    Buying stock 5 from 1
    Buying stock 6 from 2
    Selling stock 5 by 1
    Selling stock 6 by 2
    Seller 1 finished
    Seller 2 finished

    Test 2
    Seller 1 PID: 84450
    Seller 2 PID: 84451
    Buyer PID: 84452
    Buying stock 4 from 2
    Buyer PID: 84453
    Selling stock 4 by 2
    Buying stock 1 from 1
    Buying stock 2 from 2
    Selling stock 2 by 2
    Selling stock 1 by 1
    Buying stock 3 from 1
    Selling stock 3 by 1
    Buying stock 5 from 1
    Selling stock 5 by 1
    Seller 2 finished
    Seller 1 finished

    Test 3
    Seller 1 PID: 84460
    Seller 2 PID: 84461
    Buyer PID: 84462
    Buying stock 3 from 1
    Buyer PID: 84463
    Buying stock 4 from 2
    Buyer PID: 84464
    Selling stock 3 by 1
    Selling stock 4 by 2
    Buying stock 6 from 2
    Buying stock 1 from 1
    Selling stock 6 by 2
    Selling stock 1 by 1
    Buying stock 2 from 2
    Selling stock 2 by 2
    Buying stock 3 from 1
    Selling stock 3 by 1
    Buying stock 5 from 1
    Selling stock 5 by 1
    Seller 2 finished
    Seller 1 finished


    Programs finished
    ```

## Как запустить

На тестовом наборе:

```bash
make run
```

Перекомпилировать:

```bash
make compile
```
