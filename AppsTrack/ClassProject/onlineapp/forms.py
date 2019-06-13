from django import forms
from onlineapp.models import College, Student, MockTest1



class CollegeForm(forms.ModelForm):
    name = forms.CharField(max_length=128)
    location = forms.CharField(max_length=64)
    acronym = forms.CharField(max_length=8)
    contact = forms.EmailField()

    class Meta:
        model = College
        fields = ('name', 'location', 'acronym', 'contact')


class StudentForm(forms.ModelForm):
    name = forms.CharField(max_length=128)
    dob = forms.DateField(required=False)
    email = forms.EmailField()
    db_folder = forms.CharField(max_length=50)
    dropped_out = forms.BooleanField(required=False, initial=False)

    college = forms.ModelChoiceField(College.objects.all(), widget=forms.HiddenInput())

    class Meta:
        model = Student
        fields = ('name', 'dob', 'email', 'db_folder', 'dropped_out', 'college')


class MockTest1Form(forms.ModelForm):
    problem1 = forms.IntegerField(initial=0)
    problem2 = forms.IntegerField(initial=0)
    problem3 = forms.IntegerField(initial=0)
    problem4 = forms.IntegerField(initial=0)
    total = forms.IntegerField(initial=0, widget=forms.HiddenInput(), required=False)

    student = forms.ModelChoiceField(Student.objects.all(), widget=forms.HiddenInput(), required=False)

    class Meta:
        model = MockTest1
        fields = ('problem1', 'problem2', 'problem3', 'problem4', 'total', 'student')


class LoginForm(forms.Form):
    username = forms.CharField(
        required= True,
        widget=forms.TextInput(
                attrs= {'class': 'input', 'type': 'text', 'placeholders': 'Enter name', 'name' : 'name'}
            ))
    password = forms.CharField(
        required= True,
        widget= forms.PasswordInput(
                attrs= {'class': 'input', 'type': 'password', 'placeholders': 'Enter password', 'name' : 'password'}
            ))

class SignupForm(forms.Form):
    username = forms.CharField(
        required= True,
        widget= forms.TextInput(
                attrs= {'class': 'input', 'type': 'text', 'placeholders': 'Enter name', 'name' : 'username'}
            ))
    password = forms.CharField(
        required= True,
        widget= forms.PasswordInput(
                attrs= {'class': 'input', 'type': 'password', 'placeholders': 'Enter password', 'name' : 'password'}
            ))
    email = forms.CharField(
        required= True,
        widget= forms.PasswordInput(
                attrs= {'class': 'input', 'type': 'email', 'placeholders': 'Enter email', 'name' : 'email'}
            ))
    is_superuser = forms.BooleanField(
        required=True,
        widget= forms.CheckboxInput(
                attrs={'class': 'input', 'type':'checkbox', 'name': 'isAdmin'}
        ))
