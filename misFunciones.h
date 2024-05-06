int generarNumAleatorio(int a, int b);

int generarNumAleatorio(int a, int b)
{
    return(rand()%((b-a)+1)+a);
}