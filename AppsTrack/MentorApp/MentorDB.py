import os
from django import setup as dj_setup

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'MentorApp.settings')
dj_setup()

import openpyxl
from bs4 import BeautifulSoup
from onlineapp.models import *

def scrap(source):
    soup = BeautifulSoup(open(source), 'lxml')
    data = []

    # table data
    table_data = soup.find_all('tr')[1:]
    for tr in table_data:
        current = []
        td = tr.findAll('td')[1:]
        for val in td:
            current.append(val.text)
        data.append(current)

    return data

def dump_to_mocktest1(data):
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

def dump_to_student(student_ws, is_dropped):
    row_num=1
    for row in student_ws.rows:
        if row_num == 1:
            row_num += 1
            continue
        student_data = []
        for cell in row:
            student_data.append(str(cell.value))
        s = Student()
        s.name = student_data[0]
        s.email = student_data[2]
        s.db_folder = student_data[3]
        s.dropped_out = is_dropped
        try:
            s.college = College.objects.get(acronym=student_data[1])
            s.save()
        except:
            pass
        del s

def add_college_data(data):
    c = College(name=data[0], location=data[2], acronym=data[1], contact=data[3])
    c.save()
    return


def dump_to_college(college_ws):
    row_num = 1
    for row in college_ws.rows:
        if row_num == 1:
            row_num += 1
            continue
        college_data = []
        for cell in row:
            college_data.append(str(cell.value))
        c = College(name= college_data[0], location=college_data[2], acronym= college_data[1], contact=college_data[3])
        c.save()
        del c
    pass

def importdata():
    student_wb = openpyxl.load_workbook(filename = "populate/students.xlsx")
    student_ws = student_wb['Current']
    college_ws = student_wb['Colleges']
    deletion_ws = student_wb['Deletions']

    dump_to_college(college_ws)
    dump_to_student(student_ws, 0)
    dump_to_student(deletion_ws, 1)

    data = scrap("populate/mocktest.html")
    dump_to_mocktest1(data)

    pass

if __name__ == '__main__':
    importdata()