#include "darray.h"
#include <stdio.h>

void fn_dtr(void *p) {
        if (p) {
                free(*(int**)p);
        }
}
int main(void) {
        darray(int) d = NULL;
        darray_init(d,100,NULL);
        assert(darray_size(d) == 0);
        for (int i = 0;i < 10;i++) {
                darray_push_back(d,i);
        }
        printf("%d\n",*darray_back(d));
        darray_pop_back(d);
        printf("%d\n",*darray_back(d));

        return 0;        
}