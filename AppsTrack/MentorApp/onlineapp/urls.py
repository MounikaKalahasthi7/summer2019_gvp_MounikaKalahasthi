from django.urls import path
from onlineapp.views import basic

urlpatterns = [
    path('hello_text', basic.demo_response, name= "dummy_response" ),
    path('hello_template', basic.demo_template, name= "dummy_template"),
]