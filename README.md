# StockExchange
Order book and Matching engine simulator built in C++
# Current Project Status
- The app is able to match limit orders placed through client tcp connections with price-time priority and send back match confirmation messages using FIX.
- TODO:
  - Implement pro-rata matching with strategy design pattern
  - Benchmarking and optimization
  - Create Enums for each FIX protocol code to avoid magic numbers scattered throughout application.
