from onlineapp.models import *
from onlineapp.forms import CollegeForm, StudentForm, MockTest1Form, LoginForm, SignupForm
from django.views import View
from django.shortcuts import render, get_object_or_404, reverse, redirect
from django.http import HttpResponseRedirect
from django.contrib.auth import authenticate, login, logout
from django.contrib import messages
from django.contrib.auth.models import User


class CollegeView(View):
    def get(self, request, *args, **kwargs):
        if not request.user.is_authenticated :
            return HttpResponseRedirect('/login/')

        if self.request.path == reverse('add_college'):
            form = CollegeForm()
            return render(request, 'onlineapp/add_college.html', {
                'form': form
            })

        if kwargs:
            if self.request.path == reverse('edit_college', kwargs={'college_acronym': kwargs['college_acronym']}):
                form = CollegeForm()
                college = College.objects.get(acronym=kwargs['college_acronym'])
                form.fields['name'].initial = college.name
                form.fields['location'].initial = college.location
                form.fields['acronym'].initial = college.acronym
                form.fields['contact'].initial = college.contact

                return render(request, 'onlineclass/add_college.html', {
                    'form': form
                })


            if self.request.path == reverse('delete_college', kwargs={'college_acronym': kwargs['college_acronym']}):
                MockTest1.objects.filter(student__college__acronym=kwargs['college_acronym']).delete()
                Student.objects.filter(college__acronym=kwargs['çollege_acronym']).delete()
                College.objects.filter(acronym=kwargs['college_acronym']).delete()

            acronym = kwargs['acronym']
            students = MockTest1.objects.values('student__id', 'student__name', 'total').filter(student__college__acronym=acronym)
            return render(
                 request,
                 template_name="onlineapp/students.html",
                 context={
                   'coll': students,
                    'college': kwargs['acronym']
                 }
            )

        college = College.objects.all()
        return render(
              request,
              template_name="onlineapp/colleges.html",
              context={
                 'coll': college,
                 'title': 'All college | OnlineApp',
              })

    def post(self, request, *args, **kwargs):
        if not request.user.is_authenticated :
            return HttpResponseRedirect('/login/')

        if kwargs:
            student_form = StudentForm(request.POST)
            mocktest1_form = MockTest1Form(request.POST)

            if student_form.is_valid() and mocktest1_form.is_valid():
                student_form.save(commit=True)
                mocktest1_form = mocktest1_form.save(commit=False)
                mocktest1_form.total = mocktest1_form.problem1 + mocktest1_form.problem2 + mocktest1_form.problem3 + mocktest1_form.problem4
                mocktest1_form.student = Student.objects.get(db_folder=request.POST['db_folder'])
                mocktest1_form.save()

            return HttpResponseRedirect('/colleges/{0}/'.format(kwargs['acronym']))

        if self.request.path == reverse('colleges'):
            try:
                college = College.objects.get(acronym=request.POST['acronym'])

                form = CollegeForm(request.POST, instance=college)
                if form.is_valid():
                    form = form.save(commit=False)
                    form.save()
            except:
                form = CollegeForm(request.POST)

                if form.is_valid():
                    form.save(commit=True)

        return HttpResponseRedirect('/colleges/')

class StudentView(View):
    def get(self, request, *args, **kwargs):
        if not request.user.is_authenticated :
            return HttpResponseRedirect('/login/')

        if self.request.path == reverse('add-student', kwargs={'college_acronym': kwargs['college_acronym']}):
            student_form = StudentForm()
            student_form.fields['college'].initial = College.objects.get(acronym=kwargs['college_acronym'])

            mocktest1_form = MockTest1Form()

            return render(request, 'onlineapp/add_student.html', {
                'student_form': student_form,
                'mocktest1_form': mocktest1_form,
                'college_acronym': kwargs['college_acronym']
            })

        if self.request.path == reverse('delete_student', kwargs={'college_acronym': kwargs['college_acronym']}):
            MockTest1.objects.filter(student__college__acronym=kwargs['college_acronym']).delete()
            Student.objects.filter(college_acronym=kwargs['college-acronym']).delete()
            return HttpResponseRedirect('/colleges/{}/'.format(kwargs['college_acronym']))

    def post(self, request, *args, **kwargs):
        if not request.user.is_authenticated :
            return HttpResponseRedirect('/login/')

        form = StudentForm(request.POST)

        if form.is_valid():
            form.save(commit=True)

        return HttpResponseRedirect('/colleges/{0}/'.format(kwargs['college_acronym']))

class LoginView(View):
    def get(self, request, *args, **kwargs):
        if self.request.path == reverse('user_login'):
            form = LoginForm()
            title = 'login'
            action = 'login'
        else:
            form = SignupForm()
            title = 'Signup'
            action = 'signup'
        return render(request, 'onlineapp/login.html', context={'form' : form, 'title': title, 'action': action})

    def post(self, request, *args, **kwargs):

        if self.request.path == reverse('user_login'):
            input_form = LoginForm(request.POST)
            print('entered user_login')
            user = None
            if input_form.is_valid():
                user = authenticate(request, username=input_form.cleaned_data['username'],
                                    password=input_form.cleaned_data['password'])

            if user is not None:
                login(request, user)
                return HttpResponseRedirect('/colleges/')
            else:
                messages.error(request, 'invalid credentials')

        if self.request.path == reverse('user_signup'):
            input_form = SignupForm(request.POST)
            print('entered user_signup')
            if input_form.is_valid():
                user = User.objects.create_user(**input_form.cleaned_data)
                user.save()

        return  HttpResponseRedirect('/colleges/')


def user_logout(request):
    logout(request)
    return HttpResponseRedirect('/login/')