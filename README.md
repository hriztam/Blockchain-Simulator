# Blockchain-Simulator

A simple blockchain simulation in C++ that mimics the core features of a blockchain. This project demonstrates fundamental concepts like block structure, hashing, proof-of-work, and chain validation.

## 🚀 Features

- **Block Structure:** Each block contains an index, timestamp, transaction data, previous block hash, current block hash, and a nonce.
- **Hashing:** SHA-256 hashing algorithm to secure block data.
- **Proof-of-Work:** A basic mechanism to make block creation computationally intensive.
- **Chain Validation:** Ensures the integrity of the blockchain by verifying hashes.
- **Tampering Simulation:** Ability to tamper with a block and detect the breach through validation.

## 🛠️ Requirements

- C++ compiler (e.g., GCC)
- OpenSSL library (for SHA-256 hashing)

Install OpenSSL (if not already installed):

```sh
brew install openssl
brew --prefix openssl
```

## 🔧 Build and Run

### Compile the program:

Replace "/usr/local" with the path u got from --prefix openssl

```sh

g++ blockchain.cpp -o blockchain -I/usr/local/include -L/usr/local/lib -lssl -lcrypto -std=c++11
```

Run the program:

```sh
./blockchain
```

## 🧠 How It Works

1. **Genesis Block:** The first block is hardcoded.
2. **Adding Blocks:** New blocks can be added with dummy transaction data.
3. **Proof-of-Work:** Mining adjusts the nonce until the hash meets a difficulty condition.
4. **Validation:** The blockchain checks if all blocks are correctly linked and hashes match.
5. **Tampering:** A block can be modified, and the validation process will catch the manipulation.

## 🧾 Example Output

```
Initial Blockchain:
Index: 0
Transactions: Genesis Block
Current Hash: 0000abc123...

Index: 1
Transactions: Transaction 1: A -> B
Current Hash: 0000def456...

Is blockchain valid? Yes

Blockchain after tampering:
Index: 1
Transactions: Tampered Transaction 1: X -> Y
Current Hash: 12345xyz...

Is blockchain valid? No
```

## 📂 Project Structure

```
.
├── blockchain.cpp   # Main source code
├── README.md        # Project documentation
```

## 🚩 Improvements

- Implement Merkle Trees for transaction integrity.
- Add networking to simulate P2P nodes.
- Handle dynamic difficulty adjustment.
- Ability to dynamically add transactions to blocks before mining

## 🧑‍💻 Contributing

Feel free to fork the repository and submit a pull request for any improvements!

## 📜 License

This project is licensed under the MIT License.

---
