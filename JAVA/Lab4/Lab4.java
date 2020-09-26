/*
 * ID:18080128
 * Name:孙晨伟
 * Title：实验四
 * Comment：本次实验由于代码量较小，故使用一个java源文件进行提交，仍可进行单个题目的运行。
 */

import java.util.*;

class Question1 {
    public static void main(String[] args) {

        /*这道题用Math.random不是很方便，不如用新学的Collections.shuffle，效果*/
        String[] teamList = {"科特迪瓦", "阿根廷", "澳大利亚", "塞尔维亚", "荷兰", "尼日利亚", "日本",
                "美国", "中国", "新西兰", "巴西", "比利时", "韩国", "喀麦隆", "洪都拉斯", "意大利"};
        List<String> list = Arrays.asList(teamList);//转换成List
        Collections.shuffle(list);//洗牌打乱

        int group = 0;//直接遍历输出
        for (char team = 'A'; team <= 'D'; team++) {
            System.out.println("Group " + team);
            for (int i = 0; i < 4; i++) {
                System.out.print(list.get(group * 4 + i) + ',');//类似数组寻址方式寻找index
            }
            group++;
            System.out.println();
        }
    }

}

class SortSearchMainClass {
    static class Book implements Comparable {//实现comparable接口
        public String name;
        public double price;

        Book(String name, double price) {//添加构造方法，便于创建新对象
            this.name = name;
            this.price = price;
        }

        @Override//确保接口方法继承无误
        public int compareTo(Object o) {
            Book a = (Book) o;
            if (this.price == a.price)//相同返回0
                return 0;
            return this.price < a.price ? -1 : 1;//用尽可能少的语句实现compareTo的功能
        }
    }

    public static void main(String[] args) {
        LinkedList<Book> bookList = new LinkedList<>();//创建书单链表
        bookList.add(new Book("C++基础教程", 29.0));//添加若干元素
        bookList.add(new Book("Java基础教程", 29.0));
        bookList.add(new Book("数据库技术", 29.0));
        bookList.add(new Book("离散数学", 36.7));
        bookList.add(new Book("高等数学", 22.5));
        bookList.add(new Book("我爱Java", 520.0));

        //创建单个Book对象并开始遍历链表
        Book java = new Book("Java与模式", 29.0);
        System.out.println("新书:" + java.name + "(" + java.price + ")与下列图书：");
        for (Book temp : bookList) {//foreach遍历链表
            if (java.compareTo(temp) == 0)
                System.out.println("\t" + temp.name + "(" + temp.price + ");");//尽可能与题目输出格式相同
        }
        System.out.println("价格相同。");
    }
}

class Question3 {
    static class Student {//构造学生类
        public String name;
        public int age;
        public double score;
        public String classNum;

        Student(String name, int age, double score, String classNum) {
            this.name = name;
            this.age = age;
            this.score = score;
            this.classNum = classNum;
        }//便于运行的构造函数
    }

    public static void main(String[] args) {
        List<Student> list4 = new ArrayList<>();//创建三个list，便于输入map中
        List<Student> list5 = new ArrayList<>();
        List<Student> list6 = new ArrayList<>();

        list5.add(new Student("Tom", 18, 100, "class05"));//创建学生对象并添加进list中
        list4.add(new Student("Jerry", 22, 70, "class04"));
        list5.add(new Student("Owen", 25, 90, "class05"));
        list5.add(new Student("Jim", 30, 80, "class05"));
        list6.add(new Student("Steve", 28, 66, "class06"));
        list4.add(new Student("Kevin", 24, 100, "class04"));

        Map<String, List<Student>> map = new HashMap<>();//创建map，并赋予对应键
        map.put("class04", list4);
        map.put("class05", list5);
        map.put("class06", list6);

        /*此处将平均分数和平均年龄一起统计，减少代码容量*/
        int sumAge = 0;
        System.out.println("班级  平均分");
        for (String classNumber : map.keySet()) {//获取map中所有键
            double score = 0;
            for (Student temp : map.get(classNumber)) {//获取单个键中对应list中的所有学生信息
                sumAge += temp.age;
                score += temp.score;
            }
            System.out.println(classNumber + " " + score / map.get(classNumber).size());//获取完一个班级就输出一次信息
        }
        System.out.println("平均年龄：" + sumAge / map.size());//当遍历完所有学生后输出平均年龄。
    }
}