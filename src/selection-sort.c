#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

time_t t;

typedef struct Algoinfo{
    unsigned long long int comp;
    unsigned long long int attr;
}Algoinfo;
Algoinfo data;

void swap_elements(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(int* arr, int n)
{
    int lowest_value_index; 
    for(int i = 0; i < n; i++){
        lowest_value_index = i; 
        for(int j = i; j < n; j++){
            data.comp++; 
            if(arr[j] < arr[lowest_value_index]){
                data.attr++; 
                lowest_value_index = j;
            }
        }
        swap_elements(&arr[i], &arr[lowest_value_index]); 
    }
}

int main(int argc, char** argv)
{
    int  option  = atoi(argv[1]); 
    int  sizes[] = {2000, 4000, 8000, 16000, 32000, 64000, 128000};
    char* test_type; 
     
    FILE* resultf; 
    resultf = fopen("../result/result-selection-sort.txt", "a"); 
    for(int i = 0; i < 7; i++){
        int* arr = malloc(sizeof(int) * sizes[i]); 
        data.attr = 0; 
        data.comp = 0; 
         
        FILE* fp; 
        switch(option){
            case 1:
                fp = fopen("../test/cres128.txt","r");  
                test_type = "crescente"; 
                break;
            case 2:
                fp = fopen("../test/decres128.txt","r");  
                test_type = "decrescente"; 
                break;
            case 3:
                fp = fopen("../test/random128.txt","r");  
                test_type = "random";
                break; 
            default:
                break;
        } 
        for(int k = 0; k < sizes[i]; k++){
            fscanf(fp, "%d\n", &arr[k]);
        } 
        
        clock_t t;
        t = clock();
        selection_sort(arr, sizes[i]);  
        t = clock() - t;   
        
        free(arr);
        arr = NULL; 
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        fprintf(resultf, "Teste %s %d\n\
            Tempo: %f\n\
            Num. de Comparacoes: %llu\n\
            Num. de atribuicoes: %llu\n", test_type, sizes[i],
                                            time_taken, data.comp, data.attr); 

        fclose(fp);
        free(arr);
        arr = NULL; 
    } 
    fclose(resultf); 
    return 0;
}

