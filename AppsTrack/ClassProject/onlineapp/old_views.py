from django.shortcuts import render
from django.http import HttpResponse
from onlineapp.models import *
import os

# def get_college_name(request):
#     clg_name = College.objects.values('name').get(acronym='gvp')
#     clg_name = clg_name['name']
#     return HttpResponse(clg_name)
#
# def get_all_colleges_template(request):
#     clgs = College.objects.values('id','acronym', 'name')
#     CONTEXT_DIR = dict()
#     CONTEXT_DIR['data'] = clgs
#     return render(request, 'onlineapp/all_colleges.html', context= CONTEXT_DIR)
#
# def get_all_students(request, name):
#     data = MockTest1.objects.values('student__id','student__name', 'total').filter(student__college__id = name)
#     CONTEXT_DIR = dict()
#     name = College.objects.values('name').get(id=name)
#     CONTEXT_DIR['clg_name'] = name['name']
#     CONTEXT_DIR['fields'] = [{'student__id': "student_id", 'student__name': "student_name", 'total':"Mockmarks_total"}]
#     CONTEXT_DIR['data'] = data
#     return render(request, 'onlineapp/clg_students.html', CONTEXT_DIR)
#
# def get_all_colleges(request):
#     print("I'm called")
#     clgs = College.objects.values('id', 'acronym', 'name')
#     data = "<table>"
#     for each_acronym in clgs:
#         data += "<tr>"
#         data += "<td>" + each_acronym['acronym'] + "</td>"
#         data += "<td>" + each_acronym['name'] + "</td>"
#         data += "</tr>"
#     data += "</data>"
#     return HttpResponse(data)
#
# def hello(request):
#     file = os.path.dirname(os.path.abspath(__file__))
#     file = os.path.join(file, 'hello.html')
#     data = open(file)
#     data = data.read()
#
#     # data = request.headers['foo']
#
#     return HttpResponse(data)

