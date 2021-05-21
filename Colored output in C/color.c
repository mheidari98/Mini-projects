/***************************************************************************//**

  @file         color.c

  @author       mahdi heidari

  @date         I don't remember

  @brief        Colored output in C with ANSI colour codes. 

  @compile      gcc color.c -o color

*******************************************************************************/

#include<stdio.h>  // fprintf() - printf() - stderr - getchar() - perror()

#define clear() printf("\033[H\033[J") 

void settextFormat(int General_Formatting)
{
switch (General_Formatting)
    {
    case 0:   // Reset all attributes
        printf("\033[0;0m");
        break; 
    case 1:   // Bright (Bold on)
        printf("\033[0;1m");
        break;
    case 2:   // Dim
        printf("\033[0;2m");
        break;
    case 4:   // Underscore (on monochrome display adapter only) 
        printf("\033[0;4m");
        break;
    case 5:   // Blink on
        printf("\033[0;5m");
        break;
    case 7:   // Reverse video on 
        printf("\033[0;7m");
        break;
    case 8:   // Hidden  (Concealed on )
        printf("\033[0;8m");
        break;
    default:
        break;
    }
}
void setBGColor( int backGround_color , int bold)
{
    switch (backGround_color)
    {
    case 0:   // Black
        (bold)?(printf("\033[0;40m")):(printf("\033[1;40m"));
        break; 
    case 1:   // Red
        (bold)?(printf("\033[0;41m")):(printf("\033[1;41m"));
        break;
    case 2:   // Green
        (bold)?(printf("\033[0;42m")):(printf("\033[1;42m"));
        break;
    case 3:   // Yellow
        (bold)?(printf("\033[0;43m")):(printf("\033[1;43m"));
        break;
    case 4:   // Blue
        (bold)?(printf("\033[0;44m")):(printf("\033[1;44m"));
        break;
    case 5:   // Magenta  (purple)
        (bold)?(printf("\033[0;45m")):(printf("\033[1;45m"));
        break;
    case 6:  // Cyan
        (bold)?(printf("\033[0;46m")):(printf("\033[1;46m"));
        break;
    case 7:   // White
        (bold)?(printf("\033[0;47m")):(printf("\033[1;47m"));
        break;
    case 8:   // Reset
        printf("\033[0m");
        break;
    default:
        break;
    }
}

void setTextColor(int text_color , int bold)
{
    switch (text_color)
    {
    case 0:   // Black
        (bold)?(printf("\033[0;30m")):(printf("\033[1;30m"));
        break; 
    case 1:   // Red
        (bold)?(printf("\033[0;31m")):(printf("\033[1;31m"));
        break;
    case 2:   // Green
        (bold)?(printf("\033[0;32m")):(printf("\033[1;32m"));
        break;
    case 3:   // Yellow
        (bold)?(printf("\033[0;33m")):(printf("\033[1;33m"));
        break;
    case 4:   // Blue
        (bold)?(printf("\033[0;34m")):(printf("\033[1;34m"));
        break;
    case 5:   // Magenta  (purple)
        (bold)?(printf("\033[0;35m")):(printf("\033[1;35m"));
        break;
    case 6:  // Cyan
        (bold)?(printf("\033[0;36m")):(printf("\033[1;36m"));
        break;
    case 7:   // White
        (bold)?(printf("\033[0;37m")):(printf("\033[1;37m"));
        break;
    case 8:   // Reset
        printf("\033[0m");
        break;
    default:
        break;
    }
}


int main()
{
    setTextColor(2,0);
    printf("salam");
    setBGColor(4,0);
    printf("salam");
    setTextColor(5,0);
    printf("salam");
    setBGColor(5,1);
    printf("salam");
    setBGColor(6,0);
    printf("salam");
    setTextColor(5,0);
    printf("salam");
    settextFormat(2);
    printf("salam");
    settextFormat(2);
    printf("salam");
}