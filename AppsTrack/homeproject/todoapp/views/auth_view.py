from django.contrib import messages
from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.views import View
from django.contrib.auth.models import User
from django.contrib.auth import login, authenticate, logout
from django.contrib.auth.decorators import login_required
from todoapp.auth import LoginForm, SignupForm


class LoginController(View):
    def get(self, request):
        # if request.user.is_authenticated:
        #     return HttpResponseRedirect('/colleges/')

        form = LoginForm()
        return render(request, 'auth.html', {
            'form': form,
            'page_title': 'Login',
        })

    def post(self, request):
        login_form = LoginForm(request.POST)
        if login_form.is_valid():
            user = authenticate(
                request,
                username=login_form.cleaned_data['username'],
                password=login_form.cleaned_data['password']
            )
            if user is not None:
                login(request, user)
            else:
                messages.error(request, "Invalid Credentials")
        else:
            print(login_form.errors)

        return HttpResponseRedirect('/login/')


class SignupController(View):
    def get(self, request):
        form = SignupForm()
        return render(request, 'auth.html', {
            'form': form,
            'page_title' : 'SignUp',
        })

    def post(self, request):
        signup_form = SignupForm(request.POST)

        if signup_form.is_valid():
            new_user = User.objects.create_user(**signup_form.cleaned_data)
            login(request, user=new_user)
            return HttpResponseRedirect('/colleges/')
        else:
            print(signup_form.errors)

        signup_form = SignupForm()
        return render(request, 'onlineclass/signup.html', {
            'signup_form': signup_form
        })


@login_required()
def logout_user(request):
    logout(request)
    return HttpResponseRedirect('/login/')