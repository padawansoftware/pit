# Coding style

## C

### Function brackets will be in the next line

```C
int function (void)
{
    // code here
}
```

### Library includes must be in order

First, include system libraries and then project libraries

```C
// System libraries
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// Project libraries
#include "command.h"
#include "directory.h"
#include "error.h"
#include "common.h"
```
### Includes in headers

Header files must only include other headers that are used in the header, as part of function declarations or as part of a macro. Other headers that are needed for the implementation of a function, must be included in the corresponding implementation file.

**Good include**

```C
#ifndef _DIRECTORY_H
#define _DIRECTORY_H

// Part of the declaration
#include <stdbool.h>

bool dir_exists(const char path[]);

#endif
```

**Bad include**

```C
#ifndef _DIRECTORY_H
#define _DIRECTORY_H

// Part of the declaration
#include <stdbool.h>

// Part of the implementation, must be in the implementation file
#include <sys/types.h>
#include <dirent.h>

bool dir_exists(const char path[]);

#endif
```




