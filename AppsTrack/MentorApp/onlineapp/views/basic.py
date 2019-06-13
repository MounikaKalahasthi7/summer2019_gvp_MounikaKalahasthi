from django.http import HttpResponse
from django.shortcuts import render

def demo_response(request):
    return HttpResponse("Hello")

def demo_template(request):
    return render(
        request,
        template_name= 'onlineapp/demo.html',
        context={
            'page_title' : 'demo',
            'data' : ['hello', ]
        })
