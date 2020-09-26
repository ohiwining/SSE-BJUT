/* 18080128 孙晨伟
   时间：2020-4-15
   编写语言：Java14 2020-3-7
   Default encoding: utf-8
*/

import java.util.Scanner;//包含输入包

public class Lab1 {
    public static void Question4(int a) {//第四题所需函数
        for (int i = 1; i <= a; i++) {
            if (a % i == 0) {
                System.out.print(i + " ");
            }
        }
        System.out.println();
    }

    public static int Question5(int i) {//第五题所需函数
        return (1 + i) * i / 2;
    }

    public static int Question6(int a) {//第六题所需函数
        if (a == 1 || a == 0)//判断特殊情况
            return 1;
        else {
            int result2 = 1;//此处需要和第二题不一样的变量名否则会出错
            for (int i = 2; i <= a; i++) {
                result2 *= i;
            }
            return result2;
        }
    }

    public static void main(String[] args) {
        //第一题
        int a = 0;
        for (int i = 1; i <= 100; i++) {
            a += i;
        }
        System.out.println("第一题：sigma 100 = " + a);
        //此处可能需要类型转换，即String.valueOf(int)但我这里可以正常运行，下同。

        //第二题
        System.out.println("第二题：请输入0-9之间的数：");
        Scanner sc = new Scanner(System.in);
        int var1 = sc.nextInt();
        if (var1 < 10 && var1 >= 2) {//判断特殊情况
            int result = 1;
            for (int i = 1; i <= var1; i++) {
                result *= i;
            }
            System.out.println("结果 " + var1 + "! = " + result);
        } else if (var1 == 1 || var1 == 0) {
            System.out.println("结果" + var1 + "! = 1");
        } else {
            System.out.println("输入的数请在0-9之间！");
        }

        //第三题
        System.out.println("第三题：所有合适的数: ");
        for (int i = 3; i <= 99; i++) {
            if (i % 3 == 0 && i % 5 != 0) {
                System.out.print(i + " ");
            }
        }
        System.out.println();//用于输出格式的排版

        //第四题
        System.out.println("第四题：请输入一个数:");
        int var3 = sc.nextInt();
        System.out.println("它的因子:");
        Question4(var3);

        //第五题
        System.out.println("第五题：请输入一个数:");
        int var4 = sc.nextInt();
        System.out.println("结果：" + Question5(var4));

        //第六题
        System.out.println("第六题：请输入一个数:");
        int var5 = sc.nextInt();
        System.out.println("结果：" + Question6(var5));
    }
}