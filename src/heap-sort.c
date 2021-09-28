#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct Algoinfo{
    unsigned long long int comp;
    unsigned long long int attr;
}Algoinfo;
Algoinfo data;

void swap_elements(uint64_t * a, uint64_t* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void build(uint64_t *array, uint64_t heap_size)
{
    for(uint64_t i = heap_size; i > 1 && array[i] > array[i / 2]; i /= 2)
        swap_elements(array + i, array + i/2); 
}
int get_largest_child(uint64_t *array, uint64_t i, uint64_t heap_size)
{
    uint64_t child;
    if(2 * i == heap_size || array[2 * i] > array[2 * i + 1])
        child = 2 * i;
    else 
        child = 2 * i + 1;
    
    return child;
}
void rebuild(uint64_t *array, uint64_t heap_size)
{
    uint64_t i = 1;
    while(i <= (heap_size/2)){
        int child = get_largest_child(array, i, heap_size);
        if(array[i] < array[child]){
            swap_elements(array + i, array + child);
            i = child;
        }
        else{
            i = heap_size;
        }
    }
}
void heap_sort(uint64_t *array, uint64_t n) 
{
    uint64_t *tmp_array = malloc((n + 1) * sizeof(uint64_t));
    
    for(uint64_t i = 0; i < n; i++){
        tmp_array[i+1] = array[i];
        data.attr++;
    }

    for(uint64_t heap_size = 2; heap_size <= n; heap_size++)
        build(tmp_array, heap_size);
    
    uint64_t heap_size = n;
    while(heap_size > 1){
        swap_elements(tmp_array + 1, tmp_array + heap_size--);
        rebuild(tmp_array, heap_size);
    }

    for(uint64_t i = 0; i < n; i++)
        array[i] = tmp_array[i + 1];
    
    free(tmp_array);
}

int main(int argc, char** argv)
{
    int  option  = atoi(argv[1]); 
    int  sizes[] = {2000, 4000, 8000, 16000, 32000, 64000, 128000};
    char* test_type; 
     
    FILE* resultf; 
    resultf = fopen("../result/result-heap-sort.txt", "a"); 
    for(int i = 0; i < 7; i++){
        uint64_t* arr = malloc(sizeof(uint64_t) * sizes[i]); 
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
            fscanf(fp, "%lu\n", &arr[k]);
        } 
        
        clock_t t;
        t = clock();
        heap_sort(arr, sizes[i]);  
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
        
    } 
    fclose(resultf);    
    
    return 0;
}

