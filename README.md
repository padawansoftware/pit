# PIT

PIT is an application and a set of bash scripts ment to improve common tasks in console.

This version is very little and does not offer great functionalities or garanties.

## Installation

PIT is formed by a couple of parts: the application, written in C, that is the core and a set of bash scripts that extends the functionality.

### Installing application

From `pit/application` directory

```bash
make
make install
```

### Installing bash scripts

From `pit/scripts` directory

```bash
./install.sh
```

In your `~/.bashrc` include
```bash
source /usr/share/pit/pit
```

## Functionalities

### pit path

Allows to create a path alias. You can use it then with cd command.

```bash
# Create path alias
pit path add myPath /my/custom/path

# Use path alias
cd myPath
```

### pit cmd

Allows to create an script command. You can write the script in any script languaje as long as you include the shebang

```bash
# Create a new script command
pit cmd add myCommand
```

```bash
#!/bin/bash

echo This is myCommand
```

### pit exec

Allows to execute script commands created by pit cmd

```bash
# Execute script command
pit exec myCommand
```

## Limitations

It has only been tested in Ubuntu Linux and bash


## License

MIT