/*
 * ID:18080128
 * Name:孙晨伟
 * Title：实验七-第二题
 * Date：2020-6-4
 */

class Cashier {//定义收银员类，专门负责收银找零
    public int fiveNum;

    Cashier() {
        fiveNum = 3;
    }//构造函数，初始条件是有三张五元钱

    public synchronized void checkOut(String name, int putMoney) {//找零函数，负责检查顾客需要的零钱
        if (putMoney == 5) {//如果付款刚好是5块钱
            fiveNum++;//五元钱数量加一
            System.out.println("五元钱剩余数量：" + fiveNum);
            System.out.println(name + "成功购票！");//显示成功购票
            notify();//此时无论如何一定能找零了
        } else if (putMoney > 5) {//当付款大于5元时
            int needFiveNum = (putMoney / 5) - 1;//需要找零的五元张数
            for (int i = 0; i < needFiveNum; i++) {
                if (fiveNum == 0)//此时没有五元零钱了
                    try {
                        wait();//此时无法找零，只好挂起
                    } catch (InterruptedException ignored) {
                    }
                fiveNum--;//此时有多余的五元零钱
                System.out.println("五元钱剩余数量：" + fiveNum);
            }
            System.out.println(name + "成功购票！");//显示成功购票
        }
    }
}


class Customer extends Thread {//顾客类
    public int money;
    Cashier cashier;
    String name;

    Customer(String n, int m, Cashier ca) {
        name = n;
        money = m;
        cashier = ca;//线程共用一个收银员
    }

    public void run() {
        System.out.println(name + "来排队购票了。");//用来表明线程启动顺序的
        cashier.checkOut(name, money);
    }
}

public class Question2 {
    public static void main(String[] args) {
        Cashier cashier = new Cashier();//构造收银员项
        System.out.println("开始一共有三张五元");

        /*注：代码是按照小张、小李、小赵的顺序编写的，运行可能并不按照这个顺序*/
        new Customer("小张", 20, cashier).start();
        new Customer("小李", 10, cashier).start();
        new Customer("小赵", 5, cashier).start();

    }
}