#include <iostream>
using namespace std;
const int inf = 10000;
const int NUMS = 8;
typedef struct nodea {//创建位置节点，存放各个地点的位置信息
    string name;//全名
    string info;//简介
    string abbr;//缩写
} Place;
Place P[8];//共有八个地方
typedef struct g {//构建邻接矩阵
    int n = NUMS;//存放点的个数
    int E[NUMS][NUMS] = {//邻接矩阵（由于地图是固定的所以矩阵也直接规定了）
            {000, 200, inf, inf, inf, 250, inf, 500},
            {200, 000, 400, inf, 180, inf, inf, inf},
            {inf, 400, inf, 150, inf, inf, 380, 375},
            {inf, inf, 150, 000, inf, 350, inf, inf},
            {inf, 180, inf, inf, 000, 200, inf, inf},
            {250, inf, inf, 350, 200, 000, inf, inf},
            {inf, inf, 380, inf, inf, inf, 000, 300},
            {500, inf, 375, inf, inf, inf, 300, 000},
    };
} Graph;
void init() {//初始化各个地点，存放各个地点的信息
    P[0].name = "Teaching building 1";
    P[0].info = "Main teaching building. ";
    P[0].abbr = "T1";
    P[1].name = "Teaching 2";
    P[1].info = "Sub-important teaching building. ";
    P[1].abbr = "T2";
    P[2].name = "Canteen";
    P[2].info = "Various food is given. ";
    P[2].abbr = "CT";
    P[3].name = "Natatorium";
    P[3].info = "A big swimming pool is inclusive. ";
    P[3].abbr = "NT";
    P[4].name = "Playground";
    P[4].info = "Next sports meeting is comming. ";
    P[4].abbr = "PG";
    P[5].name = "Stadium";
    P[5].info = "Normal gym lesson site. ";
    P[5].abbr = "SD";
    P[6].name = "Dorm 1";
    P[6].info = "Boy's dorm. ";
    P[6].abbr = "D1";
    P[7].name = "Dorm 2";
    P[7].info = "Girl's dorm. ";
    P[7].abbr = "D2";
}
void welcome() {//开始界面，欢迎菜单
    cout << "**********************************" << endl;
    cout << "**                              **" << endl;
    cout << "**      Welcome to use our      **" << endl;
    cout << "**   school guidance program!   **" << endl;
    cout << "**                              **" << endl;
    cout << "**       Made by 18080128       **" << endl;
    cout << "**                              **" << endl;
    cout << "**********************************" << endl;
    system("pause");
}
void menu() {//主菜单，选择功能
    system("cls");
    cout << "**************************" << endl;
    cout << "**1-Know about campus.  **" << endl;
    cout << "**2-Find nearest path.  **" << endl;
    cout << "**3-Exit.               **" << endl;
    cout << "**************************" << endl;
    cout << "Please input your choice: " << endl;
}
void info_menu() {//进入信息查询功能时的菜单
    system("cls");
    cout << "***************************" << endl;
    cout << "**1-Teaching building 1# **" << endl;
    cout << "**2-Teaching building 2# **" << endl;
    cout << "**3-Canteen              **" << endl;
    cout << "**4-Natatorium           **" << endl;
    cout << "**5-Playground           **" << endl;
    cout << "**6-Stadium              **" << endl;
    cout << "**7-Dorm 1               **" << endl;
    cout << "**8-Dorm 2               **" << endl;
    cout << "**9-Back                 **" << endl;
    cout << "***************************" << endl;
    cout<<"Which information do you want to search?"<<endl;
}
void information() {//信息查询功能的主函数
    int choice;//用户选择
    while (true) {
        info_menu();//展示主菜单
        cin >> choice;
        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8://此时用户选择一个地点，便输出这个地点的全部信息，switch中不必做区分
                system("cls");
                cout << "Name: " << P[choice - 1].name << endl << "Description: " << P[choice - 1].info << endl
                     << "Abbrviation: " << P[choice - 1].abbr << endl;//直接输出
                system("pause");
                break;
            case 9:
                return;
            default:
                cout << "Please input your choice again." << endl;
                system("pause");
        }
    }
}
void Display_path(int A[][NUMS], int path[][NUMS], int n,int start,int end);//floyd算法的输出结果部分，由于先后顺序问题需要先声明后定义
void Floyd(Graph G,int a,int b) {//floyd算法主函数
    int A[NUMS][NUMS], path[NUMS][NUMS];//A表示距离，可通过邻接矩阵直接读取，path表示两点之间可否到达
    int i, j, k;
    for (i = 0; i < G.n; i++) {
        for (j = 0; j < G.n; j++) {
            A[i][j] = G.E[i][j];//遍历读取邻接矩阵
            path[i][j] = -1;//初始化设定所有点都不能到达
        }
    }
    for (k = 0; k < G.n; k++) {
        for (i = 0; i < G.n; i++) {
            for (j = 0; j < G.n; j++) {
                if (A[i][j] > A[i][k] + A[k][j]) {//计算有没有比两点间的直线距离更短的路径
                    A[i][j] = A[i][k] + A[k][j];//将更短的路径写入路径矩阵中
                    path[i][j] = k;//需要通过多少点
                }
            }
        }
    }
    Display_path(A, path, G.n,a,b);
}
void Find_path(int path[][NUMS], int i, int j) {//递归寻找最短路径
    int k;
    k = path[i][j];//k表示还需要通过多少点  如果等于-1则已经到达目的地
    if (k == -1) {
        return;
    }
    Find_path(path, i, k);
    cout << P[k].name << ",";//此时并未到达目的地，输出中间点代表的地点
    Find_path(path, k, j);
}
void Display_path(int A[][NUMS], int path[][NUMS], int n,int start,int end) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (A[i][j] == inf) {
                if (i != j && i == start && j == end) {//此时用户输入的两点之间没有路径
                    cout << "You cannot go from " << P[i].name << " to " << P[j].name <<"!\n";//提示你无法从这里到达那里
                }
            } else if (i == start && j == end) {//如果有路径
                cout << "From " << P[i].name << " to " << P[j].name << " distance: " << A[i][j] <<endl;//输出路径矩阵中符合条件的值
                cout << "Checkpoints :";//并且输出路径
                cout << P[i].name << ",";//输出起始点
                Find_path(path, i, j);//寻找路径
                cout << P[j].name << endl;//输出末尾点
            }
        }
    }
    system("pause");
}
void find_path() {
    system("cls");
    int start, end;
    cout << "***************************" << endl;
    for (int i = 0; i < 8; ++i) {
        cout << "**" <<i + 1 << "-" << P[i].name << endl;
    }
    cout << "***************************" << endl;
    cout << "Please input start point and destination:" << endl;
    cin >> start >> end;
    Graph G;
    Floyd(G,start,end);
}
int main() {
    int choice;
    welcome();
    init();
    while (true) {
        menu();
        cin >> choice;
        switch (choice) {
            case 1:
                information();
                break;
            case 2:
                find_path();
                break;
            case 3:
                return 0;
            default:
                cout << "Please input your choice again." << endl;
                system("pause");
        }
    }
}