#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct makemake_try make_try;

typedef struct judgeRes res;

struct makemake_try{
    char onLeft[3][10];
    char onRight[3][10];
    char res[3][10];
};

struct judgeRes{
    bool res;
    char condition[20];
};

make_try init(){
    make_try t;
    for(int i = 0; i < 3; i++){
        scanf("%s   %s   %s", t.onLeft[i], t.onRight[i], t.res[i]);
    }
    return t;
}

res notCounterfeit(res r){
    r.res = false;
    return r;
}

res isCounterfeit(res r, char * condition){
    r.res = true;
    strcpy(r.condition, condition);
    return r;
}

res judgeCounterfeit(char c, make_try t){
    res r;
    int index;
    for(int i = 0; i < 3; i++){
        switch(t.res[i][0]){
        case 'e':
            if(strchr(t.onLeft[i], c) || strchr(t.onRight[i], c)){
                r = notCounterfeit(r);
                return r;
            }
            break;
        default:
            index = i;
            if(strchr(t.onLeft[i], c) == NULL && strchr(t.onRight[i], c) == NULL){
                r = notCounterfeit(r);
                return r;
            }
            break;
        }
    }
    switch(t.res[index][0]){
    case 'u':
        if(strchr(t.onLeft[index], c)){
            r = isCounterfeit(r, (char*)"heavy");
        }
        else{
            r = isCounterfeit(r, (char*)"light");
        }
        break;
    default:
        if(strchr(t.onLeft[index], c)){
            r = isCounterfeit(r, (char*)"light");
        }
        else{
            r = isCounterfeit(r, (char*)"heavy");
        }
        break;
    }
    return r;
}

void circle(){
    make_try t = init();
    char c;
    for(c = 'A'; c <= 'L'; c++){
        res r = judgeCounterfeit(c, t);
        if(r.res){
            printf("%c is the counterfeit coin and it is %s.\n", c, r.condition);
            break;
        }
    }
}

int main()
{
    int times;
    scanf("%d", &times);
    while(times){
        circle();
        times--;
    }
    return 0;
}
