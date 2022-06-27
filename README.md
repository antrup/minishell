# minishell
Simple shell in C

### Dependencies

#### Readline library
sudo apt-get install libreadline-dev (ubuntu)

#### Clang

### Build
make

### Run
./minishell

### Features
- command history
- redirections
- pipes
- environment variables
- && and || with parenthesis for priorities
- builtins:
  ◦ echo with option -n
  ◦ cd with only a relative or absolute path
  ◦ pwd with no options
  ◦ export with no options
  ◦ unset with no options
  ◦ env with no options or arguments
  ◦ exit with no options
