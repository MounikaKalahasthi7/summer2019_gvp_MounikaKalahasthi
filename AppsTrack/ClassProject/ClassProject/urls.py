"""ClassProject URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.conf import settings
from django.conf.urls import url
from django.urls import include, path

from onlineapp.views.college import CollegeView, StudentView, LoginView, user_logout

urlpatterns = [
    # url(r'^$', views.hello, name="onlinepp"),
    path('colleges/', CollegeView.as_view(), name='colleges_html'),
    path('colleges/add-college/', CollegeView.as_view(), name='add_college'),
    path('colleges/<str:acronym>/delete-college/', CollegeView.as_view(), name='delete_college'),
    path('colleges/<str:acronym>/edit-college/', CollegeView.as_view(), name='edit_college'),
    # path('colleges/<str:acronym>/edit-college-form/', CollegeView.as_view(), name='edit_college_form'),
    path('colleges/<str:acronym>/', CollegeView.as_view(), name='students_html'),
    path('colleges/<str:college_acronym>/add-student/', StudentView.as_view(), name='add-student'),
    path('colleges/<str:college_acronym>/delete-student/', StudentView.as_view(), name='delete_student'),
    path('login/', LoginView.as_view() , name='user_login'),
    path('logout/', user_logout, name='user_logout'),
    path('signup/', LoginView.as_view(), name='user_signup'),

    url('^onlineapp/', include('onlineapp.urls')),
    path('admin/', admin.site.urls),
]

if settings.DEBUG:
    import debug_toolbar
    urlpatterns = [
        path('__debug__/', include(debug_toolbar.urls)),
    ] + urlpatterns