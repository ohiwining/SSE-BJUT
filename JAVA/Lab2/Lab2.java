/*
* Coder:18080128
* Name:孙晨伟
* Date:2020-4-29
* Content:实验二：动物园
*/
abstract class Animal{//定义动物抽象类
    String name;
    int legNum=0;
    public abstract String getName();//获取名称的抽象函数
    public abstract void Shout();//模拟动物叫声的抽象函数
}
interface Terrestrial{//陆生动物接口，仅用在陆生动物上
    int getLegNum();//获取腿的条数
}
class Cat extends Animal implements Terrestrial{//定义猫的类，继承动物类，实现陆生动物接口
    Cat(String name,int leg){//猫的带参数构造函数
        this.name=name;
        this.legNum=leg;
    }
    public void Shout(){//模拟猫叫的函数，下同
        System.out.println("喵喵喵...");
    }
    public String getName(){//获取猫名称的函数，下同
        return this.name;
    }
    public int getLegNum(){//获取猫腿条数的函数，下同
        return this.legNum;
    }
}
class Duck extends Animal implements Terrestrial{//定义鸭子的类，继承动物类，实现陆生动物接口
    Duck(String name,int leg){//鸭子的带参数构造函数
        this.name=name;
        this.legNum=leg;
    }
    public void Shout(){
        System.out.println("嘎嘎嘎...");
    }
    public String getName(){
        return this.name;
    }
    public int getLegNum(){
        return this.legNum;
    }
}
class Dolphin extends Animal{//定义海豚的类，继承动物类，不实现陆生动物接口
    Dolphin(String name){//海豚的带参数构造函数
        this.name=name;
    }
    public String getName(){
        return this.name;
    }
    public void Shout(){
        System.out.println("海豚音...");
    }
}
public class Lab2{
    public static void main(String[] args) {
        //打印表头
        System.out.println("动物名字\t腿的条数\t动物叫");
        //创建动物类数组及内部元素
        Animal[] list={new Cat("加菲猫",4),new Duck("唐小鸭",2),new Dolphin("海豚奇奇")};

        //使用for-each语句来遍历内部成员
        for (Animal animal:list) {
            System.out.print(animal.getName()+"\t");//输出动物名称
            //如果该动物是陆生动物
            if(animal instanceof Terrestrial){
                System.out.print(((Terrestrial) animal).getLegNum()+"\t");//使用类型转换即可实现陆生动物接口
            }
            else{//否则该动物不是陆生动物，腿的条数为0
                System.out.print(0+"\t");
            }
            animal.Shout();//输出动物的叫声
        }
    }

}