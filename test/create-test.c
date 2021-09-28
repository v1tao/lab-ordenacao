#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t t;

void fill_random()
{
    FILE* fp;
    fp = fopen("random128.txt", "w");
    srand((unsigned) time(&t));    
    for(int i = 0; i < 128000; i++){
        fprintf(fp, "%u\n", rand() % 128000 + 1);
    }
    fclose(fp);
}
void fill_cres()
{
    FILE* fp;
    fp = fopen("cres128.txt", "w");
    for(int i = 1; i < 128001; i++){
        fprintf(fp, "%u\n", i);
    }
    fclose(fp);
}
void fill_decres()
{
    FILE* fp;
    fp = fopen("decres128.txt", "w");
    for(int i = 128000; i > 0; i--){
        fprintf(fp, "%u\n", i);
    }
    fclose(fp);
}
int main(int argc, char** argv)
{
    fill_cres();
    fill_decres();
    fill_random();
    return 0;
}

