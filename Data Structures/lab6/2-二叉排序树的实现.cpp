#include <iostream>
using namespace std;
typedef struct node//定义节点类型
{
    int data;
    node *l = nullptr;//初始化左右孩子为空指针
    node *r = nullptr;
} Node;
bool balanced = true;//用于判断树是否为排序树  默认为true

void welcome() {//欢迎页面函数
    cout << "************************************" << endl;
    cout << "**  Welcome to use Tree Program!  **" << endl;
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
    cout << "**1-Create a ordered tree              **" << endl;
    cout << "**2-Judge whether tree is ordered      **" << endl;
    cout << "**3-Search for a node (Recursion)      **" << endl;
    cout << "**4-Search for a node (non-Recursion)  **" << endl;
    cout << "**5-Delete a node                      **" << endl;
    cout << "**6-Print this tree                    **" << endl;
    cout << "**7-Quit                               **" << endl;
    cout << "*****************************************" << endl;
    cout << "Please input your choice:";
}

void print(Node *a) {//输出树中所有数据，使用递归
    if (a != nullptr) {//如果传入节点不为空则继续进行输出
        cout << a->data;
        if (a->l != nullptr || a->r != nullptr) {
            cout << "(";
            print(a->l);
            if (a->r != nullptr)
                cout << ",";
            print(a->r);
            cout << ")";
        }
    }
}

void insert(Node *&a, int x) {//插入节点函数
    if (a == nullptr) {
        a = new node;//分配内存
        a->data = x;//如果当前节点为空，则该节点用于插入数据
        return;
    } else if (x < a->data)//如果当前节点不为空则判断要往哪个方向走
        insert(a->l, x);
    else
        insert(a->r, x);
}

Node *Create(Node *a) {//创建排序树主函数
    int numbers[10] = {4, 9, 0, 1, 8, 6, 3, 5, 2, 7};//创建顺序
    for (int number : numbers) {
        insert(a, number);
    }
    print(a);//最后输出结果
    return a;
}

void judgement(Node *a) {//判断是否为排序树
    if (a->l != nullptr) {
        if (a->l->data > a->data)
            balanced = false;//此时不符合排序树定义，判断为false
        judgement(a->l);
    }
    if (a->r != nullptr) {
        if (a->r->data < a->data)
            balanced = false;
        judgement(a->r);//向左或向右走继续判断
    }
}

void search_recursion(Node *a, int x) {//递归方式查找节点
    if (x == a->data) {
        cout << x << ". " << endl;
        return;//找到节点时，直接输出
    } else if (x < a->data) {//判断要查找数字与当前节点数据的大小来决定方向
        cout << a->data << " ";
        search_recursion(a->l, x);
    } else if (x > a->data) {
        cout << a->data << " ";
        search_recursion(a->r, x);
    }
}

void search_non_recursion(Node *a, int x) {//使用非递归来查找节点
    while (a) {
        if (x == a->data) {//语句与递归类似
            cout << a->data << ". " << endl;
            return;
        } else if (x < a->data) {
            cout << a->data << " ";
            a = a->l;
        } else if (x > a->data) {
            cout << a->data << " ";
            a = a->r;
        }
    }
}

void delete_node(Node *&a, int x) {//删除一个节点
    if (x < a->data)
        delete_node(a->l, x);//如果要删除的节点不是当前节点，则通过判断大小来选择方向
    else if (x > a->data)
        delete_node(a->r, x);
    else if (x == a->data) {//此时找到要删除的节点
        if (!a->l && !a->r) {//如果该节点是叶子
            Node *temp = a;
            a = nullptr;//设置为空指针并释放内存
            delete temp;
            return;
        } else if (!a->l && a->r) {//如果该节点有左分支或右分支
            Node *temp = a;
            a = a->r;
            delete temp;//使用分支来代替当前节点
        } else if (a->l && !a->r) {
            Node *temp = a;
            a = a->l;
            delete temp;
        } else if (a->l && a->r) {//如果该节点既有左分支又有右分支
            Node *min = a->r;
            Node *temp = min;
            while (min->l) {//寻找右分支中最小的节点，该节点的数据离要删除的数据差距最小
                temp = min;
                min = min->l;
            }
            a->data = min->data;//替换要删除的节点的数据
            if (min == temp) {
                a->r = min->r;
            } else {
                temp->l = min->l;
            }
            delete min;//释放内存
        }
    }
}

int main() {
    int choice, which_node;
    Node *root = nullptr;
    welcome();
    while (true) {//选择菜单
        system("cls");
        menu();
        cin >> choice;
        system("cls");
        switch (choice) {
            case 1:
                root = Create(root);//创建一个排序树
                cout << endl << "Ordered tree created." << endl;
                system("pause");
                break;
            case 2:
                judgement(root);//判断是否为排序树
                if (balanced)
                    cout << "It is a ordered tree." << endl;
                else
                    cout << "It is not a ordered tree." << endl;
                system("pause");
                break;
            case 3:
                cout << "Which node you want to search?" << endl;//用户选择要查找哪个节点
                cin >> which_node;
                cout << "Path (Recursion):";
                search_recursion(root, which_node);
                system("pause");
                break;
            case 4:
                cout << "Which node you want to search?" << endl;
                cin >> which_node;
                cout << "Path (non-Recursion):";
                search_non_recursion(root, which_node);
                system("pause");
                break;
            case 5:
                cout << "Which node you want to delete?" << endl;//用户选择要删除哪个节点
                cin >> which_node;
                delete_node(root, which_node);
                cout << "Delete successfully" << endl;
                cout << "Now tree:" << endl;
                print(root);//输出结果
                cout << endl;
                system("pause");
                break;
            case 6:
                cout << "Tree: " << endl;//仅用来输出结果
                print(root);
                cout << endl;
                system("pause");
                break;
            case 7:
                return 0;//程序出口
            default:
                cout << "Wrong input!" << endl;
        }
    }
}