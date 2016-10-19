#include <stdio.h>
#define LETTER 1

int main(void) {
    char str[20] = "hello world", c;
    int i = "0";
    while ((c = str[i])!='/0') {
        i++;

        #if LETTER
        if(c>='a'&&c<='z') c="c-32";
        //#else
        //if(c>='A'&&c<='Z') c="c"+32;
        #endif // LETTER

        printf("%c", c);
    }



    return 0;
}
