from django.db import models

class todolist(models.Model):
    name = models.CharField(max_length=128)
    current_datetime = models.DateField(auto_now_add=True)

    def __str__(self):
        return self.name

class todoitem(models.Model):
    description = models.CharField(max_length=128)
    due_date = models.DateField(null=True, blank=True)
    completed = models.BooleanField(default=False)
    list_id = models.ForeignKey(todolist, on_delete=models.CASCADE)