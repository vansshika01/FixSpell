
# FixSpell 🔍✨  
A fast and efficient **console-based spell checker** built in **C++**, using the **Trie data structure** for quick prefix lookups and auto-suggestions. Ideal for beginners and intermediate learners looking to understand how spell correction, data structures, and file handling work together in real-world applications.

---

## 🚀 Features

- ✅ Loads dictionary from a text file (`dictionary.txt`)
- 📚 Uses **Trie** for prefix-based suggestions
- 🔍 Provides up to 5 most relevant suggestions for incorrect inputs
- 🧠 Uses **Edit Distance (Levenshtein Algorithm)** for fuzzy matching
- ⚡ Fast lookups and real-time response in the terminal
- 🛠️ Built with clean and modular C++ code

---

## 📂 Project Structure

FixSpell/
│
├── FixSpell.cpp        # Main source code  
├── dictionary.txt      # Word list (500 common English words)  
└── README.md           # Project description  

---

## 🧠 Data Structures Used

- **Trie (Prefix Tree)**: Fast insert and search operations, O(L) time complexity where L is word length.  
- **Edit Distance Algorithm**: Computes similarity between user input and dictionary words when no prefix matches are found.  

---

## 🖥️ How It Works

1. Loads 500+ common English words from `dictionary.txt`.
2. Builds a Trie to enable fast lookups and prefix auto-suggestions.
3. Takes user input.
4. If input is valid, confirms correct spelling.
5. If input is incorrect:
   - Suggests up to 5 words with similar prefixes.
   - If no prefix match is found, falls back to fuzzy matching using edit distance.

---

## 🛠️ How to Run

### ✅ Prerequisites
- C++ compiler (G++ recommended)  
- Terminal or Command Prompt  

### ⚙️ Compilation
```bash
g++ FixSpell.cpp -o FixSpell
📘 dictionary.txt
A plain text file containing 500+ common English words — one word per line.
You can expand this file with a larger dictionary or domain-specific vocabulary.

