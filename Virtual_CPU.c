#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

long int characters_counter(FILE *file_pointer, int string_number); // Возвращает количетво символов от начала файла до указанной строки

int main(void)
{
    int i_comand = 0;                                          // > Счётчики символов в комаде и аргументах
    int i_argument_1 = 0;
    int i_argument_2 = 0;                                      // <
    int size_comand = 1;                                       // > Размеры строк, в которые сохраняются команда и два аргумента
    int size_argument_1 = 1;
    int size_argument_2 = 1;                                   // <
    char comand[size_comand];
    char argument_1[size_argument_1];
    char argument_2[size_argument_2];
    FILE *pf;

    int memory[256] = {0};
    int reg_a = 0, reg_b = 0, reg_c = 0, reg_d = 0,
        carry_flag = FALSE, zero_flag = FALSE,
        *stack_pointer, *instruction_pointer;


    instruction_pointer = memory;
    stack_pointer = & memory[231];

    if((pf = fopen("assembler_code.txt", "r")) == NULL)        // Открытие файла с исходным кодом
    {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    while(feof(pf) == 0)
    {
        while((comand[i_comand] = getc(pf)) != ' ')                                           // > Расчленяем строку из исходного кода на команду, аргумент 1 и аргумент 2, 
        {                                                                                     //   и записываем их в отдельные строки
            if(comand[i_comand] == EOF)
                break;
            ++i_comand;
            ++size_comand;
        }
        comand[i_comand] = '\0';

        while((argument_1[i_argument_1] = getc(pf)) != ' ')
        {
                if(argument_1[i_argument_1] == EOF || argument_1[i_argument_1] == '\n')
                    break;
                ++i_argument_1;
                ++size_argument_1;
        }

        if(argument_1[i_argument_1] != '\n')
        {
            while((argument_2[i_argument_2] = getc(pf)) != ' ')
            {
                if(argument_2[i_argument_2] == EOF || argument_2[i_argument_2] == '\n')
                    break;
                ++i_argument_2;
                ++size_argument_2;
            }
            argument_2[i_argument_2] = '\0';
        }

        argument_1[i_argument_1] = '\0';
                                                                                              // <


        if(strcmp(comand, "MOV") == 0)                                                        // > Команда MOV
        {
            *instruction_pointer = 10;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)                                              // > Запись в регистр А
            {
                *instruction_pointer = 0;
                ++instruction_pointer;
                if(strcmp(argument_2, "B") == 0)
                {
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                    reg_a = reg_b;
                }
                else if(strcmp(argument_2, "C") == 0)
                {
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                    reg_a = reg_c;
                }
                else if(strcmp(argument_2, "D") == 0)
                {
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                    reg_a = reg_d;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    reg_a = memory[atoi(argument_2 + 1)];
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    reg_a = atoi(argument_2);                                             // <
                }
            }
            else if(strcmp(argument_1, "B") == 0)                                         // > Запись в регистр В
            {
                *instruction_pointer = 1;
                ++instruction_pointer;
                if(strcmp(argument_2, "A") == 0)
                {
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                    reg_b = reg_a;
                }
                else if(strcmp(argument_2, "C") == 0)
                {
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                    reg_b = reg_c;
                }
                else if(strcmp(argument_2, "D") == 0)
                {
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                    reg_b = reg_d;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    reg_b = memory[atoi(argument_2 + 1)];
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    reg_b = atoi(argument_2);                                             // <
                }
            }
            else if(strcmp(argument_1, "C") == 0)                                         // > Запись в регистр С
            {
                *instruction_pointer = 2;
                ++instruction_pointer;
                if(strcmp(argument_2, "A") == 0)
                {
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                    reg_c = reg_a;
                }
                else if(strcmp(argument_2, "B") == 0)
                {
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                    reg_c = reg_b;
                }
                else if(strcmp(argument_2, "D") == 0)
                {
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                    reg_c = reg_d;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    reg_c = memory[atoi(argument_2 + 1)];
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    reg_c = atoi(argument_2);                                             // <
                }
            }
            else if(strcmp(argument_1, "D") == 0)                                         // > Запись в регистр D
            {
                *instruction_pointer = 3;
                ++instruction_pointer;
                if(strcmp(argument_2, "A") == 0)
                {
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                    reg_d = reg_a;
                }
                else if(strcmp(argument_2, "B") == 0)
                {
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                    reg_d = reg_b;
                }
                else if(strcmp(argument_2, "C") == 0)
                {
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                    reg_d = reg_c;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    reg_d = memory[atoi(argument_2 + 1)];
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    reg_d = atoi(argument_2);                                             // <
                }
            }
            else if(argument_1[0] == '[')                                                 // > Запись по адресу
            {
                *instruction_pointer = atoi(argument_1 + 1);
                ++instruction_pointer;
                if(strcmp(argument_2, "A") == 0)
                {
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                    memory[atoi(argument_1 + 1)] = reg_a;
                }
                else if(strcmp(argument_2, "B") == 0)
                {
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                    memory[atoi(argument_1 + 1)] = reg_b;
                }
                else if(strcmp(argument_2, "C") == 0)
                {
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                    memory[atoi(argument_1 + 1)] = reg_c;
                }
                else if(strcmp(argument_2, "D") == 0)
                {
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                    memory[atoi(argument_1 + 1)] = reg_d;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    memory[atoi(argument_1 + 1)] = memory[atoi(argument_2 + 1)];
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    memory[atoi(argument_1 + 1)] = atoi(argument_2);                      // <
                }
            }
        }                                                                                     // < Комадна MOV

        if(strcmp(comand, "INC") == 0)                                                        // > Команда INC
        {
            *instruction_pointer = 12;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)
            {
                *instruction_pointer = 0;
                ++instruction_pointer;
                ++reg_a;
            }
            else if(strcmp(argument_1, "B") == 0)
            {
                *instruction_pointer = 1;
                ++instruction_pointer;
                ++reg_b;
            }
            else if(strcmp(argument_1, "C") == 0)
            {
                *instruction_pointer = 2;
                ++instruction_pointer;
                ++reg_c;
            }
            else if(strcmp(argument_1, "D") == 0)
            {
                *instruction_pointer = 3;
                ++instruction_pointer;
                ++reg_d;
            }
            printf("%c\n", argument_1[i_argument_1]);
        }                                                                                     // <

        if(strcmp(comand, "DEC") == 0)                                                        // > Команда DEC
        {
            *instruction_pointer = 14;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)
            {
                *instruction_pointer = 0;
                ++instruction_pointer;
                --reg_a;
            }
            else if(strcmp(argument_1, "B") == 0)
            {
                *instruction_pointer = 1;
                ++instruction_pointer;
                --reg_b;
            }
            else if(strcmp(argument_1, "C") == 0)
            {
                *instruction_pointer = 2;
                ++instruction_pointer;
                --reg_c;
            }
            else if(strcmp(argument_1, "D") == 0) 
            {
                *instruction_pointer = 3;
                ++instruction_pointer;
                --reg_d;
            }
        }                                                                                     // <

        if(strcmp(comand, "MUL") == 0)                                                        // > Команда MUL(умножение)
        {
            *instruction_pointer = 11;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)
                {
                    reg_a *= reg_a;
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                }
            else if(strcmp(argument_1, "B") == 0)
                {
                    reg_a *= reg_b;
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                }
            else if(strcmp(argument_1, "C") == 0)
                {
                    reg_a *= reg_c;
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                }
            else if(strcmp(argument_1, "D") == 0) 
                {
                    reg_a *= reg_d;
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                }
            else if(argument_1[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    reg_a *= memory[atoi(argument_2 + 1)];
                }
            else
                {
                    *instruction_pointer = atoi(argument_1);
                    ++instruction_pointer;
                    reg_a *= atoi(argument_1);                                             // <
                }                
        }                                                                                     // <

        if(strcmp(comand, "DIV") == 0)                                                        // > Команада DIV(деление)
        {
        	*instruction_pointer = 13;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)
                {
                    reg_a /= reg_a;
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                }
            else if(strcmp(argument_1, "B") == 0)
                {
                    reg_a /= reg_b;
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                }
            else if(strcmp(argument_1, "C") == 0)
                {
                    reg_a /= reg_c;
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                }
            else if(strcmp(argument_1, "D") == 0) 
                {
                    reg_a /= reg_d;
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                }
            else if(argument_1[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    reg_a /= memory[atoi(argument_2 + 1)];
                }
            else
                {
                    *instruction_pointer = atoi(argument_1);
                    ++instruction_pointer;
                    reg_a /= atoi(argument_1);                                             // <
                }
        }                                                                                     // <

        if(strcmp(comand, "CMP") == 0)                                                        // > Команда CMP
        {
            *instruction_pointer = 16;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)                                              // > Сравнение с регистром А
            {
                *instruction_pointer = 0;
                ++instruction_pointer;
                if(strcmp(argument_2, "B") == 0)
                {
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                    zero_flag = (reg_a == reg_b) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "C") == 0)
                {
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                    zero_flag = (reg_a == reg_c) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "D") == 0)
                {
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                    zero_flag = (reg_a == reg_d) ? TRUE : FALSE;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    zero_flag = (reg_a == memory[atoi(argument_2 + 1)]) ? TRUE : FALSE;
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    zero_flag = (reg_a == atoi(argument_2)) ? TRUE : FALSE;               // <
                }
            }
            else if(strcmp(argument_1, "B") == 0)                                         // > Сравнение с регистром B
            {
                *instruction_pointer = 1;
                ++instruction_pointer;
                if(strcmp(argument_2, "A") == 0)
                {
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                    zero_flag = (reg_b == reg_a) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "C") == 0)
                {
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                    zero_flag = (reg_b == reg_c) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "D") == 0)
                {
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                    zero_flag = (reg_b == reg_d) ? TRUE : FALSE;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    zero_flag = (reg_b == memory[atoi(argument_2 + 1)]) ? TRUE : FALSE;
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    zero_flag = (reg_b == atoi(argument_2)) ? TRUE : FALSE;               // <
                }
            }
            else if(strcmp(argument_1, "C") == 0)                                         // > Сравнение с регистром C
            {
                *instruction_pointer = 2;
                ++instruction_pointer;
                if(strcmp(argument_2, "A") == 0)
                {
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                    zero_flag = (reg_c == reg_a) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "B") == 0)
                {
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                    zero_flag = (reg_c == reg_b) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "D") == 0)
                {
                    *instruction_pointer = 3;
                    ++instruction_pointer;
                    zero_flag = (reg_c == reg_d) ? TRUE : FALSE;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    zero_flag = (reg_c == memory[atoi(argument_2 + 1)]) ? TRUE : FALSE;
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    zero_flag = (reg_c == atoi(argument_2)) ? TRUE : FALSE;               // <
                }
            }
            else if(strcmp(argument_1, "D") == 0)                                         // > Сравнение с регистром D
            {
                *instruction_pointer = 3;
                ++instruction_pointer;
                if(strcmp(argument_2, "A") == 0)
                {
                    *instruction_pointer = 0;
                    ++instruction_pointer;
                    zero_flag = (reg_d == reg_a) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "B") == 0)
                {
                    *instruction_pointer = 1;
                    ++instruction_pointer;
                    zero_flag = (reg_d == reg_b) ? TRUE : FALSE;
                }
                else if(strcmp(argument_2, "C") == 0)
                {
                    *instruction_pointer = 2;
                    ++instruction_pointer;
                    zero_flag = (reg_d == reg_c) ? TRUE : FALSE;
                }
                else if(argument_2[0] == '[')
                {
                    *instruction_pointer = atoi(argument_2 + 1);
                    ++instruction_pointer;
                    zero_flag = (reg_d == memory[atoi(argument_2 + 1)]) ? TRUE : FALSE;
                }
                else
                {
                    *instruction_pointer = atoi(argument_2);
                    ++instruction_pointer;
                    zero_flag = (reg_d == atoi(argument_2)) ? TRUE : FALSE;
                }
            }                                                                             // <
        }                                                                                     // < Команда CMP

        if(strcmp(comand, "JMP") == 0)                                                        // > Команда JMP
        {
            *instruction_pointer = 18;
            ++instruction_pointer;
            *instruction_pointer = atoi(argument_1);
            ++instruction_pointer;
            if(zero_flag != TRUE)
                fseek(pf, characters_counter(pf, atoi(argument_1)), SEEK_SET);
        }                                                                                     // <

        if(strcmp(comand, "ADD") == 0)                                                        // > Команда ADD(сложение)
        {
            *instruction_pointer = 15;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)                                              // > сложение с регистром A
            {
                *instruction_pointer = 0;
                ++instruction_pointer;
                    
                if(strcmp(argument_2, "A") == 0)
                    {
                        reg_a += reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        reg_a += reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_a += reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_a += reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        reg_a += memory[atoi(argument_2 + 1)];
                    }
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        reg_a += atoi(argument_2);
                    }                                                                     // <
            }
            else if(strcmp(argument_1, "B") == 0)                                         // > сложение с регистром B
            {
                *instruction_pointer = 1;
                ++instruction_pointer;

                if(strcmp(argument_2, "A") == 0)
                    {
                        reg_b += reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        reg_b += reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_b += reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_b += reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        reg_a += memory[atoi(argument_2 + 1)];
                    }
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        reg_a += atoi(argument_2);
                    }                                                                     // <
            }
            else if(strcmp(argument_1, "C") == 0)                                         // > сложение с регистром C
            {
                *instruction_pointer = 2;
                ++instruction_pointer;

                if(strcmp(argument_2, "A") == 0)
                    {
                        reg_c += reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }                    	
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_c += reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        reg_c += reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_c += reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                            reg_a += memory[atoi(argument_2 + 1)];
                    }
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        reg_a += atoi(argument_2);                                        
                    }                                                                     // <
            }
            else if(strcmp(argument_1, "D") == 0)                                         // > сложение с регистром D
            {
                if(strcmp(argument_2, "A") == 0)
                    {
                        reg_d += reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_d += reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        reg_d += reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_d += reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                            *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        reg_a /= memory[atoi(argument_2 + 1)];
                    } 
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        reg_a += atoi(argument_2);
                    }                                                                     // <
            }
            else if(argument_1[0] == '[')                                                 // > сложение по адресу
            {
                if(strcmp(argument_2, "A") == 0)
                    {
                        memory[atoi(argument_1 + 1)] += reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        memory[atoi(argument_1 + 1)] += reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        memory[atoi(argument_1 + 1)] += reg_c;
                        *instruction_pointer =2;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        memory[atoi(argument_1 + 1)] += reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        memory[atoi(argument_1 + 1)] += memory[atoi(argument_2 + 1)];
                    }
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        memory[atoi(argument_1 + 1)] += atoi(argument_2);
                    }                                         // <
            }
        }                                                                                 // <

        if(strcmp(comand, "SUB") == 0)                                                    // > Команда SUB(вычитание)
        {
            *instruction_pointer = 17;
            ++instruction_pointer;
            if(strcmp(argument_1, "A") == 0)                                      // > вычитание из регистра A
            {
                *instruction_pointer = 0;
                ++instruction_pointer;
                if(strcmp(argument_2, "B") == 0)
                    {
                        reg_a -= reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "A") == 0)
                   {
                        reg_a -= reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_a -= reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_a -= reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        reg_a -= memory[atoi(argument_2 + 1)];
                    } 
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        memory[atoi(argument_1 + 1)] -= atoi(argument_2);
                    }                                                                        // <
            }
            else if(strcmp(argument_1, "B") == 0)                                         // > вычитание из регистра B
            {
                *instruction_pointer = 1;
                ++instruction_pointer;

                if(strcmp(argument_2, "A") == 0)
                    {
                        reg_b -= reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        reg_b -= reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_b -= reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_b -= reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        reg_a -= memory[atoi(argument_2 + 1)];
                    } 
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        memory[atoi(argument_1 + 1)] -= atoi(argument_2);
                    }                                                                     // <
            }
            else if(strcmp(argument_1, "C") == 0)                                         // > вычитание из регистра C
            {
                if(strcmp(argument_2, "A") == 0)
                    {
                        reg_c -= reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_c -= reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        reg_c -= reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_c -= reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        reg_a -= memory[atoi(argument_2 + 1)];
                    } 
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        memory[atoi(argument_1 + 1)] -= atoi(argument_2);
                    }                                                                     // <
            }
            else if(strcmp(argument_1, "D") == 0)                                         // > вычитание из регистра D
            {
                if(strcmp(argument_2, "A") == 0)
                    {
                        reg_d -= reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "D") == 0)
                    {
                        reg_d -= reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "B") == 0)
                    {
                        reg_d -= reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                        reg_d -= reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }                
                else if(argument_2[0] == '[')
                        {
                            *instruction_pointer = atoi(argument_2 + 1);
                            ++instruction_pointer;
                            reg_a -= memory[atoi(argument_2 + 1)];
                        } 
                else
                        {
                            *instruction_pointer = atoi(argument_2);
                            ++instruction_pointer;
                            memory[atoi(argument_1 + 1)] -= atoi(argument_2);
                        }
            }
            else if(argument_1[0] == '[')                                                 // > вычитание из адреса
            {
            	*instruction_pointer = atoi(argument_1);
                ++instruction_pointer;

                if(strcmp(argument_2, "A") == 0)
                    {
                    	memory[atoi(argument_1 + 1)] -= reg_a;
                        *instruction_pointer = 0;
                        ++instruction_pointer;
                    }                    	
                else if(strcmp(argument_2, "B") == 0)
                    {
                    	memory[atoi(argument_1 + 1)] -= reg_b;
                        *instruction_pointer = 1;
                        ++instruction_pointer;
                    }
                else if(strcmp(argument_2, "C") == 0)
                    {
                    	memory[atoi(argument_1 + 1)] -= reg_c;
                        *instruction_pointer = 2;
                        ++instruction_pointer;
                    }                    	
                else if(strcmp(argument_2, "D") == 0)
                    {
                    	memory[atoi(argument_1 + 1)] -= reg_d;
                        *instruction_pointer = 3;
                        ++instruction_pointer;
                    }                    	
                else if(argument_2[0] == '[')
                    {
                        *instruction_pointer = atoi(argument_2 + 1);
                        ++instruction_pointer;
                        memory[atoi(argument_1)] -= memory[atoi(argument_2 + 1)];
                    }                
                else
                    {
                        *instruction_pointer = atoi(argument_2);
                        ++instruction_pointer;
                        memory[atoi(argument_1 + 1)] -= atoi(argument_2);
                    }
            }
        }                                                                                     // <

                                                                                              // > Консольный вывод

        for (int i = 0; i < 50; ++i)                                                      // Верхняя двойная черта
        {
            printf("%c", 205);
        }
        printf("\n");

        printf("  A    B    C    D    Z    C  \n");                                            // Наименование регистров и их значения
        printf("%3i  %3i  %3i  %3i  %3i  %3i\n", reg_a, reg_b, reg_c, reg_d, zero_flag, carry_flag);

        for (int i = 0; i < 50; ++i)                                                      // Одинарная черта, отделяющая регистры от остальной памяти
        {
            printf("%c", 196);
        }
        printf("\n");

        for (int i = 0; i < 256; ++i)                                                     // Значения ячеек памяти
        {
            printf("%3i", memory[i]);
            if(((i+1) % 16) == 0)
                printf("\n");
        }
        printf("\n");

        for (int i = 0; i < 50; ++i)                                                      // Нижняя двойная черта
        {
            printf("%c", 205);
        }
        printf("\n\n\n\n\n");
                                                                                              // <

        i_comand = 0;
        i_argument_1 = 0;
        i_argument_2 = 0;
        size_comand = 1;
        size_argument_1 = 1;
        size_argument_2 = 1;
    }

    if (fclose(pf) != 0)
        fprintf(stderr, "Error closing file.\n");

    return 0;
}

long int characters_counter(FILE* file_pointer, int string_number)
{
    char ch;
    long int ch_amount = 0;

    fseek(file_pointer, 0, SEEK_SET);
    for (int str_amount = 0; str_amount < (string_number - 1); ++str_amount)
    {
        while((ch = getc(file_pointer)) != '\n')
            ++ch_amount;
            ch_amount += 2;
    }

    return ch_amount;
}