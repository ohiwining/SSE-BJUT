#include <iostream>
using namespace std;
typedef struct node {//定义节点
    int data = -1;//初始值设为-1表示没有存储
    int address = 0;
    int times = 1;//表示搜索次数
} Node;
Node Hash[11];//创建哈希表

void insert(int x) {//插入函数
    Node a;//暂时存储数据
    a.times = 1;
    a.data = x;
    int temp = x;
    int remainder = temp % 11;
    while (Hash[remainder].data != -1) {//寻找合适的节点
        temp++;
        remainder = temp % 11;
        a.times++;
    }
    Hash[remainder].data = a.data;//向哈希表中存储数据
    Hash[remainder].times = a.times;
}

void print() {//输出哈希表函数
    cout << "Data  Address  Times" << endl;
    for (auto &i : Hash) {
        if (i.data != -1)//判断当前行是否没有存储数据
            cout << " " << i.data << "      " << i.address << "       " << i.times << endl;
    }
}

void create() {//创建哈希表
    int numbers[11] = {16, 74, 60, 43, 54, 90, 46, 31, 29, 88, 77};//按照规定顺序
    for (int i = 0; i < 11; ++i) {
        Hash[i].address = i;//初始化哈希表地址
    }
    for (int number :numbers)
        insert(number);//挨个插入数据
    cout << "Create successfully!" << endl;
    print();
}

int search(int x) {//查找函数
    int times = 1, temp = x, remainder = temp % 11;
    while (x != Hash[remainder].data) {//当找到数据时自动退出循环
        temp++;
        times++;
        remainder = temp % 11;
        if (times > 11)
            return -1;//当循环执行11次时，可以判断输入数据不存在
    }
    return times;//返回查找次数
}

void welcome() {//欢迎页面函数
    cout << "************************************" << endl;
    cout << "**  Welcome to use Hash Program!  **" << endl;
    cout << "**                                **" << endl;
    cout << "**          Created by            **" << endl;
    cout << "**           18080128             **" << endl;
    cout << "**          Sun Chenwei           **" << endl;
    cout << "**                                **" << endl;
    cout << "************************************" << endl;
    system("pause");
}

void menu() {//菜单函数，用户选择功能
    cout << "*****************************************" << endl;
    cout << "**1-Create Hash table                  **" << endl;
    cout << "**2-Search for a node                  **" << endl;
    cout << "**3-Insert a node                      **" << endl;
    cout << "**4-Delete a node                      **" << endl;
    cout << "**5-Print hash table                   **" << endl;
    cout << "**6-Quit                               **" << endl;
    cout << "*****************************************" << endl;
    cout << "Please input your choice:";
}

int main() {
    int choice, which_node, times, pos;
    welcome();//欢迎页面
    while (true) {//选择菜单
        system("cls");
        menu();
        cin >> choice;
        system("cls");
        switch (choice) {
            case 1:
                create();//创建哈希表
                system("pause");
                break;
            case 2:
                cout << "Which node you want to search?" << endl;//用户选择要查找哪个节点
                cin >> which_node;
                times = search(which_node);//如果返回值为-1
                if (times == -1)
                    cout << "Not found!" << endl;
                else {
                    cout << "Found!" << endl;//返回值不为-1时则输入数据存在
                    cout << "position: " << (which_node + times) % 11 - 1 << endl << "Searched times: " << times
                         << endl;
                }
                system("pause");
                break;
            case 3:
                cout << "Please input a number:" << endl;//插入一个节点
                cin >> which_node;
                insert(which_node);//直接调用插入函数
                cout << "Insert successfully" << endl;
                print();//输出结果
                system("pause");
                break;
            case 4:
                cout << "Which node you want to delete?" << endl;//用户选择要删除哪个节点
                cin >> which_node;
                pos = search(which_node);
                if (pos == -1) {//返回值为-1，该节点不存在
                    cout << "No such node!" << endl;
                    system("pause");
                    break;
                } else
                    Hash[pos - 1].data = -1;//如果存在，设数据值为-1表示被清除
                cout << "Delete successfully" << endl;
                cout << "Now tree:" << endl;
                print();//输出结果
                cout << endl;
                system("pause");
                break;
            case 5:
                cout << "Hash table: " << endl;//输出结果
                print();
                system("pause");
                break;
            case 6:
                return 0;//程序出口
            default:
                cout << "Wrong input!" << endl;
        }
    }
}