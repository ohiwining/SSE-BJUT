import MySQLdb

db = MySQLdb.connect(user='manager', passwd='123', db='图书管理系统', host='localhost', port=3306,charset='utf8')
cursor=db.cursor()
loginID=''
loginName=''

def welcome():
    print("*******************************")
    print("**                           **")
    print("**    欢迎使用图书管理系统！   **")
    print("**                           **")
    print("**         管理员端           **")
    print("**                           **")
    print("*******************************")

def menu() -> int:
    print("*******************************")
    print("**  1-管理书本信息            **")
    print("**  2-管理学生借阅请求         **")
    print("**  3-管理学生归还请求         **")
    print("**  4-退出登陆                **")
    print("*******************************")
    print("请输入你的选择：",end='')
    a=int(input())
    return a

def manageBookMenu()->int:
    print("*******************************")
    print("**  1-添加图书                **")
    print("**  2-删除图书                **")
    print("**  3-更新图书信息            **")
    print("**  4-查询图书                **")
    print("**  5-退出功能                **")
    print("*******************************")
    print("请输入你的选择：", end='')
    a = int(input())
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
    nameList=[]
    cursor.execute("select * from 管理员信息表")
    for row in cursor.fetchall():
        idList.append(row[0])
        pswdList.append(row[1])
        nameList.append(row[2])
    id=input("请输入你的用户名：")
    passwd=input("请输入密码：")
    for i in range(len(idList)):
        if id ==idList[i] and passwd==pswdList[i]:
            loginID=idList[i]
            loginName=nameList[i]
            print("欢迎，{}！".format(loginName))
            return True
    print("用户名或密码错误！")
    return False

def manageBooks():
    while True:
        choice = manageBookMenu()
        if choice == 1:
            bookList = []
            cursor.execute("select * from 图书信息表")
            for row in cursor.fetchall():
                bookList.append(row[0])
            isbn = input("请输入ISBN：")
            for i in range(len(bookList)):
                if isbn == bookList[i]:
                    print("该书已存在！")
                    return
            name = input("请输入书名：")
            author = input("请输入作者：")
            publish = input("请输入出版社：")
            date = input("请输入出版日期：")
            category = input("请输入书籍分类：")
            number = input("请输入在架数量：")
            sql="""INSERT INTO 图书信息表 VALUES('{}','{}','{}','{}','{}','{}','{}');""".format(isbn,name,author,publish,date,category,number)
            cursor.execute(sql)
            db.commit()
        elif choice == 2:
            bookList = []
            cursor.execute("select * from 图书信息表")
            for row in cursor.fetchall():
                bookList.append(row[0])
            isbn = input("请输入ISBN：")
            for i in range(len(bookList)):
                if isbn == bookList[i]:
                    sql = """DELETE FROM 图书信息表 WHERE isbn={}""".format(int(isbn))
                    cursor.execute(sql)
                    db.commit()
                    print("删除成功！")
                    return
            print("未找到此图书！")
        elif choice == 3:
            bookList = []
            cursor.execute("select * from 图书信息表")
            for row in cursor.fetchall():
                bookList.append(row[0])
            isbn = input("请输入ISBN：")
            for i in range(len(bookList)):
                if isbn == bookList[i]:
                    name = input("请输入书名：")
                    author = input("请输入作者：")
                    publish = input("请输入出版社：")
                    date = input("请输入出版日期：")
                    category = input("请输入书籍分类：")
                    number = input("请输入在架数量：")
                    sql = """UPDATE 图书信息表 SET ISBN={},书名='{}',作者='{}',出版社='{}',出版日期='{}',书籍分类='{}',在架数量='{}' WHERE ISBN='{}'""".format(int(isbn),name,author,publish,date,category,number,int(isbn))
                    cursor.execute(sql)
                    db.commit()
                    print("更新成功！")
                    return
            print("未找到此书！")
        elif choice == 4:
            print("ISBN\t书名\t作者\t\t出版社\t出版日期\t\t书籍分类\t\t在架数量")
            cursor.execute("select * from 图书信息表")
            for row in cursor.fetchall():
                print(row[0],end='\t\t')
                print(row[1], end='\t')
                print(row[2], end='\t')
                print(row[3], end='\t')
                print(row[4], end='\t')
                print(row[5], end='\t')
                print(row[6], end='\n')
        elif choice == 5:
            break

def manageBorrow():
    cursor.execute("select * from 图书借阅表")
    print("读者学号\tISBN\t结束日期\t还书日期")
    for row in cursor.fetchall():
        print(row[0],end='\t')
        print(row[1], end='\t')
        print(row[2], end='\t')
        print(row[3], end='\n')
    inputId=input('请输入要处理的学号:')
    times=input('请输入借书的次数:')
    sql = """INSERT INTO 管理员_读者表 VALUES('{}','{}','未还','暂无','{}');""".format(loginID, inputId, times)
    cursor.execute(sql)
    db.commit()
    print("处理完成。\n当前借阅结果：")
    loginId=int(loginID)
    cursor.execute("select * from 管理员_读者表 where 工作号='{}'".format(loginId))
    print("工作号\t读者学号\t借还确认\t违章状况\t借书累计")
    for row in cursor.fetchall():
        print(row[0], end='\t')
        print(row[1], end='\t')
        print(row[2], end='\t')
        print(row[3], end='\t')
        print(row[4], end='\n')

def manageReturn():
    cursor.execute("select * from 管理员_读者表 where 工作号='{}'".format(int(loginID)))
    print("工作号\t读者学号\t借还确认\t违章状况\t借书累计")
    for row in cursor.fetchall():
        print(row[0], end='\t')
        print(row[1], end='\t')
        print(row[2], end='\t')
        print(row[3], end='\t')
        print(row[4], end='\n')
    input("即将处理上述请求。")
    sql = """UPDATE 管理员_读者表 SET 借还确认='已还'"""
    cursor.execute(sql)
    db.commit()
    cursor.execute("select * from 管理员_读者表 where 工作号='{}'".format(int(loginID)))
    print("工作号\t读者学号\t借还确认\t违章状况\t借书累计")
    for row in cursor.fetchall():
        print(row[0], end='\t')
        print(row[1], end='\t')
        print(row[2], end='\t')
        print(row[3], end='\t')
        print(row[4], end='\n')
    input("处理完成。")

def main():
    welcome()
    if login():
        while True:
            choice=menu()
            if choice ==1:
                manageBooks()
            elif choice==2:
                manageBorrow()
            elif choice==3:
                manageReturn()
            elif choice==4:
                input("欢迎您的下次使用！")
                break
    quit()

if __name__ == '__main__':
    main()