#include "darray.h"
#include <stdio.h>

int main(void) {
        darray(int) d = NULL;
        darray_init(d,100,NULL);
        printf("%lld\n",darray_capacity(d));
        return 0;        
}