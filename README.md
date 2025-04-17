# 🚀 ModuLink - The Modular Execution Orchestration Framework (MEOF)

## **📜 What is ModuLink?**
ModuLink is a **Modular Execution Orchestration Framework (MEOF)** that allows **dynamic function linking across multiple programming languages** (C++, JavaScript, TypeScript, Python, and more).

✅ **Supports `.mlk` files as execution maps**  
✅ **Automatically detects functions from imported modules**  
✅ **Provides both CLI execution (`modulink run pipeline.mlk`) & embedded usage (`#include "modulink.h"`)**  
✅ **Enforces full type validation at runtime (C++-based validation)**  
✅ **Infinitely scalable for AI workflows, automation, and modular execution**  

---

## **⚡ Getting Started**
### **1️⃣ Installation**
```sh
make build
```
✅ **This compiles ModuLink into an executable (`modulink`).**  
✅ **The compiled binary can now run `.mlk` execution files.**  

---

### **2️⃣ Running ModuLink**
🔥 **Run `.mlk` execution maps directly**:
```sh
./modulink run tests/pipeline.mlk
```
🔥 **Or embed it inside a C++ project**:
```cpp
#include "modulink.h"

int main() {
    executeMLK("tests/pipeline.mlk");
    return 0;
}
```
✅ **No need to manually define functions—ModuLink detects them dynamically.**  
✅ **Execution is controlled by `.mlk` files, which load dynamically into the runtime.**  

---

## **🛠 How Function Detection Works**
ModuLink **automatically detects functions from imported files inside `.mlk`**.

🔥 **Example `.mlk` File (Imports Instead of Function Registration)**
```mlk
@typescript
import { fetch_data, process_data } from "functions.ts"

@python
import { analyze_data, generate_report } from "utilities.py"

# Define execution flow
[fetch_data -> process_data] as data_pipeline
data_pipeline -> analyze_data -> generate_report
```

✅ **ModuLink extracts function signatures from these imports and registers them automatically.**  

---

## **🔄 Running Execution Pipelines**
🔥 **ModuLink reads the `.mlk` execution file and runs the defined functions dynamically**.

```sh
./modulink run tests/pipeline.mlk
```
Example Output:
```
✅ Execution started...
🔄 Executing: fetch_data
🔄 Executing: process_data
🔄 Executing: analyze_data
✅ Execution completed successfully!
```

🔥 **If a function is missing or the type validation fails, ModuLink will stop execution**:
```
❌ Error: Function `analyze_data` not found.
💡 Fix: Ensure it is correctly imported in your `.mlk` file.
```

🔥 **Example of a Type Mismatch Error:**
```
❌ Type Mismatch: `fetch_data` outputs `object` but `process_data` expects `list<object>`.
💡 Fix: Ensure `fetch_data` returns a type that matches `process_data`'s expected input.
```

✅ **ModuLink enforces full type validation dynamically at runtime (C++ level).**  

---

## **🏗 How ModuLink Works Internally**
### **🔹 Function Detection**
1️⃣ **ModuLink scans `.mlk` for `import` statements.**  
2️⃣ **It then parses those TypeScript/Python files to extract function signatures.**  
3️⃣ **Detected functions are stored in `functionSignatures`.**  

### **🔹 Execution Flow**
1️⃣ **Reads `.mlk` execution pipeline.**  
2️⃣ **Validates function signatures & type safety.**  
3️⃣ **Executes functions in order.**  
4️⃣ **Outputs results or stops on errors.**  

---

## **🧪 Running Tests**
🔥 **Compile and run all tests:**
```sh
make test
```
🔥 **Run a specific test:**
```sh
./modulink_test --gtest_filter=ExecutionTest.ValidPipelineExecution
```

---

## **🔗 What is an MEOF? (Modular Execution Orchestration Framework)**
🔥 **ModuLink is an MEOF—a system that dynamically orchestrates modular function execution across multiple languages, ensuring seamless, scalable, and type-safe execution pipelines.**  

### **🔹 What MEOF Means in Practice**
✅ **Modular** – Function execution is decoupled, reusable, and dynamically linked via `.mlk` files.  
✅ **Execution** – Functions don’t manually call each other—ModuLink orchestrates execution at runtime.  
✅ **Orchestration** – Manages execution flows, validates types, and routes function calls dynamically.  
✅ **Framework** – Provides a structured way to define, execute, and scale function pipelines across languages.  

🚀 **MEOF: The next evolution of modular execution frameworks.**  

---

## **🔗 Next Steps**
✅ **Refine `.mlk` syntax to support advanced function chaining**  
✅ **Allow user-defined function registration inside ModuLink**  
✅ **Develop a UI editor for drag-and-drop function linking**  

🚀 **ModuLink is the future of modular execution—let’s build it together!**  
