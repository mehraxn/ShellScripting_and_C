# Complete Guide to errno in C

## Table of Contents
1. [What is errno?](#what-is-errno)
2. [How errno Works](#how-errno-works)
3. [Common errno Values](#common-errno-values)
4. [Basic Examples](#basic-examples)
5. [Advanced Examples](#advanced-examples)
6. [Best Practices](#best-practices)
7. [Common Pitfalls](#common-pitfalls)
8. [Comparison with Java Exceptions](#comparison-with-java-exceptions)

---

## What is errno?

**errno** (short for "error number") is a **global variable** in C that is used by system calls and library functions to indicate what type of error occurred during an operation.

### Key Characteristics:
- **Global variable**: Accessible from anywhere in your program
- **Integer type**: Contains numeric error codes
- **Set by functions**: Many C standard library functions set it when errors occur
- **Header file**: Defined in `<errno.h>`
- **Not cleared**: Functions that succeed don't reset errno to 0

### Declaration:
```c
#include <errno.h>
// errno is now available as a global variable
```

---

## How errno Works

### The Process:

1. **Call a function** that might fail (like `fopen`, `malloc`, `sqrt`)
2. **Check the return value** to see if an error occurred
3. **If error occurred**, check `errno` to see what went wrong
4. **Use `strerror(errno)`** to get a human-readable error message

### Important Notes:
- ⚠️ **Always check return values first!** Don't check errno without verifying the function failed
- ⚠️ **errno is only set on error**, successful operations don't clear it
- ⚠️ **Check errno immediately** after the function call, as other functions might overwrite it

---

## Common errno Values

| errno Value | Constant | Meaning |
|-------------|----------|---------|
| 1 | EPERM | Operation not permitted |
| 2 | ENOENT | No such file or directory |
| 3 | ESRCH | No such process |
| 4 | EINTR | Interrupted system call |
| 5 | EIO | Input/output error |
| 9 | EBADF | Bad file descriptor |
| 12 | ENOMEM | Cannot allocate memory |
| 13 | EACCES | Permission denied |
| 14 | EFAULT | Bad address |
| 17 | EEXIST | File exists |
| 20 | ENOTDIR | Not a directory |
| 21 | EISDIR | Is a directory |
| 22 | EINVAL | Invalid argument |
| 28 | ENOSPC | No space left on device |
| 33 | EDOM | Numerical argument out of domain |
| 34 | ERANGE | Numerical result out of range |

---

## Basic Examples

### Example 1: File Operations
```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("nonexistent.txt", "r");
    
    if (file == NULL) {
        printf("Error code: %d\n", errno);
        printf("Error message: %s\n", strerror(errno));
        // Output:
        // Error code: 2
        // Error message: No such file or directory
    }
    
    return 0;
}
```

### Example 2: Math Operations
```c
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

int main() {
    double result;
    
    // Clear errno before the operation
    errno = 0;
    
    result = sqrt(-1.0);  // Invalid: square root of negative number
    
    if (errno == EDOM) {
        printf("Domain error occurred!\n");
        printf("Error: %s\n", strerror(errno));
        printf("Result: %f\n", result);
        // Output:
        // Domain error occurred!
        // Error: Numerical argument out of domain
        // Result: -nan
    }
    
    return 0;
}
```

### Example 3: Memory Allocation
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {
    // Try to allocate an impossibly large amount of memory
    size_t huge_size = (size_t)-1;
    void *ptr = malloc(huge_size);
    
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        printf("errno: %d\n", errno);
        printf("Error: %s\n", strerror(errno));
        // Output:
        // Memory allocation failed!
        // errno: 12
        // Error: Cannot allocate memory
    }
    
    return 0;
}
```

---

## Advanced Examples

### Example 4: Multiple File Operations
```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

void openMultipleFiles() {
    FILE *files[3];
    const char *filenames[] = {
        "file1.txt",
        "file2.txt", 
        "file3.txt"
    };
    
    for (int i = 0; i < 3; i++) {
        errno = 0;  // Clear errno before each operation
        
        files[i] = fopen(filenames[i], "r");
        
        if (files[i] == NULL) {
            printf("Failed to open %s\n", filenames[i]);
            printf("  errno: %d (%s)\n\n", errno, strerror(errno));
        } else {
            printf("Successfully opened %s\n", filenames[i]);
            fclose(files[i]);
        }
    }
}

int main() {
    openMultipleFiles();
    return 0;
}
```

### Example 5: Network Operations (Socket)
```c
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in addr;
    
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Socket creation failed!\n");
        printf("errno: %d (%s)\n", errno, strerror(errno));
        return 1;
    }
    
    // Try to bind to a privileged port (requires root)
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);  // Port 80 requires privileges
    addr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("Bind failed!\n");
        printf("errno: %d (%s)\n", errno, strerror(errno));
        // Likely output:
        // errno: 13 (Permission denied)
    }
    
    close(sock);
    return 0;
}
```

### Example 6: Directory Operations
```c
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void demonstrateDirectoryErrors() {
    DIR *dir;
    struct stat statbuf;
    
    // Try to open non-existent directory
    printf("=== Opening non-existent directory ===\n");
    errno = 0;
    dir = opendir("/nonexistent/path");
    if (dir == NULL) {
        printf("errno: %d (%s)\n\n", errno, strerror(errno));
    }
    
    // Try to create directory that already exists
    printf("=== Creating existing directory ===\n");
    mkdir("/tmp", 0755);  // /tmp always exists
    if (errno == EEXIST) {
        printf("errno: %d (%s)\n\n", errno, strerror(errno));
    }
    
    // Try to stat a non-existent file
    printf("=== Stating non-existent file ===\n");
    errno = 0;
    if (stat("ghost_file.txt", &statbuf) == -1) {
        printf("errno: %d (%s)\n\n", errno, strerror(errno));
    }
}

int main() {
    demonstrateDirectoryErrors();
    return 0;
}
```

### Example 7: String to Number Conversion
```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

void demonstrateStrToL() {
    char *endptr;
    long value;
    
    // Test 1: Valid conversion
    printf("=== Test 1: Valid number ===\n");
    errno = 0;
    value = strtol("12345", &endptr, 10);
    if (errno == 0 && *endptr == '\0') {
        printf("Converted successfully: %ld\n\n", value);
    }
    
    // Test 2: Number too large
    printf("=== Test 2: Number out of range ===\n");
    errno = 0;
    value = strtol("99999999999999999999", &endptr, 10);
    if (errno == ERANGE) {
        printf("errno: %d (%s)\n", errno, strerror(errno));
        printf("Value: %ld (LONG_MAX)\n\n", value);
    }
    
    // Test 3: Invalid input
    printf("=== Test 3: Invalid input ===\n");
    errno = 0;
    value = strtol("not_a_number", &endptr, 10);
    if (endptr == "not_a_number") {
        printf("No conversion performed\n");
        printf("errno: %d\n\n", errno);
    }
}

int main() {
    demonstrateStrToL();
    return 0;
}
```

### Example 8: Time Operations
```c
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main() {
    time_t t;
    struct tm *tm_info;
    
    // Get current time
    errno = 0;
    t = time(NULL);
    
    if (t == (time_t)-1) {
        printf("time() failed!\n");
        printf("errno: %d (%s)\n", errno, strerror(errno));
        return 1;
    }
    
    // Convert to local time
    errno = 0;
    tm_info = localtime(&t);
    
    if (tm_info == NULL) {
        printf("localtime() failed!\n");
        printf("errno: %d (%s)\n", errno, strerror(errno));
        return 1;
    }
    
    printf("Current time: %s", asctime(tm_info));
    return 0;
}
```

### Example 9: Process Operations
```c
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    
    // Try to fork
    printf("=== Forking process ===\n");
    errno = 0;
    pid = fork();
    
    if (pid < 0) {
        printf("Fork failed!\n");
        printf("errno: %d (%s)\n", errno, strerror(errno));
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        printf("Child process (PID: %d)\n", getpid());
    } else {
        // Parent process
        printf("Parent process (PID: %d), Child PID: %d\n", getpid(), pid);
    }
    
    return 0;
}
```

### Example 10: Comprehensive Error Handling Function
```c
#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef enum {
    ERR_NONE = 0,
    ERR_FILE_NOT_FOUND,
    ERR_PERMISSION_DENIED,
    ERR_OUT_OF_MEMORY,
    ERR_INVALID_ARGUMENT,
    ERR_IO_ERROR,
    ERR_OTHER
} ErrorType;

ErrorType classifyError(int err_num) {
    switch (err_num) {
        case ENOENT:
            return ERR_FILE_NOT_FOUND;
        case EACCES:
        case EPERM:
            return ERR_PERMISSION_DENIED;
        case ENOMEM:
            return ERR_OUT_OF_MEMORY;
        case EINVAL:
            return ERR_INVALID_ARGUMENT;
        case EIO:
            return ERR_IO_ERROR;
        default:
            return ERR_OTHER;
    }
}

void handleError(const char *operation, int err_num) {
    ErrorType err_type = classifyError(err_num);
    
    printf("Operation: %s\n", operation);
    printf("Error code: %d\n", err_num);
    printf("Error message: %s\n", strerror(err_num));
    
    switch (err_type) {
        case ERR_FILE_NOT_FOUND:
            printf("Action: Check if the file exists\n");
            break;
        case ERR_PERMISSION_DENIED:
            printf("Action: Check file permissions\n");
            break;
        case ERR_OUT_OF_MEMORY:
            printf("Action: Free up memory or reduce allocation size\n");
            break;
        case ERR_INVALID_ARGUMENT:
            printf("Action: Verify function parameters\n");
            break;
        case ERR_IO_ERROR:
            printf("Action: Check device/disk status\n");
            break;
        default:
            printf("Action: Refer to documentation\n");
            break;
    }
    printf("\n");
}

int main() {
    FILE *file;
    
    // Simulate various errors
    errno = 0;
    file = fopen("nonexistent.txt", "r");
    if (file == NULL && errno != 0) {
        handleError("fopen", errno);
    }
    
    errno = 0;
    file = fopen("/root/protected.txt", "r");
    if (file == NULL && errno != 0) {
        handleError("fopen", errno);
    }
    
    return 0;
}
```

---

## Best Practices

### ✅ DO's:

1. **Always clear errno before operations that might set it**
   ```c
   errno = 0;
   result = some_function();
   if (result == ERROR_VALUE && errno != 0) {
       // Handle error
   }
   ```

2. **Check return values first, then errno**
   ```c
   FILE *f = fopen("file.txt", "r");
   if (f == NULL) {  // Check return value first
       printf("Error: %s\n", strerror(errno));  // Then check errno
   }
   ```

3. **Use strerror() for human-readable messages**
   ```c
   printf("Error: %s\n", strerror(errno));
   ```

4. **Use perror() for quick error printing**
   ```c
   perror("fopen");  // Prints: "fopen: No such file or directory"
   ```

5. **Save errno immediately if you need to do other operations**
   ```c
   int saved_errno = errno;
   // Do other operations
   printf("Original error: %s\n", strerror(saved_errno));
   ```

### ❌ DON'Ts:

1. **Don't check errno without verifying the function failed**
   ```c
   // WRONG:
   fopen("file.txt", "r");
   if (errno != 0) { }  // Don't do this!
   
   // RIGHT:
   FILE *f = fopen("file.txt", "r");
   if (f == NULL) {
       // Now check errno
   }
   ```

2. **Don't assume errno is cleared on success**
   ```c
   // WRONG:
   some_function();
   if (errno != 0) { }  // errno might be from previous error!
   ```

3. **Don't use errno for flow control**
   ```c
   // WRONG: Don't use errno as your primary error checking mechanism
   ```

4. **Don't forget that errno can be overwritten**
   ```c
   FILE *f1 = fopen("file1.txt", "r");
   FILE *f2 = fopen("file2.txt", "r");  // This might overwrite errno!
   if (f1 == NULL) {
       // errno might not be from f1 anymore!
   }
   ```

---

## Common Pitfalls

### Pitfall 1: Forgetting to Check errno
```c
// BAD:
FILE *f = fopen("file.txt", "r");
// Forgot to check! Program continues with NULL pointer

// GOOD:
FILE *f = fopen("file.txt", "r");
if (f == NULL) {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return 1;
}
```

### Pitfall 2: errno Gets Overwritten
```c
// BAD:
FILE *f1 = fopen("file1.txt", "r");
printf("Something\n");  // printf might change errno!
if (f1 == NULL) {
    printf("Error: %s\n", strerror(errno));  // Wrong errno!
}

// GOOD:
FILE *f1 = fopen("file1.txt", "r");
if (f1 == NULL) {
    int saved_errno = errno;  // Save immediately
    printf("Something\n");
    printf("Error: %s\n", strerror(saved_errno));
}
```

### Pitfall 3: Not Clearing errno
```c
// BAD:
some_function_that_fails();  // Sets errno to 5
// ... later ...
errno = 0;  // Don't forget to clear!
another_function();  // Succeeds but doesn't clear errno
if (errno != 0) {  // Still 5 from before!
    // False positive!
}

// GOOD:
errno = 0;  // Clear before each check
if (some_function() == ERROR) {
    printf("Error: %s\n", strerror(errno));
}
```

### Pitfall 4: Thread Safety
```c
// PROBLEM: In multi-threaded programs, errno can be a problem
void* thread1(void* arg) {
    FILE *f = fopen("file1.txt", "r");
    // errno might be changed by thread2 here!
    if (f == NULL) {
        printf("Error: %s\n", strerror(errno));  // Wrong!
    }
}

// SOLUTION: Modern C libraries make errno thread-local
// But still save errno immediately to be safe
```

---

## Comparison with Java Exceptions

### C with errno:
```c
FILE *file = fopen("config.txt", "r");
if (file == NULL) {
    fprintf(stderr, "Cannot open config.txt: %s\n", strerror(errno));
    return -1;
}

char buffer[1024];
if (fgets(buffer, sizeof(buffer), file) == NULL) {
    fprintf(stderr, "Cannot read from file: %s\n", strerror(errno));
    fclose(file);
    return -1;
}

fclose(file);
return 0;
```

### Java with exceptions:
```java
try {
    BufferedReader reader = new BufferedReader(
        new FileReader("config.txt")
    );
    String line = reader.readLine();
    reader.close();
} catch (FileNotFoundException e) {
    System.err.println("Cannot open config.txt: " + e.getMessage());
} catch (IOException e) {
    System.err.println("Cannot read from file: " + e.getMessage());
}
```

### Key Differences:

| Feature | C errno | Java Exceptions |
|---------|---------|-----------------|
| **Type** | Global integer variable | Objects (Exception classes) |
| **Propagation** | Manual (must check at each level) | Automatic (up call stack) |
| **Compiler Check** | No | Yes (checked exceptions) |
| **Thread Safety** | Issues with old implementations | Thread-safe |
| **Code Clarity** | Error handling mixed with logic | Separated (try-catch) |
| **Information** | Just error number + message | Full stack trace + custom data |
| **Forgot to Check** | Silent bug | Compiler error or runtime crash |

### Why Java Exceptions are Better:

1. **Automatic Propagation**: Exceptions travel up the call stack automatically
2. **Compiler Enforcement**: You must handle checked exceptions
3. **Rich Information**: Exception objects can contain detailed context
4. **Cleaner Code**: Error handling separated from normal logic
5. **Type Safety**: Different exception types for different errors
6. **No Global State**: Thread-safe by design

### When errno is Still Used:

- System programming (POSIX API)
- Embedded systems
- Legacy C codebases
- Low-level library functions

---

## Summary

**errno** is C's traditional error reporting mechanism, but it has several limitations:

### Advantages:
- ✅ Simple to use
- ✅ Standardized across POSIX systems
- ✅ Minimal overhead
- ✅ Works in low-level code

### Disadvantages:
- ❌ Easy to forget checking
- ❌ Can be overwritten
- ❌ Global state (thread safety concerns)
- ❌ No automatic propagation
- ❌ Makes code messy
- ❌ No compiler enforcement

Modern languages like **Java** use **exceptions** instead, which solve most of errno's problems by providing automatic error propagation, compiler checking, and cleaner code organization.

---

## Additional Resources

- **Manual page**: `man errno`
- **Header file**: `/usr/include/errno.h`
- **List all errno values**: `man errno` or `errno -l` (if errno command is installed)
- **POSIX specification**: https://pubs.opengroup.org/onlinepubs/9699919799/functions/errno.html

---

**Created by**: Your AI Assistant  
**Date**: December 2024  
**Version**: 1.0