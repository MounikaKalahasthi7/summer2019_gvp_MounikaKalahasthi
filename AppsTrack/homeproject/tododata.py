import click
from os import environ
from django import setup

environ.setdefault('DJANGO_SETTINGS_MODULE', 'homeproject.settings')
setup()

from todoapp.models import *

@click.command()
def populate():
    for list_id in range(1, 6):
        list_var = todolist(name="todolist"+str(list_id))
        list_var.save()
        for item_id in range(1, 6):
            item_var = todoitem(description="list"+str(list_id)+"item"+str(item_id), list_id= todolist.objects.get(id=list_id))
            item_var.save()

if __name__ == '__main__':
    populate()