import click
import openpyxl
import os
import django
from bs4 import BeautifulSoup
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'ClassProject.settings')
django.setup()

from onlineapp.models import College,Student,MockTest1


def scrap(source):
    soup = BeautifulSoup(open(source), 'lxml')
    data = []

    # table head
    table_head = soup.find_all('th')[1:]
    current = []
    for val in table_head:
        current.append(val.text)
    data.append(current)

    # table data
    table_data = soup.find_all('tr')[1: -1]
    for tr in table_data:
        current = []
        td = tr.findAll('td')[1:]
        for val in td:
            current.append(val.text)
        data.append(current)

    return data


def dump_to_mocktest(data):
    data = data[1:]

    for row in data:
        mock = MockTest1()
        try:
            mock.student = Student.objects.get(db_folder=row[0].split('_')[2])
            mock.problem1 = int(row[1])
            mock.problem2 = int(row[2])
            mock.problem3 = int(row[3])
            mock.problem4 = int(row[4])
            mock.total = int(row[5])
            mock.save()
        except Exception as e:
            print(row[0].split('_')[2], e)
        del mock

def add_college_data(data):
    c = College(name=data[0], location=data[2], acronym=data[1], contact=data[3])
    c.save()
    return

# dummy method
def all_fields_college_data():
    # display all data
    c = College.objects.all()
    data_list = c.values()

    # num_of_records

    len(data_list) # or
    College.objects.count()

    # retrieve only particular fields
    for each_rec in data_list:
        print(each_rec['acronym'], each_rec["contact"])
        # or
    fields= College.objects.values('acronym', 'contact')

    # both particular fields and constraints
    fields = College.objects.values('acronym', 'contact').filter(acronym='gvp')

    # constraints and count
    fields = College.objects.filter(location='vizag').count()

    # retrieving in sorted way ascending
    data = College.objects.values().order_by('acronym')
    # retrieving in sorted way descending
    data = College.objects.values().order_by('-acronym')

    # top 5 elements
    data = College.objects.values().order_by('acronym')[:5]

    # bottom 5 elements
    data = College.objects.values().order_by('-acronym')[-5:]

    #group data
    from django.db.models import Count
    data = College.objects.values('location').annotate(num_sum=Count('location'))

    # two dbs
    data = Student.objects.filter(dropped_out=True).values('college').distinct()

    # num of students in each college
    data = Student.objects.values(College('college')).annotate(num_sum=Count('college'))
    pass

def add_student_data(data):
    s=Student()
    s.name=data[0]
    s.email=data[2]
    s.db_folder=data[3]
    s.dropped_out=0
    s.college = College.objects.get(acronym=data[1])
    s.dob='2019-06-06'
    s.save()
    return

@click.group()
def database():
    pass


@database.command()
@click.argument('student_file', nargs=1)
@click.argument('mock_file',nargs=1)
def importdata(student_file,mock_file):
    student_wb = openpyxl.load_workbook(filename = student_file)
    student_ws = student_wb['Current']
    college_ws = student_wb['Colleges']
    row_num = 1
    for row in college_ws.rows:
        if row_num == 1:
            row_num += 1
            continue
        college_data = []
        for cell in row:
            college_data.append(str(cell.value))
        add_college_data(college_data)
    row_num=1
    for row in student_ws.rows:
        if row_num == 1:
            row_num += 1
            continue
        student_data = []
        for cell in row:
            student_data.append(str(cell.value))
        add_student_data(student_data)

    data = scrap(mock_file)
    dump_to_mocktest(data)



if __name__=='__main__':
    database()