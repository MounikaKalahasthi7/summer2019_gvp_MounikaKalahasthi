from django import forms

class LoginForm(forms.Form):
    username = forms.CharField(
        max_length=128,
        widget=forms.TextInput(
            attrs={
                'class': 'input',
                'placeholder': 'Enter username',
            }
        )
    )

    password = forms.CharField(
        max_length=128,
        widget=forms.PasswordInput(
            attrs={
                'class': 'input',
                'placeholder': 'Enter password',
            }
        )
    )

class SignupForm(forms.Form):
    first_name = forms.CharField(max_length=128, widget=forms.TextInput(attrs={
        'class': 'input',
        'placeholder': 'Enter fullname'
    }))

    email = forms.EmailField(widget=forms.EmailInput(attrs={
        'class': 'input',
        'placeholder': 'Enter Email'
    }))

    username = forms.CharField(max_length=128, widget=forms.TextInput(attrs={
        'class': 'input',
        'placeholder': "Enter username"
    }))

    password = forms.CharField(max_length=128, widget=forms.PasswordInput(attrs={
        'class': 'input',
        'placeholder': 'Enter Password'
    }))