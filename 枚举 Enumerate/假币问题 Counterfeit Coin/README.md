## 枚举 Enumerate \ 假币问题 Counterfeit Coin
### 题目描述
赛利有12枚银币。其中有11枚真币和1枚假币。假币看起来和真币没有区别，但是重量不同。但赛利不知道假币比真币轻还是重。于是他向朋友借了一架天平。朋友希望赛利称三次就能找出假币并且确定假币是轻是重。例如:如果赛利用天平称两枚硬币，发现天平平衡，说明两枚都是真的。如果赛利用一枚真币与另一枚银币比较，发现它比真币轻或重，说明它是假币。经过精心安排每次的称量，赛利保证在称三次后确定假币。
### 输入
第一行有一个数字n，表示有n组测试用例。
对于每组测试用例：
输入有三行，每行表示一次称量的结果。赛利事先将银币标号为A-L。每次称量的结果用三个以空格隔开的字符串表示：天平左边放置的硬币 天平右边放置的硬币 平衡状态。其中平衡状态用 `up`, `down` 或 `even` 表示, 分别为右端高、右端低和平衡。天平左右的硬币数总是相等的。
### 输出
输出哪一个标号的银币是假币，并说明它比真币轻还是重(heavy or light)。
### 要求
<table>
<tr>
<td>输入</td>
<td>结果</td>
</tr>
<tr>
<td>1 <br> ABCD EFGH even <br> ABCI EFJK up<br> ABIJ EFGH even</td>
<td> K is the counterfeit coin and it is light.</td>
</tr>
</table>

### 实现结果
<div align=left>
<img decoding="async" src="./result.png" width="80%" >
</div>

### 实现代码
```c
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

```