### OOP Lab Work №2

**“Matrix: Reloaded”**

---

### **Description**

You need to modify the **“Matrix”** program created in Lab Work №1 by adding a **new input parameter** — the **line generation frequency**.

After starting, the program should request **four parameters**:

1. **Line generation frequency**
2. **Line speed**
3. **Line length**
4. **Epilepsy mode flag**

Once all parameters are entered, the animation begins.

---

### **Work Requirements**

* Implement input and **“foolproof” validation** for the new parameter.
* **Line generation frequency:** 1–30 (lines per second).
* In **command-line (CLI)** mode, the new parameter is added as the **first argument**.

Example program launch with:

* line generation frequency = 3
* speed = 23
* length = 8
* epilepsy mode = ON

```
matrix.exe 3 23 8 Y
```

* The **total number of lines appearing per second** must match the specified **generation frequency**.
* If the frequency is **n lines per second**, then **n random time intervals** in the range **0–1000 milliseconds** (within one second) should be generated.

  * These intervals determine **when** each line starts moving.

**Example:**
If the generated intervals are **200 ms**, **700 ms**, and **400 ms**,
then the lines begin moving in the following order:

* First line — after **200 ms**

* Second line — after **400 ms**

* Third line — after **700 ms**

* As in Lab Work №1, each line should **crawl out from behind the starting border** of the screen and **move to the opposite border**.

---

### **Implementation Requirements**

The program must include at least **three classes**:

1. **Character Class**
2. **Line Class**
3. **Application Manager Class**

Optionally, a **utility class** can be implemented to handle system functions (console operations, input/output, etc.).

Methods should be **logically distributed** among the classes.
For example:

* The **Line** class should control its **movement** and **speed**.
* The **Application Manager** should control the overall application, **coordinate** the movement of lines, etc.

> The logic of line operation must be implemented **without using threads**.
> Memory management must follow **C++ style** (manual memory control).

## Run programm
```bash
make build

./solution.out
```