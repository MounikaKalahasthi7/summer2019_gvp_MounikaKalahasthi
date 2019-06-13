from django.views import View
from django.shortcuts import render
from onlineapp import models

class StudentView(View):
    def get(self, request, *args, **kwargs):
        print(kwargs['clg_id'])
        name = models.College.objects.values('name').get(acronym=kwargs['clg_id'])
        data = models.MockTest1.objects.values('student__id', 'student__email', 'total').filter(student__college__acronym=kwargs['clg_id'])
        fields = [{'student__id': "student_id", 'student__email': "student_email", 'total':"Mockmarks_total"}]
        return render(request,template_name= 'onlineapp/students.html', context= {'students':data, 'fields': fields, 'name': name['name']})
