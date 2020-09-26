/*
 * Name: 孙晨伟
 * NO. 18080128
 * Date: 2020-5-7
 * Title：实验三-第二题
 */

import java.util.Scanner;

public class Lab32 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入字符串：");//用户输入字符串
        String str = sc.nextLine();//用nextLine防止用户输入带空格字符串

        System.out.println("你输入的是：" + str);//此处用于debug

        char[] strChar = str.toCharArray();//将string转为char数组
        for (int i = 0; i < strChar.length / 2; i++) {
            if (strChar[i] != strChar[strChar.length - 1 - i]) {//直接通过数组下标寻找对应字符
                System.out.println("它不是回文字符串！");
                return;//判断到不是回文字符直接终止程序
            }
        }
        System.out.println("它是回文字符串！");//循环结束，程序未终止，字符串符合条件。
    }
}