#include "solo.h"
#include "solo_func.cpp"
int main(){           //main 시작
    srand(time(NULL));
    hero any={.name="",.LV=11,.exp=0,{0,300}};
    int flag[4]={0};
    int turn=1;
    int quest_count=0;
    double up_exp=0;
    game_start(&any);     // 게임 시작 초기 화면
    sleep(2);
    for(int i = 2 ; i<100 ; i++){
        any.LV_exp_count[i]+=any.LV_exp_count[i-1]*DoubleRand(1,5);
        cout<<any.LV_exp_count[i]<<endl;
    }
    do{                   // do-while문 시작 (게임의 모든 흐름)
        turn++;
        // system("clear");  
        cout<<"\n\n";
        run_exp(&any,&turn); 
    while(any.exp<0){//레벨 등감 판단 구간
        Lv_DOWN(&any,&up_exp,flag);
        cout<<any.LV<<"레벨\n";
        if(flag[lv1]==1 || flag[lv0]==1 ) break;
    }
    while(any.LV_exp_count[any.LV]<any.exp){
        Lv_UP(&any,&up_exp,flag);
        if(flag[lv100] == 1)
            break;
        int quest_rand=IntRand(0,10);
        if(quest_rand<3)
            quest(&any,flag,&quest_count);    
        if(flag[lv1] == 1 || flag[lv100] == 1) break; 
    }
    if(flag[lv0] == 1 || flag[lv100] == 1)
        break;
        next_turn(&any,&turn,flag); //다음 턴 진행 여부

    } while(any.LV<100 && flag[quit] != 1 && flag[lv1] != 1 && flag[lv0] != 1);   //do-while문 종료
    end_credit(&any,flag,&turn);

    return 0;
}                      //main 끝
