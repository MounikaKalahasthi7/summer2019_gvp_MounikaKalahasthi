from django.conf.urls import url
from onlineapp.views import college, student

urlpatterns = [
    # url(r'^$', views.hello.as_view()),
    # url(r'^hello', views.hello),
    # url('get_my_college', views.get_college_name),
    # url('get_all_colleges', views.get_all_colleges),
    # url('get_colleges_template', views.get_all_colleges_template),
    # url(r'^get_all_students/(?P<name>\d+)/$', views.get_all_students),

    url(r'^colleges/$', college.CollegeView.as_view()),
    url(r'^students/(?P<clg_id>\D+)/$', student.StudentView.as_view())
]
