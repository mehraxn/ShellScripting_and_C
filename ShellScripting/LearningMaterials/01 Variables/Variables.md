# 🐚 Bash Variables — A Practical Guide

A standalone guide to **creating, naming, assigning, expanding, and using variables in Bash**.

This README covers the essential rules for Bash variables, including:

- variable assignment syntax
- valid and invalid variable names
- case sensitivity
- `$VARIABLE` and `${VARIABLE}`
- why braces matter
- single quotes `'...'` vs double quotes `"..."`
- assigning command output with `$(...)`
- common mistakes and best practices

---

## 📚 Table of Contents

- [What Is a Variable?](#-what-is-a-variable)
- [Creating a Variable](#-creating-a-variable)
- [The Most Important Assignment Rules](#-the-most-important-assignment-rules)
- [Using a Variable](#-using-a-variable)
- [`$VARIABLE` vs `${VARIABLE}`](#-variable-vs-variable)
- [Why Braces Sometimes Matter](#-why-braces-sometimes-matter)
- [Single Quotes vs Double Quotes](#-single-quotes-vs-double-quotes)
- [Can a Variable Be Assigned with Single Quotes?](#-can-a-variable-be-assigned-with-single-quotes)
- [Assigning Command Output to a Variable](#-assigning-command-output-to-a-variable)
- [Variable Naming Rules](#-variable-naming-rules)
- [Case Sensitivity](#-case-sensitivity)
- [Uppercase or Lowercase Variable Names?](#-uppercase-or-lowercase-variable-names)
- [Variables Are Usually Strings](#-variables-are-usually-strings)
- [Shell Variables vs Environment Variables](#-shell-variables-vs-environment-variables)
- [Useful Commands](#-useful-commands)
- [Common Mistakes](#-common-mistakes)
- [Complete Example](#-complete-example)
- [Quick Reference](#-quick-reference)

---

# 📦 What Is a Variable?

A variable is a **named place used to store a value**.

You can think of it as a name-value pair:

```text
NAME  →  VALUE
```

For example:

```bash
MY_SHELL="bash"
```

Here:

- `MY_SHELL` is the **variable name**
- `bash` is the **value**

Later, the stored value can be accessed using `$`:

```bash
echo "$MY_SHELL"
```

Output:

```text
bash
```

---

# ✍️ Creating a Variable

The basic Bash syntax is:

```bash
VARIABLE_NAME="value"
```

Example:

```bash
NAME="Milad"
```

Another example:

```bash
MY_SHELL="bash"
```

> [!IMPORTANT]
> When **assigning** a variable, do **not** put `$` before the variable name.

✅ Correct:

```bash
NAME="Milad"
```

❌ Incorrect:

```bash
$NAME="Milad"
```

The `$` is normally used when you want to **read/expand the value** of a variable.

---

# 🚨 The Most Important Assignment Rules

## Rule 1 — No spaces around `=`

This is correct:

```bash
NAME="Milad"
```

These are incorrect:

```bash
NAME = "Milad"
```

```bash
NAME= "Milad"
```

```bash
NAME ="Milad"
```

Bash uses spaces to separate words and commands, so spaces around `=` change the meaning of the line.

### Easy rule to remember

```text
VARIABLE=value
```

There should be:

```text
NO SPACE before =
NO SPACE after  =
```

---

## Rule 2 — Quotes are not always required

All of these assignments are valid:

```bash
NAME=Milad
NAME="Milad"
NAME='Milad'
```

For simple literal text such as `Milad`, they store the same visible value.

However, the type of quoting becomes very important when the value contains:

- spaces
- `$VARIABLE` references
- command substitutions
- wildcard characters
- special shell characters

For safe and readable shell scripts, quoting values is usually a good habit.

---

# 🔎 Using a Variable

After assigning:

```bash
MY_SHELL="bash"
```

you can access its value using `$`:

```bash
echo "$MY_SHELL"
```

Output:

```text
bash
```

You can also place it inside other text:

```bash
echo "I like the $MY_SHELL shell."
```

Output:

```text
I like the bash shell.
```

---

# 🔤 `$VARIABLE` vs `${VARIABLE}`

Bash provides two common ways to expand a variable:

```bash
$VARIABLE
```

and:

```bash
${VARIABLE}
```

For many simple cases, they do exactly the same thing.

Example:

```bash
MY_SHELL="bash"

echo "$MY_SHELL"
echo "${MY_SHELL}"
```

Output:

```text
bash
bash
```

So this:

```bash
echo "I like the $MY_SHELL shell."
```

and this:

```bash
echo "I like the ${MY_SHELL} shell."
```

both produce:

```text
I like the bash shell.
```

---

# 🧩 Why Braces Sometimes Matter

Braces tell Bash **exactly where the variable name ends**.

Suppose:

```bash
MY_SHELL="bash"
```

and you want to print:

```text
I am bashing on my keyboard.
```

You might try:

```bash
echo "I am $MY_SHELLing on my keyboard."
```

But Bash reads:

```text
$MY_SHELLing
```

as a reference to a variable named:

```text
MY_SHELLing
```

—not as `$MY_SHELL` followed by `ing`.

If `MY_SHELLing` is undefined, its expansion is empty, so the output becomes:

```text
I am  on my keyboard.
```

## ✅ Correct solution

Use braces:

```bash
echo "I am ${MY_SHELL}ing on my keyboard."
```

Bash now clearly sees:

```text
${MY_SHELL} + ing
```

Output:

```text
I am bashing on my keyboard.
```

### Memory rule

Use:

```bash
${VARIABLE}
```

when characters immediately after the variable could be interpreted as part of its name.

---

# 💬 Single Quotes vs Double Quotes

This is one of the most important Bash concepts.

Both types of quotes can be used in variable assignments, but they behave differently.

| Syntax | Variable expansion? | Command substitution? | Best description |
|---|---:|---:|---|
| `'...'` | ❌ No | ❌ No | Keep text **literal** |
| `"..."` | ✅ Yes | ✅ Yes | Keep text together but still **expand** variables/commands |
| unquoted | ✅ Yes | ✅ Yes | More shell interpretation; use carefully |

---

## 🔴 Single Quotes `'...'`

Single quotes preserve the content **literally**.

Example:

```bash
NAME="Milad"
MESSAGE='Hello $NAME'
```

Now:

```bash
echo "$MESSAGE"
```

Output:

```text
Hello $NAME
```

Why?

Because inside single quotes:

```bash
$NAME
```

is treated as ordinary text.

It is **not expanded**.

---

## 🟢 Double Quotes `"..."`

Double quotes allow variable expansion.

Example:

```bash
NAME="Milad"
MESSAGE="Hello $NAME"
```

Now:

```bash
echo "$MESSAGE"
```

Output:

```text
Hello Milad
```

Bash expands `$NAME` while creating the value of `MESSAGE`.

---

## Side-by-side example

```bash
NAME="Milad"

A='Hello $NAME'
B="Hello $NAME"

echo "$A"
echo "$B"
```

Output:

```text
Hello $NAME
Hello Milad
```

So the key idea is:

```text
'...'  → literal text
"..."  → expansion is allowed
```

---

# ✅ Can a Variable Be Assigned with Single Quotes?

**Yes. Absolutely.**

This is valid Bash:

```bash
NAME='Milad'
```

This is also valid:

```bash
MESSAGE='Hello world'
```

Single quotes are especially useful when you want the value to be stored **exactly as written**.

For example:

```bash
PRICE='The cost is $20'
```

Then:

```bash
echo "$PRICE"
```

Output:

```text
The cost is $20
```

The `$` remains literal because it was inside single quotes during the assignment.

---

## When should I use `'...'` or `"..."`?

Use **single quotes** when you want everything to remain literal:

```bash
TEXT='The variable is $HOME'
```

Stored value:

```text
The variable is $HOME
```

Use **double quotes** when you want Bash to expand something:

```bash
TEXT="My home directory is $HOME"
```

Possible stored value:

```text
My home directory is /home/milad
```

---

# 🖥️ Assigning Command Output to a Variable

Bash can run a command and save its output in a variable.

The modern syntax is:

```bash
VARIABLE=$(command)
```

This is called **command substitution**.

Example:

```bash
SERVER_NAME=$(hostname)
```

The command:

```bash
hostname
```

might output:

```text
linuxsvr
```

Therefore:

```bash
SERVER_NAME=$(hostname)
```

stores:

```text
linuxsvr
```

inside `SERVER_NAME`.

Now:

```bash
echo "You are running this script on ${SERVER_NAME}."
```

could output:

```text
You are running this script on linuxsvr.
```

---

## Another command substitution example

```bash
CURRENT_USER=$(whoami)

echo "Current user: $CURRENT_USER"
```

Possible output:

```text
Current user: milad
```

---

## `$(...)` vs backticks

Older shell scripts may use:

```bash
SERVER_NAME=`hostname`
```

This can work, but modern Bash code should generally prefer:

```bash
SERVER_NAME=$(hostname)
```

because `$(...)` is easier to read and easier to nest.

---

# 🏷️ Variable Naming Rules

A Bash variable name may contain:

- letters: `A-Z`, `a-z`
- digits: `0-9`
- underscore: `_`

However, the **first character cannot be a digit**.

A good simplified rule is:

```text
[A-Za-z_][A-Za-z0-9_]*
```

---

## ✅ Valid variable names

```bash
FIRST3LETTERS="ABC"
```

```bash
FIRST_THREE_LETTERS="ABC"
```

```bash
firstThreeLetters="ABC"
```

```bash
first_three_letters="ABC"
```

```bash
_name="ABC"
```

---

## ❌ Invalid variable names

### Starts with a number

```bash
3LETTERS="ABC"
```

❌ Invalid because a variable name cannot begin with a digit.

---

### Contains a hyphen

```bash
first-three-letters="ABC"
```

❌ Invalid because `-` is not allowed in a Bash variable name.

Use underscores instead:

```bash
first_three_letters="ABC"
```

---

### Contains `@`

```bash
first@Three@Letters="ABC"
```

❌ Invalid because `@` is not allowed in an ordinary variable name.

---

## Naming summary

| Name | Valid? | Reason |
|---|---:|---|
| `NAME` | ✅ | Letters only |
| `MY_NAME` | ✅ | Underscore allowed |
| `name2` | ✅ | Digit allowed after first character |
| `_NAME` | ✅ | May start with `_` |
| `2NAME` | ❌ | Cannot start with a digit |
| `MY-NAME` | ❌ | Hyphen not allowed |
| `MY@NAME` | ❌ | `@` not allowed |
| `MY NAME` | ❌ | Spaces not allowed |

---

# 🔠 Case Sensitivity

Bash variable names are **case-sensitive**.

These are three different variables:

```bash
NAME="one"
Name="two"
name="three"
```

Example:

```bash
echo "$NAME"
echo "$Name"
echo "$name"
```

Output:

```text
one
two
three
```

So:

```text
NAME ≠ Name ≠ name
```

---

# 🔡 Uppercase or Lowercase Variable Names?

Some introductory material uses uppercase names such as:

```bash
MY_SHELL="bash"
SERVER_NAME="linuxsvr"
```

That is valid Bash.

However, a useful modern convention is:

- **lowercase** names for variables created inside your own scripts
- **UPPERCASE** names for exported environment variables, shell-defined variables, and constants/configuration-style values

For example:

```bash
user_name="Milad"
file_count=10
```

and environment variables commonly look like:

```bash
HOME
PATH
USER
SHELL
```

Using lowercase for ordinary script variables reduces the chance of accidentally overwriting important shell/environment variables.

> [!NOTE]
> Uppercase is not a syntax requirement. Bash accepts both uppercase and lowercase names.

---

# 🧵 Variables Are Usually Strings

Bash does not require you to declare a variable type before assigning it.

For example:

```bash
NAME="Milad"
AGE=25
```

Bash variables are generally treated as strings unless they are used in an arithmetic context or given special attributes.

Example:

```bash
A=5
B=3

echo "$A"
```

Output:

```text
5
```

For arithmetic:

```bash
echo $((A + B))
```

Output:

```text
8
```

---

# 🌍 Shell Variables vs Environment Variables

A normal assignment creates a **shell variable**:

```bash
MY_NAME="Milad"
```

It exists in the current shell.

To export it to programs started from that shell:

```bash
export MY_NAME
```

Or do both at once:

```bash
export MY_NAME="Milad"
```

Common environment variables include:

```bash
HOME
PATH
USER
SHELL
```

Example:

```bash
echo "$USER"
echo "$HOME"
```

---

# 🛠️ Useful Commands

## Display a variable

```bash
echo "$NAME"
```

For robust formatted output, `printf` is often preferred:

```bash
printf '%s\n' "$NAME"
```

---

## Remove a variable

```bash
unset NAME
```

After:

```bash
unset NAME
```

the variable is no longer defined.

---

## Make a variable read-only

```bash
readonly APP_NAME="MyApp"
```

Trying to change it later will cause an error:

```bash
APP_NAME="OtherApp"
```

---

## Check whether a variable is empty

```bash
if [[ -z "$NAME" ]]; then
    echo "NAME is empty"
fi
```

---

# ⚠️ Common Mistakes

## 1. Putting spaces around `=`

❌ Wrong:

```bash
NAME = "Milad"
```

✅ Correct:

```bash
NAME="Milad"
```

---

## 2. Using `$` while assigning

❌ Wrong:

```bash
$NAME="Milad"
```

✅ Correct:

```bash
NAME="Milad"
```

Use `$` when reading the value:

```bash
echo "$NAME"
```

---

## 3. Forgetting braces when adding text directly after a variable

Given:

```bash
MY_SHELL="bash"
```

❌ Problematic:

```bash
echo "$MY_SHELLing"
```

Bash searches for the variable `MY_SHELLing`.

✅ Correct:

```bash
echo "${MY_SHELL}ing"
```

Output:

```text
bashing
```

---

## 4. Expecting expansion inside single quotes

```bash
NAME="Milad"

echo 'Hello $NAME'
```

Output:

```text
Hello $NAME
```

If expansion is wanted:

```bash
echo "Hello $NAME"
```

Output:

```text
Hello Milad
```

---

## 5. Creating an invalid variable name

❌ Wrong:

```bash
my-name="Milad"
```

✅ Correct:

```bash
my_name="Milad"
```

---

## 6. Forgetting that names are case-sensitive

```bash
NAME="Milad"

echo "$name"
```

`NAME` and `name` are different variables.

---

# 🚀 Complete Example

Create a file called:

```text
variables.sh
```

with:

```bash
#!/bin/bash

# Simple variable
user_name="Milad"

# Variable containing a literal value
literal_message='The variable syntax is $VARIABLE'

# Command substitution
server_name=$(hostname)

# Normal expansion
echo "Hello, $user_name!"

# Braces make the variable boundary explicit
echo "You are running this script on ${server_name}."

# Single quotes preserved $VARIABLE literally during assignment
echo "$literal_message"

# Braces are necessary when text follows immediately
MY_SHELL="bash"
echo "I am ${MY_SHELL}ing on my keyboard."
```

Possible output:

```text
Hello, Milad!
You are running this script on linuxsvr.
The variable syntax is $VARIABLE
I am bashing on my keyboard.
```

---

# 🧪 Quote Comparison Example

This short example demonstrates the difference clearly:

```bash
#!/bin/bash

NAME="Milad"

A='Hello $NAME'
B="Hello $NAME"
C=Hello

echo "$A"
echo "$B"
echo "$C"
```

Output:

```text
Hello $NAME
Hello Milad
Hello
```

### What happened?

```bash
A='Hello $NAME'
```

Single quotes → `$NAME` stays literal.

```bash
B="Hello $NAME"
```

Double quotes → `$NAME` is expanded.

```bash
C=Hello
```

No quotes → simple single-word assignment is valid.

---

# 📌 Quick Reference

| Task | Bash syntax |
|---|---|
| Assign text | `name="Milad"` |
| Assign literal text | `text='$HOME'` |
| Read a variable | `$name` |
| Explicit variable boundary | `${name}` |
| Assign command output | `host=$(hostname)` |
| Export a variable | `export name="Milad"` |
| Remove a variable | `unset name` |
| Read-only variable | `readonly name="Milad"` |

---

## 🎯 Core Rules to Remember

```text
1. Assign:       VARIABLE="value"
2. No spaces:    VARIABLE = "value"   ❌
3. Read value:   $VARIABLE
4. Safer form:   ${VARIABLE}
5. Literal:      '...'
6. Expand:       "..."
7. Command out:  VARIABLE=$(command)
8. Names:        letters, digits, underscore
9. First char:   cannot be a digit
10. Bash names:  case-sensitive
```

---

## 🧠 One-Minute Summary

### Creating a variable

```bash
MY_SHELL="bash"
```

### Reading it

```bash
echo "$MY_SHELL"
```

### Adding characters immediately after it

```bash
echo "${MY_SHELL}ing"
```

### Literal value

```bash
TEXT='Hello $USER'
```

`$USER` is **not expanded**.

### Expand a variable inside a value

```bash
TEXT="Hello $USER"
```

`$USER` **is expanded**.

### Save a command's output

```bash
SERVER_NAME=$(hostname)
```

---

> **Key idea:** In Bash, use `VARIABLE=value` to assign and `$VARIABLE` or `${VARIABLE}` to retrieve the value. Use single quotes for literal text and double quotes when you want Bash expansion.
