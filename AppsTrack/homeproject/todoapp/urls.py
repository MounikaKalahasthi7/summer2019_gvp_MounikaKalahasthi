from django.urls import path
from todoapp.views.auth_view import *

urlpatterns = [
    path('login/', LoginController.as_view(), name='login'),
    path('signup/', SignupController.as_view(), name='signup'),
    path('logout/', logout_user, name='logout')
]
