# 🐚 Shebang in Shell Scripts

> A simple guide to understanding what `#!/bin/bash` means, why it matters, and how it is used when running shell scripts on Linux.

---

## 📌 What Is a Shebang?

A **shebang** is the special first line of a script that tells the operating system **which interpreter should execute the file**.

```bash
#!/bin/bash
```

### Breaking it down

| Part | Meaning |
|---|---|
| `#!` | The **shebang** |
| `/bin/bash` | The path to the **Bash interpreter** |

So:

```bash
#!/bin/bash
```

means:

> **Use Bash to execute this script.**

---

## ⚙️ How It Works

Suppose we have a file called `script.sh`:

```bash
#!/bin/bash

echo "Scripting is fun!"
```

After making it executable:

```bash
chmod 755 script.sh
```

we can run it with:

```bash
./script.sh
```

Output:

```text
Scripting is fun!
```

### What happens behind the scenes?

When you execute:

```bash
./script.sh
```

Linux:

1. Opens `script.sh`
2. Reads the first line
3. Finds:

   ```bash
   #!/bin/bash
   ```

4. Starts the Bash interpreter
5. Bash reads and executes the remaining commands

Conceptually, this is similar to running:

```bash
/bin/bash script.sh
```

---

## 🧠 Why Is the Shebang Important?

Without a shebang, the operating system does not get an explicit instruction about **which interpreter should execute the script** when you run it directly.

The shebang makes the script:

- ✅ Clear about which interpreter it requires
- ✅ Directly executable with `./script.sh`
- ✅ More predictable across environments
- ✅ Easier for other developers to understand

---

## 📍 The Shebang Must Be First

The shebang should be the **very first line** of the script.

### ✅ Correct

```bash
#!/bin/bash
echo "Hello!"
```

### ❌ Incorrect

```bash

#!/bin/bash
echo "Hello!"
```

There should not be a blank line before the shebang.

---

## 🔀 Different Scripts Can Use Different Interpreters

The idea is not specific to Bash.

### Bash

```bash
#!/bin/bash
```

### POSIX Shell

```bash
#!/bin/sh
```

### Python

```python
#!/usr/bin/python3
```

The general form is:

```text
#!path-to-interpreter
```

---

## 🌍 A More Portable Bash Shebang

You may also see:

```bash
#!/usr/bin/env bash
```

Instead of assuming Bash is located exactly at `/bin/bash`, this asks `env` to locate `bash` using the system's `PATH`.

### Comparison

| Shebang | Meaning |
|---|---|
| `#!/bin/bash` | Use Bash specifically from `/bin/bash` |
| `#!/usr/bin/env bash` | Find Bash through the current `PATH` |

For many Linux systems:

```bash
#!/bin/bash
```

is perfectly normal.

For scripts intended to run across different Unix-like systems, you will often see:

```bash
#!/usr/bin/env bash
```

---

## 🚀 Complete Example

### `script.sh`

```bash
#!/bin/bash

name="Milad"

echo "Hello, $name!"
echo "Scripting is fun!"
```

Give the script execute permission:

```bash
chmod 755 script.sh
```

Run it:

```bash
./script.sh
```

Output:

```text
Hello, Milad!
Scripting is fun!
```

---

## 🔐 Why Do We Use `chmod`?

A script file is not always executable by default.

This command:

```bash
chmod 755 script.sh
```

changes its permissions.

`755` means:

| User | Permission |
|---|---|
| Owner | `rwx` → read, write, execute |
| Group | `r-x` → read, execute |
| Others | `r-x` → read, execute |

The important permission here is:

```text
x = execute
```

After that, the script can be launched directly:

```bash
./script.sh
```

---

## ❓ `./script.sh` vs `bash script.sh`

These commands are related, but they are not exactly the same.

### Direct execution

```bash
./script.sh
```

The operating system looks at the **shebang** to determine the interpreter.

### Explicit Bash execution

```bash
bash script.sh
```

You are explicitly telling Bash to read the file.

In this case, Bash has already been chosen from the command line, so the shebang is not what selects the interpreter.

---

## ⚠️ Common Mistakes

### 1. Forgetting execute permission

```bash
./script.sh
```

may produce:

```text
Permission denied
```

Fix:

```bash
chmod +x script.sh
```

---

### 2. Writing the wrong interpreter path

For example:

```bash
#!/wrong/path/bash
```

The operating system will not be able to find the requested interpreter.

You can check where Bash is located with:

```bash
which bash
```

Typical output:

```text
/usr/bin/bash
```

or:

```text
/bin/bash
```

---

### 3. Putting something before the shebang

Avoid:

```bash
# My script
#!/bin/bash
```

Instead:

```bash
#!/bin/bash

# My script
```

The shebang belongs on **line 1**.

---

## 📝 Quick Reference

```bash
#!/bin/bash
```

**Meaning:** Use Bash to execute this script.

```bash
chmod +x script.sh
```

**Meaning:** Give the script execute permission.

```bash
./script.sh
```

**Meaning:** Execute `script.sh` from the current directory.

```bash
bash script.sh
```

**Meaning:** Explicitly ask Bash to execute `script.sh`.

---

## 🎯 Key Takeaway

> `#!/bin/bash` tells the operating system:
>
> **“Execute this file using the Bash interpreter.”**

It is called the **shebang**, and it should normally be the **first line of a directly executable shell script**.

---

### ⭐ One-line memory trick

```text
#!  →  "Which interpreter should run this file?"
```
