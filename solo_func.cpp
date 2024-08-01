#include "solo.h"
void game_start(hero* any){
    cout<<"닉네임을 지정해주세요: ";
    getline(cin,any->name);
    cout<<"\n========== 게임을 시작 합니다 ============\n";
    cout<<"용사 이름 : "<<any->name<<endl;
    cout<<"시작 레벨 : "<<any->LV<<endl;
    cout<<"\n첫턴은 자동으로 지납니다."<<endl;
}
void run_exp(hero* any,int* turn){
    int j=0;
    double random_exp=0,turn_exp=0,event_exp=0.0,event_random=0.0;
    turn_exp=0;
    for(j=0;j<5; j++){ 
        random_exp = DoubleRand(-5,1);
        turn_exp+=random_exp;
    }
    event_random = DoubleRand(1,5);
    event_exp = event_random * turn_exp;
    any->exp += turn_exp*event_random;
    cout<<"==========================================\n";
    cout<<"(이벤트 포함 6번의 경험치득실 진행 후 얻은)"<<endl;
    cout<<*turn<<"번째 턴 경험치 : "<<event_exp*100<<endl;
    cout<<"현재 보유 경험치 : "<< any->exp*100<<'\n';
}
void Lv_UP(hero* any, double* up_exp,int(* flag)){
    if(any->LV >=100)
        flag[lv100] =1;
    cout<<"==========================================\n";
    cout<<"레벨 up\n";
    any->exp = any->exp - any->LV_exp_count[any->LV];
    cout<<"레벨 업 후 남은 경험치 "<<any->exp*100<<endl;
    ++any->LV;
    cout<<"레벨 업 = "<<any->LV<<endl;

    *up_exp=FloatRand(1.8,2.6);
    any->LV_exp_count[any->LV] = any->LV_exp_count[any->LV-1] * *up_exp;
    cout<<"==========================================\n";
}
void quest(hero* any,int(* flag),int* quest_count){
    *quest_count+=1;
    system("clear");
    sleep(1);
    int answer;
    int a=IntRand(1,99), b = IntRand(1,99);
    if(*quest_count == 1){
        cout<<"\n\n\t\t"<<any->name<<" : 어라...";
        sleep(2);
        cout<<"\n\t\t"<<any->name<<" : 여긴 어디지...?";
        sleep(2);
        cout<<"\n\n\t\t??? : 어이, 심심한데 잘됐네, 문제하나 줄게";
        sleep(1);
        cout<<"\n\t\t간단한 구구단인데 설마 못맞추겠어?";
        sleep(1);
        cout<<"\n\t\t아, 그래도 대가는 있어야 겠지? ";
        sleep(1);
        cout<<"\n\t\t맞추지 못한다면, 강제로 1레벨로 보내주마.";
        sleep(2);
        system("clear");
    }
    cout<<any->LV;
    cout<<"\n\n\t\t"<<a<<" * "<<b<<" = ";
    cin>>answer;
    cin.ignore();
    if(answer == a*b){
        // system("clear");
        cout<<"\n\t\t??? : 축하하네, 경험치가 오르겠군.\n";
        any->exp+=30;
        if(any->LV >=100) 
            flag[lv100] =1;
    }
    else{
        system("clear");
        cout<<"\n\t\t??? : 뭐야 이것도 못맞춰?";
        sleep(1);
        cout<<"\n\t\t시시하군..";
        flag[lv1]=1;
    }
}
void Lv_DOWN(hero* any, double* up_exp, int(* flag)){
    cout<<"==========================================\n";
    cout<<"레벨 down\n";
    --any->LV;
    if(any->LV==1 && any->LV_exp_count[2]>0)
        flag[lv1]=1;
    if(any->LV == 0)
        flag[lv0]=1;
    if(flag[lv0]==1 || flag[lv1] ==1)
        flag[lv1] =0;
    any->exp=any->LV_exp_count[any->LV]+any->exp;
    if(any->LV>0){
        cout<<"레벨 다운 후 남은 경험치 "<<any->exp*100<<'\n';
        cout<<"======================================\n";
    }
}
void next_turn(hero* any,int* turn,int(* flag)){
    char ch;
    cout<<"------------------------------------------\n";
    cout<< any->name<<" 용사님,  "<<*turn<<"번째 턴, 현재 레벨 : "
        << any->LV<<"LV, 현재 레벨 경험치 경험치 수치 : "
        << any->LV_exp_count[any->LV]*100<<", 남은 경험치 : "
        << any->LV_exp_count[any->LV]*100-any->exp*100<<endl;
    cout<<"------------------------------------------\n";
    cout<<"\n다음 턴을 진행하시겠습니까?\n";
    cout<<"진행하려면 y 종료하려면 n을 눌러주세요 : \n";
    cin>>ch;
    cin.ignore();
    if (ch == 'n')
        flag[quit] =1;
    cout<<("-----------------------------------------\n");
}

void end_credit(hero* any,int(* flag),int* turn){
    if(flag[lv0]==1)
        cout<<"knock down\n게임을 종료합니다.";
    else if(flag[lv1]==1){        cout<<"1레벨로 돌아왔습니다..\n";
                printf("\n\n\n=======================================\n");
                printf("|                                     | \n");
                printf("|                                     | \n");
                printf("|                                     | \n");
                printf("|             BAD ENDING              | \n");
                printf("|                                     | \n");
                printf("|                                     | \n");
                printf("|                                     | \n");
                printf("=======================================\n");}
    else if (flag[lv0] != 1 && flag[lv1] != 1 && flag[lv0] != 1 && flag[quit] != 1){
        cout<<"happy ending\n";
        cout<<"- "<<*turn<<"번째 턴 -"<<endl
        <<any->name<<"용사님, 현재 레벨 "<<any->LV<<"LV, 현재 레벨 경험치 경험치 수치 "
        <<any->LV_exp_count[any->LV]*100<<", 남은 경험치 "
        <<any->LV_exp_count[any->LV]*100-any->exp*100<<endl;
    }
    else if(flag[quit]==1)
        cout<<"게임을 종료합니다.\n";
}
