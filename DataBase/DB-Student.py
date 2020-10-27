import MySQLdb

db = MySQLdb.connect(user='student', passwd='123', db='图书管理系统', host='localhost', port=3306,charset='utf8')
cursor=db.cursor()
loginID=''
loginName=''

def welcome():
    print("*******************************")
    print("**                           **")
    print("**    欢迎使用图书借阅系统！   **")
    print("**                           **")
    print("**          学生端            **")
    print("**                           **")
    print("*******************************")

def menu() -> int:
    print("*******************************")
    print("**  1-借阅新的书本            **")
    print("**  2-查询已借书本            **")
    print("**  3-退出登陆                **")
    print("*******************************")
    print("请输入你的选择：",end='')
    a=int(input())
    return a

def quit():
    print("*******************************")
    print("**                           **")
    print("**       系统正在退出...      **")
    print("**                           **")
    print("**      欢迎您的下次使用！     **")
    print("**                           **")
    print("*******************************")

def login() -> bool:
    global loginID,loginName
    idList = []
    pswdList = []
    nameList = []
    cursor.execute("select * from 读者信息表")
    for row in cursor.fetchall():
        idList.append(row[0])
        pswdList.append(row[1])
        nameList.append(row[2])
    id = input("请输入你的用户名：")
    passwd = input("请输入密码：")
    for i in range(len(idList)):
        if id == idList[i] and passwd == pswdList[i]:
            loginID = idList[i]
            loginName = nameList[i]
            print("欢迎，{}！".format(loginName))
            return True
    print("用户名或密码错误！")
    return False

def borrowBooks():
    print("ISBN\t书名\t作者\t\t出版社\t出版日期\t\t书籍分类\t\t在架数量")
    cursor.execute("select * from 图书信息表")
    for row in cursor.fetchall():
        print(row[0], end='\t\t')
        print(row[1], end='\t')
        print(row[2], end='\t')
        print(row[3], end='\t')
        print(row[4], end='\t')
        print(row[5], end='\t')
        print(row[6], end='\n')
    isbn=input("请输入你要借阅的图书ISBN:")
    startDate=input("请输入借书日期：")
    endDate=input("请输入还书日期：")
    sql = """INSERT INTO `图书借阅表`VALUES('{}','{}','{}','{}');""".format(loginID,isbn,startDate,endDate)
    cursor.execute(sql)
    db.commit()
    print("借书任务已提交！")

def inquireBorrowed():
    print("读者学号 \tISBN\t借阅日期\t\t归还日期")
    cursor.execute("select * from 图书借阅表 where 读者学号='{}'".format(int(loginID)))
    for row in cursor.fetchall():
        print(row[0], end='\t')
        print(row[1], end='\t')
        print(row[2], end='\t')
        print(row[3], end='\n')

def main():
    welcome()
    if login():
        while True:
            choice=menu()
            if choice ==1:
                borrowBooks()
            elif choice==2:
                inquireBorrowed()
            elif choice==3:
                input("欢迎您的下次使用！")
                break
    quit()

if __name__ == '__main__':
    main()