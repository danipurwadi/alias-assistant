# Introduction
This project is just a weekend project to try out programming in c. It is not meant for production use and is not even well structured/engineered. The way to use this project is to just clone and modify bits and pieces depending what you need.

# Setup guide
1. Clone the project to local environment
```
$ git clone git@github.com:danipurwadi/alias-assistant.git
```

2. Build the `main.c` file to an executable
```
$ gcc main.c -o main
```

3. You are ready to run it!
```
$ main -h
```

4. For easy use, add it to your own bashrc/zshrc file (you can use the compiled program to use this also)
```
$ main -a aa "<insert_path>/main"
```
Next time you can easily call the program by using the alias `aa`
```
$ aa -h
```