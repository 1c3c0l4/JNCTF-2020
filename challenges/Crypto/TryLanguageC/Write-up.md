```c
#include <stdio.h>

int main()
{
    int i = 0;
    int numberflag[20] ={567,383,799,775,975,855,383,871,1007,951,1023,991,775,839,1007,887,1023,831,951};
    
    for(i = 0; i<19; i++)
    {
        numberflag[i] = numberflag[i]^ 0x7f;
        numberflag[i] = numberflag[i]>> 3;
        printf("%d ",numberflag[i]);
    }
    printf("\n");
    char flags[20];
    for(i = 0; i<19; i++)
    {
        flags[i] = numberflag[i]; 
        printf("%c",flags[i]);
    }
}
```

flag:

```
I love cryptography
```

