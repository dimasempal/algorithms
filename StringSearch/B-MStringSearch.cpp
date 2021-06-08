/*
Идея эвристики плохих символов проста. Символ текста, который не соответствует текущему символу шаблона, называется недопустимым символом. Всякий раз, когда символ не совпадает, мы сдвигаем шаблон таким образом, чтобы выровнять плохой символ с последним его появлением в шаблоне. Мы предварительно обрабатываем шаблон и сохраняем последнее вхождение каждого возможного символа в массив размером, равным размеру алфавита. Если символ отсутствует, это может привести к сдвигу на m (длина шаблона). 
*/

# include <limits.h>
# include <string.h>
# include <stdio.h>
# define NO_OF_CHARS 256
//Универсальная функция поиска максимума, пригодится
int max(int a, int b)
{
      return (a > b) ? a : b;
}
// Функция предварительной обработки для эвристики плохих символов Бойера Мура 
void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS])
{
        int i;
// Инициализируем все вхождения как -1 
        for (i = 0; i < NO_OF_CHARS; i++)
            badchar[i] = -1;

// Заполняем фактическое значение последнего появления символа 
        for (i = 0; i < size; i++)
            badchar[(int) str[i]] = i;
}    

// Сам поиск, на вход текст и паттерн
void search(char *txt, char *pat)
{
        int m = strlen(pat);
        int n = strlen(txt);

        int badchar[NO_OF_CHARS];
        badCharHeuristic(pat, m, badchar);
     
// s - сдвиг шаблона относительно текста 
        int s = 0;
	//пока текст не будет меньше длины паттерна
        while (s <= (n - m))
        {
            int j = m - 1;
//Уменьшаем длинну при успешном совпадении
            while (j >= 0 && pat[j] == txt[s + j])
                j--;

            if (j < 0)
            {
                cout << "\n Паттерн входит начиная с " << s << endl;
                s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
            }
            else
                s += max(1, j - badchar[txt[s + j]]);
        }
    }     

int main()
{
    char txt[] = "ABAAABCD";
    char pat[] = "ABC";
    search(txt, pat);
    return 0;
}