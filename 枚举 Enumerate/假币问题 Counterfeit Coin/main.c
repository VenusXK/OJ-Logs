#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct makemake_try make_try;
typedef struct judgeRes res;

// 定义每次尝试的结构体
struct makemake_try{
    char onLeft[3][10];
    char onRight[3][10];
    char res[3][10];
};

// 定义判断的结果 包括布尔类型用来判断是否为假币、字符串用来记录重量信息
struct judgeRes{
    bool res;
    char condition[20];
};

// 初始化输入结构体
make_try init(){
    make_try t;
    for(int i = 0; i < 3; i++){
        scanf("%s   %s   %s", t.onLeft[i], t.onRight[i], t.res[i]);
    }
    return t;
}

// 不是假币时执行该函数
res notCounterfeit(res r){
    r.res = false;
    return r;
}

// 是假币时执行该函数
res isCounterfeit(res r, char * condition){
    r.res = true;
    strcpy(r.condition, condition);
    return r;
}

// 判断是否为假币，并判断假币的重量情况
res judgeCounterfeit(char c, make_try t){
    res r;
    int index;// 用来记录up或down那一行的索引
    for(int i = 0; i < 3; i++){
        switch(t.res[i][0]){
        // 若为平衡
        case 'e':
            // 若字符在左右字符串中，则返回不是假币
            if(strchr(t.onLeft[i], c) || strchr(t.onRight[i], c)){
                r = notCounterfeit(r);
                return r;
            }
            break;
        // 不平衡
        default:
            // 记录up或down那一行的索引
            index = i;
            // 若字符不在左右字符串中，则返回不是假币
            if(strchr(t.onLeft[i], c) == NULL && strchr(t.onRight[i], c) == NULL){
                r = notCounterfeit(r);
                return r;
            }
            break;
        }
    }
    // 判断右端是重还是轻
    switch(t.res[index][0]){
    // 若是轻
    case 'u':
        //若有问题的字符在左边 
        if(strchr(t.onLeft[index], c)){
            r = isCounterfeit(r, (char*)"heavy");
        }
        //若有问题的字符在右边 
        else{
            r = isCounterfeit(r, (char*)"light");
        }
        break;
    // 若是重
    default:
        //若有问题的字符在左边 
        if(strchr(t.onLeft[index], c)){
            r = isCounterfeit(r, (char*)"light");
        }
        //若有问题的字符在右边 
        else{
            r = isCounterfeit(r, (char*)"heavy");
        }
        break;
    }
    // 返回结果结构体
    return r;
}

// 每次执行的代码
void circle(){
    // 初始化输入结构体
    make_try t = init();
    char c;
    // 枚举每个字母
    for(c = 'A'; c <= 'L'; c++){
        // 判断是否为假币，并判断假币的重量情况
        res r = judgeCounterfeit(c, t);
        if(r.res){
            // 输出
            printf("%c is the counterfeit coin and it is %s.\n", c, r.condition);
            break;
        }
    }
}

int main()
{
    int times;
    scanf("%d", &times);
    // 执行输入的次数次程序
    while(times){
        circle();
        times--;
    }
    return 0;
}
