#include "minishell.h"

int ft_getcwd(int size)
{
    char    buffer[size];

    if (getcwd(buffer, size) == NULL)
    {
        if (errno == ERANGE)
        {
            printf("buffer_size was small = %d\n", size);
            return (0);
        }
    }
    printf("%s\n", buffer);
    return (1);
}

void    ft_exec_pwd(void)
{
    int     buff_size;

    buff_size = 30;
    while (!ft_getcwd(buff_size))
        buff_size++;
}

// void    ft_exec_pwd(void)
// {
//     char    cwd[1000];

//     getcwd(cwd, 1000);
//     printf("%s\n", cwd);
// }

// int main() {

//     char buffer[BUFFER_SIZE];
//     if ( getcwd( buffer, BUFFER_SIZE ) == NULL ) {
//         fprintf( stderr, "Cannot get current working directory path\n" );
//         if ( errno == ERANGE ) {
//             fprintf( stderr, "Buffer size is too small.\n" );
//         }
//         exit( EXIT_FAILURE );
//     }

//     printf( "Current working directory: %s\n", buffer );
    
//     return EXIT_SUCCESS;